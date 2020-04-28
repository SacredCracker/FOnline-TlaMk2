#include "scriptfilesystem.h"

#if defined(_WIN32)
#include <direct.h> // _getcwd
#include <Windows.h> // FindFirstFile, GetFileAttributes

#else
#include <unistd.h> // getcwd
#include <dirent.h> // opendir, readdir, closedir
#include <sys/stat.h> // stat
#endif
#include <assert.h> // assert

using namespace std;

BEGIN_AS_NAMESPACE

// TODO: The file system should have a way to allow the application to define in
//       which sub directories it is allowed to make changes and/or read

ScriptFileSystem *ScriptFileSystem_Factory()
{
	return new ScriptFileSystem();
}

void RegisterScriptFileSystem_Native()
{
	int r;

	r = ASEngine->RegisterObjectType("filesystem", 0, asOBJ_REF); assert( r >= 0 );
	r = ASEngine->RegisterObjectBehaviour("filesystem", asBEHAVE_FACTORY, "filesystem @f()", asFUNCTION(ScriptFileSystem_Factory), asCALL_CDECL); assert( r >= 0 );
	r = ASEngine->RegisterObjectBehaviour("filesystem", asBEHAVE_ADDREF, "void f()", asMETHOD(ScriptFileSystem,AddRef), asCALL_THISCALL); assert( r >= 0 );
	r = ASEngine->RegisterObjectBehaviour("filesystem", asBEHAVE_RELEASE, "void f()", asMETHOD(ScriptFileSystem,Release), asCALL_THISCALL); assert( r >= 0 );
	
	r = ASEngine->RegisterObjectMethod("filesystem", "bool changeCurrentPath(const string &in)", asMETHOD(ScriptFileSystem, ChangeCurrentPath), asCALL_THISCALL); assert( r >= 0 );
	r = ASEngine->RegisterObjectMethod("filesystem", "string@+ getCurrentPath() const", asMETHOD(ScriptFileSystem, GetCurrentPath), asCALL_THISCALL); assert( r >= 0 );
	r = ASEngine->RegisterObjectMethod("filesystem", "array<string@> @getDirs() const", asMETHOD(ScriptFileSystem, GetDirs), asCALL_THISCALL); assert( r >= 0 );
	r = ASEngine->RegisterObjectMethod("filesystem", "array<string@> @getFiles() const", asMETHOD(ScriptFileSystem, GetFiles), asCALL_THISCALL); assert( r >= 0 );
	r = ASEngine->RegisterObjectMethod("filesystem", "bool isDir(const string &in) const", asMETHOD(ScriptFileSystem, IsDir), asCALL_THISCALL); assert( r >= 0 );
	r = ASEngine->RegisterObjectMethod("filesystem", "bool isLink(const string &in) const", asMETHOD(ScriptFileSystem, IsLink), asCALL_THISCALL); assert(r >= 0);
	r = ASEngine->RegisterObjectMethod("filesystem", "int64 getSize(const string &in) const", asMETHOD(ScriptFileSystem, GetSize), asCALL_THISCALL); assert(r >= 0);
	r = ASEngine->RegisterObjectMethod("filesystem", "int makeDir(const string &in)", asMETHOD(ScriptFileSystem, MakeDir), asCALL_THISCALL); assert(r >= 0);
	r = ASEngine->RegisterObjectMethod("filesystem", "int removeDir(const string &in)", asMETHOD(ScriptFileSystem, RemoveDir), asCALL_THISCALL); assert(r >= 0);
	r = ASEngine->RegisterObjectMethod("filesystem", "int deleteFile(const string &in)", asMETHOD(ScriptFileSystem, FileDelete), asCALL_THISCALL); assert(r >= 0);
	r = ASEngine->RegisterObjectMethod("filesystem", "int copyFile(const string &in, const string &in)", asMETHOD(ScriptFileSystem, FileCopy), asCALL_THISCALL); assert(r >= 0);
	r = ASEngine->RegisterObjectMethod("filesystem", "int move(const string &in, const string &in)", asMETHOD(ScriptFileSystem, Move), asCALL_THISCALL); assert(r >= 0);
}

void RegisterScriptFileSystem()
{
	RegisterScriptFileSystem_Native();
}

ScriptFileSystem::ScriptFileSystem()
{
	refCount = 1;

	// Gets the application's current working directory as the starting point
	// TODO: Replace backslash with slash to keep a unified naming convention
	char buffer[1000];
#if defined(_WIN32)
	currentPath = _getcwd(buffer, 1000);
#else
	currentPath = getcwd(buffer, 1000);
#endif
}

ScriptFileSystem::~ScriptFileSystem()
{
}

void ScriptFileSystem::AddRef() const
{
	refCount++;
}

void ScriptFileSystem::Release() const
{
	if( --refCount == 0 )
		delete this;
}

CScriptArray *ScriptFileSystem::GetFiles() const
{
	CScriptArray *array = &CScriptArray::Create("string");

#if defined(_WIN32)
	// Windows uses UTF16 so it is necessary to convert the string
	wchar_t bufUTF16[10000];
	string searchPattern = currentPath + "/*";
	MultiByteToWideChar(CP_UTF8, 0, searchPattern.c_str(), -1, bufUTF16, 10000);

	WIN32_FIND_DATAW ffd;
	HANDLE hFind = FindFirstFileW(bufUTF16, &ffd);
	if( INVALID_HANDLE_VALUE == hFind ) 
		return array;
	
	do
	{
		// Skip directories
		if( (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
			continue;

		// Convert the file name back to UTF8
		char bufUTF8[10000];
		WideCharToMultiByte(CP_UTF8, 0, ffd.cFileName, -1, bufUTF8, 10000, 0, 0);
		
		// Add the file to the array
		array->InsertLast( &ScriptString::Create( bufUTF8 ) );
	}
	while( FindNextFileW(hFind, &ffd) != 0 );

	FindClose(hFind);
#else
	dirent *ent = 0;
	DIR *dir = opendir(currentPath.c_str());
	while( (ent = readdir(dir)) != NULL ) 
	{
		const string filename = ent->d_name;

		// Skip . and ..
		if( filename[0] == '.' )
			continue;

		// Skip sub directories
		const string fullname = currentPath + "/" + filename;
		struct stat st;
		if( stat(fullname.c_str(), &st) == -1 )
			continue;
		if( (st.st_mode & S_IFDIR) != 0 )
			continue;

		// Add the file to the array
		array->InsertLast( &ScriptString::Create( filename ) );
	}
	closedir(dir);
#endif

	return array;
}

CScriptArray *ScriptFileSystem::GetDirs() const
{
	CScriptArray *array = &CScriptArray::Create("string");

#if defined(_WIN32)
	// Windows uses UTF16 so it is necessary to convert the string
	wchar_t bufUTF16[10000];
	string searchPattern = currentPath + "/*";
	MultiByteToWideChar(CP_UTF8, 0, searchPattern.c_str(), -1, bufUTF16, 10000);
	
	WIN32_FIND_DATAW ffd;
	HANDLE hFind = FindFirstFileW(bufUTF16, &ffd);
	if( INVALID_HANDLE_VALUE == hFind ) 
		return array;
	
	do
	{
		// Skip files
		if( !(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
			continue;

		// Convert the file name back to UTF8
		char bufUTF8[10000];
		WideCharToMultiByte(CP_UTF8, 0, ffd.cFileName, -1, bufUTF8, 10000, 0, 0);

		if( strcmp(bufUTF8, ".") == 0 || strcmp(bufUTF8, "..") == 0 )
			continue;
		
		// Add the dir to the array
		array->InsertLast( &ScriptString::Create( bufUTF8 ) );
	}
	while( FindNextFileW(hFind, &ffd) != 0 );

	FindClose(hFind);
#else
	dirent *ent = 0;
	DIR *dir = opendir(currentPath.c_str());
	while( (ent = readdir(dir)) != NULL ) 
	{
		const string filename = ent->d_name;

		// Skip . and ..
		if( filename[0] == '.' )
			continue;

		// Skip files
		const string fullname = currentPath + "/" + filename;
		struct stat st;
		if( stat(fullname.c_str(), &st) == -1 )
			continue;
		if( (st.st_mode & S_IFDIR) == 0 )
			continue;

		// Add the dir to the array
		array->InsertLast( &ScriptString::Create( filename ) );
	}
	closedir(dir);
#endif

	return array;
}

// Doesn't change anything if the new path is not valid
bool ScriptFileSystem::ChangeCurrentPath(const ScriptString &path)
{
	string newPath;
	if( path.c_std_str().find(":") != string::npos || path.c_std_str().find("/") == 0 || path.c_std_str().find("\\") == 0 )
		newPath = path.c_std_str();
	else
		newPath = currentPath + "/" + path.c_std_str();

	// TODO: Resolve internal /./ and /../
	// TODO: Replace backslash with slash to keep a unified naming convention

	// Remove trailing slashes from the path
	while(newPath.length() && (newPath[newPath.length()-1] == '/' || newPath[newPath.length()-1] == '\\') )
		newPath.resize(newPath.length()-1);
	ScriptString& str = ScriptString::Create( newPath.c_str() );
	if (!IsDir(str))
	{
		str.Release();
		return false;
	}
	currentPath = newPath;
	str.Release();
	return true;
}

bool ScriptFileSystem::IsDir(const ScriptString &path) const
{
	string search;
	if( path.c_std_str().find(":") != string::npos || path.c_std_str().find("/") == 0 || path.c_std_str().find("\\") == 0 )
		search = path.c_std_str();
	else
		search = currentPath + "/" + path.c_std_str();

#if defined(_WIN32)
	// Windows uses UTF16 so it is necessary to convert the string
	wchar_t bufUTF16[10000];
	MultiByteToWideChar(CP_UTF8, 0, search.c_str(), -1, bufUTF16, 10000);

	// Check if the path exists and is a directory
	DWORD attrib = GetFileAttributesW(bufUTF16);
	if( attrib == INVALID_FILE_ATTRIBUTES ||
		!(attrib & FILE_ATTRIBUTE_DIRECTORY) )
		return false;
#else
	// Check if the path exists and is a directory
	struct stat st;
	if( stat(search.c_str(), &st) == -1 )
		return false;
	if( (st.st_mode & S_IFDIR) == 0 )
		return false;
#endif

	return true;
}

bool ScriptFileSystem::IsLink(const ScriptString &path) const
{
	string search;
	if (path.c_std_str().find(":") != string::npos || path.c_std_str().find("/") == 0 || path.c_std_str().find("\\") == 0)
		search = path.c_std_str();
	else
		search = currentPath + "/" + path.c_std_str();

#if defined(_WIN32)
	// Windows uses UTF16 so it is necessary to convert the string
	wchar_t bufUTF16[10000];
	MultiByteToWideChar(CP_UTF8, 0, search.c_str(), -1, bufUTF16, 10000);

	// Check if the path exists and is a link
	DWORD attrib = GetFileAttributesW(bufUTF16);
	if (attrib == INVALID_FILE_ATTRIBUTES ||
		!(attrib & FILE_ATTRIBUTE_REPARSE_POINT))
		return false;
#else
	// Check if the path exists and is a link
	struct stat st;
	if (stat(search.c_str(), &st) == -1)
		return false;
	if ((st.st_mode & S_IFLNK) == 0)
		return false;
#endif

	return true;
}

asINT64 ScriptFileSystem::GetSize(const ScriptString &path) const
{
	string search;
	if (path.c_std_str().find(":") != string::npos || path.c_std_str().find("/") == 0 || path.c_std_str().find("\\") == 0)
		search = path.c_std_str();
	else
		search = currentPath + "/" + path.c_std_str();

#if defined(_WIN32)
	// Windows uses UTF16 so it is necessary to convert the string
	wchar_t bufUTF16[10000];
	MultiByteToWideChar(CP_UTF8, 0, search.c_str(), -1, bufUTF16, 10000);

	// Get the size of the file
	LARGE_INTEGER largeInt;
	HANDLE file = CreateFileW(bufUTF16, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	BOOL success = GetFileSizeEx(file, &largeInt);
	CloseHandle(file);
	if( !success )
		return -1;
	return asINT64(largeInt.QuadPart);
#else
	// Get the size of the file
	struct stat st;
	if (stat(search.c_str(), &st) == -1)
		return -1;
	return asINT64(st.st_size);
#endif
}

// TODO: Should be able to return different codes for
//       - directory exists
//       - path not found
//       - access denied
// TODO: Should be able to define the permissions for the directory
int ScriptFileSystem::MakeDir(const ScriptString &path)
{
	string search;
	if (path.c_std_str().find(":") != string::npos || path.c_std_str().find("/") == 0 || path.c_std_str().find("\\") == 0)
		search = path.c_std_str();
	else
		search = currentPath + "/" + path.c_std_str();

#if defined(_WIN32)
	// Windows uses UTF16 so it is necessary to convert the string
	wchar_t bufUTF16[10000];
	MultiByteToWideChar(CP_UTF8, 0, search.c_str(), -1, bufUTF16, 10000);

	// Create the directory
	BOOL success = CreateDirectoryW(bufUTF16, 0);
	return success ? 0 : -1;
#else
	// Create the directory
	int failure = mkdir(search.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	return !failure ? 0 : -1;
#endif
}

// TODO: Should be able to return different codes for 
//       - directory doesn't exist
//       - directory is not empty
//       - access denied
// TODO: Should have an option to remove the directory and all content recursively
int ScriptFileSystem::RemoveDir(const ScriptString &path)
{
	string search;
	if (path.c_std_str().find(":") != string::npos || path.c_std_str().find("/") == 0 || path.c_std_str().find("\\") == 0)
		search = path.c_std_str();
	else
		search = currentPath + "/" + path.c_std_str();

#if defined(_WIN32)
	// Windows uses UTF16 so it is necessary to convert the string
	wchar_t bufUTF16[10000];
	MultiByteToWideChar(CP_UTF8, 0, search.c_str(), -1, bufUTF16, 10000);

	// Remove the directory
	BOOL success = RemoveDirectoryW(bufUTF16);
	return success ? 0 : -1;
#else
	// Remove the directory
	int failure = rmdir(search.c_str());
	return !failure ? 0 : -1;
#endif
}

int ScriptFileSystem::FileDelete(const ScriptString &path)
{
	string search;
	if (path.c_std_str().find(":") != string::npos || path.c_std_str().find("/") == 0 || path.c_std_str().find("\\") == 0)
		search = path.c_std_str();
	else
		search = currentPath + "/" + path.c_std_str();

#if defined(_WIN32)
	// Windows uses UTF16 so it is necessary to convert the string
	wchar_t bufUTF16[10000];
	MultiByteToWideChar(CP_UTF8, 0, search.c_str(), -1, bufUTF16, 10000);

	// Remove the file
	BOOL success = DeleteFileW(bufUTF16);
	return success ? 0 : -1;
#else
	// Remove the file
	int failure = unlink(search.c_str());
	return !failure ? 0 : -1;
#endif
}

int ScriptFileSystem::FileCopy(const ScriptString &source, const ScriptString &target)
{
	string search1;
	if (source.c_std_str().find(":") != string::npos || source.c_std_str().find("/") == 0 || source.c_std_str().find("\\") == 0)
		search1 = source.c_std_str();
	else
		search1 = currentPath + "/" + source.c_std_str();

	string search2;
	if (target.c_std_str().find(":") != string::npos || target.c_std_str().find("/") == 0 || target.c_std_str().find("\\") == 0)
		search2 = target.c_std_str();
	else
		search2 = currentPath + "/" + target.c_std_str();

#if defined(_WIN32)
	// Windows uses UTF16 so it is necessary to convert the string
	wchar_t bufUTF16_1[10000];
	MultiByteToWideChar(CP_UTF8, 0, search1.c_str(), -1, bufUTF16_1, 10000);

	wchar_t bufUTF16_2[10000];
	MultiByteToWideChar(CP_UTF8, 0, search2.c_str(), -1, bufUTF16_2, 10000);

	// Copy the file
	BOOL success = CopyFileW(bufUTF16_1, bufUTF16_2, TRUE);
	return success ? 0 : -1;
#else
	// Copy the file manually as there is no posix function for this
	bool failure = false;
	FILE *src = 0, *tgt = 0;
	src = fopen(search1.c_str(), "r");
	if (src == 0) failure = true;
	if( !failure ) tgt - fopen(search2.c_str(), "w");
	if (tgt == 0) failure = true;
	char buf[1024];
	size_t n;
	while (!failure && (n = fread(buf, sizeof(char), sizeof(buf), src)) > 0)
	{
		if (fwrite(buf, sizeof(char), n, tgt) != n)
			failure = true;
	}
	if (src) fclose(src);
	if (tgt) fclose(tgt);
	return !failure ? 0 : -1;
#endif
}

int ScriptFileSystem::Move(const ScriptString &source, const ScriptString &target)
{
	string search1;
	if (source.c_std_str().find(":") != string::npos || source.c_std_str().find("/") == 0 || source.c_std_str().find("\\") == 0)
		search1 = source.c_std_str();
	else
		search1 = currentPath + "/" + source.c_std_str();

	string search2;
	if (target.c_std_str().find(":") != string::npos || target.c_std_str().find("/") == 0 || target.c_std_str().find("\\") == 0)
		search2 = target.c_std_str();
	else
		search2 = currentPath + "/" + target.c_std_str();

#if defined(_WIN32)
	// Windows uses UTF16 so it is necessary to convert the string
	wchar_t bufUTF16_1[10000];
	MultiByteToWideChar(CP_UTF8, 0, search1.c_str(), -1, bufUTF16_1, 10000);

	wchar_t bufUTF16_2[10000];
	MultiByteToWideChar(CP_UTF8, 0, search2.c_str(), -1, bufUTF16_2, 10000);

	// Move the file or directory
	BOOL success = MoveFileW(bufUTF16_1, bufUTF16_2);
	return success ? 0 : -1;
#else
	// Move the file or directory
	int failure = rename(search1.c_str(), search2.c_str());
	return !failure ? 0 : -1;
#endif
}

ScriptString* ScriptFileSystem::GetCurrentPath() const
{
	return &ScriptString::Create( currentPath.c_str() );
}


END_AS_NAMESPACE


#ifdef __MAPPER
#define __SERVER_PATH(s)	".\\..\\..\\Server\\"#s
#define __SERVER_P		    ".\\..\\..\\Server\\"
#endif

#ifdef __SERVER
#define __SERVER_PATH(s)	".\\"#s
#define __SERVER_P		    ".\\"
#endif

#include <fstream>
#include <iostream>
#include <sstream>  
#include <algorithm>


#include "AngelScript/scripthandle/scripthandle.cpp"
#include "AngelScript/scriptbuilder/scriptbuilder.cpp"

#define AngelScriptAPI_Check( reg )    if( reg < 0 ) \
        Log( "Error registration <%d>.\n", __LINE__ )

enum TypeFile;
enum ReasonRunPreproccessor;
class ScriptFileMk2;
class PreprocessorModule;
ScriptFileMk2* CreateScriptFile( string name, TypeFile type );
bool RunPreproccess( string& code, ScriptFileMk2* script, int reason );

vector<ScriptFileMk2*> LibraryScript;
vector<PreprocessorModule*> LibraryPreproccess;

#define COUNT_TYPE_FILE ( 4 )
#define BUFFER_MAX_SIZE ( 256 )

ifstream* ReadIfStream( string path )
{
	string override_path = __SERVER_PATH( Override\\ ) + path;
	path = __SERVER_P + path;
	ifstream* result = new ifstream( override_path.c_str() );
	if(!result->is_open())
	{
		delete result;
		result = new ifstream( path.c_str());
	}
	if(!result->is_open() )
		Log( "Error open file <%s> <%s>\n", override_path.c_str(), path.c_str() );
	return result;
}

enum TypeFile
{
	TFNone,
	TFContent,
	TFHeader,
	TFScript,
	TFCount = COUNT_TYPE_FILE
};

enum ReasonRunPreproccessor
{
	RRPLoad,
	RRPEnd
};

struct _TypeFileData
{
public:
	TypeFile type;
	const char* ext;
	const char* define_prefix;
	const char* path;

	class proccess
	{
	public:
		virtual void operator()(ofstream& writestream, ScriptFileMk2* script) = 0;
	};
	proccess* pre_proccess;
	proccess* post_proccess;
};

class script_preproccess : _TypeFileData::proccess
{
public:
	script_preproccess(){}
	void operator()(ofstream& writestream, ScriptFileMk2* script)
	{

	}
};

class script_postproccess : _TypeFileData::proccess
{
public:
	script_postproccess() {}
	void operator()(ofstream& writestream, ScriptFileMk2* script)
	{

	}
};

class header_preproccess : _TypeFileData::proccess
{
public:
	header_preproccess() {}
	void operator()(ofstream& writestream, ScriptFileMk2* script)
	{

	}
};

class header_postproccess : _TypeFileData::proccess
{
public:
	header_postproccess() {}
	void operator()(ofstream& writestream, ScriptFileMk2* script)
	{

	}
};

_TypeFileData TypeFileData[COUNT_TYPE_FILE] = 
{ 
	{ TFNone, "", "", "", (_TypeFileData::proccess*)&script_postproccess(), (_TypeFileData::proccess*)&script_preproccess() },
	{ TFContent, ".content", "__CONTENT_", __SERVER_PATH(scripts\\Mk2\\*.content), (_TypeFileData::proccess*)&script_postproccess(), (_TypeFileData::proccess*)&script_preproccess() },
	{ TFHeader, ".fosh", "__HEADER_", __SERVER_PATH(scripts\\Mk2\\*.fosh), (_TypeFileData::proccess*)&header_postproccess(), (_TypeFileData::proccess*)&header_postproccess() },
	{ TFScript, ".fos", "__MODULE_", __SERVER_PATH(scripts\\Mk2\\*.fos), (_TypeFileData::proccess*)&script_postproccess(), (_TypeFileData::proccess*)&script_preproccess() }
};

enum OwnerType
{
	OTServer,
	OTClient,
	OTMapper,
	OTCommon,
};

class _Owner
{
public:
	union
	{
		struct
		{
			bool Server : 1;
			bool Client : 1;
			bool Mapper : 1;
		};
		uint8 flags;
	};

	_Owner* operator=(const OwnerType& right)
	{
		Drop();

		switch (right)
		{
		case OTServer: this->Server = true; break;
		case OTClient: this->Client = true; break;
		case OTMapper: this->Mapper = true; break;
		case OTCommon: this->SetCommon(); break;
		default:return this;
		}
		return this;
	}

	inline bool IsCommon() const { return Server && Client && Mapper; }
	inline void SetCommon() { Server = Client = Mapper = true; }
	inline void Drop() { flags = 0; }
};

bool operator==(const _Owner& left, const OwnerType& right)
{
	switch (right)
	{
	case OTServer: return left.Server;
	case OTClient: return left.Client;
	case OTMapper: return left.Mapper;
	case OTCommon: return left.IsCommon();
	default:return false;
	}
}

bool operator!=(const _Owner& left, const OwnerType& right)
{
	return !(left == right);
}

bool operator==(const _Owner& left, const _Owner& right)
{
	if (left.Server) return left.Server == right.Server;
	if (left.Client) return left.Client == right.Client;
	if (left.Mapper) return left.Mapper == right.Mapper;
	return false;
}

bool operator!=(const _Owner& left, const _Owner& right)
{
	return !(left == right);
}

class ScriptFileMk2
{
public:

	string Name;
	string Code;
	_Owner Owner;

	int Sort;
	bool IsDebbug;
	TypeFile Type;
	
	int script_GetType();
	int script_GetSort();
	bool script_GetIsDebbug();
	ScriptString* script_GetName();
};

class PreprocessorModule
{
public:
	vector<uint> PreproccessFunctionIds;
	uint ExitFunctionId;
	uint EntryFunctionId;
	
	bool RunPreproccess( ScriptString& code, ScriptFileMk2* script, int reason );
};

ScriptFileMk2* CreateScriptFile( string name, TypeFile type )
{
	for( uint i = 0, size = LibraryScript.size(); i < size; ++i )
	{
		if( LibraryScript[i]->Name == name && LibraryScript[i]->Type == type )
			return LibraryScript[i];
	}
	
	ScriptFileMk2* newscript = new ScriptFileMk2();
	newscript->Name = name;
	newscript->Type = type;
	
	return newscript;
}

void WriteScriptFile( string name, TypeFile type, int sort, bool isDebbug, string code, _Owner owner)
{
	ScriptFileMk2* scriptFile = CreateScriptFile( name, type );
	
	scriptFile->Sort = sort;
	scriptFile->IsDebbug = isDebbug;
	scriptFile->Owner = owner;

	if( RunPreproccess( code, scriptFile, RRPLoad ) )
	{
		scriptFile->Code = code;
		LibraryScript.push_back( scriptFile );
	}
}

ScriptFileMk2* script_GetScriptFile( ScriptString* name, TypeFile type )
{
	if( !name )
		return NULL;

	for (uint i = 0, size = LibraryScript.size(); i < size; ++i)
	{
		if (LibraryScript[i]->Name == name->c_str() && LibraryScript[i]->Type == type)
			return LibraryScript[i];
	}
	return NULL;
}

bool SortScriptFileMk2(ScriptFileMk2* i,ScriptFileMk2* j){ return ( i->Sort < j->Sort ); }

class Collector
{
public:
	Collector(){}

	void LibraryBuild(vector<ScriptFileMk2*>& library);
	void LibraryBuildTypes(vector<ScriptFileMk2*>& library, TypeFile type);
	void LibraryBuildList(vector<ScriptFileMk2*>& library, const OwnerType& owner );
	void LibraryBuildListType(vector<ScriptFileMk2*>& library, const OwnerType& owner, TypeFile type);

	inline void ExitPreproccess();
	void LoadPreproccessModule();
	inline void ParsePreproccessModule();
	void ProccesHashFiles();
	inline void ParseHashFiles();
	inline void ParseDLG();
	void ParseGameVar();
	void ParseContent();
	void ParseScripts( const _TypeFileData& data );
	void Run(const char* write_file);

	inline void FindClose()
	{
		::FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
	}
	
private:
	ofstream		write;
	char			buff[BUFFER_MAX_SIZE];
	WIN32_FIND_DATA ffd;
	HANDLE          hFind;
};

void Collector::LibraryBuildTypes(vector<ScriptFileMk2*>& library, TypeFile type)
{
	for (uint i = 0, size = library.size(); i < size; ++i)
	{
		ScriptFileMk2* script = library[i];
		if (script->Type != type)
			continue;
		string& code = script->Code;
		if (RunPreproccess(code, script, RRPEnd))
		{
			write << "#ifdef " << TypeFileData[script->Type].define_prefix << script->Name.c_str() << "__\n";

			write << "#define MODULE_NAME \"" << script->Name << "\"\n";
			write << "#define ThisModule " << script->Name << "\n";
			write << "#define Log #(s) (::ClearLog( MODULE_NAME + \": \" + s))\n";
			if (script->IsDebbug)
				write << "#define DL #(s) (::ClearLog( MODULE_NAME  + \": Debbug: \" + s))\n";
			else
				write << "#define DL #(s)\n";
			if (script->Type == TFScript)
				write << "namespace " << script->Name.c_str() << "\n{\n";
			write << code.c_str() << "\n";
			if (script->Type == TFScript)
				write << "}\n";
			write << "#endif\n";
		}
	}
}

void Collector::LibraryBuildList(vector<ScriptFileMk2*>& library, const OwnerType& owner)
{
	switch (owner)
	{
	case OTMapper: write << "#ifdef __MAPPER\n"; break;
	case OTServer: write << "#ifdef __SERVER\n"; break;
	case OTClient: write << "#ifdef __CLIENT\n"; break;
	case OTCommon:
	default: break;
	}

	LibraryBuildListType(library, owner, TFHeader);
	LibraryBuildListType(library, owner, TFScript);

	if (owner!=OTCommon) write << "#endif\n";
}


void Collector::LibraryBuildListType(vector<ScriptFileMk2*>& library, const OwnerType& owner, TypeFile type)
{
	for (uint i = 0, size = library.size(); i < size; ++i)
	{
		ScriptFileMk2* script = library[i];
		if (script->Owner != owner)
			continue;
		if (script->Type != type)
			continue;
		write << "#define " << TypeFileData[script->Type].define_prefix << script->Name.c_str() << "__    //" << script->Sort << "\n";
	}
}

void Collector::LibraryBuild( vector<ScriptFileMk2*>& library )
{	
	if( !write.is_open() )
		return;
	
	sort(library.begin(), library.end(), SortScriptFileMk2);
	LibraryBuildList(library, OTServer);
	LibraryBuildList(library, OTClient);
	LibraryBuildList(library, OTMapper);
	LibraryBuildTypes(library, TFHeader);
	LibraryBuildTypes(library, TFScript);
	write << "Mk2::BuilderCall@ BuildCall = @Mk2::BuilderCall();\n";
}

bool PreprocessorModule::RunPreproccess( ScriptString& code, ScriptFileMk2* script, int reason )
{
	for( uint i = 0, size = PreproccessFunctionIds.size(); i < size; ++i )
		if( FOnline->ScriptPrepare( PreproccessFunctionIds[i] ) )
		{
			FOnline->ScriptSetArgAddress( &code );
			FOnline->ScriptSetArgAddress( script );
			FOnline->ScriptSetArgInt( reason );
			if( !FOnline->ScriptRunPrepared() )
				Log( "Error run preproccess\n" );
			else if( !FOnline->ScriptGetReturnedBool() )
				return false;
		}
	return true;
}

inline bool RunPreproccess( string& code, ScriptFileMk2* script, int reason )
{
	ScriptString& script_code = ScriptString::Create( code.c_str() );
	bool result = true;
	
	for( uint i = 0, size = LibraryPreproccess.size(); i < size; ++i )
		if( !LibraryPreproccess[i]->RunPreproccess( script_code, script, reason ) )
		{
			result = false;
			break;
		}
	
	code = script_code.c_str();
	script_code.Release();
	return result;
}

inline void Collector::ExitPreproccess( )
{	
	for( uint i = 0, size = LibraryPreproccess.size(); i < size; ++i )
	{
		if( LibraryPreproccess[i]->ExitFunctionId && FOnline->ScriptPrepare( LibraryPreproccess[i]->ExitFunctionId ) )
		{
			if( !FOnline->ScriptRunPrepared() )
				Log( "Error run exit preproccess\n" );
		}
		LibraryPreproccess[i]->PreproccessFunctionIds.clear();
	}
	
	LibraryPreproccess.clear();
}

void Collector::LoadPreproccessModule()
{
	if (ASEngine->GetModule(ffd.cFileName))
		ASEngine->DiscardModule(ffd.cFileName);

	CScriptBuilder builder;

	char path[256];
	path[CharEndJoin(__SERVER_PATH(scripts\\), ffd.cFileName, path)] = '\0';

	AngelScriptAPI_Check(builder.StartNewModule(ASEngine, ffd.cFileName));
	AngelScriptAPI_Check(builder.AddSectionFromFile(path));
	AngelScriptAPI_Check(builder.BuildModule());
	asIScriptModule* module = builder.GetModule();

	if (module)
	{
		PreprocessorModule* preproccess = new PreprocessorModule;

		for (uint iFunc = 0, iEnd = module->GetFunctionCount(); iFunc < iEnd; iFunc++)
		{
			asIScriptFunction* func = module->GetFunctionByIndex(iFunc);
			if (func)
			{
				uint position = 0;
				if (CharFindPosition(func->GetDeclaration(false, false), "bool preproccess_", position))
				{
					if (func->GetParamCount() == 3)
					{
						ostringstream out;
						out << "bool " << func->GetName() << "( string&, Preprocessor::ScriptFile&, Preprocessor::ReasonRun )";
						uint funcId = FOnline->ScriptBind(ffd.cFileName, out.str().c_str(), false);
						if (funcId) preproccess->PreproccessFunctionIds.push_back(funcId);
					}
					continue;
				}

				position = 0;
				if (!strcmp("void entry()", func->GetDeclaration(false)))
				{
					preproccess->EntryFunctionId = FOnline->ScriptBind(ffd.cFileName, "void entry( )", false);
					if (preproccess->EntryFunctionId && FOnline->ScriptPrepare(preproccess->EntryFunctionId))
					{
						if (!FOnline->ScriptRunPrepared())
							Log("Error run entry preproccess\n");
					}
					continue;
				}

				position = 0;
				if (!strcmp("void exit()", func->GetDeclaration(false)))
				{
					preproccess->ExitFunctionId = FOnline->ScriptBind(ffd.cFileName, "void exit( )", false);
					continue;
				}
			}
		}

		LibraryPreproccess.push_back(preproccess);
	}
	else Log("Error getmodule\n");
}

inline void Collector::ParsePreproccessModule()
{
	hFind = FindFirstFile(__SERVER_PATH(scripts\\*.preproccess), &ffd);
	if (INVALID_HANDLE_VALUE != hFind) do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			continue;

		LoadPreproccessModule();
	} while (FindNextFile(hFind, &ffd) != 0);
	FindClose();
}

void Collector::ProccesHashFiles()
{
	uint posExt = 0;
	if (CharFindPosition(ffd.cFileName, ".hash", posExt))
	{
		char path[256];
		path[CharEndJoin("scripts\\Mk2\\", ffd.cFileName, path)] = '\0';
		ifstream* read = ReadIfStream(path);
		char     name[256];
		name[posExt] = '\0';
		if (CharSubstring(ffd.cFileName, 0, posExt, name) && read->is_open())
		{
			ostringstream out;
			out << __SERVER_PATH(scripts\\hash\\) << name << ".fos";
			ofstream hash(out.str().c_str());
			if (hash.is_open())
			{

				while (read->getline( buff, BUFFER_MAX_SIZE))
				{
					hash << buff << "\n";
				}
				hash.close();
			}
			read->close();
			
			out.str("");
			out << "\\hash\\" << name;
			if (FOnline->ScriptLoadModule(out.str().c_str()))
			{
				uint funcId = FOnline->ScriptBind(out.str().c_str(), "bool Hash( string&, string&, int& )", false);
				if (funcId && FOnline->ScriptPrepare(funcId))
				{
					ScriptString& scriptName = ScriptString::Create("");
					ScriptString& scriptCode = ScriptString::Create("");
					int sort = 0;
					FOnline->ScriptSetArgAddress(&scriptName);
					FOnline->ScriptSetArgAddress(&scriptCode);
					FOnline->ScriptSetArgAddress(&sort);
					if (!FOnline->ScriptRunPrepared())
						Log("Error run HashFunction <%s>\n", out.str().c_str());
					else if (FOnline->ScriptGetReturnedBool())
					{
						_Owner owner = { true, false, false };
						WriteScriptFile(scriptName.c_std_str(), TFScript, sort, false, scriptCode.c_str(), owner);
					}
					scriptName.Release();
					scriptCode.Release();
				}
				else
					Log("Error bind HashFunction <%s>\n", out.str().c_str());
			}
			else Log("Error %s\n", out.str().c_str());
		}
		if( read )
			delete read;
	}
}

inline void Collector::ParseHashFiles()
{
	hFind = FindFirstFile(__SERVER_PATH(scripts\\Mk2\\*.hash), &ffd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				continue;

			ProccesHashFiles();
		} while (FindNextFile(hFind, &ffd) != 0);
	}
	FindClose();
}

inline void Collector::ParseDLG()
{
	hFind = FindFirstFile(__SERVER_PATH(text\\*), &ffd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && !CharIsWord(".", ffd.cFileName) && !CharIsWord("..", ffd.cFileName))
			{
				ostringstream out;
				out << "text\\" << ffd.cFileName << "\\FODLG.Mk2";
				ifstream* read = ReadIfStream(out.str().c_str());
				if (read->is_open())
				{
					out.str("");
					out << __SERVER_PATH(text\\) << ffd.cFileName << "\\FODLG.MSG";
					ofstream textFile(out.str().c_str());

					if (textFile.is_open())
					{
						while (read->getline( buff, BUFFER_MAX_SIZE))
							textFile << buff << "\n";
						textFile.close();
					}
					read->close();
				}
			}
		} while (FindNextFile(hFind, &ffd) != 0);
	}
	FindClose();
}

void Collector::ParseGameVar()
{
	class GameVar_stream
	{
	public:
		GameVar_stream( const char* _path )
		{
			stream.open(_path, ofstream::out | ofstream::trunc);
			if (stream.is_open())
				stream << "Begin,\n";
			path = _path;
		}

		~GameVar_stream()
		{
			if (stream.is_open())
			{
				stream << "End,\n";
				stream.close();
			}
		}

		void write_var( const char* name, const char* value )
		{
			stream << name << "=" << value << ",\n";
		}

		bool check()
		{
			if (stream.is_open())
				return true;
			Log("Parser error GameVar's <%s>.\n", path.c_str());
			return false;
		}

	private:
		string path;
		ofstream stream;
	};

	ifstream* read = ReadIfStream("scripts\\_vars.fos");
	if (read->is_open())
	{
		GameVar_stream	vars(__SERVER_PATH(scripts\\Mk2\\GameVar.content)), // Все переменные
						lvar(__SERVER_PATH(scripts\\Mk2\\LVAR.content)),	// Локальная
						uvar(__SERVER_PATH(scripts\\Mk2\\UVAR.content)),	// Уникальная
						gvar(__SERVER_PATH(scripts\\Mk2\\GVAR.content)),	// Глобальная
						llvar(__SERVER_PATH(scripts\\Mk2\\LLVAR.content)),	// Локальная локации
						livar(__SERVER_PATH(scripts\\Mk2\\LIVAR.content)),	// Локальная итема
						lmvar(__SERVER_PATH(scripts\\Mk2\\LMVAR.content));	// Локальная карты

		if (vars.check() && lvar.check() && uvar.check() && gvar.check() && llvar.check() && livar.check() && lmvar.check())
		{
			const char* chars = "\t\n =()";
			char word[256], word2[256];
			uint pos = 1, pos2 = 0;
			string name;
			while (read->getline( buff, BUFFER_MAX_SIZE))
			{
				if (buff[0] == '#')
				{
					pos = 1;
					pos2 = 0;
					if (CharNextWordEx(buff, pos, word, BUFFER_MAX_SIZE, chars) && CharIsWord("define", word) && CharNextWordEx(buff, pos, word, BUFFER_MAX_SIZE, chars))
					{
						CharFindPosition(word, "_", pos2);
						CharSubstring(word, pos2 + 1, CharLength(word), word2);
						name = word2;
						CharSubstring(word, 0, pos2, word2);

						if (CharNextWordEx(buff, pos, word, BUFFER_MAX_SIZE, chars))
						{
							vars.write_var(name.c_str(), word);
							if (CharIsWord("LVAR", word2)) lvar.write_var(name.c_str(), word);
							else if (CharIsWord("GVAR", word2)) gvar.write_var(name.c_str(), word);
							else if (CharIsWord("UVAR", word2)) uvar.write_var(name.c_str(), word);
							else if (CharIsWord("LLVAR", word2)) llvar.write_var(name.c_str(), word);
							else if (CharIsWord("LIVAR", word2)) livar.write_var(name.c_str(), word);
							else if (CharIsWord("LMVAR", word2)) lmvar.write_var(name.c_str(), word);
						}
					}
				}
			}
		}
		read->close();
	}
	if( read ) delete read;
}

void Collector::ParseContent()
{
	hFind = FindFirstFile(__SERVER_PATH(scripts\\Mk2\\*.content), &ffd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		write << "\nnamespace Content\n{\n";
		char     name[256], path[256];
		uint  posExt = 0;
		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				continue;

			char* name_ext = ffd.cFileName;
			posExt = 0;
			if (CharFindPosition(name_ext, ".content", posExt))
			{
				path[CharEndJoin("scripts\\Mk2\\", name_ext, path)] = '\0';
				ifstream* read = ReadIfStream( path );
				name[posExt] = '\0';
				if (CharSubstring(name_ext, 0, posExt, name))
				{
					if (read->is_open())
					{
						write << "\nenum " << name << "\n{\n";
						while (read->getline( buff, BUFFER_MAX_SIZE))
						{
							write << buff << "\n";
						}
						read->close();

						write << "\n}\n";
					}
					else Log("Error open content file <%s>\n", path);
				}
				if( read ) delete read;
			}
		} while (FindNextFile(hFind, &ffd) != 0);
		write << "}\n";
	}
	FindClose();
}

void Collector::ParseScripts(const _TypeFileData& data)
{
	hFind = FindFirstFile(data.path, &ffd);
	if (INVALID_HANDLE_VALUE != hFind)
	{
		char name[256], path[256];
		uint  posExt = 0, len = 0, endPos = 0;
		_Owner owner = { false, false, false };
		const uint ext_len = CharLength(data.ext);
		bool isDebbug = false;
		int sort = 0;
		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				continue;

			char* name_ext = ffd.cFileName;
			posExt = 0;
			len = CharLength(name_ext);
			if (len > ext_len && name_ext[len - ext_len] == '.' && CharFindPosition(name_ext, data.ext, posExt))
			{
				name[posExt] = '\0';
				if (CharSubstring(name_ext, 0, posExt, name))
				{
					path[CharEndJoin("scripts\\Mk2\\", name_ext, path)] = '\0';
					ifstream* read = ReadIfStream(path);
					if (read->is_open())
					{
						read->getline( buff, BUFFER_MAX_SIZE); //  определяем для чего предназначен скрипт ( клиент, маппер, сервер )
						posExt = 0;
						if (CharFindPosition(buff, "FOS", posExt))
						{
							posExt = 0;
							if (CharFindPosition(buff, "Common", posExt))
							{
								owner.SetCommon();
							}
							else
							{
								posExt = 0;
								owner.Client = CharFindPosition(buff, "Client", posExt);
								posExt = 0;
								owner.Server = CharFindPosition(buff, "Server", posExt);
								posExt = 0;
								owner.Mapper = CharFindPosition(buff, "Mapper", posExt);
							}

							if (owner.Client || owner.Server || owner.Mapper)
							{
								posExt = 0;
								isDebbug = CharFindPosition(buff, "Debbug", posExt);

								sort = 0;
								posExt = 0;
								if (CharFindPosition(buff, "Sort", posExt))
								{
									char memm[10];
									if (CharSubstring(buff, posExt + 4, CharLength(buff) - posExt + 4, memm) )
										sort = strtol(memm, NULL, 10);
								}

								ostringstream out;
								out << read->rdbuf();
								WriteScriptFile(name, data.type, sort, isDebbug, out.str(), owner);
							}
						}
						read->close();
					}
					if( read ) delete read;
				}
			}
		} while (FindNextFile(hFind, &ffd) != 0);
	}
	FindClose();
}

void Collector::Run( const char* write_file )
{
	write.open(write_file, ofstream::out | ofstream::trunc);
	if (write.is_open())
	{
		write << "#define __MK2_MODULE__";

		ParseHashFiles();
		ParsePreproccessModule();
		ParseDLG();
		ParseGameVar();
		ParseContent();

		write << "#ifdef __SERVER\n#define UnsafeFunc  #( name )  name( ::Critter& player, int param0, int param1, int param2, ::string@ param3, int[]@ param4 )\n#define CritterMutual Critter\n#define ItemMutual Item\n#endif\n";
		write << "#ifdef __CLIENT\n#define CritterMutual CritterCl\n#define ItemMutual ItemCl\n#endif\n";
		write << "#ifdef __MAPPER\n#define CritterMutual MapperObject\n#define ItemMutual MapperObject\n#endif\n";

		ParseScripts(TypeFileData[TFHeader]);
		ParseScripts(TypeFileData[TFScript]);

		LibraryBuild(LibraryScript);
		ExitPreproccess();
		write.close();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Собирает все модули из папки Mk2 в один скрипт Mk2, помещая все файлы *.fos в namespace с именем файла, а файлы *.fosh в начало файла, организовывая глобальный доступ к ним
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AutoScript()
{		
	RegisterScriptHandle( );
	ASEngine->SetEngineProperty( asEP_USE_CHARACTER_LITERALS, 1 );
	
	const char* defName = ASEngine->GetDefaultNamespace();
    ASEngine->SetDefaultNamespace( "Preprocessor" );
	
	ASEngine->RegisterEnum( "TypeFile" );
	ASEngine->RegisterEnumValue( "TypeFile", "TFNone", TFNone );
	ASEngine->RegisterEnumValue( "TypeFile", "TFHeader", TFHeader );
	ASEngine->RegisterEnumValue( "TypeFile", "TFScript", TFScript );
	ASEngine->RegisterEnumValue( "TypeFile", "TFContent", TFContent );
	
	ASEngine->RegisterEnum( "ReasonRun" );
	ASEngine->RegisterEnumValue( "ReasonRun", "RRPLoad", RRPLoad );
	ASEngine->RegisterEnumValue( "ReasonRun", "RRPEnd", RRPEnd );
	
	AngelScriptAPI_Check( ASEngine->RegisterObjectType( "ScriptFile", 0, asOBJ_REF | asOBJ_NOCOUNT ) );
	AngelScriptAPI_Check( ASEngine->RegisterGlobalFunction( "ScriptFile@ GetScriptFile( ::string@+ name, TypeFile type )", asFUNCTION( script_GetScriptFile ), asCALL_CDECL ) );
	AngelScriptAPI_Check( ASEngine->RegisterObjectMethod( "ScriptFile", "TypeFile get_Type()", asMETHOD( ScriptFileMk2, script_GetType ), asCALL_THISCALL ) );
	AngelScriptAPI_Check( ASEngine->RegisterObjectMethod( "ScriptFile", "int get_Sort()", asMETHOD( ScriptFileMk2, script_GetSort ), asCALL_THISCALL ) );
	AngelScriptAPI_Check( ASEngine->RegisterObjectMethod( "ScriptFile", "bool get_IsDebbug()", asMETHOD( ScriptFileMk2, script_GetIsDebbug ), asCALL_THISCALL ) );
	AngelScriptAPI_Check( ASEngine->RegisterObjectMethod( "ScriptFile", "::string@+ get_Name()", asMETHOD( ScriptFileMk2, script_GetName ), asCALL_THISCALL ) );
    ASEngine->SetDefaultNamespace( defName );
	
	Collector().Run(__SERVER_PATH(scripts\\Mk2.fos));
	for (uint i = 0, size = LibraryScript.size(); i < size; ++i)
	{
		delete LibraryScript[i];
		LibraryScript[i] = NULL;
	}
	LibraryScript.clear();
}

int ScriptFileMk2::script_GetType()
{
	return Type;
}

int ScriptFileMk2::script_GetSort()
{
	return Sort;
}

bool ScriptFileMk2::script_GetIsDebbug()
{
	return IsDebbug;
}

ScriptString* ScriptFileMk2::script_GetName()
{
	return &ScriptString::Create( Name.c_str() );
}

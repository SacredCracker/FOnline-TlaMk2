#ifndef __SCRIPT_ENUM_H
#define __SCRIPT_ENUM_H

#include "angelscript.h"
#include "scriptstring.h"
#include <string>

#define RegScriptEnum( reg )    if( reg < 0 ) \
	Log( "Ошибка регистрации класса Enum <%d>.\n", __LINE__ )

class ScriptEnum
{	
public:

	ScriptEnum( const string& nameSpace, const string& name, const string* moduleName );

	// Functions
	int GetValueById( uint id );
	int GetValueByName( ScriptString& );
	ScriptString* GetNameByValue( int value );
	
    void AddRef();
    void Release();
	
	ScriptString& GetName( )		{ return ScriptString::Create( Name ); 		}
	ScriptString& GetNameSpace( )	{ return ScriptString::Create( NameSpace ); }
	
	
	static ScriptEnum* Factory( ScriptString& nameSpace, ScriptString& name, ScriptString* moduleName );
	static void        Registration();
	
	// Vars
	int 				TypeId;
	uint 				ValueCount;
	uint 				Index;
	const char* 		Name;
	const char*			NameSpace;
	int					NoneIndex;
	asITypeInfo*		EnumInfo;
	
protected:
	asIScriptModule* 	Module;
    int      			RefCount;
	map <string,int> 	ValueNames;
	static asIScriptModule* GetModule( const char* moduleName );
};

#endif
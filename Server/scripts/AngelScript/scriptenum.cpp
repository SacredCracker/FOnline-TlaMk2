#ifndef __SCRIPT_ENUM
#define __SCRIPT_ENUM

#include "scriptenum.h"
#include "../fonline.h"

void ScriptEnum::AddRef()
{
    RefCount++;
}

void ScriptEnum::Release()
{
    if( --RefCount == 0 )
	{
		ValueNames.clear();
        delete this;
	}
}

ScriptEnum* ScriptEnum::Factory( ScriptString& nameSpace, ScriptString& nameEnum, ScriptString* moduleName )
{
	return new ScriptEnum( nameSpace.c_std_str(), nameEnum.c_std_str(), moduleName ? &moduleName->c_std_str() : NULL );
}

asIScriptModule* ScriptEnum::GetModule( const char* moduleName )
{
	if( moduleName )
		return ASEngine->GetModule( moduleName );
	else
	{
		asIScriptContext* context = ScriptGetActiveContext();
		if( context )
		{
			asIScriptFunction* ActiveFunc = context->GetFunction();
			if( ActiveFunc && ActiveFunc->GetModuleName() )
				return ASEngine->GetModule( ActiveFunc->GetModuleName() );
		}
	}
	return NULL;
}

ScriptEnum::ScriptEnum( const string& nameSpace, const string& name, const string* moduleName )
{
	RefCount = 1;
	NoneIndex = -1;
	Module = GetModule( moduleName ? moduleName->c_str( ) : NULL );
	if( Module )
	{
		Index = 0;
		for( uint indexEnd = Module->GetEnumCount(); Index < indexEnd; Index++ )
		{
			EnumInfo = Module->GetEnumByIndex( Index ); // , &TypeId, &NameSpace );
			TypeId = EnumInfo->GetTypeId();
			Name = EnumInfo->GetName();
			NameSpace = EnumInfo->GetNamespace();
			if( Name && NameSpace )
			{
				if( CharIsWord( nameSpace.c_str(), NameSpace ) && CharIsWord( name.c_str(), Name ) )
				{
					ValueCount = EnumInfo->GetEnumValueCount( );
					for( uint i = 0; i < ValueCount; i++ )
					{
						int value = 0;
						string nameValue = EnumInfo->GetEnumValueByIndex( i, &value );
						ValueNames[nameValue] = value;
						if( CharIsWord( nameValue.c_str(), "None" ) )
							NoneIndex = value;
					}
					return;
				}
				
				TypeId = -1;
				Name = NULL;
				NameSpace = NULL;
			}
		}
	}
}

int ScriptEnum::GetValueById( uint id )
{
	if( EnumInfo )
    {
		int out = 0;
		EnumInfo->GetEnumValueByIndex( id, &out );
		return out;
	}
	return NoneIndex;
}

ScriptString* ScriptEnum::GetNameByValue( int value )
{
	for( auto iter = ValueNames.begin(); iter != ValueNames.end(); ++iter )
		if( iter->second == value )
			return &ScriptString::Create( iter->first.c_str() );
	return &ScriptString::Create( "" );
}

int ScriptEnum::GetValueByName( ScriptString& valueName )
{
	if( Module )
    {
		auto iter = ValueNames.find( valueName.c_std_str() );
		if( iter != ValueNames.end() )
			return iter->second;
	}
	return NoneIndex;
}

void ScriptEnum::Registration()
{
	Log( "kdslk\n" );
	RegScriptEnum( ASEngine->RegisterObjectType( "Enum", sizeof( ScriptEnum ), asOBJ_REF ) );
    RegScriptEnum( ASEngine->RegisterObjectBehaviour( "Enum", asBEHAVE_FACTORY, "Enum@ f( ::string&, ::string&, ::string@ )", asFUNCTION( ScriptEnum::Factory ), asCALL_CDECL ) );
    RegScriptEnum( ASEngine->RegisterObjectBehaviour( "Enum", asBEHAVE_ADDREF, "void f()", asMETHOD( ScriptEnum, AddRef ), asCALL_THISCALL ) );
    RegScriptEnum( ASEngine->RegisterObjectBehaviour( "Enum", asBEHAVE_RELEASE, "void f()", asMETHOD( ScriptEnum, Release ), asCALL_THISCALL ) );

    RegScriptEnum( ASEngine->RegisterObjectMethod( "Enum", "int get_opIndex( uint )", asMETHOD( ScriptEnum, GetValueById ), asCALL_THISCALL ) );	
    RegScriptEnum( ASEngine->RegisterObjectMethod( "Enum", "int get_Value( ::string& )", asMETHOD( ScriptEnum, GetValueByName ), asCALL_THISCALL ) );	
    RegScriptEnum( ASEngine->RegisterObjectMethod( "Enum", "::string@ get_ValueName( int value )", asMETHOD( ScriptEnum, GetNameByValue ), asCALL_THISCALL ) );	
	
    RegScriptEnum( ASEngine->RegisterObjectMethod( "Enum", "::string& get_Name( )", asMETHOD( ScriptEnum, GetName ), asCALL_THISCALL ) );	
    RegScriptEnum( ASEngine->RegisterObjectMethod( "Enum", "::string& get_NameSpace( )", asMETHOD( ScriptEnum, GetNameSpace ), asCALL_THISCALL ) );	
	
	RegScriptEnum( ASEngine->RegisterObjectProperty( "Enum", "const uint Length", offsetof( ScriptEnum, ValueCount ) ) );	
	RegScriptEnum( ASEngine->RegisterObjectProperty( "Enum", "const int TypeId", offsetof( ScriptEnum, TypeId ) ) );
	RegScriptEnum( ASEngine->RegisterObjectProperty( "Enum", "const uint Index", offsetof( ScriptEnum, Index ) ) );
}
#endif
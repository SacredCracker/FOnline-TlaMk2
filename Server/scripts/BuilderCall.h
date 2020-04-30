#ifndef __BUILDER_CALL_H
#define __BUILDER_CALL_H

#define RegBuilderCall( reg )    if( reg < 0 ) \
        Log( "ќшибка регистрации класса BuilderCall <%d>.\n", __LINE__ )

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

struct Msg
{
	uint Number;
	string Text;
	
	void Write( ofstream& file );
	
	static bool Sort(Msg* i,Msg* j);	
};

struct MsgFile
{
	vector<Msg*> MsgList;
	string Name;
	
	void Add( ScriptString& line, uint number );
	void Write();
};
	
struct BuilderCall
{
    BuilderCall();
	
	static BuilderCall* Factory();
	static void Registration();
};

	
void DlgMsgAddText( uint number, ScriptString& text, ScriptString& lang );
void WriteDlgMsg( );
MsgFile* GetMsgFile( ScriptString& lang );
vector<MsgFile*> MsgFileList;

void DlgMsgAddText( uint number, ScriptString& text, ScriptString& lang )
{
	GetMsgFile( lang )->Add( text, number );
}

MsgFile* GetMsgFile( ScriptString& lang )
{
	for( uint i = 0, size = MsgFileList.size(); i < size; ++i )
		if( CharIsWord( lang.c_str(), MsgFileList[i]->Name.c_str() ) )
			return MsgFileList[i];
		
	MsgFile* file = new MsgFile;
	file->Name = lang.c_str();
	MsgFileList.push_back( file );
	return file;
}

void WriteDlgMsg( )
{
	for( uint i = 0, size = MsgFileList.size(); i < size; ++i )
		MsgFileList[i]->Write( );
	
	MsgFileList.clear();
}

void MsgFile::Add( ScriptString& line, uint number )
{
	Msg* msg = new Msg;
	msg->Text = line.c_str();
	msg->Number = number;
	MsgList.push_back( msg );
}

void MsgFile::Write()
{
	ostringstream out;
	out << ".\\text\\" << Name << "\\FODLG.MSG";
	ofstream file( out.str().c_str(), std::ios::app );
	if( file.is_open() )
	{
		sort(MsgList.begin(), MsgList.end(), Msg::Sort);
		for( uint i = 0, size = MsgList.size(); i < size; ++i )
			MsgList[i]->Write( file );
		MsgList.clear();
		file.close();
	}	
}

void Msg::Write( ofstream& file )
{
	file << "{" << Number << "}{}{" << Text.c_str() << "}\n";
}

bool Msg::Sort(Msg* i,Msg* j)
{
	return (i->Number < j->Number); 
}

void BuilderCall::Registration()
{
    const char* defName = ASEngine->GetDefaultNamespace();
    ASEngine->SetDefaultNamespace( "Mk2" );

    RegBuilderCall( ASEngine->RegisterObjectType( "BuilderCall", 0, asOBJ_REF | asOBJ_NOCOUNT ) );
    RegBuilderCall( ASEngine->RegisterObjectBehaviour( "BuilderCall", asBEHAVE_FACTORY, "BuilderCall@ f( )", asFUNCTION( BuilderCall::Factory ), asCALL_CDECL ) );
	
    ASEngine->SetDefaultNamespace( "BuilderCall" );
	
	RegBuilderCall( ASEngine->RegisterGlobalFunction( "void WriteDlgMsg( )", asFUNCTION( WriteDlgMsg ), asCALL_CDECL ) );	
	RegBuilderCall( ASEngine->RegisterGlobalFunction( "void DlgMsgAddText( uint number, ::string& text, ::string& lang )", asFUNCTION( DlgMsgAddText ), asCALL_CDECL ) );	
	
    ASEngine->SetDefaultNamespace( defName );
}

BuilderCall::BuilderCall()
{	
	asIScriptModule* mk2Module = ASEngine->GetModule( "Mk2" );
    if( mk2Module )
    {
		ostringstream out;
		asIScriptContext *ctx = ASEngine->CreateContext();
		
		for( uint index = 0, iEnd = mk2Module->GetEnumCount(); index < iEnd; index++ )
        {
			//const char *enumName = mk2Module->GetEnumByIndex( index, &enumTypeId, &nameSpace );
			asITypeInfo* enumInfo = mk2Module->GetEnumByIndex( index ); // , &TypeId, &NameSpace );
			if( enumInfo )
			{
				const char *enumName = enumInfo->GetName();
				int enumTypeId = enumInfo->GetTypeId();
				const char *nameSpace = enumInfo->GetNamespace();
				out.str("");
				out << "void " << enumName << "Init(string&inout, " << enumName << ")"; 
				
				for( uint iFunc = 0, funcEnd = mk2Module->GetFunctionCount(); iFunc < funcEnd; iFunc++ )
				{
					asIScriptFunction* func = mk2Module->GetFunctionByIndex( iFunc );
					if( func->GetParamCount() != 2 )
						continue;
					int typeId = 0;
					func->GetParam( 1, &typeId );
					if( func && CharIsWord( out.str().c_str(), func->GetDeclaration( false ) ) && typeId == enumTypeId )
					{
						for( int value = 0, valueCount = enumInfo->GetEnumValueCount(); value < valueCount; value++ )
						{
							if( ctx->Prepare(func) >= 0 ) // FOnline->ScriptPrepare( funcId ) )
							{    
								int outValue = -1;
								ScriptString& nameValue = ScriptString::Create( enumInfo->GetEnumValueByIndex( value, &outValue) );
								ctx->SetArgAddress( 0, &nameValue );
								ctx->SetArgDWord( 1, outValue );
								if( ctx->Execute() != asEXECUTION_FINISHED )
									Log( "Error run %s \n", func->GetDeclaration( true, true ) );
								nameValue.Release();
							}
							else
								Log( "Error run %s \n", func->GetDeclaration( true, true ) );
						}
					}
				}
			}
        }
		ctx->Release( );
	}
}

BuilderCall* BuilderCall::Factory()
{
    return new BuilderCall();
}
#endif


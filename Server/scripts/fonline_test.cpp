#include "fonline_tla.h"

// Extern data definition
_GlobalVars GlobalVars;

// класс счётчик ссылок
class RefC
{
private:
    int refC;
public:
    RefC() { refC = 1; }
    void AddRef() { refC++; }
    void Release()
    {
        if( !--refC )
            delete this;
    }
};

uint CountObjArrTest = 0;
class ObjArrTest: public RefC
{
public:
    uint Id;


    ObjArrTest() { CountObjArrTest++;
                   Id = CountObjArrTest;
                   Log( "Create ObjArrTest %u\n", CountObjArrTest ); }

    void LogId()
    {
        Log( "ObjArrTest::Id %u\n", Id );
    }
};

// Фабрика
ObjArrTest* ObjArrTestFactoryE()
{
    return new ObjArrTest();
}

// Entry point
FONLINE_DLL_ENTRY( isCompiler )
{
    /*ASEngine->RegisterObjectType("ObjArrTest",0,asOBJ_REF);

       ASEngine->RegisterObjectMethod("ObjArrTest"," void LogId()",asMETHOD(ObjArrTest, LogId),asCALL_THISCALL);
       ASEngine->RegisterObjectBehaviour("ObjArrTest",asBEHAVE_FACTORY,"ObjArrTest@ new_ObjArrTest()",asFUNCTION(ObjArrTestFactoryE),asCALL_CDECL);
       ASEngine->RegisterObjectBehaviour("ObjArrTest",asBEHAVE_ADDREF,"void AddRef()",asMETHOD(ObjArrTest,AddRef),asCALL_THISCALL);
       ASEngine->RegisterObjectBehaviour("ObjArrTest",asBEHAVE_RELEASE,"void Release()",asMETHOD(ObjArrTest,Release),asCALL_THISCALL);
     */
    if( isCompiler )
        return;

    // Test Memory Level 3 for loaded DLLs
    for( uint i = 0; i < 666; i++ )
        volatile char* leak = new char[ 2 ];
}

// Test function
EXPORT void TestFunc( ScriptString& str )
{
    Log( "TEST %s", str.c_str() );
}

EXPORT bool TestScriptCallNative( ScriptString& moduleName, ScriptString& funcDecl )
{
    uint bindId = FOnline->ScriptBind( moduleName.c_str(), funcDecl.c_str(), true );
    if( bindId && FOnline->ScriptPrepare( bindId ) )
    {
        FOnline->ScriptSetArgInt( 321 );
        FOnline->ScriptSetArgUInt64( 2222222 );
        FOnline->ScriptSetArgFloat( 1.55f );
        FOnline->ScriptSetArgObject( &funcDecl );
        if( FOnline->ScriptRunPrepared() )
        {
            Log( "TestScriptCallNative return %g.\n", FOnline->ScriptGetReturnedUInt64() );
            return true;
        }
    }
    return false;
}

EXPORT void StringExample()
{
    ScriptString& str = ScriptString::Create( "Test1" );
    Log( "StringExample 1: '%s' (len %u, ref count %d)\n", str.c_str(), str.length(), str.rcount() );
    str = "Hello World!";
    Log( "StringExample 2: '%s' (len %u, ref count %d)\n", str.c_str(), str.length(), str.rcount() );
    ScriptString& str2 = ScriptString::Create();
    ScriptString& str3 = ScriptString::Create();
    str2 = str3;
    str = "1234567890abcdefghijklmnopqrs....";
    Log( "StringExample 3: '%s' (len %u, ref count %d)\n", str.c_str(), str.length(), str.rcount() );
    str.Release();
    str2.Release();
    str3.Release();
}

EXPORT void TestNativeRunScriptGlobalFunction( ScriptString& str )
{
    Log( "BEgin\n" );
    asIScriptFunction* func = ASEngine->GetGlobalFunctionByIndex( 141 );
    int                bindId = func->GetId();
    if( bindId < 0 )
    {
        Log( "Error\n" );
        return;
    }

    if( bindId && FOnline->ScriptPrepare( bindId ) )
    {
        Log( "Ok\n" );
        FOnline->ScriptSetArgObject( &str );
        FOnline->ScriptRunPrepared();
    }
    else
        Log( "Error\n" );
    Log( "End\n" );
    // Index 141 ModuleName (null) FuncName void ::Log(string&inout)
}

EXPORT void TestClassAny( ScriptAny& any )
{
    ScriptString& str = ScriptString::Create( "Error\n" );
    int           typeId = ASEngine->GetTypeIdByDecl( "string" );
    any.Retrieve( &str, typeId );
    Log( str.c_str() );
}

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

EXPORT void ArrayExample()
{
    ScriptArray&  arr = ScriptArray::Create( "string" );
    ScriptString& first = ScriptString::Create( "first" );
    arr.InsertFirst( &first );
    first.Release();
    arr.InsertAt( 1, &ScriptString::Create( "mid" ) );    // Leak
    arr.InsertLast( &ScriptString::Create( "last" ) );    // Leak
    arr.InsertFirst( &ScriptString::Create( "first0" ) ); // Leak
    arr.RemoveAt( 0 );
    Log( "Array example:\n" );
    for( asUINT i = 0; i < arr.GetSize(); i++ )
    {
        ScriptString& str = *(ScriptString*) arr.At( i );
        Log( "%u) '%s'\n", i, str.c_str() );
    }
    arr.Release();
}

EXPORT void TestItemArray( ScriptArray& Items )
{
    for( uint i = 0, iEnd = Items.GetSize(); i < iEnd; i++ )
    {
        Log( "i=%u \n", i );
        Item& it = *( *(Item**) Items.At( i ) );
        if( it.GetId() )
            Log( "items[i].Id %u \n", it.Id );
        else
            Log( "Ошибка \n" );
    }
    //
    // Log("items[i].Id %u",((Item*)&Items.At( i )).Id);
}

EXPORT void TestUintArray( ScriptArray& u )
{
    for( uint i = 0, iEnd = u.GetSize(); i < iEnd; i++ )
    {
        Log( "u[%u].Id %u \n", i, *(asUINT*) u.At( i ) );
    }
}

/*
   [02:15:33] <@Atom> ScriptArray::At returns a pointer to the array's element at the given index
   [02:16:05] <@Atom> in case of item handle array, it's a pointer to the pointer to the item, not the pointer itself
   [02:16:52] <@Atom> it's so it can be bind as returning a reference in scripts, and in native you can do stuff like Item* it = ...; *(arr->At(15)) = (void*)it;
   [02:17:28] <@Atom> so cast the At return to Item** and then do stuff
   [02:17:48] <@Atom> *be bound
 */
EXPORT void TestObjArrTestNative( ScriptArray& u )
{
    for( uint i = 0, iEnd = u.GetSize(); i < iEnd; i++ )
    {
        // ObjArrTest* it = ...; *(arr->At(15)) = (void*)it;
        // ObjArrTest* it=(ObjArrTest*) u.At( i );
        // *(u->At(15)) = (void*)it;
        // Log("u[%u].Id %u \n",i,it.Id);
    }
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

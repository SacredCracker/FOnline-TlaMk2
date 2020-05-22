
// #define __ASEngineInfo

#pragma warning (push)
#pragma warning (disable : 4244)

void CallStackToLog();

#include <windows.h>
#include "fonline_tla.h"
#include "_itempid.fos"
#include "fonline_param.h"
#include "ve_char_api.h"
#include "as_engine_Info.cpp"
#include "BlockLines.h"
#include "md5.h"
#include <time.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "AngelScript/scriptenum.cpp"
#include "AngelScript/scriptfilesystem.cpp"
#include "BuilderCall.h"

#ifndef MAX
#define MAX( v1, v2 )    ( ( v1 ) > ( v2 ) ? ( v1 ) : ( v2 ) )
#endif

#ifndef asTYPEID_STRING
#define asTYPEID_STRING		( 67108876 )
#endif

#ifdef __CLIENT
#include <process.h>
#include "winsock.h"
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "wsock32.lib")
#endif

_GlobalVars GlobalVars;

asIScriptModule* GetModule( const char* moduleName );

#ifdef __SERVER

#include <excpt.h>
#include "_farm_defines.fos"

EXPORT bool         	RunFarmScriptBool						( ScriptString* module, ScriptString* func );
EXPORT uint         	BindFarmScript							( ScriptString* module, ScriptString* func );
EXPORT int          	MakeBackup								( ScriptString* parameters );

EXPORT bool 	__cdecl	check_look								( Map& map, Critter& cr, Critter& opponent );
EXPORT bool 	__cdecl	check_trap_look							( Map& map, Critter& cr, Item& trap );
EXPORT void         	Map_GetExitGlobalGrid					( Map& map, Critter& cr, uint16& x, uint16& y );
EXPORT void         	Map_GetExitGrid							( Map& map, Critter& cr, uint16& x, uint16& y, uint16& MapPid, uint& EntireId );
EXPORT uint  			GetFarmEntire							( Map& map, CScriptArray& outArr, uint pid, uint id );

EXPORT void 			Critter_SetScriptDescriptor				( Critter& cr, asIScriptObject* value );
EXPORT void  			Critter_GetGroupNative					( Critter& cr );
EXPORT void         	Critter_RefreshSpeed					( Critter& cr );
EXPORT uint				Critter_GetGlobalGroupCarId				( Critter& cr );
EXPORT uint  			Critter_GetGlobalGroupProcessLastTick	( Critter& cr );
EXPORT uint  			Critter_GetGlobalGroupTimeCanFollow		( Critter& cr );
EXPORT uint         	Critter_GetLanguage						( Critter& cr );
EXPORT uint 			Critter_GetViewMapId					( Critter& cr );
EXPORT uint 			Critter_GetViewMapParams				( Critter& cr, uint16& ViewMapHx, uint16& ViewMapHy, uint8& ViewMapDir, uint& ViewMapLocEnt, uint& ViewMapLocId );
EXPORT int 				Critter_AddScoreMK2						( Critter& cr, uint scoreIndex, int value );
EXPORT int  			getParamDialog_Intellect				( Critter& cr, Critter& slave, uint index );
EXPORT int  			getParamDialog_Reputation				( Critter& cr, Critter& slave, uint index );
EXPORT int 				getParam_CountMerc						( Critter& cr, uint );
EXPORT asIScriptObject* Critter_GetScriptDescriptor				( Critter& cr );

EXPORT uint 			SearchDeleteItem						( CScriptArray& inItems, CScriptArray& outItems, uint count );

EXPORT bool 			allowSlot_Hand1							( uint8, Item &, Critter &, Critter & toCr );

EXPORT int 				_CheckVisor								( uint parameter, Critter& fromCr, Critter& toCr );
EXPORT int 				_CheckAwareness							( uint parameter, Critter& fromCr, Critter& toCr );
EXPORT bool         	RunFarmScriptBoolById					( uint funcId );
EXPORT bool         	RunIsCreateFarmItem						( uint funcId, ScriptDictionary& farmIt, int typeCreated, uint idCreated, uint16 hexX, uint16 hexY );

EXPORT void 			init									( );
	   
	   uint 			GetDialogDemandFunctionId				( ScriptString& module, ScriptString& func, CScriptArray& args );
	   bool 			RunDialogDemandFunctionId				( Critter& cr, Critter* npc, uint funcId, CScriptArray& args );
	   uint 			RunDialogResultFunctionId				( Critter& cr, Critter* npc, uint funcId, CScriptArray& args, bool isRet );
	   uint 			GetDialogResultFunctionId				( ScriptString& module, ScriptString& func, CScriptArray& args, bool& isReturn );
	   uint 			GetDialogBranchFunctionId				( ScriptString& module, ScriptString& func, bool& isReturn );
	   uint 			RunDialogBranchFunctionId				( Critter& cr, Critter* npc, uint funcId, ScriptString* arg, bool isRet );
#endif

	   asIScriptObject* Item_GetScriptDescriptor				( Item& item );
	   void 			Item_SetScriptDescriptor				( Item& item, asIScriptObject* value );
	   ScriptString* 	Item_GetLexems							( Item& item );
	   ScriptString* 	Global_GetFunctionName					( asIScriptFunction* function );
	   ScriptString* 	Global_GetFunctionDeclaration			( asIScriptFunction* function, bool includeObjectName, bool includeNamespace );
#ifdef __CLIENT
EXPORT void 			ChangeClientParam						( CritterCl& cr, int param, int value );
EXPORT void 			critter_out								( CritterCl& cr );
	   CritterCl* 		SetCritterHex							( CritterCl* cr, uint16 hexX, uint16 hexY );
	   
EXPORT void 			FocusClient								( );
EXPORT void 			FlashClient								( );
EXPORT bool 			ClientIsFocused							( );
EXPORT int  			GetClientMapWidth						( );
EXPORT int  			GetClientMapHeight						( );
EXPORT int 				PrepareWSA								( );
EXPORT int 				ClearWSA								( );

EXPORT bool 			map_message								( ScriptString& message, uint16& hexX, uint16& hexY, uint& color, uint& delay );

EXPORT bool 			IsHexPassed								( uint hexX, uint hexY );
EXPORT bool 			IsScenNoPassed							( uint hexX, uint hexY );
EXPORT bool 			IsHexRaked								( uint hexX, uint hexY );
EXPORT void 			UnblockHexPassed						( uint hexX, uint hexY );
EXPORT void 			BlockHexPassed							( uint hexX, uint hexY );
EXPORT void 			BlockHexRaked							( uint hexX, uint hexY );
EXPORT void 			UnblockHexRaked							( uint hexX, uint hexY );

EXPORT uint 			getItemInHex							( uint16 pid, uint hexX, uint hexY );
EXPORT uint 			checkWorkbenchInRadius					( uint16 pid, uint hexX, uint hexY, uint16 radius );

EXPORT void				GetOnline								( uint& online, uint& uptame );
EXPORT void 			item_map_in								( Item& item );
EXPORT void 			item_map_out							( Item& item );
EXPORT void 			item_inv_in								( Item& item );
EXPORT void 			item_inv_out							( Item& item );
EXPORT void 			item_drop								( Item& item );
EXPORT void				item_map_changed						( Item& itemNow, Item& itemBefore );

EXPORT bool 			out_message								( ScriptString& message, int& sayType );
#endif

#ifndef __SERVER
EXPORT bool 			start									( );
#endif
#ifndef __CLIENT
	   void 			AutoScript								( );
#endif

EXPORT bool 			Critter_IsInjured						( CritterMutual& cr );
EXPORT bool 			Critter_IsDmgEye						( CritterMutual& cr );
EXPORT bool 			Critter_IsDmgLeg						( CritterMutual& cr );
EXPORT bool 			Critter_IsDmgTwoLeg						( CritterMutual& cr );
EXPORT bool 			Critter_IsDmgArm						( CritterMutual& cr );
EXPORT bool 			Critter_IsDmgTwoArm						( CritterMutual& cr );
EXPORT bool 			Critter_IsAddicted						( CritterMutual& cr );
EXPORT bool 			Critter_IsOverweight					( CritterMutual& cr );
EXPORT int 				getParam_VisibleDist					( CritterMutual& cr, uint );
	   uint 			GetMultihex								( CritterMutual& cr );
	   uint 			GetUseApCost							( CritterMutual& cr, Item& item, uint8 mode );
	   uint 			GetAttackDistantion						( CritterMutual& cr, Item& item, uint8 mode );

	   uint 			GetAimApCost							( int hitLocation );
	   uint 			GetAimHit								( int hitLocation );
	   
EXPORT bool 			Item_Weapon_IsHtHAttack					( Item& item, uint8 mode );
EXPORT bool 			Item_Weapon_IsGunAttack					( Item& item, uint8 mode );
EXPORT bool 			Item_Weapon_IsRangedAttack				( Item& item, uint8 mode );

EXPORT bool 			FileDelete								( ScriptString& filename );
EXPORT bool 			FileRename								( ScriptString& filename, ScriptString& newName );
EXPORT bool 			GetMyFolderFiles						( ScriptString& dirName, ScriptString& outStr );
EXPORT void 			ClearLog								( ScriptString& log );

	   uint 			GetCountGlobalVars						( const ScriptString& );
	   bool 			RunOption								( uint index, ScriptString& arg, const ScriptString& moduleName, ScriptString& function );
	   bool 			GetDeclarationGlobalVar					( ScriptString& declaration, uint index, const ScriptString& );
	   void 			HashToStr								( uint hash, ScriptString& str );

void GetModuleName( ScriptString& outStr )
{
    outStr = "none";
    asIScriptContext* context = ScriptGetActiveContext();
    if( context )
    {
        asIScriptFunction* ActiveFunc = context->GetFunction();
        if( ActiveFunc && ActiveFunc->GetModuleName() )
            outStr = ActiveFunc->GetModuleName();
    }
}

void ClearLog( ScriptString& log )
{
    
	__try
	{
		Log( "%s\n", log.c_str() );
	}
	__except( EXCEPTION_ACCESS_VIOLATION )
	{
		Log( "Oups clearlog.\n" );
    }
}
#ifndef __MAPPER
#ifdef __SERVER

uint BindFarmScript( ScriptString* module, ScriptString* func )
{
    if( module && func )
        return FOnline->ScriptBind( module->c_str(), func->c_str(), false );
	return 0;
}

bool RunFarmScriptBool( ScriptString* module, ScriptString* func )
{
    return RunFarmScriptBoolById( BindFarmScript( module, func ) );
}

bool RunIsCreateFarmItem( uint funcId, ScriptDictionary& farmIt, int typeCreated, uint idCreated, uint16 hexX, uint16 hexY )
{
    if( funcId && FOnline->ScriptPrepare( funcId ) )
    {
        FOnline->ScriptSetArgObject( &farmIt );
        FOnline->ScriptSetArgInt( typeCreated );
        FOnline->ScriptSetArgUInt( idCreated );
        FOnline->ScriptSetArgUInt16( hexX );
        FOnline->ScriptSetArgUInt16( hexY );
        if( FOnline->ScriptRunPrepared() )
            return FOnline->ScriptGetReturnedBool();
    }
    return false;
}

bool RunFarmScriptBoolById( uint funcId )
{
    if( funcId && FOnline->ScriptPrepare( funcId ) && FOnline->ScriptRunPrepared() )
        return FOnline->ScriptGetReturnedBool();
    return false;
}

bool Critter_IsEvent( Critter& cr, int event )
{
    if( CRITTER_EVENT_MAX <= event )
        return false;
    return cr.FuncId[ event ] != 0;
}

bool Item_IsEvent( Item& item, int event )
{
    if( ITEM_EVENT_MAX <= event )
        return false;
    return item.FuncId[ event ] != 0;
}

bool SetCustomName( Critter& cr, ScriptString& name )
{
    if( ( name.length() > 0 && name.length() < FOnline->MinNameLength ) || name.length() >= ( CUSTOM_NAME_END - CUSTOM_NAME_BEGIN ) * 4 / -1 )
    {
        char log[ 255 ];
        sprintf_s( log, "Unable to assign custom name! Invalid name length: %d\n", name.length() );
        Log( log );
        return false;
    }
    for( uint n = CUSTOM_NAME_BEGIN; n <= CUSTOM_NAME_END; n++ )
    {
        const_cast< int& >( cr.Params[ n ] ) = 0;
        FOnline->CritterChangeParameter( cr, n );
    }
    memcpy( const_cast< int* >( &( cr.Params[ CUSTOM_NAME_BEGIN ] ) ), const_cast< char* >( name.c_str() ), name.length() );
    return true;
}

uint Critter_GetViewMapId( Critter& cr )
{
    return cr.ViewMapId;
}

uint Critter_GetViewMapParams( Critter& cr, uint16& ViewMapHx, uint16& ViewMapHy, uint8& ViewMapDir, uint& ViewMapLocEnt, uint& ViewMapLocId )
{
    ViewMapLocId = cr.ViewMapLocId;
    ViewMapHx = cr.ViewMapHx;
    ViewMapHy = cr.ViewMapHy;
    ViewMapDir = cr.ViewMapDir;
    ViewMapLocEnt = cr.ViewMapLocEnt;
    return cr.ViewMapId;
}

ScriptString* GetCustomName( Critter& cr )
{
    if( cr.Params[ CUSTOM_NAME_BEGIN ] == 0 )
    {
        return &( ScriptString::Create( ( cr.NameStr.c_str() ) ) );
    }
#endif

#ifdef __CLIENT
ScriptString* GetCustomName( CritterCl& cr )
{
    if( cr.Params[ CUSTOM_NAME_BEGIN ] == 0 )
        return &( ScriptString::Create( cr.Name.c_str() ) );
#endif

    return &( ScriptString::Create( reinterpret_cast< const char* >( &cr.Params[ CUSTOM_NAME_BEGIN ] ) ) );
}
#endif
#ifdef __CLIENT

void SetRainSpeed( int16 x, int16 y )
{
    const_cast< int16& >( FOnline->RainSpeedX ) = x;
    const_cast< int16& >( FOnline->RainSpeedY ) = y;
}

int MsgBox( ScriptString& text, ScriptString& caption, uint flags )
{
    return MessageBox( NULL, text.c_str(), caption.c_str(), flags );
}
#endif

const char* FuncTypeName( asEFuncType type )
{
	switch( type )
	{
		case asFUNC_DUMMY:  return "Dummy";
		case asFUNC_SYSTEM: return "System";
		case asFUNC_SCRIPT: return "Script";
		case asFUNC_INTERFACE: return "Interface";
		case asFUNC_VIRTUAL: return "Virtual";
		case asFUNC_FUNCDEF: return "Funcdef";
		case asFUNC_IMPORTED: return "Import";
	}
	return "Error";
}

void CallStackToLog()
{
    asIScriptContext* context = ScriptGetActiveContext();
    if( context )
    {
		asIScriptFunction* func = context->GetSystemFunction();
        if( func )
            Log( "\"%s\" %s\n", FuncTypeName( func->GetFuncType() ), func->GetDeclaration( true, true ) );
		
        uint       currentCallStack = 0;
        const uint lenghCallStack = context->GetCallstackSize();
        while( currentCallStack < lenghCallStack )
        {
            func = context->GetFunction( currentCallStack );
            if( func )
                Log( "%u - \"%s\" %s@%s\n", currentCallStack++, FuncTypeName( func->GetFuncType() ), func->GetModuleName(), func->GetDeclaration( true, true ) );
        }
    }
}

void GetMD5FileMK2( ScriptString& name, ScriptString& outStr )
{
    TMD5   MD5;
    DWORD  dwSize;
    LPVOID pFile = MapFile_ReadOnly( TEXT( name.c_str() ), dwSize );
    MD5 = GetMD5( PUCHAR( pFile ), dwSize );
    UnmapViewOfFile( pFile );
    outStr = MD5.hash;
}

void GetMD5StringMK2( ScriptString& name, ScriptString& outStr )
{
    TMD5        MD5;
    const char* str = name.c_str();
    MD5 = GetMD5( PUCHAR( str ), strlen( str ) - 1 );
    outStr = MD5.hash;
}

template< typename T1, typename T2 >
bool        GetMyFloderFiles( T1& dirName, T2& outStr );

bool GetMyFolderFiles( ScriptString& dirName, ScriptString& outStr )
{
    return GetMyFloderFiles< ScriptString, ScriptString  >( dirName, outStr );
}

template< typename T1, typename T2 >
bool GetMyFloderFiles( T1& dirName, T2& outStr )
{
    WIN32_FIND_DATA ffd;
    HANDLE          hFind = INVALID_HANDLE_VALUE;

    hFind = FindFirstFile( dirName.c_str(), &ffd );

    if( INVALID_HANDLE_VALUE == hFind )
        return false;

    do
    {
        if( ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
            continue;

        outStr += "\n";
        outStr += ffd.cFileName;
    }
    while( FindNextFile( hFind, &ffd ) != 0 );
    FindClose( hFind );
    return true;
}

#ifdef __SERVER
#define STR_SCRIPT_ITEM		"::Item"
#endif
#ifdef __CLIENT
#define STR_SCRIPT_ITEM		"::ItemCl"
#endif

FONLINE_DLL_ENTRY( isCompiler )
{
    //ASEngine->SetEngineProperty( asEP_REQUIRE_ENUM_SCOPE, 1 );
    ASEngine->SetEngineProperty( asEP_BUILD_WITHOUT_LINE_CUES , 1 );
    //ASEngine->SetEngineProperty( asEP_COMPILER_WARNINGS , false );
	
    const char* defName = ASEngine->GetDefaultNamespace();
    // bool compiler - true if script compiled using ASCompiler, false if script compiled in server
    // In this function all global variables is initialized, if compiled not by compiler

    if( !InitMD5() )
        Log( "Error InitMD5: %u\n", GetLastError() );
	
    ASEngine->SetDefaultNamespace( "ScriptInfo" );
	ScriptEnum::Registration();
	BuilderCall::Registration();
	RegisterScriptFileSystem();
	
    if( ASEngine->RegisterGlobalFunction( "void CallStackToLog( )", asFUNCTION( CallStackToLog ), asCALL_CDECL ) < 0 )
        Log( "Error reg void CallStackToLog\n" );

    if( ASEngine->RegisterGlobalFunction( "uint CountGlobalVars( const ::string&in moduleName )", asFUNCTION( GetCountGlobalVars ), asCALL_CDECL ) < 0 )
        Log( "Error reg CountGlobalVars\n" );
    if( ASEngine->RegisterGlobalFunction( "bool GetDeclarationGlobalVar( ::string& declaration, uint index, const ::string& moduleName )", asFUNCTION( GetDeclarationGlobalVar ), asCALL_CDECL ) < 0 )
        Log( "Error reg GetDeclarationGlobalVar\n" );
	
#ifdef __SERVER
    if( ASEngine->RegisterGlobalFunction( "uint GetDialogDemandFunctionId( ::string&, ::string&, int[]& )", asFUNCTION( GetDialogDemandFunctionId ), asCALL_CDECL ) < 0 )
        Log( "Error reg GetDialogDemandFunctionId\n" );
    if( ASEngine->RegisterGlobalFunction( "bool RunDialogDemandFunctionId( ::Critter&, ::Critter@, uint funcId, int[]& )", asFUNCTION( RunDialogDemandFunctionId ), asCALL_CDECL ) < 0 )
        Log( "Error reg RunDialogDemandFunctionId\n" );
    if( ASEngine->RegisterGlobalFunction( "uint GetDialogResultFunctionId( ::string&, ::string&, int[]&, bool& isReturn )", asFUNCTION( GetDialogResultFunctionId ), asCALL_CDECL ) < 0 )
        Log( "Error reg GetDialogResultFunctionId\n" );
    if( ASEngine->RegisterGlobalFunction( "uint RunDialogResultFunctionId( ::Critter&, ::Critter@, uint funcId, int[]&, bool isReturn )", asFUNCTION( RunDialogResultFunctionId ), asCALL_CDECL ) < 0 )
        Log( "Error reg RunDialogResultFunctionId\n" );
    if( ASEngine->RegisterGlobalFunction( "uint GetDialogBranchFunctionId( ::string&, ::string&, bool& isReturn )", asFUNCTION( GetDialogBranchFunctionId ), asCALL_CDECL ) < 0 )
        Log( "Error reg GetDialogBranchFunctionId\n" );
    if( ASEngine->RegisterGlobalFunction( "uint RunDialogBranchFunctionId( ::Critter&, ::Critter@, uint funcId, ::string@ text, bool isReturn )", asFUNCTION( RunDialogBranchFunctionId ), asCALL_CDECL ) < 0 )
        Log( "Error reg RunDialogBranchFunctionId\n" );
#endif
	
    if( ASEngine->RegisterGlobalFunction( "bool RunOptionFunction( uint index, ::string& type, const ::string&in moduleName, ::string& function )", asFUNCTION( RunOption ), asCALL_CDECL ) < 0 )
        Log( "Error reg RunOption\n" );

    ASEngine->SetDefaultNamespace( "Mk2" );
	
    ASEngine->RegisterInterface( "TraceDescriptor" );
	
    ASEngine->RegisterInterface( "Descriptor" );
	
	ASEngine->RegisterInterface( "ClientDataPacket" );
	
    ASEngine->RegisterInterface( "ItemPacket" );
    ASEngine->RegisterInterface( "UpgradedItemPacket" );
	
    ASEngine->RegisterInterface( "CombatArmorPacket" );
	
    ASEngine->RegisterInterfaceMethod( "Descriptor", "uint get_Priority( )" );
    ASEngine->RegisterInterfaceMethod( "Descriptor", "bool IsSet( Mk2::Descriptor@ new )" );
    ASEngine->RegisterInterfaceMethod( "Descriptor", "::string@ get_Name( )" );

#ifdef __SERVER
    ASEngine->RegisterInterfaceMethod( "ItemPacket", "bool CritterUse( ::Critter& cr, ::Item& item, ::Critter@ targetCr, ::Item@ targetItem, ::Scenery@ targetScen, uint param )" );
#endif

#ifndef __MAPPER
    if( ASEngine->RegisterObjectMethod( STR_SCRIPT_ITEM, "void set_ScriptDescriptor( Mk2::Descriptor@ value )", asFUNCTION( Item_SetScriptDescriptor ), asCALL_CDECL_OBJFIRST ) < 0 )
        Log( "Error registering Item::set_ScriptDescriptor()\n" );
    if( ASEngine->RegisterObjectMethod( STR_SCRIPT_ITEM, "Mk2::Descriptor@ get_ScriptDescriptor()", asFUNCTION( Item_GetScriptDescriptor ), asCALL_CDECL_OBJFIRST ) < 0 )
        Log( "Error registering Item::get_ScriptDescriptor()\n" );
#endif

	if( ASEngine->RegisterGlobalFunction( "void HashToStr( uint hash, ::string& str )", asFUNCTION( HashToStr ), asCALL_CDECL ) < 0 )
        Log( "Error reg void HashToStr\n" );
	
	if( ASEngine->RegisterGlobalFunction( "void GetMD5File( ::string&in, ::string&out )", asFUNCTION( GetMD5FileMK2 ), asCALL_CDECL ) < 0 )
        Log( "Error reg void GetMD5FileMK2\n" );
    if( ASEngine->RegisterGlobalFunction( "bool GetFolderFiles( ::string&in, ::string&out )", asFUNCTION( GetMyFolderFiles ), asCALL_CDECL ) < 0 )
        Log( "Error reg bool GetFolderFiles\n" );
    if( ASEngine->RegisterGlobalFunction( "void GetMD5String( ::string&in, ::string&out )", asFUNCTION( GetMD5StringMK2 ), asCALL_CDECL ) < 0 )
        Log( "Error reg void GetMD5StringMK2\n" );
	
    ASEngine->SetDefaultNamespace( defName );
#ifdef __SERVER

    if( ASEngine->RegisterObjectMethod( STR_SCRIPT_ITEM, "::string@ GetLexems()", asFUNCTION( Item_GetLexems ), asCALL_CDECL_OBJFIRST ) < 0 )
        Log( "Error registering Item::GetLexems()\n" );
	
	
    if( ASEngine->RegisterObjectProperty( "Critter", "uint GlobalPVP_TargetGroupLeadId", offsetof( Critter, GlobalPVP_TargetGroupLeadId ) ) < 0 )
        Log( "Error reg uint Critter::GlobalTargetGroupLeadId\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "int GlobalPVP_PosX", offsetof( Critter, GlobalPVP_PosX ) ) < 0 )
        Log( "Error reg int Critter::GlobalPVP_PosX\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "int GlobalPVP_PosY", offsetof( Critter, GlobalPVP_PosY ) ) < 0 )
        Log( "Error reg int Critter::GlobalPVP_PosY\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "uint GlobalPVP_LastHunterId", offsetof( Critter, GlobalPVP_LastHunterId ) ) < 0 )
        Log( "Error reg uint Critter::GlobalPVP_LastHunterId\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "uint GlobalPVP_LastHunterTick", offsetof( Critter, GlobalPVP_LastHunterTick ) ) < 0 )
        Log( "Error reg uint Critter::GlobalPVP_LastHunterTick\n" );
    if( ASEngine->RegisterObjectMethod( "Critter", "bool SetCustomName(string& name)", asFUNCTION( SetCustomName ), asCALL_CDECL_OBJFIRST ) < 0 )
        Log( "Error registering Critter::SetCustomName()\n" );
    if( ASEngine->RegisterObjectMethod( "Critter", "string@ get_Name()", asFUNCTION( GetCustomName ), asCALL_CDECL_OBJFIRST ) < 0 )
        Log( "Error registering Critter::GetCustomName()\n" );

    if( ASEngine->RegisterObjectProperty( "Item", "int16 CurrentHp", offsetof( Item, Data.Deterioration ) ) < 0 )
        Log( "Error reg int16 Item::CurrentHp\n" );
    if( ASEngine->RegisterObjectProperty( "Item", "int16 CraftFlags", offsetof( Item, Data.CraftFlags ) ) < 0 )
        Log( "Error reg int16 Item::CraftFlags\n" );
    if( ASEngine->RegisterObjectProperty( "Item", "uint8 Steal", offsetof( Item, AccCritter.Steal ) ) < 0 )
        Log( "Error reg uint8 Item::AccCritter::Steal\n" );
	
	
    if( ASEngine->RegisterObjectMethod( "Item", "void UpdateViewer( Critter@ cr )", asMETHOD( Item, UpdateViewer ), asCALL_THISCALL ) < 0 )
        Log( "Error registering Item::UpdateViewer( Critter@ )\n" );
	
    if( ASEngine->RegisterObjectProperty( "Critter", "uint GlobalGroupUid", offsetof( Critter, GlobalGroupUid ) ) < 0 )
        Log( "Error reg uint Critter::GlobalGroupUid\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "bool IsFarmGenerated", offsetof( Critter, IsFarmGenerated ) ) < 0 )
        Log( "Error reg bool Critter::IsFarmGenerated\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "uint FarmUnicId", offsetof( Critter, FarmUnicId ) ) < 0 )
        Log( "Error reg uint Critter::FarmUnicId\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "uint FarmProtoMobId", offsetof( Critter, FarmProtoMobId ) ) < 0 )
        Log( "Error reg uint Critter::FarmProtoMobId\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "const uint16 LastHexX", offsetof( Critter, LastHexX ) ) < 0 )
        Log( "Error reg const uint16 Critter::LastHexX\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "const uint16 LastHexY", offsetof( Critter, LastHexY ) ) < 0 )
        Log( "Error reg const uint16 Critter::LastHexY\n" );
    if( ASEngine->RegisterObjectProperty( "Location", "uint FarmLocId", offsetof( Location, Data.FarmLocId ) ) < 0 )
        Log( "Error reg uint Location::FarmLocId\n" );
    if( ASEngine->RegisterObjectProperty( "Location", "uint FarmLocPId", offsetof( Location, Data.FarmLocPId ) ) < 0 )
        Log( "Error reg uint Location::FarmLocPId\n" );
    if( ASEngine->RegisterObjectProperty( "Location", "uint FarmLocVersion", offsetof( Location, Data.FarmLocVersion ) ) < 0 )
        Log( "Error reg uint Location::FarmLocVersion\n" );
    if( ASEngine->RegisterObjectProperty( "Location", "uint8 Type", offsetof( Location, Data.TypeLocation ) ) < 0 )
        Log( "Error reg uint8 Location::TypeLocation\n" );
    if( ASEngine->RegisterObjectProperty( "Location", "uint FractionId", offsetof( Location, Data.FractionId ) ) < 0 )
        Log( "Error reg uint Location::FractionId\n" );
    if( ASEngine->RegisterObjectProperty( "Location", "uint FarmLocTimeEventId", offsetof( Location, Data.FarmLocTimeEventId ) ) < 0 )
        Log( "Error reg uint Location::FarmLocTimeEventId\n" );

    if( ASEngine->RegisterObjectProperty( "Critter", "bool CityRole_IsProtected", offsetof( Critter, Params[ CITY_ROLE_ENGINE_0 ] ) + sizeof( bool ) * 2 ) < 0 )
        Log( "Error reg bool Critter::IsFarmGenerated\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "bool CityRole_IsNotHelper", offsetof( Critter, Params[ CITY_ROLE_ENGINE_0 ] ) + sizeof( bool ) * 3 ) < 0 )
        Log( "Error reg bool Critter::IsFarmGenerated\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "bool CityRole_IsGuard", offsetof( Critter, Params[ CITY_ROLE_ENGINE_0 ] ) ) < 0 )
        Log( "Error reg bool Critter::IsFarmGenerated\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "bool CityRole_IsPatrol", offsetof( Critter, Params[ CITY_ROLE_ENGINE_0 ] ) + sizeof( bool ) ) < 0 )
        Log( "Error reg bool Critter::IsFarmGenerated\n" );

    if( ASEngine->RegisterObjectProperty( "Critter", "const uint LastContainerId", offsetof( Critter, AccessContainerId ) ) < 0 )
        Log( "Error reg const uint Critter::AccessContainerId\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "const uint PrevHexTick", offsetof( Critter, PrevHexTick ) ) < 0 )
        Log( "Error reg const uint Critter::PrevHexTick\n" );

    if( ASEngine->RegisterObjectProperty( "Critter", "uint ToLeader_MapId", offsetof( Critter, ToLeader_MapId ) ) < 0 )
        Log( "Error reg uint Critter::ToLeader_MapId\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "uint16 ToLeader_HexX", offsetof( Critter, ToLeader_HexX ) ) < 0 )
        Log( "Error reg uint16 Critter::ToLeader_HexX\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "uint16 ToLeader_HexY", offsetof( Critter, ToLeader_HexY ) ) < 0 )
        Log( "Error reg uint16 Critter::ToLeader_HexY\n" );
    if( ASEngine->RegisterObjectProperty( "Critter", "uint GlobalIdleNextTick", offsetof( Critter, GlobalIdleNextTick ) ) < 0 )
        Log( "Error reg uint Critter::GlobalIdleNextTick\n" );

    if( ASEngine->RegisterObjectMethod( "Critter", "uint8 get_SurplusPoint( uint ind )", asMETHOD( Critter, get_SurplusPoint ), asCALL_THISCALL ) < 0 )
        Log( "Error registering Critter::get_SurplusPoint( uint )\n" );
    if( ASEngine->RegisterObjectMethod( "Critter", "void set_SurplusPoint( uint ind, uint8 value )", asMETHOD( Critter, set_SurplusPoint ), asCALL_THISCALL ) < 0 )
        Log( "Error registering Critter::set_SurplusPoint( uint, uint )\n" );
    if( ASEngine->RegisterObjectMethod( "Critter", "uint8 get_CountReadBook( uint ind )", asMETHOD( Critter, get_CountReadBook ), asCALL_THISCALL ) < 0 )
        Log( "Error registering Critter::get_CountReadBook( uint )\n" );
    if( ASEngine->RegisterObjectMethod( "Critter", "void set_CountReadBook( uint ind, uint8 value )", asMETHOD( Critter, set_CountReadBook ), asCALL_THISCALL ) < 0 )
        Log( "Error registering Critter::set_CountReadBook( uint, uint )\n" );

    if( ASEngine->RegisterObjectMethod( "Map", "bool UnSetHexFlag( uint16 hx, uint16 hy, uint flag )", asMETHOD( Map, UnSetHexFlag ), asCALL_THISCALL ) < 0 )
        Log( "Error reg bool Map::UnSetHexFlag( uint16 hx, uint16 hy, uint flag )\n" );
    if( ASEngine->RegisterObjectMethod( "Map", "bool SetHexFlag( uint16 hx, uint16 hy, uint flag )", asMETHOD( Map, SetHexFlag ), asCALL_THISCALL ) < 0 )
        Log( "Error reg bool Map::SetHexFlag( uint16 hx, uint16 hy, uint flag )\n" );

    if( ASEngine->RegisterObjectProperty( "Map", "uint FarmMapVersion", offsetof( Map, Data.FarmMapVersion ) ) < 0 )
        Log( "Error reg uint Map::FarmMapVersion\n" );
    if( ASEngine->RegisterObjectProperty( "Map", "int CityManagerIndex", offsetof( Map, Data.CityManagerIndex ) ) < 0 )
        Log( "Error reg int Map::CityManagerIndex\n" );

    if( ASEngine->RegisterObjectProperty( "Map", "int MapDynamicIndex", offsetof( Map, Data.MapDynamicIndex ) ) < 0 )
        Log( "Error reg uint Map::MapDynamicIndex\n" );
    if( ASEngine->RegisterObjectProperty( "Map", "uint MapDynamicObjectCount", offsetof( Map, Data.MapDynamicObjectCount ) ) < 0 )
        Log( "Error reg uint Map::MapDynamicObjectCount\n" );
    if( ASEngine->RegisterObjectProperty( "Map", "uint MapDynamicVersion", offsetof( Map, Data.MapDynamicVersion ) ) < 0 )
        Log( "Error reg uint Map::MapDynamicVersion\n" );

    if( ASEngine->RegisterObjectProperty( "Map", "bool CityManager_IsNoob", offsetof( Map, Data.CityManager_IsNoob ) ) < 0 )
        Log( "Error reg bool Map::CityManager_IsNoob\n" );
    if( ASEngine->RegisterObjectProperty( "Map", "bool FarmMapIsProtect", offsetof( Map, Data.FarmMapIsProtect ) ) < 0 )
        Log( "Error reg bool Map::FarmMapIsProtect\n" );

    if( ASEngine->RegisterObjectProperty( "NpcPlane", "bool Prosecution_Run", offsetof( NpcPlane, Prosecution.IsRun ) ) < 0 )
        Log( "Error reg bool NpcPlane::Prosecution_Run\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint Prosecution_TargetId", offsetof( NpcPlane, Prosecution.TargId ) ) < 0 )
        Log( "Error reg uint NpcPlane::Prosecution_TargetId\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "int Walk_Var0", offsetof( NpcPlane, Walk.Vars[ 0 ] ) ) < 0 )
        Log( "Error reg int NpcPlane::Walk_Var0\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "int Walk_Var1", offsetof( NpcPlane, Walk.Vars[ 1 ] ) ) < 0 )
        Log( "Error reg int NpcPlane::Walk_Var1\n" );

    if( ASEngine->RegisterObjectProperty( "NpcPlane", "NpcPlane@ ChildPlane", offsetof( NpcPlane, ChildPlane ) ) < 0 )
        Log( "Error reg NpcPlane@ NpcPlane:: ChildPlane\n" );

    if( ASEngine->RegisterObjectMethod( "NpcPlane", "uint GetChildsCount()", asMETHOD( NpcPlane, GetChildsCount ), asCALL_THISCALL ) < 0 )
        Log( "Error reg uint NpcPlane::GetChildsCount()\n" );
    if( ASEngine->RegisterObjectMethod( "NpcPlane", "uint GetChildIndex(NpcPlane@+)", asMETHOD( NpcPlane, GetChildIndex ), asCALL_THISCALL ) < 0 )
        Log( "Error reg uint NpcPlane::GetChildIndex()\n" );

    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint8 Walk_TypeWalkReason", offsetof( NpcPlane, Walk.TypeWalkReason ) ) < 0 )
        Log( "Error reg uint8 NpcPlane::Walk_TypeWalkReason\n" );

    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint Walk_Reason_CritterId", offsetof( NpcPlane, Walk.Transit_Id ) ) < 0 )
        Log( "Error reg uint NpcPlane::Walk_Transit_GroupId\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint Walk_Reason_MapId", offsetof( NpcPlane, Walk.Transit_Id ) ) < 0 )
        Log( "Error reg uint NpcPlane::Walk_Transit_MapId\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint16 Walk_Reason_EntireId", offsetof( NpcPlane, Walk.Transit_X ) ) < 0 )
        Log( "Error reg uint8 NpcPlane::Walk_Transit_EntireId\n" );

    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint16 Walk_Reason_HexX", offsetof( NpcPlane, Walk.Transit_X ) ) < 0 )
        Log( "Error reg uint16 NpcPlane::Walk_Transit_HexX\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint16 Walk_Reason_HexY", offsetof( NpcPlane, Walk.Transit_Y ) ) < 0 )
        Log( "Error reg uint16 NpcPlane::Walk_Transit_HexY\n" );

    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint16 Walk_Reason_WorldX", offsetof( NpcPlane, Walk.Transit_X ) ) < 0 )
        Log( "Error reg uint16 NpcPlane::Walk_Transit_WorldX\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint16 Walk_Reason_WorldY", offsetof( NpcPlane, Walk.Transit_Y ) ) < 0 )
        Log( "Error reg uint16 NpcPlane::Walk_Transit_WorldY\n" );

    if( ASEngine->RegisterObjectProperty( "NpcPlane", "int Misc_Var0", offsetof( NpcPlane, Misc.Vars[ 0 ] ) ) < 0 )
        Log( "Error reg int NpcPlane::Misc_Var0\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "int Misc_Var1", offsetof( NpcPlane, Misc.Vars[ 1 ] ) ) < 0 )
        Log( "Error reg int NpcPlane::Misc_Var1\n" );

    if( ASEngine->RegisterObjectProperty( "NpcPlane", "int Pick_Var0", offsetof( NpcPlane, Pick.Vars[ 0 ] ) ) < 0 )
        Log( "Error reg int NpcPlane::Pick_Var0\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "int Pick_Var1", offsetof( NpcPlane, Pick.Vars[ 1 ] ) ) < 0 )
        Log( "Error reg int NpcPlane::Pick_Var1\n" );

    if( ASEngine->RegisterObjectProperty( "NpcPlane", "int Prosecution_Var0", offsetof( NpcPlane, Prosecution.Vars[ 0 ] ) ) < 0 )
        Log( "Error reg uint NpcPlane::Prosecution_Var0\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint Prosecution_Var1", offsetof( NpcPlane, Prosecution.Vars[ 1 ] ) ) < 0 )
        Log( "Error reg uint NpcPlane::Prosecution_Var1\n" );

    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint8 Chamber", offsetof( NpcPlane, Attack.hamberStage ) ) < 0 )
        Log( "Error reg NpcPlane::СhamberStage\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint16 ChamberBestX", offsetof( NpcPlane, Attack.hamberStageBestCoord[ 0 ] ) ) < 0 )
        Log( "Error reg ChamberBestX\n" );
    if( ASEngine->RegisterObjectProperty( "NpcPlane", "uint16 ChamberBestY", offsetof( NpcPlane, Attack.hamberStageBestCoord[ 1 ] ) ) < 0 )
        Log( "Error reg ChamberBestY\n" );


    if( ASEngine->RegisterObjectMethod( "Critter", "void set_SetMaster( Critter& master )", asMETHOD( Critter, set_SetMaster ), asCALL_THISCALL ) < 0 )
        Log( "Error registering Critter::set_SetMaster( Critter& )\n" );
    if( ASEngine->RegisterObjectMethod( "Critter", "uint GetMercIds( array< uint >@ ids )", asMETHOD( Critter, GetMercIds ), asCALL_THISCALL ) < 0 )
        Log( "Error registering Critter::GetMercIds( array< uint >@ ids )\n" );
    if( ASEngine->RegisterObjectMethod( "Critter", "void DeleteMerc( Critter& merc )", asMETHOD( Critter, DeleteMerc ), asCALL_THISCALL ) < 0 )
        Log( "Error registering Critter::DeleteMerc( Critter& )\n" );
    if( ASEngine->RegisterObjectMethod( "Critter", "void FreeMercSlot( uint )", asMETHOD( Critter, FreeMercSlot ), asCALL_THISCALL ) < 0 )
        Log( "Error registering Critter::FreeMercSlot( uint )\n" );

	
    ASEngine->SetDefaultNamespace( "Mk2" );
	
    ASEngine->RegisterInterface( "CritterPacket" );
    ASEngine->RegisterInterface( "PlayerPacket" );
    ASEngine->RegisterInterface( "NpcPacket" );
    ASEngine->RegisterInterface( "MessagePacket" );
    ASEngine->RegisterInterface( "CombatTargetPacket" );
    ASEngine->RegisterInterface( "CombatProccessPacket" );
	
    ASEngine->SetDefaultNamespace( defName );
	
	ASEngine->RegisterFuncdef( "bool FuncdefEventCritterInit( ::Critter@ critter, bool firstTime )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterFinish( ::Critter@ critter, bool toDelete )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterIdle( ::Critter@ critter )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterRespawn( ::Critter@ critter )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterMoveItem( ::Critter@ critter, ::Item@ item, uint8 fromSlot )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterAttacked( ::Critter@ critter, ::Critter@ attacker )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterDead( ::Critter@ critter, ::Critter@ killer )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterAttack( ::Critter@ critter, ::Critter@ target, ::ProtoItem@ weapon, uint8 weaponMode, ::ProtoItem@ ammo )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventNpcPlaneRun( ::Critter& critter, ::NpcPlane& plane, int reason, uint& r0, uint& r1, uint& r2 )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventNpcPlaneBegin( ::Critter@ critter, ::NpcPlane@ plane, int reason, ::Critter@ someCr, ::Item@ someItem )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventNpcPlaneEnd( ::Critter@ critter, ::NpcPlane@ plane, int reason, ::Critter@ someCr, ::Item@ someItem )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventPlayerGetAccess( ::Critter@ critter, int access, ::string@ password )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventPlayerAllowCommand( ::Critter@ player, ::string@ adminPanel, uint8 command )" );

    ASEngine->RegisterFuncdef( "bool FuncdefEventPlayerLevelUp(::Critter@ player, uint skillIndex, uint skillUp, uint perkIndex)" );

    ASEngine->RegisterFuncdef( "bool FuncdefEventWorldSave( uint currentIndex, ::array<uint>& deleteIndexes )" );

    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterShow( ::Critter@ critter, ::Critter@ opponent )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterShowMe( ::Critter@ critter, ::Critter@ opponent )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterHide( ::Critter@ critter, ::Critter@ opponent )" );
    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterHideMe( ::Critter@ critter, ::Critter@ opponent )" );

    ASEngine->RegisterFuncdef( "bool FuncdefEventCritterMessage( ::Critter@ critter, Mk2::MessagePacket@ message )" );
	
	ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterInit( ::Critter@ critter, bool firstTime )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterFinish( ::Critter@ critter, bool toDelete )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterIdle( ::Critter@ critter )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterRespawn( ::Critter@ critter )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterMoveItem( ::Critter@ critter, ::Item@ item, uint8 fromSlot )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterAttacked( ::Critter@ critter, ::Critter@ attacker )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterDead( ::Critter@ critter, ::Critter@ killer )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterAttack( ::Critter@ critter, ::Critter@ target, ::ProtoItem@ weapon, uint8 weaponMode, ::ProtoItem@ ammo )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultNpcPlaneRun( ::Critter& critter, ::NpcPlane& plane, int reason, uint& r0, uint& r1, uint& r2 )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultNpcPlaneBegin( ::Critter@ critter, ::NpcPlane@ plane, int reason, ::Critter@ someCr, ::Item@ someItem )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultNpcPlaneEnd( ::Critter@ critter, ::NpcPlane@ plane, int reason, ::Critter@ someCr, ::Item@ someItem )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultPlayerGetAccess( ::Critter@ critter, int access, ::string@ password )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultPlayerAllowCommand( ::Critter@ player, ::string@ adminPanel, uint8 command )" );

    ASEngine->RegisterFuncdef( "void FuncdefEventResultPlayerLevelUp(::Critter@ player, uint skillIndex, uint skillUp, uint perkIndex)" );

    ASEngine->RegisterFuncdef( "void FuncdefEventResultWorldSave( uint currentIndex, ::array<uint>& deleteIndexes )" );

    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterShow( ::Critter@ critter, ::Critter@ opponent )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterShowMe( ::Critter@ critter, ::Critter@ opponent )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterHide( ::Critter@ critter, ::Critter@ opponent )" );
    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterHideMe( ::Critter@ critter, ::Critter@ opponent )" );

    ASEngine->RegisterFuncdef( "void FuncdefEventResultCritterMessage( ::Critter@ critter, Mk2::MessagePacket@ message )" );
	
    ASEngine->SetDefaultNamespace( "Mk2" );
	
    if( ASEngine->RegisterGlobalFunction( "bool IsEvent( ::Critter&inout cr, int event )", asFUNCTION( Critter_IsEvent ), asCALL_CDECL ) < 0 )
        Log( "Error reg void Critter_IsEvent\n" );
    if( ASEngine->RegisterGlobalFunction( "bool IsEvent( ::Item&inout item, int event )", asFUNCTION( Item_IsEvent ), asCALL_CDECL ) < 0 )
        Log( "Error reg void Item_IsEvent\n" );
	
    if( ASEngine->RegisterObjectMethod( "::Critter", "void set_ScriptDescriptor( Mk2::Descriptor@ value )", asFUNCTION( Critter_SetScriptDescriptor ), asCALL_CDECL_OBJFIRST ) < 0 )
        Log( "Error registering Critter::set_ScriptDescriptor()\n" );
    if( ASEngine->RegisterObjectMethod( "::Critter", "Mk2::Descriptor@ get_ScriptDescriptor()", asFUNCTION( Critter_GetScriptDescriptor ), asCALL_CDECL_OBJFIRST ) < 0 )
        Log( "Error registering Critter::get_ScriptDescriptor()\n" );
	
	
    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool CritterInit(::Critter& crInit, bool firstTime)" );
    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool CritterFinish(::Critter& crFinish, bool toDelete)" );
    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool CritterDead(::Critter@ critter, ::Critter@ killer)" );
    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool CritterRespawn(::Critter& critter)" );
	
    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool CritterIdle(::Critter& npc)" );
    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool CritterAttacked( ::Critter& critter, ::Critter& attacker )" );
    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool CritterAttack( ::Critter@ critter, ::Critter@ target, ::ProtoItem@ weapon, uint8 weaponMode, ::ProtoItem@ ammo )" );

    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool CritterShow( ::Critter& critter, ::Critter& opponent )" );
    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool CritterShowMe( ::Critter& critter, ::Critter& opponent )" );

    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool CritterHide( ::Critter& critter, ::Critter& opponent )" );
    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool CritterHideMe( ::Critter& critter, ::Critter& opponent )" );

    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool Message( ::Critter& critter, Mk2::MessagePacket@ message )" );
	
    ASEngine->RegisterInterfaceMethod( "CritterPacket", "bool Stealing( ::Critter@ cr, ::Critter@ thief, bool& success, ::Item@ item, uint count )" );

    ASEngine->RegisterInterfaceMethod( "MessagePacket", "::Critter@ get_Sender( )" );
	
    ASEngine->RegisterInterfaceMethod( "CombatTargetPacket", "bool FormatDamage( Mk2::CombatProccessPacket@ combatData, int& damage, int& typeDamage, bool& isCrit, uint& damageMulForCriticals, uint& countBullet )" );
    ASEngine->RegisterInterfaceMethod( "CombatTargetPacket", "void TakeDamage(  Mk2::CombatProccessPacket@ combatData, int reason, int& totalDamage )" );
	
    ASEngine->RegisterInterfaceMethod( "NpcPacket", "bool NpcPlaneEnd(::Critter& npc, ::NpcPlane& plane, int reason, ::Critter@ someCr, ::Item@ someItem)" );
    ASEngine->RegisterInterfaceMethod( "NpcPacket", "bool NpcPlaneBegin(::Critter& npc, ::NpcPlane& plane, int reason, ::Critter@ someCr, ::Item@ someItem)" );
    ASEngine->RegisterInterfaceMethod( "NpcPacket", "bool NpcPlaneRun(::Critter& npc, ::NpcPlane& plane, int reason, uint& r0, uint& r1, uint& r2)" );
	
    ASEngine->RegisterInterfaceMethod( "UpgradedItemPacket", "bool SetUpgrade( ::Item@ item )" );
    ASEngine->RegisterInterfaceMethod( "UpgradedItemPacket", "bool UpgradedTriggered( const uint8 trigger )" );
	
    ASEngine->SetDefaultNamespace( defName );
	
#endif
#ifdef __CLIENT
    if( ASEngine->RegisterGlobalFunction( "CritterCl@+ SetCritterHex( CritterCl@+ cr, uint16 hexX, uint16 hexY )", asFUNCTION( SetCritterHex ), asCALL_CDECL ) < 0 )
        Log( "Error reg CritterCl@ SetCritterHex\n" );
    if( ASEngine->RegisterGlobalFunction( "void SetRainSpeed( int16 x, int16 y)", asFUNCTION( SetRainSpeed ), asCALL_CDECL ) < 0 )
        Log( "Error reg void SetRainSpeed\n" );

    if( ASEngine->RegisterObjectProperty( "CritterCl", "CritterCl@ LastHexCritter", offsetof( CritterCl, Params[ ST_LAST_CRITTER_HEX ] ) ) < 0 )
        Log( "Error reg Critter@ Critter::LastHexCritter\n" );
    if( ASEngine->RegisterObjectProperty( "CritterCl", "bool CityRole_IsNotHelper", offsetof( CritterCl, Params[ CITY_ROLE_ENGINE_0 ] ) + sizeof( bool ) * 3 ) < 0 )
        Log( "Error reg bool Critter::IsFarmGenerated\n" );
    if( ASEngine->RegisterObjectProperty( "CritterCl", "bool CityRole_IsGuard", offsetof( CritterCl, Params[ CITY_ROLE_ENGINE_0 ] ) ) < 0 )
        Log( "Error reg bool Critter::IsFarmGenerated\n" );
    if( ASEngine->RegisterObjectProperty( "CritterCl", "bool CityRole_IsPatrol", offsetof( CritterCl, Params[ CITY_ROLE_ENGINE_0 ] ) + sizeof( bool ) ) < 0 )
        Log( "Error reg bool Critter::IsFarmGenerated\n" );
    if( ASEngine->RegisterObjectProperty( "CritterCl", "bool CityRole_IsProtected", offsetof( CritterCl, Params[ CITY_ROLE_ENGINE_0 ] ) + sizeof( bool ) * 2 ) < 0 )
        Log( "Error reg bool Critter::IsFarmGenerated\n" );
    if( ASEngine->RegisterObjectMethod( "CritterCl", "string@ get_Name()", asFUNCTION( GetCustomName ), asCALL_CDECL_OBJFIRST ) < 0 )
        Log( "Error registering Critter::GetCustomName()\n" );

    if( ASEngine->RegisterObjectProperty( "ItemCl", "int16 CurrentHp", offsetof( Item, Data.Deterioration ) ) < 0 )
        Log( "Error reg int16 ItemCl::CurrentHp\n" );
    if( ASEngine->RegisterObjectProperty( "ItemCl", "int16 CraftFlags", offsetof( Item, Data.CraftFlags ) ) < 0 )
        Log( "Error reg int16 ItemCl::CraftFlags\n" );
    if( ASEngine->RegisterGlobalFunction( "int MsgBox(string&, string&, uint)", asFUNCTION( MsgBox ), asCALL_CDECL ) < 0 )
        Log( "Unable to register MsgBox function\n" );

    RegistrationItemBlockLinesClass();
#endif

    if( ASEngine->RegisterObjectMethod( "ProtoItem", "int GetType()", asMETHOD( ProtoItem, GetType ), asCALL_THISCALL ) < 0 )
        Log( "Error registering ProtoItem::GetType()\n" );
#ifdef __MAPPER
    if( ASEngine->RegisterObjectProperty( "MapperObject", "uint Id", offsetof( MapObject, UID ) ) < 0 )
        Log( "Error reg uint MapperObject::Id\n" );
    if( ASEngine->RegisterObjectMethod( "MapperObject", "uint16 GetProtoId()", asMETHOD( MapObject, GetProtoId ), asCALL_THISCALL ) < 0 )
        Log( "Error registering MapperObject::GetProtoId()\n" );
    if( ASEngine->RegisterObjectProperty( "MapperObject", "uint Reserved", offsetof( MapObject, Reserved[0] ) ) < 0 )
        Log( "Error reg uint MapperObject::Reserved\n" );
    if( ASEngine->RegisterObjectProperty( "MapperObject", "int UserData", offsetof( MapObject, UserData[0] ) ) < 0 )
        Log( "Error reg uint MapperObject::UserData\n" );
#endif

    if( isCompiler )
        return;

    // Register callbacks
    FOnline->GetUseApCost = &GetUseApCost;
    FOnline->GetAttackDistantion = &GetAttackDistantion;
	
#ifndef __CLIENT
	float fTimeStart = clock()/(float)CLOCKS_PER_SEC;
    AutoScript();
	float fTimeStop = clock()/(float)CLOCKS_PER_SEC; 
	Log("Module Mk2 build %f seconds\n", fTimeStop-fTimeStart); 
#endif
}

void RegisterGlobalVars( )
{
	// Register script global vars
    memset( &GlobalVars, 0, sizeof( GlobalVars ) );
    for( uint i = 0; i < ASEngine->GetGlobalPropertyCount(); i++ ) 
    {
        const char* name;
        void*       ptr;
        if( ASEngine->GetGlobalPropertyByIndex( i, &name, NULL, NULL, NULL, NULL, &ptr ) < 0 )
            continue;		
		// Ну и хули, переменные начинаются с подчеркиваний, вся структура не валидна, дампает к херам, не говоря о том что CurX\Y вообще отсутствует - Cracker
        #define REGISTER_GLOBAL_VAR( type, gvar )    else if( !strcmp( # gvar, name ) ) \
			GlobalVars.gvar = (type*) ptr
        REGISTER_GLOBAL_VAR( bool, __NewbieLocationIsActive );
        REGISTER_GLOBAL_VAR( uint, __HitAimEyes );
        REGISTER_GLOBAL_VAR( uint, __HitAimHead );
        REGISTER_GLOBAL_VAR( uint, __HitAimGroin );
        REGISTER_GLOBAL_VAR( uint, __HitAimTorso );
        REGISTER_GLOBAL_VAR( uint, __HitAimArms );
        REGISTER_GLOBAL_VAR( uint, __HitAimLegs );
        REGISTER_GLOBAL_VAR( uint, __MaxLifeLevelSoftCap );
        REGISTER_GLOBAL_VAR( uint, __EncounterTime );
        REGISTER_GLOBAL_VAR( uint, __ExperienceRate );
#ifdef __CLIENT
        REGISTER_GLOBAL_VAR( bool, __AutoAim );
        REGISTER_GLOBAL_VAR( bool, __GrenadeMode );
#endif
#ifdef __SERVER
		REGISTER_GLOBAL_VAR( uint16, __StartServerVersion );
#endif
    }
}

ScriptString* 	Global_GetFunctionName( asIScriptFunction* function )
{
	if( function )
		return &ScriptString::Create( function->GetName( ) );
		
	return &ScriptString::Create( "null" );
}

ScriptString* 	Global_GetFunctionDeclaration( asIScriptFunction* function, bool includeObjectName, bool includeNamespace )
{
	if( function )
		return &ScriptString::Create( function->GetDeclaration( includeObjectName, includeNamespace ) );
		
	return &ScriptString::Create( "null" );
}
	
#ifdef __SERVER

ScriptString* Item_GetLexems( Item& item )
{
	if( item.Lexems )
		return &ScriptString::Create( item.Lexems );
	return &ScriptString::Create( "" );
}

uint Critter_GetGlobalGroupCarId( Critter& cr )
{
    const GlobalMapGroup* groupMove = cr.GroupMove;
    if( groupMove )
        return groupMove->CarId;
    return 0;
}

uint Critter_GetGlobalGroupProcessLastTick( Critter& cr )
{
    const GlobalMapGroup* groupMove = cr.GroupMove;
    if( groupMove )
        return groupMove->ProcessLastTick;
    return 0;
}

uint Critter_GetGlobalGroupTimeCanFollow( Critter& cr )
{
    const GlobalMapGroup* groupMove = cr.GroupMove;
    if( groupMove )
        return groupMove->TimeCanFollow;
    return 0;
}

uint GetFarmEntire( Map& map, CScriptArray& outArr, uint pid, uint id )
{
    uint count = 0;
    for( MapObjectVecIt it = map.Proto->SceneriesVec.begin(), end = map.Proto->SceneriesVec.end(); it != end; ++it )
    {
        MapObject* grid = *it;
        if( grid )
        {
            if( grid->ProtoId == pid )
            {
                if( id == grid->MScenery.Param[ 0 ] )
                {
                    count++;
                    int HexX = grid->MapX;
                    int HexY = grid->MapY;
                    outArr.InsertLast( &HexX );
                    outArr.InsertLast( &HexY );
                    if( SPAWN_ENTIRE_PID_MOB == pid )
                    {
                        int Radius = grid->MScenery.Param[ 1 ];
                        if( Radius == 0 )
                            Radius = 5;
                        int Clear = 0;
                        outArr.InsertLast( &Radius );
                        outArr.InsertLast( &Clear );
                    }
                    else if( SPAWN_ENTIRE_PID_CONT == pid )
                    {
                        int OffsetX = grid->MScenery.OffsetX;
                        int OffsetY = grid->MScenery.OffsetY;

                        outArr.InsertLast( &OffsetX );
                        outArr.InsertLast( &OffsetY );
                    }
                }
            }
        }
    }
    return count;
}

/************************************************************************/
/* Slot/parameters allowing                                             */
/************************************************************************/

bool allowSlot_Hand1( uint8, Item&, Critter&, Critter& toCr )
{
    return toCr.Params[ PE_AWARENESS ] != 0;
}
#endif

/************************************************************************/
/* Extended methods                                                     */
/************************************************************************/

bool Critter_IsInjured( CritterMutual& cr )
{
    return Critter_IsDmgArm( cr ) || Critter_IsDmgLeg( cr ) || Critter_IsDmgEye( cr );
}

bool Critter_IsDmgEye( CritterMutual& cr )
{
    return cr.Params[ DAMAGE_EYE ] != 0;
}

bool Critter_IsDmgLeg( CritterMutual& cr )
{
    return cr.Params[ DAMAGE_RIGHT_LEG ] || cr.Params[ DAMAGE_LEFT_LEG ];
}

bool Critter_IsDmgTwoLeg( CritterMutual& cr )
{
    return cr.Params[ DAMAGE_RIGHT_LEG ] && cr.Params[ DAMAGE_LEFT_LEG ];
}

bool Critter_IsDmgArm( CritterMutual& cr )
{
    return cr.Params[ DAMAGE_RIGHT_ARM ] || cr.Params[ DAMAGE_LEFT_ARM ];
}

bool Critter_IsDmgTwoArm( CritterMutual& cr )
{
    return cr.Params[ DAMAGE_RIGHT_ARM ] && cr.Params[ DAMAGE_LEFT_ARM ];
}

bool Critter_IsAddicted( CritterMutual& cr )
{
    for( uint i = ADDICTION_BEGIN; i <= ADDICTION_END; i++ )
        if( cr.Params[ i ] )
            return true;
    return false;
}

bool Critter_IsOverweight( CritterMutual& cr )
{
    // Calculate inventory items weight
    uint w = 0;
    for( ItemVecIt it = cr.InvItems.begin(), end = cr.InvItems.end(); it != end; ++it )
    {
        Item* item = *it;
        if( item && !item->IsNotValid )
            w += item->GetWeight();
    }

    return w > (uint) getParam_MaxWeight( cr, 0 );
}

bool Item_Weapon_IsHtHAttack( Item& item, uint8 mode )
{
    if( !item.IsWeapon() || !item.WeapIsUseAviable( mode & 7 ) )
        return false;
    int skill = SKILL_OFFSET( item.Proto->Weapon_Skill[ mode & 7 ] );
    return skill == SK_UNARMED;
}

bool Item_Weapon_IsGunAttack( Item& item, uint8 mode )
{
    if( !item.IsWeapon() || !item.WeapIsUseAviable( mode & 7 ) )
        return false;
    int skill = SKILL_OFFSET( item.Proto->Weapon_Skill[ mode & 7 ] );
    return skill == SK_SMALL_GUNS || skill == SK_BIG_GUNS || skill == SK_ENERGY_WEAPONS;
}

bool Item_Weapon_IsRangedAttack( Item& item, uint8 mode )
{
    if( !item.IsWeapon() || !item.WeapIsUseAviable( mode & 7 ) )
        return false;
    int skill = SKILL_OFFSET( item.Proto->Weapon_Skill[ mode & 7 ] );
    return skill == SK_DOCTOR || skill == SK_SMALL_GUNS || skill == SK_BIG_GUNS || skill == SK_ENERGY_WEAPONS || skill == SK_THROWING;
}

/************************************************************************/
/* Callbacks                                                            */
/************************************************************************/

uint GetUseApCost( CritterMutual& cr, Item& item, uint8 mode )
{
    uint8 use = mode & 0xF;
    uint8 aim = mode >> 4;
    int   apCost = 0;

    if( use == USE_USE )
    {
        apCost = FOnline->RtApCostUseItem;
        if( cr.Params[ PE_QUICK_POCKETS ] )
            apCost -= ceil( (double) apCost / 3 );
    }

    else if( use == USE_RELOAD )
    {
        if( item.IsWeapon() )
            apCost = item.Proto->Weapon_ReloadAp;
        if( item.IsWeapon() && item.Proto->Weapon_Perk == WEAPON_PERK_FAST_RELOAD && apCost > 0 )
            apCost--;
        if( cr.Params[ PE_QUICK_POCKETS ] )
            apCost -= ceil( (double) apCost / 3 );
    }

    else if( use >= USE_PRIMARY && use <= USE_THIRD && item.IsWeapon() )
    {
        int  skill = item.Proto->Weapon_Skill[ use ];
        bool hthAttack = Item_Weapon_IsHtHAttack( item, mode );
        bool rangedAttack = Item_Weapon_IsRangedAttack( item, mode );
        bool isGun = Item_Weapon_IsGunAttack( item, mode );
        apCost = item.Proto->Weapon_ApCost[ use ];
        #ifdef __SERVER
        if( aim )
            apCost += GetAimApCost( aim );
        #endif
        #ifdef __CLIENT
        if( item.Proto->Weapon_Aim[ use ] && *GlobalVars.__AutoAim )
            apCost++;
        #endif
        if( hthAttack && cr.Params[ PE_BONUS_HTH_ATTACKS ] )
            apCost--;
        if( rangedAttack && cr.Params[ PE_BONUS_RATE_OF_FIRE ] )
            apCost--;
        if( cr.Params[ TRAIT_FAST_SHOT ] && isGun )
            apCost--;
        apCost -= item.Data.WeaponBonus_AP;

        if( aim && apCost < 3 )
            apCost = 3;
        else if( apCost < 2 )
            apCost = 2;
    }

    if( apCost < 1 )
        apCost = 1;

    return apCost;
}

uint GetAttackDistantion( CritterMutual& cr, Item& slot1Item, uint8 mode )
{
    Item* item = &slot1Item;
    #ifdef __CLIENT
    if( *GlobalVars.__GrenadeMode )
    {
        item = const_cast< Item* >( cr.ItemSlotArmor );
        mode = 0;
    }
    #endif
    uint8 use = mode & 0xF;
    int   dist = item->Proto->Weapon_MaxDist[ use ];
    int   strength = getParam_Strength( cr, 0 );
    if( item->Proto->Weapon_Skill[ use ] == SKILL_OFFSET( SK_THROWING ) )
        dist = min( dist, 3 * min( 10, strength + 2 * cr.Params[ PE_HEAVE_HO ] ) );
    if( Item_Weapon_IsHtHAttack( *item, mode ) && cr.Params[ MODE_RANGE_HTH ] )
        dist++;
    dist += GetMultihex( cr );
    if( dist < 0 )
        dist = 0;
    return dist;
}

void GetRainOffset( int16* ox, int16* oy )
{
    *ox = FOnline->Random( -10, 10 );
    *oy = -100 - FOnline->Random( 0, 100 );
}

/************************************************************************/
/* Generic stuff                                                        */
/************************************************************************/

uint GetAimApCost( int hitLocation )
{
    switch( hitLocation )
    {
    case HIT_LOCATION_TORSO:
        return FOnline->ApCostAimTorso;
    case HIT_LOCATION_EYES:
        return FOnline->ApCostAimEyes;
    case HIT_LOCATION_HEAD:
        return FOnline->ApCostAimHead;
    case HIT_LOCATION_LEFT_ARM:
    case HIT_LOCATION_RIGHT_ARM:
        return FOnline->ApCostAimArms;
    case HIT_LOCATION_GROIN:
        return FOnline->ApCostAimGroin;
    case HIT_LOCATION_RIGHT_LEG:
    case HIT_LOCATION_LEFT_LEG:
        return FOnline->ApCostAimLegs;
    case HIT_LOCATION_NONE:
    case HIT_LOCATION_UNCALLED:
    default:
        break;
    }
    return 0;
}

uint GetAimHit( int hitLocation )
{
    switch( hitLocation )
    {
    case HIT_LOCATION_TORSO:
        return *GlobalVars.__HitAimTorso;
    case HIT_LOCATION_EYES:
        return *GlobalVars.__HitAimEyes;
    case HIT_LOCATION_HEAD:
        return *GlobalVars.__HitAimHead;
    case HIT_LOCATION_LEFT_ARM:
    case HIT_LOCATION_RIGHT_ARM:
        return *GlobalVars.__HitAimArms;
    case HIT_LOCATION_GROIN:
        return *GlobalVars.__HitAimGroin;
    case HIT_LOCATION_RIGHT_LEG:
    case HIT_LOCATION_LEFT_LEG:
        return *GlobalVars.__HitAimLegs;
    case HIT_LOCATION_NONE:
    case HIT_LOCATION_UNCALLED:
    default:
        break;
    }
    return 0;
}

uint GetMultihex( CritterMutual& cr )
{
    int mh = cr.Multihex;
    if( mh < 0 )
        mh = FOnline->CritterTypes[ cr.BaseType ].Multihex;
    return CLAMP( mh, 0, MAX_HEX_OFFSET );
}

bool FileDelete( ScriptString& filename )
{
    if( DeleteFile( filename.c_str() ) )
        return true;
    return false;
}

bool FileRename( ScriptString& filename, ScriptString& newName )
{
    if( MoveFile( filename.c_str(), newName.c_str() ) )
        return true;
    return false;
}


asIScriptObject* Item_GetScriptDescriptor( Item& item )
{		
#ifdef __SERVER
	if( *GlobalVars.__StartServerVersion != item.InitVersion )
#else
	if( item.InitVersion == 0 )
#endif
	{		
		item.ScriptDescriptor = NULL;
#ifdef __SERVER
		item.InitVersion = *GlobalVars.__StartServerVersion;
		uint funcId_defDescript = FOnline->ScriptBind( "Mk2", "Mk2::Descriptor@+ item_default_descriptor( ::Item& item )", false );
#else
		item.InitVersion = 1;
		uint funcId_defDescript = FOnline->ScriptBind( "Mk2", "Mk2::Descriptor@+ item_default_descriptor( ::ItemCl& item )", false );
#endif
        if( funcId_defDescript && FOnline->ScriptPrepare( funcId_defDescript ) )
        {
            FOnline->ScriptSetArgObject( &item );
            FOnline->ScriptRunPrepared();
				
			item.ScriptDescriptor = (asIScriptObject*)FOnline->ScriptGetReturnedAddress();
			if(item.ScriptDescriptor)
				item.ScriptDescriptor->AddRef();
        }
	}
	
	if(item.ScriptDescriptor)
	{
		item.ScriptDescriptor->AddRef();
		return item.ScriptDescriptor;
	}
    return NULL;
}

void Item_SetScriptDescriptor(  Item& item, asIScriptObject* value )
{
#ifdef __SERVER
	if( *GlobalVars.__StartServerVersion != item.InitVersion )
#else
	if( item.InitVersion == 0 )
#endif
	{
		item.ScriptDescriptor = NULL;
#ifdef __SERVER
		item.InitVersion = *GlobalVars.__StartServerVersion;
#else
		item.InitVersion = 1;
#endif
	}
	
	if(item.ScriptDescriptor)
	{
		item.ScriptDescriptor->Release();
	}
	
	item.ScriptDescriptor = value;
}

#ifdef __SERVER

asIScriptObject* Critter_GetScriptDescriptor( Critter& cr )
{		
	if( *GlobalVars.__StartServerVersion != cr.InitVersion )
	{
		cr.ScriptDescriptor = NULL;
		cr.InitVersion = *GlobalVars.__StartServerVersion;
	}
	
	if(cr.ScriptDescriptor)
	{
		__try
		{
			cr.ScriptDescriptor->AddRef();
		}
		__except( EXCEPTION_EXECUTE_HANDLER )
        {
            cr.ScriptDescriptor = NULL;
			cr.InitVersion = *GlobalVars.__StartServerVersion;
			Log( "Exception<Critter_GetScriptDescriptor> :: ScriptDescriptor is not valid.\n" );
			return NULL;
        }
		return cr.ScriptDescriptor;
	}
    return NULL;
}

void Critter_SetScriptDescriptor(  Critter& cr, asIScriptObject* value )
{
	if( *GlobalVars.__StartServerVersion != cr.InitVersion )
	{
		cr.ScriptDescriptor = NULL;
		cr.InitVersion = *GlobalVars.__StartServerVersion;
	}
	
	if(cr.ScriptDescriptor)
	{
		__try
		{
			cr.ScriptDescriptor->Release();
		}
		__except( EXCEPTION_EXECUTE_HANDLER )
        {
            cr.ScriptDescriptor = NULL;
			cr.InitVersion = *GlobalVars.__StartServerVersion;
			Log( "Exception<Critter_SetScriptDescriptor> :: ScriptDescriptor is not valid.\n" );
        }
	}
	
	cr.ScriptDescriptor = value;
}

uint Critter_GetLanguage( Critter& cr )
{
    return ( (Client*) &cr )->LanguageMsg;
}

uint SearchDeleteItem( CScriptArray& inItems, CScriptArray& outItems, uint cost )
{
    for( uint i = 0, iEnd = inItems.GetSize(); i < iEnd; i++ )
    {
        Item& it = *( *(Item**) inItems.At( i ) );
        if( it.GetCost() / ( it.GetCount() == 0 ? 1 : it.GetCount() )  > cost )
            continue;
        if( !it.IsNotValid )
        {
            {
                switch( it.GetType() )
                {
                case ITEM_TYPE_NONE:
                    break;
                case ITEM_TYPE_ARMOR:
                case ITEM_TYPE_DRUG:
                case ITEM_TYPE_WEAPON:
                case ITEM_TYPE_AMMO:
                case ITEM_TYPE_MISC:
                    outItems.InsertLast( inItems.At( i ) );
                    break;
                case ITEM_TYPE_KEY:
                case ITEM_TYPE_CONTAINER:
                case ITEM_TYPE_DOOR:
                case ITEM_TYPE_GRID:
                case ITEM_TYPE_GENERIC:
                case ITEM_TYPE_WALL:
                case ITEM_TYPE_CAR:
                default:
                    break;
                }
            }
        }
    }
    return outItems.GetSize();
}

int getParamDialog_Intellect( Critter& master, Critter& slave, uint index )
{
    if( !master.IsNotValid )
        return ( getParam_Intellegence( master, ST_INTELLECT ) + 2 * master.Params[ PE_SMOOTH_TALKER ] );
    return 0;
}

int getParamDialog_Reputation( Critter& master, Critter& slave, uint index )
{
    if( !master.IsNotValid )
    {
        if( master.Params[ index ] == int(0x80000000) )
        {
            FOnline->CritterChangeParameter( master, index );
            const_cast< int* >( master.Params )[ index ] = 0;
        }
        return master.Params[ index ];
    }
    return 0;
}

void Map_GetExitGrid( Map& map, Critter& cr, uint16& x, uint16& y, uint16& MapPid, uint& EntireId )
{
    for( MapObjectVecIt it = map.Proto->GridsVec.begin(), end = map.Proto->GridsVec.end(); it != end; ++it )
    {
        MapObject* grid = *it;
        if( x == 0 && y == 0 )
        {
            MapPid = grid->MScenery.ToMapPid;
            EntireId = grid->MScenery.ToEntire;
            x = grid->MapX;
            y = grid->MapY;
        }
        else if( GetDistantion( x, y, cr.HexX, cr.HexY ) > GetDistantion( grid->MapX, grid->MapY, cr.HexX, cr.HexY ) )
        {
            MapPid = grid->MScenery.ToMapPid;
            EntireId = grid->MScenery.ToEntire;
            x = grid->MapX;
            y = grid->MapY;
        }
    }
}

void Map_GetExitGlobalGrid( Map& map, Critter& cr, uint16& x, uint16& y )
{
    for( MapObjectVecIt it = map.Proto->GridsVec.begin(), end = map.Proto->GridsVec.end(); it != end; ++it )
    {
        MapObject* grid = *it;
        if( grid->ProtoId == 2049 )
        {
            if( grid->MScenery.ToMapPid == 0 && grid->MScenery.ToEntire == 0 )
            {
                if( x == 0 && y == 0 )
                {
                    x = grid->MapX;
                    y = grid->MapY;
                }
                else if( GetDistantion( x, y, cr.HexX, cr.HexY ) > GetDistantion( grid->MapX, grid->MapY, cr.HexX, cr.HexY ) )
                {
                    x = grid->MapX;
                    y = grid->MapY;
                }
            }
        }
    }
}

void ChangeParam( Critter& cr, uint index, int value )
{
    FOnline->CritterChangeParameter( cr, index );
    const_cast< int* >( cr.Params )[ index ] = value;
}


int _CheckVisor( uint parameter, Critter& fromCr, Critter& toCr )
{
    if( fromCr.Id == toCr.Id )
        return fromCr.Params[ parameter ];
    return 0;
}

int _CheckAwareness( uint parameter, Critter& fromCr, Critter& toCr )
{
    if( toCr.Params[ PE_AWARENESS ] != 0 )
    {
        return fromCr.Params[ parameter ];
    }
    return MAX( 0, getParam_Hp( fromCr, 0 ) ) * 100 / MAX( 1, getParam_MaxLife( fromCr, 0 ) );
}

int Critter_AddScoreMK2( Critter& cr, uint scoreIndex, int value )
{
    if( scoreIndex >= SCORES_MAX )
    {
        Log( "Обращение к несуществующему score, index %u.\n", scoreIndex );
        return 0;
    }
    const_cast< int* >( cr.Scores )[ scoreIndex ] += value;
    return cr.Scores[ scoreIndex ];
}

void Critter_RefreshSpeed( Critter& cr )
{
    if( FOnline->RunOnCombat )
    {
        if( cr.Params[ PE_BONUS_MOVE ] == 0 && cr.Timeout( TO_BATTLE ) != 0 )
            ChangeParam( cr, MODE_NO_RUN, 1 );            // Отменяем бег во время боя.
        else
            ChangeParam( cr, MODE_NO_RUN, 0 );
    }

    if( !cr.CritterIsNpc && ( (Client*) &cr )->Access != ACCESS_ADMIN )
    {
        ChangeParam( cr, ST_WALK_TIME, 400 - cr.Params[ ST_BONUS_WALK_TIME ] );
        ChangeParam( cr, ST_RUN_TIME, 200 - cr.Params[ ST_BONUS_RUN_TIME ] );
        if( cr.Params[ ST_WALK_TIME ] < 268 )
            ChangeParam( cr, ST_WALK_TIME, 268 );
        if( cr.Params[ ST_RUN_TIME ] < 134 )
            ChangeParam( cr, ST_RUN_TIME, 134 );

        if( getParam_Lionhead( cr, SK_LIONHEART ) > 105 )
        {
            if( cr.Timeout( TO_BATTLE ) != 0 && cr.Params[ PE_COMBAT_EVASION ] == 0 )
                return;
            int percent = ( getParam_Lionhead( cr, SK_LIONHEART ) - 100 ) / 6;

            ChangeParam( cr, ST_WALK_TIME, 400 - ( 4 * percent ) - cr.Params[ ST_BONUS_WALK_TIME ] );
            ChangeParam( cr, ST_RUN_TIME, 200 - ( 2 * percent ) - cr.Params[ ST_BONUS_RUN_TIME ] );
            if( cr.Params[ ST_WALK_TIME ] < 268 )
                ChangeParam( cr, ST_WALK_TIME, 268 );
            if( cr.Params[ ST_RUN_TIME ] < 134 )
                ChangeParam( cr, ST_RUN_TIME, 134 );

        }

        if( cr.Params[ ST_WALK_TIME ] > 600 )
            ChangeParam( cr, ST_WALK_TIME, 600 );
        if( cr.Params[ ST_RUN_TIME ] > 300 )
            ChangeParam( cr, ST_RUN_TIME, 300 );
    }
}

int MakeBackup( ScriptString* parameters )
{
    return (int) ShellExecute( NULL, NULL, "7za.exe", (LPCTSTR) parameters->c_str(), NULL, 3 );
}

bool _check_trap_look( Map& map, Critter& cr, Item& trap )
{
    if( !cr.CritterIsNpc && ( (Client*) &cr )->Access == ACCESS_ADMIN )
        return true;

    int dist = GetDistantion( cr.HexX, cr.HexY, trap.AccHex.HexX, trap.AccHex.HexY );
    if( dist >= 80 )
        return false;
    if( dist == 0 )
        return true;

    int perc = getParam_Perception( cr, 0 );
    int visibleDist = getParam_VisibleDist( cr, 0 );
	
    if( visibleDist >= dist )
    {
        if( trap.Data.ScriptValues[ 2 ] == cr.Id )
            return true;
        int skill = getParam_Skill( cr, SK_TRAPS );
        int trapSkill = trap.Data.ScriptValues[ 3 ] + trap.Data.ScriptValues[ 3 ] / 2;
        if( skill > trapSkill + 20 )
            return true;
        if( perc * 5 + skill >= trapSkill )
        {
            visibleDist = ( perc * 5 + skill - trapSkill ) / 10;
            if( visibleDist >= dist )
                return true;
        }
    }

    return false;
}

bool check_trap_look( Map& map, Critter& cr, Item& trap )
{
    bool isShow = cr.VisItem.find( trap.Id ) != cr.VisItem.end();

    if( _check_trap_look( map, cr, trap ) != isShow )
    {
        if( isShow )
        {
            uint funcId_hide = FOnline->ScriptBind( "Mk2", "void hide_trap(::Critter& cr, ::Item& item )", true );
            if( funcId_hide && FOnline->ScriptPrepare( funcId_hide ) )
            {
                FOnline->ScriptSetArgObject( &cr );
                FOnline->ScriptSetArgObject( &trap );
                FOnline->ScriptRunPrepared();
				
				isShow = !FOnline->ScriptGetReturnedBool();
            }
        }
        else
        {
            uint funcId_show = FOnline->ScriptBind( "Mk2", "void show_trap(::Critter& cr, ::Item& item )", true );
            if( funcId_show && FOnline->ScriptPrepare( funcId_show ) )
            {
                FOnline->ScriptSetArgObject( &cr );
                FOnline->ScriptSetArgObject( &trap );
                FOnline->ScriptRunPrepared();
				
				isShow = !FOnline->ScriptGetReturnedBool();
            }
        }
        return !isShow;
    }
    return isShow;
}

int getParam_CountMerc( Critter& cr, uint )
{
    return cr.CountMerc;
}

#endif

int getParam_VisibleDist( CritterMutual& cr, uint )
{
    uint16 hour = 0;
    if( cr.Params[ ST_CURRENT_MAP_TIME ] < 1 )
        hour = FOnline->Hour;
    else
        hour = (uint16) cr.Params[ ST_CURRENT_MAP_TIME ] / 60;

    float Z;
    if( cr.Params[ PE_NIGHT_VISION ] == 0 )
        if( hour >= 9 && hour < 17 )
            Z = (float) 1.2;
        else if( hour >= 21 || hour < 5 )
            Z = (float) 0.8;
        else if( hour < 10 )
            Z = (float) ( 0.9 + ( ( hour - 4.0 ) / 20.0 ) );
        else
            Z = (float) ( 1.2 - ( hour - 16.0 ) / 10.0 );
    else if( hour >= 9 && hour < 17 )
        Z = (float) 1.2;
    else if( hour >= 21 || hour < 5 )
        Z = (float) 1.0;
    else if( hour < 10 )
        Z = (float) ( 1.0 + ( ( hour - 4.0 ) / 20.0 ) );
    else
        Z = (float) ( 1.2 - ( hour - 16.0 ) / 20.0 );

	int val = ( 20 + ( getParam_Perception( cr, 0 ) + cr.Params[ PE_SHARPSHOOTER ] * 2 ) * 3 ) * Z;
    val = CLAMP( val, 1, 70 );
    return val;
}

// //////////////////////////////////////////////////////////////////////////////////////////////////
// Called on something item in/changed/out map.

#ifdef __CLIENT
inline void MoveHexByDir( uint16& hx, uint16& hy, uint8 dir )
{
    switch( dir )
    {
    case 0:
    {
		if( hx > 1 )
			hx -= 1;
        if( hx % 2 == 0 && hy > 1 )
            hy -= 1;
    } break;

    case 1:
    {
		if( hx > 1 )
			hx -= 1;
        if( hx % 2 == 1 && FOnline->ClientMapHeight - 1 > hy )
            hy += 1;
    } break;

    case 2:
    {
		if( FOnline->ClientMapWidth - 1 > hy )
			hy += 1;
    } break;

    case 3:
    {
		if( FOnline->ClientMapWidth - 1 > hx )
			hx += 1;
        if( hx % 2 == 1 && FOnline->ClientMapHeight - 1 > hy )
            hy += 1;
    } break;

    case 4:
    {
		if( FOnline->ClientMapWidth - 1 > hx )
			hx += 1;
        if( hx % 2 == 0 && 1 < hy )
            hy -= 1;
    } break;

    case 5:
    {
		if( hy > 1 )
			hy -= 1;
    } break;

    default:
        break;
    }
}

#define ONLINE_CHECKER_OFFLAIN	4000000000

uint Online = ONLINE_CHECKER_OFFLAIN;
uint Uptame = 0;
bool ActiveChecker = false;
HANDLE LockThread = nullptr;

bool CheckActive( )
{
	WaitForSingleObject( LockThread, INFINITE );
	bool active = ActiveChecker;
	ReleaseMutex( LockThread );
	return active;
}

void CheckOnlineThread( void* )
{
	WaitForSingleObject( LockThread, INFINITE );
	Online = ONLINE_CHECKER_OFFLAIN;
	Uptame = 0;
	ReleaseMutex( LockThread );
	
	WSADATA wsaData;
	if( WSAStartup(MAKEWORD(1, 1), &wsaData) == 0 )
	{
		int result = 0;
		while( CheckActive( ) )
		{
			
			sockaddr_in serv_addr;
			serv_addr.sin_family=AF_INET;
			serv_addr.sin_port=htons(FOnline->Port);	
			if((serv_addr.sin_addr.s_addr=inet_addr(FOnline->Host.c_str()))==-1)
			{
				hostent* h=gethostbyname(FOnline->Host.c_str());
				memcpy(&serv_addr.sin_addr,h->h_addr,sizeof(in_addr));
			}
			
			SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if( connect( sock, (struct sockaddr *)&serv_addr, sizeof( serv_addr ) ) == 0 )
			{
			
				char sendPacket[4]={(char)255,(char)255,(char)255,(char)255};
				char recvPacket[16];
				
				send(sock, sendPacket, 4, 0);
				recv(sock, recvPacket, 16,0);
				
				WaitForSingleObject( LockThread, INFINITE );
				Online = *(unsigned int*)&recvPacket[0];
				Uptame = *(unsigned int*)&recvPacket[4];
				ReleaseMutex( LockThread );
				closesocket(sock);
			}
			else
			{
				WaitForSingleObject( LockThread, INFINITE );
				Online = ONLINE_CHECKER_OFFLAIN;
				Uptame = 0;
				ReleaseMutex( LockThread );
			}
			Sleep( 100 );
		}
		WSACleanup( );
	}
	CloseHandle( LockThread );
	LockThread = nullptr;
}

int PrepareWSA( )
{
	if( LockThread )
		return -1;
		
	LockThread = CreateMutex( NULL, FALSE, NULL );
	WaitForSingleObject( LockThread, INFINITE );
	ActiveChecker = true;
	ReleaseMutex( LockThread );
	_beginthread( CheckOnlineThread, 0, NULL );
	return 0;
}

int ClearWSA( )
{
	WaitForSingleObject( LockThread, INFINITE );
	ActiveChecker = false;
	ReleaseMutex( LockThread );
	return 0;
}

void GetOnline( uint& online, uint& uptame )
{	
	WaitForSingleObject( LockThread, INFINITE );
	online = Online;
	uptame = Uptame;
	ReleaseMutex( LockThread );
}

bool out_message( ScriptString& message, int& sayType )
{
	if( message.length() == 0 )
		return false;
	const char* mess = message.c_str();
	if( mess && mess[0] == '#' || mess[0] == '~' && message.length() > 1 )
	{
		asIScriptModule* mk2 = GetModule( "Mk2" );
		if( mk2 )
		{
			char functionName[50];
			unsigned int pos = 1;
			if( CharNextWord( mess, pos, functionName, 50 ) )
			{
				ostringstream out;      		
				out << "::string " << functionName << "_MsgCommand( ::string )"; 
				if( mk2->GetFunctionByDecl( out.str().c_str() ) )
				{
					uint funcId = FOnline->ScriptBind( "Mk2", out.str().c_str(), true );
					if( funcId && FOnline->ScriptPrepare( funcId ) )
					{
						FOnline->ScriptSetArgObject( &message );
						FOnline->ScriptRunPrepared();
						ScriptString* result = (ScriptString*)FOnline->ScriptGetReturnedObject( );
						if( result )
						{
							if( result->length() != 0 )
							{
								// Message( result->c_str() );
							}
						}
						return false;
					}
				}
				out.clear();
			}
		}
	}
	
	uint funcIdOutMess = FOnline->ScriptBind( "Mk2", "bool out_message( ::string& message, int& sayType )", true );
	if( funcIdOutMess && FOnline->ScriptPrepare( funcIdOutMess ) )
	{
		FOnline->ScriptSetArgAddress( &message );
		FOnline->ScriptSetArgAddress( &sayType );
		FOnline->ScriptRunPrepared();
		return FOnline->ScriptGetReturnedBool();
	}
	return false;
}

void critter_out( CritterCl& cr )
{}

void item_map_changed( Item& itemNow, Item& itemBefore )
{
    if( itemNow.GetType() == ITEM_TYPE_DOOR || itemNow.GetType() == ITEM_TYPE_CONTAINER )
    {
        uint funcId = FOnline->ScriptBind( "client_main", "void soundItem_map_changed(ItemCl& itemNow, ItemCl& itemBefore)", true );
        if( funcId && FOnline->ScriptPrepare( funcId ) )
        {
            FOnline->ScriptSetArgObject( &itemNow );
            FOnline->ScriptSetArgObject( &itemBefore );
            FOnline->ScriptRunPrepared();
        }
    }
}

void item_map_in( Item& item )
{
    if( item.Proto )
    {
        BlockData b = { 0 };
        uint16    hx = item.AccHex.HexX;
        uint16    hy = item.AccHex.HexY;
        uint8     dir = 0, dist = 0;
        b.Block = item.Proto->BlockLines[ 0 ];
        if( b.Dist != 0 )
        {
            ItemBlockLines* lines = new ItemBlockLines();
            lines->ItemId = item.Id;

            for( uint8 j = 0; j < ITEM_MAX_BLOCK_LINES; j++ )
            {
                b.Block = item.Proto->BlockLines[ j ];
                dir = b.Dir;
                dist = b.Dist;
                if( dist == 0 )
                    break;
                lines->Data[ j ] = b;
                while( dist-- != 0 )
                {
                    MoveHexByDir( hx, hy, dir );
                    Field* field = GetField( hx, hy );
                    if( field )
                    {
                        if( !item.IsRaked() )
                            const_cast< bool& >( field->IsNotRaked ) = true;
                        if( !item.IsPassed() )
                            const_cast< bool& >( field->IsNotPassed ) = true;
                    }
                }
            }

            uint funcId = FOnline->ScriptBind( "client_main", "void BlockLinesAdd( Mk2::ItemBlockLines@+ lines )", true );
            if( funcId && FOnline->ScriptPrepare( funcId ) )
            {
                FOnline->ScriptSetArgObject( lines );
                FOnline->ScriptRunPrepared();
                lines->Release();
            }
        }
    }
}

void item_map_out( Item& item )
{
	
}

// //////////////////////////////////////////////////////////////////////////////////////////////////
// Call on receive message on map.
// By default delay==[TextDelay + message length * 100] ms
bool map_message( ScriptString& message, uint16& hexX, uint16& hexY, uint& color, uint& delay ) // 
{
    return ( color != 0xFFFFFFFE );
}

uint checkWorkbenchInRadius( uint16 pid, uint hexX, uint hexY, uint16 radius )
{
    bool   result = false;
    uint   u = 10 % 2;
    uint16 X = hexX;
    uint16 Y = hexY - radius;
    uint16 finX = 0;
    uint16 finY = 0;
    int8   dy = ( X % 2 == 0 ) ? 1 : 0;
    int8   dy2 = dy;
    for( uint16      j = 0; j < radius + 1; j++ )
    {
        for( uint16 i = 0; i < radius + j + 1; i++ )
        {
            Field* field = GetField( X - i + j, Y + ( i + dy2 ) / 2 + ( j + dy ) / 2 );
            if( !field )
                continue;
            ItemVec items = field->Items;
            for( ItemVecIt it = items.begin(), end = items.end(); it != end; ++it )
            {
                const Item* item = *it;
                if( item->Proto->ProtoId != pid )
                    continue;

                result = true;
                finX = X - i + j;
                finY = Y + ( i + dy2 ) / 2 + ( j + dy ) / 2;
                break;
            }
        }
        dy2 *= -1;
        dy2 += 1;
    }

    if( !result )
    {
        Y = hexY + radius;
        dy = ( X % 2 == 0 ) ? 0 : 1;
        dy2 = dy;
        for( uint16      j = 0; j < radius; j++ )
        {
            for( uint16 i = 0; i < radius + j + 1; i++ )
            {
                Field* field = GetField( X + i - j, Y - ( i + dy2 ) / 2 - ( j + dy ) / 2 );
                if( !field )
                    continue;
                ItemVec items = field->Items;
                for( ItemVecIt it = items.begin(), end = items.end(); it != end; ++it )
                {
                    const Item* item = *it;
                    if( item->Proto->ProtoId != pid )
                        continue;

                    result = true;
                    finX = X + i - j;
                    finY = Y - ( i + dy2 ) / 2 - ( j + dy ) / 2;
                    break;
                }
            }
            dy2 *= -1;
            dy2 += 1;
        }
    }

    int dist = GetDistantion( hexX, finX, hexY, finY );
    for( uint16 i = 0; i < dist; i++ )
    {
        Field* field = GetField( ( hexX * ( dist - i ) + finX * i ) / dist, ( hexY * ( dist - i ) + finY * i ) / dist );
        if( !field )
        {
            result = false;
            break;
        }

        if( field->IsNotRaked )
        {
            result = false;
            break;
        }
    }

    return result;
}

CritterCl* SetCritterHex( CritterCl* cr, uint16 hexX, uint16 hexY )
{
    Field* field = GetField( hexX, hexY );
    if( !field ) return NULL;
    /*if( field->Crit )
       {
            const_cast< int& >(field->Crit->RefCounter)-=1;
       }
       if( cr )
       {
            const_cast< int& >(cr->RefCounter)+=1;
       }*/
    CritterCl* lastCr = const_cast< CritterCl*& >( field->Crit );
    const_cast< CritterCl*& >( field->Crit ) = cr;
    return lastCr;
}

bool        IsHexPassed( uint hexX, uint hexY )
{
    Field* field = GetField( hexX, hexY );
    if( !field ) return false;

    return !field->IsNotPassed;
}

bool        IsScenNoPassed( uint hexX, uint hexY )
{
    Field* field = GetField( hexX, hexY );
    if( !field ) return false;

    return ( field->IsNotPassed && field->IsScen );
}

bool        IsHexRaked( uint hexX, uint hexY )
{
    Field* field = GetField( hexX, hexY );
    if( !field )
        return false;

    return field->IsNotRaked == false;
}

void BlockHexPassed( uint hexX, uint hexY )
{
    Field* field = GetField( hexX, hexY );
    if( !field )
        return;

    const_cast< bool& >( field->IsNotPassed ) = true;
}

void UnblockHexPassed( uint hexX, uint hexY )
{
    Field* field = GetField( hexX, hexY );
    if( !field )
        return;

    const_cast< bool& >( field->IsNotPassed ) = false;
}

void BlockHexRaked( uint hexX, uint hexY )
{
    Field* field = GetField( hexX, hexY );
    if( field ) const_cast< bool& >( field->IsNotRaked ) = true;
}

void UnblockHexRaked( uint hexX, uint hexY )
{
    Field* field = GetField( hexX, hexY );
    if( field ) const_cast< bool& >( field->IsNotRaked ) = false;
}

uint getItemInHex( uint16 pid, uint hexX, uint hexY )
{
    Field* field = GetField( hexX, hexY );
    if( !field )
        return 0;

    ItemVec items = field->Items;
    uint    result = 0;

    for( ItemVecIt it = items.begin(), end = items.end(); it != end; ++it )
    {
        const Item* item = *it;
        if( item->Proto->ProtoId != pid )
            continue;

        result += item->GetCount();
    }

    return result;
}

#include "ClientWindowInfo.h"

bool ClientIsFocused()
{
    return FindWindow( __ClientWindowClass, __ClientWindowName ) == GetForegroundWindow();
}

void ChangeClientParam( CritterCl& cr, int param, int val )
{
    const_cast< int* >( cr.Params )[ param ] = val;
}

void FocusClient()
{
    SetFocus( FindWindow( __ClientWindowClass, __ClientWindowName ) );
}

void FlashClient()
{
    FLASHWINFO fwinfo;
    fwinfo.hwnd = FindWindow( __ClientWindowClass, __ClientWindowName );
	if( fwinfo.hwnd && GetForegroundWindow() != fwinfo.hwnd )
	{
		fwinfo.cbSize = sizeof( FLASHWINFO );
		fwinfo.dwFlags = FLASHW_ALL;
		fwinfo.uCount = 10;
		fwinfo.dwTimeout = 200;
		FlashWindowEx( &fwinfo );
	}
}
#endif

#ifdef __SERVER
uint RunDialogResultFunctionId( Critter& cr, Critter* npc, uint funcId, CScriptArray& args, bool isRet )
{
	if( funcId && FOnline->ScriptPrepare( funcId ) )
	{
		FOnline->ScriptSetArgObject( &cr );
		FOnline->ScriptSetArgObject( npc );
		
		for( uint i = 0, iEnd = args.GetSize(); i < iEnd; i++ )
			FOnline->ScriptSetArgInt( *(int*)args.At( i ) );
		
		if( !FOnline->ScriptRunPrepared() )
			Log( "Error run DialogDemandFunctionId\n" );
		else 
		{
			if( !isRet )
				return 0;
			return FOnline->ScriptGetReturnedUInt();
		}
	}
	return -1;
}

uint GetDialogResultFunctionId( ScriptString& module, ScriptString& func, CScriptArray& args, bool& isReturn )
{
	isReturn = false;
	asIScriptModule* realModule = GetModule( module.c_str() );
	if( realModule )
	{
		ostringstream out;
		out << "void " << func.c_str() << "( Critter&, Critter@";
		
		for( uint i = 0, iEnd = args.GetSize(); i < iEnd; i++ )
			out << ", int";
		out << " )";
		
		if( realModule->GetFunctionByDecl( out.str().c_str() ) )
			return FOnline->ScriptBind( module.c_str(), out.str().c_str(), false );
		
		out.str("");
		out << "uint " << func.c_str() << "( Critter&, Critter@";
		
		for( uint i = 0, iEnd = args.GetSize(); i < iEnd; i++ )
			out << ", int";
		out << " )";
		
		if( realModule->GetFunctionByDecl( out.str().c_str() ) )
		{
			isReturn = true;
			return FOnline->ScriptBind( module.c_str(), out.str().c_str(), false );
		}
	}
	return 0;
}

uint RunDialogBranchFunctionId( Critter& cr, Critter* npc, uint funcId, ScriptString* arg, bool isRet )
{
	if( funcId && FOnline->ScriptPrepare( funcId ) )
	{
		FOnline->ScriptSetArgObject( &cr );
		FOnline->ScriptSetArgObject( npc );
		FOnline->ScriptSetArgObject( arg );
		
		if( !FOnline->ScriptRunPrepared() )
			Log( "Error run DialogDemandFunctionId\n" );
		else 
		{
			if( !isRet )
				return 0;
			return FOnline->ScriptGetReturnedUInt();
		}
	}
	return -1;
}

uint GetDialogBranchFunctionId( ScriptString& module, ScriptString& func, bool& isReturn )
{
	isReturn = false;
	asIScriptModule* realModule = GetModule( module.c_str() );
	if( realModule )
	{
		ostringstream out;
		out << "void " << func.c_str() << "( Critter&, Critter@, string@ )";
		
		if( realModule->GetFunctionByDecl( out.str().c_str() ) )
			return FOnline->ScriptBind( module.c_str(), out.str().c_str(), false );
		
		out.str("");
		out << "uint " << func.c_str() << "( Critter&, Critter@, string@ )";
		
		if( realModule->GetFunctionByDecl( out.str().c_str() ) )
		{
			isReturn = true;
			return FOnline->ScriptBind( module.c_str(), out.str().c_str(), false );
		}
	}
	return 0;
}

bool RunDialogDemandFunctionId( Critter& cr, Critter* npc, uint funcId, CScriptArray& args )
{
	if( funcId && FOnline->ScriptPrepare( funcId ) )
	{
		FOnline->ScriptSetArgObject( &cr );
		FOnline->ScriptSetArgObject( npc );
		
		for( uint i = 0, iEnd = args.GetSize(); i < iEnd; i++ )
			FOnline->ScriptSetArgInt( *(int*)args.At( i ) );
		
		if( !FOnline->ScriptRunPrepared() )
			Log( "Error run DialogDemandFunctionId\n" );
		else return FOnline->ScriptGetReturnedBool();
	}
	return false;
}

uint GetDialogDemandFunctionId( ScriptString& module, ScriptString& func, CScriptArray& args )
{
	asIScriptModule* realModule = GetModule( module.c_str() );
	if( realModule )
	{
		ostringstream out;
		
		out << "bool " << func.c_str() << "( Critter&, Critter@";
		
		for( uint i = 0, iEnd = args.GetSize(); i < iEnd; i++ )
			out << ", int";
		out << " )";
		
		if( realModule->GetFunctionByDecl( out.str().c_str() ) )
			return FOnline->ScriptBind( module.c_str(), out.str().c_str(), false );
	}
	return false;
}

#endif

#ifndef __CLIENT
#include "fonline_scriptpreprocessormk2.cpp"
#endif

asITypeInfo* GetTypeByTypeId( asIScriptModule* module, int typeId )
{
	uint len = module->GetObjectTypeCount();
	for( uint a = 0; a < len; a++)
    {
        if( module->GetObjectTypeByIndex( a )->GetTypeId() == typeId )
            return module->GetObjectTypeByIndex( a );
    }
    return 0;
}

string GetTypeName( int typeId, asIScriptModule* module )
{
	switch ( typeId )
	{	
	case asTYPEID_VOID: return "void";
	case asTYPEID_BOOL: return "bool";
	case asTYPEID_INT8: return "int8";
	case asTYPEID_INT16: return "int16";
	case asTYPEID_INT32: return "int";
	case asTYPEID_INT64: return "int64";
	case asTYPEID_UINT8: return "uint8";
	case asTYPEID_UINT16: return "uint16";
	case asTYPEID_UINT32: return "uint";
	case asTYPEID_UINT64: return "uint64";
	case asTYPEID_FLOAT: return "float";
	case asTYPEID_DOUBLE: return "double";
	case asTYPEID_STRING: return "::string";
	default:
		{
			if( module )
			{
				asITypeInfo* typeObj = GetTypeByTypeId( module, typeId );
				if(!typeObj)
					return "";
				
				ostringstream out;      				
				out << typeObj->GetNamespace() << "::" << typeObj->GetName(); 
				return out.str().c_str(); 
			}
		} break;
	};
	return "";
}

asIScriptModule* GetModule( const char* moduleName )
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

bool RunOptionInModule( uint index, ScriptString& arg, asIScriptModule* moduleVar, asIScriptModule* moduleRun, const char* functionName )
{
	if( moduleVar && moduleRun )
	{
		int typeId = 0;
		const char *nameVar; 
		const char *nameSpace = 0;
		moduleVar->GetGlobalVar( index, &nameVar, &nameSpace, &typeId );
	
		string declaration = GetTypeName( typeId, moduleRun );
		
		if( declaration.empty() )
		{
			if( moduleRun == moduleVar )
			{
				declaration = ASEngine->GetTypeDeclaration( typeId );
				asITypeInfo* objType = ASEngine->GetTypeInfoById( typeId );	
				if( objType && !strcmp( objType->GetName(), "array" ) )
				{
					ostringstream out;
					out << GetTypeName( objType->GetSubTypeId(0), moduleRun ) << "[]";
					declaration = out.str();
				}
			}
			else
				return false;
		}
		
		
        ostringstream out;      		
		if( moduleVar == moduleRun )
			out << "bool " << nameSpace << "::" << functionName << nameVar << "(" << declaration.c_str() << "&,::string&,::string&)"; 
		else out << "bool Options::" << functionName << nameVar << "(" << declaration.c_str() << "&,::string&,::string&)"; 
		bool isFunc = !( out.str().empty() || !moduleRun->GetFunctionByDecl( out.str().c_str() ) );
		if( !isFunc )
		{	
			out.str("");
			
			if( moduleVar == moduleRun )
				out << "bool " << nameSpace << "::" << functionName << "(" << declaration.c_str() << "&,::string&,::string&)"; 
			
			if( !out.str().empty() )
				isFunc = ( NULL != moduleRun->GetFunctionByDecl( out.str().c_str() ) );
			
			if( !isFunc )
			{
				out.str("");
				out << "bool Options::" << functionName << "(" << declaration.c_str() << "&,::string&,::string&)";
				isFunc = ( NULL != moduleRun->GetFunctionByDecl( out.str().c_str() ) );
			}
		}
		
		if( isFunc )
		{
			uint funcId = FOnline->ScriptBind( moduleRun->GetName(), out.str().c_str(), true );
			if( funcId && FOnline->ScriptPrepare( funcId ) )
			{
				ScriptString& decl = ScriptString::Create( moduleVar->GetGlobalVarDeclaration( index, true ) );
				FOnline->ScriptSetArgAddress( moduleVar->GetAddressOfGlobalVar( index ) );
				FOnline->ScriptSetArgAddress( &arg );
				FOnline->ScriptSetArgAddress( &decl );
				if( !FOnline->ScriptRunPrepared() )
					Log( "Error %s: %s\n", functionName, out.str().c_str() );
				else
				{
					decl.Release();
					return FOnline->ScriptGetReturnedBool();
				}
				decl.Release();
			}
			else
				Log( "Error %s: %s\n", functionName, out.str().c_str() );
		}	
	}
	else
		Log( "Error %s: no found module: \n", functionName );
	return false;	
}

bool RunOption( uint index, ScriptString& arg, const ScriptString& moduleName, ScriptString& function )
{
	asIScriptModule* moduleVar = GetModule( moduleName.length() != 0 ? moduleName.c_str( ) : NULL );
	if( !moduleVar )
		return false;
	
	asIScriptModule* moduleMk2 = GetModule(  "Mk2" );
	bool result = RunOptionInModule( index, arg, moduleVar, moduleMk2, function.c_str() );
	if( !result && moduleMk2 != moduleVar )
		return RunOptionInModule( index, arg, moduleVar, moduleVar, function.c_str() );
	return result;
}

uint GetCountGlobalVars( const ScriptString& moduleName )
{
	asIScriptModule* module = GetModule( moduleName.length() != 0 ? moduleName.c_str( ) : NULL );
	if( module )
        return module->GetGlobalVarCount();
    return 0;
}

bool GetDeclarationGlobalVar( ScriptString& declaration, uint index, const ScriptString& moduleName )
{
	asIScriptModule* module = GetModule( moduleName.length() != 0 ? moduleName.c_str( ) : NULL );	
	if( module )
	{
        declaration = module->GetGlobalVarDeclaration( index, true );
		return true;
	}
    return false;
}

void HashToStr( uint hash, ScriptString& str )
{
	str = FOnline->GetNameByHash( hash );
}

#ifdef __SERVER
void init()
#endif
#ifndef __SERVER
bool start()
#endif
{
	RegisterGlobalVars( );
    asIScriptModule* mk2Module = ASEngine->GetModule( "Mk2" );
    if( mk2Module )
    {
		ostringstream out;
        for( uint iFunc = 0, iEnd = mk2Module->GetFunctionCount(); iFunc < iEnd; iFunc++ )
        {
            asIScriptFunction* func = mk2Module->GetFunctionByIndex( iFunc );
            if( func && !strcmp( "void ModuleInit()", func->GetDeclaration( false ) ) )
            {
                uint funcId = FOnline->ScriptBind( "Mk2", func->GetDeclaration( true, true ), true );
                if( funcId && FOnline->ScriptPrepare( funcId ) )
                {    
                    if( !FOnline->ScriptRunPrepared() )
                        Log( "Error run ModuleInit \n" );
                }
                else
                    Log( "Error run ModuleInit \n" );
            }
        }
    }

    #ifndef __SERVER
    uint funcId = FOnline->ScriptBind( "Mk2", "bool start()", true );
    if( funcId && FOnline->ScriptPrepare( funcId ) )
    {
        if( !FOnline->ScriptRunPrepared() )
            Log( "Error run start \n" );
        else return FOnline->ScriptGetReturnedBool();
    }
    return false;
    #endif
}

#ifdef __MAPPER

EXPORT uint GetContObjects( ProtoMap& map, uint pid )
{
    uint count = 0;

    for( MapObjectVecIt it = map.MObjects.begin(), end = map.MObjects.end(); it != end; ++it )
    {
        MapObject* grid = *it;
        if( grid )
        {
            if( grid->ProtoId == pid || pid == 0 )
                count++;
        }
    }
    return count;
}

EXPORT void GetObjectIndex( ProtoMap& map, uint index, uint pid, uint16& hx, uint16& hy, int& p0 )
{
    uint count = 0;
    for( MapObjectVecIt it = map.MObjects.begin(), end = map.MObjects.end(); it != end; ++it )
    {
        MapObject* grid = *it;
        if( grid )
        {
            if( ( grid->ProtoId == pid  || pid == 0 ) && count++ == index )
            {
                hx = grid->MapX;
                hy = grid->MapY;
                p0 = grid->MScenery.Param[ 0 ];
                return;
            }
        }
    }
}

EXPORT bool CreateFolder( ScriptString& name )
{
    return CreateDirectoryA( name.c_str(), NULL ) != 0;
}

EXPORT bool CheckFile( ScriptString& name, ScriptString* outName )
{
    bool            retIs = false;
    WIN32_FIND_DATA ffd;
    HANDLE          hFind = INVALID_HANDLE_VALUE;

    hFind = FindFirstFile( name.c_str(), &ffd );

    if( INVALID_HANDLE_VALUE != hFind )
    {
        retIs = true;
        if( outName )
            *outName = ffd.cFileName;
    }
    FindClose( hFind );
    return retIs;
}

EXPORT void GetNameByHash( uint hash, ScriptString& name )
{
    name = FOnline->GetNameByHash( hash );
}

EXPORT void MapperMap_GetTileName( ProtoMap& map, uint16 hx, uint16 hy, uint numberHex, ScriptString& name )
{
    if( map.GetTiles( hx, hy, false ).size() > numberHex )
        name = FOnline->GetNameByHash( map.GetTiles( hx, hy, false )[ numberHex ].NameHash );
}

#include "animation.cpp"
#endif

#pragma warning (pop)
/************************************************************************/
/*                                                                      */
/************************************************************************/

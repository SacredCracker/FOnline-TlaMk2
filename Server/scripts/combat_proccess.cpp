#ifndef __COMBAT_PROCCESS
#define __COMBAT_PROCCESS

#include "combat_proccess.h"

// int CountRef = 0;

CombatProccess::CombatProccess()
{
    RefCount = 1;
    // Log( "CombatRef %i\n", ++CountRef);

    TypeDamage = -1;
    TargetDT = 0;
    TargetDR = 0;

    for( uint i = 0; i < DAMAGE_TYPE_COUNT; i++ )
        AllDamage[ i ] = 0;

    IsCritical = false;
    ArmorTarget = NULL;
    RealWeapon = NULL;
    Attacker = NULL;
    Result = 0;

    Hx = 0;
    Hy = 0;
    Aim = HIT_LOCATION_UNCALLED;
    IsBurst = false;
    BloodyMess = false;
    CombatMessage = false;
    ScoreUnarmed = false;
    FirstWeaponPerk = -1;
    SecondWeaponPerk = -1;
    AmmoPerk = -1;
    WeaponSubtype = 0;
    DmgMin = 0;
    DmgMax = 0;
    BonusDmg = 0;
    DmgMul = 2;
    DRMod = 0;
    TDMod = 1;
    DMMod = 1;
    DDMod = 1;
    AmmoPid = 0;
    ProtoItemId = 0;

    TypeAttack = 0;
    TargetId = 0;
    TargetHit = false;
    ForceFlags = 0;
    ShowHitAnimForce = false;
}

void CombatProccess::AddRef()
{
    RefCount++;
    // Log( "CombatRef %i\n", ++CountRef);
}

void CombatProccess::Release()
{
    // Log( "CombatRef %i\n", --CountRef);
    if( --RefCount == 0 )
    {
        if( ArmorTarget )
        {
            const_cast< int16& >( ArmorTarget->RefCounter ) -= 1;
            ArmorTarget = NULL;
        }
        if( RealWeapon )
        {
            const_cast< int16& >( RealWeapon->RefCounter ) -= 1;
            RealWeapon = NULL;
        }
        if( Attacker )
        {
            const_cast< int& >( Attacker->RefCounter ) -= 1;
            Attacker = NULL;
        }

        delete this;
    }
}

bool CombatProccess::IsWeaponPerk( int number )
{
    return ( FirstWeaponPerk == number || SecondWeaponPerk == number || AmmoPerk == number );
}

int CombatProccess::get_TotalDamage()
{
    int allDamage = 0;
    for( uint i = 0; i < DAMAGE_TYPE_COUNT; i++ )
        allDamage += AllDamage[ i ];
    return allDamage;
}

void CombatProccess::DropTotalDamage()
{
    for( uint i = 0; i < DAMAGE_TYPE_COUNT; i++ )
        AllDamage[i] = 0;
}

int CombatProccess::get_DamageDefault()
{
    if( TypeDamage >= DAMAGE_TYPE_COUNT || TypeDamage < 0 )
        return get_TotalDamage();
    return AllDamage[ TypeDamage ];
}

int CombatProccess::get_Damage( uint idx )
{
    if( idx >= DAMAGE_TYPE_COUNT )
        return get_TotalDamage();
    return AllDamage[ idx ];
}

void CombatProccess::set_Damage( uint idx, int value )
{
    if( idx >= DAMAGE_TYPE_COUNT )
    {
        Log( "Error! Damage Unknown.  %u \n", idx );
        return;
    }

    AllDamage[ idx ] = value;
}

void CombatProccess::set_DamageDefault( int value )
{
    if( TypeDamage >= DAMAGE_TYPE_COUNT || TypeDamage < 0 )
    {
        Log( "Error! Damage Unknown.  %i \n", TypeDamage );
        asIScriptContext* ctx = ScriptGetActiveContext();
        if( ctx )
        {
            asIScriptFunction* func = NULL;
            for( uint i = 0, iEnd = ctx->GetCallstackSize(); i < iEnd; i++ )
            {
                func = ctx->GetFunction( i );
                if( func )
                    Log( "%u)     %s :: %s :: %u\n", i, ( func->GetModuleName() ) ? func->GetModuleName() : "None", func->GetDeclaration(), ctx->GetLineNumber( i ) );
                else
                    Log( "None\n" );
            }
        }
        return;
    }

    AllDamage[ TypeDamage ] = value;
}

CombatProccess* CombatProccessFactory()
{
    return new CombatProccess();
}

void RegistrationCombatProccessClass()
{
    RegCombatProccess( ASEngine->RegisterObjectType( "CombatProccess", sizeof( CombatProccess ), asOBJ_REF ) );
    RegCombatProccess( ASEngine->RegisterObjectBehaviour( "CombatProccess", asBEHAVE_FACTORY, "CombatProccess@ f( )", asFUNCTION( CombatProccessFactory ), asCALL_CDECL ) );
    RegCombatProccess( ASEngine->RegisterObjectBehaviour( "CombatProccess", asBEHAVE_ADDREF, "void f()", asMETHOD( CombatProccess, AddRef ), asCALL_THISCALL ) );
    RegCombatProccess( ASEngine->RegisterObjectBehaviour( "CombatProccess", asBEHAVE_RELEASE, "void f()", asMETHOD( CombatProccess, Release ), asCALL_THISCALL ) );

    RegCombatProccess( ASEngine->RegisterObjectMethod( "CombatProccess", "bool IsWeaponPerk( int perk )", asMETHOD( CombatProccess, IsWeaponPerk ), asCALL_THISCALL ) );

    RegCombatProccess( ASEngine->RegisterObjectMethod( "CombatProccess", "void set_Damage( uint, int )", asMETHOD( CombatProccess, set_Damage ), asCALL_THISCALL ) );
    RegCombatProccess( ASEngine->RegisterObjectMethod( "CombatProccess", "int get_Damage( uint )", asMETHOD( CombatProccess, get_Damage ), asCALL_THISCALL ) );
    RegCombatProccess( ASEngine->RegisterObjectMethod( "CombatProccess", "void set_Damage( int )", asMETHOD( CombatProccess, set_DamageDefault ), asCALL_THISCALL ) );
    RegCombatProccess( ASEngine->RegisterObjectMethod( "CombatProccess", "int get_Damage( )", asMETHOD( CombatProccess, get_DamageDefault ), asCALL_THISCALL ) );
    RegCombatProccess( ASEngine->RegisterObjectMethod( "CombatProccess", "int get_TotalDamage( )", asMETHOD( CombatProccess, get_TotalDamage ), asCALL_THISCALL ) );
    RegCombatProccess( ASEngine->RegisterObjectMethod( "CombatProccess", "void DropDamage( )", asMETHOD( CombatProccess, DropTotalDamage ), asCALL_THISCALL ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "bool IsCritical", offsetof( CombatProccess, IsCritical ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "::Item@ ArmorTarget", offsetof( CombatProccess, ArmorTarget ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "::Item@ RealWeapon", offsetof( CombatProccess, RealWeapon ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "uint16 ProtoItemId", offsetof( CombatProccess, ProtoItemId ) ) );

    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "::Critter@ Attacker", offsetof( CombatProccess, Attacker ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "uint8 Result", offsetof( CombatProccess, Result ) ) );

    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "uint16 Hx", offsetof( CombatProccess, Hx ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "uint16 Hy", offsetof( CombatProccess, Hy ) ) );

    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "uint8 Aim", offsetof( CombatProccess, Aim ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "uint8 WeaponSubtype", offsetof( CombatProccess, WeaponSubtype ) ) );

    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "bool IsBurst", offsetof( CombatProccess, IsBurst ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "bool BloodyMess", offsetof( CombatProccess, BloodyMess ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "bool CombatMessage", offsetof( CombatProccess, CombatMessage ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "bool ScoreUnarmed", offsetof( CombatProccess, ScoreUnarmed ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "bool TargetHit", offsetof( CombatProccess, TargetHit ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "bool ShowHitAnimForce", offsetof( CombatProccess, ShowHitAnimForce ) ) );

    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int FirstWeaponPerk", offsetof( CombatProccess, FirstWeaponPerk ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int SecondWeaponPerk", offsetof( CombatProccess, SecondWeaponPerk ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int AmmoPerk", offsetof( CombatProccess, AmmoPerk ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int DmgMin", offsetof( CombatProccess, DmgMin ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int DmgMax", offsetof( CombatProccess, DmgMax ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int BonusDmg", offsetof( CombatProccess, BonusDmg ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int DmgMul", offsetof( CombatProccess, DmgMul ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int DRMod", offsetof( CombatProccess, DRMod ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int DMMod", offsetof( CombatProccess, DMMod ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int DDMod", offsetof( CombatProccess, DDMod ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int TDMod", offsetof( CombatProccess, TDMod ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int TypeAttack", offsetof( CombatProccess, TypeAttack ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int TypeDamage", offsetof( CombatProccess, TypeDamage ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int TargetDT", offsetof( CombatProccess, TargetDT ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "int TargetDR", offsetof( CombatProccess, TargetDR ) ) );

    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "uint TargetId", offsetof( CombatProccess, TargetId ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "uint ForceFlags", offsetof( CombatProccess, ForceFlags ) ) );
    RegCombatProccess( ASEngine->RegisterObjectProperty( "CombatProccess", "uint AmmoPid", offsetof( CombatProccess, AmmoPid ) ) );
}

#endif

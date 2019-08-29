#ifndef __COMBAT_PROCCESS_H
#define __COMBAT_PROCCESS_H

#define RegCombatProccess( reg )    if( reg < 0 ) \
        Log( "ќшибка регистрации класса CombatProccess <%d>.\n", __LINE__ )

struct CombatProccess
{
    CombatProccess();
    void AddRef();
    void Release();
    bool IsWeaponPerk( int number );
    int  get_TotalDamage();
	void DropTotalDamage();
    int  get_DamageDefault();
    void set_DamageDefault( int value );
    int  get_Damage( uint idx );
    void set_Damage( uint idx, int value );

    uint16   ProtoItemId;
    uint16   Hx;
    uint16   Hy;

    uint8    Aim;
    uint8    WeaponSubtype;
    uint8    Result;

    bool     IsBurst;
    bool     BloodyMess;
    bool     CombatMessage;
    bool     ScoreUnarmed;
    bool     TargetHit;
    bool     ShowHitAnimForce;
    bool     IsCritical;

    int      FirstWeaponPerk;
    int      SecondWeaponPerk;
    int      AmmoPerk;
    int      DmgMin;
    int      DmgMax;
    int      DmgType;
    int      BonusDmg;
    int      DmgMul;
    int      DRMod;
    int      DMMod;
    int      DDMod;
    int      TDMod;
    int      TypeAttack;
    int      AllDamage[ DAMAGE_TYPE_COUNT ];
    int      TypeDamage;
    int      TargetDT;
    int      TargetDR;

    uint     TargetId;
    uint     ForceFlags;
    uint     AmmoPid;

    Item*    ArmorTarget;
    Item*    RealWeapon;

    Critter* Attacker;
    int      RefCount;
};

CombatProccess* CombatProccessFactory();
void            RegistrationCombatProccessClass();
EXPORT void     CritterDamage( Critter& cr, CombatProccess& combatProccess, int reason );

#endif

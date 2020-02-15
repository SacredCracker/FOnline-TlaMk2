#define __NATIVE
#define _MAIN_
#include "_skill_max.fos"
#undef _MAIN_

inline int GetNightPersonBonus();

EXPORT int getParam_Strength( CritterMutual & cr, uint );
EXPORT int getParam_Perception( CritterMutual & cr, uint );
EXPORT int getParam_Endurance( CritterMutual & cr, uint );
EXPORT int getParam_Charisma( CritterMutual & cr, uint );
EXPORT int getParam_Intellegence( CritterMutual & cr, uint );
EXPORT int getParam_Agility( CritterMutual & cr, uint );
EXPORT int getParam_Luck( CritterMutual & cr, uint );
EXPORT int getParam_Hp( CritterMutual & cr, uint );
EXPORT int getParam_MaxLife( CritterMutual & cr, uint );
EXPORT int getParam_MaxAp( CritterMutual & cr, uint );
EXPORT int getParam_Ap( CritterMutual & cr, uint );
EXPORT int getParam_MaxMoveAp( CritterMutual & cr, uint );
EXPORT int getParam_MoveAp( CritterMutual & cr, uint );
EXPORT int getParam_MaxWeight( CritterMutual & cr, uint );
EXPORT int getParam_Sequence( CritterMutual & cr, uint );
EXPORT int getParam_MeleeDmg( CritterMutual & cr, uint );
EXPORT int getParam_ThrowingDmg( CritterMutual & cr, uint );
EXPORT int getParam_HealingRate( CritterMutual & cr, uint );
EXPORT int getParam_CriticalChance( CritterMutual & cr, uint );
EXPORT int getParam_MaxCritical( CritterMutual & cr, uint );
EXPORT int getParam_Ac( CritterMutual & cr, uint );
EXPORT int getParam_DamageResistance( CritterMutual& cr, uint index );
EXPORT int getParam_DamageThreshold( CritterMutual& cr, uint index );
EXPORT int getParam_ArmorBonus( CritterMutual& cr, uint index );
EXPORT int getParam_RadiationResist( CritterMutual & cr, uint );
EXPORT int getParam_CriticalResist( CritterMutual & cr, uint );
EXPORT int getParam_PoisonResist( CritterMutual & cr, uint );
EXPORT int getParam_Reputation( CritterMutual& cr, uint index );
EXPORT int getParam_Lionhead( CritterMutual & cr, uint );
EXPORT int  getParam_Timeout( CritterMutual& cr, uint index );
EXPORT void changedParam_Skill( CritterMutual& cr, uint index, int oldValue );

EXPORT void SetParam( CritterMutual& cr, uint index, int val )
{
    const_cast< int* >( cr.Params )[ index ] = val;
}

/************************************************************************/
/* Parameters Get behaviors                                             */
/************************************************************************/

EXPORT int getParam_Lionhead( CritterMutual& cr, uint )
{
    int         val = cr.Params[ SK_LIONHEART ];

    const Item* armor = cr.ItemSlotArmor;
    if( armor && !armor->IsNotValid )
        val -= armor->Proto->Volume * 13;
    const Item* h1 = cr.ItemSlotMain;
    const Item* h2 = cr.ItemSlotExt;
    if( h1 )
    {
        if( h2 )
        {
            if( h1->Proto->Volume > h2->Proto->Volume )
                val -= h1->Proto->Volume * 13;
            else
                val -= h2->Proto->Volume * 13;
        }
        else
            val -= h1->Proto->Volume * 13;
    }
    else if( h2 )
        val -= h2->Proto->Volume * 13;
    // (ќбъем наибольшей вещи из двух рук)*13 + (ќбъем брони)*13
    return ( ( ( val ) > ( 300 ) ) ? ( 300 ) : ( ( ( val ) < ( 0 ) ) ? ( 0 ) : ( val ) ) );
}

EXPORT void changedParam_Skill( CritterMutual& cr, uint index, int oldValue )
{
    int val = cr.Params[ index ];
    if( val > GetMaxSkill( index ) )
    {
        #ifdef __SERVER
        FOnline->CritterChangeParameter( cr, index );
        const_cast< int* >( cr.Params )[ index ] = GetMaxSkill( index );
        #endif
    }
}

EXPORT int getParam_Skill( CritterMutual& cr, uint i )
{
    int val = cr.Params[ i ];
    return ( ( ( val ) > ( GetMaxSkill( i ) ) ) ? ( GetMaxSkill( i ) ) : ( ( ( val ) < ( 0 ) ) ? ( 0 ) : ( val ) ) );
}

EXPORT int getParam_Timeout( CritterMutual& cr, uint index )
{
    return (uint) cr.Params[ index ] > FOnline->FullSecond ? (uint) cr.Params[ index ] - FOnline->FullSecond : 0;
}

EXPORT int getParam_Strength( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_STRENGTH ] + cr.Params[ ST_STRENGTH_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_STRENGTH );
    if( cr.Params[ PE_ADRENALINE_RUSH ]  && getParam_Timeout( cr, TO_BATTLE )  && // Adrenaline rush perk
        cr.Params[ ST_CURRENT_HP ] <= ( cr.Params[ ST_MAX_LIFE ] + cr.Params[ ST_STRENGTH ] + cr.Params[ ST_ENDURANCE ] * 2 ) * 2 / 3 )
        val += 2;
    if( cr.Params[ TRAIT_NIGHT_PERSON ] )
        val += GetNightPersonBonus();
    return CLAMP( val, 1, 15 );
}

EXPORT int getParam_Perception( CritterMutual& cr, uint )
{
    int val = ( cr.Params[ DAMAGE_EYE ] ? 1 : cr.Params[ ST_PERCEPTION ] + cr.Params[ ST_PERCEPTION_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_PERCEPTION ) );
    if( cr.Params[ TRAIT_NIGHT_PERSON ] )
        val += GetNightPersonBonus();
    return CLAMP( val, 1, 15 );
}

EXPORT int getParam_Endurance( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_ENDURANCE ] + cr.Params[ ST_ENDURANCE_EXT ];
    return CLAMP( val, 1, 15 );
}

EXPORT int getParam_Charisma( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_CHARISMA ] + cr.Params[ ST_CHARISMA_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_HARISMA );
    return CLAMP( val, 1, 15 );
}

EXPORT int getParam_Intellegence( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_INTELLECT ] + cr.Params[ ST_INTELLECT_EXT ];
    return CLAMP( val, 1, 15 );
}

EXPORT int getParam_Agility( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_AGILITY ] + cr.Params[ ST_AGILITY_EXT ];
    if( cr.Params[ TRAIT_NIGHT_PERSON ] )
        val += GetNightPersonBonus();
    return CLAMP( val, 1, 15 );
}

EXPORT int getParam_Luck( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_LUCK ] + cr.Params[ ST_LUCK_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_LUCK );
    return CLAMP( val, 1, 15 );
}

EXPORT int getParam_Hp( CritterMutual& cr, uint )
{
    if( getParam_MaxLife( cr, 0 ) < cr.Params[ ST_CURRENT_HP ] )
    {
        const_cast< int* >( cr.Params )[ ST_CURRENT_HP ] = getParam_MaxLife( cr, 0 );
        return getParam_MaxLife( cr, 0 );
    }
    return cr.Params[ ST_CURRENT_HP ];
}

EXPORT int getParam_MaxLife( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_MAX_LIFE ] + cr.Params[ ST_MAX_LIFE_EXT ] + cr.Params[ ST_STRENGTH ] + cr.Params[ ST_ENDURANCE ] * 2;
    return CLAMP( val, 1, 9999 );
}

EXPORT int getParam_MaxAp( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_ACTION_POINTS ] + cr.Params[ ST_ACTION_POINTS_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_ACTION_POINTS ) + getParam_Agility( cr, 0 ) / 2;
    if( cr.Params[ PE_ADRENALINE_RUSH ] && getParam_Timeout( cr, TO_BATTLE ) &&        // Adrenaline rush perk
        cr.Params[ ST_CURRENT_HP ] <= ( cr.Params[ ST_MAX_LIFE ] + cr.Params[ ST_STRENGTH ] + cr.Params[ ST_ENDURANCE ] * 2 ) / 3 )
        val += 1;
    return CLAMP( val, 1, 9999 );
}

EXPORT int getParam_Ap( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_CURRENT_AP ];
    val /= AP_DIVIDER;
    return CLAMP( val, -9999, 9999 );
}

EXPORT int getParam_MaxMoveAp( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_MAX_MOVE_AP ];
    return CLAMP( val, 0, 9999 );
}

EXPORT int getParam_MoveAp( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_MOVE_AP ];
    return CLAMP( val, 0, 9999 );
}

EXPORT int getParam_MaxWeight( CritterMutual& cr, uint )
{
    int val = max( cr.Params[ ST_CARRY_WEIGHT ] + cr.Params[ ST_CARRY_WEIGHT_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_CARRYWEIGHT ), 0 );
    val += CONVERT_GRAMM( 141 + getParam_Strength( cr, 0 ) * 13 );
    return CLAMP( val, 0, 2000000000 );
}

EXPORT int getParam_Sequence( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_SEQUENCE ] + cr.Params[ ST_SEQUENCE_EXT ] + getParam_Perception( cr, 0 ) * 2;
    return CLAMP( val, 0, 9999 );
}

EXPORT int getParam_MeleeDmg( CritterMutual& cr, uint )
{
    int strength = getParam_Strength( cr, 0 );
    int bonus = getParam_Skill( cr, SK_UNARMED );
    int val = cr.Params[ ST_MELEE_DAMAGE ] + cr.Params[ ST_MELEE_DAMAGE_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_MELEE_DAMAGE ) + ( strength > 6 ? ( ( strength - 5 ) * 2 ) : 1 ) + ( bonus > 100 ? ( ( bonus - 80 ) / ( 12 - ( bonus / 100 ) ) ) : 0 );
    return CLAMP( val, 1, 9999 );
}

EXPORT int getParam_ThrowingDmg( CritterMutual& cr, uint )
{
    int strength = getParam_Strength( cr, 0 );
    int val = ( strength > 6 ? ( strength - 5 ) * 2 : 1 ) + ( getParam_Skill( cr, SK_THROWING ) > 100 ? ( ( getParam_Skill( cr, SK_THROWING ) - 80 ) / ( 12 - ( getParam_Skill( cr, SK_THROWING ) / 100 ) ) ) : 0 );
    return CLAMP( val, 1, 9999 );
}

EXPORT int getParam_HealingRate( CritterMutual& cr, uint )
{
    int e = getParam_Endurance( cr, 0 );
    int s = getParam_Strength( cr, 0 );
    int val = max( 1, e / 2 + s / 3 ) + cr.Params[ ST_HEALING_RATE ] + cr.Params[ ST_HEALING_RATE_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_FASTERHEALING );
    if( cr.Params[ PE_ADRENALINE_RUSH ] && getParam_Timeout( cr, TO_BATTLE ) && // Adrenaline rush perk
        cr.Params[ ST_CURRENT_HP ] <= ( cr.Params[ ST_MAX_LIFE ] + cr.Params[ ST_STRENGTH ] + cr.Params[ ST_ENDURANCE ] * 2 ) / 2 )
        val += 8;

    if( cr.Params[ TRAIT_NIGHT_PERSON ] != 0 )
    {
        if( GetNightPersonBonus() == 1 )
            val *= 2;
        else if( GetNightPersonBonus() == -1 )
            val /= 2;
    }

    return CLAMP( val, 0, 9999 );
}

EXPORT int getParam_CriticalChance( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_CRITICAL_CHANCE ] + cr.Params[ ST_CRITICAL_CHANCE_EXT ] + getParam_Luck( cr, 0 );
    return CLAMP( val, 0, 100 );
}

EXPORT int getParam_MaxCritical( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_MAX_CRITICAL ] + cr.Params[ ST_MAX_CRITICAL_EXT ];
    return CLAMP( val, -100, 100 );
}

EXPORT int getParam_Ac( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_ARMOR_CLASS ] + cr.Params[ ST_ARMOR_CLASS_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_AC );
    if( cr.Params[ PE_ADRENALINE_RUSH ] > 0 && getParam_Hp( cr, 0 ) <= ( getParam_MaxLife( cr, 0 ) / 3 ) )
    {
        val += 5;
    }
    const Item* armor = cr.ItemSlotArmor;
    // const Item* weapon=cr.ItemSlotMain;
    /*if(cr.Params[PE_HTH_EVADE]!=0)
       {
            int skill=SKILL_OFFSET(weapon->Proto->Weapon_Skill[0 & 7]);
            if(skill==SK_UNARMED && getParam_Ap(cr, 0)>0) val+=getParam_Ap(cr, 0)*2+cr.Params[SK_UNARMED]/15;
       }
       else val+=getParam_Ap(cr, 0);*/
    int armorVal = 0;
    if( armor && !armor->IsNotValid && armor->GetId() && armor->IsArmor() )
    {
        armorVal += armor->Proto->Armor_AC;
        if( armor->GetDeteriorationProc() > 20 )
            armorVal = ( armorVal * ( 100 - armor->GetDeteriorationProc() ) ) / 80;
    }

    return CLAMP( val + armorVal, 0, 39 );
}

EXPORT int getParam_DamageResistance( CritterMutual& cr, uint index )
{
    int         dmgType = index - ST_NORMAL_RESIST + 1;

    const Item* armor = cr.ItemSlotArmor;
    int         val = 0;
    int         drVal = 0;
    switch( dmgType )
    {
    case DAMAGE_NORMAL:
        val = cr.Params[ ST_NORMAL_RESIST ]  + cr.Params[ ST_NORMAL_RESIST_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DRNORMAL );
		if( armor && !armor->IsNotValid )
			drVal = armor->Proto->Armor_DRNormal;
        break;
    case DAMAGE_LASER:
        val = cr.Params[ ST_LASER_RESIST ]   + cr.Params[ ST_LASER_RESIST_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DRLASER );
        if( armor && !armor->IsNotValid )
			drVal = armor->Proto->Armor_DRLaser;
        break;
    case DAMAGE_FIRE:
        val = cr.Params[ ST_FIRE_RESIST ]    + cr.Params[ ST_FIRE_RESIST_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DRFIRE );
        if( armor && !armor->IsNotValid )
			drVal = armor->Proto->Armor_DRFire;
        break;
    case DAMAGE_PLASMA:
        val = cr.Params[ ST_PLASMA_RESIST ]  + cr.Params[ ST_PLASMA_RESIST_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DRPLASMA );
        if( armor && !armor->IsNotValid )
			drVal = armor->Proto->Armor_DRPlasma;
        break;
    case DAMAGE_ELECTR:
        val = cr.Params[ ST_ELECTRO_RESIST ] + cr.Params[ ST_ELECTRO_RESIST_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DRELECTR );
        if( armor && !armor->IsNotValid )
			drVal = armor->Proto->Armor_DRElectr;
        break;
    case DAMAGE_EMP:
        val = cr.Params[ ST_EMP_RESIST ]     + cr.Params[ ST_EMP_RESIST_EXT ];
        if( armor && !armor->IsNotValid )
			drVal = armor->Proto->Armor_DREmp;
        break;
    case DAMAGE_EXPLODE:
        val = cr.Params[ ST_EXPLODE_RESIST ] + cr.Params[ ST_EXPLODE_RESIST_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DREXPLODE );
        if( armor && !armor->IsNotValid )
			drVal = armor->Proto->Armor_DRExplode;
        break;
    case DAMAGE_UNCALLED:
    default:
        break;
    }

    if( armor && !armor->IsNotValid && armor->GetId() && armor->IsArmor() )
    {
        if( armor->GetDeteriorationProc() > 20 )
            drVal = ( drVal * ( 100 - armor->GetDeteriorationProc() ) ) / 80;
        val += drVal;
    }

    if( dmgType == DAMAGE_EMP )
        return CLAMP( val, 0, 999 );
    return CLAMP( val, 0, 90 );
}

EXPORT int getParam_ArmorBonus( CritterMutual& cr, uint index )
{
    const Item* armor = cr.ItemSlotArmor;
    if( armor == NULL || armor->IsNotValid || armor->GetId() == 0 )
        return 0;
    return cr.Params[ index ];
}

EXPORT int getParam_DamageThreshold( CritterMutual& cr, uint index )
{
    if( index == 4294966346 )
	{
		//Log( "Поврежденный индекс трешхолда\n");
		//CallStackToLog();
        index = ST_ELECTRO_ABSORB;                     // TabaK. В душе не ебу, что за кал...
    }
	const Item* armor = cr.ItemSlotArmor;
    int         val = 0;
    int         dtVal = 0;
    switch( index )
    {
    case ST_NORMAL_ABSORB:
        val = cr.Params[ ST_NORMAL_ABSORB ]  + cr.Params[ ST_NORMAL_ABSORB_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DTNORMAL );
        if( armor && !armor->IsNotValid )
			dtVal = armor->Proto->Armor_DTNormal;
        break;
    case ST_LASER_ABSORB:
        val = cr.Params[ ST_LASER_ABSORB ]   + cr.Params[ ST_LASER_ABSORB_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DTLASER );
        if( armor && !armor->IsNotValid )
			dtVal = armor->Proto->Armor_DTLaser;
        break;
    case ST_FIRE_ABSORB:
        val = cr.Params[ ST_FIRE_ABSORB ]    + cr.Params[ ST_FIRE_ABSORB_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DTFIRE );
        if( armor && !armor->IsNotValid )
			dtVal = armor->Proto->Armor_DTFire;
        break;
    case ST_PLASMA_ABSORB:
        val = cr.Params[ ST_PLASMA_ABSORB ]  + cr.Params[ ST_PLASMA_ABSORB_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DTPLASMA );
        if( armor && !armor->IsNotValid )
			dtVal = armor->Proto->Armor_DTPlasma;
        break;
    case ST_ELECTRO_ABSORB:
        val = cr.Params[ ST_ELECTRO_ABSORB ] + cr.Params[ ST_ELECTRO_ABSORB_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DTELECTR );
        if( armor && !armor->IsNotValid )
			dtVal = armor->Proto->Armor_DTElectr;
        break;
    case ST_EMP_ABSORB:
        val = cr.Params[ ST_EMP_ABSORB ]     + cr.Params[ ST_EMP_ABSORB_EXT ];
        if( armor && !armor->IsNotValid )
			dtVal = armor->Proto->Armor_DTEmp;
        break;
    case ST_EXPLODE_ABSORB:
        val = cr.Params[ ST_EXPLODE_ABSORB ] + cr.Params[ ST_EXPLODE_ABSORB_EXT ] + getParam_ArmorBonus( cr, ARMOR_BONUS_DTEXPLODE );
        if( armor && !armor->IsNotValid )
			dtVal = armor->Proto->Armor_DTExplode;
        break;
    default:
        break;
    }
/*
        char log[255];
        if(index==ST_ELECTRO_ABSORB)
        {
                sprintf_s(log, "Val=%d, ST_ELECTRO_ABSORB=%d, ST_ELECTRO_ABSORB_EXT=%d, ARMOR_BONUS_DTELECTR=%d\n", val, cr.Params[ST_ELECTRO_ABSORB], cr.Params[ST_ELECTRO_ABSORB_EXT], getParam_ArmorBonus(cr, ARMOR_BONUS_DTELECTR));
                Log(log);
        }
        else
        {
                sprintf_s(log,"index=%u\n", index);
                Log(log);
        }*/

    if( armor && !armor->IsNotValid && armor->GetId() && armor->IsArmor() )
    {
        if( armor->GetDeteriorationProc() > 20 )
            dtVal = ( dtVal * ( 100 - armor->GetDeteriorationProc() ) ) / 80;
        val += dtVal;
    }

    return CLAMP( val, 0, 999 );
}

EXPORT int getParam_CriticalResist( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_CRITICAL_RESISTANCE ] + getParam_ArmorBonus( cr, ARMOR_BONUS_CRITICAL_RESISTANCE );
    return CLAMP( val, 0, 95 );
}

EXPORT int getParam_RadiationResist( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_RADIATION_RESISTANCE ] + cr.Params[ ST_RADIATION_RESISTANCE_EXT ]  + getParam_ArmorBonus( cr, ARMOR_BONUS_DRRAD ) + getParam_Endurance( cr, 0 ) * 2;
    return CLAMP( val, 0, 95 );
}

EXPORT int getParam_PoisonResist( CritterMutual& cr, uint )
{
    int val = cr.Params[ ST_POISON_RESISTANCE ] + cr.Params[ ST_POISON_RESISTANCE_EXT ] + getParam_Endurance( cr, 0 ) * 5 + ( cr.Params[ PE_SNAKEATER ] * 25 );
    return CLAMP( val, 0, 95 );
}

EXPORT int getParam_Reputation( CritterMutual& cr, uint index )
{
    Log( " EXPORT int getParam_Reputation(CritterMutual& cr, uint index) \n" );
    #ifdef __SERVER
    if( cr.Params[ index ] == 0x80000000 )
    {
        FOnline->CritterChangeParameter( cr, index );
        const_cast< int* >( cr.Params )[ index ] = 0;
    }
    #endif
    #ifdef __CLIENT
    if( cr.Params[ index ] == 0x80000000 )
        return 0;
    #endif
    return cr.Params[ index ];
}

inline int GetNightPersonBonus()
{
    if( FOnline->Hour < 5 || FOnline->Hour > 21 )
        return 1;
    if( FOnline->Hour == 5 )
        return 1;
    if( FOnline->Hour == 21 )
        return 1;
    if( ( FOnline->Hour > 5 && FOnline->Hour < 9 ) || ( FOnline->Hour < 21 && FOnline->Hour > 17 ) )
        return 0;
    return -1;
}

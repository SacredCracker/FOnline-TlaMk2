#include "windows.h"
#include "fonline_tla.h"

#ifdef __SERVER
#pragma comment(lib, "shell32.lib")
#endif

#ifdef __CLIENT
#include "angelscript.h"
#include "winsock.h"
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "user32.lib")
#endif

// Engine data
GameOptions* Game;
asIScriptEngine* ASEngine;
void (*Log)(const char* frmt, ...);

// Extern data definition
_GlobalVars GlobalVars;

#ifdef __SERVER
EXPORT void Map_GetExitGrid(Map& map, CritterMutual& cr,uint16& x, uint16& y,uint16& MapPid, uint& EntireId);
EXPORT bool FileDelete(ScriptString* filename);
EXPORT int MakeBackup(ScriptString* parameters);
extern "C" __declspec(dllexport) bool __cdecl check_look(Map& map, Critter& cr, Critter& opponent);
EXPORT void Map_GetExitGlobalGrid(Map& map, CritterMutual& cr,uint16& x, uint16& y);
#endif
#ifdef __CLIENT
EXPORT void ChangeClientParam(CritterCl& cr, int param, int value);
EXPORT unsigned int GetOnline(ScriptString* serverIp, uint serverPort);
EXPORT void FocusClient();
EXPORT void FlashClient();
EXPORT bool ClientIsFocused();
EXPORT int getParam_VisibleDist(CritterMutual& cr, uint);
#endif

// Slot/parameters allowing
EXPORT bool allowSlot_Hand1(uint8, Item&, Critter&, Critter& toCr);

// Parameters Get behavior
EXPORT int getParam_Strength(CritterMutual& cr, uint);
EXPORT int getParam_Perception(CritterMutual& cr, uint);
EXPORT int getParam_Endurance(CritterMutual& cr, uint);
EXPORT int getParam_Charisma(CritterMutual& cr, uint);
EXPORT int getParam_Intellegence(CritterMutual& cr, uint);
EXPORT int getParam_Agility(CritterMutual& cr, uint);
EXPORT int getParam_Luck(CritterMutual& cr, uint);
EXPORT int getParam_Hp(CritterMutual& cr, uint);
EXPORT int getParam_MaxLife(CritterMutual& cr, uint);
EXPORT int getParam_MaxAp(CritterMutual& cr, uint);
EXPORT int getParam_Ap(CritterMutual& cr, uint);
EXPORT int getParam_MaxMoveAp(CritterMutual& cr, uint);
EXPORT int getParam_MoveAp(CritterMutual& cr, uint);
EXPORT int getParam_MaxWeight(CritterMutual& cr, uint);
EXPORT int getParam_Sequence(CritterMutual& cr, uint);
EXPORT int getParam_MeleeDmg(CritterMutual& cr, uint);
EXPORT int getParam_ThrowingDmg(CritterMutual& cr, uint);
EXPORT int getParam_HealingRate(CritterMutual& cr, uint);
EXPORT int getParam_CriticalChance(CritterMutual& cr, uint);
EXPORT int getParam_MaxCritical(CritterMutual& cr, uint);
EXPORT int getParam_Ac(CritterMutual& cr, uint);
EXPORT int getParam_DamageResistance(CritterMutual& cr, uint index);
EXPORT int getParam_DamageThreshold(CritterMutual& cr, uint index);
EXPORT int getParam_RadiationResist(CritterMutual& cr, uint);
EXPORT int getParam_PoisonResist(CritterMutual& cr, uint);
EXPORT int getParam_Timeout(CritterMutual& cr, uint index);
EXPORT int getParam_Reputation(CritterMutual& cr, uint index);
EXPORT void changedParam_Reputation(CritterMutual& cr, uint index, int oldValue);

// Extended methods
EXPORT bool Critter_IsInjured(CritterMutual& cr);
EXPORT bool Critter_IsDmgEye(CritterMutual& cr);
EXPORT bool Critter_IsDmgLeg(CritterMutual& cr);
EXPORT bool Critter_IsDmgTwoLeg(CritterMutual& cr);
EXPORT bool Critter_IsDmgArm(CritterMutual& cr);
EXPORT bool Critter_IsDmgTwoArm(CritterMutual& cr);
EXPORT bool Critter_IsAddicted(CritterMutual& cr);
EXPORT bool Critter_IsOverweight(CritterMutual& cr);
EXPORT bool Item_Weapon_IsHtHAttack(Item& item, uint8 mode);
EXPORT bool Item_Weapon_IsGunAttack(Item& item, uint8 mode);
EXPORT bool Item_Weapon_IsRangedAttack(Item& item, uint8 mode);

// Callbacks
uint GetUseApCost(CritterMutual& cr, Item& item, uint8 mode);
uint GetAttackDistantion(CritterMutual& cr, Item& item, uint8 mode);

// Generic stuff
int  GetNightPersonBonus();
uint GetAimApCost(int hitLocation);
uint GetAimHit(int hitLocation);
uint GetMultihex(CritterMutual& cr);

/************************************************************************/
/* Initialization                                                       */
/************************************************************************/

int __stdcall DllMain(void* module, unsigned long reason, void* reserved)
{
	// In this function all global variables is NOT initialized, use DllMainEx instead
	return 1;
}

EXPORT void DllMainEx(bool compiler)
{
	// bool compiler - true if script compiled using ASCompiler, false if script compiled in server
	// In this function all global variables is initialized, if compiled not by compiler

	if(compiler) return;

	// Register callbacks
	Game->GetUseApCost=&GetUseApCost;
	Game->GetAttackDistantion=&GetAttackDistantion;

	// Register script global vars
	memset(&GlobalVars, 0, sizeof(GlobalVars));
	for(int i=0; i<ASEngine->GetGlobalPropertyCount(); i++)
	{
		const char* name;
		void* ptr;
		if(ASEngine->GetGlobalPropertyByIndex(i, &name, NULL, NULL, NULL, &ptr)<0) continue;

#define REGISTER_GLOBAL_VAR(type, gvar) else if(!strcmp(#gvar, name)) GlobalVars.gvar=(type*)ptr
		REGISTER_GLOBAL_VAR(int , CurX);
		REGISTER_GLOBAL_VAR(int , CurY);
		REGISTER_GLOBAL_VAR(uint, HitAimEyes);
		REGISTER_GLOBAL_VAR(uint, HitAimHead);
		REGISTER_GLOBAL_VAR(uint, HitAimGroin);
		REGISTER_GLOBAL_VAR(uint, HitAimTorso);
		REGISTER_GLOBAL_VAR(uint, HitAimArms);
		REGISTER_GLOBAL_VAR(uint, HitAimLegs);
#ifdef __CLIENT
		REGISTER_GLOBAL_VAR(bool, AutoAim);
#endif
	}
}

/************************************************************************/
/* Slot/parameters allowing                                             */
/************************************************************************/

EXPORT bool allowSlot_Hand1(uint8, Item&, Critter&, Critter& toCr)
{
	return toCr.Params[PE_AWARENESS] !=0;
}

/************************************************************************/
/* Parameters Get behaviors                                             */
/************************************************************************/


EXPORT int getParam_Strength(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_STRENGTH] + cr.Params[ST_STRENGTH_EXT];
	if(cr.Params[PE_ADRENALINE_RUSH] && getParam_Timeout(cr, TO_BATTLE) && // Adrenaline rush perk
		cr.Params[ST_CURRENT_HP]<=(cr.Params[ST_MAX_LIFE] + cr.Params[ST_STRENGTH] + cr.Params[ST_ENDURANCE] * 2) * 2 / 3) val+=2;
	if(cr.Params[TRAIT_NIGHT_PERSON]) val +=GetNightPersonBonus();
	return CLAMP(val, 1, 15);
}

EXPORT int getParam_Perception(CritterMutual& cr, uint)
{
	int val=(cr.Params[DAMAGE_EYE] ? 1 : cr.Params[ST_PERCEPTION] + cr.Params[ST_PERCEPTION_EXT]);
	if(cr.Params[TRAIT_NIGHT_PERSON]) val +=GetNightPersonBonus();
	return CLAMP(val, 1, 15);
}

EXPORT int getParam_Endurance(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_ENDURANCE] + cr.Params[ST_ENDURANCE_EXT];
	return CLAMP(val, 1, 15);
}

EXPORT int getParam_Charisma(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_CHARISMA] + cr.Params[ST_CHARISMA_EXT];
	return CLAMP(val, 1, 15);
}

EXPORT int getParam_Intellegence(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_INTELLECT] + cr.Params[ST_INTELLECT_EXT];
	return CLAMP(val, 1, 15);
}

EXPORT int getParam_Agility(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_AGILITY] + cr.Params[ST_AGILITY_EXT];
	if(cr.Params[TRAIT_NIGHT_PERSON]) val +=GetNightPersonBonus();
	return CLAMP(val,1,15);
}

EXPORT int getParam_Luck(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_LUCK] + cr.Params[ST_LUCK_EXT];
	return CLAMP(val, 1, 15);
}

EXPORT int getParam_Hp(CritterMutual& cr, uint)
{
	return cr.Params[ST_CURRENT_HP];
}

EXPORT int getParam_MaxLife(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_MAX_LIFE] + cr.Params[ST_MAX_LIFE_EXT] + cr.Params[ST_STRENGTH] + cr.Params[ST_ENDURANCE] * 2;
	return CLAMP(val, 1, 9999);
}

EXPORT int getParam_MaxAp(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_ACTION_POINTS] + cr.Params[ST_ACTION_POINTS_EXT] + getParam_Agility(cr, 0) / 2;
		if(cr.Params[PE_ADRENALINE_RUSH] && getParam_Timeout(cr, TO_BATTLE) && // Adrenaline rush perk
		cr.Params[ST_CURRENT_HP]<=(cr.Params[ST_MAX_LIFE] + cr.Params[ST_STRENGTH] + cr.Params[ST_ENDURANCE] * 2) / 3) val+=1;
	return CLAMP(val, 1, 9999);
}

EXPORT int getParam_Ap(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_CURRENT_AP];
	val /=AP_DIVIDER;
	return CLAMP(val, -9999, 9999);
}

EXPORT int getParam_MaxMoveAp(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_MAX_MOVE_AP];
	return CLAMP(val, 0, 9999);
}

EXPORT int getParam_MoveAp(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_MOVE_AP];
	return CLAMP(val, 0, 9999);
}

EXPORT int getParam_MaxWeight(CritterMutual& cr, uint)
{
	int val=max(cr.Params[ST_CARRY_WEIGHT] + cr.Params[ST_CARRY_WEIGHT_EXT], 0);
	val +=CONVERT_GRAMM(141 + getParam_Strength(cr, 0) * 13);
	return CLAMP(val, 0, 2000000000);
}

EXPORT int getParam_Sequence(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_SEQUENCE] + cr.Params[ST_SEQUENCE_EXT] + getParam_Perception(cr, 0) * 2;
	return CLAMP(val, 0, 9999);
}

EXPORT int getParam_MeleeDmg(CritterMutual& cr, uint)
{
	int strength=getParam_Strength(cr, 0);
	int bonus=(cr.Params[SK_UNARMED]>cr.Params[SK_MELEE_WEAPONS]?cr.Params[SK_UNARMED]:cr.Params[SK_MELEE_WEAPONS]);
	int val=cr.Params[ST_MELEE_DAMAGE] + cr.Params[ST_MELEE_DAMAGE_EXT]+(strength > 6 ? ((strength - 5)*2) : 1) + (bonus>100?((bonus-80)/(12-(bonus/100))):0);
	return CLAMP(val, 1, 9999);
}


EXPORT int getParam_ThrowingDmg(CritterMutual& cr, uint)
{
	int strength=getParam_Strength(cr, 0);
	int val=(strength > 6 ? (strength - 5)*2 : 1) + (cr.Params[SK_THROWING]>100?((cr.Params[SK_THROWING]-80)/(12-(cr.Params[SK_THROWING]/100))):0);
	return CLAMP(val, 1, 9999);
}

EXPORT int getParam_HealingRate(CritterMutual& cr, uint)
{
	int e=getParam_Endurance(cr, 0);
	int s=getParam_Strength(cr, 0);
	int val=max(1, e/2 + s/3) + cr.Params[ST_HEALING_RATE] + cr.Params[ST_HEALING_RATE_EXT];
	if(cr.Params[PE_ADRENALINE_RUSH] && getParam_Timeout(cr, TO_BATTLE) && // Adrenaline rush perk
	cr.Params[ST_CURRENT_HP]<=(cr.Params[ST_MAX_LIFE] + cr.Params[ST_STRENGTH] + cr.Params[ST_ENDURANCE] * 2) / 2) val+=8;
	
	if(cr.Params[TRAIT_NIGHT_PERSON]!=0)
	{
		if(GetNightPersonBonus()==1) val *=2;
		else if(GetNightPersonBonus()==-1)val/=2;
	}
	
	return CLAMP(val, 0, 9999);
}

EXPORT int getParam_CriticalChance(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_CRITICAL_CHANCE] + cr.Params[ST_CRITICAL_CHANCE_EXT] + getParam_Luck(cr, 0);
	return CLAMP(val, 0, 100);
}

EXPORT int getParam_MaxCritical(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_MAX_CRITICAL] + cr.Params[ST_MAX_CRITICAL_EXT];
	return CLAMP(val, -100, 100);
}

EXPORT int getParam_Ac(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_ARMOR_CLASS] + cr.Params[ST_ARMOR_CLASS_EXT] + getParam_Agility(cr, 0)*2 /*+ cr.Params[ST_TURN_BASED_AC]*/;
	Item* armor=cr.ItemSlotArmor;
	Item* weapon=cr.ItemSlotMain;
	/*if(cr.Params[PE_HTH_EVADE]!=0)
	{
		int skill=SKILL_OFFSET(weapon->Proto->Weapon_Skill[0 & 7]);
		if(skill==SK_UNARMED && getParam_Ap(cr, 0)>0) val+=getParam_Ap(cr, 0)*2+cr.Params[SK_UNARMED]/15;
	}
	else val+=getParam_Ap(cr, 0);*/
	if(armor->GetId() && armor->IsArmor()) val +=armor->Proto->Armor_AC * (100 - armor->GetDeteriorationProc()) / 100;

	return CLAMP(val, 0, 285);
}

EXPORT int getParam_DamageResistance(CritterMutual& cr, uint index)
{
	int dmgType=index - ST_NORMAL_RESIST + 1;

	Item* armor=cr.ItemSlotArmor;
	int val=0;
	int drVal=0;
	switch(dmgType)
	{
	case DAMAGE_NORMAL:   val=cr.Params[ST_NORMAL_RESIST]  + cr.Params[ST_NORMAL_RESIST_EXT];  drVal=armor->Proto->Armor_DRNormal;  break;
	case DAMAGE_LASER:    val=cr.Params[ST_LASER_RESIST]   + cr.Params[ST_LASER_RESIST_EXT];   drVal=armor->Proto->Armor_DRLaser;   break;
	case DAMAGE_FIRE:     val=cr.Params[ST_FIRE_RESIST]    + cr.Params[ST_FIRE_RESIST_EXT];    drVal=armor->Proto->Armor_DRFire;    break;
	case DAMAGE_PLASMA:   val=cr.Params[ST_PLASMA_RESIST]  + cr.Params[ST_PLASMA_RESIST_EXT];  drVal=armor->Proto->Armor_DRPlasma;  break;
	case DAMAGE_ELECTR:   val=cr.Params[ST_ELECTRO_RESIST] + cr.Params[ST_ELECTRO_RESIST_EXT]; drVal=armor->Proto->Armor_DRElectr;  break;
	case DAMAGE_EMP:      val=cr.Params[ST_EMP_RESIST]     + cr.Params[ST_EMP_RESIST_EXT];     drVal=armor->Proto->Armor_DREmp;     break;
	case DAMAGE_EXPLODE:  val=cr.Params[ST_EXPLODE_RESIST] + cr.Params[ST_EXPLODE_RESIST_EXT]; drVal=armor->Proto->Armor_DRExplode; break;
	case DAMAGE_UNCALLED:
	default: break;
	}

	if(armor->GetId() && armor->IsArmor()) val +=drVal * (100 - armor->GetDeteriorationProc()) / 100;

	if(dmgType==DAMAGE_EMP) return CLAMP(val, 0, 999);
	return CLAMP(val, 0, 90);
}

EXPORT int getParam_DamageThreshold(CritterMutual& cr, uint index)
{
	int dmgType=index - ST_NORMAL_ABSORB + 1;

	Item* armor=cr.ItemSlotArmor;
	int val=0;
	int dtVal=0;
	switch(dmgType)
	{
	case DAMAGE_NORMAL:   val=cr.Params[ST_NORMAL_ABSORB]  + cr.Params[ST_NORMAL_ABSORB_EXT];  dtVal=armor->Proto->Armor_DTNormal;  break;
	case DAMAGE_LASER:    val=cr.Params[ST_LASER_ABSORB]   + cr.Params[ST_LASER_ABSORB_EXT];   dtVal=armor->Proto->Armor_DTLaser;   break;
	case DAMAGE_FIRE:     val=cr.Params[ST_FIRE_ABSORB]    + cr.Params[ST_FIRE_ABSORB_EXT];    dtVal=armor->Proto->Armor_DTFire;    break;
	case DAMAGE_PLASMA:   val=cr.Params[ST_PLASMA_ABSORB]  + cr.Params[ST_PLASMA_ABSORB_EXT];  dtVal=armor->Proto->Armor_DTPlasma;  break;
	case DAMAGE_ELECTR:   val=cr.Params[ST_ELECTRO_ABSORB] + cr.Params[ST_ELECTRO_ABSORB_EXT]; dtVal=armor->Proto->Armor_DTElectr;  break;
	case DAMAGE_EMP:      val=cr.Params[ST_EMP_ABSORB]     + cr.Params[ST_EMP_ABSORB_EXT];     dtVal=armor->Proto->Armor_DTEmp;     break;
	case DAMAGE_EXPLODE:  val=cr.Params[ST_EXPLODE_ABSORB] + cr.Params[ST_EXPLODE_ABSORB_EXT]; dtVal=armor->Proto->Armor_DTExplode; break;
	case DAMAGE_UNCALLED:
	default: break;
	}

	if(armor->GetId() && armor->IsArmor()) val +=dtVal * (100 - armor->GetDeteriorationProc()) / 100;

	return CLAMP(val, 0, 999);
}

EXPORT int getParam_RadiationResist(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_RADIATION_RESISTANCE] + cr.Params[ST_RADIATION_RESISTANCE_EXT] + getParam_Endurance(cr, 0) * 2;
	return CLAMP(val, 0, 95);
}

EXPORT int getParam_PoisonResist(CritterMutual& cr, uint)
{
	int val=cr.Params[ST_POISON_RESISTANCE] + cr.Params[ST_POISON_RESISTANCE_EXT] + getParam_Endurance(cr, 0) * 5;
	return CLAMP(val, 0, 95);
}

EXPORT int getParam_Timeout(CritterMutual& cr, uint index)
{
	return (uint)cr.Params[index] > Game->FullSecond ? (uint)cr.Params[index] - Game->FullSecond : 0;
}

EXPORT int getParam_Reputation(CritterMutual& cr, uint index)
{
#ifdef __SERVER
	if(cr.Params[index]==0x80000000)
	{
		Game->CritterChangeParameter(cr, index);
		cr.Params[index]=0;
	}
#endif
#ifdef __CLIENT
	if(cr.Params[index]==0x80000000) return 0;
#endif
	return cr.Params[index];
}

EXPORT void changedParam_Reputation(CritterMutual& cr, uint index, int oldValue)
{
	if(oldValue==0x80000000) cr.Params[index] +=0x80000000;
}

/************************************************************************/
/* Extended methods                                                     */
/************************************************************************/

EXPORT bool Critter_IsInjured(CritterMutual& cr)
{
	return Critter_IsDmgArm(cr) || Critter_IsDmgLeg(cr) || Critter_IsDmgEye(cr);
}

EXPORT bool Critter_IsDmgEye(CritterMutual& cr)
{
	return cr.Params[DAMAGE_EYE] !=0;
}

EXPORT bool Critter_IsDmgLeg(CritterMutual& cr)
{
	return cr.Params[DAMAGE_RIGHT_LEG] || cr.Params[DAMAGE_LEFT_LEG];
}

EXPORT bool Critter_IsDmgTwoLeg(CritterMutual& cr)
{
	return cr.Params[DAMAGE_RIGHT_LEG] && cr.Params[DAMAGE_LEFT_LEG];
}

EXPORT bool Critter_IsDmgArm(CritterMutual& cr)
{
	return cr.Params[DAMAGE_RIGHT_ARM] || cr.Params[DAMAGE_LEFT_ARM];
}

EXPORT bool Critter_IsDmgTwoArm(CritterMutual& cr)
{
	return cr.Params[DAMAGE_RIGHT_ARM] && cr.Params[DAMAGE_LEFT_ARM];
}

EXPORT bool Critter_IsAddicted(CritterMutual& cr)
{
	for(uint i=ADDICTION_BEGIN; i<=ADDICTION_END; i++)
		if(cr.Params[i]) return true;
	return false;
}

EXPORT bool Critter_IsOverweight(CritterMutual& cr)
{
	// Calculate inventory items weight
	uint w=0;
	for(ItemVecIt it=cr.InvItems.begin(), end=cr.InvItems.end(); it !=end; ++it)
		w +=(*it)->GetWeight();

	return w > (uint)getParam_MaxWeight(cr, 0);
}

EXPORT bool Item_Weapon_IsHtHAttack(Item& item, uint8 mode)
{
	if(!item.IsWeapon() || !item.WeapIsUseAviable(mode & 7)) return false;
	int skill=SKILL_OFFSET(item.Proto->Weapon_Skill[mode & 7]);
	return skill==SK_UNARMED || skill==SK_MELEE_WEAPONS;
}

EXPORT bool Item_Weapon_IsGunAttack(Item& item, uint8 mode)
{
	if(!item.IsWeapon() || !item.WeapIsUseAviable(mode & 7)) return false;
	int skill=SKILL_OFFSET(item.Proto->Weapon_Skill[mode & 7]);
	return skill==SK_SMALL_GUNS || skill==SK_BIG_GUNS || skill==SK_ENERGY_WEAPONS;
}

EXPORT bool Item_Weapon_IsRangedAttack(Item& item, uint8 mode)
{
	if(!item.IsWeapon() || !item.WeapIsUseAviable(mode & 7)) return false;
	int skill=SKILL_OFFSET(item.Proto->Weapon_Skill[mode & 7]);
	return skill==SK_DOCTOR || skill==SK_SMALL_GUNS || skill==SK_BIG_GUNS || skill==SK_ENERGY_WEAPONS || skill==SK_THROWING;
}

/************************************************************************/
/* Callbacks                                                            */
/************************************************************************/

uint GetUseApCost(CritterMutual& cr, Item& item, uint8 mode)
{
	uint8 use=mode & 0xF;
	uint8 aim=mode >> 4;
	int apCost=0;

	if(use==USE_USE)
	{
		return Game->RtApCostUseItem;
	}
	
	if(use==USE_RELOAD)
	{
		if(item.IsWeapon()) apCost=item.Proto->Weapon_ReloadAp;
		if(item.IsWeapon() && item.Proto->Weapon_Perk==WEAPON_PERK_FAST_RELOAD && apCost>0) apCost--;
		return apCost;
	}
	
    if(use >=USE_PRIMARY && use<=USE_THIRD && item.IsWeapon())
	{
		int skill=item.Proto->Weapon_Skill[use];
		bool hthAttack=Item_Weapon_IsHtHAttack(item, mode);
		bool rangedAttack=Item_Weapon_IsRangedAttack(item, mode);
		bool isGun=Item_Weapon_IsGunAttack(item, mode);
		apCost=item.Proto->Weapon_ApCost[use];
#ifdef __SERVER
		if(aim) apCost +=GetAimApCost(aim);
#endif
#ifdef __CLIENT
		if(item.Proto->Weapon_Aim[use] && *GlobalVars.AutoAim) apCost++;
#endif
		if(hthAttack && cr.Params[PE_BONUS_HTH_ATTACKS]) apCost--;
		if(rangedAttack && cr.Params[PE_BONUS_RATE_OF_FIRE]) apCost--;
		if(cr.Params[TRAIT_FAST_SHOT] && isGun) apCost--;
	}

	return apCost;
}

uint GetAttackDistantion(CritterMutual& cr, Item& item, uint8 mode)
{
	uint8 use=mode & 0xF;
	int dist=item.Proto->Weapon_MaxDist[use];
	int strength=getParam_Strength(cr, 0);
	if(item.Proto->Weapon_Skill[use]==SKILL_OFFSET(SK_THROWING)) dist=min(dist, 3 * min(10, strength + 2 * cr.Params[PE_HEAVE_HO]));
	if(Item_Weapon_IsHtHAttack(item, mode) && cr.Params[MODE_RANGE_HTH]) dist++;
	dist +=GetMultihex(cr);
	if(dist<0) dist=0;
	return dist;
}

/************************************************************************/
/* Generic stuff                                                        */
/************************************************************************/

int GetNightPersonBonus()
{
	if(Game->Hour<5 || Game->Hour > 21) return 1;
	if(Game->Hour==5) return 1;
	if(Game->Hour==21) return 1;
	if((Game->Hour > 5 && Game->Hour<9) || (Game->Hour<21 && Game->Hour > 17)) return 0;
	return -1;
}

uint GetAimApCost(int hitLocation)
{
	switch(hitLocation)
	{
	case HIT_LOCATION_TORSO:     return Game->ApCostAimTorso;
	case HIT_LOCATION_EYES:      return Game->ApCostAimEyes;
	case HIT_LOCATION_HEAD:      return Game->ApCostAimHead;
	case HIT_LOCATION_LEFT_ARM:
	case HIT_LOCATION_RIGHT_ARM: return Game->ApCostAimArms;
	case HIT_LOCATION_GROIN:     return Game->ApCostAimGroin;
	case HIT_LOCATION_RIGHT_LEG:
	case HIT_LOCATION_LEFT_LEG:  return Game->ApCostAimLegs;
	case HIT_LOCATION_NONE:
	case HIT_LOCATION_UNCALLED:
	default: break;
	}
	return 0;
}

uint GetAimHit(int hitLocation)
{
	switch(hitLocation)
	{
	case HIT_LOCATION_TORSO:     return *GlobalVars.HitAimTorso;
	case HIT_LOCATION_EYES:      return *GlobalVars.HitAimEyes;
	case HIT_LOCATION_HEAD:      return *GlobalVars.HitAimHead;
	case HIT_LOCATION_LEFT_ARM:
	case HIT_LOCATION_RIGHT_ARM: return *GlobalVars.HitAimArms;
	case HIT_LOCATION_GROIN:     return *GlobalVars.HitAimGroin;
	case HIT_LOCATION_RIGHT_LEG:
	case HIT_LOCATION_LEFT_LEG:  return *GlobalVars.HitAimLegs;
	case HIT_LOCATION_NONE:
	case HIT_LOCATION_UNCALLED:
	default: break;
	}
	return 0;
}

uint GetMultihex(CritterMutual& cr)
{
	int mh=cr.Multihex;
	if(mh<0) mh=Game->CritterTypes[cr.BaseType].Multihex;
	return CLAMP(mh, 0, MAX_HEX_OFFSET);
}

#ifdef __SERVER

EXPORT bool Map_IsRoof(Map& map, uint16 hexX, uint16 hexY);
EXPORT uint Map_CountTile(Map& map, uint16& roofCount, uint16& GrandCount);

uint Map_CountTile(Map& map, uint16& roofCount, uint16& GrandCount)
{
	roofCount=0;
	GrandCount=0;
	for(uint i=0; i<map.Proto->Tiles.size();i++)
	{
		if(map.Proto->Tiles[i].IsRoof)
		{
			roofCount+=1;
		}
		else GrandCount+=1;
	}
	return (map.Proto->Tiles.size());
}

bool Map_IsRoof(Map& map, uint16 hexX, uint16 hexY)
{
	for(uint i=0; i<map.Proto->Tiles.size();i++)
	{
		uint16 hx=map.Proto->Tiles[i].HexX;
		uint16 hy=map.Proto->Tiles[i].HexY;
		if(hx==hexX)
		{
			if(hy==hexY)
			{
				if(map.Proto->Tiles[i].IsRoof)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Map_GetExitGrid(Map& map, CritterMutual& cr, uint16& x, uint16& y,uint16& MapPid, uint& EntireId)
{
	for(MapObjectVecIt it=map.Proto->GridsVec.begin(), end=map.Proto->GridsVec.end();it!=end;++it)
	{
		MapObject* grid=*it;
		if(x==0 && y==0)
		{
			MapPid=grid->MScenery.ToMapPid;
			EntireId=grid->MScenery.ToEntire;
			x=grid->MapX;
			y=grid->MapY;
		}
		else if(GetDistantion(x, y, cr.HexX, cr.HexY) > GetDistantion(grid->MapX, grid->MapY, cr.HexX, cr.HexY))
		{
			MapPid=grid->MScenery.ToMapPid;
			EntireId=grid->MScenery.ToEntire;
			x=grid->MapX;
			y=grid->MapY;
		}
	}
}

void Map_GetExitGlobalGrid(Map& map, CritterMutual& cr,uint16& x, uint16& y)
{
	for(MapObjectVecIt it=map.Proto->GridsVec.begin(), end=map.Proto->GridsVec.end();it!=end;++it)
	{
		MapObject* grid=*it;
		if(grid->ProtoId==2049)
		{
			if(grid->MScenery.ToMapPid==0 && grid->MScenery.ToEntire==0)
			{
				if(x==0 && y==0)
				{
					x=grid->MapX;
					y=grid->MapY;
				}
				else if(GetDistantion(x, y, cr.HexX, cr.HexY) > GetDistantion(grid->MapX, grid->MapY, cr.HexX, cr.HexY))
				{
					x=grid->MapX;
					y=grid->MapY;
				}
			}
		}
	}
}

int MakeBackup(ScriptString* parameters)
{
	return (int)ShellExecute(NULL,NULL,"7za.exe",(LPCTSTR)parameters->Buffer.c_str(),NULL,3);
}

bool FileDelete(ScriptString* filename)
{
	if(DeleteFile(filename->Buffer.c_str())) return true;
	else return false;
}

bool check_look(Map& map, Critter& cr, Critter& opponent)
{
	if(opponent.Params[MODE_HIDE]==1 && !opponent.CritterIsNpc && ((Client*)&opponent)->Access==ACCESS_ADMIN) return false;
	int dist=GetDistantion(cr.HexX, cr.HexY, opponent.HexX, opponent.HexY);
	if(dist<=3+cr.Params[PE_SHARPSHOOTER]*3) return true;
	uint16 hour=0;
	if(cr.Params[ST_CURRENT_MAP_TIME]<1) hour=Game->Hour;
	else hour=cr.Params[ST_CURRENT_MAP_TIME]/60;
	
	float Z;	
	if(cr.Params[PE_NIGHT_VISION]==0)
		if(hour>=9 && hour<17) Z=(float)1.2;
		else if(hour>=21 || hour<5) Z=(float)0.8;
		else if(hour<10) Z=(float)(0.9+((hour-4.0)/20.0));
		else Z=(float)(1.2-(hour-16.0)/10.0);
	else 
		if(hour>=9 && hour<17) Z=(float)1.2;
		else if(hour>=21 || hour<5) Z=(float)1.0;
		else if(hour<10) Z=(float)(1.0+((hour-4.0)/20.0));
		else Z=(float)(1.2-(hour-16.0)/20.0);

	int visibleDist=CLAMP((20+(getParam_Perception(cr, 0)+cr.Params[PE_SHARPSHOOTER]*2)*3)*Z, 1, 70);
	if(opponent.Params[MODE_HIDE]==0)
	{
		if(visibleDist>=dist) return true;
		else return false;
	}
	else
	{
		int D=0;
		if(opponent.Params[PE_GHOST]==1)
		{
			if(hour>=21 || hour<5) D=40;
			else if(hour>=17 && hour<21 || hour>=5 && hour<10) D=20;
		}
		float SneakPenalty=0;
		int SneakBonus=0;
		int LookBonus=0;
		for(ItemVecIt it=opponent.InvItems.begin(), end=opponent.InvItems.end(); it !=end; ++it)
		{
			Item* item=*it;
			if(item->GetProtoId()==210) SneakBonus=2;
			if(!item->IsHidden())
			{
				uint volume=item->GetVolume();
				uint count=item->GetCount();
				if(volume==0)
				{
					SneakPenalty+=(float)0.2*count;
				}
				else if(volume/count==1)
				{
					SneakPenalty+=(float)4*count;
				}
				else if(volume/count==2)
				{
					 SneakPenalty+=(float)15*count;
				}
				else if(volume/count==3)
				{
					SneakPenalty+=(float)30*count;
				}
				else if(volume/count==4)
				{
					SneakPenalty+=(float)50*count;
				}
				else if(volume/count==5)
				{
					SneakPenalty+=(float)100*count;
				}
				else
				{
					SneakPenalty+=(float)150;
				}
			}
		}
		for(ItemVecIt it=cr.InvItems.begin(), end=cr.InvItems.end(); it !=end; ++it)
		{
			Item* item=*it;
			if(item->GetProtoId()==59) LookBonus=2;
		}
		if(visibleDist - ((opponent.Params[SK_SNEAK]+D-SneakPenalty)/6) >=dist) return true;
		else return false;
	}
	return false;
}
#endif
#ifdef __CLIENT

EXPORT int getParam_VisibleDist(CritterMutual& cr, uint)
{
	uint16 hour=0;
	if(cr.Params[ST_CURRENT_MAP_TIME]<1) hour=Game->Hour;
	else hour=(uint16)cr.Params[ST_CURRENT_MAP_TIME]/60;
	
	float Z;
	if(cr.Params[PE_NIGHT_VISION]==0)
		if(hour>=9 && hour<17) Z=(float)1.2;
		else if(hour>=21 || hour<5) Z=(float)0.8;
		else if(hour<10) Z=(float)(0.9+((hour-4.0)/20.0));
		else Z=(float)(1.2-(hour-16.0)/10.0);
	else 
		if(hour>=9 && hour<17) Z=(float)1.2;
		else if(hour>=21 || hour<5) Z=(float)1.0;
		else if(hour<10) Z=(float)(1.0+((hour-4.0)/20.0));
		else Z=(float)(1.2-(hour-16.0)/20.0);

	int val=CLAMP((20+(getParam_Perception(cr, 0)+cr.Params[PE_SHARPSHOOTER]*2)*3)*Z, 1, 70);
	return val;
}

bool ClientIsFocused()
{
	return FindWindow(NULL,"FOnline")==GetForegroundWindow();
}

void ChangeClientParam(CritterCl& cr, int param, int val)
{
	cr.Params[param]=val;
}

unsigned int GetOnline(ScriptString* serverIp, uint serverPort)
{
	WSADATA wsaData;
	int err=WSAStartup(MAKEWORD(1, 1), &wsaData);
	if(err !=0)
	{
		return 4000000000;
	}
	SOCKET sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	struct sockaddr_in  serv_addr;
	
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(serverPort);
	
	if((serv_addr.sin_addr.s_addr=inet_addr(serverIp->Buffer.c_str()))==-1)
        {
            hostent* h=gethostbyname(serverIp->Buffer.c_str());
			memcpy(&serv_addr.sin_addr,h->h_addr,sizeof(in_addr));
		}			
	
	if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==0)
	{
		char sendPacket[4]={(char)255,(char)255,(char)255,(char)255};
		char recvPacket[16];
		send(sock, sendPacket, 4, 0);
		recv(sock, recvPacket, 16,0);
		unsigned int retValue=*(unsigned int*)&recvPacket[0];
		closesocket(sock);
		return retValue;
	}
	else return 4000000000;
}

void FocusClient()
{
	SetFocus(FindWindow(NULL,"FOnline"));
}

void FlashClient()
{
	FLASHWINFO fwinfo;
	fwinfo.hwnd=FindWindow(NULL,"FOnline");
	fwinfo.cbSize=sizeof(FLASHWINFO);
	fwinfo.dwFlags=FLASHW_ALL;
	fwinfo.uCount=10;
	fwinfo.dwTimeout=200;
	FlashWindowEx(&fwinfo);
}
#endif
/************************************************************************/
/*                                                                      */
/************************************************************************/
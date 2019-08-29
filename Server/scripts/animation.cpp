#include "_animation.fos"

EXPORT bool critter_animation_substitute( int animType, uint crTypeBase, uint anim1Base, uint anim2Base, uint& crType, uint& anim1, uint& anim2 )
{
    // Unset shield (Arcanum animations)
    if( ( anim1 & ANIM1_SHIELD ) != 0 )
    {
        anim1 ^= ANIM1_SHIELD;
        return true;
    }

    // Check crType alias
    if( crTypeBase != 0 )  // Zero for 3d animations
    {
        uint crTypeAlias = FOnline->CritterTypes[ crTypeBase ].Alias;
        if( crType == crTypeBase && crType != crTypeAlias )
        {
            switch( anim2 )
            {
            case ANIM2_DEAD_PULSE:
            case ANIM2_DEAD_PULSE_DUST:
            case ANIM2_DEAD_BURN:
            case ANIM2_DEAD_BURN_RUN:
                crType = crTypeAlias;
                return true;
            default:
                break;
            }
        }
    }
    crType = crTypeBase;

    // Check Unarmed specific substitute
    if( ( anim1 & ANIM1_WEAPON_MASK ) == ANIM1_UNARMED )
    {
        bool swapped = true;
        switch( anim2 )
        {
        case ANIM2_LIMP:
            anim2 = ANIM2_WALK;
            break;
        case ANIM2_RUN:
            anim2 = ANIM2_WALK;
            break;
        case ANIM2_PANIC_RUN:
            anim2 = ANIM2_RUN;
            break;
        case ANIM2_SNEAK_WALK:
            anim2 = ANIM2_WALK;
            break;
        case ANIM2_SNEAK_RUN:
            anim2 = ANIM2_SNEAK_WALK;
            break;
        case ANIM2_PICKUP:
            anim2 = ANIM2_USE;
            break;
        case ANIM2_SWITCH_ITEMS:
            anim2 = ANIM2_USE;
            break;
        default:
            swapped = false;
            break;
        }
        if( swapped )
            return true;
    }

    // Check anim2 substitute
    bool swapped = true;
    switch( anim2 )
    {
    case ANIM2_IDLE_STUNNED:
        anim2 = ANIM2_IDLE;
        break;
    case ANIM2_IDLE_COMBAT:
        anim2 = ANIM2_IDLE;
        break;
    case ANIM2_CLIMBING:
        anim2 = ANIM2_USE;
        break;
    case ANIM2_PUNCH_LEFT:
        anim2 = ANIM2_PUNCH_RIGHT;
        break;
    case ANIM2_PUNCH_COMBO:
        anim2 = ANIM2_PUNCH_LEFT;
        break;
    case ANIM2_KICK_HI:
        anim2 = ANIM2_PUNCH_RIGHT;
        break;
    case ANIM2_KICK_LO:
        anim2 = ANIM2_KICK_HI;
        break;
    case ANIM2_KICK_COMBO:
        anim2 = ANIM2_KICK_HI;
        break;
    case ANIM2_SWING_1H:
        anim2 = ANIM2_THRUST_1H;
        break;
    case ANIM2_THRUST_2H:
        anim2 = ANIM2_THRUST_1H;
        break;
    case ANIM2_SWING_2H:
        anim2 = ANIM2_SWING_1H;
        break;
    case ANIM2_SWEEP:
        anim2 = ANIM2_BURST;
        break;
    case ANIM2_BURST:
        anim2 = ANIM2_SINGLE;
        break;
    case ANIM2_BUTT:
        anim2 = ANIM2_PUNCH_RIGHT;
        break;
    case ANIM2_FLAME:
        anim2 = ANIM2_SINGLE;
        break;
    case ANIM2_NO_RECOIL:
        anim2 = ANIM2_USE;
        break;
    case ANIM2_THROW:
        anim2 = ANIM2_PUNCH_RIGHT;
        break;
    case ANIM2_RELOAD:
        anim2 = ANIM2_USE;
        break;
    case ANIM2_REPAIR:
        anim2 = ANIM2_RELOAD;
        break;
    case ANIM2_DODGE_BACK:
        anim2 = ANIM2_DODGE_FRONT;
        break;
    case ANIM2_DAMAGE_BACK:
        anim2 = ANIM2_DAMAGE_FRONT;
        break;
    case ANIM2_DAMAGE_MUL_BACK:
        anim2 = ANIM2_DAMAGE_MUL_FRONT;
        break;
    case ANIM2_WALK_DAMAGE_BACK:
        anim2 = ANIM2_WALK_DAMAGE_FRONT;
        break;
    case ANIM2_LIMP_DAMAGE_BACK:
        anim2 = ANIM2_LIMP_DAMAGE_FRONT;
        break;
    case ANIM2_RUN_DAMAGE_BACK:
        anim2 = ANIM2_RUN_DAMAGE_FRONT;
        break;
    case ANIM2_LOOT:
        anim2 = ANIM2_PICKUP;
        break;
    case ANIM2_STEAL:
        anim2 = ANIM2_USE;
        break;
    case ANIM2_PUSH:
        anim2 = ANIM2_PUNCH_RIGHT;
        break;
    case ANIM2_SHOW_WEAPON:
        anim2 = ANIM2_USE;
        break;
    case ANIM2_HIDE_WEAPON:
        anim2 = ANIM2_USE;
        break;

    case ANIM2_KNOCK_BACK:
        anim2 = ANIM2_KNOCK_FRONT;
        break;
    case ANIM2_LAYDOWN_BACK:
        anim2 = ANIM2_LAYDOWN_FRONT;
        break;
    case ANIM2_IDLE_PRONE_BACK:
        anim2 = ANIM2_IDLE_PRONE_FRONT;
        break;
    case ANIM2_STANDUP_BACK:
        anim2 = ANIM2_STANDUP_FRONT;
        break;
    case ANIM2_DEAD_PRONE_BACK:
        anim2 = ANIM2_DEAD_PRONE_FRONT;
        break;
    case ANIM2_DAMAGE_PRONE_BACK:
        anim2 = ANIM2_DAMAGE_PRONE_FRONT;
        break;
    case ANIM2_DAMAGE_MUL_PRONE_BACK:
        anim2 = ANIM2_DAMAGE_MUL_PRONE_FRONT;
        break;
    case ANIM2_TWITCH_PRONE_BACK:
        anim2 = ANIM2_TWITCH_PRONE_FRONT;
        break;

    case ANIM2_DEAD_FRONT:
        anim2 = ANIM2_KNOCK_FRONT;
        break;
    case ANIM2_DEAD_BACK:
        anim2 = ANIM2_KNOCK_BACK;
        break;
    case ANIM2_DEAD_BLOODY_SINGLE:
    case ANIM2_DEAD_BLOODY_BURST:
    case ANIM2_DEAD_BURST:
    case ANIM2_DEAD_PULSE:
    case ANIM2_DEAD_PULSE_DUST:
    case ANIM2_DEAD_LASER:
    case ANIM2_DEAD_FUSED:
    case ANIM2_DEAD_EXPLODE:
    case ANIM2_DEAD_BURN:
    case ANIM2_DEAD_BURN_RUN:
        anim2 = ANIM2_DEAD_FRONT;
        break;

    default:
        swapped = false;
        break;
    }
    if( swapped )
        return true;

    // Restore anim2
    anim2 = anim2Base;

    // Find anim1 substitute
    uint flags = anim1 & ANIM1_FLAGS_MASK; // Store flags
    anim1 &= ANIM1_WEAPON_MASK;            // Keep only weapon
    switch( anim1 )
    {
    case ANIM1_KNIFE:
        anim1 = ANIM1_UNARMED;
        break;
    case ANIM1_CLUB:
        anim1 = ANIM1_KNIFE;
        break;
    case ANIM1_HAMMER:
        anim1 = ANIM1_CLUB;
        break;
    case ANIM1_SPEAR:
        anim1 = ANIM1_KNIFE;
        break;
    case ANIM1_PISTOL:
        anim1 = ANIM1_UNARMED;
        break;
    case ANIM1_SMG:
        anim1 = ANIM1_PISTOL;
        break;
    case ANIM1_SHOOTGUN:
        anim1 = ANIM1_SMG;
        break;
    case ANIM1_RIFLE:
        anim1 = ANIM1_SHOOTGUN;
        break;
    case ANIM1_MINIGUN:
        anim1 = ANIM1_RIFLE;
        break;
    case ANIM1_ROCKET_LAUNCHER:
        anim1 = ANIM1_MINIGUN;
        break;
    case ANIM1_FLAMER:
        anim1 = ANIM1_ROCKET_LAUNCHER;
        break;
    case ANIM1_HEAVY_RIFLE:
        anim1 = ANIM1_RIFLE;
        break;
    case ANIM1_SWORD:
        anim1 = ANIM1_KNIFE;
        break;
    case ANIM1_LONG_SWORD:
        anim1 = ANIM1_KNIFE;
        break;
    case ANIM1_AXE:
        anim1 = ANIM1_HAMMER;
        break;
    case ANIM1_BOW:
        anim1 = ANIM1_KNIFE;
        break;
    default:
        return false;
    }
    anim1 |= flags;    // Merge weapon and flags

    return true;
}

EXPORT bool critter_animation_fallout( uint crType, uint& anim1, uint& anim2, uint& anim1ex, uint& anim2ex, uint& flags )
{
    // Message("AnimFal");
    // Still only weapon
    anim1 &= ANIM1_WEAPON_MASK;

    // Weapon
    switch( anim1 )
    {
    case ANIM1_UNARMED:
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM1_KNIFE:
        anim1 = ANIM1_FALLOUT_KNIFE;
        break;
    case ANIM1_CLUB:
        anim1 = ANIM1_FALLOUT_CLUB;
        break;
    case ANIM1_HAMMER:
        anim1 = ANIM1_FALLOUT_HAMMER;
        break;
    case ANIM1_SPEAR:
        anim1 = ANIM1_FALLOUT_SPEAR;
        break;
    case ANIM1_PISTOL:
        anim1 = ANIM1_FALLOUT_PISTOL;
        break;
    case ANIM1_SMG:
        anim1 = ANIM1_FALLOUT_UZI;
        break;
    case ANIM1_SHOOTGUN:
        anim1 = ANIM1_FALLOUT_SHOOTGUN;
        break;
    case ANIM1_HEAVY_RIFLE:
        anim1 = ANIM1_FALLOUT_RIFLE;
        break;
    case ANIM1_MINIGUN:
        anim1 = ANIM1_FALLOUT_MINIGUN;
        break;
    case ANIM1_ROCKET_LAUNCHER:
        anim1 = ANIM1_FALLOUT_ROCKET_LAUNCHER;
        break;
    case ANIM1_FLAMER:
        anim1 = ANIM1_FALLOUT_RIFLE;
        break;
    case ANIM1_RIFLE:
        anim1 = ANIM1_FALLOUT_RIFLE;
        break;
    case ANIM1_SWORD:
        anim1 = ANIM1_FALLOUT_KNIFE;
        break;
    case ANIM1_LONG_SWORD:
        anim1 = ANIM1_FALLOUT_KNIFE;
        break;
    case ANIM1_AXE:
        anim1 = ANIM1_FALLOUT_CLUB;
        break;
    case ANIM1_BOW:
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    default:
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    }

    // Action
    switch( anim2 )
    {
    case ANIM2_IDLE:
        anim2 = ANIM2_FALLOUT_STAY;
        flags |= ANIM_FLAG_FIRST_FRAME;
        break;
    case ANIM2_IDLE_STUNNED:
        anim2 = ANIM2_FALLOUT_STAY;
        flags |= ANIM_FLAG_FIRST_FRAME;
        break;
    case ANIM2_WALK:
        anim2 = ANIM2_FALLOUT_WALK;
        break;
    case ANIM2_LIMP:
        anim2 = ANIM2_FALLOUT_WALK;
        break;
    case ANIM2_RUN:
        anim2 = ANIM2_FALLOUT_RUN;
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM2_PANIC_RUN:
        anim2 = ANIM2_FALLOUT_RUN;
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM2_SHOW_WEAPON:
        anim2 = ANIM2_FALLOUT_SHOW;
        break;
    case ANIM2_HIDE_WEAPON:
        anim2 = ANIM2_FALLOUT_HIDE;
        break;
    case ANIM2_PREPARE_WEAPON:
        anim2 = ANIM2_FALLOUT_PREPARE_WEAPON;
        break;
    case ANIM2_TURNOFF_WEAPON:
        anim2 = ANIM2_FALLOUT_TURNOFF_WEAPON;
        break;
    case ANIM2_FIDGET:
        anim2 = ANIM2_FALLOUT_STAY;
        break;
//	case ANIM2_CLIMBING:           anim2=;                                                     break;
    case ANIM2_PICKUP:
        anim2 = ANIM2_FALLOUT_PICKUP;
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM2_USE:
        anim2 = ANIM2_FALLOUT_USE;
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM2_SWITCH_ITEMS:
        anim2 = ANIM2_FALLOUT_USE;
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM2_LOOT:
        anim2 = ANIM2_FALLOUT_PICKUP;
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM2_STEAL:
        anim2 = ANIM2_FALLOUT_USE;
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM2_PUSH:
        anim2 = ANIM2_FALLOUT_PUNCH;
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM2_IDLE_COMBAT:
        anim2 = ANIM2_FALLOUT_STAY;
        flags |= ANIM_FLAG_FIRST_FRAME;
        break;
    case ANIM2_PUNCH_RIGHT:
        anim2 = ANIM2_FALLOUT_PUNCH;
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM2_KICK_HI:
        anim2 = ANIM2_FALLOUT_KICK;
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM2_THRUST_1H:
        anim2 = ANIM2_FALLOUT_THRUST;
        break;
    case ANIM2_THRUST_2H:
        anim2 = ANIM2_FALLOUT_THRUST;
        break;
    case ANIM2_SWING_1H:
        anim2 = ANIM2_FALLOUT_SWING;
        break;
    case ANIM2_SWING_2H:
        anim2 = ANIM2_FALLOUT_SWING;
        break;
    case ANIM2_SINGLE:
        anim2 = ANIM2_FALLOUT_SHOOT;
        break;
    case ANIM2_BURST:
        anim2 = ANIM2_FALLOUT_BURST;
        break;
    case ANIM2_SWEEP:
        anim2 = ANIM2_FALLOUT_BURST;
        break;
    case ANIM2_FLAME:
        anim2 = ANIM2_FALLOUT_FLAME;
        break;
    case ANIM2_BUTT:
        anim2 = ANIM2_FALLOUT_PUNCH;
        anim1 = ANIM1_FALLOUT_UNARMED;
        break;
    case ANIM2_THROW:
        anim2 = ( anim1 == ANIM1_FALLOUT_UNARMED ? ANIM2_FALLOUT_THROW_EMPTY : ANIM2_FALLOUT_THROW_WEAPON );
        break;
    case ANIM2_DODGE_FRONT:
        anim2 = ( anim1 == ANIM1_FALLOUT_UNARMED ? ANIM2_FALLOUT_DODGE_EMPTY : ANIM2_FALLOUT_DODGE_WEAPON );
        break;
    case ANIM2_DODGE_BACK:
        anim2 = ( anim1 == ANIM1_FALLOUT_UNARMED ? ANIM2_FALLOUT_DODGE_EMPTY : ANIM2_FALLOUT_DODGE_WEAPON );
        break;
    case ANIM2_DAMAGE_FRONT:
        anim2 = ANIM2_FALLOUT_DAMAGE_FRONT;
        break;
    case ANIM2_DAMAGE_BACK:
        anim2 = ANIM2_FALLOUT_DAMAGE_BACK;
        break;
    case ANIM2_DAMAGE_MUL_FRONT:
        anim2 = ANIM2_FALLOUT_DAMAGE_FRONT;
        break;
    case ANIM2_DAMAGE_MUL_BACK:
        anim2 = ANIM2_FALLOUT_DAMAGE_BACK;
        break;
    case ANIM2_KNOCK_FRONT:
        anim2 = ANIM2_FALLOUT_KNOCK_FRONT;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;
    case ANIM2_KNOCK_BACK:
        anim2 = ANIM2_FALLOUT_KNOCK_BACK;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;
    case ANIM2_STANDUP_FRONT:
        anim2 = ANIM2_FALLOUT_STANDUP_FRONT;
        anim1 = ANIM1_FALLOUT_KNOCKOUT;
        break;
    case ANIM2_STANDUP_BACK:
        anim2 = ANIM2_FALLOUT_STANDUP_BACK;
        anim1 = ANIM1_FALLOUT_KNOCKOUT;
        break;
    case ANIM2_DEAD_PRONE_FRONT:
        anim2 = ANIM2_FALLOUT_DEAD_FRONT2;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;
    case ANIM2_DEAD_PRONE_BACK:
        anim2 = ANIM2_FALLOUT_DEAD_BACK2;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;
    case ANIM2_DEAD_BLOODY_SINGLE:
        anim2 = ANIM2_FALLOUT_DEAD_BLOODY_SINGLE;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;
    case ANIM2_DEAD_BLOODY_BURST:
        anim2 = ANIM2_FALLOUT_DEAD_BLOODY_BURST;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;
    case ANIM2_DEAD_BURST:
        anim2 = ANIM2_FALLOUT_DEAD_BURST;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;
    case ANIM2_DEAD_PULSE:
        anim2 = ANIM2_FALLOUT_DEAD_PULSE;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;
    case ANIM2_DEAD_PULSE_DUST:
        anim2 = ANIM2_FALLOUT_DEAD_PULSE_DUST;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;
    case ANIM2_DEAD_LASER:
        anim2 = ANIM2_FALLOUT_DEAD_LASER;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;
    case ANIM2_DEAD_FUSED:
        anim2 = ANIM2_FALLOUT_DEAD_FUSED;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;
    case ANIM2_DEAD_EXPLODE:
        anim2 = ANIM2_FALLOUT_DEAD_EXPLODE;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;

    case ANIM2_IDLE_PRONE_FRONT:
        anim2 = ANIM2_FALLOUT_KNOCK_FRONT;
        anim1 = ANIM1_FALLOUT_DEAD;
        flags |= ANIM_FLAG_LAST_FRAME;
        break;
    case ANIM2_IDLE_PRONE_BACK:
        anim2 = ANIM2_FALLOUT_KNOCK_BACK;
        anim1 = ANIM1_FALLOUT_DEAD;
        flags |= ANIM_FLAG_LAST_FRAME;
        break;

    case ANIM2_DEAD_BURN:
        anim2 = ANIM2_FALLOUT_DEAD_BURN;
        anim1 = ANIM1_FALLOUT_DEAD;
        break;                                                                                                      // ANIM2_FALLOUT_DEAD_BURN2
    case ANIM2_DEAD_BURN_RUN:
        anim2 = ANIM2_FALLOUT_DEAD_BURN_RUN;
        anim1 = ANIM1_FALLOUT_DEAD;
        anim2ex = ANIM2_FALLOUT_DEAD_BURN;
        anim1ex = ANIM1_FALLOUT_DEAD;
        break;

    case ANIM2_DEAD_FRONT:
        anim1 = ANIM1_FALLOUT_DEAD;
        anim1ex = ANIM1_FALLOUT_DEAD;
        anim2 = ANIM2_FALLOUT_KNOCK_FRONT;
        anim2ex = ANIM2_FALLOUT_DEAD_FRONT2;
        break;
    case ANIM2_DEAD_BACK:
        anim1 = ANIM1_FALLOUT_DEAD;
        anim1ex = ANIM1_FALLOUT_DEAD;
        anim2 = ANIM2_FALLOUT_KNOCK_BACK;
        anim2ex = ANIM2_FALLOUT_DEAD_BACK2;
        break;
    case ANIM2_NO_RECOIL:
    case ANIM2_RELOAD:
    case ANIM2_REPAIR:
        anim1ex = anim1;
        anim2 = ANIM2_FALLOUT_PREPARE_WEAPON;
        anim2ex = ANIM2_FALLOUT_TURNOFF_WEAPON;
        break;

    // ANIM2_BEGIN_COMBAT
    // ANIM2_END_COMBAT
    // ANIM2_PUNCH_LEFT
    // ANIM2_PUNCH_COMBO
    // ANIM2_KICK_LO
    // ANIM2_KICK_COMBO
    // ANIM2_WALK_DAMAGE_FRONT
    // ANIM2_WALK_DAMAGE_BACK
    // ANIM2_LIMP_DAMAGE_FRONT
    // ANIM2_LIMP_DAMAGE_BACK
    // ANIM2_RUN_DAMAGE_FRONT
    // ANIM2_RUN_DAMAGE_BACK
    // ANIM2_LAYDOWN_FRONT
    // ANIM2_LAYDOWN_BACK
    // ANIM2_DAMAGE_PRONE_FRONT
    // ANIM2_DAMAGE_PRONE_BACK
    // ANIM2_DAMAGE_MUL_PRONE_FRONT
    // ANIM2_DAMAGE_MUL_PRONE_BACK
    // ANIM2_TWITCH_PRONE_FRONT
    // ANIM2_TWITCH_PRONE_BACK
    default:
        return false;
    }
    return true;
}
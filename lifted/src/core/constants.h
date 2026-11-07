#pragma once

#include <cstdint>

namespace lf2 {

// Game constants
constexpr uint32_t MAX_OBJECTS = 400;
constexpr uint32_t MAX_FILES = 65;
constexpr uint32_t MAX_FRAMES = 400;

// Character & Object file IDs
constexpr uint32_t TEMPLATE_DAT       = 0;
constexpr uint32_t DEEP_DAT           = 1;
constexpr uint32_t JOHN_DAT           = 2;
constexpr uint32_t HENRY_DAT          = 4;
constexpr uint32_t RUDOLF_DAT         = 5;
constexpr uint32_t LOUIS_DAT          = 6;
constexpr uint32_t FIREN_DAT          = 7;
constexpr uint32_t FREEZE_DAT         = 8;
constexpr uint32_t DENNIS_DAT         = 9;
constexpr uint32_t WOODY_DAT          = 10;
constexpr uint32_t DAVIS_DAT          = 11;
constexpr uint32_t BANDIT_DAT         = 30;
constexpr uint32_t HUNTER_DAT         = 31;
constexpr uint32_t MARK_DAT           = 32;
constexpr uint32_t JACK_DAT           = 33;
constexpr uint32_t SORCERER_DAT       = 34;
constexpr uint32_t MONK_DAT           = 35;
constexpr uint32_t JAN_DAT            = 36;
constexpr uint32_t KNIGHT_DAT         = 37;
constexpr uint32_t BAT_DAT            = 38;
constexpr uint32_t JUSTIN_DAT         = 39;
constexpr uint32_t LOUISE_EX_DAT      = 50;
constexpr uint32_t FIRZEN_DAT         = 51;
constexpr uint32_t JULIAN_DAT         = 52;

// Weapons
constexpr uint32_t STICK_DAT          = 100;
constexpr uint32_t HOE_DAT            = 101;
constexpr uint32_t KNIFE_DAT          = 120;
constexpr uint32_t BASEBALL_DAT       = 121;
constexpr uint32_t MILK_DAT           = 122;
constexpr uint32_t BEER_DAT           = 123;
constexpr uint32_t BOOMERANG_DAT      = 124;
constexpr uint32_t STONE_DAT          = 150;
constexpr uint32_t WOODEN_BOX_DAT     = 151;
constexpr uint32_t LOUIS_WRISTER_DAT  = 217;
constexpr uint32_t LOUIS_ARMOUR_DAT   = 218;
constexpr uint32_t CRIMINAL_DAT       = 300;

// Projectiles & Special attacks
constexpr uint32_t JOHN_BALL_DAT      = 200;
constexpr uint32_t HENRY_ARROW1_DAT   = 201;
constexpr uint32_t RUDOLF_WEAPON_DAT  = 202;
constexpr uint32_t DEEP_BALL_DAT      = 203;
constexpr uint32_t HENRY_WIND_DAT     = 204;
constexpr uint32_t DENNIS_BALL_DAT    = 205;
constexpr uint32_t WOODY_BALL_DAT     = 206;
constexpr uint32_t DAVIS_BALL_DAT     = 207;
constexpr uint32_t HENRY_ARROW2_DAT   = 208;
constexpr uint32_t FREEZE_BALL_DAT    = 209;
constexpr uint32_t FIREN_BALL_DAT     = 210;
constexpr uint32_t FIREN_FLAME_DAT    = 211;
constexpr uint32_t FREEZE_COLUMN_DAT  = 212;
constexpr uint32_t ICE_SWORD_DAT      = 213;
constexpr uint32_t JOHN_BISCUIT_DAT   = 214;
constexpr uint32_t DENNIS_CHASE_DAT   = 215;
constexpr uint32_t JACK_BALL_DAT      = 216;
constexpr uint32_t JAN_CHASEH_DAT     = 219;
constexpr uint32_t JAN_CHASE_DAT      = 220;
constexpr uint32_t FIRZEN_CHASEF_DAT  = 221;
constexpr uint32_t FIRZEN_CHASEI_DAT  = 222;
constexpr uint32_t FIRZEN_BALL_DAT    = 223;
constexpr uint32_t BAT_BALL_DAT       = 224;
constexpr uint32_t BAT_CHASE_DAT      = 225;
constexpr uint32_t JUSTIN_BALL_DAT    = 226;
constexpr uint32_t JULIAN_BALL_DAT    = 228;
constexpr uint32_t JULIAN_BALL2_DAT   = 229;
constexpr uint32_t ETC_DAT            = 998;
constexpr uint32_t BROKEN_WEAPON_DAT  = 999;

// Entity / File Types
constexpr uint32_t TYPE_CHARACTER     = 0;
constexpr uint32_t TYPE_LIGHT_WEAPON  = 1;
constexpr uint32_t TYPE_HEAVY_WEAPON  = 2;
constexpr uint32_t TYPE_ATTACK        = 3; // Projectile / energy ball
constexpr uint32_t TYPE_THROW_WEAPON  = 4;
constexpr uint32_t TYPE_CRIMINAL      = 5;
constexpr uint32_t TYPE_DRINK         = 6;

// Facing Directions
constexpr uint8_t FACING_RIGHT        = 0;
constexpr uint8_t FACING_LEFT         = 1;

// Animation States
constexpr uint32_t STATE_STANDING       = 0;
constexpr uint32_t STATE_WALKING        = 1;
constexpr uint32_t STATE_RUNNING        = 2;
constexpr uint32_t STATE_ATTACKING      = 3;
constexpr uint32_t STATE_JUMPING        = 4;
constexpr uint32_t STATE_DASHING        = 5;
constexpr uint32_t STATE_ROWING         = 6;
constexpr uint32_t STATE_DEFEND         = 7;
constexpr uint32_t STATE_BROKEN_DEFEND  = 8;
constexpr uint32_t STATE_CATCHING       = 9;
constexpr uint32_t STATE_PICKED_CAUGHT  = 10;
constexpr uint32_t STATE_INJURED_1      = 11;
constexpr uint32_t STATE_FALLING        = 12;
constexpr uint32_t STATE_ICE            = 13;
constexpr uint32_t STATE_LYING          = 14;
constexpr uint32_t STATE_INJURED_2      = 15;
constexpr uint32_t STATE_FIRE           = 16;
constexpr uint32_t STATE_DRINKING       = 17;
constexpr uint32_t STATE_BURNING        = 18;
constexpr uint32_t STATE_BURN_RUN       = 18; // Legacy alias for STATE_BURNING
constexpr uint32_t STATE_BROKEN_WEAPON  = 999;

// Teleport Targets
constexpr uint32_t TELEPORT_TO_ENEMY    = 1;
constexpr uint32_t TELEPORT_TO_TEAM     = 2;

// ITR Kinds
constexpr uint32_t ITR_NORMAL_ATTACK    = 0;
constexpr uint32_t ITR_CATCH_INJURED    = 1;
constexpr uint32_t ITR_PICK_UP_WEAPON   = 2;
constexpr uint32_t ITR_CATCH            = 3;
constexpr uint32_t ITR_THROWN           = 4;
constexpr uint32_t ITR_WEAPON_STRENGTH  = 5;
constexpr uint32_t ITR_SUPER_PUNCH      = 6;
constexpr uint32_t ITR_ROWING_PICK      = 7;
constexpr uint32_t ITR_HEAL             = 8;
constexpr uint32_t ITR_FORCEFIELD       = 9;
constexpr uint32_t ITR_FLUTE            = 10;
constexpr uint32_t ITR_FLOAT            = 11;
constexpr uint32_t ITR_FREEZE           = 14;
constexpr uint32_t ITR_WHIRLWIND_ICE    = 15;
constexpr uint32_t ITR_WHIRLWIND_WIND   = 16;

// Attack Effects
constexpr uint32_t EFFECT_PUNCH            = 0;
constexpr uint32_t EFFECT_BLEED            = 1;
constexpr uint32_t EFFECT_FIRE             = 2;
constexpr uint32_t EFFECT_ICE              = 3;
constexpr uint32_t EFFECT_SHINING          = 4;
constexpr uint32_t EFFECT_BURN             = 3;  // Legacy alias
constexpr uint32_t EFFECT_FLAME            = 4;  // Legacy alias
constexpr uint32_t EFFECT_FIRE_NO_SOUND    = 20;
constexpr uint32_t EFFECT_FIRE_JULIAN      = 21;
constexpr uint32_t EFFECT_FIRE_EXPLODE     = 22;
constexpr uint32_t EFFECT_FIREN_EXPLOSION  = 20; // Legacy alias
constexpr uint32_t EFFECT_JULIAN_EXPLOSION = 21; // Legacy alias
constexpr uint32_t EFFECT_FREEZE           = 30;

} // namespace lf2


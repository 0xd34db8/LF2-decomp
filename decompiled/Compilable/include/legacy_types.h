#ifndef LEGACY_TYPES_H
#define LEGACY_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#include <winsock.h>
#include <commdlg.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Win32 tagMSG compatibility
typedef MSG tagMSG;
typedef struct tagOFNA tagOFNA;
typedef SYSTEMTIME _SYSTEMTIME;

// Time structure compatibility
typedef struct tm tm;

// Ghidra decompiler synthetic primitive types
typedef uint8_t   undefined1;
typedef uint16_t  undefined2;
typedef uint32_t  undefined4;
typedef uint64_t  undefined8;
typedef uint8_t   byte;
typedef uint8_t   uchar;
typedef uint16_t  ushort;
typedef uint32_t  uint;
typedef uint32_t  ulong;
typedef int64_t   longlong;
typedef uint64_t  ulonglong;
typedef double    float10; // x87 80-bit float represented as 64-bit IEEE double

// Ghidra decompiler synthetic macros
#undef NAN
#define NAN(x) isnan(x)
#define SBORROW4(a, b) ((int32_t)(a) < (int32_t)(b))
#define CARRY4(a, b) ((uint32_t)(a) + (uint32_t)(b) < (uint32_t)(a))
#define operator_new(sz) malloc(sz)
#define __security_check_cookie(x) ((void)0)

// Ghidra generic function pointer type
typedef void (*code)();

// Builtin intrinsics
#define builtin_strncpy strncpy
#define builtin_memcpy memcpy

typedef union {
    char _0_1_;
    char str[4];
    int val;
} dat_0044d320_t;

// Calling convention bridge
#if defined(__GNUC__) && defined(__i386__)
#define THISCALL __attribute__((thiscall))
#elif defined(_MSC_VER)
#define THISCALL __thiscall
#else
#define THISCALL
#endif

// ============================================================================
// Authentic Little Fighter 2 Domain Structures & Constants
// Memory layout: 1:1 binary match with MSVC++ 32-bit x86 compiled executable
// ============================================================================

#define MAX_OBJECTS 400
#define MAX_FILES   65
#define MAX_FRAMES  400

// Facing Directions
enum {
    FACING_RIGHT = 0,
    FACING_LEFT  = 1
};

// Entity / File Types
enum {
    TYPE_CHARACTER    = 0,
    TYPE_LIGHT_WEAPON = 1,
    TYPE_HEAVY_WEAPON = 2,
    TYPE_ATTACK       = 3, // projectile / energy ball
    TYPE_THROW_WEAPON = 4,
    TYPE_CRIMINAL     = 5,
    TYPE_DRINK        = 6
};

// Character & Object File IDs
enum {
    ID_TEMPLATE_DAT       = 0,
    ID_DEEP_DAT           = 1,
    ID_JOHN_DAT           = 2,
    ID_HENRY_DAT          = 4,
    ID_RUDOLF_DAT         = 5,
    ID_LOUIS_DAT          = 6,
    ID_FIREN_DAT          = 7,
    ID_FREEZE_DAT         = 8,
    ID_DENNIS_DAT         = 9,
    ID_WOODY_DAT          = 10,
    ID_DAVIS_DAT          = 11,
    ID_BANDIT_DAT         = 30,
    ID_HUNTER_DAT         = 31,
    ID_MARK_DAT           = 32,
    ID_JACK_DAT           = 33,
    ID_SORCERER_DAT       = 34,
    ID_MONK_DAT           = 35,
    ID_JAN_DAT            = 36,
    ID_KNIGHT_DAT         = 37,
    ID_BAT_DAT            = 38,
    ID_JUSTIN_DAT         = 39,
    ID_LOUISE_EX_DAT      = 50,
    ID_FIRZEN_DAT         = 51,
    ID_JULIAN_DAT         = 52,
    ID_STICK_DAT          = 100,
    ID_HOE_DAT            = 101,
    ID_KNIFE_DAT          = 120,
    ID_BASEBALL_DAT       = 121,
    ID_MILK_DAT           = 122,
    ID_BEER_DAT           = 123,
    ID_BOOMERANG_DAT      = 124,
    ID_STONE_DAT          = 150,
    ID_WOODEN_BOX_DAT     = 151,
    ID_JOHN_BALL_DAT      = 200,
    ID_HENRY_ARROW1_DAT   = 201,
    ID_RUDOLF_WEAPON_DAT  = 202,
    ID_DEEP_BALL_DAT      = 203,
    ID_HENRY_WIND_DAT     = 204,
    ID_DENNIS_BALL_DAT    = 205,
    ID_WOODY_BALL_DAT     = 206,
    ID_DAVIS_BALL_DAT     = 207,
    ID_HENRY_ARROW2_DAT   = 208,
    ID_FREEZE_BALL_DAT    = 209,
    ID_FIREN_BALL_DAT     = 210,
    ID_FIREN_FLAME_DAT    = 211,
    ID_FREEZE_COLUMN_DAT  = 212,
    ID_ICE_SWORD_DAT      = 213,
    ID_JOHN_BISCUIT_DAT   = 214,
    ID_DENNIS_CHASE_DAT   = 215,
    ID_JACK_BALL_DAT      = 216,
    ID_LOUIS_WRISTER_DAT  = 217,
    ID_LOUIS_ARMOUR_DAT   = 218,
    ID_JAN_CHASEH_DAT     = 219,
    ID_JAN_CHASE_DAT      = 220,
    ID_FIRZEN_CHASEF_DAT  = 221,
    ID_FIRZEN_CHASEI_DAT  = 222,
    ID_FIRZEN_BALL_DAT    = 223,
    ID_BAT_BALL_DAT       = 224,
    ID_BAT_CHASE_DAT      = 225,
    ID_JUSTIN_BALL_DAT    = 226,
    ID_JULIAN_BALL_DAT    = 228,
    ID_JULIAN_BALL2_DAT   = 229,
    ID_CRIMINAL_DAT       = 300,
    ID_ETC_DAT            = 998,
    ID_BROKEN_WEAPON_DAT  = 999
};

// Hitbox (ITR) interaction kinds
enum {
    ITR_KIND_NORMAL         = 0,
    ITR_KIND_CATCH          = 1,
    ITR_KIND_PICKUP_WEAPON  = 2,
    ITR_KIND_CATCH_INJURED  = 3,
    ITR_KIND_THROWN         = 4,
    ITR_KIND_ROWING_PICK    = 6,
    ITR_KIND_HEAL           = 8,
    ITR_KIND_FORCEFIELD     = 9,
    ITR_KIND_FLUTE          = 10,
    ITR_KIND_FLOAT          = 11,
    ITR_KIND_SUPER_PUNCH    = 14,
    ITR_KIND_FLY            = 15,
    ITR_KIND_FREEZE         = 16
};

// Hitbox effect kinds
enum {
    EFFECT_BLOOD            = 0,
    EFFECT_FIRE             = 1,
    EFFECT_FREEZE           = 2,
    EFFECT_BURN_RUN         = 3,
    EFFECT_FIRE_COLUMN      = 4,
    EFFECT_FLAME            = 20,
    EFFECT_FIREN_EXPLODE    = 21,
    EFFECT_COLUMN           = 22
};

// Animation States
enum {
    STATE_STANDING          = 0,
    STATE_WALKING           = 1,
    STATE_RUNNING           = 2,
    STATE_ATTACKING         = 3,
    STATE_JUMPING           = 4,
    STATE_DASHING           = 5,
    STATE_ROWING            = 6,
    STATE_DEFENDING         = 7,
    STATE_BROKEN_DEFEND     = 8,
    STATE_CATCHING          = 9,
    STATE_CAUGHT            = 10,
    STATE_INJURED_1         = 11,
    STATE_FALLING           = 12,
    STATE_ICE               = 13,
    STATE_LYING             = 14,
    STATE_OTHER             = 15,
    STATE_INJURED_2         = 16,
    STATE_DRINKING          = 17,
    STATE_BURNING           = 18,
    STATE_FIRE              = 19
};

#pragma pack(push, 4)

// 1. Bounding Box (bdy)
// Size: 0x28 (40 bytes)
typedef struct bdy {
    uint32_t  kind;          // 0x00
    int32_t   x;             // 0x04
    int32_t   y;             // 0x08
    int32_t   w;             // 0x0C
    int32_t   h;             // 0x10
    uint32_t  _unknown1;     // 0x14
    uint32_t  _unknown2;     // 0x18
    uint32_t  _unknown3;     // 0x1C
    uint32_t  _unknown4;     // 0x20
    uint32_t  _unknown5;     // 0x24
} bdy_t;

// 2. Hitbox Interaction (itr)
// Size: 0x50 (80 bytes)
typedef struct itr {
    uint32_t  kind;          // 0x00
    int32_t   x;             // 0x04
    int32_t   y;             // 0x08
    int32_t   w;             // 0x0C
    int32_t   h;             // 0x10
    int32_t   dvx;           // 0x14
    int32_t   dvy;           // 0x18
    int32_t   fall;          // 0x1C
    uint32_t  arest;         // 0x20
    uint32_t  vrest;         // 0x24
    uint32_t  respond;       // 0x28
    int32_t   effect;        // 0x2C
    uint32_t  catching_act1; // 0x30
    uint32_t  catching_act2; // 0x34
    uint32_t  caught_act1;   // 0x38
    uint32_t  caught_act2;   // 0x3C
    uint32_t  bdefend;       // 0x40
    int32_t   injury;        // 0x44
    int32_t   zwidth;        // 0x48
    uint32_t  _unknown1;     // 0x4C
} itr_t;

// 3. Object Point (opoint: weapon, projectile, spawn point)
// Size: 0x20 (32 bytes)
typedef struct opoint {
    uint32_t  kind;          // 0x00
    int32_t   x;             // 0x04
    int32_t   y;             // 0x08
    uint32_t  action;        // 0x0C
    int32_t   dvx;           // 0x10
    int32_t   dvy;           // 0x14
    uint32_t  oid;           // 0x18
    uint32_t  facing;        // 0x1C
} opoint_t;

// 4. Blood Point (bpoint: visual blood origin)
// Size: 0x0C (12 bytes)
typedef struct bpoint {
    int32_t   x;             // 0x00
    int32_t   y;             // 0x04
    int32_t   _unknown;      // 0x08
} bpoint_t;

// 5. Catch Point (cpoint: grappling anchor)
// Size: 0x44 (68 bytes)
typedef struct cpoint {
    uint32_t  kind;          // 0x00
    int32_t   x;             // 0x04
    int32_t   y;             // 0x08
    int32_t   throwv_x;      // 0x0C
    int32_t   throwv_y;      // 0x10
    uint32_t  _unknown1;     // 0x14
    uint32_t  _unknown2;     // 0x18
    uint32_t  throw_injury;  // 0x1C
    uint32_t  _unknown3;     // 0x20
    uint32_t  v_action;      // 0x24
    uint32_t  throw_a;       // 0x28
    uint32_t  throw_d;       // 0x2C
    uint32_t  throw_j;       // 0x30
    uint32_t  throw_Fa;      // 0x34
    uint32_t  throw_Ua;      // 0x38
    uint32_t  throw_Da;      // 0x3C
    uint32_t  _unknown4;     // 0x40
} cpoint_t;

// 6. Weapon Point (wpoint: carried weapon attachment)
// Size: 0x24 (36 bytes)
typedef struct wpoint {
    uint32_t  kind;          // 0x00
    int32_t   x;             // 0x04
    int32_t   y;             // 0x08
    uint32_t  weaponact;     // 0x0C
    uint32_t  attacking;     // 0x10
    uint32_t  cover;         // 0x14
    int32_t   dvx;           // 0x18
    int32_t   dvy;           // 0x1C
    int32_t   dvz;           // 0x20
} wpoint_t;

// 7. Animation Frame (frame)
// Size: 0x178 (376 bytes)
typedef struct frame {
    uint32_t       present;        // 0x000
    uint32_t       pic;            // 0x004
    uint32_t       state;          // 0x008
    uint32_t       wait;           // 0x00C
    int32_t        next;           // 0x010
    int32_t        dvx;            // 0x014
    int32_t        dvy;            // 0x018
    int32_t        dvz;            // 0x01C
    uint32_t       _unknown1;      // 0x020
    uint32_t       hit_a;          // 0x024
    uint32_t       hit_d;          // 0x028
    uint32_t       hit_j;          // 0x02C
    uint32_t       hit_Fa;         // 0x030
    uint32_t       hit_Ua;         // 0x034
    uint32_t       hit_Da;         // 0x038
    uint32_t       hit_Fj;         // 0x03C
    uint32_t       hit_Uj;         // 0x040
    uint32_t       hit_Dj;         // 0x044
    uint32_t       hit_ja;         // 0x048
    int32_t        mp;             // 0x04C
    int32_t        centerx;        // 0x050
    int32_t        centery;        // 0x054
    opoint_t       opoint;         // 0x058 - 0x078
    uint32_t       _unknown2;      // 0x078
    bpoint_t       bpoint;         // 0x07C - 0x088
    cpoint_t       cpoint;         // 0x088 - 0x0CC
    uint32_t       _unknown3[3];   // 0x0CC - 0x0D8
    wpoint_t       wpoint;         // 0x0D8 - 0x0FC
    uint32_t       _unknown4[11];  // 0x0FC - 0x128
    uint32_t       itrs_size;      // 0x128
    uint32_t       bdys_size;      // 0x12C
    itr_t*         itrs;           // 0x130
    bdy_t*         bdys;           // 0x134 (on 32-bit: 0x134, on 64-bit: 0x138)
#if INTPTR_MAX == INT32_MAX
    uint32_t       _unknown5[9];   // 0x138 - 0x15C (36 bytes)
#else
    uint32_t       _unknown5[7];   // 0x140 - 0x15C (28 bytes)
#endif
    char           name[4];        // 0x15C
    uint32_t       continue1;      // 0x160
    uint32_t       continue2;      // 0x164
    uint32_t       continue3;      // 0x168
    uint32_t       continue4;      // 0x16C
    uint32_t       sound;          // 0x170
    uint32_t       _unknown6;      // 0x174
} frame_t;

// 8. Character / Weapon / Item Definition (.dat file)
// Total Size: 0x25360 (152,416 bytes)
typedef struct file {
    uint32_t         walking_frame_rate;    // 0x000
    uint32_t         _pad0;                 // 0x004
    double           walking_speed;         // 0x008
    double           walking_speedz;        // 0x010
    uint32_t         running_frame_rate;    // 0x018
    uint32_t         _pad1;                 // 0x01C
    double           running_speed;         // 0x020
    double           running_speedz;        // 0x028
    double           heavy_walking_speed;   // 0x030
    double           heavy_walking_speedz;  // 0x038
    double           heavy_running_speed;   // 0x040
    double           heavy_running_speedz;  // 0x048
    double           jump_height;           // 0x050
    double           jump_distance;         // 0x058
    double           jump_distancez;        // 0x060
    double           dash_height;           // 0x068
    double           dash_distance;         // 0x070
    double           dash_distancez;        // 0x078
    double           rowing_height;         // 0x080
    double           rowing_distance;       // 0x088
    int32_t          weapon_hp;             // 0x090
    int32_t          weapon_drop_hurt;      // 0x094
    uint32_t         weapon_hit_sound;      // 0x098
    uint32_t         weapon_drop_sound;     // 0x09C
    uint32_t         weapon_broken_sound;   // 0x0A0
    int32_t          weapon_hit_sound_id;   // 0x0A4
    int32_t          weapon_drop_sound_id;  // 0x0A8
    int32_t          weapon_broken_sound_id;// 0x0AC
    itr_t            attacking_itrs[4];     // 0x0B0 - 0x1F0
    uint8_t          _pad3[0x2A8];          // 0x1F0 - 0x498
    int32_t          bmp_count;             // 0x498
    char             bmp_paths[10][40];     // 0x49C - 0x62C
    int32_t          sheet_start[10];       // 0x62C - 0x654
    int32_t          sheet_w[10];           // 0x654 - 0x67C
    int32_t          sheet_h[10];           // 0x67C - 0x6A4
    int32_t          sheet_row[10];         // 0x6A4 - 0x6CC
    int32_t          sheet_col[10];         // 0x6CC - 0x6F4
    uint32_t         id;                    // 0x6F4
    uint32_t         type;                  // 0x6F8
    uint32_t         head_bmp_mgr;          // 0x6FC
    char             head[40];              // 0x700
    uint32_t         small_bmp_mgr;         // 0x728
    char             small[36];             // 0x72C
    uint32_t         bmp_mgrs[10];          // 0x750 - 0x778
    uint32_t         mirror_bmp_mgrs[10];   // 0x778 - 0x7A0
    uint32_t         _pad6;                 // 0x7A0 - 0x7A4
    frame_t          frames[MAX_FRAMES];    // 0x7A4 - 0x25324
    char             name[60];              // 0x25324 - 0x25360
} file_t;

// 9. World Entity / Character / Weapon Instance (object)
// Total Size: 0x370 (880 bytes)
typedef struct object {
    uint32_t        move_counter;             // 0x000
    uint32_t        run_counter;              // 0x004
    uint32_t        invincible_time;          // 0x008
    uint32_t        _unknown1;                // 0x00C
    int32_t         x;                        // 0x010
    int32_t         y;                        // 0x014
    int32_t         z;                        // 0x018
    uint32_t        _unknown2;                // 0x01C
    uint32_t        attacks;                  // 0x020
    uint32_t        _unknown3;                // 0x024
    double          pic_x_gain;               // 0x028
    double          y_accl;                   // 0x030
    double          z_accl;                   // 0x038
    double          x_velocity;               // 0x040
    double          y_velocity;               // 0x048
    double          z_velocity;               // 0x050
    double          x_position;               // 0x058
    double          y_position;               // 0x060
    double          z_position;               // 0x068
    uint32_t        frame_id1;                // 0x070
    uint32_t        frame_id2;                // 0x074
    uint32_t        frame_id3;                // 0x078
    uint32_t        frame_id4;                // 0x07C
    uint8_t         facing;                   // 0x080 (0: right, 1: left)
    uint8_t         _unknown4[3];             // 0x081 - 0x084
    uint32_t        _unknown7;                // 0x084
    uint32_t        wait_counter;             // 0x088
    uint32_t        cpoint_catcher;           // 0x08C
    uint32_t        cpoint_timer;             // 0x090
    uint32_t        _unknown8;                // 0x094
    uint32_t        weapon_type;              // 0x098
    uint32_t        weapon_id;                // 0x09C
    uint32_t        holder_id;                // 0x0A0
    uint32_t        _unknown9[3];             // 0x0A4 - 0x0B0
    int32_t         fall;                     // 0x0B0
    int32_t         shaking;                  // 0x0B4
    uint32_t        bdefend;                  // 0x0B8
    uint8_t         _unknown12[10];           // 0x0BC - 0x0C6
    uint8_t         holding_up;               // 0x0C6
    uint8_t         holding_down;             // 0x0C7
    uint8_t         holding_left;             // 0x0C8
    uint8_t         holding_right;            // 0x0C9
    uint8_t         holding_attack;           // 0x0CA
    uint8_t         holding_jump;             // 0x0CB
    uint8_t         holding_defend;           // 0x0CC
    uint8_t         click_up;                 // 0x0CD
    uint8_t         click_down;               // 0x0CE
    uint8_t         click_left;               // 0x0CF
    uint8_t         click_right;              // 0x0D0
    uint8_t         click_attack;             // 0x0D1
    uint8_t         click_jump;               // 0x0D2
    uint8_t         click_defend;             // 0x0D3
    uint32_t        defense_breaking;         // 0x0D4
    uint32_t        _unknown15[4];            // 0x0D8 - 0x0E8
    uint32_t        _unknown26;               // 0x0E8
    uint32_t        arest;                    // 0x0EC
    uint8_t         vrest_of_objects[MAX_OBJECTS]; // 0x0F0 - 0x280 (400 bytes)
    int32_t         injured_of_attack[20];    // 0x280 - 0x2D0 (80 bytes)
    uint8_t         itr_of_attack[20];        // 0x2D0 - 0x2E4 (20 bytes)
    int32_t         successful_attacks;       // 0x2E4
    int32_t         attackable_distance;      // 0x2E8
    int32_t         vulnerable_distance;      // 0x2EC
    uint32_t        _unknown29;               // 0x2F0
    uint32_t        clone;                    // 0x2F4
    uint32_t        _unknown30;               // 0x2F8
    int32_t         hp;                       // 0x2FC
    int32_t         dark_hp;                  // 0x300
    int32_t         max_hp;                   // 0x304
    int32_t         mp;                       // 0x308
    uint32_t        _unknown31[3];            // 0x30C - 0x318
    uint32_t        pic_no_gain;              // 0x318
    int32_t         drink_hp;                 // 0x31C
    uint32_t        thrown_injury;            // 0x320
    uint32_t        _unknown34[5];            // 0x324 - 0x338
    uint32_t        firen_counter;            // 0x338
    uint32_t        _unknown39;               // 0x33C
    uint32_t        armor_multiplier;         // 0x340
    uint32_t        _unknown40;               // 0x344
    uint32_t        total_attack;             // 0x348
    uint32_t        hp_lost;                  // 0x34C
    uint32_t        mp_used;                  // 0x350
    uint32_t        owner;                    // 0x354
    uint32_t        kills;                    // 0x358
    uint32_t        get_weapon_counter;       // 0x35C
    uint32_t        enemy;                    // 0x360
    uint32_t        team;                     // 0x364
#if INTPTR_MAX == INT32_MAX
    file_t*         file;                     // 0x368
    uint32_t        _pad_end;                 // 0x36C - 0x370
#else
    file_t*         file;                     // 0x368 - 0x370 (8-byte pointer on 64-bit)
#endif
} object_t;

// 10. Global Game Manager State (global)
// Address in original binary: 0x00458B00
typedef struct global {
    uint32_t        game_state;                   // 0x000
    uint8_t         is_object_exists[MAX_OBJECTS];// 0x004 - 0x194 (400 bytes)
    object_t*       objects[MAX_OBJECTS];         // 0x194 - 0x7D4 (400 object pointers)
    file_t*         files[MAX_FILES];             // 0x7D4 - 0x8D8 (65 file pointers)
} global_t;

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif // LEGACY_TYPES_H

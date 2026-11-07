#pragma once

#include <cstdint>
#include <cstddef>
#include "constants.h"
#include "types.h"
#include "file.h"

namespace lf2 {

#pragma pack(push, 4)

// Entity / Object in the game world
// Total Size: 0x418 (1048 bytes)
struct object_t {
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
    int32_t         wait_counter;             // 0x084
    union {
        int32_t     cpoint_hurt;              // 0x088
        int32_t     in_sky;                   // 0x088
        uint32_t    _unknown7;                // 0x088
    };
    int32_t         cpoint_catcher;           // 0x08C
    union {
        int32_t     cpoint_caught;            // 0x090
        uint32_t    cpoint_timer;             // 0x090
    };
    union {
        int32_t     cpoint_hurtable;          // 0x094
        uint32_t    _unknown8;                // 0x094
    };
    int32_t         weapon_type;              // 0x098
    int32_t         weapon_id;                // 0x09C
    int32_t         holder_id;                // 0x0A0
    int32_t         _unknown9[3];             // 0x0A4 - 0x0B0
    int32_t         fall;                     // 0x0B0
    int32_t         shaking;                  // 0x0B4
    int32_t         bdefend;                  // 0x0B8
    union {
        uint8_t     key_state[10];            // 0x0BC - 0x0C6 (0..6: up, down, left, right, attack, jump, defend)
        uint8_t     _unknown12[10];           // 0x0BC - 0x0C6
    };
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
    union {
        struct {
            uint8_t  run_left_right;          // 0x0D4
            uint8_t  run_up_down;             // 0x0D5
            uint8_t  last_dir_x;              // 0x0D6
            uint8_t  _pad_d7;                 // 0x0D7
        };
        uint32_t     defense_breaking;        // 0x0D4
    };
    int32_t         row_timer1;               // 0x0D8
    int32_t         row_timer2;               // 0x0DC
    union {
        int32_t     curing_hp;                // 0x0E0
        uint32_t    _unknown15_2;             // 0x0E0
    };
    int32_t         _unknown15_3;             // 0x0E4
    union {
        struct {
            uint8_t  flag_e8;                 // 0x0E8
            uint8_t  has_arest;               // 0x0E9
            uint8_t  can_hit_flag;            // 0x0EA
            uint8_t  flag_eb;                 // 0x0EB
        };
        uint32_t     _unknown26;              // 0x0E8
    };
    int32_t         arest;                    // 0x0EC
    uint8_t         vrest_of_objects[MAX_OBJECTS]; // 0x0F0 - 0x280 (400 bytes)
    int32_t         injured_of_attack[20];    // 0x280 - 0x2D0 (80 bytes)
    uint8_t         itr_of_attack[20];        // 0x2D0 - 0x2E4 (20 bytes)
    int32_t         successful_attacks;       // 0x2E4
    int32_t         attackable_distance;      // 0x2E8
    int32_t         vulnerable_distance;      // 0x2EC
    uint32_t        _unknown29;               // 0x2F0
    int32_t         clone;                    // 0x2F4
    union {
        int32_t     weapon_throw_injury;      // 0x2F8
        int32_t     under_attack_distance;    // 0x2F8
        uint32_t    _unknown30;               // 0x2F8
    };
    int32_t         hp;                       // 0x2FC
    int32_t         dark_hp;                  // 0x300
    int32_t         max_hp;                   // 0x304
    int32_t         mp;                       // 0x308
    int32_t         reserve;                  // 0x30C
    uint32_t        _unknown31[2];            // 0x310 - 0x318
    int32_t         pic_no_gain;              // 0x318
    union {
        int32_t     weapon_hp;                // 0x31C
        int32_t     drink_hp;                 // 0x31C
    };
    union {
        int32_t     cpoint_hurt_act;          // 0x320
        uint32_t    thrown_injury;            // 0x320
    };
    int32_t         uid;                      // 0x324
    uint32_t        _unknown34[4];            // 0x328 - 0x338
    uint32_t        firen_counter;            // 0x338
    uint32_t        _unknown39;               // 0x33C
    uint32_t        armor_multiplier;         // 0x340
    int32_t         player_index;             // 0x344
    uint32_t        total_attack;             // 0x348
    uint32_t        hp_lost;                  // 0x34C
    uint32_t        mp_used;                  // 0x350
    int32_t         owner;                    // 0x354
    uint32_t        kills;                    // 0x358
    uint32_t        get_weapon_counter;       // 0x35C
    int32_t         enemy;                    // 0x360
    uint32_t        team;                     // 0x364
#if INTPTR_MAX == INT32_MAX
    file_t*         file;                     // 0x368
    uint32_t        ai_vars[36];              // 0x36C - 0x3FC
#else
    file_t*         file;                     // 0x368 - 0x370 (8-byte pointer on 64-bit)
    uint32_t        ai_vars[35];              // 0x370 - 0x3FC
#endif
    int32_t         ai_target_x;              // 0x3FC
    int32_t         ai_target_z;              // 0x400
    uint32_t        ai_vars_tail[5];          // 0x404 - 0x418
};

#pragma pack(pop)

static_assert(sizeof(object_t) == 0x418, "object_t size must be 0x418 (1048 bytes)");
static_assert(offsetof(object_t, x) == 0x010, "object_t::x offset mismatch");
static_assert(offsetof(object_t, y) == 0x014, "object_t::y offset mismatch");
static_assert(offsetof(object_t, z) == 0x018, "object_t::z offset mismatch");
static_assert(offsetof(object_t, x_velocity) == 0x040, "object_t::x_velocity offset mismatch");
static_assert(offsetof(object_t, y_velocity) == 0x048, "object_t::y_velocity offset mismatch");
static_assert(offsetof(object_t, z_velocity) == 0x050, "object_t::z_velocity offset mismatch");
static_assert(offsetof(object_t, x_position) == 0x058, "object_t::x_position offset mismatch");
static_assert(offsetof(object_t, y_position) == 0x060, "object_t::y_position offset mismatch");
static_assert(offsetof(object_t, z_position) == 0x068, "object_t::z_position offset mismatch");
static_assert(offsetof(object_t, frame_id1) == 0x070, "object_t::frame_id1 offset mismatch");
static_assert(offsetof(object_t, frame_id4) == 0x07C, "object_t::frame_id4 offset mismatch");
static_assert(offsetof(object_t, facing) == 0x080, "object_t::facing offset mismatch");
static_assert(offsetof(object_t, wait_counter) == 0x084, "object_t::wait_counter offset mismatch");
static_assert(offsetof(object_t, in_sky) == 0x088, "object_t::in_sky offset mismatch");
static_assert(offsetof(object_t, holding_attack) == 0x0CA, "object_t::holding_attack offset mismatch");
static_assert(offsetof(object_t, click_attack) == 0x0D1, "object_t::click_attack offset mismatch");
static_assert(offsetof(object_t, vrest_of_objects) == 0x0F0, "object_t::vrest_of_objects offset mismatch");
static_assert(offsetof(object_t, injured_of_attack) == 0x280, "object_t::injured_of_attack offset mismatch");
static_assert(offsetof(object_t, itr_of_attack) == 0x2D0, "object_t::itr_of_attack offset mismatch");
static_assert(offsetof(object_t, successful_attacks) == 0x2E4, "object_t::successful_attacks offset mismatch");
static_assert(offsetof(object_t, attackable_distance) == 0x2E8, "object_t::attackable_distance offset mismatch");
static_assert(offsetof(object_t, hp) == 0x2FC, "object_t::hp offset mismatch");
static_assert(offsetof(object_t, dark_hp) == 0x300, "object_t::dark_hp offset mismatch");
static_assert(offsetof(object_t, mp) == 0x308, "object_t::mp offset mismatch");
static_assert(offsetof(object_t, team) == 0x364, "object_t::team offset mismatch");
static_assert(offsetof(object_t, file) == 0x368, "object_t::file offset mismatch");
static_assert(offsetof(object_t, ai_target_x) == 0x3FC, "object_t::ai_target_x offset mismatch");
static_assert(offsetof(object_t, ai_target_z) == 0x400, "object_t::ai_target_z offset mismatch");

} // namespace lf2

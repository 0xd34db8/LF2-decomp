#pragma once

#include <cstdint>
#include <cstddef>
#include "constants.h"
#include "types.h"
#include "file.h"

namespace lf2 {

#pragma pack(push, 4)

// Entity / Object in the game world
// Total Size: 0x370 (880 bytes)
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
    uint8_t         _unknown12[14];           // 0x0BC - 0x0CA
    uint8_t         holding_attack;           // 0x0CA
    uint8_t         _unknown13[6];            // 0x0CB - 0x0D1
    uint8_t         click_attack;             // 0x0D1
    uint8_t         _unknown14[2];            // 0x0D2 - 0x0D4
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
};

#pragma pack(pop)

static_assert(sizeof(object_t) == 0x370, "object_t size must be 0x370 (880 bytes)");
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
static_assert(offsetof(object_t, wait_counter) == 0x088, "object_t::wait_counter offset mismatch");
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

} // namespace lf2

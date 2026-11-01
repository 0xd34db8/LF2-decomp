#pragma once

#include <cstdint>
#include <cstddef>
#include "constants.h"
#include "types.h"
#include "bdy.h"
#include "itr.h"

namespace lf2 {

#pragma pack(push, 4)

// Object Point (opoint: weapon, projectile, spawn point)
// Size: 0x20 (32 bytes)
struct opoint_t {
    uint32_t kind;       // 0x00
    int32_t  x;          // 0x04
    int32_t  y;          // 0x08
    uint32_t action;     // 0x0C
    int32_t  dvx;        // 0x10
    int32_t  dvy;        // 0x14
    uint32_t oid;        // 0x18
    uint32_t facing;     // 0x1C
};

// Blood Point (bpoint: visual blood/damage splatter origin)
// Size: 0x0C (12 bytes)
struct bpoint_t {
    int32_t x;           // 0x00
    int32_t y;           // 0x04
    int32_t _unknown;    // 0x08
};

// Catch Point (cpoint: catching, holding, and throwing entities)
// Size: 0x44 (68 bytes)
struct cpoint_t {
    uint32_t kind;       // 0x00
    int32_t  x;          // 0x04
    int32_t  y;          // 0x08
    union {
        // kind == 1: Catcher properties
        struct {
            int32_t  throwv_x;        // 0x0C
            int32_t  throwv_y;        // 0x10
            uint32_t _unknown1;       // 0x14
            uint32_t _unknown2;       // 0x18
            uint32_t throw_injury;    // 0x1C
            uint32_t _unknown3;       // 0x20
            uint32_t v_action;        // 0x24
            uint32_t throw_a;         // 0x28
            uint32_t throw_d;         // 0x2C
            uint32_t throw_j;         // 0x30
            uint32_t throw_Fa;        // 0x34
            uint32_t throw_Ua;        // 0x38
            uint32_t throw_Da;        // 0x3C
            uint32_t _unknown4;       // 0x40
        };
        // kind == 2: Caught properties
        struct {
            uint32_t front_hurt_act;  // 0x0C
            uint32_t back_hurt_act;   // 0x10
            uint32_t _pad_caught[12];
        };
    };
};

// Weapon Point (wpoint: weapon attachment position & hand interaction)
// Size: 0x24 (36 bytes)
struct wpoint_t {
    uint32_t kind;       // 0x00
    int32_t  x;          // 0x04
    int32_t  y;          // 0x08
    uint32_t weaponact;  // 0x0C
    uint32_t attacking;  // 0x10
    uint32_t cover;      // 0x14
    int32_t  dvx;        // 0x18
    int32_t  dvy;        // 0x1C
    int32_t  dvz;        // 0x20
};

// Frame (single animation and logic state of an entity)
// Size: 0x178 (376 bytes)
struct frame_t {
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
    opoint_t       opoint;         // 0x058
    uint32_t       _unknown2;      // 0x078
    bpoint_t       bpoint;         // 0x07C
    cpoint_t       cpoint;         // 0x088
    uint32_t       _unknown3[3];   // 0x0CC
    wpoint_t       wpoint;         // 0x0D8
    uint32_t       _unknown4[11];  // 0x0FC
    uint32_t       itrs_size;      // 0x128
    uint32_t       bdys_size;      // 0x12C
    itr_t*         itrs;           // 0x130
    bdy_t*         bdys;           // 0x134 (on 32-bit: 0x134, on 64-bit: 0x138)
#if INTPTR_MAX == INT32_MAX
    uint32_t       _unknown5[9];   // 0x138 - 0x15C
#else
    uint32_t       _unknown5[7];   // 0x140 - 0x15C
#endif
    char           name[4];        // 0x15C
    uint32_t       continue1;      // 0x160
    uint32_t       continue2;      // 0x164
    uint32_t       continue3;      // 0x168
    uint32_t       continue4;      // 0x16C
    uint32_t       sound;          // 0x170
    uint32_t       _unknown6;      // 0x174
};

#pragma pack(pop)

static_assert(sizeof(opoint_t) == 0x20, "opoint_t size must be 0x20 (32 bytes)");
static_assert(sizeof(bpoint_t) == 0x0C, "bpoint_t size must be 0x0C (12 bytes)");
static_assert(sizeof(cpoint_t) == 0x44, "cpoint_t size must be 0x44 (68 bytes)");
static_assert(sizeof(wpoint_t) == 0x24, "wpoint_t size must be 0x24 (36 bytes)");
static_assert(sizeof(frame_t) == 0x178, "frame_t size must be 0x178 (376 bytes)");

static_assert(offsetof(frame_t, present) == 0x000, "frame_t::present offset mismatch");
static_assert(offsetof(frame_t, state) == 0x008, "frame_t::state offset mismatch");
static_assert(offsetof(frame_t, wait) == 0x00C, "frame_t::wait offset mismatch");
static_assert(offsetof(frame_t, next) == 0x010, "frame_t::next offset mismatch");
static_assert(offsetof(frame_t, dvx) == 0x014, "frame_t::dvx offset mismatch");
static_assert(offsetof(frame_t, centerx) == 0x050, "frame_t::centerx offset mismatch");
static_assert(offsetof(frame_t, centery) == 0x054, "frame_t::centery offset mismatch");
static_assert(offsetof(frame_t, opoint) == 0x058, "frame_t::opoint offset mismatch");
static_assert(offsetof(frame_t, bpoint) == 0x07C, "frame_t::bpoint offset mismatch");
static_assert(offsetof(frame_t, cpoint) == 0x088, "frame_t::cpoint offset mismatch");
static_assert(offsetof(frame_t, wpoint) == 0x0D8, "frame_t::wpoint offset mismatch");
static_assert(offsetof(frame_t, itrs_size) == 0x128, "frame_t::itrs_size offset mismatch");
static_assert(offsetof(frame_t, bdys_size) == 0x12C, "frame_t::bdys_size offset mismatch");
static_assert(offsetof(frame_t, itrs) == 0x130, "frame_t::itrs offset mismatch");
static_assert(offsetof(frame_t, name) == 0x15C, "frame_t::name offset mismatch");
static_assert(offsetof(frame_t, sound) == 0x170, "frame_t::sound offset mismatch");

} // namespace lf2

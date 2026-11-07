#pragma once

#include <cstdint>
#include <cstddef>
#include "constants.h"
#include "types.h"
#include "itr.h"
#include "frame.h"

namespace lf2 {

#pragma pack(push, 4)

// Character / Weapon / Item definition loaded from .dat file
// Total Size: 0x25360 (152,416 bytes)
struct file_t {
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
    itr_t            attacking_itrs[5];     // 0x0B0 - 0x240 (1-based: index 0 at 0x0B0, entry 1..4 at 0x100..0x23F)
    uint8_t          _pad3[0x258];          // 0x240 - 0x498
    int32_t          bmp_count;             // 0x498
    char             bmp_paths[10][40];     // 0x49C - 0x62C (10 sprite sheet filenames)
    int32_t          sheet_start[10];       // 0x62C - 0x654 (first frame pic id for each sheet)
    int32_t          sheet_w[10];           // 0x654 - 0x67C (frame width)
    int32_t          sheet_h[10];           // 0x67C - 0x6A4 (frame height)
    int32_t          sheet_row[10];         // 0x6A4 - 0x6CC (rows in sheet)
    int32_t          sheet_col[10];         // 0x6CC - 0x6F4 (cols in sheet)
    uint32_t         id;                    // 0x6F4
    uint32_t         type;                  // 0x6F8
    uint32_t         head_bmp_mgr;          // 0x6FC
    char             head[40];              // 0x700
    uint32_t         small_bmp_mgr;         // 0x728
    char             small[36];             // 0x72C
    uint32_t         bmp_mgrs[10];          // 0x750 - 0x778
    uint32_t         mirror_bmp_mgrs[10];   // 0x778 - 0x7A0
    uint32_t         _pad6;                 // 0x7A0 - 0x7A4
    frame_t          frames[MAX_FRAMES];    // 0x7A4 - 0x25324 (400 * 0x178 = 0x24B80)
    char             name[60];              // 0x25324 - 0x25360
};

#pragma pack(pop)

static_assert(sizeof(file_t) == 0x25360, "file_t size must be exactly 0x25360 bytes");
static_assert(offsetof(file_t, walking_speed) == 0x008, "file_t::walking_speed offset mismatch");
static_assert(offsetof(file_t, walking_speedz) == 0x010, "file_t::walking_speedz offset mismatch");
static_assert(offsetof(file_t, running_speed) == 0x020, "file_t::running_speed offset mismatch");
static_assert(offsetof(file_t, jump_height) == 0x050, "file_t::jump_height offset mismatch");
static_assert(offsetof(file_t, weapon_hp) == 0x090, "file_t::weapon_hp offset mismatch");
static_assert(offsetof(file_t, weapon_hit_sound_id) == 0x0A4, "file_t::weapon_hit_sound_id offset mismatch");
static_assert(offsetof(file_t, attacking_itrs) == 0x0B0, "file_t::attacking_itrs offset mismatch");
static_assert(offsetof(file_t, attacking_itrs) + offsetof(itr_t, dvx) == 0x0C4, "file_t::attacking_itrs[0].dvx offset mismatch");
static_assert(offsetof(file_t, bmp_count) == 0x498, "file_t::bmp_count offset mismatch");
static_assert(offsetof(file_t, bmp_paths) == 0x49C, "file_t::bmp_paths offset mismatch");
static_assert(offsetof(file_t, sheet_start) == 0x62C, "file_t::sheet_start offset mismatch");
static_assert(offsetof(file_t, sheet_w) == 0x654, "file_t::sheet_w offset mismatch");
static_assert(offsetof(file_t, sheet_h) == 0x67C, "file_t::sheet_h offset mismatch");
static_assert(offsetof(file_t, sheet_row) == 0x6A4, "file_t::sheet_row offset mismatch");
static_assert(offsetof(file_t, sheet_col) == 0x6CC, "file_t::sheet_col offset mismatch");
static_assert(offsetof(file_t, id) == 0x6F4, "file_t::id offset mismatch");
static_assert(offsetof(file_t, type) == 0x6F8, "file_t::type offset mismatch");
static_assert(offsetof(file_t, head_bmp_mgr) == 0x6FC, "file_t::head_bmp_mgr offset mismatch");
static_assert(offsetof(file_t, head) == 0x700, "file_t::head offset mismatch");
static_assert(offsetof(file_t, small_bmp_mgr) == 0x728, "file_t::small_bmp_mgr offset mismatch");
static_assert(offsetof(file_t, small) == 0x72C, "file_t::small offset mismatch");
static_assert(offsetof(file_t, bmp_mgrs) == 0x750, "file_t::bmp_mgrs offset mismatch");
static_assert(offsetof(file_t, mirror_bmp_mgrs) == 0x778, "file_t::mirror_bmp_mgrs offset mismatch");
static_assert(offsetof(file_t, frames) == 0x7A4, "file_t::frames offset mismatch");
static_assert(offsetof(file_t, name) == 0x25324, "file_t::name offset mismatch");

} // namespace lf2

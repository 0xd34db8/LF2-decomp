#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x004061d0
 * Function: object_init / object_reset
 * Calling Convention: __thiscall (ECX = object_t*)
 */

#include <stdint.h>
#include <string.h>

void __thiscall func_004061d0_object_init(void* this_ptr)
{
    uint8_t* obj = (uint8_t*)this_ptr;

    // Reset velocities and accelerations (offsets 0x28 - 0x58)
    *(double*)(obj + 0x50) = 0.0; // z_velocity
    *(double*)(obj + 0x48) = 0.0; // y_velocity
    *(double*)(obj + 0x40) = 0.0; // x_velocity
    *(double*)(obj + 0x38) = 0.0; // z_accl
    *(double*)(obj + 0x30) = 0.0; // y_accl
    *(double*)(obj + 0x28) = 0.0; // pic_x_gain

    // Reset continuous positions (offsets 0x58 - 0x70)
    *(double*)(obj + 0x68) = 0.0; // z_position
    *(double*)(obj + 0x60) = 0.0; // y_position
    *(double*)(obj + 0x58) = 0.0; // x_position

    // Integer positions (offsets 0x10 - 0x1C)
    *(int32_t*)(obj + 0x10) = 0;   // x
    *(int32_t*)(obj + 0x14) = 0;   // y
    *(int32_t*)(obj + 0x18) = 0;   // z
    *(uint32_t*)(obj + 0x1c) = 0;

    // Counters and flags
    *(uint32_t*)(obj + 0x00) = 0;   // move_counter
    *(uint32_t*)(obj + 0x04) = 0;   // run_counter
    *(uint32_t*)(obj + 0x08) = 0;   // invincible_time
    *(uint32_t*)(obj + 0x0c) = 0;

    // Frame identifiers (offsets 0x70 - 0x80)
    *(uint32_t*)(obj + 0x70) = 0;   // frame_id1
    *(uint32_t*)(obj + 0x74) = 0;   // frame_id2
    *(uint32_t*)(obj + 0x78) = 0;   // frame_id3
    *(uint32_t*)(obj + 0x7c) = 0;   // frame_id4
    *(uint8_t*)(obj + 0x80)  = 0;   // facing (0 = right)
    *(uint32_t*)(obj + 0x84) = 0;
    *(uint32_t*)(obj + 0x88) = 0;   // wait_counter

    // Weapon & holding states
    *(uint32_t*)(obj + 0x8c) = 0;   // cpoint_catcher
    *(uint32_t*)(obj + 0x90) = 0;   // cpoint_timer
    *(uint32_t*)(obj + 0x94) = 0;
    *(uint32_t*)(obj + 0x98) = 0;   // weapon_type
    *(uint32_t*)(obj + 0x9c) = 0;   // weapon_id
    *(uint32_t*)(obj + 0xa0) = 0;   // holder_id
    *(uint32_t*)(obj + 0xa4) = 0;
    *(uint32_t*)(obj + 0xa8) = 0;
    *(uint32_t*)(obj + 0xac) = 0;
    *(int32_t*)(obj + 0xb0)  = 0;   // fall
    *(int32_t*)(obj + 0xb4)  = 0;   // shaking
    *(uint32_t*)(obj + 0xb8) = 0;   // bdefend

    // Keystates (offsets 0xCA - 0xD3)
    memset(obj + 0xbc, 0, 0x18);
    *(uint8_t*)(obj + 0xeb) = 0;

    // Combat statistics (offsets 0x348 - 0x35C)
    *(uint32_t*)(obj + 0x348) = 0;  // total_attack
    *(uint32_t*)(obj + 0x34c) = 0;  // hp_lost
    *(uint32_t*)(obj + 0x350) = 0;  // mp_used
    *(uint32_t*)(obj + 0x354) = 99; // owner (default 99 = unassigned)
    *(uint32_t*)(obj + 0x358) = 0;  // kills
    *(uint32_t*)(obj + 0x35c) = 0;  // get_weapon_counter
    *(uint32_t*)(obj + 0x364) = 0;  // team

    // HP & MP initialization (500 by default)
    *(int32_t*)(obj + 0x2fc) = 500; // hp
    *(int32_t*)(obj + 0x300) = 500; // dark_hp
    *(int32_t*)(obj + 0x304) = 500; // max_hp
    *(int32_t*)(obj + 0x308) = 500; // mp

    // Clear victim rest arrays (400 bytes at 0x0F0)
    memset(obj + 0x0f0, 0, 400);

    // Clear attack injury and itr buffers (20 slots)
    for (int i = 0; i < 20; ++i) {
        *(int32_t*)(obj + 0x280 + i * 4) = 0;
        *(uint8_t*)(obj + 0x2d0 + i) = 0;
    }

    // Default distance thresholds
    *(int32_t*)(obj + 0x2e4) = 0;    // successful_attacks
    *(int32_t*)(obj + 0x2e8) = 1000; // attackable_distance
    *(int32_t*)(obj + 0x2ec) = 1000; // vulnerable_distance
    *(int32_t*)(obj + 0x2f0) = 1000;
}


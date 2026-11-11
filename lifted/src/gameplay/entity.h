#pragma once

#include <cstdint>
#include "core/object.h"
#include "core/global.h"

namespace lf2 {

// 1:1 Lift of 0x004061d0: Initializes/resets an object_t instance
void object_init(object_t* obj);

// 1:1 Lift of 0x004061A0: 1D interval betweenness test (checks if b is strictly between a and c)
inline bool is_between(int32_t a, int32_t b, int32_t c) {
    return ((a < b && b < c) || (c < b && b < a));
}

// 1:1 Lift of 0x004196F0: Physics velocity/impulse averaging pass across all active objects
void world_average_velocities(global_t* world);

// 1:1 Lift of 0x004197A0: Network / remote input bit unpacking and holding state latching
void slot_unpack_network_inputs(global_t* world, const uint8_t* packet_bytes, int32_t clear_mode);

// 1:1 Lift of 0x004198F0: Local player input latching & replay recording
void slot_latch_local_inputs(global_t* world, const int32_t* slot_types, const uint8_t* input_bytes,
                             int32_t clear_mode, bool record_replay = false, uint8_t* replay_out = nullptr, size_t replay_idx = 0);

// 1:1 Lift of 0x00406a20: Spawns an opoint object/projectile in world->objects[50..399]
int32_t object_spawn_opoint(global_t* world, int32_t file_id, int32_t owner, int32_t frame_id,
                            int32_t team, int32_t x, int32_t y, int32_t z,
                            double vx, double vy, double vz, uint8_t facing);

// 1:1 Lift of 0x00406ba0: Processes hit_Fa homing/chase/volcano projectile physics
void object_process_hit_fa(global_t* world, int32_t obj_idx);

// 1:1 Lift of 0x00417F80: Integrates continuous 3D velocity and rounds to integer coordinates
void object_update_motion(object_t* obj, int32_t stage_z_min = 0, int32_t stage_z_max = 400, int32_t stage_width = 2000);

// Applies vertical gravity acceleration and ground impact collision
void object_update_physics(object_t* obj);

// Decays horizontal and depth sliding velocity when grounded
void object_apply_ground_friction(object_t* obj, double friction = 0.6);

// Player controller input state
struct input_state_t {
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool attack = false;
    bool jump = false;
    bool defend = false;
};

// Processes player inputs and executes character state machine transitions
void object_handle_input(object_t* obj, const input_state_t& input);

// Advances frame wait counter, updates frame history, and transitions to frame->next
// Returns false if entity has expired (next == 999 or 1000)
bool object_tick_frame(object_t* obj);

} // namespace lf2


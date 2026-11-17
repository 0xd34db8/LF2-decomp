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

// 1:1 Lift of 0x00417200: Broad-phase 2D bounding box overlap check between attacker and injured
bool is_broadphase_overlap(const global_t* world, uint32_t attacker_id, uint32_t injured_id);

// 1:1 Lift of 0x00419380: Per-frame frame_id4/arest update, pairwise vrest decrement & collision dispatch
void world_step_collisions(global_t* world, uint32_t mode = 0);

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

// 1:1 Lift of 0x0040D960: Per-object frame timer, sound trigger & frame.next advancement
void object_frame_advance(object_t* obj, int32_t mode = 0, int32_t obj_idx = 0, int32_t difficulty = 1, bool match_running = true);

// 1:1 Lift of 0x0040E170: Combo timer == 5 interruption check helper
int32_t object_combo_interrupted(const object_t* obj, char expected_key, int32_t advanced);

// 1:1 Lift of 0x0040E2D0: Frame transition & HP/MP cost helper
int32_t object_frame_transition(object_t* obj, int32_t target_frame, bool match_running = true);

// 1:1 Lift of 0x0040E450: 5-entry input history shift register
void object_input_history_push(object_t* obj, uint32_t key_code);

// 1:1 Lift of 0x0040E490: Per-object physics, velocity integration, gravity & ground landing
void object_physics_tick(object_t* obj, int32_t counter_12 = 0);

// 1:1 Lifts of 0x00412800..0x00412F40: 9 special-move combo recognizers
void object_combo_dra(object_t* obj, bool match_running = true);
void object_combo_dla(object_t* obj, bool match_running = true);
void object_combo_dua(object_t* obj, bool match_running = true);
void object_combo_dda(object_t* obj, bool match_running = true);
void object_combo_drj(object_t* obj, bool match_running = true);
void object_combo_dlj(object_t* obj, bool match_running = true);
void object_combo_duj(object_t* obj, bool match_running = true);
void object_combo_ddj(object_t* obj, bool match_running = true);
void object_combo_dja(object_t* obj, bool match_running = true, int32_t unlock_chars = 0);

// 1:1 Lift of 0x00413080: Master per-object input/state tick & combo dispatcher
void object_input_tick(object_t* obj, bool match_running = true, int32_t unlock_chars = 0);

// Integrates continuous 3D velocity, stage clamping with blocked_* flags, and truncates to integer coordinates
void object_update_motion(object_t* obj, int32_t stage_z_min = 0, int32_t stage_z_max = 400, int32_t stage_width = 2000);

// Applies vertical gravity acceleration and ground impact collision (delegates to object_physics_tick)
void object_update_physics(object_t* obj);

// Decays horizontal and depth sliding velocity when grounded (1:1 -1.0 linear decay with 0.0001 threshold)
void object_apply_ground_friction(object_t* obj, double friction = 1.0);

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

// Processes player inputs and executes character state machine transitions (delegates to object_input_tick)
void object_handle_input(object_t* obj, const input_state_t& input, bool match_running = true, int32_t unlock_chars = 0);

// Advances frame wait counter, updates frame history, and transitions to frame->next (delegates to object_frame_advance)
// Returns false if entity has expired (frame_id1 > 399 or frame == 1000)
bool object_tick_frame(object_t* obj, int32_t mode = 0, int32_t obj_idx = 0, int32_t difficulty = 1, bool match_running = true);

} // namespace lf2


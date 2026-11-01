#pragma once

#include <cstdint>
#include "core/object.h"

namespace lf2 {

// 1:1 Lift of 0x004061d0: Initializes/resets an object_t instance
void object_init(object_t* obj);

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


#include "entity.h"
#include <cmath>
#include <cstring>
#include <algorithm>

namespace lf2 {

void object_init(object_t* obj)
{
    if (!obj) return;

    // Reset velocities and accelerations (offsets 0x28 - 0x58)
    obj->pic_x_gain = 0.0;
    obj->y_accl = 0.0;
    obj->z_accl = 0.0;
    obj->x_velocity = 0.0;
    obj->y_velocity = 0.0;
    obj->z_velocity = 0.0;

    // Reset continuous positions (offsets 0x58 - 0x70)
    obj->x_position = 0.0;
    obj->y_position = 0.0;
    obj->z_position = 0.0;

    // Integer positions (offsets 0x10 - 0x1C)
    obj->x = 0;
    obj->y = 0;
    obj->z = 0;
    obj->_unknown2 = 0;

    // Counters and timers
    obj->move_counter = 0;
    obj->run_counter = 0;
    obj->invincible_time = 0;
    obj->_unknown1 = 0;

    // Frame indices & facing
    obj->frame_id1 = 0;
    obj->frame_id2 = 0;
    obj->frame_id3 = 0;
    obj->frame_id4 = 0;
    obj->facing = 0; // 0 = right
    obj->_unknown7 = 0;
    obj->wait_counter = 0;

    // Weapon & grapple states
    obj->cpoint_catcher = 0;
    obj->cpoint_timer = 0;
    obj->_unknown8 = 0;
    obj->weapon_type = 0;
    obj->weapon_id = 0;
    obj->holder_id = 0;
    obj->fall = 0;
    obj->shaking = 0;
    obj->bdefend = 0;

    // Clear input & button states
    obj->holding_attack = 0;
    obj->click_attack = 0;
    std::memset(obj->_unknown12, 0, sizeof(obj->_unknown12));
    std::memset(obj->_unknown13, 0, sizeof(obj->_unknown13));
    std::memset(obj->_unknown14, 0, sizeof(obj->_unknown14));

    // Combat statistics
    obj->total_attack = 0;
    obj->hp_lost = 0;
    obj->mp_used = 0;
    obj->owner = 99; // Default unassigned owner
    obj->kills = 0;
    obj->get_weapon_counter = 0;
    obj->team = 0;

    // Standard starting vitals
    obj->hp = 500;
    obj->dark_hp = 500;
    obj->max_hp = 500;
    obj->mp = 500;

    // Clear victim rest table (400 bytes)
    std::memset(obj->vrest_of_objects, 0, sizeof(obj->vrest_of_objects));

    // Clear attack injury and itr buffers
    for (int i = 0; i < 20; ++i) {
        obj->injured_of_attack[i] = 0;
        obj->itr_of_attack[i] = 0;
    }

    // Default distance thresholds
    obj->successful_attacks = 0;
    obj->attackable_distance = 1000;
    obj->vulnerable_distance = 1000;
}

void object_update_motion(object_t* obj, int32_t stage_z_min, int32_t stage_z_max, int32_t stage_width)
{
    if (!obj) return;

    // Continuous 3D integration
    obj->x_position += obj->x_velocity;
    obj->y_position += obj->y_velocity;
    obj->z_position += obj->z_velocity;

    // Stage boundary clamping
    if (obj->z_position < static_cast<double>(stage_z_min)) {
        obj->z_position = static_cast<double>(stage_z_min);
    } else if (obj->z_position > static_cast<double>(stage_z_max)) {
        obj->z_position = static_cast<double>(stage_z_max);
    }

    if (obj->x_position < 0.0) {
        obj->x_position = 0.0;
    } else if (obj->x_position > static_cast<double>(stage_width)) {
        obj->x_position = static_cast<double>(stage_width);
    }

    // Ground plane collision (y = 0 is ground surface in LF2)
    if (obj->y_position >= 0.0) {
        obj->y_position = 0.0;
        if (obj->y_velocity > 0.0) {
            obj->y_velocity = 0.0;
        }
    }

    // Mathematical integer projection (0x00417F80 / 0x004450D0)
    obj->x = static_cast<int32_t>(std::round(obj->x_position));
    obj->y = static_cast<int32_t>(std::round(obj->y_position));
    obj->z = static_cast<int32_t>(std::round(obj->z_position));
}

void object_update_physics(object_t* obj)
{
    if (!obj) return;

    // In LF2 coordinate conventions, negative Y represents elevation in the air
    if (obj->y_position < 0.0) {
        // Apply gravitational acceleration downward toward ground plane
        obj->y_velocity += 1.0;
    } else if (obj->y_position >= 0.0) {
        // Ground impact & landing resolution
        obj->y_position = 0.0;
        obj->y = 0;
        if (obj->y_velocity > 0.0) {
            obj->y_velocity = 0.0;
        }
    }
}

void object_apply_ground_friction(object_t* obj, double friction)
{
    if (!obj) return;

    // Friction only decelerates movement while grounded (y == 0)
    if (obj->y == 0 && obj->y_position == 0.0) {
        if (obj->x_velocity > 0.0) {
            obj->x_velocity = std::max(0.0, obj->x_velocity - friction);
        } else if (obj->x_velocity < 0.0) {
            obj->x_velocity = std::min(0.0, obj->x_velocity + friction);
        }

        if (obj->z_velocity > 0.0) {
            obj->z_velocity = std::max(0.0, obj->z_velocity - friction);
        } else if (obj->z_velocity < 0.0) {
            obj->z_velocity = std::min(0.0, obj->z_velocity + friction);
        }
    }
}

bool object_tick_frame(object_t* obj)
{
    if (!obj || !obj->file) return true;

    if (obj->frame_id1 >= 400) {
        return false;
    }

    const auto& cur_frame = obj->file->frames[obj->frame_id1];

    obj->wait_counter++;

    // When wait counter expires, advance frame
    if (obj->wait_counter >= std::max<uint32_t>(1u, cur_frame.wait)) {
        obj->wait_counter = 0;

        // Shift frame history
        obj->frame_id4 = obj->frame_id3;
        obj->frame_id3 = obj->frame_id2;
        obj->frame_id2 = obj->frame_id1;

        // Check for entity expiration (standard LF2 particle / effect disposal tags)
        if (cur_frame.next == 999 || cur_frame.next == 1000) {
            return false;
        }

        obj->frame_id1 = static_cast<uint32_t>(cur_frame.next);
    }

    return true;
}

void object_handle_input(object_t* obj, const input_state_t& input)
{
    if (!obj || !obj->file) return;

    if (obj->frame_id1 >= MAX_FRAMES) return;

    const auto& cur_frame = obj->file->frames[obj->frame_id1];
    uint32_t state = cur_frame.state;

    // Handle jump landing frame transition (State 4 landing on ground)
    if (state == STATE_JUMPING && obj->y == 0 && obj->y_position == 0.0) {
        if (obj->frame_id1 >= 210 && obj->frame_id1 <= 214) {
            obj->frame_id1 = 215; // Landing frame
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            obj->z_velocity = 0.0;
            return;
        }
    }

    // State 0: Standing / Idle
    if (state == STATE_STANDING) {
        if (input.jump) {
            double jh = (obj->file->jump_height > 0.0) ? obj->file->jump_height : 11.0;
            obj->y_velocity = -jh;
            obj->y_position = -1.0;
            obj->frame_id1 = 210;
            obj->wait_counter = 0;

            double jd = (obj->file->jump_distance > 0.0) ? obj->file->jump_distance : 4.0;
            double jdz = (obj->file->jump_distancez > 0.0) ? obj->file->jump_distancez : 2.0;

            if (input.left) {
                obj->facing = FACING_LEFT;
                obj->x_velocity = -jd;
            } else if (input.right) {
                obj->facing = FACING_RIGHT;
                obj->x_velocity = jd;
            } else {
                obj->x_velocity = 0.0;
            }

            if (input.up) {
                obj->z_velocity = -jdz;
            } else if (input.down) {
                obj->z_velocity = jdz;
            } else {
                obj->z_velocity = 0.0;
            }
            return;
        }

        if (input.attack) {
            obj->frame_id1 = 60; // Punch
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            obj->z_velocity = 0.0;
            return;
        }

        if (input.defend) {
            obj->frame_id1 = 110; // Guard
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            obj->z_velocity = 0.0;
            return;
        }

        if (input.left || input.right || input.up || input.down) {
            obj->frame_id1 = 5; // Walk start
            obj->wait_counter = 0;
            if (input.left) obj->facing = FACING_LEFT;
            else if (input.right) obj->facing = FACING_RIGHT;
            return;
        }
    }

    // State 1: Walking
    if (state == STATE_WALKING) {
        if (input.jump) {
            double jh = (obj->file->jump_height > 0.0) ? obj->file->jump_height : 11.0;
            obj->y_velocity = -jh;
            obj->y_position = -1.0;
            obj->frame_id1 = 210;
            obj->wait_counter = 0;

            double jd = (obj->file->jump_distance > 0.0) ? obj->file->jump_distance : 4.0;
            obj->x_velocity = (obj->facing == FACING_LEFT) ? -jd : jd;
            return;
        }

        if (input.attack) {
            obj->frame_id1 = 60;
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            return;
        }

        if (input.defend) {
            obj->frame_id1 = 110;
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            return;
        }

        if (!input.left && !input.right && !input.up && !input.down) {
            obj->frame_id1 = 0; // Return to idle
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            obj->z_velocity = 0.0;
            return;
        }

        if (input.left) obj->facing = FACING_LEFT;
        else if (input.right) obj->facing = FACING_RIGHT;

        double ws = (obj->file->walking_speed > 0.0) ? obj->file->walking_speed : 4.0;
        double wsz = (obj->file->walking_speedz > 0.0) ? obj->file->walking_speedz : 2.5;

        if (input.left) obj->x_velocity = -ws;
        else if (input.right) obj->x_velocity = ws;
        else obj->x_velocity = 0.0;

        if (input.up) obj->z_velocity = -wsz;
        else if (input.down) obj->z_velocity = wsz;
        else obj->z_velocity = 0.0;
    }

    // State 7: Defending / Guard
    if (state == STATE_DEFEND) {
        if (!input.defend) {
            obj->frame_id1 = 0; // Return to stance
            obj->wait_counter = 0;
        }
    }
}

} // namespace lf2

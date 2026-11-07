#include "entity.h"
#include "audio/audio.h"
#include <cmath>
#include <cstring>
#include <algorithm>

namespace lf2 {

void object_init(object_t* obj)
{
    if (!obj) return;

    std::memset(obj, 0, sizeof(object_t));

    // Exact ground-truth initializations from FUN_004061d0 (0x004061D0)
    obj->in_sky = 1; // 0x088
    std::memset(obj->key_state, 'u', sizeof(obj->key_state)); // 0x0BC - 0x0C5

    obj->attackable_distance = 1000;   // 0x2E8
    obj->vulnerable_distance = 1000;   // 0x2EC
    obj->clone = -1;                   // 0x2F4
    obj->under_attack_distance = 1000; // 0x2F8

    obj->hp = 500;                     // 0x2FC
    obj->dark_hp = 500;                // 0x300
    obj->max_hp = 500;                 // 0x304
    obj->mp = 500;                     // 0x308

    obj->weapon_hp = 1000;             // 0x31C
    obj->owner = -1;                   // 0x354
    obj->enemy = -1;                   // 0x360

    obj->ai_target_x = -1000;          // 0x3FC
    obj->ai_target_z = -1000;          // 0x400
}

int32_t object_spawn_opoint(global_t* world, int32_t file_id, int32_t owner, int32_t frame_id,
                            int32_t team, int32_t x, int32_t y, int32_t z,
                            double vx, double vy, double vz, uint8_t facing)
{
    if (!world) return -1;

    int32_t slot = -1;
    for (int32_t i = 50; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
        if (world->is_object_exists[i] == 0) {
            slot = i;
            break;
        }
    }
    if (slot == -1) return -1;

    for (uint32_t f = 0; f < MAX_FILES; ++f) {
        file_t* file = world->files[f];
        if (file && static_cast<int32_t>(file->id) == file_id) {
            object_t* obj = world->objects[slot];
            if (!obj) return -1;
            object_init(obj);
            obj->file = file;
            obj->weapon_hp = file->weapon_hp;
            obj->owner = owner;
            obj->x = x;
            obj->y = y;
            obj->z = z;
            obj->team = static_cast<uint32_t>(team);
            obj->x_position = static_cast<double>(x);
            obj->y_position = static_cast<double>(y);
            obj->z_position = static_cast<double>(z);
            obj->frame_id1 = static_cast<uint32_t>(frame_id);
            obj->x_velocity = vx;
            obj->y_velocity = vy;
            obj->z_velocity = vz;
            obj->facing = facing;
            world->is_object_exists[slot] = 1;
            return slot;
        }
    }
    return -1;
}

void object_process_hit_fa(global_t* world, int32_t obj_idx)
{
    if (!world || obj_idx < 0 || obj_idx >= static_cast<int32_t>(MAX_OBJECTS) || !world->is_object_exists[obj_idx]) return;
    object_t* proj = world->objects[obj_idx];
    if (!proj || !proj->file || proj->frame_id1 >= MAX_FRAMES) return;

    int32_t hit_fa = static_cast<int32_t>(proj->file->frames[proj->frame_id1].hit_Fa);
    if (hit_fa == 1 || hit_fa == 2 || hit_fa == 7 || hit_fa == 10 || hit_fa == 13 || hit_fa == 14) {
        int32_t best_target = -1;
        int32_t best_dist = 10000;
        for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
            if (!world->is_object_exists[i]) continue;
            object_t* cand = world->objects[i];
            if (!cand || !cand->file || cand->file->type != TYPE_CHARACTER) continue;
            if (cand->team == proj->team || cand->hp <= 0) continue;
            int32_t d = std::abs(cand->x - proj->x) + std::abs(cand->z - proj->z);
            if (d < best_dist) {
                best_dist = d;
                best_target = i;
            }
        }
        if (best_target >= 0) {
            object_t* tgt = world->objects[best_target];
            proj->enemy = best_target;
            if (tgt->x > proj->x) {
                proj->x_velocity += 1.0;
                if (proj->x_velocity > 14.0) proj->x_velocity = 14.0;
                proj->facing = FACING_RIGHT;
            } else if (tgt->x < proj->x) {
                proj->x_velocity -= 1.0;
                if (proj->x_velocity < -14.0) proj->x_velocity = -14.0;
                proj->facing = FACING_LEFT;
            }
            if (tgt->z > proj->z) {
                proj->z_velocity += 0.5;
                if (proj->z_velocity > 3.0) proj->z_velocity = 3.0;
            } else if (tgt->z < proj->z) {
                proj->z_velocity -= 0.5;
                if (proj->z_velocity < -3.0) proj->z_velocity = -3.0;
            }
        }
    }
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
        obj->in_sky = 0;
        if (obj->y_velocity > 0.0) {
            obj->y_velocity = 0.0;
        }
    } else {
        obj->in_sky = 1;
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
        double grav = (obj->y_accl != 0.0) ? obj->y_accl : 1.0;
        obj->y_velocity += grav;
    } else if (obj->y_position >= 0.0) {
        // Ground impact & landing resolution
        obj->y_position = 0.0;
        obj->y = 0;
        obj->in_sky = 0;
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

static void apply_frame_dv(object_t* obj, const frame_t& f)
{
    if (f.dvx == 550) {
        obj->x_velocity = 0.0;
    } else if (f.dvx != 0) {
        obj->x_velocity = (obj->facing == FACING_LEFT) ? -static_cast<double>(f.dvx) : static_cast<double>(f.dvx);
    }
    if (f.dvy == 550) {
        obj->y_velocity = 0.0;
    } else if (f.dvy != 0) {
        obj->y_velocity += static_cast<double>(f.dvy);
    }
    if (f.dvz == 550) {
        obj->z_velocity = 0.0;
    } else if (f.dvz != 0) {
        obj->z_velocity = static_cast<double>(f.dvz);
    }
}

bool object_tick_frame(object_t* obj)
{
    if (!obj || !obj->file) return true;

    if (obj->frame_id1 >= MAX_FRAMES) {
        return false;
    }

    const auto& cur_frame = obj->file->frames[obj->frame_id1];

    obj->wait_counter++;

    // When wait counter expires, advance frame
    int32_t wait_threshold = std::max<int32_t>(1, static_cast<int32_t>(cur_frame.wait));
    if (cur_frame.state == STATE_WALKING) {
        wait_threshold = std::max<int32_t>(1, static_cast<int32_t>(obj->file->walking_frame_rate + 1));
    }

    if (obj->wait_counter >= wait_threshold) {
        obj->wait_counter = 0;

        // Shift frame history
        obj->frame_id4 = obj->frame_id3;
        obj->frame_id3 = obj->frame_id2;
        obj->frame_id2 = obj->frame_id1;

        uint32_t prev_frame = obj->frame_id1;

        // Authentic LF2 walking frame cycling (State 1: 5 -> 6 -> 7 -> 8 -> 7 -> 6 -> 5...)
        if (cur_frame.state == STATE_WALKING) {
            static const uint32_t walk_sequence[6] = {5, 6, 7, 8, 7, 6};
            obj->move_counter = (obj->move_counter + 1) % 6;
            obj->frame_id1 = walk_sequence[obj->move_counter];
        } else if (cur_frame.next == 1000) {
            // Particle / effect disposal
            return false;
        } else if (cur_frame.next == 999) {
            // Authentic LF2 behavior: next == 999 loops back to frame 0 (standing stance)
            obj->frame_id1 = 0;
        } else if (cur_frame.next < 0) {
            obj->facing = (obj->facing == FACING_RIGHT) ? FACING_LEFT : FACING_RIGHT;
            obj->frame_id1 = static_cast<uint32_t>(-cur_frame.next);
        } else {
            obj->frame_id1 = static_cast<uint32_t>(cur_frame.next);
        }

        // Apply frame dvx/dvy/dvz and sound on frame transition
        if (obj->frame_id1 != prev_frame && obj->frame_id1 < MAX_FRAMES) {
            const auto& next_frame = obj->file->frames[obj->frame_id1];
            apply_frame_dv(obj, next_frame);
            uint32_t snd = next_frame.sound;
            if (snd != 0) {
                get_audio_system().on_frame_sound(snd);
            }
        }
        return true;
    }

    return true;
}

static bool try_special_move(object_t* obj, uint32_t target_frame_id)
{
    if (target_frame_id == 0 || target_frame_id >= MAX_FRAMES) return false;
    const auto& target_frame = obj->file->frames[target_frame_id];
    int32_t mp_cost = target_frame.mp % 1000;
    if (mp_cost > 0 && obj->mp < mp_cost) return false;
    if (mp_cost > 0) {
        obj->mp -= mp_cost;
        obj->mp_used += static_cast<uint32_t>(mp_cost);
    }
    obj->frame_id1 = target_frame_id;
    obj->wait_counter = 0;
    apply_frame_dv(obj, target_frame);
    return true;
}

void object_handle_input(object_t* obj, const input_state_t& input)
{
    if (!obj || !obj->file) return;

    if (obj->frame_id1 >= MAX_FRAMES) return;

    uint32_t prev_frame = obj->frame_id1;
    const auto& cur_frame = obj->file->frames[obj->frame_id1];
    uint32_t state = cur_frame.state;

    // Update holding & click states on object_t (0x0C6 - 0x0D3)
    obj->click_up     = (input.up     && !obj->holding_up)     ? 1 : 0;
    obj->click_down   = (input.down   && !obj->holding_down)   ? 1 : 0;
    obj->click_left   = (input.left   && !obj->holding_left)   ? 1 : 0;
    obj->click_right  = (input.right  && !obj->holding_right)  ? 1 : 0;
    obj->click_attack = (input.attack && !obj->holding_attack) ? 1 : 0;
    obj->click_jump   = (input.jump   && !obj->holding_jump)   ? 1 : 0;
    obj->click_defend = (input.defend && !obj->holding_defend) ? 1 : 0;

    obj->holding_up     = input.up     ? 1 : 0;
    obj->holding_down   = input.down   ? 1 : 0;
    obj->holding_left   = input.left   ? 1 : 0;
    obj->holding_right  = input.right  ? 1 : 0;
    obj->holding_jump   = input.jump   ? 1 : 0;
    obj->holding_defend = input.defend ? 1 : 0;

    // Check .dat-defined special move transitions (D>A, D^A, DvA, D>J, D^J, DvJ, J+A) from FUN_00419380
    bool forward_held = (obj->facing == FACING_RIGHT && input.right) || (obj->facing == FACING_LEFT && input.left);
    if (input.defend) {
        if (forward_held && input.attack && try_special_move(obj, cur_frame.hit_Fa)) goto finish_input;
        if (input.up     && input.attack && try_special_move(obj, cur_frame.hit_Ua)) goto finish_input;
        if (input.down   && input.attack && try_special_move(obj, cur_frame.hit_Da)) goto finish_input;
        if (forward_held && input.jump   && try_special_move(obj, cur_frame.hit_Fj)) goto finish_input;
        if (input.up     && input.jump   && try_special_move(obj, cur_frame.hit_Uj)) goto finish_input;
        if (input.down   && input.jump   && try_special_move(obj, cur_frame.hit_Dj)) goto finish_input;
    }
    if (input.jump && input.attack && try_special_move(obj, cur_frame.hit_ja)) goto finish_input;

    // Handle jump landing frame transition (State 4 landing on ground)
    if (state == STATE_JUMPING && obj->y == 0 && obj->y_position == 0.0) {
        if (obj->frame_id1 >= 210 && obj->frame_id1 <= 214) {
            obj->frame_id1 = 215; // Landing frame
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            obj->z_velocity = 0.0;
            goto finish_input;
        }
    }

    // State 0: Standing / Idle
    if (state == STATE_STANDING) {
        if (input.jump) {
            double jh = (std::abs(obj->file->jump_height) > 0.0) ? std::abs(obj->file->jump_height) : 11.0;
            obj->y_velocity = -jh;
            obj->y_position = -1.0;
            obj->in_sky = 1;
            obj->frame_id1 = (cur_frame.hit_j != 0) ? cur_frame.hit_j : 210;
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
            goto finish_input;
        }

        if (input.attack) {
            obj->frame_id1 = (cur_frame.hit_a != 0) ? cur_frame.hit_a : 60; // Punch 1
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            obj->z_velocity = 0.0;
            goto finish_input;
        }

        if (input.defend) {
            obj->frame_id1 = (cur_frame.hit_d != 0) ? cur_frame.hit_d : 110; // Guard
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            obj->z_velocity = 0.0;
            goto finish_input;
        }

        if (input.left || input.right || input.up || input.down) {
            obj->move_counter = 0;
            obj->frame_id1 = 5; // Walk start
            obj->wait_counter = 0;
            if (input.left) obj->facing = FACING_LEFT;
            else if (input.right) obj->facing = FACING_RIGHT;
            goto finish_input;
        }
    }

    // State 1: Walking
    if (state == STATE_WALKING) {
        if (input.jump) {
            double jh = (std::abs(obj->file->jump_height) > 0.0) ? std::abs(obj->file->jump_height) : 11.0;
            obj->y_velocity = -jh;
            obj->y_position = -1.0;
            obj->in_sky = 1;
            obj->frame_id1 = (cur_frame.hit_j != 0) ? cur_frame.hit_j : 210;
            obj->wait_counter = 0;

            double jd = (obj->file->jump_distance > 0.0) ? obj->file->jump_distance : 4.0;
            obj->x_velocity = (obj->facing == FACING_LEFT) ? -jd : jd;
            goto finish_input;
        }

        if (input.attack) {
            obj->frame_id1 = (cur_frame.hit_a != 0) ? cur_frame.hit_a : 60; // Punch 1
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            goto finish_input;
        }

        if (input.defend) {
            obj->frame_id1 = (cur_frame.hit_d != 0) ? cur_frame.hit_d : 110;
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            goto finish_input;
        }

        if (!input.left && !input.right && !input.up && !input.down) {
            obj->move_counter = 0;
            obj->frame_id1 = 0; // Return to idle
            obj->wait_counter = 0;
            obj->x_velocity = 0.0;
            obj->z_velocity = 0.0;
            goto finish_input;
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

    // State 3: Attack / Punch combos
    if (state == STATE_ATTACKING) {
        if (input.attack && !obj->holding_attack) {
            if (cur_frame.hit_a != 0) {
                obj->frame_id1 = cur_frame.hit_a;
                obj->wait_counter = 0;
            } else if (obj->frame_id1 >= 60 && obj->frame_id1 <= 63) {
                obj->frame_id1 = 65; // Punch 2 combo
                obj->wait_counter = 0;
            } else if (obj->frame_id1 >= 65 && obj->frame_id1 <= 68) {
                obj->frame_id1 = 70; // Punch 3 / Finisher
                obj->wait_counter = 0;
            }
        }
    }

    // State 7: Defending / Guard
    if (state == STATE_DEFEND) {
        if (!input.defend) {
            obj->frame_id1 = 0; // Return to stance
            obj->wait_counter = 0;
        }
    }

finish_input:
    obj->holding_attack = input.attack ? 1 : 0;

    // Trigger authentic audio when input causes frame transition
    if (obj->frame_id1 != prev_frame && obj->frame_id1 < MAX_FRAMES) {
        uint32_t snd = obj->file->frames[obj->frame_id1].sound;
        if (snd != 0) {
            get_audio_system().on_frame_sound(snd);
        }
    }
}

} // namespace lf2

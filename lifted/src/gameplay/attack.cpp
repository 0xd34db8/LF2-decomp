#include "global.h"
#include "overlap.h"
#include "random.h"
#include "entity.h"
#include <cstdlib>

namespace lf2 {

// func_00417400: Check and resolve attack collision between attacker and injured entity
// ECX: global_t* this
// param_1: attacker_id
// param_2: injured_id
// param_3: mode (0: normal / vs, 1: stage)
void global_t::does_attack_success(uint32_t attacker_id, uint32_t injured_id, uint32_t mode) {
    if (attacker_id >= MAX_OBJECTS || !is_object_exists[attacker_id] ||
        injured_id >= MAX_OBJECTS || !is_object_exists[injured_id]) {
        return;
    }

    object_t* attacker = objects[attacker_id];
    object_t* injured = objects[injured_id];
    if (!attacker || !attacker->file || !injured || !injured->file) {
        return;
    }

    file_t* attacker_file = attacker->file;
    file_t* injured_file = injured->file;

    uint32_t a_frame_id4 = attacker->frame_id4;
    uint32_t i_frame_id4 = injured->frame_id4;
    if (a_frame_id4 >= MAX_FRAMES || i_frame_id4 >= MAX_FRAMES) {
        return;
    }

    frame_t* a_frame4 = &attacker_file->frames[a_frame_id4];
    frame_t* i_frame4 = &injured_file->frames[i_frame_id4];

    uint32_t a_frame_id1 = attacker->frame_id1;
    uint32_t i_frame_id1 = injured->frame_id1;
    frame_t* a_frame1 = (a_frame_id1 < MAX_FRAMES) ? &attacker_file->frames[a_frame_id1] : a_frame4;
    frame_t* i_frame1 = (i_frame_id1 < MAX_FRAMES) ? &injured_file->frames[i_frame_id1] : i_frame4;

    uint32_t a_frame_id3 = attacker->frame_id3;
    uint32_t i_frame_id3 = injured->frame_id3;
    frame_t* a_frame3 = (a_frame_id3 < MAX_FRAMES) ? &attacker_file->frames[a_frame_id3] : a_frame4;
    frame_t* i_frame3 = (i_frame_id3 < MAX_FRAMES) ? &injured_file->frames[i_frame_id3] : i_frame4;

    for (uint32_t itr_id = 0; itr_id < a_frame4->itrs_size; ++itr_id) {
        itr_t* itr = &a_frame4->itrs[itr_id];

        for (uint32_t bdy_id = 0; bdy_id < i_frame4->bdys_size; ++bdy_id) {
            bdy_t* bdy = &i_frame4->bdys[bdy_id];

            // 1. Freeze ball immunity check
            uint32_t a_file_id = attacker_file->id;
            if ((a_file_id == 200 || a_file_id == 203 || a_file_id == 205 ||
                 a_file_id == 206 || a_file_id == 207 || a_file_id == 215 ||
                 a_file_id == 216) &&
                injured_file->id == 209 && itr->kind != 9) {
                break;
            }

            // 2. Catch only character
            if (itr->kind == 3 && injured_file->type != TYPE_CHARACTER) {
                break;
            }

            // 3. Normal attack (kind == 0) special effects
            if (itr->kind == 0) {
                if (itr->effect == 4 && injured_file->type == TYPE_CHARACTER) {
                    break;
                }
                if (itr->effect == 20 &&
                    (injured_file->type != TYPE_CHARACTER ||
                     i_frame3->state == 18 || i_frame3->state == 19)) {
                    break;
                }
                if (itr->effect == 21 && (i_frame3->state == 18 || i_frame3->state == 19)) {
                    break;
                }
                if (itr->effect == 30 && (i_frame_id1 >= 200 && i_frame_id1 <= 203)) {
                    break;
                }
                if (itr->effect == 2 && a_frame3->state == 19 && i_frame3->state == 18) {
                    break;
                }
            }

            // 4. Heal kind check
            if (itr->kind == 8 && injured_file->type != TYPE_CHARACTER) {
                break;
            }

            // 5. Invincibility check
            if (injured->invincible_time != 0 && itr->kind != 8 && itr->kind != 14) {
                break;
            }

            // 6. Friendly fire / Team checks
            if (itr->kind < 4 || itr->kind == 6 ||
                (itr->kind == 9 && injured_file->type == TYPE_CHARACTER) ||
                itr->kind == 10 || itr->kind == 11 || itr->kind == 15 || itr->kind == 16) {
                
                if (i_frame1->state != 13 && i_frame1->state != 10 &&
                    (injured_file->id != 212 ||
                     (attacker_file->id == 212 && (i_frame_id1 % 10 != 5 || a_frame_id1 % 10 != 0)))) {
                    
                    if (attacker->team == injured->team && attacker->team != 0 && itr->kind != 8 &&
                        (a_frame1->state != 18 || (itr->effect == 21 || itr->effect == 22)) &&
                        (attacker_file->type != TYPE_CHARACTER || injured_file->type != 3 ||
                         attacker->facing == injured->facing) &&
                        (injured_file->type != 1 && injured_file->type != 2 &&
                         injured_file->type != 4 && injured_file->type != 6)) {
                        break;
                    }
                }
            }

            // 7. Weapon strength list team check
            if (itr->kind == 5) {
                uint32_t h_id = attacker->holder_id;
                if (h_id < MAX_OBJECTS && is_object_exists[h_id]) {
                    object_t* holder = objects[h_id];
                    if (holder && holder->team == injured->team && holder->team != 0 &&
                        i_frame1->state != 13 &&
                        (injured_file->type != 1 && injured_file->type != 2 &&
                         injured_file->type != 4 && injured_file->type != 6) &&
                        (injured_file->id != 212 ||
                         (attacker_file->id == 212 && (i_frame_id1 % 10 != 5 || holder->frame_id1 % 10 != 0)))) {
                        break;
                    }
                }
            }

            // 8. Calculate world-space bounding box coordinates
            int32_t bdy_left;
            if (injured->facing == FACING_RIGHT) {
                bdy_left = bdy->x + (injured->x - i_frame4->centerx);
            } else {
                bdy_left = ((i_frame4->centerx + injured->x) - bdy->w) - bdy->x;
            }
            int32_t bdy_top = bdy->y + (injured->y - i_frame4->centery);

            int32_t itr_left;
            if (attacker->facing == FACING_RIGHT) {
                itr_left = itr->x + (attacker->x - a_frame4->centerx);
            } else {
                itr_left = ((attacker->x + a_frame4->centerx) - itr->w) - itr->x;
            }
            int32_t itr_top = itr->y + (attacker->y - a_frame4->centery);

            // 9. Z-depth tolerance check
            int32_t zwidth = (itr->zwidth != 0) ? static_cast<int32_t>(itr->zwidth) : 15;
            int32_t diff_z = std::abs(attacker->z - injured->z);
            if (diff_z >= zwidth) {
                continue;
            }

            // 10. 2D Hitbox Overlap check
            if (!is_itr_bdy_overlap(bdy_left, bdy_top, bdy->w, bdy->h,
                                    itr_left, itr_top, itr->w, itr->h)) {
                continue;
            }

            // 11. Overlap confirmed! Now process hit eligibility
            bool hit_fail = false;
            if (i_frame1->state == 12 && itr->fall <= 40 && itr->kind != 10 && itr->kind != 11) {
                hit_fail = true;
            }

            if (mode == 1) { // Stage mode
                bool can_rescue = false;
                if ((attacker_file->type == TYPE_CHARACTER || attacker_file->id == 201 || attacker_file->id == 202) &&
                    attacker->team != 5) {
                    can_rescue = true;
                }
                uint32_t h_id = attacker->holder_id;
                if (attacker->weapon_type != 0 && h_id < MAX_OBJECTS && is_object_exists[h_id]) {
                    object_t* holder = objects[h_id];
                    if (holder && holder->file->type == TYPE_CHARACTER && holder->team != 5) {
                        can_rescue = true;
                    }
                }
                if (bdy->kind >= 1000 && !can_rescue) {
                    hit_fail = true;
                }
            }

            // 12. Register hit into attacker queue
            if (itr->vrest != 0 || itr->kind == 1 || itr->kind == 2 || itr->kind == 7 ||
                (i_frame4->state == 1004 && (attacker_file->type < 1 || attacker->weapon_type != 0)) ||
                hit_fail) {

                if (attacker->successful_attacks >= 20 || hit_fail) {
                    continue;
                }

                int32_t flag = 0;
                if (i_frame4->state == 1004 &&
                    (attacker_file->type < 1 || attacker->weapon_type != 0) &&
                    itr->kind != 2 && itr->kind != 7 && itr->kind != 10) {
                    flag = 2;
                }

                if (itr->kind == 1) {
                    int32_t dist_x = std::abs(attacker->x - injured->x);
                    if (dist_x < injured->vulnerable_distance ||
                        (dist_x == injured->vulnerable_distance && lf2_random(0x86, 2) == 0)) {
                        injured->vulnerable_distance = dist_x;
                    } else {
                        flag = 2;
                    }
                }

                if (itr->kind == 4 && attacker->thrown_injury != 0 && flag != 2) {
                    flag = 1;
                }

                if (itr->kind == 1 &&
                    ((attacker->holding_attack && attacker->x < injured->x) ||
                     (attacker->click_attack && injured->x <= attacker->x)) &&
                    i_frame1->state == 16) {
                    if (flag != 2) flag = 1;
                } else if (itr->kind != 1 && itr->kind != 2 && itr->kind != 7) {
                    if (flag != 2) flag = 1;
                }

                if (itr->kind == 2) {
                    if (attacker->weapon_type == 0 && attacker->click_attack && !attacker->holding_attack &&
                        i_frame1->state == 1004 && flag != 2) {
                        flag = 1;
                    }
                    if (attacker->click_attack && !attacker->holding_attack &&
                        i_frame1->state == 2004 && flag != 2) {
                        flag = 1;
                    }
                }

                if ((itr->kind == 7 && attacker->click_attack && !attacker->holding_attack &&
                     i_frame1->state == 1004 && flag != 2) || flag == 1) {
                    
                    int32_t slot = attacker->successful_attacks;
                    attacker->injured_of_attack[slot] = static_cast<int32_t>(injured_id);
                    attacker->itr_of_attack[slot] = static_cast<uint8_t>(itr_id);
                    attacker->successful_attacks++;
                }
            } else {
                // Tracking minimum attackable distance target
                int32_t dist_x = attacker->x - injured->x;
                if (attacker->weapon_type != 0) {
                    uint32_t h_id = attacker->holder_id;
                    if (injured_id != h_id && h_id < MAX_OBJECTS && is_object_exists[h_id]) {
                        dist_x = objects[h_id]->x - injured->x;
                    } else {
                        dist_x = 2000;
                    }
                }
                if (dist_x < 0) {
                    dist_x = -dist_x;
                }

                if (dist_x < attacker->attackable_distance ||
                    (dist_x == attacker->attackable_distance && lf2_random(0x85, 2) == 0)) {
                    attacker->attackable_distance = dist_x;
                    attacker->injured_of_attack[0] = static_cast<int32_t>(injured_id);
                    attacker->itr_of_attack[0] = static_cast<uint8_t>(itr_id);
                    attacker->successful_attacks = 1;
                }
            }
        }
    }
}

// 1:1 Lift of 0x0042E100: Full Combat Damage, Fall State & Knockback Dispatcher
void global_t::attack_process(uint32_t attacker_id) {
    if (attacker_id >= MAX_OBJECTS || !is_object_exists[attacker_id]) {
        return;
    }

    object_t* attacker = objects[attacker_id];
    if (!attacker || !attacker->file) {
        return;
    }

    uint32_t a_frame_id = (attacker->frame_id4 < MAX_FRAMES) ? attacker->frame_id4 : attacker->frame_id1;
    if (a_frame_id >= MAX_FRAMES) return;

    frame_t* a_frame = &attacker->file->frames[a_frame_id];

    int32_t hit_count = attacker->successful_attacks;
    if (hit_count <= 0) return;

    for (int32_t i = 0; i < hit_count && i < 20; ++i) {
        int32_t injured_id = attacker->injured_of_attack[i];
        uint32_t itr_id = attacker->itr_of_attack[i];

        if (injured_id < 0 || injured_id >= static_cast<int32_t>(MAX_OBJECTS) || !is_object_exists[injured_id]) {
            continue;
        }

        object_t* injured = objects[injured_id];
        if (!injured || !injured->file) continue;

        // Victim multi-hit rest check (vrest)
        if (injured->vrest_of_objects[attacker_id] > 0) {
            continue;
        }

        if (itr_id >= a_frame->itrs_size) continue;
        const itr_t* itr = &a_frame->itrs[itr_id];

        // Set victim rest counter to prevent repeated hits within same swing
        injured->vrest_of_objects[attacker_id] = (itr->arest > 0) ? static_cast<uint8_t>(itr->arest) : 8;
        attacker->arest = (itr->arest > 0) ? itr->arest : 4;

        // Apply damage (0x0042E9B0)
        int32_t injury = itr->injury;
        if (injury <= 0) injury = 15; // default fallback punch damage

        injured->hp -= injury;
        injured->dark_hp += injury / 6;
        injured->hp_lost += injury;
        attacker->total_attack += injury;

        // Calculate fall & knockdown (0x0042EAA0)
        int32_t fall_increment = (itr->fall == 0) ? 20 : itr->fall;
        injured->fall += fall_increment;

        // Check if victim should enter falling knockdown state (0x0042EB00)
        if (injured->hp <= 0 || injured->fall >= 60 || itr->dvy != 0 || itr->effect == 4) {
            injured->fall = 80; // Full knockdown flag
            injured->frame_id1 = 180; // Standard LF2 falling frame
            injured->wait_counter = 0;

            double knock_x = (itr->dvx != 0) ? static_cast<double>(itr->dvx) : 5.0;
            double knock_y = (itr->dvy != 0) ? static_cast<double>(itr->dvy) : -8.0;

            injured->x_velocity = (attacker->facing == FACING_LEFT) ? -knock_x : knock_x;
            injured->y_velocity = knock_y;
            injured->y_position = -1.0; // Ensure airborne so gravity applies
        } else {
            // Flinch / hurt state (0x0042EC00: State 11 / frame 222 or 226)
            if (injured->facing == attacker->facing) {
                injured->frame_id1 = 226; // Back hurt
            } else {
                injured->frame_id1 = 222; // Front hurt
            }
            injured->wait_counter = 0;

            double flinch_x = (itr->dvx != 0) ? static_cast<double>(itr->dvx) * 0.4 : 2.0;
            injured->x_velocity = (attacker->facing == FACING_LEFT) ? -flinch_x : flinch_x;
        }

        // Weapon damage
        if (injured->file->type == TYPE_LIGHT_WEAPON || injured->file->type == TYPE_HEAVY_WEAPON) {
            injured->hp -= injury;
            if (injured->hp <= 0) {
                injured->fall = 80;
            }
        }
    }

    // Reset hit queue after processing
    attacker->successful_attacks = 0;
}

void global_t::process_all_attacks() {
    // 1. Decrement rest timers (vrest_of_objects) across all active objects
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!is_object_exists[i] || !objects[i]) continue;
        object_t* obj = objects[i];
        for (uint32_t j = 0; j < MAX_OBJECTS; ++j) {
            if (obj->vrest_of_objects[j] > 0) {
                obj->vrest_of_objects[j]--;
            }
        }
    }

    // 2. Pairwise collision check
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!is_object_exists[i] || !objects[i]) continue;
        for (uint32_t j = 0; j < MAX_OBJECTS; ++j) {
            if (i == j || !is_object_exists[j] || !objects[j]) continue;
            does_attack_success(i, j, 0);
        }
    }

    // 3. Process damage, fall states, and knockback for all successful attackers
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!is_object_exists[i] || !objects[i]) continue;
        if (objects[i]->successful_attacks > 0) {
            attack_process(i);
        }
    }
}

int32_t global_t::spawn_projectile(uint32_t owner_id, uint32_t file_id, int32_t x, int32_t y, int32_t z, double dvx, double dvy, uint8_t facing) {
    int32_t slot = -1;
    for (uint32_t i = 10; i < MAX_OBJECTS; ++i) {
        if (!is_object_exists[i]) {
            slot = static_cast<int32_t>(i);
            break;
        }
    }
    if (slot == -1) return -1;

    file_t* proj_file = nullptr;
    for (uint32_t f = 0; f < MAX_FILES; ++f) {
        if (files[f] && files[f]->id == file_id) {
            proj_file = files[f];
            break;
        }
    }

    if (!objects[slot]) {
        objects[slot] = new object_t();
    }

    object_t* proj = objects[slot];
    object_init(proj);
    proj->file = proj_file;
    proj->x_position = static_cast<double>(x);
    proj->y_position = static_cast<double>(y);
    proj->z_position = static_cast<double>(z);
    proj->x = x;
    proj->y = y;
    proj->z = z;
    proj->facing = facing;
    proj->x_velocity = (facing == FACING_LEFT) ? -dvx : dvx;
    proj->y_velocity = dvy;
    proj->owner = owner_id;
    if (owner_id < MAX_OBJECTS && objects[owner_id]) {
        proj->team = objects[owner_id]->team;
    }

    is_object_exists[slot] = 1;
    return slot;
}

} // namespace lf2


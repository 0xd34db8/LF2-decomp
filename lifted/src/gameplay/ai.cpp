#include "gameplay/ai.h"
#include "core/random.h"
#include <cstdlib>
#include <cstring>
#include <cmath>

namespace lf2 {

namespace {

constexpr int32_t BINARY_STATE_DIZZY    = 16;
constexpr int32_t BINARY_STATE_BURNING  = 18;
constexpr int32_t BINARY_STATE_FIRE_RUN = 19;

void copy_and_clear_keys(object_t* obj)
{
    obj->holding_up     = obj->click_up;
    obj->holding_down   = obj->click_down;
    obj->holding_left   = obj->click_left;
    obj->holding_right  = obj->click_right;
    obj->holding_attack = obj->click_attack;
    obj->holding_jump   = obj->click_jump;
    obj->holding_defend = obj->click_defend;
    obj->click_defend   = 0;
    obj->click_jump     = 0;
    obj->click_attack   = 0;
    obj->click_down     = 0;
    obj->click_up       = 0;
    obj->click_left     = 0;
    obj->click_right    = 0;
}

int32_t map_difficulty_to_binary(ai_difficulty_t difficulty)
{
    switch (difficulty) {
    case AI_CRAZY: return -1;
    case AI_EASY:  return 2;
    case AI_NORMAL:
    default:       return 1;
    }
}

bool is_low_health_self(const object_t* obj)
{
    return ((obj->hp < obj->dark_hp - 70 && obj->hp < 140) ||
            (obj->hp < (obj->dark_hp * 3) / 5 && obj->hp >= 140));
}

bool far_from(const object_t* a, const object_t* b)
{
    return (std::abs(a->z - b->z) > 150 || std::abs(a->x - b->x) > 240);
}

void edge_move(object_t* self, const object_t* target, int32_t width_limit)
{
    int32_t tx = target->x;
    if ((tx < 250 || tx < self->x) && tx <= width_limit - 250) {
        self->click_right = 1;
        self->holding_right = 0;
    } else if (tx > width_limit - 250 || self->x < tx) {
        self->click_left = 1;
        self->holding_left = 0;
    }
}

bool help_ally(global_t* world, int32_t self_id, int32_t dist, int32_t z_close)
{
    object_t* self = world->objects[self_id];
    if (!self || !self->file) return false;

    if ((self->weapon_type == 0 || static_cast<int32_t>(self->frame_id1) < 9) &&
        !is_low_health_self(self) && z_close == 0) {
        for (int32_t j = 0; j < 20; ++j) {
            if (j == self_id || !world->is_object_exists[j] || !world->objects[j]) continue;
            object_t* ally = world->objects[j];
            if (ally->team != 0 && ally->team == self->team) {
                int32_t near_x = std::abs(ally->x - self->x);
                if (near_x < 250) {
                    int32_t near_z = std::abs(ally->z - self->z);
                    if (near_z < 60 && self->mp > 350 &&
                        ((ally->hp < ally->dark_hp - 90 && ally->hp < 140) ||
                         (ally->hp < (ally->dark_hp * 3) / 5 && ally->hp >= 140)) &&
                        ally->hp > 0 && near_z + near_x < dist / 3) {
                        if (self->x < ally->x) {
                            self->click_right = 1;
                            self->click_left = 0;
                        } else {
                            self->click_right = 0;
                            self->click_left = 1;
                        }
                        if (((self->x < ally->x && self->facing == FACING_RIGHT) ||
                             (ally->x < self->x && self->facing == FACING_LEFT)) ||
                            std::abs(ally->x - self->x) < 5) {
                            self->click_DUJ = 3;
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

input_state_t clicks_to_input_state(const object_t* self)
{
    input_state_t in{};
    if (!self) return in;
    in.up     = (self->click_up != 0);
    in.down   = (self->click_down != 0);
    in.left   = (self->click_left != 0);
    in.right  = (self->click_right != 0);
    in.attack = (self->click_attack != 0);
    in.jump   = (self->click_jump != 0);
    in.defend = (self->click_defend != 0);

    if (self->click_DRA == 3) { in.defend = true; in.right = true; in.attack = true; }
    if (self->click_DLA == 3) { in.defend = true; in.left = true; in.attack = true; }
    if (self->click_DUA == 3) { in.defend = true; in.up = true; in.attack = true; }
    if (self->click_DDA == 3) { in.defend = true; in.down = true; in.attack = true; }
    if (self->click_DRJ == 3) { in.defend = true; in.right = true; in.jump = true; }
    if (self->click_DLJ == 3) { in.defend = true; in.left = true; in.jump = true; }
    if (self->click_DUJ == 3) { in.defend = true; in.up = true; in.jump = true; }
    if (self->click_DDJ == 3) { in.defend = true; in.down = true; in.jump = true; }
    if (self->click_DJA == 3) { in.defend = true; in.jump = true; in.attack = true; }
    return in;
}

} // namespace

uint32_t ai_find_nearest_target(const global_t* world, uint32_t ai_id)
{
    if (!world || ai_id >= MAX_OBJECTS || !world->is_object_exists[ai_id]) {
        return MAX_OBJECTS;
    }
    const object_t* self = world->objects[ai_id];
    if (!self || !self->file) return MAX_OBJECTS;

    uint32_t best_target = MAX_OBJECTS;
    int32_t best_dist = 10000;

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!world->is_object_exists[i] || i == ai_id) continue;
        const object_t* cand = world->objects[i];
        if (!cand || !cand->file || cand->frame_id1 >= MAX_FRAMES) continue;

        if (cand->hp <= 0 || cand->team == self->team) continue;
        if (cand->file->type != TYPE_CHARACTER) continue;
        if (cand->file->frames[cand->frame_id1].state == STATE_LYING ||
            std::abs(cand->blink_time) >= 3) {
            continue;
        }

        int32_t d = std::abs(cand->z - self->z) + std::abs(cand->x - self->x);
        if (d < best_dist) {
            best_dist = d;
            best_target = i;
        }
    }

    return best_target;
}

int32_t ai_evaluate_character_special(global_t* world, int32_t target_id, int32_t ai_id,
                                      int32_t self_state, int32_t target_state,
                                      int32_t incoming_proj, int32_t dist, int32_t z_close,
                                      int32_t width_limit, int32_t edge_flag, int32_t skill5)
{
    if (!world || target_id < 0 || target_id >= static_cast<int32_t>(MAX_OBJECTS) ||
        ai_id < 0 || ai_id >= static_cast<int32_t>(MAX_OBJECTS)) {
        return 0;
    }
    if (lf2_random(0x3c, skill5 + 1) > 0) {
        return 0;
    }

    object_t* self = world->objects[ai_id];
    object_t* target = world->objects[target_id];
    if (!self || !target || !self->file || !target->file || self->frame_id1 >= MAX_FRAMES) {
        return 0;
    }

    int32_t cid = static_cast<int32_t>(self->file->id);
    int32_t tid = static_cast<int32_t>(target->file->id);
    int32_t dx = std::abs(target->x - self->x);
    int32_t dz = std::abs(target->z - self->z);
    bool facing_toward = (self->facing == FACING_RIGHT && self->x < target->x) ||
                         (self->facing == FACING_LEFT && target->x < self->x);

    if (cid == static_cast<int32_t>(JOHN_DAT)) {
        if (lf2_random(0x3d, 10) == 0 && self->mp > 350 && is_low_health_self(self)) {
            self->click_DDJ = 3;
            return 1;
        }
        if (dist < 10000 && lf2_random(0x3e, 30) == 0 && self->mp > 250) {
            self->click_DUA = 3;
            return 1;
        }
        if (tid == static_cast<int32_t>(JOHN_DAT) || tid == static_cast<int32_t>(DENNIS_DAT) ||
            tid == static_cast<int32_t>(WOODY_DAT) || tid == static_cast<int32_t>(DAVIS_DAT) ||
            tid == static_cast<int32_t>(JACK_DAT) || tid == static_cast<int32_t>(SORCERER_DAT)) {
            if (lf2_random(0x3f, 15) == 0 && dx > 100 && dx < 500 && dz < 30 &&
                self->mp > 100 && target->mp > 220 && incoming_proj == 0) {
                if (self->x < target->x) self->click_DRJ = 3;
                else self->click_DLJ = 3;
                return 1;
            }
        } else {
            if (lf2_random(0x40, 15) == 0 && dx > 100 && dx < 250 && dz < 30 &&
                self->mp > 100 && target->mp > 170 && incoming_proj == 0) {
                if (self->x < target->x) self->click_DRJ = 3;
                else self->click_DLJ = 3;
                return 1;
            }
        }
        if (help_ally(world, ai_id, dist, z_close)) {
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(DEEP_DAT)) {
        if (self->frame_id1 >= 260 && self->frame_id1 <= 289 && dx < 100 && dz < 7) {
            if ((target->y == 0 && self->y == 0 && lf2_random(0x41, 3) == 0) ||
                (target->y < 0 && self->y < 0 && lf2_random(0x42, 7) == 0)) {
                self->click_attack = 1;
                self->holding_attack = 0;
                return 1;
            }
            if ((target->y < 0 && lf2_random(0x43, 5) == 0) || lf2_random(0x44, 30) == 0) {
                if (facing_toward) {
                    self->click_jump = 1;
                }
                self->holding_jump = 0;
            }
            return 1;
        }
        if (lf2_random(0x45, 7) == 0 && dx < 150 && dz < 8 && self->mp > 150 &&
            ((lf2_random(0x46, 10) == 0 && target_state != static_cast<int32_t>(STATE_ATTACKING)) ||
             (lf2_random(0x47, 3) > 0 &&
              (target_state == BINARY_STATE_DIZZY ||
               target_state == static_cast<int32_t>(STATE_BROKEN_DEFEND) ||
               target_state == static_cast<int32_t>(STATE_INJURED_1))))) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (lf2_random(0x48, 7) == 0 && dx < 100 && dz < 7 && self->mp > 75) {
            if (self->mp > 150 &&
                ((lf2_random(0x49, 10) == 0 && target_state != static_cast<int32_t>(STATE_ATTACKING)) ||
                 (lf2_random(0x4a, 3) > 0 && target_state == BINARY_STATE_DIZZY))) {
                if (self->x < target->x) self->click_DRJ = 3;
                else self->click_DLJ = 3;
                return 1;
            }
            self->click_DDA = 3;
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(HENRY_DAT)) {
        if (self->mp > 360 && dx < 100 && dz < 70 && lf2_random(0x4b, self->hp / 5 + 10) == 0) {
            self->click_DUJ = 3;
            return 1;
        }
        if (lf2_random(0x4c, 45) == 0 && dx > 100 && dx < 550 && dz < 20 && self->mp > 170) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (lf2_random(0x4d, 30) == 0 && self->mp > 200 && dx > 100 && dx < 160 && dz < 55 && facing_toward) {
            self->click_DJA = 3;
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(RUDOLF_DAT)) {
        if (self->mp > 450 && dx > 100 && dz > 50 && lf2_random(0x4e, 3) == 0) {
            if (lf2_random(0x4f, 2) == 0) self->click_DUJ = 3;
            else self->click_DDJ = 3;
            return 1;
        }
        if (self->mp > 70 && dx > 100 && dx < 160 && dz < 8 && lf2_random(0x50, 10) == 0) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (lf2_random(0x51, 30) == 0 && self->mp > 200 && dx > 100 && dx < 160 && dz < 55) {
            if (self->facing == FACING_RIGHT && self->x < target->x) {
                self->click_DRA = 3;
                return 1;
            }
            if (self->facing == FACING_LEFT && target->x < self->x) {
                self->click_DLA = 3;
                return 1;
            }
        }
    }

    if (cid == static_cast<int32_t>(LOUIS_DAT)) {
        if (self->mp > 100 && dx > 80 && dx < 130 && dz < 30 && lf2_random(0x52, 10) == 0) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (self->mp > 100 && dx < 45 && dz < 5 && lf2_random(0x53, 3) == 0) {
            self->click_DUJ = 3;
            return 1;
        }
        if (self_state == static_cast<int32_t>(STATE_CATCHING) && lf2_random(0x54, 8) == 0) {
            self->click_jump = 1;
            self->holding_jump = 0;
        }
    }

    if (cid == static_cast<int32_t>(FIREN_DAT)) {
        if (self->frame_id1 > 267 && self->frame_id1 < 283) {
            if (target_state == static_cast<int32_t>(STATE_FALLING) ||
                target_state == static_cast<int32_t>(STATE_INJURED_1) ||
                dx > 150 || dz > 25 || facing_toward) {
                self->click_defend = 1;
                self->holding_defend = 0;
                return 1;
            }
        }
        if (target_state != BINARY_STATE_BURNING && target_state != static_cast<int32_t>(STATE_LYING)) {
            if (target_state != static_cast<int32_t>(STATE_FALLING) && self->hp > 70 && self->mp > 320 &&
                (dx > 50 || dz > 10) && dx < 85 && target->hp < self->hp && dz < 35 &&
                lf2_random(0x55, 5) == 0) {
                self->click_DUJ = 3;
                return 1;
            }
            if (target_state != static_cast<int32_t>(STATE_FALLING) && self->mp > 200 &&
                dx > 100 && dx < 370 && dz < 60 && lf2_random(0x56, 20) == 0) {
                if (self->x < target->x) self->click_DRJ = 3;
                else self->click_DLJ = 3;
                return 1;
            }
        }
        if (lf2_random(0x57, 100) == 0 && dx > 240 && dx < 400) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (target_state != BINARY_STATE_BURNING &&
            target_state != static_cast<int32_t>(STATE_LYING) &&
            target_state != static_cast<int32_t>(STATE_FALLING) &&
            self->mp > 200 && dx > 60 && dx < 280 && dz < 60 && lf2_random(0x58, 15) == 0) {
            if (facing_toward) {
                self->click_DDJ = 3;
                return 1;
            }
        }
        if (self->frame_id1 >= 255 && self->frame_id1 <= 261) {
            if ((self->facing == FACING_RIGHT && (target->x + 120 < self->x || width_limit - 30 < self->x)) ||
                (self->facing == FACING_LEFT && (self->x < target->x - 120 || self->x < 30)) ||
                dz > 70 || edge_flag == 1) {
                self->click_defend = 1;
                self->holding_defend = 0;
                return 1;
            }
            if (facing_toward) {
                if (target->z <= self->z) self->click_up = 1;
                else self->click_down = 1;
            } else {
                if (target->z < self->z) self->click_down = 1;
                else self->click_up = 1;
            }
        }
    }

    if (cid == static_cast<int32_t>(FREEZE_DAT)) {
        if (target_state != static_cast<int32_t>(STATE_ICE)) {
            if ((self->mp > 200 && dx < 400 && dz < 170 && lf2_random(0x59, 250) == 0) ||
                (target_state != static_cast<int32_t>(STATE_LYING) && self->mp > 200 &&
                 dx > 60 && dx < 280 && dz < 65 && lf2_random(0x5a, 15) == 0)) {
                if (self->x < target->x) self->click_DRJ = 3;
                else self->click_DLJ = 3;
                return 1;
            }
        }
        if (target_state != static_cast<int32_t>(STATE_LYING) && self->mp > 320 &&
            ((dx > 50 || dz > 7) || target_state == static_cast<int32_t>(STATE_ICE)) &&
            dx < 125 && dz < 25 && lf2_random(0x5b, 3) == 0 && facing_toward) {
            self->click_DUJ = 3;
            return 1;
        }
        if (lf2_random(0x5c, 50) == 0 && self->weapon_type == 0 && self->mp > 200 &&
            dx > 200 && dz > 50) {
            self->click_DDJ = 3;
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(DAVIS_DAT)) {
        if (self->mp > 150 && dx < 280 && dz < 30 && lf2_random(0x5d, 10) == 0) {
            if (self->facing == FACING_RIGHT && self->x < target->x) {
                self->click_DDA = 3;
                return 1;
            }
            if (self->facing == FACING_LEFT && target->x < self->x) {
                if (target->x <= self->x) return 1;
                self->click_DDA = 3;
                return 1;
            }
        }
        if (self->file->frames[self->frame_id1].hit_j == 290 && target->y < 0) {
            self->holding_jump = 0;
            self->click_jump = 1;
        }
        if (lf2_random(0x5e, 5) == 0 || target_state == BINARY_STATE_DIZZY ||
            target_state == static_cast<int32_t>(STATE_BROKEN_DEFEND)) {
            int32_t dx_lead = std::abs((static_cast<int32_t>(self->x_velocity) - self->x) + target->x);
            if (dx_lead < 100 && dz < 7 && self->mp > 200 && facing_toward) {
                self->click_DUA = 3;
                return 1;
            }
        }
    }

    if (cid == static_cast<int32_t>(WOODY_DAT)) {
        if (self->mp > 100 && dx < 280 && dz < 25 && lf2_random(0x5f, 10) == 0) {
            if (self->facing == FACING_RIGHT && self->x < target->x) {
                self->click_DDA = 3;
                return 1;
            }
            if (self->facing == FACING_LEFT && target->x < self->x) {
                if (target->x <= self->x) return 1;
                self->click_DDA = 3;
                return 1;
            }
        }
        if (self->frame_id1 == 271 && target->y < 0 && target_state == static_cast<int32_t>(STATE_FALLING)) {
            self->click_DUA = 3;
            return 1;
        }
        if (lf2_random(0x60, 10) == 0 || target_state == BINARY_STATE_DIZZY ||
            target_state == static_cast<int32_t>(STATE_BROKEN_DEFEND)) {
            int32_t dx_lead = std::abs((static_cast<int32_t>(self->x_velocity) - self->x) + target->x);
            if (dx_lead < 80 && dz < 7 && facing_toward) {
                self->click_DUA = 3;
                return 1;
            }
        }
        if (self->mp > 200 && dx > 60 && dx < 280 && dz < 65 &&
            (lf2_random(0x61, 15) == 0 ||
             (lf2_random(0x62, 4) == 0 &&
              (target_state == BINARY_STATE_DIZZY ||
               target_state == static_cast<int32_t>(STATE_BROKEN_DEFEND) ||
               (target_state == static_cast<int32_t>(STATE_FALLING) && target->y < -40))))) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (self->hp < 250 && self->hp < target->hp + 50 &&
            lf2_random(99, 20) == 0 && self->mp > 75) {
            int32_t best = -1;
            int32_t best_idx = -1;
            for (int32_t j = 0; j < static_cast<int32_t>(MAX_OBJECTS); ++j) {
                if (j != ai_id && world->is_object_exists[j] && world->objects[j] && world->objects[j]->file) {
                    object_t* cand = world->objects[j];
                    if (cand->file->type == TYPE_CHARACTER && cand->team == self->team && target->hp < cand->hp) {
                        int32_t d = std::abs(cand->z - self->z) + std::abs(cand->x - self->x);
                        if (best < d) {
                            best = d;
                            best_idx = j;
                        }
                    }
                }
            }
            if (best_idx != -1 && best > 300 && self->weapon_type == 0) {
                self->click_DDJ = 3;
            }
        }
        if (target->hp < self->hp && lf2_random(100, 70) == 0 && self->mp > 500) {
            self->click_DUJ = 3;
        }
    }

    if (cid == static_cast<int32_t>(DENNIS_DAT)) {
        if (lf2_random(0x65, 10) == 0 || target_state == BINARY_STATE_DIZZY ||
            target_state == static_cast<int32_t>(STATE_BROKEN_DEFEND)) {
            int32_t dx_lead = std::abs((static_cast<int32_t>(self->x_velocity) - self->x) + target->x);
            if (dx_lead < 120 && dz < 7 && facing_toward) {
                self->click_DDA = 3;
                return 1;
            }
        }
        if ((target_state != BINARY_STATE_BURNING &&
             target_state != static_cast<int32_t>(STATE_LYING) &&
             target_state != static_cast<int32_t>(STATE_FALLING) &&
             self->mp > 200 && dx > 75 && dx < 370 && dz < 60 && lf2_random(0x66, 13) == 0) ||
            (lf2_random(0x67, target->hp / 4 + 40) == 0 && dx > 150 && dx < 400)) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (dist < 10000 && lf2_random(0x68, 30) == 0 && self->mp > 150) {
            self->click_DUA = 3;
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(MARK_DAT)) {
        if ((target_state != BINARY_STATE_BURNING &&
             target_state != static_cast<int32_t>(STATE_LYING) &&
             target_state != static_cast<int32_t>(STATE_FALLING) &&
             self->mp > 200 && dx < 270 && dz < 60 && lf2_random(0x69, 60) == 0) ||
            (lf2_random(0x6a, target->hp / 4 + 40) == 0 && dx > 150 && dx < 400)) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (dx < 150 && dz < 40 && lf2_random(0x6b, 15) == 0) {
            if (self->x < target->x) self->click_DRA = 3;
            else self->click_DLA = 3;
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(JACK_DAT) &&
        (lf2_random(0x6c, 5) == 0 || target_state == BINARY_STATE_DIZZY ||
         target_state == static_cast<int32_t>(STATE_BROKEN_DEFEND))) {
        int32_t dx_lead = std::abs((static_cast<int32_t>(self->x_velocity) - self->x) + target->x);
        if (dx_lead < 60 && dz < 7 && self->mp > 150 && facing_toward) {
            self->click_DUA = 3;
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(SORCERER_DAT)) {
        if (lf2_random(0x6d, 10) == 0 && self->mp > 350 && is_low_health_self(self)) {
            self->click_DDJ = 3;
            return 1;
        }
        if (help_ally(world, ai_id, dist, z_close)) {
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(LOUISE_EX_DAT)) {
        if (lf2_random(0x6e, 7) == 0 && dx < 500 && dx > 90 && dz < 4 && self->mp > 150) {
            if (target->frame_id1 == 263 || target->frame_id1 == 264) {
                self->holding_attack = 0;
                self->click_attack = 1;
            } else {
                if (self->x < target->x) self->click_DRA = 3;
                else self->click_DLA = 3;
                return 1;
            }
        }
        if (lf2_random(0x6f, 7) == 0 && dx < 100 && dz < 7 && self->mp > 75) {
            self->click_DDA = 3;
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(MONK_DAT) && lf2_random(0x70, 7) == 0 &&
        dx < 650 && dx > 40 && dz < 4 && self->mp > 120) {
        if (self->x < target->x) self->click_DRA = 3;
        else self->click_DLA = 3;
        return 1;
    }

    if (cid == static_cast<int32_t>(JAN_DAT)) {
        if (self->mp > 200 && lf2_random(0x71, 5) == 0) {
            for (int32_t j = 0; j < 100; ++j) {
                if (world->is_object_exists[j] == 1 && world->objects[j] && world->objects[j]->file) {
                    object_t* ally = world->objects[j];
                    if (ally->file->type == TYPE_CHARACTER && ally->team == self->team &&
                        (ally->hp < ally->dark_hp - 200 || (ally->hp < 200 && ally->hp < ally->dark_hp - 100))) {
                        self->click_DUJ = 3;
                        return 1;
                    }
                }
            }
            return 1;
        }
        if (self->mp > 260 && lf2_random(0x72, 10) == 0 && dx < 650 && dz < 240) {
            self->click_DUA = 3;
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(BAT_DAT)) {
        if (self->mp > 150 && lf2_random(0x73, 5) == 0 && dx < 250 && dx > 130 && dz < 10) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (self->mp > 200 && lf2_random(0x74, 10) == 0 && dz < 10) {
            if (self->x < target->x) self->click_DRA = 3;
            else self->click_DLA = 3;
            return 1;
        }
        if (self->mp > 200 && lf2_random(0x75, 10) == 0 && (dx > 200 || dz < 250)) {
            self->click_DUJ = 3;
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(JUSTIN_DAT)) {
        if (self->mp > 100 && lf2_random(0x76, 3) == 0 && dx < 120 && facing_toward && dz < 10) {
            self->click_DDA = 3;
            return 1;
        }
        if (self->mp > 100 && lf2_random(0x77, 7) == 0 && dx < 250 && dz < 10) {
            if (self->x < target->x) self->click_DRA = 3;
            else self->click_DLA = 3;
            return 1;
        }
    }

    if (cid == static_cast<int32_t>(JULIAN_DAT)) {
        if (target_state == static_cast<int32_t>(STATE_ATTACKING) && self->mp > 125 &&
            lf2_random(0x78, 10) == 0 && dx < 120 && dz < 10) {
            self->click_DJA = 3;
            return 1;
        }
        if (self->mp > 125 && lf2_random(0x7b, 5) == 0 && dx < 100 && dz < 30) {
            if (target->x <= self->x) return 1;
            self->click_DUJ = 3;
            return 1;
        }
        if (self->mp > 125 && lf2_random(0x7c, 14) == 0 && dx < 700 && dz < 150) {
            if (self->x < target->x) self->click_DRA = 3;
            else self->click_DLA = 3;
            return 1;
        }
        if (self->mp > 125 && lf2_random(0x7d, 5) == 0 && dz < 20) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (lf2_random(0x7e, 5) == 0 || target_state == BINARY_STATE_DIZZY ||
            target_state == static_cast<int32_t>(STATE_BROKEN_DEFEND)) {
            int32_t dx_lead = std::abs((static_cast<int32_t>(self->x_velocity) - self->x) + target->x);
            if (dx_lead < 100 && dz < 7 && self->mp < 100 && facing_toward) {
                self->click_DUA = 3;
                return 1;
            }
        }
    }

    if (cid != static_cast<int32_t>(FIRZEN_DAT)) {
        return 0;
    }

    if (self->frame_id1 > 265 && self->frame_id1 < 280 &&
        (dz > 13 || target->file->type != TYPE_CHARACTER)) {
        self->holding_defend = 0;
        self->click_defend = 1;
        return 1;
    }
    if (self->mp > 300 && lf2_random(0x7f, 10) == 0 && dx < 300 && dz < 200) {
        self->click_DUJ = 3;
        return 1;
    }
    if (self->mp > 300 && lf2_random(0x80, 10) == 0 && dx < 950) {
        self->click_DUA = 3;
        return 1;
    }
    if (lf2_random(0x81, 5) == 0 && self->mp > 250 && dx < 1200 && dx > 40 && dz < 13) {
        if (self->x < target->x) self->click_DRJ = 3;
        else self->click_DLJ = 3;
        return 1;
    }
    return 0;
}

bool ai_evaluate_character_special(object_t* self, const object_t* target, input_state_t& out_input)
{
    if (!self || !self->file || !target || !target->file ||
        self->frame_id1 >= MAX_FRAMES || target->frame_id1 >= MAX_FRAMES) {
        return false;
    }
    global_t tmp{};
    tmp.objects[0] = self;
    tmp.objects[1] = const_cast<object_t*>(target);
    tmp.is_object_exists[0] = 1;
    tmp.is_object_exists[1] = 1;

    int32_t self_st = static_cast<int32_t>(self->file->frames[self->frame_id1].state);
    int32_t tgt_st = static_cast<int32_t>(target->file->frames[target->frame_id1].state);
    int32_t dist = std::abs(target->x - self->x) + std::abs(target->z - self->z);
    int32_t z_close = (std::abs(target->z - self->z) < 15) ? 1 : 0;

    int32_t res = ai_evaluate_character_special(&tmp, 1, 0, self_st, tgt_st, 0, dist, z_close, 2000, 0, 0);
    if (res != 0) {
        out_input = clicks_to_input_state(self);
        return true;
    }
    return false;
}

int32_t ai_evaluate_weapon_decision(global_t* world, int32_t target_id, int32_t ai_id,
                                    int32_t self_state, int32_t target_state,
                                    int32_t z_close, int32_t incoming_proj,
                                    int32_t width_limit, int32_t edge_flag,
                                    int32_t skill3, int32_t skill5, int32_t skill15,
                                    const ai_world_params_t& params)
{
    if (!world || target_id < 0 || target_id >= static_cast<int32_t>(MAX_OBJECTS) ||
        ai_id < 0 || ai_id >= static_cast<int32_t>(MAX_OBJECTS)) {
        return 0;
    }
    if (lf2_random(0x28, skill3 + 1) > 0) {
        return 0;
    }

    object_t* self = world->objects[ai_id];
    object_t* target = world->objects[target_id];
    if (!self || !target || !self->file || !target->file ||
        self->weapon_id < 0 || self->weapon_id >= static_cast<int32_t>(MAX_OBJECTS)) {
        return 0;
    }
    object_t* weapon = world->objects[self->weapon_id];
    if (!weapon || !weapon->file) return 0;

    uint32_t wid = weapon->file->id;
    bool ally_in_line = false;
    for (int32_t i = 0; i < 20; ++i) {
        if (i != ai_id && world->is_object_exists[i] && world->objects[i] &&
            world->objects[i]->file && world->objects[i]->frame_id1 < MAX_FRAMES) {
            object_t* ally = world->objects[i];
            // Original binary 0x00408D46 checks target->team == self->team alongside ally->team != 0
            if (ally->team != 0 && target->team == self->team && ally->hp > 0 &&
                ally->file->frames[ally->frame_id1].state != STATE_LYING &&
                std::abs(ally->blink_time) < 3 &&
                std::abs(ally->z - self->z) < 15 &&
                is_between(self->x, ally->x, target->x)) {
                ally_in_line = true;
            }
        }
    }

    if (self_state == static_cast<int32_t>(STATE_RUNNING) && lf2_random(0x29, skill3 + 5) == 0) {
        if (ally_in_line) self->click_jump = 1;
        else self->click_attack = 1;
    }

    if (wid == STICK_DAT || wid == HOE_DAT || wid == KNIFE_DAT ||
        wid == BASEBALL_DAT || wid == BOOMERANG_DAT) {
        int32_t dx_lead = std::abs((target->x + static_cast<int32_t>(self->x_velocity) * -2) - self->x);
        int32_t dz = std::abs(target->z - self->z);
        if (dx_lead < 115 && dz < 6 && lf2_random(0x2a, skill3 + 3) == 0 &&
            target_state != static_cast<int32_t>(STATE_LYING)) {
            self->click_attack = 1;
        }
        if (wid == BOOMERANG_DAT && lf2_random(0x2b, skill15 + 30) == 0) {
            self->click_attack = 1;
        }
        if (lf2_random(0x2c, skill3 + 5) == 0) {
            if (self->follow_order == 0 ||
                (std::abs(self->z - target->z) <= 150 && std::abs(self->x - target->x) <= 240)) {
                int32_t raw_dx = std::abs(target->x - self->x);
                if (raw_dx < 600 && dz < 20) {
                    if (self->x < target->x && edge_flag == 0) {
                        self->click_right = 1;
                        self->holding_right = 0;
                    }
                    if (target->x < self->x) {
                        self->click_left = 1;
                        self->holding_left = 0;
                    }
                }
            }
        }
    }

    if ((wid == STONE_DAT || wid == WOODEN_BOX_DAT) && !ally_in_line) {
        int32_t dx_lead = std::abs((target->x + static_cast<int32_t>(self->x_velocity) * -2) - self->x);
        int32_t dz = std::abs(target->z - self->z);
        if (dx_lead < 300 && dz < 6 && lf2_random(0x2d, skill5 + 7) == 0 &&
            target_state != static_cast<int32_t>(STATE_LYING)) {
            self->click_attack = 1;
        }
    }

    if (wid != MILK_DAT && wid != BEER_DAT) {
        return 1;
    }

    self->click_defend = 0;
    self->click_jump = 0;
    self->click_attack = 0;
    self->click_down = 0;
    self->click_up = 0;
    self->click_left = 0;
    self->click_right = 0;

    if (self_state == static_cast<int32_t>(STATE_DRINKING) && z_close == 1 &&
        incoming_proj == 0 && self->blink_time != 0) {
        self->click_defend = 1;
        return 0;
    }

    if (self->follow_order != 0) {
        if (std::abs(self->z - target->z) > 150) return 0;
        if (std::abs(self->x - target->x) > 240) return 0;
    }

    int32_t tz = target->z;
    if (params.zboundary_min + 30 <= tz && (tz < params.zboundary_max - 30 || self->z < tz)) {
        self->click_up = 1;
    } else {
        self->click_down = 1;
    }

    int32_t tx = target->x;
    if (tx < 400 && self->x < 200) {
        self->click_right = 1;
        if (lf2_random(0x2e, skill3 + 7) == 0) self->holding_right = 0;
        if (lf2_random(0x2f, skill3 + 5) == 0 && self_state == static_cast<int32_t>(STATE_RUNNING)) {
            self->click_jump = 1;
            return 0;
        }
    } else if (width_limit - 400 < tx && width_limit - 200 < self->x) {
        self->click_left = 1;
        if (lf2_random(0x30, skill3 + 7) == 0) self->holding_left = 0;
        if (lf2_random(0x31, skill3 + 5) == 0 && self_state == static_cast<int32_t>(STATE_RUNNING)) {
            self->click_jump = 1;
            return 0;
        }
    } else {
        int32_t dx = std::abs(tx - self->x);
        if (dx < 350 && std::abs(tz - self->z) < 70) {
            if (self->x < tx) {
                self->click_left = 1;
                if (lf2_random(0x32, skill3 + 4) == 0) self->holding_left = 0;
            }
            if (self->x < target->x) {
                return 0;
            }
            self->click_right = 1;
            if (lf2_random(0x33, skill3 + 4) == 0) self->holding_right = 0;
            return 0;
        }
        if (self_state == static_cast<int32_t>(STATE_RUNNING)) {
            if (self->facing == FACING_RIGHT) self->click_left = 1;
            if (self->facing == FACING_LEFT) {
                self->click_right = 1;
                return 0;
            }
        } else if (lf2_random(0x34, 5) == 0) {
            if (incoming_proj == 0) {
                uint32_t cid = self->file->id;
                if ((cid == JOHN_DAT || cid == SORCERER_DAT) &&
                    self->mp > 150 && lf2_random(0x35, skill3 + 3) > 0) {
                    if (self->x < target->x) self->click_DRJ = 3;
                    else self->click_DLJ = 3;
                    return 1;
                }
            }
            self->click_attack = 1;
        }
    }
    return 0;
}

bool ai_evaluate_weapon_decision(const global_t* world, uint32_t ai_id, uint32_t target_id, input_state_t& out_input)
{
    if (!world || ai_id >= MAX_OBJECTS || target_id >= MAX_OBJECTS) return false;
    object_t* self = world->objects[ai_id];
    object_t* target = world->objects[target_id];
    if (!self || !target || !self->file || !target->file ||
        self->frame_id1 >= MAX_FRAMES || target->frame_id1 >= MAX_FRAMES ||
        self->weapon_type == 0) {
        return false;
    }
    int32_t self_st = static_cast<int32_t>(self->file->frames[self->frame_id1].state);
    int32_t tgt_st = static_cast<int32_t>(target->file->frames[target->frame_id1].state);
    int32_t z_close = (std::abs(target->z - self->z) < 15) ? 1 : 0;
    ai_world_params_t params{};

    ai_evaluate_weapon_decision(const_cast<global_t*>(world), static_cast<int32_t>(target_id),
                                static_cast<int32_t>(ai_id), self_st, tgt_st, z_close, 0,
                                params.stage_width, 0, 0, 0, 0, params);

    out_input = clicks_to_input_state(self);
    return (out_input.attack || out_input.jump || out_input.defend ||
            out_input.left || out_input.right || out_input.up || out_input.down);
}

int32_t ai_evaluate_dodge(global_t* world, int32_t target_id, int32_t ai_id,
                            int32_t target_state, int32_t hazard_right, int32_t hazard_left,
                            int32_t skill3, int32_t skill5)
{
    if (!world || target_id < 0 || target_id >= static_cast<int32_t>(MAX_OBJECTS) ||
        ai_id < 0 || ai_id >= static_cast<int32_t>(MAX_OBJECTS)) {
        return 0;
    }
    object_t* self = world->objects[ai_id];
    object_t* target = world->objects[target_id];
    if (!self || !target || !self->file || !target->file) return 0;

    int32_t cid = static_cast<int32_t>(self->file->id);
    int32_t dx_self_lead = std::abs((target->x - static_cast<int32_t>(self->x_velocity) * 2) - self->x);
    int32_t dx_target_lead = std::abs((target->x + static_cast<int32_t>(target->x_velocity) * 2) - self->x);
    int32_t dz = std::abs(target->z - self->z);

    if (((cid != static_cast<int32_t>(HENRY_DAT) && cid != static_cast<int32_t>(RUDOLF_DAT)) &&
         cid != static_cast<int32_t>(HUNTER_DAT)) || cid != static_cast<int32_t>(JAN_DAT)) {
        if (dx_self_lead < 80 && dz < 5 && lf2_random(0x37, skill3 + 3) == 0 &&
            target_state != static_cast<int32_t>(STATE_LYING)) {
            self->click_attack = 1;
        }
    }

    if (hazard_right != 0 && self->x < target->x) return 0;
    if (hazard_left != 0 && target->x < self->x) return 0;
    if (lf2_random(0x38, skill3 + 1) != 0) return 0;

    if (cid == static_cast<int32_t>(JOHN_DAT) || cid == static_cast<int32_t>(HENRY_DAT) ||
        cid == static_cast<int32_t>(LOUIS_DAT) || cid == static_cast<int32_t>(FIREN_DAT) ||
        cid == static_cast<int32_t>(FREEZE_DAT) || cid == static_cast<int32_t>(DENNIS_DAT) ||
        cid == static_cast<int32_t>(WOODY_DAT) || cid == static_cast<int32_t>(DAVIS_DAT) ||
        cid == static_cast<int32_t>(JACK_DAT) || cid == static_cast<int32_t>(SORCERER_DAT)) {
        if (dx_target_lead > 100 && dx_target_lead < 900 && dz < 5 &&
            lf2_random(0x39, skill3 + 10) == 0 &&
            target_state != static_cast<int32_t>(STATE_LYING)) {
            self->click_defend = 1;
        }
        if (dx_target_lead > 90) {
            bool facing_ok = (self->facing == FACING_RIGHT && self->x < target->x) ||
                             (self->facing == FACING_LEFT && target->x < self->x);
            int32_t frame = static_cast<int32_t>(self->frame_id1);
            if (facing_ok && (frame == 110 || frame > 234) && dz < 13 &&
                target_state != static_cast<int32_t>(STATE_LYING)) {
                self->holding_right = 0;
                self->holding_left = 0;
                self->holding_attack = 0;
                if (self->x < target->x) self->click_right = 1;
                else self->click_left = 1;
                if (cid == static_cast<int32_t>(SORCERER_DAT) && lf2_random(0x3a, 2) == 0) {
                    self->click_jump = 1;
                } else {
                    self->click_attack = 1;
                }
            }
        }
    }

    if (cid == static_cast<int32_t>(DEEP_DAT)) {
        if (dx_target_lead > 100 && dx_target_lead < 300 && dz < 5 &&
            lf2_random(0x3b, skill5 + 10) == 0 &&
            target_state != static_cast<int32_t>(STATE_LYING)) {
            self->click_defend = 1;
        }
        if (dx_target_lead > 90) {
            bool facing_ok = (self->facing == FACING_RIGHT && self->x < target->x) ||
                             (self->facing == FACING_LEFT && target->x < self->x);
            int32_t frame = static_cast<int32_t>(self->frame_id1);
            if (facing_ok && (frame == 110 || frame > 234) && dz < 7 &&
                target_state != static_cast<int32_t>(STATE_LYING)) {
                self->holding_right = 0;
                self->holding_left = 0;
                self->holding_attack = 0;
                if (self->x < target->x) self->click_right = 1;
                else self->click_left = 1;
                self->click_attack = 1;
            }
        }
    }

    return 1;
}

bool ai_evaluate_dodge(const global_t* world, uint32_t ai_id, uint32_t target_id,
                       input_state_t& out_input, ai_difficulty_t difficulty)
{
    if (!world || ai_id >= MAX_OBJECTS || target_id >= MAX_OBJECTS) return false;
    object_t* self = world->objects[ai_id];
    const object_t* target = world->objects[target_id];
    if (!self || !target || !self->file || !target->file || target->frame_id1 >= MAX_FRAMES) {
        return false;
    }

    int32_t skill = map_difficulty_to_binary(difficulty);
    if (skill < 0) skill = 0;
    int32_t target_state = static_cast<int32_t>(target->file->frames[target->frame_id1].state);

    self->click_defend = 0;
    self->click_jump = 0;
    self->click_attack = 0;
    self->click_down = 0;
    self->click_up = 0;
    self->click_left = 0;
    self->click_right = 0;

    ai_evaluate_dodge(const_cast<global_t*>(world), static_cast<int32_t>(target_id),
                      static_cast<int32_t>(ai_id), target_state, 0, 0, skill * 3, skill * 5);

    out_input = clicks_to_input_state(self);
    return (out_input.attack || out_input.defend || out_input.jump);
}

void ai_control_object(global_t* world, int32_t ai_id, const ai_world_params_t& params)
{
    if (!world || ai_id < 0 || ai_id >= static_cast<int32_t>(MAX_OBJECTS) ||
        !world->is_object_exists[ai_id]) {
        return;
    }
    object_t* self = world->objects[ai_id];
    if (!self || !self->file || self->frame_id1 >= MAX_FRAMES) return;

    int32_t mode = params.mode;

    // 1. Stage "GO!" advance scroll override
    if (mode == 1 && params.stage_last_phase == 1) {
        copy_and_clear_keys(self);
        self->click_right = 1;
        self->holding_right = 0;
        if (self->blocked_right == 1) {
            self->holding_attack = 0;
            self->click_attack = 1;
        }
        return;
    }

    // 2. Waypoint navigation when ai_target_x > -1000
    int32_t skill;
    if (params.random_game ||
        (mode == 1 && self->team != 5 && (ai_id < 20 || self->file->id < 30)) ||
        params.difficulty < 0) {
        skill = 0;
    } else {
        skill = params.difficulty;
    }
    int32_t skill3  = skill * 3;
    int32_t skill5  = skill * 5;
    int32_t skill15 = skill * 15;
    int32_t skill20 = skill * 20;

    if (self->ai_target_x > -1000) {
        copy_and_clear_keys(self);
        uint32_t state = self->file->frames[self->frame_id1].state;
        if (self->x > self->ai_target_x + 6) {
            self->click_left = 1;
            if (self->x > self->ai_target_x + 250 && lf2_random(0x11, skill3 + 3) == 0) {
                self->holding_left = 0;
            }
            if (self->x < self->ai_target_x + 100 && state == STATE_RUNNING && self->facing == FACING_LEFT) {
                self->click_right = 1;
            }
        } else if (self->x < self->ai_target_x - 6) {
            self->click_right = 1;
            if (self->x < self->ai_target_x - 250 && lf2_random(0x12, skill3 + 3) == 0) {
                self->holding_right = 0;
            }
            if (self->x > self->ai_target_x - 100 && state == STATE_RUNNING && self->facing == FACING_RIGHT) {
                self->click_left = 1;
            }
        }
        if (self->z < self->ai_target_z - 3) self->click_down = 1;
        else if (self->z > self->ai_target_z + 3) self->click_up = 1;
        if (self->blocked_right == 1 || self->blocked_left == 1) {
            self->holding_attack = 0;
            self->click_attack = 1;
        }
        if (std::abs(self->ai_target_z - self->z) <= 90 &&
            std::abs(self->ai_target_x - self->x) <= 90) {
            self->ai_target_x = -1000;
            self->ai_target_z = -1000;
        }
        return;
    }

    // 3. Width limit & ally/edge evaluation
    int32_t width_limit = (params.stage_bound > 0) ? params.stage_bound
                        : ((params.stage_width > 0) ? params.stage_width : 794);
    int32_t nearest_distance = 10000;
    int32_t moving_distance = 10000;
    int32_t special_distance = 10000;
    int32_t target_id = -1;
    int32_t close_target = 0;
    int32_t team_count = 0;
    bool strongest = false;
    bool needs_help = false;
    bool cautious = false;
    int32_t edge_flag = 0;

    if ((mode == 1 || mode == 4) && self->team != 5) {
        uint32_t self_team = self->team;
        strongest = true;
        if ((self->max_hp * 4) / 5 < self->hp || self->max_hp - 130 < self->hp) {
            strongest = false;
        }
        for (int32_t j = 0; j < static_cast<int32_t>(MAX_OBJECTS); ++j) {
            if (j != ai_id && world->is_object_exists[j] && world->objects[j] && world->objects[j]->file) {
                object_t* ally = world->objects[j];
                if (ally->hp > 0 && ally->file->type == TYPE_CHARACTER && ally->team == self_team) {
                    if (ally->hp < self->hp) strongest = false;
                    team_count++;
                }
            }
        }
        needs_help = (self->hp > 430 || self->max_hp - 130 < self->hp);
        for (int32_t j = 0; j < static_cast<int32_t>(MAX_OBJECTS); ++j) {
            if (j != ai_id && world->is_object_exists[j] && world->objects[j] && world->objects[j]->file) {
                object_t* ally = world->objects[j];
                if (ally->hp > 0 && ally->file->type == TYPE_CHARACTER && ally->team == self_team &&
                    ally->hp < self->hp - 200) {
                    needs_help = true;
                }
            }
        }
        if (mode == 1) {
            int32_t best_x = -1;
            int32_t best_z = 0;
            for (int32_t j = 0; j < 10; ++j) {
                if (j != ai_id && world->is_object_exists[j] && world->objects[j] && world->objects[j]->file) {
                    object_t* p = world->objects[j];
                    if (p->hp > 0 && p->file->type == TYPE_CHARACTER && best_x < p->x) {
                        best_x = p->x;
                        best_z = p->z;
                    }
                }
            }
            if (best_x > -1) {
                if (best_x < self->x && (std::abs(self->z - best_z) / 2 - best_x) + self->x > 200) {
                    edge_flag = 1;
                }
                if (best_x + 400 < self->x) {
                    edge_flag = 2;
                }
            }
        }
        if (team_count == 0) strongest = false;
    }

    if (self->clone > -1) {
        needs_help = true;
        cautious = true;
    }
    if (self->mp > 250) cautious = true;
    if (mode == 1 && self->team == 1) cautious = true;
    if (ai_id >= 20 && mode == 4) cautious = true;

    // 4. Target acquisition Pass 1
    for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
        if (i == ai_id || !world->is_object_exists[i] || !world->objects[i] || !world->objects[i]->file) {
            continue;
        }
        object_t* cand = world->objects[i];
        if (cand->frame_id1 >= MAX_FRAMES) continue;
        int32_t cstate = static_cast<int32_t>(cand->file->frames[cand->frame_id1].state);
        bool eligible = (cand->file->type == TYPE_CHARACTER) ||
                        (cstate == 3000 && ((self->x < cand->x && cand->x_velocity < 0.0) ||
                                            (cand->x < self->x && cand->x_velocity > 0.0)));
        if (!eligible) continue;

        bool hostile = !((cand->team == self->team) || (mode == 1 && self->team != 5 && cand->team != 5));
        if (hostile && cand->hp > 0 && cstate != static_cast<int32_t>(STATE_LYING) &&
            std::abs(cand->blink_time) < 3) {
            int32_t d = std::abs(cand->z - self->z) + std::abs(cand->x - self->x);
            if (d < nearest_distance) {
                nearest_distance = d;
                target_id = i;
            }
        }
    }

    if (target_id >= 0 && std::abs(world->objects[target_id]->z - self->z) < 15) {
        close_target = 1;
    }

    // 5. Target acquisition Pass 2 (lying / blinking nearby enemy when not catching)
    if (self->file->frames[self->frame_id1].state != STATE_CATCHING) {
        for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
            if (i == ai_id || !world->is_object_exists[i] || !world->objects[i] || !world->objects[i]->file) {
                continue;
            }
            object_t* cand = world->objects[i];
            if (cand->frame_id1 >= MAX_FRAMES) continue;
            bool hostile = !((cand->team == self->team) || (mode == 1 && self->team != 5 && cand->team != 5));
            if (hostile && cand->hp > 0) {
                int32_t cstate = static_cast<int32_t>(cand->file->frames[cand->frame_id1].state);
                if (cstate == static_cast<int32_t>(STATE_LYING) || std::abs(cand->blink_time) >= 3) {
                    int32_t dz_c = std::abs(cand->z - self->z);
                    int32_t dx_c = std::abs(cand->x - self->x);
                    if (dz_c + dx_c < moving_distance && dz_c < 40 && dx_c < 250) {
                        target_id = i;
                        moving_distance = dz_c + dx_c;
                    }
                }
            }
        }
    }

    // 6. Sticky target retention
    int32_t prev = self->enemy;
    if (prev >= 0 && prev < static_cast<int32_t>(MAX_OBJECTS) && world->is_object_exists[prev] == 1 &&
        world->objects[prev] && world->objects[prev]->hp > 0 &&
        lf2_random(0x13, 30) > 0 && world->objects[prev]->file &&
        world->objects[prev]->file->type == TYPE_CHARACTER) {
        target_id = prev;
    } else {
        self->enemy = target_id;
    }

    copy_and_clear_keys(self);
    int32_t saved_target = target_id;
    int32_t anchor_idx = -1;

    if (target_id >= 0) {
        // 7. Hazard & item scan (20..399)
        int32_t right = 0, left = 0, deeper = 0, shallower = 0;
        int32_t danger_aligned = 0, danger_near = 0, found = 0;

        for (int32_t k = 20; k < static_cast<int32_t>(MAX_OBJECTS); ++k) {
            if (!world->is_object_exists[k] || !world->objects[k] || !world->objects[k]->file) continue;
            object_t* obj = world->objects[k];
            if (obj->frame_id1 >= MAX_FRAMES) continue;
            uint32_t oid = obj->file->id;
            int32_t ostate = static_cast<int32_t>(obj->file->frames[obj->frame_id1].state);

            bool john_hazard = false;
            if (oid == JOHN_BALL_DAT) {
                int32_t tenth = static_cast<int32_t>(obj->frame_id1) / 10;
                if (tenth == 6 && obj->team != self->team) {
                    john_hazard = true;
                } else if (tenth == 5 &&
                           (self->file->id == JOHN_DAT || self->file->id == SORCERER_DAT) &&
                           (self->max_hp - 70 <= self->hp || self->max_hp - 200 <= self->hp) &&
                           ((self->max_hp * 3) / 5 <= self->hp || self->hp < self->max_hp - 200) &&
                           obj->team == self->team) {
                    john_hazard = true;
                }
            }
            if (john_hazard) {
                int32_t dz_o = std::abs(obj->z - self->z);
                danger_near = 1;
                if (dz_o < 25) {
                    int32_t dx_o = std::abs(obj->x - self->x);
                    if (dx_o < 150) {
                        danger_aligned = 1;
                        if (dz_o < 20) {
                            if (dx_o < 180) {
                                if (self->z < obj->z) deeper = 1;
                                else shallower = 1;
                            }
                            if (self->x < obj->x) right = 1;
                            else left = 1;
                        }
                    }
                }
            }

            if ((oid == FIREN_FLAME_DAT && ostate == BINARY_STATE_BURNING) ||
                (oid == FREEZE_COLUMN_DAT && obj->frame_id1 >= 150 && obj->frame_id1 <= 170)) {
                if (std::abs(obj->x - self->x) < 80) {
                    if (self->z + 20 < obj->z) deeper = 1;
                    else if (obj->z < self->z - 20) shallower = 1;
                }
                if (std::abs(obj->z - self->z) < 20) {
                    if (self->x + 100 < obj->x) right = 1;
                    else if (obj->x < self->x - 100) left = 1;
                }
            }

            bool skip = false;
            if (found == 0) {
                if (close_target == 0 && danger_near == 0) {
                    int32_t d_item = std::abs(obj->z - self->z) + std::abs(obj->x - self->x);
                    if (self->weapon_type == 0 && d_item < nearest_distance * 2 && d_item < special_distance &&
                        (oid / 100 == 1 || oid == ICE_SWORD_DAT) && obj->weapon_type == 0 &&
                        (ostate == 1004 || ostate == 2004)) {
                        if (!(needs_help && oid == MILK_DAT) &&
                            !(cautious && oid == BEER_DAT) &&
                            !(self->follow_order == 1 && oid != MILK_DAT)) {
                            target_id = k;
                            special_distance = d_item;
                        }
                    }
                }
            } else if (found > 1) {
                skip = true;
            }

            if (!skip) {
                if (oid == JOHN_BALL_DAT && static_cast<int32_t>(obj->frame_id1) / 10 == 5) {
                    if (std::abs(obj->x - self->x) < 300 && std::abs(obj->z - self->z) < 90 &&
                        obj->team == self->team) {
                        if (is_low_health_self(self)) {
                            target_id = k;
                        }
                        found = 1;
                    }
                }
                if (strongest && oid == MILK_DAT && ostate == 1004 && self->weapon_type == 0) {
                    target_id = k;
                    found = 1;
                }
            }
        }

        if (danger_near == 1) {
            target_id = saved_target;
        }

        if (target_id >= 0 && world->objects[target_id] && world->objects[target_id]->file &&
            world->objects[target_id]->frame_id1 < MAX_FRAMES) {
            object_t* target = world->objects[target_id];
            int32_t target_state = static_cast<int32_t>(target->file->frames[target->frame_id1].state);
            int32_t self_state = static_cast<int32_t>(self->file->frames[self->frame_id1].state);
            uint32_t cid = self->file->id;
            anchor_idx = target_id;

            // Obstacle breaker attack
            if (lf2_random(0x14, skill5 + 8) == 0 &&
                (self->blocked_up == 1 || self->blocked_down == 1 ||
                 self->blocked_left == 1 || self->blocked_right == 1)) {
                self->holding_attack = 0;
                self->click_attack = 1;
            }

            // Defend oncoming flying ball
            if (target_state == 3000) {
                if (self_state != static_cast<int32_t>(STATE_DEFEND) && lf2_random(0x15, skill3) == 0) {
                    if ((self->x < target->x && target->x < self->x + 200 && target->x_velocity < 0.0) ||
                        (target->x < self->x && self->x - 200 < target->x && target->x_velocity > 0.0)) {
                        self->holding_defend = 0;
                        self->click_defend = 1;
                    }
                }
                if (self->x < target->x && self->facing == FACING_LEFT) self->click_right = 1;
                if (target->x < self->x && self->facing == FACING_RIGHT) self->click_left = 1;
                return;
            }

            // Follow/stay order drinking & braking
            if (self->follow_order == 1) {
                if (self->weapon_type > 0 && self->weapon_id >= 0 &&
                    self->weapon_id < static_cast<int32_t>(MAX_OBJECTS) &&
                    world->objects[self->weapon_id] && world->objects[self->weapon_id]->file) {
                    uint32_t wid = world->objects[self->weapon_id]->file->id;
                    if (wid == MILK_DAT || wid == BEER_DAT) {
                        self->holding_attack = 0;
                        self->click_attack = 1;
                        return;
                    }
                }
                if (self->x < target->x && self->facing == FACING_LEFT) self->click_right = 1;
                if (target->x < self->x && self->facing == FACING_RIGHT) self->click_left = 1;
                if (self_state == static_cast<int32_t>(STATE_RUNNING)) {
                    if (self->facing == FACING_LEFT) self->click_right = 1;
                    if (self->facing == FACING_RIGHT) self->click_left = 1;
                }
            }

            // Item pickup
            if (target_state == 1004 || target_state == 2004) {
                uint32_t tid = target->file->id;
                if (!(self->follow_order != 0 && far_from(self, target) &&
                      tid != MILK_DAT && tid != BEER_DAT)) {
                    if (self->x > target->x + 6) {
                        self->click_left = 1;
                        if (self->x > target->x + 250 && lf2_random(0x16, skill3 + 3) == 0) {
                            self->holding_left = 0;
                        }
                        if (self->x < target->x + 100 &&
                            self_state == static_cast<int32_t>(STATE_RUNNING) && self->facing == FACING_LEFT) {
                            self->click_right = 1;
                        }
                    } else if (self->x < target->x - 6) {
                        if (edge_flag == 0) self->click_right = 1;
                        if (self->x < target->x - 250 && lf2_random(0x17, skill3 + 3) == 0 && edge_flag == 0) {
                            self->holding_right = 0;
                        }
                        if (self->x > target->x - 100 &&
                            self_state == static_cast<int32_t>(STATE_RUNNING) && self->facing == FACING_RIGHT) {
                            self->click_left = 1;
                        }
                    }
                    if (self->z < target->z - 3) self->click_down = 1;
                    else if (target->z < self->z - 3) self->click_up = 1;
                }
                if (std::abs(target->z - self->z) <= 3 && std::abs(target->x - self->x) <= 6) {
                    self->holding_attack = 0;
                    self->click_attack = 1;
                }
                return;
            }

            // Wait nearby if target is lying / blinking
            if (!(self->follow_order != 0 && far_from(self, target)) &&
                (target_state == static_cast<int32_t>(STATE_LYING) || std::abs(target->blink_time) >= 3)) {
                if (width_limit - 30 < target->x) {
                    self->click_left = 1;
                    self->holding_left = 0;
                    return;
                }
                if (target->x < 30) {
                    self->click_right = 1;
                    self->holding_right = 0;
                    return;
                }
                if (std::abs(target->z - self->z) > 45 && std::abs(target->x - self->x) > 350) {
                    return;
                }
                if (self->x < target->x) {
                    self->click_left = 1;
                    if (lf2_random(0x18, skill20 + 35) == 0) self->holding_left = 0;
                } else {
                    self->click_right = 1;
                    if (lf2_random(0x19, skill20 + 35) == 0) self->holding_right = 0;
                }
                if (target->z < self->z || target->z < params.zboundary_min + 10) {
                    self->click_down = 1;
                } else {
                    self->click_up = 1;
                }
                return;
            }

            // Walk into friendly John healing ball
            if (target->file->id == JOHN_BALL_DAT) {
                if (target->x > self->x + 7) self->click_right = 1;
                else if (target->x < self->x - 7) self->click_left = 1;
                if (target->z > self->z + 2) self->click_down = 1;
                else if (target->z < self->z - 2) self->click_up = 1;
                return;
            }

            // Character-specific special moves (0x00403A40)
            if (ai_evaluate_character_special(world, target_id, ai_id, self_state, target_state,
                                              danger_aligned, nearest_distance, close_target,
                                              width_limit, edge_flag, skill5) != 0) {
                return;
            }

            // Approach / Keep distance
            if (!(self->follow_order != 0 && far_from(self, target))) {
                if ((right == 1 || edge_flag == 1) &&
                    self_state == static_cast<int32_t>(STATE_RUNNING) && self->facing == FACING_RIGHT) {
                    self->click_left = 1;
                }
                if (left == 1 &&
                    self_state == static_cast<int32_t>(STATE_RUNNING) && self->facing == FACING_LEFT) {
                    self->click_right = 1;
                }

                bool keep_dist = (cid == HENRY_DAT || cid == RUDOLF_DAT || cid == HUNTER_DAT) ||
                                 (mode == 1 && target->file->type == TYPE_CHARACTER && ai_id >= 20 &&
                                  self->team != 5 &&
                                  (target->hp > self->hp * 2 || (self->hp <= 100 && self->max_hp > 100)));

                if (keep_dist) {
                    if ((target->x > self->x + 170 ||
                         ((target->x > self->x + 150 ||
                           (self_state == static_cast<int32_t>(STATE_DEFEND) && target->x > self->x)) &&
                          self->facing == FACING_LEFT)) &&
                        right == 0 && edge_flag == 0) {
                        self->click_right = 1;
                        if (lf2_random(0x1a, skill20 + 35) == 0) self->holding_right = 0;
                    }
                    if ((target->x < self->x - 170 ||
                         ((target->x < self->x - 150 ||
                           (self_state == static_cast<int32_t>(STATE_DEFEND) && target->x < self->x)) &&
                          self->facing == FACING_RIGHT)) &&
                        left == 0) {
                        self->click_left = 1;
                        if (lf2_random(0x1b, skill20 + 35) == 0) self->holding_left = 0;
                    }
                } else if (self_state != BINARY_STATE_FIRE_RUN) {
                    if ((target->x > self->x + 60 || (target->x > self->x && self->facing == FACING_LEFT)) &&
                        right == 0 && (edge_flag == 0 || self->facing == FACING_LEFT)) {
                        self->click_right = 1;
                        if (lf2_random(0x1c, skill20 + 35) == 0) self->holding_right = 0;
                    }
                    if ((target->x < self->x - 60 || (target->x < self->x && self->facing == FACING_RIGHT)) &&
                        left == 0) {
                        self->click_left = 1;
                        if (lf2_random(0x1d, skill20 + 35) == 0) self->holding_left = 0;
                    }
                }

                bool dir_hazard = (right == 1 || left == 1);
                if (((target->z > self->z + 3 && danger_aligned == 0) || (dir_hazard && shallower == 1)) &&
                    deeper == 0 && self_state != BINARY_STATE_FIRE_RUN) {
                    self->click_down = 1;
                }
                if (((target->z < self->z - 3 && danger_aligned == 0) || (dir_hazard && deeper == 1)) &&
                    shallower == 0 && self_state != BINARY_STATE_FIRE_RUN) {
                    self->click_up = 1;
                }
            }

            // Held weapon / drink decision (0x00408CB0)
            if (self->weapon_type > 0 &&
                ai_evaluate_weapon_decision(world, target_id, ai_id, self_state, target_state,
                                            close_target, danger_aligned, width_limit, edge_flag,
                                            skill3, skill5, skill15, params) == 0) {
                return;
            }

            // Reactive defend
            if (lf2_random(0x1e, skill * 7 + 10) == 0 &&
                (target_state == static_cast<int32_t>(STATE_ATTACKING) || target_state / 100 == 3) &&
                std::abs(target->z - self->z) < 9 &&
                ((target->facing == FACING_RIGHT && target->x < self->x) ||
                 (target->facing == FACING_LEFT && self->x < target->x))) {
                self->click_defend = 1;
            }

            // Random jump
            if (!(self->follow_order != 0 && far_from(self, target))) {
                if (lf2_random(0x1f, (skill * 5 + 10) * 2) < 3 &&
                    lf2_random(0x20, 20) < 3 &&
                    target_state != static_cast<int32_t>(STATE_LYING)) {
                    self->click_jump = 1;
                }
            }

            // Melee punch
            bool archer_or_ninja = (cid == HENRY_DAT || cid == RUDOLF_DAT || cid == HUNTER_DAT);
            if (!(archer_or_ninja && target_state != BINARY_STATE_DIZZY)) {
                if (std::abs((target->x - static_cast<int32_t>(self->x_velocity) * 2) - self->x) < 80 &&
                    std::abs(target->z - self->z) < 5 &&
                    lf2_random(0x21, skill3 + 3) == 0 &&
                    target_state != static_cast<int32_t>(STATE_LYING)) {
                    self->click_attack = 1;
                }
            }

            // Ranged attacks & corner kite
            bool face_attack = false;
            if (self->weapon_type == 0 && target_state == BINARY_STATE_DIZZY && archer_or_ninja) {
                if (std::abs((target->x - static_cast<int32_t>(self->x_velocity) * 2) - self->x) < 350 &&
                    std::abs(target->z - self->z) < 5 &&
                    lf2_random(0x22, skill3 + 3) == 0) {
                    face_attack = true;
                }
            } else if (self->weapon_type == 0 && target_state != BINARY_STATE_DIZZY &&
                       (archer_or_ninja || cid == JAN_DAT)) {
                int32_t kite = ((target->x - self->x < 100) &&
                                std::abs(target->z - self->z) < 80 &&
                                lf2_random(0x23, skill3 + 2) == 0) ? 1 : 0;
                if (kite != 0 && self_state != static_cast<int32_t>(STATE_DEFEND)) {
                    if (!(self->follow_order != 0 && far_from(self, target))) {
                        edge_move(self, target, width_limit);
                    }
                    if (!(self->follow_order != 0 && far_from(self, target))) {
                        if (lf2_random(0x24, 17) == 0) self->click_jump = 1;
                    }
                } else if (std::abs((target->x - static_cast<int32_t>(self->x_velocity) * 2) - self->x) < 300 &&
                           std::abs(target->z - self->z) < 5 &&
                           lf2_random(0x25, skill3 + 3) == 0 &&
                           target_state != static_cast<int32_t>(STATE_LYING)) {
                    face_attack = true;
                }
            } else if ((target->hp > self->hp * 2 || (self->hp <= 100 && self->max_hp > 100)) &&
                       mode == 1 && target->file->type == TYPE_CHARACTER &&
                       ai_id >= 20 && self->team != 5) {
                int32_t kite = ((target->x - self->x < 100) &&
                                std::abs(target->z - self->z) < 80 &&
                                lf2_random(0x26, skill3 + 2) == 0) ? 1 : 0;
                if (kite != 0 && self_state != static_cast<int32_t>(STATE_DEFEND)) {
                    if (!(self->follow_order != 0 && far_from(self, target))) {
                        edge_move(self, target, width_limit);
                    }
                    if (!(self->follow_order != 0 && far_from(self, target))) {
                        if (lf2_random(0x27, 17) == 0) self->click_jump = 1;
                    }
                }
            }

            if (face_attack &&
                ((self->x < target->x && self->facing == FACING_RIGHT) ||
                 (target->x <= self->x && self->facing == FACING_LEFT))) {
                self->click_attack = 1;
            }

            // Combat dodge / roll & follow-up punch (0x004034F0)
            ai_evaluate_dodge(world, target_id, ai_id, target_state, right, left, skill3, skill5);
            return;
        }
    }

    // 8. No-target edge fallback and special-move cancel (Firen / Dennis / Mark)
    if (anchor_idx == -1 || self->follow_order == 0 ||
        (world->objects[anchor_idx] && far_from(self, world->objects[anchor_idx]))) {
        if (edge_flag == 1) {
            self->click_left = 1;
        }
    }

    uint32_t self_cid = self->file->id;
    int32_t f1 = static_cast<int32_t>(self->frame_id1);
    if ((self_cid == FIREN_DAT && f1 >= 255 && f1 <= 261) ||
        (self_cid == DENNIS_DAT && f1 >= 280 && f1 <= 290) ||
        (self_cid == MARK_DAT && f1 >= 240 && f1 <= 245)) {
        self->click_defend = 1;
    }
}

input_state_t ai_evaluate_behavior(const global_t* world, uint32_t ai_id, ai_difficulty_t difficulty)
{
    input_state_t input{};
    if (!world || ai_id >= MAX_OBJECTS || !world->is_object_exists[ai_id]) {
        return input;
    }
    object_t* self = world->objects[ai_id];
    if (!self || !self->file || self->hp <= 0) return input;
    if (self->fall > 0) return input;

    ai_world_params_t params{};
    params.difficulty = map_difficulty_to_binary(difficulty);
    ai_control_object(const_cast<global_t*>(world), static_cast<int32_t>(ai_id), params);
    return clicks_to_input_state(self);
}

void ai_tick(global_t* world, uint32_t ai_id, const ai_world_params_t& params)
{
    if (!world || ai_id >= MAX_OBJECTS || !world->is_object_exists[ai_id]) {
        return;
    }
    object_t* self = world->objects[ai_id];
    if (!self || !self->file) return;

    ai_control_object(world, static_cast<int32_t>(ai_id), params);
    object_input_tick(self, true, params.unlock_chars);
}

void ai_tick(global_t* world, uint32_t ai_id, ai_difficulty_t difficulty)
{
    ai_world_params_t params{};
    params.difficulty = map_difficulty_to_binary(difficulty);
    ai_tick(world, ai_id, params);
}

} // namespace lf2

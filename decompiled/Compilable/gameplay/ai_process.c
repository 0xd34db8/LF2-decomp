#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Addresses:
 *   0x00406A20: FUN_00406a20 (opoint projectile / effect spawn helper)
 *   0x00406BA0: FUN_00406ba0 (hit_Fa homing, multi-seeker & volcano chase physics)
 *   0x00403A40: FUN_00403a40 (AI character-specific special move decision tree)
 *   0x004034F0: FUN_004034f0 (AI combat dodge / evasive roll & defend maneuver)
 *   0x004094B0: FUN_004094b0 (Primary AI controller & target / input state machine)
 */

static void lf2_ai_copy_and_clear_keys(object_t *obj)
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

static int lf2_ai_is_low_health_self(const object_t *obj)
{
    return ((obj->hp < obj->dark_hp - 70 && obj->hp < 140) ||
            (obj->hp < (obj->dark_hp * 3) / 5 && obj->hp >= 140));
}

static int lf2_ai_help_ally(global_t *global, int self_id, int dist, int z_close)
{
    object_t *self = global->objects[self_id];
    if (!self || !self->file) return 0;

    if ((self->weapon_type == 0 || (int32_t)self->frame_id1 < 9) &&
        !lf2_ai_is_low_health_self(self) && z_close == 0) {
        for (int32_t j = 0; j < 20; ++j) {
            if (j == self_id || !global->is_object_exists[j] || !global->objects[j]) continue;
            object_t *ally = global->objects[j];
            if (ally->team != 0 && ally->team == self->team) {
                int32_t near_x = FUN_004034e0(ally->x - self->x);
                if (near_x < 250) {
                    int32_t near_z = FUN_004034e0(ally->z - self->z);
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
                            FUN_004034e0(ally->x - self->x) < 5) {
                            self->click_DUJ = 3;
                        }
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

static int lf2_ai_far_from(const object_t *a, const object_t *b)
{
    return (FUN_004034e0(a->z - b->z) > 150 || FUN_004034e0(a->x - b->x) > 240);
}

static void lf2_ai_edge_move(object_t *self, const object_t *target, int width_limit)
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

// FUNCTION: LF2 0x00406a20
int FUN_00406a20(int file_id, int owner, int frame_id, int team,
                 int x, int y, int z,
                 double vx, double vy, double vz, int facing)
{
    global_t *global = (global_t *)in_ECX;
    if (!global) return -1;

    int32_t slot = -1;
    for (int32_t i = 50; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0) {
            slot = i;
            break;
        }
    }
    if (slot == -1) return -1;

    for (int32_t f = 0; f < MAX_FILES; ++f) {
        file_t *file = global->files[f];
        if (file && (int32_t)file->id == file_id) {
            object_t *obj = global->objects[slot];
            if (!obj) return -1;
            lf2_object_init(obj);
            obj->file = file;
            obj->x_position = 580.0;
            obj->y_position = -200.0;
            obj->weapon_hp = file->weapon_hp;
            obj->z_position = 300.0;
            obj->owner = owner;
            obj->x = x;
            obj->y = y;
            obj->z = z;
            obj->team = team;
            obj->x_position = (double)x;
            obj->y_position = (double)y;
            obj->z_position = (double)z;
            obj->frame_id1 = (uint32_t)frame_id;
            obj->x_velocity = vx;
            obj->y_velocity = vy;
            obj->z_velocity = vz;
            obj->facing = (uint8_t)facing;
            global->is_object_exists[slot] = 1;
            return slot;
        }
    }
    return -1;
}

// hit_Fa projectile homing / chase / volcano physics (0x00406BA0)
// FUNCTION: LF2 0x00406ba0
void FUN_00406ba0(int param_1)
{
    global_t *global = (global_t *)in_ECX;
    if (!global || param_1 < 0 || param_1 >= MAX_OBJECTS || !global->is_object_exists[param_1]) {
        return;
    }
    object_t *obj = global->objects[param_1];
    if (!obj || !obj->file || obj->frame_id1 >= MAX_FRAMES) return;

    int32_t hit_fa = (int32_t)obj->file->frames[obj->frame_id1].hit_Fa;

    if (hit_fa == 11) {
        FUN_00406a20(ID_FIREN_FLAME_DAT, obj->owner, 109, obj->team, obj->x, obj->y, obj->z,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity, obj->facing);
        FUN_00406a20(ID_FIRZEN_CHASEF_DAT, obj->owner, 81, obj->team, obj->x, obj->y - 100, obj->z,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity, obj->facing);
        FUN_00406a20(ID_FREEZE_COLUMN_DAT, obj->owner, 100, obj->team, obj->x + 80, obj->y - 3, obj->z,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity - 7.0, FACING_RIGHT);
        FUN_00406a20(ID_FREEZE_COLUMN_DAT, obj->owner, 100, obj->team, obj->x + 100, obj->y - 3, obj->z,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_RIGHT);
        FUN_00406a20(ID_FREEZE_COLUMN_DAT, obj->owner, 100, obj->team, obj->x + 80, obj->y - 3, obj->z,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity + 7.0, FACING_RIGHT);
        FUN_00406a20(ID_FREEZE_COLUMN_DAT, obj->owner, 100, obj->team, obj->x - 80, obj->y - 3, obj->z,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity - 7.0, FACING_LEFT);
        FUN_00406a20(ID_FREEZE_COLUMN_DAT, obj->owner, 100, obj->team, obj->x - 100, obj->y - 3, obj->z,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_LEFT);
        FUN_00406a20(ID_FREEZE_COLUMN_DAT, obj->owner, 100, obj->team, obj->x - 80, obj->y - 3, obj->z,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity + 7.0, FACING_LEFT);
        FUN_00406a20(ID_FIREN_FLAME_DAT, obj->owner, 50, obj->team, obj->x - 30, obj->y - 1, obj->z - 5,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_LEFT);
        FUN_00406a20(ID_FIREN_FLAME_DAT, obj->owner, 50, obj->team, obj->x + 30, obj->y - 1, obj->z - 5,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_LEFT);
        FUN_00406a20(ID_FIREN_FLAME_DAT, obj->owner, 50, obj->team, obj->x - 30, obj->y - 1, obj->z + 2,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_RIGHT);
        FUN_00406a20(ID_FIREN_FLAME_DAT, obj->owner, 50, obj->team, obj->x + 30, obj->y - 1, obj->z + 2,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_RIGHT);
        FUN_00406a20(ID_FIREN_FLAME_DAT, obj->owner, 50, obj->team, obj->x, obj->y - 1, obj->z - 9,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_LEFT);
        FUN_00406a20(ID_FIREN_FLAME_DAT, obj->owner, 50, obj->team, obj->x, obj->y - 1, obj->z + 6,
                     obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_RIGHT);
        global->is_object_exists[param_1] = 0;
        return;
    }

    if (hit_fa == 8) {
        int32_t candidates[MAX_OBJECTS];
        int32_t cand_count = 0;
        for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
            if (global->is_object_exists[i] && global->objects[i] && global->objects[i]->file) {
                object_t *cand = global->objects[i];
                if (cand->file->type == TYPE_CHARACTER && cand->team != obj->team && cand->hp > 0) {
                    candidates[cand_count++] = i;
                }
            }
        }
        int32_t amount = (cand_count > 4) ? ((cand_count - 3) / 2 + 3) : 3;
        while (amount > 0) {
            int32_t s = FUN_00406a20(ID_BAT_CHASE_DAT, obj->owner, 0, obj->team,
                                     obj->x, obj->y, obj->z, 0.0, 0.0, 0.0, obj->facing);
            if (s != -1) {
                object_t *bat = global->objects[s];
                bat->x_velocity = (double)(FUN_00417170(4, 21) - 11);
                bat->y_velocity = 3.0 - (double)FUN_00417170(5, 24) * 0.25;
                bat->z_velocity = 3.0 - (double)FUN_00417170(6, 24) * 0.25;
                bat->chase_target = (cand_count == 0) ? param_1 : candidates[FUN_00417170(7, cand_count)];
            }
            amount--;
        }
        global->is_object_exists[param_1] = 0;
        return;
    }

    if (hit_fa == 13) {
        int32_t candidates[MAX_OBJECTS];
        int32_t cand_count = 0;
        for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
            if (global->is_object_exists[i] && global->objects[i] && global->objects[i]->file) {
                object_t *cand = global->objects[i];
                if (cand->file->type == TYPE_CHARACTER && cand->team != obj->team && cand->hp > 0) {
                    candidates[cand_count++] = i;
                }
            }
        }
        int32_t s = FUN_00406a20(ID_JULIAN_BALL_DAT, obj->owner, 0, obj->team,
                                 obj->x, obj->y, obj->z, obj->x_velocity, 0.0, 0.0, obj->facing);
        if (s != -1) {
            object_t *jb = global->objects[s];
            jb->y = FUN_00417170(8, 7) - 3 + obj->y;
            jb->x_position = obj->x_position;
            jb->y_position = obj->y_position;
            jb->z_position = obj->z_position;
            jb->z_velocity = (3.0 - (double)FUN_00417170(11, 24) * 0.25) + obj->z_velocity;
            jb->chase_target = (cand_count == 0) ? param_1 : candidates[FUN_00417170(12, cand_count)];
        }
        global->is_object_exists[param_1] = 0;
        return;
    }

    if (hit_fa == 5) {
        for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
            if (global->is_object_exists[i] == 1 && global->objects[i] && global->objects[i]->file) {
                object_t *ally = global->objects[i];
                if (ally->file->type == TYPE_CHARACTER && ally->team == obj->team && ally->hp > 0) {
                    int32_t s = FUN_00406a20(ID_JAN_CHASEH_DAT, obj->owner, 0, obj->team,
                                             obj->x, obj->y, obj->z, 0.0, 0.0, 0.0, FACING_RIGHT);
                    if (s != -1) {
                        object_t *angel = global->objects[s];
                        angel->x_velocity = (double)((ally->x - angel->x) / 50);
                        angel->y_velocity = 0.0;
                        angel->z_velocity = 0.0;
                        angel->facing = FACING_RIGHT;
                        angel->chase_target = i;
                    }
                }
            }
        }
        global->is_object_exists[param_1] = 0;
        return;
    }

    if (hit_fa == 6 || hit_fa == 9) {
        int32_t minimum = (hit_fa == 9) ? 4 : 0;
        int32_t maximum = (hit_fa == 6) ? 7 : 10;
        int32_t spawned = 0;
        int32_t pass = 0;
        int32_t last_slot = -1;
        do {
            for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
                if (global->is_object_exists[i] == 1 && global->objects[i] && global->objects[i]->file) {
                    object_t *enemy = global->objects[i];
                    if (enemy->file->type == TYPE_CHARACTER && enemy->team != obj->team && enemy->hp > 0 &&
                        (spawned < minimum || pass == 0)) {
                        spawned++;
                        int32_t spawn_fid = (hit_fa == 6) ? ID_JAN_CHASE_DAT : (ID_FIRZEN_CHASEF_DAT + FUN_00417170(13, 2));
                        last_slot = FUN_00406a20(spawn_fid, obj->owner, 0, obj->team,
                                                 obj->x, obj->y, obj->z, 0.0, 0.0, 0.0, FACING_RIGHT);
                        if (last_slot == -1) break;
                        object_t *sp = global->objects[last_slot];
                        if (hit_fa == 6) {
                            sp->x_velocity = (double)((enemy->x - sp->x) / 50);
                            sp->y_velocity = (double)(-4 - FUN_00417170(14, 4));
                        } else {
                            sp->x_velocity = (double)(FUN_00417170(15, 21) - 11);
                            sp->y_velocity = -2.0 - (double)FUN_00417170(16, 40) / 6.0;
                        }
                        sp->z_velocity = 0.0;
                        sp->facing = FACING_RIGHT;
                        sp->chase_target = i;
                        if (spawned >= maximum) break;
                    }
                }
            }
            pass++;
        } while (spawned < minimum && spawned != 0 && last_slot != -1 && spawned < maximum);
        global->is_object_exists[param_1] = 0;
        return;
    }

    if (hit_fa == 7) {
        FUN_00406a20((int)obj->file->id, obj->owner, 40, obj->team,
                     obj->x, obj->y, obj->z, 0.0, 0.0, 0.0, FACING_RIGHT);
    } else if (hit_fa == 10) {
        obj->x_velocity += (obj->x_velocity >= 0.0) ? 1.1 : -1.1;
        if (obj->x_velocity > 30.0) obj->x_velocity = 30.0;
        if (obj->x_velocity < -30.0) obj->x_velocity = -30.0;
        if (obj->y_position > 3.0) obj->y_position = 3.0;
        obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;
        return;
    }

    int32_t deflected_team = -1;
    if (obj->weapon_throw_injury >= 0 && obj->weapon_throw_injury < MAX_OBJECTS &&
        global->is_object_exists[obj->weapon_throw_injury] == 1 && global->objects[obj->weapon_throw_injury]) {
        deflected_team = global->objects[obj->weapon_throw_injury]->team;
    }

    if (hit_fa != 4 && hit_fa != 5 && hit_fa != 6 && hit_fa != 7) {
        int32_t tid = obj->chase_target;
        bool valid_target = false;
        if (tid >= 0 && tid < MAX_OBJECTS && global->is_object_exists[tid] &&
            global->objects[tid] && global->objects[tid]->file) {
            object_t *t = global->objects[tid];
            if (t->hp > 0 && t->file->frames[t->frame_id1].state != STATE_LYING &&
                FUN_004034e0((int)t->invincible_time) < 3 &&
                t->team != obj->team && t->team != deflected_team) {
                valid_target = true;
            }
        }
        if (!valid_target) {
            int32_t best_dist = 10000;
            for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
                if (i == param_1 || !global->is_object_exists[i] || !global->objects[i] || !global->objects[i]->file) {
                    continue;
                }
                object_t *cand = global->objects[i];
                if (cand->file->type == TYPE_CHARACTER && cand->team != obj->team && cand->team != deflected_team) {
                    if (cand->file->frames[cand->frame_id1].state == STATE_LYING ||
                        FUN_004034e0((int)cand->invincible_time) > 2) {
                        if (obj->chase_target != -1) continue;
                    }
                    if (cand->hp > 0) {
                        int32_t d = FUN_004034e0(cand->z - obj->z) + FUN_004034e0(cand->x - obj->x);
                        if (d < best_dist) {
                            best_dist = d;
                            obj->chase_target = i;
                        }
                    }
                }
            }
            if (obj->chase_target == -1) {
                obj->hp = 0;
                return;
            }
        }
    }

    int32_t target_id = obj->chase_target;
    if (target_id < 0 || target_id >= MAX_OBJECTS || !global->objects[target_id]) return;
    object_t *target = global->objects[target_id];

    if (hit_fa == 1) {
        if (obj->x < target->x) obj->x_velocity += 0.85;
        if (target->x < obj->x) obj->x_velocity -= 0.85;
        if (obj->z + 7 < target->z) obj->z_velocity += 0.3;
        if (target->z < obj->z - 7) obj->z_velocity -= 0.3;
        obj->y_velocity /= 1.4;
        if (target->file && target->file->type == TYPE_CHARACTER) {
            if (obj->y_position + 10.0 < target->y_position) obj->y_position += 1.2;
            if (target->y_position < obj->y_position + 10.0) obj->y_position -= 1.2;
        } else if (obj->y_position > 0.0) {
            obj->y_position += 1.0;
        }
        if (obj->x_velocity > 13.0) obj->x_velocity = 13.0;
        if (obj->x_velocity < -13.0) obj->x_velocity = -13.0;
        if (obj->z_velocity > 2.0) obj->z_velocity = 2.0;
        if (obj->z_velocity < -2.0) obj->z_velocity = -2.0;
        if (obj->y_position > 1.0) obj->y_position = 1.0;
        obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;
        return;
    }

    if (hit_fa == 4 && target->hp > 0 &&
        target->x - 30 < obj->x && obj->x < target->x + 30 &&
        target->y - 80 < obj->y && obj->y < target->y &&
        target->z - 10 < obj->z && obj->z < target->z + 10) {
        obj->x_velocity = 0.0;
        obj->y_velocity = 0.0;
        obj->z_velocity = 0.0;
        obj->frame_id1 = 60;
        target->heal_timer = 100;
        return;
    }

    bool chasing = (hit_fa == 2 || hit_fa == 4 || hit_fa == 7 || hit_fa == 12 || hit_fa == 14);
    if (chasing && obj->hp > 0 && global->is_object_exists[param_1] == 1) {
        if (obj->x < target->x) obj->x_velocity += 0.7;
        if (target->x < obj->x) obj->x_velocity -= 0.7;
        if (hit_fa == 7) {
            if (obj->x < target->x) obj->x_velocity += 0.7;
            if (target->x < obj->x) obj->x_velocity -= 0.7;
        }
        if (obj->z + 5 < target->z) obj->z_velocity += 0.4;
        if (target->z < obj->z - 5) obj->z_velocity -= 0.4;

        if (hit_fa == 2 || hit_fa == 4 || hit_fa == 12) {
            obj->y_velocity /= 1.4;
            if (target->file && target->file->type == TYPE_CHARACTER) {
                if (obj->y_position + 40.0 < target->y_position) obj->y_position += 1.0;
                if (target->y_position < obj->y_position + 40.0) obj->y_position -= 1.0;
            } else if (obj->y_position > 0.0) {
                obj->y_position += 1.0;
            }
        } else if (hit_fa == 7) {
            if (obj->y_velocity < 4.0) obj->y_velocity += 0.4;
            obj->y_position += obj->y_velocity;
            if (obj->y > -25) {
                obj->frame_id1 = 60;
                obj->x_velocity = 0.0;
                obj->y_velocity = 0.0;
                obj->z_velocity = 0.0;
            }
        }

        if (obj->x_velocity > 14.0) obj->x_velocity = 14.0;
        if (obj->x_velocity < -14.0) obj->x_velocity = -14.0;
        if (obj->y_position > 1.4) obj->y_position = 1.4;
        double max_z = (hit_fa == 14) ? 1.5 : 2.2;
        if (obj->z_velocity > max_z) obj->z_velocity = max_z;
        if (obj->z_velocity < -max_z) obj->z_velocity = -max_z;
        obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;

        double speed = (obj->x_velocity < 0.0) ? -obj->x_velocity : obj->x_velocity;
        if (hit_fa == 14) {
            if (speed >= 8.0) {
                if (obj->frame_id1 >= 41) obj->frame_id1 -= 50;
            } else {
                if (obj->frame_id1 < 10) obj->frame_id1 += 50;
            }
            return;
        }
        if (hit_fa == 2) {
            if (speed > 14.0) {
                if (obj->frame_id1 != 5 && obj->frame_id1 != 6) obj->frame_id1 = 5;
            } else if (speed > 7.0) {
                if (obj->frame_id1 != 3 && obj->frame_id1 != 4) obj->frame_id1 = 3;
            } else if (obj->frame_id1 != 1 && obj->frame_id1 != 2) {
                obj->frame_id1 = 1;
            }
        }
        return;
    }

    if (chasing && (obj->hp <= 0 || global->is_object_exists[param_1] == 0)) {
        obj->x_velocity += (obj->x_velocity >= 0.0) ? 2.0 : -2.0;
        if (obj->x_velocity > 17.0) obj->x_velocity = 17.0;
        if (obj->x_velocity < -17.0) obj->x_velocity = -17.0;
        if (hit_fa == 2 || hit_fa == 4 || hit_fa == 14 || hit_fa == 12) {
            if (obj->y_position > 1.4) obj->y_position = 1.4;
        } else if (hit_fa == 7) {
            if (obj->y_velocity < 4.0) obj->y_velocity += 0.4;
            obj->y_position += obj->y_velocity;
            if (obj->y > -25) {
                obj->frame_id1 = 60;
                obj->y = -25;
                obj->x_velocity = 0.0;
                obj->y_velocity = 0.0;
                obj->z_velocity = 0.0;
            }
        }
        obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;
        double speed = (obj->x_velocity < 0.0) ? -obj->x_velocity : obj->x_velocity;
        if (hit_fa == 2) {
            if (speed > 14.0) {
                if (obj->frame_id1 != 5 && obj->frame_id1 != 6) obj->frame_id1 = 5;
            } else if (speed > 7.0) {
                if (obj->frame_id1 != 3 && obj->frame_id1 != 4) obj->frame_id1 = 3;
            } else if (obj->frame_id1 != 1 && obj->frame_id1 != 2) {
                obj->frame_id1 = 1;
            }
        }
        return;
    }

    if (hit_fa == 3) {
        if (obj->x < target->x) obj->x_velocity += 0.7;
        if (target->x < obj->x) obj->x_velocity -= 0.7;
        if (obj->z + 10 < target->z) obj->z_velocity += 0.17;
        if (target->z < obj->z - 10) obj->z_velocity -= 0.17;
        if (obj->x_velocity > 16.0) obj->x_velocity = 16.0;
        if (obj->x_velocity < -16.0) obj->x_velocity = -16.0;
        if (obj->z_velocity > 2.4) obj->z_velocity = 2.4;
        if (obj->z_velocity < -2.4) obj->z_velocity = -2.4;
    }
}

// AI character-specific special move decision (0x00403A40)
// FUNCTION: LF2 0x00403a40
int FUN_00403a40(int target_id, int self_id, int self_state, int target_state,
                 int incoming_proj, int dist, int z_close)
{
    global_t *global = (global_t *)in_ECX;
    if (!global || target_id < 0 || target_id >= MAX_OBJECTS || self_id < 0 || self_id >= MAX_OBJECTS) {
        return 0;
    }
    if (FUN_00417170(0x3c, DAT_0044f618 + 1) > 0) {
        return 0;
    }

    object_t *self = global->objects[self_id];
    object_t *target = global->objects[target_id];
    if (!self || !target || !self->file || !target->file) return 0;

    int32_t cid = (int32_t)self->file->id;
    int32_t tid = (int32_t)target->file->id;
    int32_t dx = FUN_004034e0(target->x - self->x);
    int32_t dz = FUN_004034e0(target->z - self->z);
    int32_t width_limit = (DAT_0044f604 > 0) ? DAT_0044f604 : 794;
    bool facing_toward = (self->facing == FACING_RIGHT && self->x < target->x) ||
                         (self->facing == FACING_LEFT && target->x < self->x);

    // Trigger special inputs directly on combo_state bytes (0x0D4..0x0DC)
    if (cid == ID_JOHN_DAT) {
        if (FUN_00417170(0x3d, 10) == 0 && self->mp > 350 && lf2_ai_is_low_health_self(self)) {
            self->click_DDJ = 3;
            return 1;
        }
        if (dist < 10000 && FUN_00417170(0x3e, 30) == 0 && self->mp > 250) {
            self->click_DUA = 3;
            return 1;
        }
        if (tid == ID_JOHN_DAT || tid == ID_DENNIS_DAT || tid == ID_WOODY_DAT ||
            tid == ID_DAVIS_DAT || tid == ID_JACK_DAT || tid == ID_SORCERER_DAT) {
            if (FUN_00417170(0x3f, 15) == 0 && dx > 100 && dx < 500 && dz < 30 &&
                self->mp > 100 && target->mp > 220 && incoming_proj == 0) {
                if (self->x < target->x) self->click_DRJ = 3;
                else self->click_DLJ = 3;
                return 1;
            }
        } else {
            if (FUN_00417170(0x40, 15) == 0 && dx > 100 && dx < 250 && dz < 30 &&
                self->mp > 100 && target->mp > 170 && incoming_proj == 0) {
                if (self->x < target->x) self->click_DRJ = 3;
                else self->click_DLJ = 3;
                return 1;
            }
        }
        if (lf2_ai_help_ally(global, self_id, dist, z_close)) {
            return 1;
        }
    }

    if (cid == ID_DEEP_DAT) {
        if (self->frame_id1 >= 260 && self->frame_id1 <= 289 && dx < 100 && dz < 7) {
            if ((target->y == 0 && self->y == 0 && FUN_00417170(0x41, 3) == 0) ||
                (target->y < 0 && self->y < 0 && FUN_00417170(0x42, 7) == 0)) {
                self->click_attack = 1;
                self->holding_attack = 0;
                return 1;
            }
            if ((target->y < 0 && FUN_00417170(0x43, 5) == 0) || FUN_00417170(0x44, 30) == 0) {
                if (facing_toward) {
                    self->click_jump = 1;
                }
                self->holding_jump = 0;
            }
            return 1;
        }
        if (FUN_00417170(0x45, 7) == 0 && dx < 150 && dz < 8 && self->mp > 150 &&
            ((FUN_00417170(0x46, 10) == 0 && target_state != STATE_ATTACKING) ||
             (FUN_00417170(0x47, 3) > 0 && (target_state == 16 || target_state == 8 || target_state == 11)))) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (FUN_00417170(0x48, 7) == 0 && dx < 100 && dz < 7 && self->mp > 75) {
            if (self->mp > 150 &&
                ((FUN_00417170(0x49, 10) == 0 && target_state != STATE_ATTACKING) ||
                 (FUN_00417170(0x4a, 3) > 0 && target_state == 16))) {
                if (self->x < target->x) self->click_DRJ = 3;
                else self->click_DLJ = 3;
                return 1;
            }
            self->click_DDA = 3;
            return 1;
        }
    }

    if (cid == ID_HENRY_DAT) {
        if (self->mp > 360 && dx < 100 && dz < 70 && FUN_00417170(0x4b, self->hp / 5 + 10) == 0) {
            self->click_DUJ = 3;
            return 1;
        }
        if (FUN_00417170(0x4c, 45) == 0 && dx > 100 && dx < 550 && dz < 20 && self->mp > 170) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (FUN_00417170(0x4d, 30) == 0 && self->mp > 200 && dx > 100 && dx < 160 && dz < 55 && facing_toward) {
            self->click_DJA = 3;
            return 1;
        }
    }

    if (cid == ID_RUDOLF_DAT) {
        if (self->mp > 450 && dx > 100 && dz > 50 && FUN_00417170(0x4e, 3) == 0) {
            if (FUN_00417170(0x4f, 2) == 0) self->click_DUJ = 3;
            else self->click_DDJ = 3;
            return 1;
        }
        if (self->mp > 70 && dx > 100 && dx < 160 && dz < 8 && FUN_00417170(0x50, 10) == 0) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (FUN_00417170(0x51, 30) == 0 && self->mp > 200 && dx > 100 && dx < 160 && dz < 55) {
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

    if (cid == ID_LOUIS_DAT) {
        if (self->mp > 100 && dx > 80 && dx < 130 && dz < 30 && FUN_00417170(0x52, 10) == 0) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (self->mp > 100 && dx < 45 && dz < 5 && FUN_00417170(0x53, 3) == 0) {
            self->click_DUJ = 3;
            return 1;
        }
        if (self_state == STATE_CATCHING && FUN_00417170(0x54, 8) == 0) {
            self->click_jump = 1;
            self->holding_jump = 0;
        }
    }

    if (cid == ID_FIREN_DAT) {
        if (self->frame_id1 > 267 && self->frame_id1 < 283) {
            if (target_state == STATE_FALLING || target_state == 11 ||
                dx > 150 || dz > 25 || facing_toward) {
                self->click_defend = 1;
                self->holding_defend = 0;
                return 1;
            }
        }
        if (target_state != STATE_BURNING && target_state != STATE_LYING) {
            if (target_state != STATE_FALLING && self->hp > 70 && self->mp > 320 &&
                (dx > 50 || dz > 10) && dx < 85 && target->hp < self->hp && dz < 35 &&
                FUN_00417170(0x55, 5) == 0) {
                self->click_DUJ = 3;
                return 1;
            }
            if (target_state != STATE_FALLING && self->mp > 200 && dx > 100 && dx < 370 && dz < 60 &&
                FUN_00417170(0x56, 20) == 0) {
                if (self->x < target->x) self->click_DRJ = 3;
                else self->click_DLJ = 3;
                return 1;
            }
        }
        if (FUN_00417170(0x57, 100) == 0 && dx > 240 && dx < 400) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (target_state != STATE_BURNING && target_state != STATE_LYING && target_state != STATE_FALLING &&
            self->mp > 200 && dx > 60 && dx < 280 && dz < 60 && FUN_00417170(0x58, 15) == 0) {
            if (facing_toward) {
                self->click_DDJ = 3;
                return 1;
            }
        }
        if (self->frame_id1 >= 255 && self->frame_id1 <= 261) {
            if ((self->facing == FACING_RIGHT && (target->x + 120 < self->x || width_limit - 30 < self->x)) ||
                (self->facing == FACING_LEFT && (self->x < target->x - 120 || self->x < 30)) ||
                dz > 70 || DAT_0044f608 == 1) {
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

    if (cid == ID_FREEZE_DAT) {
        if (target_state != STATE_ICE) {
            if ((self->mp > 200 && dx < 400 && dz < 170 && FUN_00417170(0x59, 250) == 0) ||
                (target_state != STATE_LYING && self->mp > 200 && dx > 60 && dx < 280 && dz < 65 &&
                 FUN_00417170(0x5a, 15) == 0)) {
                if (self->x < target->x) self->click_DRJ = 3;
                else self->click_DLJ = 3;
                return 1;
            }
        }
        if (target_state != STATE_LYING && self->mp > 320 &&
            ((dx > 50 || dz > 7) || target_state == STATE_ICE) && dx < 125 && dz < 25 &&
            FUN_00417170(0x5b, 3) == 0 && facing_toward) {
            self->click_DUJ = 3;
            return 1;
        }
        if (FUN_00417170(0x5c, 50) == 0 && self->weapon_type == 0 && self->mp > 200 &&
            dx > 200 && dz > 50) {
            self->click_DDJ = 3;
            return 1;
        }
    }

    if (cid == ID_DAVIS_DAT) {
        if (self->mp > 150 && dx < 280 && dz < 30 && FUN_00417170(0x5d, 10) == 0) {
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
        if (FUN_00417170(0x5e, 5) == 0 || target_state == 16 || target_state == 8) {
            int32_t dx_lead = FUN_004034e0(((int32_t)self->x_velocity - self->x) + target->x);
            if (dx_lead < 100 && dz < 7 && self->mp > 200 && facing_toward) {
                self->click_DUA = 3;
                return 1;
            }
        }
    }

    if (cid == ID_WOODY_DAT) {
        if (self->mp > 100 && dx < 280 && dz < 25 && FUN_00417170(0x5f, 10) == 0) {
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
        if (self->frame_id1 == 271 && target->y < 0 && target_state == STATE_FALLING) {
            self->click_DUA = 3;
            return 1;
        }
        if (FUN_00417170(0x60, 10) == 0 || target_state == 16 || target_state == 8) {
            int32_t dx_lead = FUN_004034e0(((int32_t)self->x_velocity - self->x) + target->x);
            if (dx_lead < 80 && dz < 7 && facing_toward) {
                self->click_DUA = 3;
                return 1;
            }
        }
        if (self->mp > 200 && dx > 60 && dx < 280 && dz < 65 &&
            (FUN_00417170(0x61, 15) == 0 ||
             (FUN_00417170(0x62, 4) == 0 &&
              (target_state == 16 || target_state == 8 || (target_state == STATE_FALLING && target->y < -40))))) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (self->hp < 250 && self->hp < target->hp + 50 &&
            FUN_00417170(99, 20) == 0 && self->mp > 75) {
            int32_t best = -1;
            int32_t best_idx = -1;
            for (int32_t j = 0; j < MAX_OBJECTS; ++j) {
                if (j != self_id && global->is_object_exists[j] && global->objects[j] && global->objects[j]->file) {
                    object_t *cand = global->objects[j];
                    if (cand->file->type == TYPE_CHARACTER && cand->team == self->team && target->hp < cand->hp) {
                        int32_t d = FUN_004034e0(cand->z - self->z) + FUN_004034e0(cand->x - self->x);
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
        if (target->hp < self->hp && FUN_00417170(100, 70) == 0 && self->mp > 500) {
            self->click_DUJ = 3;
        }
    }

    if (cid == ID_DENNIS_DAT) {
        if (FUN_00417170(0x65, 10) == 0 || target_state == 16 || target_state == 8) {
            int32_t dx_lead = FUN_004034e0(((int32_t)self->x_velocity - self->x) + target->x);
            if (dx_lead < 120 && dz < 7 && facing_toward) {
                self->click_DDA = 3;
                return 1;
            }
        }
        if ((target_state != STATE_BURNING && target_state != STATE_LYING && target_state != STATE_FALLING &&
             self->mp > 200 && dx > 75 && dx < 370 && dz < 60 && FUN_00417170(0x66, 13) == 0) ||
            (FUN_00417170(0x67, target->hp / 4 + 40) == 0 && dx > 150 && dx < 400)) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (dist < 10000 && FUN_00417170(0x68, 30) == 0 && self->mp > 150) {
            self->click_DUA = 3;
            return 1;
        }
    }

    if (cid == ID_MARK_DAT) {
        if ((target_state != STATE_BURNING && target_state != STATE_LYING && target_state != STATE_FALLING &&
             self->mp > 200 && dx < 270 && dz < 60 && FUN_00417170(0x69, 60) == 0) ||
            (FUN_00417170(0x6a, target->hp / 4 + 40) == 0 && dx > 150 && dx < 400)) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (dx < 150 && dz < 40 && FUN_00417170(0x6b, 15) == 0) {
            if (self->x < target->x) self->click_DRA = 3;
            else self->click_DLA = 3;
            return 1;
        }
    }

    if (cid == ID_JACK_DAT && (FUN_00417170(0x6c, 5) == 0 || target_state == 16 || target_state == 8)) {
        int32_t dx_lead = FUN_004034e0(((int32_t)self->x_velocity - self->x) + target->x);
        if (dx_lead < 60 && dz < 7 && self->mp > 150 && facing_toward) {
            self->click_DUA = 3;
            return 1;
        }
    }

    if (cid == ID_SORCERER_DAT) {
        if (FUN_00417170(0x6d, 10) == 0 && self->mp > 350 && lf2_ai_is_low_health_self(self)) {
            self->click_DDJ = 3;
            return 1;
        }
        if (lf2_ai_help_ally(global, self_id, dist, z_close)) {
            return 1;
        }
    }

    if (cid == ID_LOUISE_EX_DAT) {
        if (FUN_00417170(0x6e, 7) == 0 && dx < 500 && dx > 90 && dz < 4 && self->mp > 150) {
            if (target->frame_id1 == 263 || target->frame_id1 == 264) {
                self->holding_attack = 0;
                self->click_attack = 1;
            } else {
                if (self->x < target->x) self->click_DRA = 3;
                else self->click_DLA = 3;
                return 1;
            }
        }
        if (FUN_00417170(0x6f, 7) == 0 && dx < 100 && dz < 7 && self->mp > 75) {
            self->click_DDA = 3;
            return 1;
        }
    }

    if (cid == ID_MONK_DAT && FUN_00417170(0x70, 7) == 0 &&
        dx < 650 && dx > 40 && dz < 4 && self->mp > 120) {
        if (self->x < target->x) self->click_DRA = 3;
        else self->click_DLA = 3;
        return 1;
    }

    if (cid == ID_JAN_DAT) {
        if (self->mp > 200 && FUN_00417170(0x71, 5) == 0) {
            for (int32_t j = 0; j < 100; ++j) {
                if (global->is_object_exists[j] == 1 && global->objects[j] && global->objects[j]->file) {
                    object_t *ally = global->objects[j];
                    if (ally->file->type == TYPE_CHARACTER && ally->team == self->team &&
                        (ally->hp < ally->dark_hp - 200 || (ally->hp < 200 && ally->hp < ally->dark_hp - 100))) {
                        self->click_DUJ = 3;
                        return 1;
                    }
                }
            }
            return 1;
        }
        if (self->mp > 260 && FUN_00417170(0x72, 10) == 0 && dx < 650 && dz < 240) {
            self->click_DUA = 3;
            return 1;
        }
    }

    if (cid == ID_BAT_DAT) {
        if (self->mp > 150 && FUN_00417170(0x73, 5) == 0 && dx < 250 && dx > 130 && dz < 10) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (self->mp > 200 && FUN_00417170(0x74, 10) == 0 && dz < 10) {
            if (self->x < target->x) self->click_DRA = 3;
            else self->click_DLA = 3;
            return 1;
        }
        if (self->mp > 200 && FUN_00417170(0x75, 10) == 0 && (dx > 200 || dz < 250)) {
            self->click_DUJ = 3;
            return 1;
        }
    }

    if (cid == ID_JUSTIN_DAT) {
        if (self->mp > 100 && FUN_00417170(0x76, 3) == 0 && dx < 120 && facing_toward && dz < 10) {
            self->click_DDA = 3;
            return 1;
        }
        if (self->mp > 100 && FUN_00417170(0x77, 7) == 0 && dx < 250 && dz < 10) {
            if (self->x < target->x) self->click_DRA = 3;
            else self->click_DLA = 3;
            return 1;
        }
    }

    if (cid == ID_JULIAN_DAT) {
        if (target_state == STATE_ATTACKING && self->mp > 125 && FUN_00417170(0x78, 10) == 0 &&
            dx < 120 && dz < 10) {
            self->click_DJA = 3;
            return 1;
        }
        if (self->mp > 125 && FUN_00417170(0x7b, 5) == 0 && dx < 100 && dz < 30) {
            if (target->x <= self->x) return 1;
            self->click_DUJ = 3;
            return 1;
        }
        if (self->mp > 125 && FUN_00417170(0x7c, 14) == 0 && dx < 700 && dz < 150) {
            if (self->x < target->x) self->click_DRA = 3;
            else self->click_DLA = 3;
            return 1;
        }
        if (self->mp > 125 && FUN_00417170(0x7d, 5) == 0 && dz < 20) {
            if (self->x < target->x) self->click_DRJ = 3;
            else self->click_DLJ = 3;
            return 1;
        }
        if (FUN_00417170(0x7e, 5) == 0 || target_state == 16 || target_state == 8) {
            int32_t dx_lead = FUN_004034e0(((int32_t)self->x_velocity - self->x) + target->x);
            if (dx_lead < 100 && dz < 7 && self->mp < 100 && facing_toward) {
                self->click_DUA = 3;
                return 1;
            }
        }
    }

    if (cid != ID_FIRZEN_DAT) {
        return 0;
    }

    if (self->frame_id1 > 265 && self->frame_id1 < 280 &&
        (dz > 13 || target->file->type != TYPE_CHARACTER)) {
        self->holding_defend = 0;
        self->click_defend = 1;
        return 1;
    }
    if (self->mp > 300 && FUN_00417170(0x7f, 10) == 0 && dx < 300 && dz < 200) {
        self->click_DUJ = 3;
        return 1;
    }
    if (self->mp > 300 && FUN_00417170(0x80, 10) == 0 && dx < 950) {
        self->click_DUA = 3;
        return 1;
    }
    if (FUN_00417170(0x81, 5) == 0 && self->mp > 250 && dx < 1200 && dx > 40 && dz < 13) {
        if (self->x < target->x) self->click_DRJ = 3;
        else self->click_DLJ = 3;
        return 1;
    }
    return 0;
}

// AI combat dodge / roll and shield defense maneuver (0x004034F0)
// FUNCTION: LF2 0x004034f0
int FUN_004034f0(int target_id, int self_id, int param_3, int target_state, int param_5, int hazard_right, int hazard_left)
{
    global_t *global = (global_t *)in_ECX;
    if (!global || target_id < 0 || target_id >= MAX_OBJECTS || self_id < 0 || self_id >= MAX_OBJECTS) {
        return 0;
    }
    object_t *self = global->objects[self_id];
    object_t *target = global->objects[target_id];
    if (!self || !target || !self->file || !target->file) return 0;

    int32_t cid = (int32_t)self->file->id;
    int32_t dx_self_lead = FUN_004034e0((target->x - ((int32_t)self->x_velocity) * 2) - self->x);
    int32_t dx_target_lead = FUN_004034e0((target->x + ((int32_t)target->x_velocity) * 2) - self->x);
    int32_t dz = FUN_004034e0(target->z - self->z);

    if (((cid != ID_HENRY_DAT && cid != ID_RUDOLF_DAT) && cid != ID_HUNTER_DAT) || cid != ID_JAN_DAT) {
        if (dx_self_lead < 80 && dz < 5 && FUN_00417170(0x37, DAT_0044f61c + 3) == 0 && target_state != STATE_LYING) {
            self->click_attack = 1;
        }
    }

    if (hazard_right != 0 && self->x < target->x) return 0;
    if (hazard_left != 0 && target->x < self->x) return 0;
    if (FUN_00417170(0x38, DAT_0044f61c + 1) != 0) return 0;

    if (cid == ID_JOHN_DAT || cid == ID_HENRY_DAT || cid == ID_LOUIS_DAT ||
        cid == ID_FIREN_DAT || cid == ID_FREEZE_DAT || cid == ID_DENNIS_DAT ||
        cid == ID_WOODY_DAT || cid == ID_DAVIS_DAT || cid == ID_JACK_DAT || cid == ID_SORCERER_DAT) {
        if (100 < dx_target_lead && dx_target_lead < 900 && dz < 5 &&
            FUN_00417170(0x39, DAT_0044f61c + 10) == 0 && target_state != STATE_LYING) {
            self->click_defend = 1;
        }
        if (dx_target_lead > 90) {
            int32_t facing_ok = (self->facing == FACING_RIGHT && self->x < target->x) ||
                                (self->facing == FACING_LEFT && target->x < self->x);
            int32_t frame = (int32_t)self->frame_id1;
            if (facing_ok && (frame == 110 || frame > 234) && dz < 13 && target_state != STATE_LYING) {
                self->holding_right = 0;
                self->holding_left = 0;
                self->holding_attack = 0;
                if (self->x < target->x) self->click_right = 1;
                else self->click_left = 1;
                if (cid == ID_SORCERER_DAT && FUN_00417170(0x3a, 2) == 0) {
                    self->click_jump = 1;
                } else {
                    self->click_attack = 1;
                }
            }
        }
    }

    if (cid == ID_DEEP_DAT) {
        if (100 < dx_target_lead && dx_target_lead < 300 && dz < 5 &&
            FUN_00417170(0x3b, DAT_0044f618 + 10) == 0 && target_state != STATE_LYING) {
            self->click_defend = 1;
        }
        if (dx_target_lead > 90) {
            int32_t facing_ok = (self->facing == FACING_RIGHT && self->x < target->x) ||
                                (self->facing == FACING_LEFT && target->x < self->x);
            int32_t frame = (int32_t)self->frame_id1;
            if (facing_ok && (frame == 110 || frame > 234) && dz < 7 && target_state != STATE_LYING) {
                self->holding_right = 0;
                self->holding_left = 0;
                self->holding_attack = 0;
                if (self->x < target->x) self->click_right = 1;
                else self->click_left = 1;
                self->click_attack = 1;
            }
        }
    }
    (void)param_3;
    (void)param_5;
    return 1;
}

// Primary AI Controller (0x004094B0)
// FUNCTION: LF2 0x004094b0
void FUN_004094b0(int obj_id, int mode)
{
    global_t *global = (global_t *)in_ECX;
    if (!global || obj_id < 0 || obj_id >= MAX_OBJECTS || !global->is_object_exists[obj_id]) {
        return;
    }
    object_t *self = global->objects[obj_id];
    if (!self || !self->file) return;

    // 1. Stage "GO!" advance scroll override
    if (mode == 1 && DAT_00450bac == 1) {
        lf2_ai_copy_and_clear_keys(self);
        self->click_right = 1;
        self->holding_right = 0;
        if (self->blocked_right == 1) {
            self->holding_attack = 0;
            self->click_attack = 1;
        }
        return;
    }

    // 2. Waypoint navigation when ai_target_x > -1000
    if (self->ai_target_x > -1000) {
        lf2_ai_copy_and_clear_keys(self);
        int32_t state = (int32_t)self->file->frames[self->frame_id1].state;
        if (self->x > self->ai_target_x + 6) {
            self->click_left = 1;
            if (self->x > self->ai_target_x + 250 && FUN_00417170(0x11, DAT_0044f61c + 3) == 0) {
                self->holding_left = 0;
            }
            if (self->x < self->ai_target_x + 100 && state == STATE_RUNNING && self->facing == FACING_LEFT) {
                self->click_right = 1;
            }
        } else if (self->x < self->ai_target_x - 6) {
            self->click_right = 1;
            if (self->x < self->ai_target_x - 250 && FUN_00417170(0x12, DAT_0044f61c + 3) == 0) {
                self->holding_right = 0;
            }
            if (self->x > self->ai_target_x - 100 && state == STATE_RUNNING && self->facing == FACING_RIGHT) {
                self->click_left = 1;
            }
        }
        if (self->z < self->ai_target_z - 3) {
            self->click_down = 1;
        } else if (self->z > self->ai_target_z + 3) {
            self->click_up = 1;
        }
        if (self->blocked_right == 1 || self->blocked_left == 1) {
            self->holding_attack = 0;
            self->click_attack = 1;
        }
        if (FUN_004034e0(self->ai_target_z - self->z) <= 90 &&
            FUN_004034e0(self->ai_target_x - self->x) <= 90) {
            self->ai_target_x = -1000;
            self->ai_target_z = -1000;
        }
        return;
    }

    // 3. Stage width & dynamic difficulty scaling
    DAT_0044f604 = (DAT_00450bb4 > 0) ? DAT_00450bb4 : 794;
    if (DAT_00450c2c == 1 ||
        (mode == 1 && self->team != 5 && (obj_id < 20 || (int32_t)self->file->id < 30)) ||
        DAT_00450c30 < 0) {
        DAT_0044f60c = 0;
    } else {
        DAT_0044f60c = DAT_00450c30;
    }
    DAT_0044f61c = DAT_0044f60c * 3;
    DAT_0044f618 = DAT_0044f60c * 5;
    DAT_0044f614 = DAT_0044f60c * 15;
    DAT_0044f610 = DAT_0044f60c * 20;

    int32_t nearest_distance = 10000;
    int32_t moving_distance = 10000;
    int32_t special_distance = 10000;
    int32_t target_id = -1;
    int32_t close_target = 0;
    int32_t team_count = 0;
    bool strongest = false;
    bool needs_help = false;
    bool cautious = false;
    DAT_0044f608 = 0;

    // 4. Stage / Battle ally health & leading player scan
    if ((mode == 1 || mode == 4) && (int32_t)self->team != 5) {
        uint32_t self_team = self->team;
        strongest = true;
        if ((self->max_hp * 4) / 5 < self->hp || self->max_hp - 130 < self->hp) {
            strongest = false;
        }
        for (int32_t j = 0; j < MAX_OBJECTS; ++j) {
            if (j != obj_id && global->is_object_exists[j] && global->objects[j] && global->objects[j]->file) {
                object_t *ally = global->objects[j];
                if (ally->hp > 0 && ally->file->type == TYPE_CHARACTER && ally->team == self_team) {
                    if (ally->hp < self->hp) strongest = false;
                    team_count++;
                }
            }
        }
        needs_help = false;
        if (self->hp > 430 || self->max_hp - 130 < self->hp) {
            needs_help = true;
        }
        for (int32_t j = 0; j < MAX_OBJECTS; ++j) {
            if (j != obj_id && global->is_object_exists[j] && global->objects[j] && global->objects[j]->file) {
                object_t *ally = global->objects[j];
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
                if (j != obj_id && global->is_object_exists[j] && global->objects[j] && global->objects[j]->file) {
                    object_t *p = global->objects[j];
                    if (p->hp > 0 && p->file->type == TYPE_CHARACTER && best_x < p->x) {
                        best_x = p->x;
                        best_z = p->z;
                    }
                }
            }
            if (best_x > -1) {
                if (best_x < self->x &&
                    (FUN_004034e0(self->z - best_z) / 2 - best_x) + self->x > 200) {
                    DAT_0044f608 = 1;
                }
                if (best_x + 400 < self->x) {
                    DAT_0044f608 = 2;
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
    if (obj_id >= 20 && mode == 4) cautious = true;

    // 5. Target acquisition Pass 1 (living enemy chars + oncoming flying balls state == 3000)
    for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (i == obj_id || !global->is_object_exists[i] || !global->objects[i] || !global->objects[i]->file) {
            continue;
        }
        object_t *cand = global->objects[i];
        int32_t cstate = (int32_t)cand->file->frames[cand->frame_id1].state;
        bool eligible = false;
        if (cand->file->type == TYPE_CHARACTER) {
            eligible = true;
        } else if (cstate == 3000) {
            if ((self->x < cand->x && cand->x_velocity < 0.0) ||
                (cand->x < self->x && cand->x_velocity > 0.0)) {
                eligible = true;
            }
        }
        if (!eligible) continue;

        bool hostile = !((cand->team == self->team) || (mode == 1 && self->team != 5 && cand->team != 5));
        if (hostile && cand->hp > 0 && cstate != STATE_LYING && FUN_004034e0((int)cand->invincible_time) < 3) {
            int32_t d = FUN_004034e0(cand->z - self->z) + FUN_004034e0(cand->x - self->x);
            if (d < nearest_distance) {
                nearest_distance = d;
                target_id = i;
            }
        }
    }

    if (target_id >= 0 && FUN_004034e0(global->objects[target_id]->z - self->z) < 15) {
        close_target = 1;
    }

    // 6. Target acquisition Pass 2 (nearby lying / blinking enemy when not catching)
    if (self->file->frames[self->frame_id1].state != STATE_CATCHING) {
        for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
            if (i == obj_id || !global->is_object_exists[i] || !global->objects[i] || !global->objects[i]->file) {
                continue;
            }
            object_t *cand = global->objects[i];
            bool hostile = !((cand->team == self->team) || (mode == 1 && self->team != 5 && cand->team != 5));
            if (hostile && cand->hp > 0) {
                int32_t cstate = (int32_t)cand->file->frames[cand->frame_id1].state;
                if (cstate == STATE_LYING || FUN_004034e0((int)cand->invincible_time) >= 3) {
                    int32_t dz_c = FUN_004034e0(cand->z - self->z);
                    int32_t dx_c = FUN_004034e0(cand->x - self->x);
                    if (dz_c + dx_c < moving_distance && dz_c < 40 && dx_c < 250) {
                        target_id = i;
                        moving_distance = dz_c + dx_c;
                    }
                }
            }
        }
    }

    // 7. Sticky target retention (29/30 stickiness)
    int32_t prev = self->enemy;
    if (prev >= 0 && prev < MAX_OBJECTS && global->is_object_exists[prev] == 1 &&
        global->objects[prev] && global->objects[prev]->hp > 0 &&
        FUN_00417170(0x13, 30) > 0 && global->objects[prev]->file &&
        global->objects[prev]->file->type == TYPE_CHARACTER) {
        target_id = prev;
    } else {
        self->enemy = target_id;
    }

    lf2_ai_copy_and_clear_keys(self);
    int32_t saved_target = target_id;
    int32_t anchor_idx = -1;

    if (target_id >= 0) {
        // 8. Object hazard & item scan (20..399)
        int32_t right = 0, left = 0, deeper = 0, shallower = 0;
        int32_t danger_aligned = 0, danger_near = 0, found = 0;

        for (int32_t k = 20; k < MAX_OBJECTS; ++k) {
            if (!global->is_object_exists[k] || !global->objects[k] || !global->objects[k]->file) continue;
            object_t *obj = global->objects[k];
            int32_t oid = (int32_t)obj->file->id;
            int32_t ostate = (int32_t)obj->file->frames[obj->frame_id1].state;

            bool john_hazard = false;
            if (oid == ID_JOHN_BALL_DAT) {
                int32_t tenth = (int32_t)obj->frame_id1 / 10;
                if (tenth == 6 && obj->team != self->team) {
                    john_hazard = true;
                } else if (tenth == 5 &&
                           ((int32_t)self->file->id == ID_JOHN_DAT || (int32_t)self->file->id == ID_SORCERER_DAT) &&
                           (self->max_hp - 70 <= self->hp || self->max_hp - 200 <= self->hp) &&
                           ((self->max_hp * 3) / 5 <= self->hp || self->hp < self->max_hp - 200) &&
                           obj->team == self->team) {
                    john_hazard = true;
                }
            }
            if (john_hazard) {
                int32_t dz_o = FUN_004034e0(obj->z - self->z);
                danger_near = 1;
                if (dz_o < 25) {
                    int32_t dx_o = FUN_004034e0(obj->x - self->x);
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

            if ((oid == ID_FIREN_FLAME_DAT && ostate == STATE_BURNING) ||
                (oid == ID_FREEZE_COLUMN_DAT && obj->frame_id1 >= 150 && obj->frame_id1 <= 170)) {
                if (FUN_004034e0(obj->x - self->x) < 80) {
                    if (self->z + 20 < obj->z) deeper = 1;
                    else if (obj->z < self->z - 20) shallower = 1;
                }
                if (FUN_004034e0(obj->z - self->z) < 20) {
                    if (self->x + 100 < obj->x) right = 1;
                    else if (obj->x < self->x - 100) left = 1;
                }
            }

            bool skip = false;
            if (found == 0) {
                if (close_target == 0 && danger_near == 0) {
                    int32_t d_item = FUN_004034e0(obj->z - self->z) + FUN_004034e0(obj->x - self->x);
                    if (self->weapon_type == 0 && d_item < nearest_distance * 2 && d_item < special_distance &&
                        (oid / 100 == 1 || oid == ID_ICE_SWORD_DAT) && obj->weapon_type == 0 &&
                        (ostate == 1004 || ostate == 2004)) {
                        if (!(needs_help && oid == ID_MILK_DAT) &&
                            !(cautious && oid == ID_BEER_DAT) &&
                            !(self->follow_order == 1 && oid != ID_MILK_DAT)) {
                            target_id = k;
                            special_distance = d_item;
                        }
                    }
                }
            } else if (found > 1) {
                skip = true;
            }

            if (!skip) {
                if (oid == ID_JOHN_BALL_DAT && (int32_t)obj->frame_id1 / 10 == 5) {
                    if (FUN_004034e0(obj->x - self->x) < 300 && FUN_004034e0(obj->z - self->z) < 90 &&
                        obj->team == self->team) {
                        if (lf2_ai_is_low_health_self(self)) {
                            target_id = k;
                        }
                        found = 1;
                    }
                }
                if (strongest && oid == ID_MILK_DAT && ostate == 1004 && self->weapon_type == 0) {
                    target_id = k;
                    found = 1;
                }
            }
        }

        if (danger_near == 1) {
            target_id = saved_target;
        }

        if (target_id >= 0 && global->objects[target_id] && global->objects[target_id]->file) {
            object_t *target = global->objects[target_id];
            int32_t target_state = (int32_t)target->file->frames[target->frame_id1].state;
            int32_t self_state = (int32_t)self->file->frames[self->frame_id1].state;
            int32_t cid = (int32_t)self->file->id;
            anchor_idx = target_id;

            // Obstacle breaker attack when blocked
            if (FUN_00417170(0x14, DAT_0044f618 + 8) == 0 &&
                (self->blocked_up == 1 || self->blocked_down == 1 ||
                 self->blocked_left == 1 || self->blocked_right == 1)) {
                self->holding_attack = 0;
                self->click_attack = 1;
            }

            // Defend oncoming flying ball (state == 3000)
            if (target_state == 3000) {
                if (self_state != STATE_DEFENDING && FUN_00417170(0x15, DAT_0044f61c) == 0) {
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

            // Stay/follow order behavior (0x404 == 1): drink immediately & face target while braking
            if (self->follow_order == 1) {
                if (self->weapon_type > 0 && self->weapon_id >= 0 && self->weapon_id < MAX_OBJECTS &&
                    global->objects[self->weapon_id] && global->objects[self->weapon_id]->file) {
                    uint32_t wid = global->objects[self->weapon_id]->file->id;
                    if (wid == ID_MILK_DAT || wid == ID_BEER_DAT) {
                        self->holding_attack = 0;
                        self->click_attack = 1;
                        return;
                    }
                }
                if (self->x < target->x && self->facing == FACING_LEFT) self->click_right = 1;
                if (target->x < self->x && self->facing == FACING_RIGHT) self->click_left = 1;
                if (self_state == STATE_RUNNING) {
                    if (self->facing == FACING_LEFT) self->click_right = 1;
                    if (self->facing == FACING_RIGHT) self->click_left = 1;
                }
            }

            // Pick up resting item (1004 / 2004)
            if (target_state == 1004 || target_state == 2004) {
                int32_t tid = (int32_t)target->file->id;
                if (!(self->follow_order != 0 && lf2_ai_far_from(self, target) &&
                      tid != ID_MILK_DAT && tid != ID_BEER_DAT)) {
                    if (self->x > target->x + 6) {
                        self->click_left = 1;
                        if (self->x > target->x + 250 && FUN_00417170(0x16, DAT_0044f61c + 3) == 0) {
                            self->holding_left = 0;
                        }
                        if (self->x < target->x + 100 && self_state == STATE_RUNNING && self->facing == FACING_LEFT) {
                            self->click_right = 1;
                        }
                    } else if (self->x < target->x - 6) {
                        if (DAT_0044f608 == 0) self->click_right = 1;
                        if (self->x < target->x - 250 && FUN_00417170(0x17, DAT_0044f61c + 3) == 0 && DAT_0044f608 == 0) {
                            self->holding_right = 0;
                        }
                        if (self->x > target->x - 100 && self_state == STATE_RUNNING && self->facing == FACING_RIGHT) {
                            self->click_left = 1;
                        }
                    }
                    if (self->z < target->z - 3) self->click_down = 1;
                    else if (target->z < self->z - 3) self->click_up = 1;
                }
                if (FUN_004034e0(target->z - self->z) <= 3 && FUN_004034e0(target->x - self->x) <= 6) {
                    self->holding_attack = 0;
                    self->click_attack = 1;
                }
                return;
            }

            // Wait nearby if target is lying / blinking
            if (!(self->follow_order != 0 && lf2_ai_far_from(self, target)) &&
                (target_state == STATE_LYING || FUN_004034e0((int)target->invincible_time) >= 3)) {
                if (DAT_0044f604 - 30 < target->x) {
                    self->click_left = 1;
                    self->holding_left = 0;
                    return;
                }
                if (target->x < 30) {
                    self->click_right = 1;
                    self->holding_right = 0;
                    return;
                }
                if (FUN_004034e0(target->z - self->z) > 45 && FUN_004034e0(target->x - self->x) > 350) {
                    return;
                }
                if (self->x < target->x) {
                    self->click_left = 1;
                    if (FUN_00417170(0x18, DAT_0044f610 + 35) == 0) self->holding_left = 0;
                } else {
                    self->click_right = 1;
                    if (FUN_00417170(0x19, DAT_0044f610 + 35) == 0) self->holding_right = 0;
                }
                if (target->z < self->z || target->z < lf2_bg_zmin + 10) {
                    self->click_down = 1;
                } else {
                    self->click_up = 1;
                }
                return;
            }

            // Walk into friendly John healing ball
            if ((int32_t)target->file->id == ID_JOHN_BALL_DAT) {
                if (target->x > self->x + 7) self->click_right = 1;
                else if (target->x < self->x - 7) self->click_left = 1;
                if (target->z > self->z + 2) self->click_down = 1;
                else if (target->z < self->z - 2) self->click_up = 1;
                return;
            }

            // Character-specific specials
            if (FUN_00403a40(target_id, obj_id, self_state, target_state, danger_aligned, nearest_distance, close_target) != 0) {
                return;
            }

            // Approach & spacing
            if (!(self->follow_order != 0 && lf2_ai_far_from(self, target))) {
                if ((right == 1 || DAT_0044f608 == 1) && self_state == STATE_RUNNING && self->facing == FACING_RIGHT) {
                    self->click_left = 1;
                }
                if (left == 1 && self_state == STATE_RUNNING && self->facing == FACING_LEFT) {
                    self->click_right = 1;
                }

                bool keep_dist = (cid == ID_HENRY_DAT || cid == ID_RUDOLF_DAT || cid == ID_HUNTER_DAT) ||
                                 (mode == 1 && target->file->type == TYPE_CHARACTER && obj_id >= 20 &&
                                  (int32_t)self->team != 5 &&
                                  (target->hp > self->hp * 2 || (self->hp <= 100 && self->max_hp > 100)));

                if (keep_dist) {
                    if ((target->x > self->x + 170 ||
                         ((target->x > self->x + 150 || (self_state == STATE_DEFENDING && target->x > self->x)) &&
                          self->facing == FACING_LEFT)) &&
                        right == 0 && DAT_0044f608 == 0) {
                        self->click_right = 1;
                        if (FUN_00417170(0x1a, DAT_0044f610 + 35) == 0) self->holding_right = 0;
                    }
                    if ((target->x < self->x - 170 ||
                         ((target->x < self->x - 150 || (self_state == STATE_DEFENDING && target->x < self->x)) &&
                          self->facing == FACING_RIGHT)) &&
                        left == 0) {
                        self->click_left = 1;
                        if (FUN_00417170(0x1b, DAT_0044f610 + 35) == 0) self->holding_left = 0;
                    }
                } else if (self_state != STATE_FIRE) {
                    if ((target->x > self->x + 60 || (target->x > self->x && self->facing == FACING_LEFT)) &&
                        right == 0 && (DAT_0044f608 == 0 || self->facing == FACING_LEFT)) {
                        self->click_right = 1;
                        if (FUN_00417170(0x1c, DAT_0044f610 + 35) == 0) self->holding_right = 0;
                    }
                    if ((target->x < self->x - 60 || (target->x < self->x && self->facing == FACING_RIGHT)) &&
                        left == 0) {
                        self->click_left = 1;
                        if (FUN_00417170(0x1d, DAT_0044f610 + 35) == 0) self->holding_left = 0;
                    }
                }

                bool dir_hazard = (right == 1 || left == 1);
                if (((target->z > self->z + 3 && danger_aligned == 0) || (dir_hazard && shallower == 1)) &&
                    deeper == 0 && self_state != STATE_FIRE) {
                    self->click_down = 1;
                }
                if (((target->z < self->z - 3 && danger_aligned == 0) || (dir_hazard && deeper == 1)) &&
                    shallower == 0 && self_state != STATE_FIRE) {
                    self->click_up = 1;
                }
            }

            // Held weapon / drink keys
            if (self->weapon_type > 0 &&
                FUN_00408cb0(target_id, obj_id, self_state, target_state, close_target, danger_aligned) == 0) {
                return;
            }

            // Reactive defend against incoming melee / weapon attack
            if (FUN_00417170(0x1e, DAT_0044f60c * 7 + 10) == 0 &&
                (target_state == STATE_ATTACKING || target_state / 100 == 3) &&
                FUN_004034e0(target->z - self->z) < 9 &&
                ((target->facing == FACING_RIGHT && target->x < self->x) ||
                 (target->facing == FACING_LEFT && self->x < target->x))) {
                self->click_defend = 1;
            }

            // Random jump when close/mid
            if (!(self->follow_order != 0 && lf2_ai_far_from(self, target))) {
                if (FUN_00417170(0x1f, (DAT_0044f60c * 5 + 10) * 2) < 3 &&
                    FUN_00417170(0x20, 20) < 3 && target_state != STATE_LYING) {
                    self->click_jump = 1;
                }
            }

            // Melee punch
            bool archer_or_ninja = (cid == ID_HENRY_DAT || cid == ID_RUDOLF_DAT || cid == ID_HUNTER_DAT);
            if (!(archer_or_ninja && target_state != 16)) {
                if (FUN_004034e0((target->x - ((int32_t)self->x_velocity) * 2) - self->x) < 80 &&
                    FUN_004034e0(target->z - self->z) < 5 &&
                    FUN_00417170(0x21, DAT_0044f61c + 3) == 0 && target_state != STATE_LYING) {
                    self->click_attack = 1;
                }
            }

            // Ranged attacks & corner kite
            bool face_attack = false;
            if (self->weapon_type == 0 && target_state == 16 && archer_or_ninja) {
                if (FUN_004034e0((target->x - ((int32_t)self->x_velocity) * 2) - self->x) < 350 &&
                    FUN_004034e0(target->z - self->z) < 5 &&
                    FUN_00417170(0x22, DAT_0044f61c + 3) == 0) {
                    face_attack = true;
                }
            } else if (self->weapon_type == 0 && target_state != 16 &&
                       (archer_or_ninja || cid == ID_JAN_DAT)) {
                int32_t kite = ((target->x - self->x < 100) &&
                                FUN_004034e0(target->z - self->z) < 80 &&
                                FUN_00417170(0x23, DAT_0044f61c + 2) == 0) ? 1 : 0;
                if (kite != 0 && self_state != STATE_DEFENDING) {
                    if (!(self->follow_order != 0 && lf2_ai_far_from(self, target))) {
                        lf2_ai_edge_move(self, target, DAT_0044f604);
                    }
                    if (!(self->follow_order != 0 && lf2_ai_far_from(self, target))) {
                        if (FUN_00417170(0x24, 17) == 0) self->click_jump = 1;
                    }
                } else if (FUN_004034e0((target->x - ((int32_t)self->x_velocity) * 2) - self->x) < 300 &&
                           FUN_004034e0(target->z - self->z) < 5 &&
                           FUN_00417170(0x25, DAT_0044f61c + 3) == 0 &&
                           target_state != STATE_LYING) {
                    face_attack = true;
                }
            } else if ((target->hp > self->hp * 2 || (self->hp <= 100 && self->max_hp > 100)) &&
                       mode == 1 && target->file->type == TYPE_CHARACTER &&
                       obj_id >= 20 && (int32_t)self->team != 5) {
                int32_t kite = ((target->x - self->x < 100) &&
                                FUN_004034e0(target->z - self->z) < 80 &&
                                FUN_00417170(0x26, DAT_0044f61c + 2) == 0) ? 1 : 0;
                if (kite != 0 && self_state != STATE_DEFENDING) {
                    if (!(self->follow_order != 0 && lf2_ai_far_from(self, target))) {
                        lf2_ai_edge_move(self, target, DAT_0044f604);
                    }
                    if (!(self->follow_order != 0 && lf2_ai_far_from(self, target))) {
                        if (FUN_00417170(0x27, 17) == 0) self->click_jump = 1;
                    }
                }
            }

            if (face_attack &&
                ((self->x < target->x && self->facing == FACING_RIGHT) ||
                 (target->x <= self->x && self->facing == FACING_LEFT))) {
                self->click_attack = 1;
            }

            // Combat dodge / roll & follow-up punch
            FUN_004034f0(target_id, obj_id, self_state, target_state, close_target, right, left);
            return;
        }
    }

    // 9. No-target edge fallback and special-move cancel (Firen / Dennis / Mark)
    if (anchor_idx == -1 || self->follow_order == 0 ||
        (global->objects[anchor_idx] && lf2_ai_far_from(self, global->objects[anchor_idx]))) {
        if (DAT_0044f608 == 1) {
            self->click_left = 1;
        }
    }

    int32_t self_cid = (int32_t)self->file->id;
    int32_t f1 = (int32_t)self->frame_id1;
    if ((self_cid == ID_FIREN_DAT && f1 >= 255 && f1 <= 261) ||
        (self_cid == ID_DENNIS_DAT && f1 >= 280 && f1 <= 290) ||
        (self_cid == ID_MARK_DAT && f1 >= 240 && f1 <= 245)) {
        self->click_defend = 1;
    }
}

void func_00406ba0_ai_process(void *world_ptr, uint32_t object_id)
{
    void *prev_ecx = in_ECX;
    in_ECX = world_ptr;
    FUN_004094b0((int)object_id, 0);
    in_ECX = prev_ecx;
}

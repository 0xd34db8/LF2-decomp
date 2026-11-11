#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Addresses:
 *   0x00406A20: FUN_00406a20 (opointprojectile / effect spawn helper)
 *   0x00406BA0: FUN_00406ba0 (hit_Fa projectile homing / chase / volcano physics)
 *   0x00403A40: FUN_00403a40 (AI character-specific special move decision)
 *   0x004094B0: FUN_004094b0 (Primary AI controller & target / input state machine)
 */

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
            obj->weapon_hp = file->weapon_hp;
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
            obj->facing = facing;
            global->is_object_exists[slot] = 1;
            return slot;
        }
    }
    return -1;
}

// hit_Fa projectile homing / chase / volcano physics (0x00406BA0)
void FUN_00406ba0(int param_1)
{
    global_t *global = (global_t *)in_ECX;
    if (!global || param_1 < 0 || param_1 >= MAX_OBJECTS || !global->is_object_exists[param_1]) {
        return;
    }
    object_t *obj = global->objects[param_1];
    if (!obj || !obj->file) return;

    int32_t hit_fa = (int32_t)obj->file->frames[obj->frame_id1].hit_Fa;
    if (hit_fa == 11) {
        // Firzen Arctic Volcano eruption (spawns fire/ice columns & flames)
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
        global->is_object_exists[param_1] = 0;
        return;
    }

    if (hit_fa == 10) {
        // Julian soul bomb acceleration
        obj->x_velocity += (obj->x_velocity >= 0.0) ? 1.1 : -1.1;
        if (obj->x_velocity > 30.0) obj->x_velocity = 30.0;
        if (obj->x_velocity < -30.0) obj->x_velocity = -30.0;
        if (obj->y_position > 3.0) obj->y_position = 3.0;
        obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;
        return;
    }

    // Target acquisition for homing projectiles (hit_Fa == 1, 2, 3, 4, 7, 12, 14)
    int32_t target_id = *((int32_t *)&obj->ai_target_x - 1);
    int32_t deflected_team = -1;
    if (obj->weapon_throw_injury >= 0 && obj->weapon_throw_injury < MAX_OBJECTS &&
        global->is_object_exists[obj->weapon_throw_injury] && global->objects[obj->weapon_throw_injury]) {
        deflected_team = global->objects[obj->weapon_throw_injury]->team;
    }

    if (hit_fa != 4 && hit_fa != 5 && hit_fa != 6 && hit_fa != 7) {
        bool valid_target = false;
        if (target_id >= 0 && target_id < MAX_OBJECTS &&
            global->is_object_exists[target_id] && global->objects[target_id] &&
            global->objects[target_id]->file) {
            object_t *t = global->objects[target_id];
            if (t->hp > 0 &&
                t->file->frames[t->frame_id1].state != STATE_LYING &&
                FUN_004034e0((int)t->invincible_time) < 3 &&
                t->team != obj->team &&
                t->team != deflected_team) {
                valid_target = true;
            }
        }
        if (!valid_target) {
            int32_t best_dist = 10000;
            target_id = -1;
            for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
                if (i == param_1 || !global->is_object_exists[i] || !global->objects[i] || !global->objects[i]->file) {
                    continue;
                }
                object_t *cand = global->objects[i];
                if (cand->file->type == TYPE_CHARACTER &&
                    cand->team != obj->team &&
                    cand->team != deflected_team &&
                    cand->hp > 0) {
                    if (cand->file->frames[cand->frame_id1].state == STATE_LYING ||
                        FUN_004034e0((int)cand->invincible_time) > 2) {
                        if (target_id != -1) continue;
                    }
                    int32_t d = FUN_004034e0(cand->z - obj->z) + FUN_004034e0(cand->x - obj->x);
                    if (d < best_dist) {
                        best_dist = d;
                        target_id = i;
                    }
                }
            }
            *((int32_t *)&obj->ai_target_x - 1) = target_id;
            if (target_id == -1) {
                obj->hp = 0;
                return;
            }
        }
    }

    if (target_id < 0 || target_id >= MAX_OBJECTS || !global->objects[target_id]) return;
    object_t *target = global->objects[target_id];

    if (hit_fa == 1) {
        // Dennis / Woody / Davis homing ball steering
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
    } else if (hit_fa == 3) {
        // Henry Sonata of the Death homing arrow steering
        if (obj->x < target->x) obj->x_velocity += 0.7;
        if (target->x < obj->x) obj->x_velocity -= 0.7;
        if (obj->z + 10 < target->z) obj->z_velocity += 0.17;
        if (target->z < obj->z - 10) obj->z_velocity -= 0.17;
        if (obj->x_velocity > 16.0) obj->x_velocity = 16.0;
        if (obj->x_velocity < -16.0) obj->x_velocity = -16.0;
        if (obj->z_velocity > 2.4) obj->z_velocity = 2.4;
        if (obj->z_velocity < -2.4) obj->z_velocity = -2.4;
    } else if (hit_fa == 2 || hit_fa == 4 || hit_fa == 7 || hit_fa == 12 || hit_fa == 14) {
        // Jan heal angel (4) / Bat (14) / Firzen disaster (7) / Chase (2, 12)
        if (hit_fa == 4 && target->hp > 0 &&
            obj->x > target->x - 30 && obj->x < target->x + 30 &&
            obj->y > target->y - 80 && obj->y < target->y &&
            obj->z > target->z - 10 && obj->z < target->z + 10) {
            obj->x_velocity = 0.0;
            obj->y_velocity = 0.0;
            obj->z_velocity = 0.0;
            obj->frame_id1 = 60;
            target->additional_y = 100;
            return;
        }
        if (obj->hp > 0 && global->is_object_exists[param_1] == 1) {
            if (obj->x < target->x) obj->x_velocity += (hit_fa == 7) ? 1.4 : 0.7;
            if (target->x < obj->x) obj->x_velocity -= (hit_fa == 7) ? 1.4 : 0.7;
            if (obj->z + 5 < target->z) obj->z_velocity += 0.4;
            if (target->z < obj->z - 5) obj->z_velocity -= 0.4;
            if (obj->x_velocity > 14.0) obj->x_velocity = 14.0;
            if (obj->x_velocity < -14.0) obj->x_velocity = -14.0;
            double max_z = (hit_fa == 14) ? 1.5 : 2.2;
            if (obj->z_velocity > max_z) obj->z_velocity = max_z;
            if (obj->z_velocity < -max_z) obj->z_velocity = -max_z;
            obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;
        }
    }
}

// AI character-specific special move decision (0x00403A40)
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
    int32_t dx = FUN_004034e0(target->x - self->x);
    int32_t dz = FUN_004034e0(target->z - self->z);

    // Trigger special input codes (reserve at 0xD8..0xDC):
    // 0xD6 = D>A, 0xD7 = D^A, 0xD8 = D>J, 0xD9 = D<J, 0xDA = D^J, 0xDB = DvJ, 0xDC = DvA
    uint8_t *combo = (uint8_t *)&self->defense_breaking;

    if (cid == ID_JOHN_DAT || cid == ID_SORCERER_DAT) {
        if (FUN_00417170(0x3d, 10) == 0 && self->mp > 350 &&
            ((self->hp < self->dark_hp - 70 && self->hp < 140) ||
             (self->hp < (self->dark_hp * 3) / 5 && self->hp >= 140))) {
            combo[7] = 3; // 0xDB: heal self
            return 1;
        }
    }
    if (cid == ID_DEEP_DAT) {
        if (FUN_00417170(0x48, 7) == 0 && dx < 100 && dz < 7 && self->mp > 75) {
            combo[3] = 3; // 0xD7: D^A / DvA slash
            return 1;
        }
    }
    if (cid == ID_HENRY_DAT && self->mp > 360 && dx < 100 && dz < 70 &&
        FUN_00417170(0x4b, self->hp / 5 + 10) == 0) {
        combo[6] = 3; // 0xDA: Sonata of the Death
        return 1;
    }
    if (cid == ID_DENNIS_DAT || cid == ID_WOODY_DAT || cid == ID_DAVIS_DAT ||
        cid == ID_FIREN_DAT || cid == ID_FREEZE_DAT || cid == ID_FIRZEN_DAT ||
        cid == ID_JULIAN_DAT) {
        if (self->mp > 150 && dx > 60 && dx < 350 && dz < 30 && FUN_00417170(0x56, 20) == 0) {
            if (self->x < target->x) combo[4] = 3; // 0xD8
            else combo[5] = 3;                     // 0xD9
            return 1;
        }
    }
    (void)self_state;
    (void)target_state;
    (void)incoming_proj;
    (void)dist;
    (void)z_close;
    return 0;
}

// AI combat dodge / roll and shield defense maneuver (0x004034F0)
int FUN_004034f0(int target_id, int self_id, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    global_t *global = (global_t *)in_ECX;
    if (!global || target_id < 0 || target_id >= MAX_OBJECTS || self_id < 0 || self_id >= MAX_OBJECTS) {
        return 0;
    }
    object_t *self = global->objects[self_id];
    object_t *target = global->objects[target_id];
    if (!self || !target || !self->file || !target->file) return 0;

    int32_t cid = (int32_t)self->file->id;
    int32_t dx = FUN_004034e0(target->x - self->x);
    int32_t dz = FUN_004034e0(target->z - self->z);

    if (cid != ID_FIREN_DAT && cid != ID_FREEZE_DAT && cid != ID_JULIAN_DAT && cid != ID_FIRZEN_DAT) {
        if (dx < 80 && dz < 5 && FUN_00417170(0x37, DAT_0044f61c + 3) == 0 && param_4 != 0xe) {
            self->click_attack = 1;
        }
    }

    if (param_6 != 0 && self->x < target->x) return 0;
    if (param_7 != 0 && target->x < self->x) return 0;
    if (FUN_00417170(0x38, DAT_0044f61c + 1) != 0) return 0;

    // Guard defense against standard roster attacks
    if (cid == ID_DEEP_DAT || cid == ID_FIREN_DAT || cid == ID_DENNIS_DAT ||
        cid == ID_MARK_DAT || cid == ID_JAN_DAT || cid == ID_MONK_DAT ||
        cid == ID_DAVIS_DAT || cid == ID_WOODY_DAT || cid == ID_BAT_DAT || cid == ID_LOUISE_EX_DAT) {
        if (100 < dx && dx < 900 && dz < 5 &&
            FUN_00417170(0x39, DAT_0044f61c + 10) == 0 && param_4 != 0xe) {
            self->click_defend = 1;
        }
        // Roll / dodge check
        if (dx > 90) {
            int32_t facing_ok = (self->facing == FACING_RIGHT && self->x < target->x) ||
                                (self->facing == FACING_LEFT && target->x < self->x);
            int32_t frame = (int32_t)self->frame_id1;
            if (facing_ok && (frame == 110 || frame > 234) && dz < 13 && param_4 != 0xe) {
                self->click_left = 0;
                self->click_right = 0;
                self->holding_left = 0;
                self->holding_right = 0;
                if (self->x < target->x) self->click_right = 1;
                else self->click_left = 1;
                if (cid == ID_LOUISE_EX_DAT && FUN_00417170(0x3a, 2) == 0) {
                    self->click_jump = 1;
                } else {
                    self->click_attack = 1;
                }
            }
        }
    }

    // John specific shield / heal defense
    if (cid == ID_JOHN_DAT) {
        if (100 < dx && dx < 300 && dz < 5 &&
            FUN_00417170(0x3b, DAT_0044f618 + 10) == 0 && param_4 != 0xe) {
            self->click_defend = 1;
        }
        if (dx > 90) {
            int32_t facing_ok = (self->facing == FACING_RIGHT && self->x < target->x) ||
                                (self->facing == FACING_LEFT && target->x < self->x);
            int32_t frame = (int32_t)self->frame_id1;
            if (facing_ok && (frame == 110 || frame > 234) && dz < 7 && param_4 != 0xe) {
                self->click_left = 0;
                self->click_right = 0;
                self->holding_left = 0;
                self->holding_right = 0;
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
void FUN_004094b0(int obj_id, int mode)
{
    global_t *global = (global_t *)in_ECX;
    if (!global || obj_id < 0 || obj_id >= MAX_OBJECTS || !global->is_object_exists[obj_id]) {
        return;
    }
    object_t *self = global->objects[obj_id];
    if (!self || !self->file) return;

    // Shift previous clicks into holding states and clear single-frame clicks
    self->holding_up     = self->click_up;
    self->holding_down   = self->click_down;
    self->holding_left   = self->click_left;
    self->holding_right  = self->click_right;
    self->holding_attack = self->click_attack;
    self->holding_jump   = self->click_jump;
    self->holding_defend = self->click_defend;
    self->click_defend   = 0;
    self->click_jump     = 0;
    self->click_attack   = 0;
    self->click_down     = 0;
    self->click_up       = 0;
    self->click_left     = 0;
    self->click_right    = 0;

    // Stage "GO!" advance scroll override
    if (mode == 1 && DAT_00450bac == 1) {
        self->click_right = 1;
        self->holding_right = 0;
        return;
    }

    // Waypoint navigation when ai_target_x > -1000
    if (self->ai_target_x > -1000) {
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
        if (FUN_004034e0(self->ai_target_z - self->z) <= 90 &&
            FUN_004034e0(self->ai_target_x - self->x) < 91) {
            self->ai_target_x = -1000;
            self->ai_target_z = -1000;
        }
        return;
    }

    // Difficulty scaling globals (CRAZY! = 0, Difficult = 1, Normal = 2, Easy = 3)
    DAT_0044f60c = (DAT_00450c2c == 1 || DAT_00450c30 < 0) ? 0 : DAT_00450c30;
    DAT_0044f61c = DAT_0044f60c * 3;
    DAT_0044f618 = DAT_0044f60c * 5;
    DAT_0044f614 = DAT_0044f60c * 15;
    DAT_0044f610 = DAT_0044f60c * 20;

    // Acquire nearest living enemy character
    int32_t best_dist = 10000;
    int32_t target_id = -1;
    for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (i == obj_id || !global->is_object_exists[i] || !global->objects[i] || !global->objects[i]->file) {
            continue;
        }
        object_t *cand = global->objects[i];
        if (cand->file->type != TYPE_CHARACTER) continue;
        if (cand->team == self->team && self->team != 0) continue;
        if (mode == 1 && self->team != 5 && cand->team != 5) continue;
        if (cand->hp <= 0) continue;
        if (cand->file->frames[cand->frame_id1].state == STATE_LYING ||
            FUN_004034e0((int)cand->invincible_time) >= 3) {
            continue;
        }
        int32_t d = FUN_004034e0(cand->z - self->z) + FUN_004034e0(cand->x - self->x);
        if (d < best_dist) {
            best_dist = d;
            target_id = i;
        }
    }

    self->enemy = target_id;
    if (target_id < 0 || target_id >= MAX_OBJECTS || !global->objects[target_id]) {
        return;
    }

    object_t *target = global->objects[target_id];
    int32_t self_state = (int32_t)self->file->frames[self->frame_id1].state;
    int32_t target_state = (int32_t)target->file->frames[target->frame_id1].state;
    int32_t dx = FUN_004034e0(target->x - self->x);
    int32_t dz = FUN_004034e0(target->z - self->z);
    int32_t z_close = (dz < 15) ? 1 : 0;

    if (FUN_00403a40(target_id, obj_id, self_state, target_state, 0, best_dist, z_close) != 0) {
        return;
    }
    FUN_004034f0(target_id, obj_id, 0, self_state, 0, 0, 0);
    if (self->weapon_type > 0 &&
        FUN_00408cb0(target_id, obj_id, self_state, target_state, z_close, 0) == 0) {
        return;
    }

    // Approach target in X and Z
    if (self->x + 60 < target->x) {
        self->click_right = 1;
        if (FUN_00417170(0x1c, DAT_0044f610 + 35) == 0) self->holding_right = 0;
    } else if (target->x < self->x - 60) {
        self->click_left = 1;
        if (FUN_00417170(0x1d, DAT_0044f610 + 35) == 0) self->holding_left = 0;
    }
    if (self->z + 3 < target->z) {
        self->click_down = 1;
    } else if (target->z < self->z - 3) {
        self->click_up = 1;
    }

    // Defend against incoming attacks
    if ((target_state == STATE_ATTACKING || target_state / 100 == 3) &&
        dz < 9 && FUN_00417170(0x1e, DAT_0044f60c * 7 + 10) == 0) {
        self->click_defend = 1;
    }

    // Melee attack when in range
    if (dx < 80 && dz < 5 && target_state != STATE_LYING &&
        FUN_00417170(0x21, DAT_0044f61c + 3) == 0) {
        self->click_attack = 1;
    }
}

void func_00406ba0_ai_process(void *world_ptr, uint32_t object_id)
{
    void *prev_ecx = in_ECX;
    in_ECX = world_ptr;
    FUN_004094b0((int)object_id, 0);
    in_ECX = prev_ecx;
}


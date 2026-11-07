#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Addresses:
 *   0x00417F80: FUN_00417f80 (wpoint carried weapon sync, Milk/Beer drinking & weapon throw)
 *   0x00408CB0: FUN_00408cb0 (AI weapon pickup / throw / drink decision)
 */

static void lf2_wpoint_sync_single(global_t *global, int32_t weapon_id)
{
    if (!global || weapon_id < 0 || weapon_id >= MAX_OBJECTS || !global->is_object_exists[weapon_id]) {
        return;
    }
    object_t *weapon = global->objects[weapon_id];
    if (!weapon || !weapon->file || weapon->weapon_type >= 0) {
        return;
    }

    int32_t holder_id = weapon->holder_id;
    if (holder_id < 0 || holder_id >= MAX_OBJECTS ||
        !global->is_object_exists[holder_id] ||
        !global->objects[holder_id] ||
        !global->objects[holder_id]->file ||
        global->objects[holder_id]->weapon_id != weapon_id) {
        weapon->weapon_type = 0;
        return;
    }

    object_t *holder = global->objects[holder_id];
    frame_t *holder_frame = &holder->file->frames[holder->frame_id1];

    // 1. Drinking Milk (id 122) or Beer (id 123) in STATE_DRINKING (17)
    if (holder_frame->state == STATE_DRINKING) {
        if (weapon->file->id == ID_MILK_DAT && weapon->hp > 0) {
            weapon->hp -= 1;
            if (weapon->hp % 5 == 0) {
                holder->dark_hp += 2;
                holder->hp += 4;
                if (holder->dark_hp > holder->max_hp) holder->dark_hp = holder->max_hp;
                if (holder->hp > holder->dark_hp) holder->hp = holder->dark_hp;
            }
            if (weapon->hp % 6 == 0) {
                holder->mp += 5;
                if (holder->mp > 500) holder->mp = 500;
            }
            if (weapon->hp < 1) {
                holder->weapon_type = 0;
                weapon->weapon_type = 0;
                holder->weapon_id = 0;
                weapon->holder_id = 0;
                weapon->frame_id1 = 0;
                weapon->y_velocity = -8.0;
                weapon->x_velocity = (double)(FUN_00417170(0x88, 7) - 3);
                holder->frame_id1 = 0;
                weapon->weapon_hp = 0;
                return;
            }
        }
        if (weapon->file->id == ID_BEER_DAT && weapon->hp > 0) {
            weapon->hp -= 2;
            holder->mp += 3;
            if (holder->mp > 500) holder->mp = 500;
            if (weapon->clone > -1 && weapon->mp > 150) {
                holder->mp = 150;
            }
            if (weapon->hp < 1) {
                holder->weapon_type = 0;
                weapon->weapon_type = 0;
                holder->weapon_id = 0;
                weapon->holder_id = 0;
                weapon->frame_id1 = 0;
                weapon->y_velocity = -8.0;
                weapon->x_velocity = (double)(FUN_00417170(0x89, 7) - 3);
                holder->frame_id1 = 0;
                weapon->weapon_hp = 0;
                return;
            }
        }
    }

    // 2. Synchronize weapon frame and coordinates with holder's wpoint
    wpoint_t *wp = &holder_frame->wpoint;
    weapon->frame_id1 = wp->weaponact;
    weapon->facing = holder->facing;
    weapon->shaking = holder->shaking;

    int32_t world_wx = (holder->facing == FACING_RIGHT)
        ? (holder->x - holder_frame->centerx + wp->x)
        : (holder->x + holder_frame->centerx - wp->x);
    int32_t world_wy = holder->y - holder_frame->centery + wp->y;

    frame_t *w_frame = &weapon->file->frames[weapon->frame_id1];
    if (weapon->facing == FACING_RIGHT) {
        weapon->x = (w_frame->centerx - w_frame->wpoint.x) + world_wx;
        weapon->y = (w_frame->centery - w_frame->wpoint.y) + world_wy;
    } else {
        weapon->x = (w_frame->wpoint.x - w_frame->centerx) + world_wx;
        weapon->y = (w_frame->centery - w_frame->wpoint.y) + world_wy;
    }

    weapon->z = holder->z;
    if (wp->cover == 0) {
        weapon->z += 1;
        weapon->y -= 1;
    } else {
        weapon->z -= 1;
        weapon->y += 1;
    }

    weapon->z_position = (double)weapon->z;
    weapon->x_position = (double)weapon->x;
    weapon->y_position = (double)weapon->y;

    // 3. Drop weapon if holder is falling (STATE_FALLING = 12) or caught (STATE_CAUGHT = 10)
    if (holder_frame->state == STATE_FALLING || holder_frame->state == STATE_CAUGHT) {
        holder->weapon_type = 0;
        weapon->weapon_type = 0;
        weapon->frame_id1 = (uint32_t)FUN_00417170(0x8a, 16);
        if (holder->attacks == 1) {
            weapon->y_velocity = holder->y_accl;
            weapon->x_velocity = holder->pic_x_gain / 3.0;
        } else {
            weapon->y_velocity = holder->y_velocity;
            weapon->x_velocity = holder->x_velocity / 3.0;
        }
    }

    // 4. Weapon throw impulse when wpoint->dvx != 0
    if (wp->dvx != 0) {
        uint32_t wtype = weapon->file->type;
        if (wtype == TYPE_LIGHT_WEAPON || wtype == TYPE_THROW_WEAPON || wtype == TYPE_DRINK) {
            weapon->weapon_throw_injury = holder_id;
            weapon->frame_id1 = 40;
            weapon->x_velocity = (holder->facing == FACING_RIGHT) ? (double)wp->dvx : (double)(-wp->dvx);
            weapon->y_velocity = (double)wp->dvy;
            holder->weapon_type = 0;
            weapon->weapon_type = 0;
            if (holder->click_up != 0 && holder->click_down == 0) {
                weapon->z_velocity = (double)(-wp->dvz);
            } else if (holder->click_up == 0 && holder->click_down != 0) {
                weapon->z_velocity = (double)wp->dvz;
            }
        }
        if (wp->dvx != 0 && wtype == TYPE_HEAVY_WEAPON) {
            weapon->frame_id1 = (uint32_t)FUN_00417170(0x8b, 6);
            weapon->x_velocity = (holder->facing == FACING_RIGHT) ? (double)wp->dvx : (double)(-wp->dvx);
            weapon->y_velocity = (double)wp->dvy;
            holder->weapon_type = 0;
            weapon->weapon_type = 0;
            if (holder->click_up != 0 && holder->click_down == 0) {
                weapon->z_velocity = (double)(-wp->dvz);
            } else if (holder->click_up == 0 && holder->click_down != 0) {
                weapon->z_velocity = (double)wp->dvz;
            }
        }
    }

    // 5. Explicit weapon drop (wpoint->kind == 3)
    if (wp->kind == 3) {
        weapon->weapon_type = 0;
        holder->weapon_type = 0;
        weapon->frame_id1 = (uint32_t)FUN_00417170(0x8c, 6);
        weapon->x_velocity = (double)(FUN_00417170(0x8d, 7) - 3);
        weapon->y_velocity = (double)(-FUN_00417170(0x8e, 4));
        weapon->z_velocity = (double)(FUN_00417170(0x8f, 5) - 2) / 3.0;
    }
}

void lf2_weapon_sync(global_t *global, uint32_t char_id)
{
    if (!global || char_id >= MAX_OBJECTS || !global->is_object_exists[char_id]) return;
    object_t *obj = global->objects[char_id];
    if (!obj) return;
    if (obj->weapon_type < 0) {
        lf2_wpoint_sync_single(global, (int32_t)char_id);
    } else if (obj->weapon_type > 0 && obj->weapon_id >= 0 && obj->weapon_id < MAX_OBJECTS) {
        lf2_wpoint_sync_single(global, obj->weapon_id);
    }
}

void FUN_00417f80(void)
{
    global_t *global = (global_t *)in_ECX;
    if (!global) return;
    for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] && global->objects[i] && global->objects[i]->file &&
            global->objects[i]->file->type == TYPE_CHARACTER) {
            global->objects[i]->z = (int32_t)global->objects[i]->z_position;
        }
    }
    for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
        lf2_wpoint_sync_single(global, i);
    }
}

// AI held-weapon decision helper (0x00408CB0)
int FUN_00408cb0(int target_id, int self_id, int self_state, int target_state, int z_close, int incoming_proj)
{
    global_t *global = (global_t *)in_ECX;
    if (!global || target_id < 0 || target_id >= MAX_OBJECTS || self_id < 0 || self_id >= MAX_OBJECTS) {
        return 0;
    }
    if (FUN_00417170(0x28, DAT_0044f61c + 1) > 0) {
        return 0;
    }

    object_t *self = global->objects[self_id];
    object_t *target = global->objects[target_id];
    if (!self || !target || self->weapon_id < 0 || self->weapon_id >= MAX_OBJECTS) return 0;
    object_t *weapon = global->objects[self->weapon_id];
    if (!weapon || !weapon->file) return 0;

    int32_t wid = (int32_t)weapon->file->id;
    bool ally_in_line = false;
    for (int32_t i = 0; i < 20; ++i) {
        if (i != self_id && global->is_object_exists[i] && global->objects[i] && global->objects[i]->file) {
            object_t *ally = global->objects[i];
            if (ally->team != 0 && target->team == self->team && ally->hp > 0 &&
                ally->file->frames[ally->frame_id1].state != STATE_LYING &&
                FUN_004034e0((int)ally->invincible_time) < 3 &&
                FUN_004034e0(ally->z - self->z) < 15) {
                if ((self->x <= ally->x && ally->x <= target->x) ||
                    (target->x <= ally->x && ally->x <= self->x)) {
                    ally_in_line = true;
                }
            }
        }
    }

    if (self_state == STATE_RUNNING && FUN_00417170(0x29, DAT_0044f61c + 5) == 0) {
        if (ally_in_line) self->click_jump = 1;
        else self->click_attack = 1;
    }

    if (wid == ID_STICK_DAT || wid == ID_HOE_DAT || wid == ID_KNIFE_DAT ||
        wid == ID_BASEBALL_DAT || wid == ID_BOOMERANG_DAT) {
        int32_t dx = FUN_004034e0(target->x - self->x);
        int32_t dz = FUN_004034e0(target->z - self->z);
        if (dx < 115 && dz < 6 && FUN_00417170(0x2a, DAT_0044f61c + 3) == 0 && target_state != STATE_LYING) {
            self->click_attack = 1;
        }
        if (wid == ID_BOOMERANG_DAT && FUN_00417170(0x2b, DAT_0044f614 + 30) == 0) {
            self->click_attack = 1;
        }
        if (FUN_00417170(0x2c, DAT_0044f61c + 5) == 0) {
            if (dx < 600 && dz < 20) {
                if (self->x < target->x && DAT_0044f608 == 0) {
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

    if ((wid == ID_STONE_DAT || wid == ID_WOODEN_BOX_DAT) && !ally_in_line) {
        int32_t dx = FUN_004034e0(target->x - self->x);
        int32_t dz = FUN_004034e0(target->z - self->z);
        if (dx < 300 && dz < 6 && FUN_00417170(0x2d, DAT_0044f618 + 7) == 0 && target_state != STATE_LYING) {
            self->click_attack = 1;
        }
    }

    if (wid != ID_MILK_DAT && wid != ID_BEER_DAT) {
        return 1;
    }

    self->click_defend = 0;
    self->click_jump = 0;
    self->click_attack = 0;
    self->click_down = 0;
    self->click_up = 0;
    self->click_left = 0;
    self->click_right = 0;

    if (self_state == STATE_DRINKING && z_close == 1 && incoming_proj == 0 && self->invincible_time != 0) {
        self->click_defend = 1;
        return 0;
    }
    if (FUN_00417170(0x34, 5) == 0) {
        self->click_attack = 1;
    }
    return 0;
}

void FUN_00408ce0(void)
{
    FUN_00417f80();
}

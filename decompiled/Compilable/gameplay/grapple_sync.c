#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Addresses:
 *   0x004187B0: FUN_004187b0 (cpoint catch sync & injury application)
 *   0x00418C30: FUN_00418c30 (cpoint chain combos, Rudolf transform & throw impulse)
 *   0x004064D0: FUN_004064d0 (Firen + Freeze -> Firzen fusion & defusion)
 */

static void lf2_cpoint_catch_sync_single(global_t *global, int32_t catcher_id)
{
    if (!global || catcher_id < 0 || catcher_id >= MAX_OBJECTS || !global->is_object_exists[catcher_id]) {
        return;
    }
    object_t *catcher = global->objects[catcher_id];
    if (!catcher || !catcher->file) return;

    frame_t *catcher_frame = &catcher->file->frames[catcher->frame_id1];
    cpoint_t *cp = &catcher_frame->cpoint;
    if (cp->kind != 1 || catcher_frame->state != STATE_CATCHING) {
        return;
    }

    int32_t victim_id = catcher->cpoint_catcher;
    if (victim_id < 0 || victim_id >= MAX_OBJECTS || !global->is_object_exists[victim_id]) {
        return;
    }
    object_t *victim = global->objects[victim_id];
    if (!victim || !victim->file) return;

    frame_t *victim_frame = &victim->file->frames[victim->frame_id1];
    if (victim->cpoint_caught != catcher_id || victim_frame->cpoint.kind != 2) {
        return;
    }

    if ((victim->shaking == 0 && cp->hurtable == 1) || cp->hurtable == 0) {
        victim->frame_id1 = (uint32_t)cp->vaction;
    }
    if ((int32_t)victim->frame_id1 < 0) {
        victim->facing = 1 - victim->facing;
        victim->frame_id1 = (uint32_t)(-(int32_t)victim->frame_id1);
    }

    int32_t dmg = cp->injury;
    if (dmg != 0 && catcher->cpoint_hurt == 0) {
        if (dmg < 1) {
            victim->hp += dmg;
            victim->dark_hp += dmg / 3;
            catcher->cpoint_hurt = 1;
        } else {
            if (victim->armor_multiplier > 0) {
                dmg = (dmg * 100) / victim->armor_multiplier;
            }
            if (victim->hp > 0 && victim->hp <= dmg && victim->clone == -1) {
                if (catcher->owner >= 0 && catcher->owner < MAX_OBJECTS && global->objects[catcher->owner]) {
                    global->objects[catcher->owner]->kills++;
                }
            }
            victim->hp -= dmg;
            victim->dark_hp -= dmg / 3;
            catcher->cpoint_hurt = 1;
            catcher->shaking = 2;
            victim->shaking = -3;
            victim->hp_lost += dmg;
            if (catcher->owner >= 0 && catcher->owner < MAX_OBJECTS && global->objects[catcher->owner]) {
                global->objects[catcher->owner]->total_attack += dmg;
            }
        }
    }

    int32_t world_cx = (catcher->facing == FACING_RIGHT)
        ? (catcher->x - catcher_frame->centerx + cp->x)
        : (catcher->x + catcher_frame->centerx - cp->x);
    int32_t world_cy = catcher->y - catcher_frame->centery + cp->y;

    frame_t *v_act_frame = &victim->file->frames[cp->vaction];
    frame_t *v_cur_frame = &victim->file->frames[victim->frame_id1];
    if (victim->facing == FACING_RIGHT) {
        victim->x = (v_cur_frame->centerx - v_act_frame->cpoint.x) + world_cx;
        victim->y = (v_cur_frame->centery - v_act_frame->cpoint.y) + world_cy;
    } else {
        victim->x = (v_act_frame->cpoint.x - v_cur_frame->centerx) + world_cx;
        victim->y = (v_cur_frame->centery - v_act_frame->cpoint.y) + world_cy;
    }

    victim->z = catcher->z;
    if (cp->cover % 10 == 0) {
        victim->z -= 1;
        victim->y += 1;
    } else {
        victim->z += 1;
        victim->y -= 1;
    }

    int32_t face_mode = cp->cover / 10;
    if (face_mode == 1) {
        victim->facing = catcher->facing;
    } else if (face_mode == 2) {
        victim->facing = 1 - catcher->facing;
    }

    victim->z_position = (double)victim->z;
    victim->x_position = (double)victim->x;
    victim->y_position = (double)victim->y;
}

static void lf2_cpoint_chain_throw_single(global_t *global, int32_t obj_id)
{
    if (!global || obj_id < 0 || obj_id >= MAX_OBJECTS || !global->is_object_exists[obj_id]) {
        return;
    }
    object_t *obj = global->objects[obj_id];
    if (!obj || !obj->file) return;

    frame_t *f4 = &obj->file->frames[obj->frame_id4];
    cpoint_t *cp = &f4->cpoint;

    if (cp->kind == 1 && obj->shaking >= 0) {
        int32_t victim_id = obj->cpoint_catcher;
        if (victim_id >= 0 && victim_id < MAX_OBJECTS &&
            global->objects[victim_id] &&
            global->objects[victim_id]->cpoint_caught == obj_id &&
            global->objects[victim_id]->file &&
            global->objects[victim_id]->file->frames[global->objects[victim_id]->frame_id4].cpoint.kind == 2) {
            object_t *victim = global->objects[victim_id];
            if (cp->decrease > 0) {
                obj->cpoint_hurtable -= cp->decrease;
            }
            if (cp->decrease < 0) {
                obj->cpoint_hurtable += cp->decrease;
                if (obj->cpoint_hurtable < 0) {
                    obj->frame_id1 = 0;
                    victim->frame_id1 = 0;
                    obj->attacks = 1;
                    victim->attacks = 1;
                    victim->pic_x_gain = (victim->x < obj->x) ? -4.0 : 4.0;
                    victim->y_accl = -3.0;
                    victim->frame_id1 = 181;
                    goto check_throw;
                }
            }

            if (obj->click_attack != 0 && (int8_t)obj->key_state[2] > 0 && cp->aaction != 0 &&
                ((obj->click_left == 0 && obj->click_right == 0) || cp->taction == 0)) {
                obj->frame_id1 = (uint32_t)cp->aaction;
                if ((int32_t)obj->frame_id1 < 0) {
                    obj->facing = 1 - obj->facing;
                    obj->frame_id1 = (uint32_t)(-(int32_t)obj->frame_id1);
                }
                victim->frame_id1 = (uint32_t)obj->file->frames[obj->frame_id1].cpoint.vaction;
                victim->cpoint_hurt = 0;
                obj->cpoint_hurt = 0;
            }
            if (obj->click_attack != 0 && (int8_t)obj->key_state[2] > 0 &&
                (obj->click_left != 0 || obj->click_right != 0 || obj->click_up != 0 || obj->click_down != 0) &&
                cp->taction != 0) {
                obj->frame_id1 = (uint32_t)cp->taction;
                if ((int32_t)obj->frame_id1 < 0) {
                    obj->facing = 1 - obj->facing;
                    obj->frame_id1 = (uint32_t)(-(int32_t)obj->frame_id1);
                }
                victim->frame_id1 = (uint32_t)obj->file->frames[obj->frame_id1].cpoint.vaction;
                victim->cpoint_hurt = 0;
                obj->cpoint_hurt = 0;
            }
            if (obj->click_jump != 0 && (int8_t)obj->key_state[3] > 0 && cp->jaction != 0) {
                obj->frame_id1 = (uint32_t)cp->jaction;
                if ((int32_t)obj->frame_id1 < 0) {
                    obj->facing = 1 - obj->facing;
                    obj->frame_id1 = (uint32_t)(-(int32_t)obj->frame_id1);
                }
                victim->frame_id1 = (uint32_t)obj->file->frames[obj->frame_id1].cpoint.vaction;
                victim->cpoint_hurt = 0;
                obj->cpoint_hurt = 0;
            }
        } else {
            obj->frame_id1 = 0;
        }

check_throw:
        if (cp->throwvx != 0 && victim_id >= 0 && victim_id < MAX_OBJECTS && global->objects[victim_id]) {
            object_t *victim = global->objects[victim_id];
            if (cp->throwinjury < 1) {
                if (cp->throwinjury == -1 && victim->file) {
                    // Rudolf transform (throwinjury == -1)
                    obj->uid = (int32_t)obj->file->id;
                    obj->_unknown39 = (int32_t)victim->file->id;
                    obj->file = victim->file;
                    obj->frame_id1 = 0;
                    for (int i = 0; i < MAX_OBJECTS; ++i) {
                        if (global->is_object_exists[i] && global->objects[i] &&
                            global->objects[i]->clone == obj_id) {
                            global->objects[i]->file = victim->file;
                        }
                    }
                }
            } else {
                victim->thrown_injury = cp->throwinjury;
            }

            frame_t *f1 = &obj->file->frames[obj->frame_id1];
            victim->y = (obj->y - f1->centery) + cp->y;
            victim->y_position = (double)victim->y;
            if (obj->facing == FACING_RIGHT) {
                victim->x = (obj->x - f1->centerx) + cp->x;
            } else {
                victim->x = (f1->centerx - cp->x) + obj->x;
            }
            victim->x_position = (double)victim->x;

            obj->frame_id1 = (uint32_t)f1->next;
            obj->frame_id4 = obj->frame_id1;
            obj->cpoint_hurt = 0;

            victim->x_velocity = (obj->facing == FACING_RIGHT) ? (double)cp->throwvx : (double)(-cp->throwvx);
            victim->frame_id1 = (uint32_t)cp->vaction;
            victim->frame_id4 = victim->frame_id1;
            victim->y_velocity = (double)cp->throwvy;

            if (obj->click_up != 0 && obj->click_down == 0) {
                victim->z_velocity = (double)(-cp->throwvz);
            } else if (obj->click_up == 0 && obj->click_down != 0) {
                victim->z_velocity = (double)cp->throwvz;
            }
        }

        if (cp->dircontrol == 1 && obj->cpoint_hurt == 2) {
            if (obj->click_right != 0 && obj->click_left == 0) obj->facing = FACING_RIGHT;
            if (obj->click_right == 0 && obj->click_left != 0) obj->facing = FACING_LEFT;
        }
        if (cp->dircontrol == -1 && obj->cpoint_hurt == 2) {
            if (obj->click_right != 0 && obj->click_left == 0) obj->facing = FACING_LEFT;
            if (obj->click_right == 0 && obj->click_left != 0) obj->facing = FACING_RIGHT;
        }
    } else if (obj->file->frames[obj->frame_id1].cpoint.kind == 2) {
        int32_t c_id = obj->cpoint_caught;
        if (c_id < 0 || c_id >= MAX_OBJECTS || !global->objects[c_id] ||
            global->objects[c_id]->cpoint_catcher != obj_id ||
            !global->objects[c_id]->file ||
            global->objects[c_id]->file->frames[global->objects[c_id]->frame_id1].cpoint.kind != 1) {
            obj->frame_id1 = 212;
            obj->y_velocity = -3.0;
            if (obj->y_position > -2.0) {
                obj->y_position = -2.0;
            }
        }
    }
}

void lf2_grapple_sync(global_t *global, uint32_t catcher_id)
{
    lf2_cpoint_catch_sync_single(global, (int32_t)catcher_id);
    lf2_cpoint_chain_throw_single(global, (int32_t)catcher_id);
}

void FUN_004187b0(void)
{
    global_t *global = (global_t *)in_ECX;
    if (!global) return;
    for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
        lf2_cpoint_catch_sync_single(global, i);
    }
}

void FUN_00418c30(void)
{
    global_t *global = (global_t *)in_ECX;
    if (!global) return;
    for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
        lf2_cpoint_chain_throw_single(global, i);
    }
}

// Firen (id 7) + Freeze (id 8) -> Firzen (id 51) fusion & defusion (0x004064D0)
void FUN_004064d0(void)
{
    global_t *global = (global_t *)in_ECX;
    if (!global) return;

    for (int32_t i = 0; i < 20; ++i) {
        object_t *obj = global->objects[i];
        if (!obj) continue;
        if (obj->firen_counter > 0) {
            obj->firen_counter--;
        }
        if (global->is_object_exists[i] != 1 || !obj->file) continue;

        uint32_t fid = obj->file->id;
        if ((fid == ID_FIREN_DAT || fid == ID_FREEZE_DAT) &&
            obj->hp > 0 &&
            obj->file->frames[obj->frame_id1].state == STATE_RUNNING &&
            obj->firen_counter == 0 &&
            (obj->hp < 177 || DAT_00458428 == 1)) {
            for (int32_t j = 0; j < 20; ++j) {
                if (global->is_object_exists[j] != 1) continue;
                object_t *partner = global->objects[j];
                if (!partner || !partner->file) continue;
                if (partner->file->id == (15 - obj->file->id) &&
                    partner->hp > 0 &&
                    obj->team == partner->team &&
                    partner->firen_counter == 0 &&
                    (partner->hp < 177 || DAT_00458428 == 1) &&
                    partner->frame_id1 < MAX_FRAMES) {
                    uint32_t p_state = partner->file->frames[partner->frame_id1].state;
                    if (p_state == STATE_RUNNING || (p_state != STATE_LYING && partner->y == 0 && j > 9)) {
                        int32_t dx = FUN_004034e0(obj->x - partner->x);
                        int32_t dz = FUN_004034e0(obj->z - partner->z);
                        if (dx < 50 && dz < 8 && (partner->x < obj->x || j > 9) && i < 10) {
                            file_t *firzen_file = NULL;
                            for (int32_t k = 0; k < MAX_FILES; ++k) {
                                if (global->files[k] && global->files[k]->id == ID_FIRZEN_DAT) {
                                    firzen_file = global->files[k];
                                    break;
                                }
                            }
                            if (firzen_file) {
                                obj->hp += partner->hp;
                                obj->dark_hp += partner->dark_hp;
                                if (obj->dark_hp > obj->max_hp) obj->dark_hp = obj->max_hp;
                                if (obj->hp > obj->dark_hp) obj->hp = obj->dark_hp;
                                obj->frame_id1 = 290;
                                obj->_unknown34_rest[0] = 1;
                                obj->x_velocity = 0.0;
                                partner->y_velocity = 0.0;
                                obj->x = (partner->x + obj->x) / 2;
                                obj->z = (partner->z + obj->z) / 2;
                                obj->x_position = (double)obj->x;
                                obj->z_position = (double)obj->z;
                                obj->_unknown34_rest[1] = j;
                                obj->firen_counter = 4500;
                                obj->_unknown34_rest[2] = (int32_t)obj->file->id;
                                obj->_unknown34_rest[3] = (int32_t)partner->file->id;
                                obj->file = firzen_file;
                                obj->mp = 500;
                                global->is_object_exists[j] = 0;
                            }
                        }
                    }
                }
            }
        } else if (fid == ID_FIRZEN_DAT &&
                   obj->_unknown34_rest[0] == 1 &&
                   (obj->frame_id1 < 9 || obj->frame_id1 > 260) &&
                   obj->firen_counter < 1) {
            int32_t p_idx = obj->_unknown34_rest[1];
            obj->_unknown34_rest[0] = -1;
            obj->firen_counter = 900;
            for (int32_t k = 0; k < MAX_FILES; ++k) {
                file_t *f = global->files[k];
                if (!f) continue;
                if ((int32_t)f->id == obj->_unknown34_rest[2]) {
                    obj->file = f;
                } else if ((int32_t)f->id == obj->_unknown34_rest[3] &&
                           p_idx >= 0 && p_idx < MAX_OBJECTS && global->objects[p_idx]) {
                    object_t *partner = global->objects[p_idx];
                    lf2_object_init(partner);
                    partner->file = f;
                    partner->weapon_hp = f->weapon_hp;
                    global->is_object_exists[p_idx] = 1;
                }
            }
            if (p_idx >= 0 && p_idx < MAX_OBJECTS && global->objects[p_idx]) {
                object_t *partner = global->objects[p_idx];
                partner->hp = obj->hp / 2;
                partner->dark_hp = obj->dark_hp / 2;
                obj->hp /= 2;
                obj->dark_hp /= 2;
                partner->x = obj->x;
                partner->z = obj->z;
                partner->y = 0;
                partner->x_position = (double)partner->x;
                partner->z_position = (double)partner->z;
                partner->y_position = 0.0;
                obj->x_velocity = 0.0;
                partner->x_velocity = 0.0;
                partner->facing = 1 - obj->facing;
                obj->frame_id1 = 112;
                partner->frame_id1 = 112;
                obj->mp = 0;
                partner->mp = 0;
                partner->team = obj->team;
            }
        }
    }
}

void FUN_004068b0(void)
{
    FUN_004064d0();
}

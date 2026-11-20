#include "gameplay/grapple.h"
#include "gameplay/entity.h"
#include <cstdlib>
#include <cstring>

namespace lf2 {

namespace {

object_t* resolve_catcher_owner(global_t* world, object_t* catcher)
{
    if (catcher->owner >= 0 && catcher->owner < static_cast<int32_t>(MAX_OBJECTS) &&
        world->objects[catcher->owner]) {
        return world->objects[catcher->owner];
    }
    return catcher;
}

void cpoint_sync_single(global_t* world, int32_t catcher_id)
{
    if (!world || catcher_id < 0 || catcher_id >= static_cast<int32_t>(MAX_OBJECTS) ||
        !world->is_object_exists[catcher_id]) {
        return;
    }

    object_t* catcher = world->objects[catcher_id];
    if (!catcher || !catcher->file || catcher->frame_id1 >= MAX_FRAMES) {
        return;
    }

    const frame_t* catcher_frame = &catcher->file->frames[catcher->frame_id1];
    const cpoint_t* cp = &catcher_frame->cpoint;
    if (cp->kind != 1 || catcher_frame->state != STATE_CATCHING) {
        return;
    }

    int32_t victim_id = catcher->cpoint_catcher;
    if (victim_id < 0 || victim_id >= static_cast<int32_t>(MAX_OBJECTS) ||
        !world->is_object_exists[victim_id]) {
        return;
    }
    object_t* victim = world->objects[victim_id];
    if (!victim || !victim->file || victim->frame_id1 >= MAX_FRAMES) {
        return;
    }

    const frame_t* victim_frame = &victim->file->frames[victim->frame_id1];
    if (victim->cpoint_caught != catcher_id || victim_frame->cpoint.kind != 2) {
        return;
    }

    if ((victim->shaking == 0 && cp->hurtable == 1) || cp->hurtable == 0) {
        victim->frame_id1 = static_cast<uint32_t>(cp->vaction);
    }
    if (static_cast<int32_t>(victim->frame_id1) < 0) {
        victim->facing = static_cast<uint8_t>(1U - victim->facing);
        victim->frame_id1 = static_cast<uint32_t>(-static_cast<int32_t>(victim->frame_id1));
    }

    int32_t dmg = cp->injury;
    if (dmg != 0 && catcher->wait_counter == 0) {
        if (dmg < 1) {
            victim->hp += dmg;
            victim->dark_hp += dmg / 3;
            catcher->wait_counter = 1;
        } else {
            if (victim->armor_multiplier > 0) {
                dmg = (dmg * 100) / static_cast<int32_t>(victim->armor_multiplier);
            }
            object_t* owner_obj = resolve_catcher_owner(world, catcher);
            if (victim->hp > 0 && victim->hp <= dmg && victim->clone == -1) {
                owner_obj->kills++;
            }
            victim->hp -= dmg;
            victim->dark_hp -= dmg / 3;
            catcher->wait_counter = 1;
            catcher->shaking = 2;
            victim->shaking = -3;
            victim->hp_lost += static_cast<uint32_t>(dmg);
            owner_obj->total_attack += static_cast<uint32_t>(dmg);
        }
    }

    int32_t world_cx = (catcher->facing == FACING_RIGHT)
        ? (catcher->x - catcher_frame->centerx + cp->x)
        : (catcher->x + catcher_frame->centerx - cp->x);
    int32_t world_cy = catcher->y - catcher_frame->centery + cp->y;

    int32_t vact_idx = (cp->vaction < 0) ? -cp->vaction : cp->vaction;
    if (vact_idx < 0 || vact_idx >= static_cast<int32_t>(MAX_FRAMES) ||
        victim->frame_id1 >= MAX_FRAMES) {
        return;
    }

    const frame_t* v_act_frame = &victim->file->frames[vact_idx];
    const frame_t* v_cur_frame = &victim->file->frames[victim->frame_id1];
    if (victim->facing == FACING_RIGHT) {
        victim->x = (v_cur_frame->centerx - v_act_frame->cpoint.x) + world_cx;
    } else {
        victim->x = (v_act_frame->cpoint.x - v_cur_frame->centerx) + world_cx;
    }
    victim->y = (v_cur_frame->centery - v_act_frame->cpoint.y) + world_cy;

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
        victim->facing = static_cast<uint8_t>(1U - catcher->facing);
    }

    victim->z_position = static_cast<double>(victim->z);
    victim->x_position = static_cast<double>(victim->x);
    victim->y_position = static_cast<double>(victim->y);
}

void cpoint_chain_single(global_t* world, int32_t obj_id)
{
    if (!world || obj_id < 0 || obj_id >= static_cast<int32_t>(MAX_OBJECTS) ||
        !world->is_object_exists[obj_id]) {
        return;
    }

    object_t* obj = world->objects[obj_id];
    if (!obj || !obj->file || obj->frame_id4 >= MAX_FRAMES || obj->frame_id1 >= MAX_FRAMES) {
        return;
    }

    const frame_t* f4 = &obj->file->frames[obj->frame_id4];
    const cpoint_t* cp = &f4->cpoint;

    if (cp->kind == 1 && obj->shaking >= 0) {
        int32_t victim_id = obj->cpoint_catcher;
        bool valid_pair = (victim_id >= 0 && victim_id < static_cast<int32_t>(MAX_OBJECTS) &&
            world->is_object_exists[victim_id] &&
            world->objects[victim_id] &&
            world->objects[victim_id]->cpoint_caught == obj_id &&
            world->objects[victim_id]->file &&
            world->objects[victim_id]->frame_id4 < MAX_FRAMES &&
            world->objects[victim_id]->file->frames[world->objects[victim_id]->frame_id4].cpoint.kind == 2);

        bool broke_out = false;
        if (valid_pair) {
            object_t* victim = world->objects[victim_id];
            if (cp->decrease > 0) {
                obj->cpoint_hold_timer -= cp->decrease;
            }
            if (cp->decrease < 0) {
                obj->cpoint_hold_timer += cp->decrease;
                if (obj->cpoint_hold_timer < 0) {
                    obj->frame_id1 = 0;
                    obj->attacks = 1;
                    victim->attacks = 1;
                    victim->pic_x_gain = (victim->x < obj->x) ? -4.0 : 4.0;
                    victim->y_accl = -3.0;
                    victim->frame_id1 = 181;
                    broke_out = true;
                }
            }

            if (!broke_out) {
                auto apply_chain_transition = [&](int32_t next_act) {
                    obj->frame_id1 = static_cast<uint32_t>(next_act);
                    if (static_cast<int32_t>(obj->frame_id1) < 0) {
                        obj->facing = static_cast<uint8_t>(1U - obj->facing);
                        obj->frame_id1 = static_cast<uint32_t>(-static_cast<int32_t>(obj->frame_id1));
                    }
                    if (obj->frame_id1 < MAX_FRAMES) {
                        victim->frame_id1 = static_cast<uint32_t>(
                            obj->file->frames[obj->frame_id1].cpoint.vaction);
                    }
                    victim->wait_counter = 0;
                    obj->wait_counter = 0;
                };

                if (obj->click_attack != 0 && static_cast<int8_t>(obj->attack_press) > 0 &&
                    cp->aaction != 0 &&
                    ((obj->click_left == 0 && obj->click_right == 0) || cp->taction == 0)) {
                    apply_chain_transition(cp->aaction);
                }
                if (obj->click_attack != 0 && static_cast<int8_t>(obj->attack_press) > 0 &&
                    (obj->click_left != 0 || obj->click_right != 0 ||
                     obj->click_up != 0 || obj->click_down != 0) &&
                    cp->taction != 0) {
                    apply_chain_transition(cp->taction);
                }
                if (obj->click_jump != 0 && static_cast<int8_t>(obj->jump_press) > 0 &&
                    cp->jaction != 0) {
                    apply_chain_transition(cp->jaction);
                }
            }
        } else {
            obj->frame_id1 = 0;
        }

        if (cp->throwvx != 0 && victim_id >= 0 && victim_id < static_cast<int32_t>(MAX_OBJECTS) &&
            world->is_object_exists[victim_id] && world->objects[victim_id]) {
            object_t* victim = world->objects[victim_id];
            if (cp->throwinjury < 1) {
                if (cp->throwinjury == -1 && victim->file) {
                    // Rudolf transform (throwinjury == -1)
                    obj->uid = static_cast<int32_t>(obj->file->id);
                    obj->transformed_to_id = static_cast<int32_t>(victim->file->id);
                    obj->file = victim->file;
                    obj->frame_id1 = 0;
                    for (int32_t k = 0; k < static_cast<int32_t>(MAX_OBJECTS); ++k) {
                        if (world->is_object_exists[k] && world->objects[k] &&
                            world->objects[k]->clone == obj_id) {
                            world->objects[k]->file = victim->file;
                        }
                    }
                }
            } else {
                victim->thrown_injury = static_cast<uint32_t>(cp->throwinjury);
            }

            if (obj->frame_id1 < MAX_FRAMES) {
                const frame_t* f1 = &obj->file->frames[obj->frame_id1];
                victim->y = (obj->y - f1->centery) + cp->y;
                victim->y_position = static_cast<double>(victim->y);
                if (obj->facing == FACING_RIGHT) {
                    victim->x = (obj->x - f1->centerx) + cp->x;
                } else {
                    victim->x = (f1->centerx - cp->x) + obj->x;
                }
                victim->x_position = static_cast<double>(victim->x);

                obj->frame_id1 = static_cast<uint32_t>(f1->next);
                obj->frame_id4 = obj->frame_id1;
            }
            obj->wait_counter = 0;

            victim->x_velocity = (obj->facing == FACING_RIGHT)
                ? static_cast<double>(cp->throwvx)
                : static_cast<double>(-cp->throwvx);
            victim->frame_id1 = static_cast<uint32_t>(cp->vaction);
            victim->frame_id4 = victim->frame_id1;
            victim->y_velocity = static_cast<double>(cp->throwvy);

            if (obj->click_up != 0 && obj->click_down == 0) {
                victim->z_velocity = static_cast<double>(-cp->throwvz);
            } else if (obj->click_up == 0 && obj->click_down != 0) {
                victim->z_velocity = static_cast<double>(cp->throwvz);
            }
        }

        if (cp->dircontrol == 1 && obj->wait_counter == 2) {
            if (obj->click_right != 0 && obj->click_left == 0) obj->facing = FACING_RIGHT;
            if (obj->click_right == 0 && obj->click_left != 0) obj->facing = FACING_LEFT;
        }
        if (cp->dircontrol == -1 && obj->wait_counter == 2) {
            if (obj->click_right != 0 && obj->click_left == 0) obj->facing = FACING_LEFT;
            if (obj->click_right == 0 && obj->click_left != 0) obj->facing = FACING_RIGHT;
        }
    } else if (obj->file->frames[obj->frame_id1].cpoint.kind == 2) {
        int32_t c_id = obj->cpoint_caught;
        if (c_id < 0 || c_id >= static_cast<int32_t>(MAX_OBJECTS) ||
            !world->is_object_exists[c_id] || !world->objects[c_id] ||
            world->objects[c_id]->cpoint_catcher != obj_id ||
            !world->objects[c_id]->file ||
            world->objects[c_id]->frame_id1 >= MAX_FRAMES ||
            world->objects[c_id]->file->frames[world->objects[c_id]->frame_id1].cpoint.kind != 1) {
            obj->frame_id1 = 212;
            obj->y_velocity = -3.0;
            if (obj->y_position > -2.0) {
                obj->y_position = -2.0;
            }
        }
    }
}

} // namespace

void world_process_cpoint_chain(global_t* world)
{
    if (!world) return;
    for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
        cpoint_chain_single(world, i);
    }
}

void world_process_cpoint_sync(global_t* world)
{
    if (!world) return;
    for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
        cpoint_sync_single(world, i);
    }
}

void process_grapple_sync(global_t* world, uint32_t catcher_id)
{
    cpoint_chain_single(world, static_cast<int32_t>(catcher_id));
    cpoint_sync_single(world, static_cast<int32_t>(catcher_id));
}

void world_process_firzen_fusion(global_t* world, int32_t unlock_chars)
{
    if (!world) return;

    for (int32_t i = 0; i < 20; ++i) {
        object_t* obj = world->objects[i];
        if (!obj) continue;
        if (obj->firen_counter > 0) {
            obj->firen_counter--;
        }
        if (world->is_object_exists[i] != 1 || !obj->file) continue;

        uint32_t fid = obj->file->id;
        if ((fid == FIREN_DAT || fid == FREEZE_DAT) &&
            obj->hp > 0 &&
            obj->frame_id1 < MAX_FRAMES &&
            obj->file->frames[obj->frame_id1].state == STATE_RUNNING &&
            obj->firen_counter == 0 &&
            (obj->hp < 177 || unlock_chars == 1)) {
            for (int32_t j = 0; j < 20; ++j) {
                if (world->is_object_exists[j] != 1) continue;
                object_t* partner = world->objects[j];
                if (!partner || !partner->file) continue;
                if (partner->file->id == (15U - fid) &&
                    partner->hp > 0 &&
                    obj->team == partner->team &&
                    partner->firen_counter == 0 &&
                    (partner->hp < 177 || unlock_chars == 1) &&
                    partner->frame_id1 < MAX_FRAMES) {
                    uint32_t p_state = partner->file->frames[partner->frame_id1].state;
                    if (p_state == STATE_RUNNING ||
                        (p_state != STATE_LYING && partner->y == 0 && j > 9)) {
                        int32_t dx = std::abs(obj->x - partner->x);
                        int32_t dz = std::abs(obj->z - partner->z);
                        if (dx < 50 && dz < 8 && (partner->x < obj->x || j > 9) && i < 10) {
                            file_t* firzen_file = nullptr;
                            for (uint32_t k = 0; k < MAX_FILES; ++k) {
                                if (world->files[k] && world->files[k]->id == FIRZEN_DAT) {
                                    firzen_file = world->files[k];
                                    break;
                                }
                            }
                            if (firzen_file) {
                                obj->hp += partner->hp;
                                obj->dark_hp += partner->dark_hp;
                                if (obj->dark_hp > obj->max_hp) obj->dark_hp = obj->max_hp;
                                if (obj->hp > obj->dark_hp) obj->hp = obj->dark_hp;
                                obj->frame_id1 = 290;
                                obj->fusion_state = 1;
                                obj->x_velocity = 0.0;
                                partner->y_velocity = 0.0;
                                obj->x = (partner->x + obj->x) / 2;
                                obj->z = (partner->z + obj->z) / 2;
                                obj->x_position = static_cast<double>(obj->x);
                                obj->z_position = static_cast<double>(obj->z);
                                obj->fusion_partner = j;
                                obj->firen_counter = 4500;
                                obj->fusion_self_id = static_cast<int32_t>(obj->file->id);
                                obj->fusion_partner_id = static_cast<int32_t>(partner->file->id);
                                obj->file = firzen_file;
                                obj->mp = 500;
                                world->is_object_exists[j] = 0;
                                break;
                            }
                        }
                    }
                }
            }
        } else if (fid == FIRZEN_DAT &&
                   obj->fusion_state == 1 &&
                   (obj->frame_id1 < 9 || obj->frame_id1 > 260) &&
                   obj->firen_counter < 1) {
            int32_t p_idx = obj->fusion_partner;
            obj->fusion_state = -1;
            obj->firen_counter = 900;
            for (uint32_t k = 0; k < MAX_FILES; ++k) {
                file_t* f = world->files[k];
                if (!f) continue;
                if (static_cast<int32_t>(f->id) == obj->fusion_self_id) {
                    obj->file = f;
                } else if (static_cast<int32_t>(f->id) == obj->fusion_partner_id &&
                           p_idx >= 0 && p_idx < static_cast<int32_t>(MAX_OBJECTS) &&
                           world->objects[p_idx]) {
                    object_t* partner = world->objects[p_idx];
                    object_init(partner);
                    partner->file = f;
                    partner->weapon_hp = f->weapon_hp;
                    world->is_object_exists[p_idx] = 1;
                }
            }
            if (p_idx >= 0 && p_idx < static_cast<int32_t>(MAX_OBJECTS) && world->objects[p_idx]) {
                object_t* partner = world->objects[p_idx];
                partner->hp = obj->hp / 2;
                partner->dark_hp = obj->dark_hp / 2;
                obj->hp /= 2;
                obj->dark_hp /= 2;
                partner->x = obj->x;
                partner->z = obj->z;
                partner->y = 0;
                partner->x_position = static_cast<double>(partner->x);
                partner->z_position = static_cast<double>(partner->z);
                partner->y_position = 0.0;
                obj->x_velocity = 0.0;
                partner->x_velocity = 0.0;
                partner->facing = static_cast<uint8_t>(1U - obj->facing);
                obj->frame_id1 = 112;
                partner->frame_id1 = 112;
                obj->mp = 0;
                partner->mp = 0;
                partner->team = obj->team;
            }
        }
    }
}

void process_firzen_fusion(global_t* world, uint32_t /*obj_id*/)
{
    world_process_firzen_fusion(world, 0);
}

bool initiate_grapple(global_t* world, uint32_t catcher_id, uint32_t victim_id)
{
    if (!world || catcher_id >= MAX_OBJECTS || victim_id >= MAX_OBJECTS) {
        return false;
    }
    if (!world->is_object_exists[catcher_id] || !world->is_object_exists[victim_id]) {
        return false;
    }

    object_t* catcher = world->objects[catcher_id];
    object_t* victim = world->objects[victim_id];
    if (!catcher || !victim || !catcher->file || !victim->file) {
        return false;
    }

    if (victim->invincible_time != 0) {
        return false;
    }
    if (victim->frame_id1 < MAX_FRAMES && victim->file->frames[victim->frame_id1].cpoint.kind == 2 &&
        victim->cpoint_caught >= 0 && victim->cpoint_caught < static_cast<int32_t>(MAX_OBJECTS) &&
        world->is_object_exists[victim->cpoint_caught] &&
        world->objects[victim->cpoint_caught] &&
        world->objects[victim->cpoint_caught]->cpoint_catcher == static_cast<int32_t>(victim_id)) {
        return false;
    }

    catcher->cpoint_catcher = static_cast<int32_t>(victim_id);
    victim->cpoint_caught = static_cast<int32_t>(catcher_id);
    catcher->cpoint_hold_timer = 300;
    catcher->wait_counter = 0;

    victim->fall = 0;
    victim->wait_counter = 0;
    victim->x_velocity = 0.0;
    victim->y_velocity = 0.0;
    victim->z_velocity = 0.0;

    if (catcher->frame_id1 < MAX_FRAMES && catcher->file->frames[catcher->frame_id1].cpoint.vaction > 0) {
        victim->frame_id1 = static_cast<uint32_t>(catcher->file->frames[catcher->frame_id1].cpoint.vaction);
    } else {
        victim->frame_id1 = 230;
    }
    victim->frame_id4 = victim->frame_id1;

    return true;
}

void execute_throw(global_t* world, uint32_t catcher_id)
{
    if (!world || catcher_id >= MAX_OBJECTS || !world->is_object_exists[catcher_id]) {
        return;
    }
    object_t* catcher = world->objects[catcher_id];
    if (!catcher || !catcher->file || catcher->cpoint_catcher < 0) {
        return;
    }

    int32_t victim_id = catcher->cpoint_catcher;
    if (victim_id < 0 || victim_id >= static_cast<int32_t>(MAX_OBJECTS) ||
        !world->is_object_exists[victim_id]) {
        return;
    }
    object_t* victim = world->objects[victim_id];
    if (!victim || !victim->file) {
        return;
    }

    uint32_t a_frame_id = (catcher->frame_id4 < MAX_FRAMES) ? catcher->frame_id4 : catcher->frame_id1;
    if (a_frame_id >= MAX_FRAMES) return;
    const frame_t* a_frame = &catcher->file->frames[a_frame_id];
    const cpoint_t& cp = a_frame->cpoint;

    double tx = (cp.throwvx != 0) ? static_cast<double>(cp.throwvx) : 8.0;
    double ty = static_cast<double>(cp.throwvy);
    double tz = static_cast<double>(cp.throwvz);

    if (cp.throwinjury > 0) {
        victim->thrown_injury = static_cast<uint32_t>(cp.throwinjury);
    }
    victim->x_velocity = (catcher->facing == FACING_RIGHT) ? tx : -tx;
    victim->y_velocity = ty;
    victim->z_velocity = tz;
    victim->frame_id1 = (cp.vaction != 0) ? static_cast<uint32_t>(cp.vaction) : 180;
    victim->frame_id4 = victim->frame_id1;

    if (catcher->frame_id1 < MAX_FRAMES) {
        catcher->frame_id1 = static_cast<uint32_t>(catcher->file->frames[catcher->frame_id1].next);
        catcher->frame_id4 = catcher->frame_id1;
    }
    catcher->wait_counter = 0;
}

void release_grapple(global_t* world, uint32_t catcher_id)
{
    if (!world || catcher_id >= MAX_OBJECTS || !world->is_object_exists[catcher_id]) {
        return;
    }
    object_t* catcher = world->objects[catcher_id];
    if (!catcher) return;

    int32_t victim_id = catcher->cpoint_catcher;
    if (victim_id >= 0 && victim_id < static_cast<int32_t>(MAX_OBJECTS) &&
        world->is_object_exists[victim_id]) {
        object_t* victim = world->objects[victim_id];
        if (victim) {
            victim->cpoint_caught = 0;
            victim->frame_id1 = 212;
            victim->y_velocity = -3.0;
            if (victim->y_position > -2.0) {
                victim->y_position = -2.0;
            }
            victim->wait_counter = 0;
        }
    }
    catcher->cpoint_catcher = 0;
}

} // namespace lf2

#include "global.h"
#include "overlap.h"
#include "random.h"
#include "entity.h"
#include "audio/audio.h"
#include "gameplay/grapple.h"
#include <algorithm>
#include <cstdlib>

namespace lf2 {

namespace {

object_t* resolve_credit_owner(global_t* world, object_t* attacker)
{
    if (attacker->owner >= 0 && attacker->owner < static_cast<int32_t>(MAX_OBJECTS) &&
        world->objects[attacker->owner]) {
        return world->objects[attacker->owner];
    }
    return attacker;
}

bool is_convertible_energy_ball(uint32_t fid)
{
    return (fid == JOHN_BALL_DAT || fid == DEEP_BALL_DAT || fid == DENNIS_BALL_DAT ||
            fid == WOODY_BALL_DAT || fid == DAVIS_BALL_DAT ||
            fid == DENNIS_CHASE_DAT || fid == JACK_BALL_DAT);
}

void trigger_weapon_sound(int32_t sound_id, uint32_t sound_tag)
{
    if (sound_id > 0) {
        get_audio_system().on_frame_sound(static_cast<uint32_t>(sound_id));
    } else if (sound_tag != 0) {
        get_audio_system().on_frame_sound(sound_tag);
    }
}

void apply_catch_grab(object_t* attacker, int32_t attacker_id,
                      object_t* injured, int32_t injured_id,
                      const itr_t& eff)
{
    injured->x_velocity = 0.0;
    attacker->x_velocity = 0.0;
    attacker->facing = (injured->x < attacker->x) ? FACING_LEFT : FACING_RIGHT;
    injured->facing = static_cast<uint8_t>(1U - attacker->facing);

    uint32_t c_act = (eff.catching_act_1 < MAX_FRAMES) ? eff.catching_act_1 : 0;
    uint32_t v_act = (eff.caught_act_1 < MAX_FRAMES) ? eff.caught_act_1 : 0;
    attacker->frame_id1 = c_act;
    injured->frame_id1 = v_act;

    const frame_t* af = &attacker->file->frames[c_act];
    const frame_t* vf = &injured->file->frames[v_act];
    int32_t att_cx_in_frame = af->cpoint.x;
    int32_t inj_cx_in_frame = vf->cpoint.x;

    attacker->x_position = static_cast<double>(attacker->x);
    attacker->y_position = static_cast<double>(attacker->y);

    if (attacker->facing == FACING_RIGHT) {
        injured->x_position = static_cast<double>(
            (attacker->x - af->centerx - vf->centerx) + inj_cx_in_frame + att_cx_in_frame);
    } else {
        injured->x_position = static_cast<double>(
            (af->centerx + vf->centerx + attacker->x - inj_cx_in_frame) - att_cx_in_frame);
    }
    injured->y_position = static_cast<double>((vf->centery - af->centery) + attacker->y);

    double half_shift = (static_cast<double>(injured->x) - injured->x_position) * 0.5;
    injured->x_position += half_shift;
    attacker->x_position += half_shift;
    injured->x = static_cast<int32_t>(injured->x_position);
    attacker->x = static_cast<int32_t>(attacker->x_position);

    attacker->cpoint_catcher = injured_id;
    injured->cpoint_caught = attacker_id;
    attacker->cpoint_hold_timer = 300;
    injured->fall = 0;
}

bool should_defend_with_armor(const object_t* attacker, const object_t* injured,
                              const frame_t* inj_f1, const frame_t* inj_f4, const itr_t& eff)
{
    uint32_t inj_s4 = inj_f4->state;
    if (eff.bdefend == 100 || inj_s4 == 8 || inj_s4 == 11 || inj_s4 == 12 ||
        inj_s4 == 13 || inj_s4 == 14 || inj_s4 == 16 || inj_s4 == 18) {
        return false;
    }

    uint32_t inj_fid = injured->file->id;
    uint32_t att_fid = attacker->file->id;
    bool elem_or_pierce = (eff.effect / 10 == 2 || eff.effect / 10 == 3 ||
                           eff.effect == 2 || eff.effect == 3 ||
                           att_fid == JOHN_BISCUIT_DAT || att_fid == HENRY_ARROW2_DAT);

    if (inj_fid == KNIGHT_DAT && injured->bdefend < 16 && !elem_or_pierce) {
        return true;
    }
    if (inj_fid == LOUIS_DAT && injured->bdefend < 2 && !elem_or_pierce &&
        (injured->frame_id1 < 20 || inj_f1->state == 5 || inj_f1->state == 4 || inj_f1->state == 7)) {
        return true;
    }
    if (inj_fid == JULIAN_DAT && injured->bdefend <= 15 &&
        att_fid != JOHN_BISCUIT_DAT && att_fid != HENRY_ARROW2_DAT) {
        return true;
    }
    return false;
}

bool is_defended_hit(const object_t* attacker, const object_t* injured,
                     const frame_t* inj_f1, const frame_t* inj_f4, const itr_t& eff)
{
    if (should_defend_with_armor(attacker, injured, inj_f1, inj_f4, eff)) {
        return true;
    }

    uint32_t att_fid = attacker->file->id;
    if (inj_f4->state == STATE_DEFEND && static_cast<int32_t>(eff.bdefend) < 61 &&
        (attacker->facing != injured->facing || eff.dvx < 0 ||
         att_fid == BOOMERANG_DAT || att_fid == JAN_CHASE_DAT ||
         att_fid == FIRZEN_CHASEF_DAT || att_fid == FIRZEN_CHASEI_DAT) &&
        injured->hp > 0) {
        return true;
    }
    return false;
}

void apply_weapon_rebound_and_stick_boost(object_t* attacker, object_t* injured, const itr_t& eff)
{
    double dvx_d = static_cast<double>(eff.dvx);
    double scaled_vx = (injured->x_velocity < 0.0)
        ? -(injured->x_velocity * 0.55)
        : (injured->x_velocity * 0.55);

    if (scaled_vx < dvx_d ||
        (attacker->facing == FACING_RIGHT && injured->pic_x_gain > 0.0) ||
        (attacker->facing == FACING_LEFT && injured->pic_x_gain < 0.0)) {
        if (attacker->facing == FACING_RIGHT) {
            injured->pic_x_gain += dvx_d;
        }
        if (attacker->facing == FACING_LEFT) {
            injured->pic_x_gain -= dvx_d;
        }
    } else if ((attacker->facing == FACING_LEFT && injured->x_velocity > 0.0) ||
               (attacker->facing == FACING_RIGHT && injured->x_velocity < 0.0)) {
        injured->pic_x_gain = -(injured->x_velocity * 0.55);
    }

    if (attacker->file->id == STICK_DAT && attacker->weapon_type < 0) {
        injured->pic_x_gain *= 2.5;
        get_audio_system().on_frame_sound(13);
        if (injured->pic_x_gain > 0.0 && injured->pic_x_gain < 10.0) {
            injured->pic_x_gain = 10.0;
        }
        if (injured->pic_x_gain < 0.0 && injured->pic_x_gain > -10.0) {
            injured->pic_x_gain = -10.0;
        }
    }
}

void apply_struck_projectile_reaction(global_t* world,
                                      object_t* attacker, int32_t attacker_id,
                                      object_t* injured)
{
    const frame_t* att_f1 = &attacker->file->frames[attacker->frame_id1];
    const frame_t* inj_f1 = &injured->file->frames[injured->frame_id1];
    uint32_t inj_state = inj_f1->state;
    uint32_t att_state = att_f1->state;

    if (inj_state != 3005 && (inj_state != 3006 || att_state == 3005)) {
        if (attacker->weapon_type < 0 && attacker->holder_id >= 0 &&
            attacker->holder_id < static_cast<int32_t>(MAX_OBJECTS) &&
            world->objects[attacker->holder_id]) {
            object_t* holder = world->objects[attacker->holder_id];
            injured->team = holder->team;
            injured->owner = holder->owner;
        } else {
            injured->team = attacker->team;
            injured->owner = attacker->owner;
        }

        injured->flag_eb = 1;
        injured->wait_counter = 0;
        injured->y_accl = 0.0;
        injured->pic_x_gain = 0.0;
        injured->z_accl = 0.0;

        uint32_t att_fid = attacker->file->id;
        uint32_t inj_fid = injured->file->id;
        if (att_fid == FREEZE_BALL_DAT && is_convertible_energy_ball(inj_fid)) {
            injured->team = attacker->team;
            injured->owner = attacker->owner;
            injured->file = attacker->file;
            injured->frame_id1 = 40;
            injured->frame_id2 = 40;
            injured->frame_id3 = 40;
        } else {
            if ((attacker->file->type == TYPE_CHARACTER || attacker->weapon_type < 0) &&
                att_f1->itrs_size > 0 && att_f1->itrs &&
                att_f1->itrs[0].effect != 2 && att_f1->itrs[0].effect != 20) {
                injured->frame_id1 = 30;
                if (att_fid == FREEZE_DAT && is_convertible_energy_ball(inj_fid)) {
                    for (uint32_t k = 0; k < MAX_FILES; ++k) {
                        if (world->files[k] && world->files[k]->id == FREEZE_BALL_DAT) {
                            injured->file = world->files[k];
                            injured->frame_id2 = injured->frame_id1;
                            injured->frame_id3 = injured->frame_id1;
                            break;
                        }
                    }
                }
            } else {
                injured->frame_id1 = 20;
            }

            if (attacker->weapon_type < 0) {
                injured->move_counter = static_cast<uint32_t>(attacker->holder_id);
                if (att_fid == ICE_SWORD_DAT && is_convertible_energy_ball(inj_fid) &&
                    attacker->holder_id >= 0 && attacker->holder_id < static_cast<int32_t>(MAX_OBJECTS) &&
                    world->objects[attacker->holder_id]) {
                    object_t* holder = world->objects[attacker->holder_id];
                    for (uint32_t k = 0; k < MAX_FILES; ++k) {
                        if (world->files[k] && world->files[k]->id == FREEZE_BALL_DAT) {
                            injured->file = world->files[k];
                            injured->frame_id2 = injured->frame_id1;
                            injured->frame_id3 = injured->frame_id1;
                            break;
                        }
                    }
                    injured->team = holder->team;
                    injured->owner = holder->owner;
                }
            } else {
                injured->move_counter = static_cast<uint32_t>(attacker_id);
            }
        }
    }

    if ((injured->file->frames[injured->frame_id1].state == 3005 && att_state == 3005) ||
        (injured->file->frames[injured->frame_id1].state == 3006 && att_state == 3006)) {
        injured->frame_id1 = 20;
        injured->wait_counter = 0;
        injured->y_accl = 0.0;
        injured->pic_x_gain = 0.0;
        injured->z_accl = 0.0;

        attacker->frame_id1 = 20;
        attacker->wait_counter = 0;
        attacker->y_accl = 0.0;
        attacker->pic_x_gain = 0.0;
        attacker->z_accl = 0.0;
    }

    if (attacker->weapon_type < 0 && attacker->holder_id >= 0 &&
        attacker->holder_id < static_cast<int32_t>(MAX_OBJECTS) &&
        world->objects[attacker->holder_id]) {
        if (world->objects[attacker->holder_id]->shaking > 0) {
            world->objects[attacker->holder_id]->shaking = -world->objects[attacker->holder_id]->shaking;
        }
    } else if (attacker->shaking > 0) {
        attacker->shaking = -attacker->shaking;
    }
}

void record_hit_spark(global_t* world,
                      object_t* attacker, uint32_t attacker_id,
                      object_t* injured, int32_t injured_id,
                      const itr_t& eff, int32_t is_bleed)
{
    int32_t spark_owner_idx = injured_id;
    if (injured->z <= attacker->z && world->is_object_exists[attacker_id] != 0) {
        if (injured->z < attacker->z || injured_id < static_cast<int32_t>(attacker_id)) {
            spark_owner_idx = static_cast<int32_t>(attacker_id);
        }
    }
    object_t* so = world->objects[spark_owner_idx];
    if (!so || so->spark_count >= 10) return;

    int32_t idx = so->spark_count;
    so->spark_count = idx + 1;
    so->spark_kind[idx] = is_bleed * 20 + ((eff.fall < 61) ? 10 : 0);

    const frame_t* att_f1 = &attacker->file->frames[attacker->frame_id1];
    int32_t sx;
    if (attacker->facing == FACING_RIGHT) {
        sx = (attacker->x - att_f1->centerx) + eff.w + eff.x;
        if (injured->x < sx) sx = injured->x;
    } else {
        sx = ((att_f1->centerx - eff.w) - eff.x) + attacker->x;
        if (sx < injured->x) sx = injured->x;
    }

    int32_t sy = (eff.h / 2 + attacker->y + eff.y) - att_f1->centery;
    int32_t min_y = injured->y - att_f1->centery;
    if (sy < min_y || injured->y < sy) {
        int32_t clamp_y = (sy < min_y) ? min_y : injured->y;
        sy = (sy + clamp_y) / 2;
    }

    so->spark_x[idx] = sx + (std::rand() % 9) - 4;
    so->spark_y[idx] = sy + attacker->z + (std::rand() % 9) - 4;
}

bool apply_plain_hit(global_t* world,
                     object_t* attacker, uint32_t attacker_id,
                     object_t* injured, int32_t injured_id,
                     const itr_t& eff, int32_t& out_is_bleed)
{
    injured->bdefend = 45;
    uint32_t injured_fid = injured->file->id;
    const frame_t* inj_f1 = &injured->file->frames[injured->frame_id1];
    const frame_t* inj_f3 = (injured->frame_id3 < MAX_FRAMES)
        ? &injured->file->frames[injured->frame_id3]
        : inj_f1;
    const frame_t* inj_f4 = &injured->file->frames[injured->frame_id4];
    const frame_t* att_f1 = &attacker->file->frames[attacker->frame_id1];

    // Criminal hostage rescue
    if (injured_fid == CRIMINAL_DAT) {
        if (inj_f1->bdys_size < 1 || !inj_f1->bdys || inj_f1->bdys[0].kind < 1001) {
            return false;
        }
        injured->team = 1;
        uint32_t rescued_frame = inj_f1->bdys[0].kind - 1000;
        injured->frame_id1 = (rescued_frame < MAX_FRAMES) ? rescued_frame : 0;
        attacker->shaking = 3;
        injured->shaking = -3;
        return false;
    }

    uint32_t injured_type = injured->file->type;
    if (injured_type != TYPE_DRINK) {
        int32_t dmg = eff.injury;
        if (injured->armor_multiplier > 0) {
            dmg = (dmg * 100) / static_cast<int32_t>(injured->armor_multiplier);
        }
        object_t* credit = resolve_credit_owner(world, attacker);
        if (injured->hp > 0 && injured->hp <= dmg &&
            injured_type == TYPE_CHARACTER && injured->clone == -1) {
            credit->kills++;
        }
        injured->hp -= dmg;
        injured->dark_hp -= dmg / 3;
        injured->hp_lost += static_cast<uint32_t>(dmg);
        if (injured_type == TYPE_CHARACTER && injured->clone == -1) {
            credit->total_attack += static_cast<uint32_t>(dmg);
        }
    }

    if (injured->hp < 1 || eff.effect == EFFECT_SHINING) {
        injured->fall = 80;
    }

    if (injured_type == TYPE_LIGHT_WEAPON || injured_type == TYPE_HEAVY_WEAPON ||
        injured_type == TYPE_THROW_WEAPON || injured_type == TYPE_DRINK) {
        injured->weapon_hp -= eff.injury;
        if (eff.bdefend == 100) {
            injured->weapon_hp = -1;
        }
    }

    if (injured_type != TYPE_HEAVY_WEAPON || eff.fall > 40) {
        injured->attacks++;
    }

    injured->fall += (eff.fall == 0) ? 20 : static_cast<int32_t>(eff.fall);

    if (inj_f3->state == STATE_ICE || inj_f4->state == STATE_FALLING ||
        injured_type == TYPE_LIGHT_WEAPON || injured_type == TYPE_THROW_WEAPON ||
        injured_type == TYPE_DRINK || injured_type == TYPE_HEAVY_WEAPON) {
        injured->fall = 80;
    }

    if (injured_type != TYPE_ATTACK) {
        if (injured->fall > 60) {
            injured->fall = 80;
        } else if (injured->fall > 40) {
            injured->frame_id1 = 226;
            injured->fall = 60;
            if (injured->y < 0) injured->fall = 80;
        } else if (injured->fall > 20) {
            injured->frame_id1 = (injured->facing == attacker->facing) ? 224 : 222;
            injured->fall = 40;
            if (injured->y < 0) injured->fall = 80;
        } else if (injured->fall > 0) {
            injured->frame_id1 = 220;
            injured->fall = 20;
            if (injured->y < 0) {
                injured->frame_id1 = (injured->facing == attacker->facing) ? 224 : 222;
            }
        }
    }

    if (attacker->file->type == TYPE_ATTACK) {
        trigger_weapon_sound(attacker->file->weapon_broken_sound_id, attacker->file->weapon_broken_sound);
    }
    if (injured_type == TYPE_CHARACTER) {
        if (eff.effect == EFFECT_PUNCH) {
            get_audio_system().on_frame_sound((injured->fall == 80) ? 2U : 0U);
        } else if (eff.effect == EFFECT_BLEED) {
            out_is_bleed = 1;
            get_audio_system().on_frame_sound((injured->fall == 80) ? 12U : 11U);
            get_audio_system().on_frame_sound((injured->fall == 80) ? 2U : 0U);
        }
    } else if (injured_type > 0) {
        trigger_weapon_sound(injured->file->weapon_hit_sound_id, injured->file->weapon_hit_sound);
    }

    // Horizontal knockback accumulation
    if (injured->fall == 80 && injured->x_velocity > -5.0 &&
        injured->x_velocity < 5.0 && eff.dvx == 0) {
        if (att_f1->state == 2000) {
            injured->pic_x_gain += 5.0;
        } else {
            injured->pic_x_gain += (attacker->facing == FACING_RIGHT) ? 5.0 : -5.0;
        }
    } else if (att_f1->state == 2000) {
        if (attacker->x < injured->x) {
            injured->pic_x_gain += static_cast<double>(eff.dvx);
        } else {
            injured->pic_x_gain -= static_cast<double>(eff.dvx);
        }
    } else if (injured_type == TYPE_THROW_WEAPON || injured_type == TYPE_DRINK) {
        apply_weapon_rebound_and_stick_boost(attacker, injured, eff);
    } else if (eff.effect == 22 || eff.effect == 23) {
        if (injured->x <= attacker->x) {
            injured->pic_x_gain += static_cast<double>(eff.dvx);
        } else {
            injured->pic_x_gain -= static_cast<double>(eff.dvx);
        }
    } else {
        if (attacker->facing == FACING_RIGHT) {
            injured->pic_x_gain += static_cast<double>(eff.dvx);
        } else {
            injured->pic_x_gain -= static_cast<double>(eff.dvx);
        }
    }

    // Flying projectile hitting target (state 3000 -> frame 10)
    if (att_f1->state == 3000 &&
        (injured_type == TYPE_CHARACTER ||
         attacker->file->id != FREEZE_BALL_DAT ||
         (!is_convertible_energy_ball(injured_fid) &&
          !(injured_fid == FREEZE_BALL_DAT && injured->frame_id1 != 40)))) {
        attacker->frame_id1 = 10;
        attacker->wait_counter = 0;
        attacker->x_velocity = 0.0;
        attacker->z_velocity = static_cast<double>(attacker->file->frames[10].dvz);
    }

    // Knockdown arc and falling frame
    if (injured->fall == 80) {
        if (eff.dvy == 0) {
            if ((injured_type != TYPE_HEAVY_WEAPON && injured_type != TYPE_ATTACK) || eff.fall > 40) {
                injured->y_accl -= 7.0;
            }
        } else {
            if ((injured_type != TYPE_HEAVY_WEAPON && injured_type != TYPE_ATTACK) || eff.fall > 40) {
                injured->y_accl += static_cast<double>(eff.dvy);
            }
            if (static_cast<int32_t>(static_cast<double>(injured->y) + injured->y_accl) > 0) {
                injured->y_accl = 12.0;
            }
        }

        if ((injured->facing == FACING_RIGHT && injured->pic_x_gain <= 0.0) ||
            (injured->facing == FACING_LEFT && injured->pic_x_gain >= 0.0)) {
            injured->frame_id1 = 180;
        } else {
            injured->frame_id1 = 186;
        }

        if (injured->weapon_type > 0 && injured->weapon_id >= 0 &&
            injured->weapon_id < static_cast<int32_t>(MAX_OBJECTS) &&
            world->objects[injured->weapon_id] &&
            injured_id == world->objects[injured->weapon_id]->holder_id) {
            attacker->vrest_of_objects[injured->weapon_id] = 45;
            injured->vrest_of_objects[injured->weapon_id] = 30;
        }
    }

    if (attacker->shaking >= 0) {
        attacker->shaking = 3;
    }
    injured->shaking = -3;

    if (eff.arest < 4 && eff.vrest == 0) {
        attacker->arest = 4;
    } else {
        attacker->arest = static_cast<int32_t>(eff.arest);
    }
    if (eff.vrest > 0) {
        injured->vrest_of_objects[attacker_id] = static_cast<uint8_t>(eff.vrest);
    }

    if (inj_f4->cpoint.kind == 2 && injured->fall != 80 &&
        inj_f4->cpoint.fronthurtact != 0) {
        int32_t c_id = injured->cpoint_caught;
        if (c_id >= 0 && c_id < static_cast<int32_t>(MAX_OBJECTS) &&
            world->objects[c_id] && world->objects[c_id]->cpoint_catcher == injured_id) {
            int32_t h_act = (injured->facing == attacker->facing)
                ? inj_f4->cpoint.backhurtact
                : inj_f4->cpoint.fronthurtact;
            if (h_act >= 0 && h_act < static_cast<int32_t>(MAX_FRAMES)) {
                injured->frame_id1 = static_cast<uint32_t>(h_act);
            }
        }
    }

    if (injured->fall == 80) {
        injured->fall = 0;
    }

    if (attacker->weapon_type < 0 && attacker->holder_id >= 0 &&
        attacker->holder_id < static_cast<int32_t>(MAX_OBJECTS) &&
        world->objects[attacker->holder_id]) {
        world->objects[attacker->holder_id]->shaking = attacker->shaking;
    }

    // Thrown weapon rebound (state 1002)
    if (att_f1->state == 1002) {
        attacker->frame_id1 = static_cast<uint32_t>(lf2_random(0xee, 16));
        attacker->x_velocity = -(injured->pic_x_gain * 0.5);
        attacker->y_velocity = -4.0;
        if (attacker->file->type == TYPE_THROW_WEAPON && injured_type == TYPE_THROW_WEAPON) {
            attacker->pic_x_gain = -injured->pic_x_gain;
        }
    }

    if (injured_type == TYPE_LIGHT_WEAPON) {
        injured->flag_eb = 1;
        injured->frame_id1 = static_cast<uint32_t>(lf2_random(0xef, 16));
        injured->team = attacker->team;
    }
    if (injured_type == TYPE_THROW_WEAPON || injured_type == TYPE_DRINK) {
        attacker->vrest_of_objects[injured_id] = 30;
        injured->flag_eb = 1;
        injured->frame_id1 = static_cast<uint32_t>(lf2_random(0xf0, 16));
        injured->team = attacker->team;
    }
    if (injured_type == TYPE_HEAVY_WEAPON) {
        injured->flag_eb = 1;
        uint8_t h_vrest = (eff.fall < 41 && eff.effect != EFFECT_SHINING) ? 3 : 19;
        if (attacker->weapon_type == -2 && attacker->holder_id >= 0 &&
            attacker->holder_id < static_cast<int32_t>(MAX_OBJECTS) &&
            world->objects[attacker->holder_id]) {
            world->objects[attacker->holder_id]->vrest_of_objects[injured_id] = h_vrest;
        } else if (attacker->file->type != TYPE_HEAVY_WEAPON) {
            attacker->vrest_of_objects[injured_id] = h_vrest;
        }
        injured->facing = attacker->facing;
        if (eff.fall < 41 && injured->y >= 0 && eff.effect != EFFECT_SHINING) {
            injured->frame_id1 = 20;
        } else {
            injured->frame_id1 = static_cast<uint32_t>(lf2_random(0xf1, 6));
        }
        injured->team = attacker->team;
    }

    if (attacker->file->id == HENRY_ARROW1_DAT && injured_type == TYPE_CHARACTER) {
        world->is_object_exists[attacker_id] = 0;
    }
    if (attacker->file->id == JOHN_BISCUIT_DAT && injured_type == TYPE_CHARACTER) {
        attacker->hp = 0;
    }

    if (injured_type == TYPE_ATTACK) {
        apply_struck_projectile_reaction(world, attacker, static_cast<int32_t>(attacker_id), injured);
    }

    if ((eff.effect == EFFECT_ICE || eff.effect == EFFECT_FREEZE) &&
        injured_type == TYPE_CHARACTER && inj_f3->state != STATE_ICE) {
        injured->frame_id1 = 200;
        injured->wait_counter = 0;
        get_audio_system().on_frame_sound(14);
    }
    if ((eff.effect == EFFECT_FIRE || eff.effect == EFFECT_FIRE_JULIAN || eff.effect == EFFECT_FIRE_EXPLODE ||
         (eff.effect == EFFECT_FIRE_NO_SOUND && inj_f3->state != STATE_BURNING)) &&
        injured_type == TYPE_CHARACTER) {
        injured->frame_id1 = 203;
        injured->wait_counter = 0;
        get_audio_system().on_frame_sound(16);
        injured->facing = (injured->pic_x_gain < 0.0) ? FACING_RIGHT : FACING_LEFT;
    }
    if (eff.effect == 23) {
        get_audio_system().on_frame_sound(16);
    }

    return true;
}

void apply_defended_hit(global_t* world,
                      object_t* attacker, uint32_t attacker_id,
                      object_t* injured,
                      const itr_t& eff)
{
    const frame_t* att_f1 = &attacker->file->frames[attacker->frame_id1];
    const frame_t* inj_f4 = &injured->file->frames[injured->frame_id4];
    uint32_t injured_fid = injured->file->id;
    uint32_t injured_type = injured->file->type;

    if (attacker->file->type == TYPE_ATTACK) {
        trigger_weapon_sound(attacker->file->weapon_broken_sound_id, attacker->file->weapon_broken_sound);
    } else if (injured_fid == KNIGHT_DAT || injured_fid == LOUIS_DAT) {
        get_audio_system().on_frame_sound(17);
    } else {
        get_audio_system().on_frame_sound(1);
    }

    if (injured_type != TYPE_DRINK) {
        int32_t scaled = eff.injury;
        if (injured->armor_multiplier > 0) {
            scaled = (scaled * 100) / static_cast<int32_t>(injured->armor_multiplier);
        }
        int32_t dmg10 = scaled / 10;
        object_t* credit = resolve_credit_owner(world, attacker);
        if (injured->hp > 0 && injured->hp <= dmg10 &&
            injured_type == TYPE_CHARACTER && injured->clone == -1) {
            credit->kills++;
        }
        injured->hp -= dmg10;
        injured->dark_hp -= dmg10 / 3;
        injured->hp_lost += static_cast<uint32_t>(dmg10);
        if (injured_type == TYPE_CHARACTER && injured->clone == -1) {
            credit->total_attack += static_cast<uint32_t>(dmg10);
        }
    }

    if (injured_type == TYPE_LIGHT_WEAPON || injured_type == TYPE_HEAVY_WEAPON ||
        injured_type == TYPE_THROW_WEAPON || injured_type == TYPE_DRINK) {
        injured->weapon_hp -= eff.injury;
        if (eff.bdefend == 100) {
            injured->weapon_hp = -1;
        }
    }

    if (injured->hp < 1) {
        injured->fall = 80;
    }

    injured->wait_counter = 0;
    injured->bdefend += static_cast<int32_t>(eff.bdefend);
    injured->attacks++;
    attacker->shaking = 3;
    injured->shaking = -5;

    if (injured->y == 0) {
        if (injured->bdefend >= 31 && inj_f4->state == STATE_DEFEND) {
            injured->frame_id1 = 112;
        } else if (injured->frame_id1 == 110) {
            injured->frame_id1 = 111;
        }

        if (injured->fall == 80 && injured->x_velocity > -3.0 &&
            injured->x_velocity < 3.0 && eff.dvx == 0) {
            if (att_f1->state == 2000) {
                injured->pic_x_gain += (attacker->x < injured->x) ? 6.0 : -6.0;
            } else {
                injured->pic_x_gain += (attacker->facing == FACING_RIGHT) ? 3.0 : -3.0;
            }
        } else if (att_f1->state == 2000) {
            if (injured->x <= attacker->x) {
                injured->pic_x_gain -= static_cast<double>(eff.dvx);
            } else {
                injured->pic_x_gain += static_cast<double>(eff.dvx);
            }
        } else if (eff.effect == 22 || eff.effect == 23) {
            if (injured->x <= attacker->x) {
                injured->pic_x_gain += static_cast<double>(eff.dvx);
            } else {
                injured->pic_x_gain -= static_cast<double>(eff.dvx);
            }
        } else {
            if (attacker->facing == FACING_RIGHT) {
                injured->pic_x_gain += static_cast<double>(eff.dvx / 2);
            } else {
                injured->pic_x_gain -= static_cast<double>(eff.dvx / 2);
            }
        }
    } else {
        if (injured->fall == 80 && injured->x_velocity > -6.0 &&
            injured->x_velocity < 6.0 && eff.dvx <= 5) {
            injured->pic_x_gain += (attacker->facing == FACING_RIGHT) ? 6.0 : -6.0;
        } else if (eff.effect == 22 || eff.effect == 23) {
            if (injured->x <= attacker->x) {
                injured->pic_x_gain += static_cast<double>(eff.dvx);
            } else {
                injured->pic_x_gain -= static_cast<double>(eff.dvx);
            }
        } else {
            if (attacker->facing == FACING_RIGHT) {
                injured->pic_x_gain += static_cast<double>(eff.dvx);
            } else {
                injured->pic_x_gain -= static_cast<double>(eff.dvx);
            }
        }
    }

    if (eff.arest < 4 && eff.vrest == 0) {
        attacker->arest = 4;
    } else {
        attacker->arest = std::min<int32_t>(static_cast<int32_t>(eff.arest), 12);
    }
    if (eff.vrest > 0) {
        int32_t vr = (eff.vrest < 5) ? 4 : std::min<int32_t>(static_cast<int32_t>(eff.vrest), 12);
        injured->vrest_of_objects[attacker_id] = static_cast<uint8_t>(vr);
    }

    if (attacker->weapon_type < 0 && attacker->holder_id >= 0 &&
        attacker->holder_id < static_cast<int32_t>(MAX_OBJECTS) &&
        world->objects[attacker->holder_id]) {
        world->objects[attacker->holder_id]->shaking = attacker->shaking;
    }

    if (att_f1->state == 1002) {
        attacker->frame_id1 = static_cast<uint32_t>(lf2_random(0xf3, 16));
        attacker->x_velocity = -(injured->pic_x_gain * 0.5);
        attacker->y_velocity = -4.0;
        attacker->z_velocity /= -1.5;
    }
    if (att_f1->state == 2000 &&
        ((injured->x < attacker->x && attacker->x_velocity >= 0.0) ||
         (attacker->x <= injured->x && attacker->x_velocity <= 0.0)) &&
        attacker->x_velocity > 0.0) {
        attacker->x_velocity /= 2.5;
        attacker->z_velocity /= 2.5;
    }
    if (att_f1->state == 3000) {
        attacker->frame_id1 = 10;
        attacker->wait_counter = 0;
        attacker->x_velocity = 0.0;
    }
}

void apply_non_zero_itr(global_t* world,
                        object_t* attacker, uint32_t attacker_id,
                        object_t* injured, int32_t injured_id,
                        const itr_t& eff, int32_t counter_12)
{
    uint32_t kind = eff.kind;
    uint32_t injured_type = injured->file->type;

    if (kind == ITR_SUPER_PUNCH) {
        injured->can_hit_flag = 3;
        return;
    }

    if (kind == ITR_CATCH_INJURED || kind == ITR_CATCH) {
        apply_catch_grab(attacker, static_cast<int32_t>(attacker_id), injured, injured_id, eff);
        return;
    }

    if (kind == ITR_ROWING_PICK && attacker->weapon_type == 0) {
        attacker->weapon_type = 1;
        injured->weapon_type = -1;
        injured->team = attacker->team;
        attacker->weapon_id = injured_id;
        injured->holder_id = static_cast<int32_t>(attacker_id);
        injured->owner = static_cast<int32_t>(attacker_id);
        attacker->get_weapon_counter++;
        uint32_t inj_fid = injured->file->id;
        if (inj_fid == KNIFE_DAT || inj_fid == BOOMERANG_DAT) {
            attacker->weapon_type = 101;
        }
        if (injured_type == TYPE_THROW_WEAPON) {
            attacker->weapon_type = 4;
            injured->weapon_type = -4;
        } else if (injured_type == TYPE_DRINK) {
            if (injured->hp < 1) {
                attacker->weapon_type = 4;
                injured->weapon_hp = 0;
            } else {
                attacker->weapon_type = 6;
            }
            injured->weapon_type = -attacker->weapon_type;
        }
        return;
    }

    if (kind == ITR_PICK_UP_WEAPON) {
        if (injured_type == TYPE_LIGHT_WEAPON) {
            attacker->frame_id1 = 115;
            attacker->weapon_type = (injured->file->id == KNIFE_DAT || injured->file->id == BOOMERANG_DAT) ? 101 : 1;
            injured->weapon_type = -1;
        } else if (injured_type == TYPE_THROW_WEAPON) {
            attacker->frame_id1 = 115;
            attacker->weapon_type = 4;
            injured->weapon_type = -4;
        } else if (injured_type == TYPE_DRINK) {
            attacker->frame_id1 = 115;
            if (injured->hp < 1) {
                attacker->weapon_type = 4;
                injured->weapon_hp = 0;
            } else {
                attacker->weapon_type = 6;
            }
            injured->weapon_type = -attacker->weapon_type;
        } else if (injured_type == TYPE_HEAVY_WEAPON) {
            attacker->frame_id1 = 116;
            attacker->weapon_type = 2;
            injured->weapon_type = -2;
        } else {
            return;
        }
        injured->team = attacker->team;
        attacker->weapon_id = injured_id;
        injured->holder_id = static_cast<int32_t>(attacker_id);
        injured->owner = static_cast<int32_t>(attacker_id);
        attacker->get_weapon_counter++;
        attacker->wait_counter = 0;
        return;
    }

    if (kind == ITR_HEAL) {
        injured->curing_hp = eff.injury + 1000;
        if (eff.dvx >= 0 && eff.dvx < static_cast<int32_t>(MAX_FRAMES)) {
            attacker->frame_id1 = static_cast<uint32_t>(eff.dvx);
        }
        attacker->x_position = injured->x_position;
        attacker->z_position = injured->z_position + 1.0;
        return;
    }

    if (kind == ITR_FORCEFIELD) {
        if (injured_type == TYPE_ATTACK) {
            trigger_weapon_sound(injured->file->weapon_broken_sound_id, injured->file->weapon_broken_sound);
            if (injured->file->frames[injured->frame_id1].state == 3005) {
                attacker->shaking = -3;
                injured->flag_eb = 1;
                injured->frame_id1 = 40;
            } else {
                attacker->shaking = -3;
                injured->team = attacker->team;
                injured->owner = attacker->owner;
                injured->flag_eb = 1;
                injured->frame_id1 = 30;
                injured->wait_counter = 0;
                injured->y_accl = 0.0;
                injured->y_velocity = 0.0;
                injured->pic_x_gain = 0.0;
                injured->x_velocity = 0.0;
                injured->z_accl = 0.0;
                injured->z_velocity = 0.0;
                injured->move_counter = attacker_id;
            }
        } else if (injured_type == TYPE_CHARACTER) {
            attacker->hp = 0;
        }
        return;
    }

    if (kind == ITR_FLUTE ||
        (kind == ITR_FLOAT && static_cast<int32_t>(injured->thrown_injury) < 0)) {
        if (injured_type == TYPE_CHARACTER) {
            injured->thrown_injury = static_cast<uint32_t>(-20);
            if (injured->clone == -1 && counter_12 == 0) {
                resolve_credit_owner(world, attacker)->total_attack += 11;
            }
            injured->pic_x_gain = injured->x_velocity / 1.07;
            injured->x_velocity = injured->pic_x_gain;
            injured->z_accl = injured->z_velocity / 1.07;
            injured->z_velocity = injured->z_accl;
            injured->frame_id1 = 182;
            if (injured->y > -3) {
                injured->y = -2;
                injured->y_velocity = -6.0;
            }
            if (injured->y_velocity > -6.0) {
                injured->y_velocity -= 3.0;
                injured->y_accl = injured->y_velocity;
            }
        } else if (injured_type == TYPE_LIGHT_WEAPON || injured_type == TYPE_THROW_WEAPON ||
                   injured_type == TYPE_DRINK) {
            uint32_t inj_fid = injured->file->id;
            if (inj_fid != HENRY_ARROW1_DAT && inj_fid != RUDOLF_WEAPON_DAT) {
                if (injured->file->frames[injured->frame_id1].state != 1000) {
                    injured->frame_id1 = 0;
                }
                injured->pic_x_gain = injured->x_velocity / 1.07;
                injured->x_velocity = injured->pic_x_gain;
                injured->z_accl = injured->z_velocity / 1.07;
                injured->z_velocity = injured->z_accl;
                if (injured->y > -3) {
                    injured->y = -2;
                    injured->y_velocity = -6.0;
                }
                if (injured->y_velocity > -6.0) {
                    injured->y_velocity -= 3.0;
                    injured->y_accl = injured->y_velocity;
                }
            }
        } else if (injured_type == TYPE_HEAVY_WEAPON) {
            if (injured->file->frames[injured->frame_id1].state != 2000) {
                injured->frame_id1 = 0;
            }
            injured->pic_x_gain = injured->x_velocity / 1.07;
            injured->x_velocity = injured->pic_x_gain;
            injured->z_accl = injured->z_velocity / 1.07;
            injured->z_velocity = injured->z_accl;
            if (injured->y > -3) {
                injured->y = -2;
                injured->y_velocity = -6.0;
            }
            if (injured->y_velocity > -6.0) {
                injured->y_velocity -= 2.3;
                injured->y_accl = injured->y_velocity;
            }
        }
        return;
    }

    if (kind == ITR_FREEZE) {
        if (attacker->x <= injured->x + 5 ||
            (injured->x_velocity <= 0.0 && injured->pic_x_gain <= 0.0)) {
            if (attacker->x < injured->x - 5 &&
                (injured->x_velocity < 0.0 || injured->pic_x_gain < 0.0)) {
                injured->blocked_left = 1;
            }
        } else {
            injured->blocked_right = 1;
        }
        if (attacker->z <= injured->z + 2 ||
            (injured->z_velocity <= 0.0 && injured->z_accl <= 0.0)) {
            if (attacker->z < injured->z - 2 &&
                (injured->z_velocity < 0.0 || injured->z_accl < 0.0)) {
                injured->blocked_up = 1;
            }
        } else {
            injured->blocked_down = 1;
        }
        return;
    }

    if (kind == ITR_WHIRLWIND_ICE || kind == ITR_WHIRLWIND_WIND) {
        if (injured_type == TYPE_CHARACTER) {
            if (kind == ITR_WHIRLWIND_WIND) {
                int32_t dmg = eff.injury;
                if (injured->armor_multiplier > 0) {
                    dmg = (dmg * 100) / static_cast<int32_t>(injured->armor_multiplier);
                }
                object_t* credit = resolve_credit_owner(world, attacker);
                if (injured->hp > 0 && injured->hp <= dmg && injured->clone == -1) {
                    credit->kills++;
                }
                injured->hp -= dmg;
                injured->dark_hp -= dmg / 3;
                injured->hp_lost += static_cast<uint32_t>(dmg);
                if (injured->clone == -1) {
                    credit->total_attack += static_cast<uint32_t>(dmg);
                }
                injured->frame_id1 = 200;
                injured->wait_counter = 0;
                get_audio_system().on_frame_sound(14);
                if (static_cast<int32_t>(eff.vrest) > 0) {
                    injured->vrest_of_objects[attacker_id] = static_cast<uint8_t>(eff.vrest);
                }
                if (injured->weapon_type == 2 && injured->weapon_id >= 0 &&
                    injured->weapon_id < static_cast<int32_t>(MAX_OBJECTS) &&
                    world->objects[injured->weapon_id]) {
                    int32_t wid = injured->weapon_id;
                    object_t* w = world->objects[wid];
                    if (w->holder_id == injured_id && w->weapon_type == -2) {
                        attacker->vrest_of_objects[wid] = 45;
                        injured->weapon_type = 0;
                        injured->vrest_of_objects[wid] = 30;
                        w->weapon_type = 0;
                        w->frame_id1 = static_cast<uint32_t>(lf2_random(0xf4, 6));
                        w->y_velocity = -1.0;
                    }
                }
            }
            if (kind == ITR_WHIRLWIND_ICE) {
                injured->pic_x_gain = (injured->x <= attacker->x)
                    ? (injured->x_velocity + 1.0)
                    : (injured->x_velocity - 1.0);
                injured->x_velocity = injured->pic_x_gain;
                injured->z_accl = (attacker->z < injured->z)
                    ? (injured->z_velocity - 0.5)
                    : (injured->z_velocity + 0.5);
                injured->z_velocity = injured->z_accl;
                injured->frame_id1 = 182;
                if (injured->y > -3) {
                    injured->y = -2;
                    injured->y_velocity = -6.0;
                }
                if (injured->y_velocity > -6.0) {
                    injured->y_velocity -= 3.0;
                    injured->y_accl = injured->y_velocity;
                }
            }
        } else if (injured_type == TYPE_LIGHT_WEAPON || injured_type == TYPE_THROW_WEAPON ||
                   injured_type == TYPE_DRINK) {
            uint32_t inj_fid = injured->file->id;
            if (inj_fid != HENRY_ARROW1_DAT && inj_fid != RUDOLF_WEAPON_DAT) {
                if (injured->file->frames[injured->frame_id1].state != 1000) {
                    injured->frame_id1 = 0;
                }
                injured->pic_x_gain = (attacker->x < injured->x)
                    ? (injured->x_velocity - 1.0)
                    : (injured->x_velocity + 1.0);
                injured->x_velocity = injured->pic_x_gain;
                injured->z_accl = (attacker->z < injured->z)
                    ? (injured->z_velocity - 0.5)
                    : (injured->z_velocity + 0.5);
                injured->z_velocity = injured->z_accl;
                if (injured->y > -3) {
                    injured->y = -2;
                    injured->y_velocity = -6.0;
                }
                if (injured->y_velocity > -6.0) {
                    injured->y_velocity -= 3.0;
                    injured->y_accl = injured->y_velocity;
                }
            }
        } else if (injured_type == TYPE_HEAVY_WEAPON) {
            if (injured->file->frames[injured->frame_id1].state != 2000) {
                injured->frame_id1 = 0;
            }
            injured->pic_x_gain = (attacker->x < injured->x)
                ? (injured->x_velocity - 1.0)
                : (injured->x_velocity + 1.0);
            injured->x_velocity = injured->pic_x_gain;
            injured->z_accl = (attacker->z < injured->z)
                ? (injured->z_velocity - 0.5)
                : (injured->z_velocity + 0.5);
            injured->z_velocity = injured->z_accl;
            if (injured->y > -3) {
                injured->y = -2;
                injured->y_velocity = -6.0;
            }
            if (injured->y_velocity > -6.0) {
                injured->y_velocity -= 2.3;
                injured->y_accl = injured->y_velocity;
            }
        }
    }
}

} // namespace

// func_00417400: Check and resolve attack collision between attacker and injured entity
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

    uint32_t i_frame_id3 = injured->frame_id3;
    frame_t* a_frame3 = (attacker->frame_id3 < MAX_FRAMES) ? &attacker_file->frames[attacker->frame_id3] : a_frame4;
    frame_t* i_frame3 = (i_frame_id3 < MAX_FRAMES) ? &injured_file->frames[i_frame_id3] : i_frame4;

    for (uint32_t itr_id = 0; itr_id < a_frame4->itrs_size; ++itr_id) {
        itr_t* itr = &a_frame4->itrs[itr_id];

        for (uint32_t bdy_id = 0; bdy_id < i_frame4->bdys_size; ++bdy_id) {
            bdy_t* bdy = &i_frame4->bdys[bdy_id];

            uint32_t a_file_id = attacker_file->id;
            if (is_convertible_energy_ball(a_file_id) &&
                injured_file->id == FREEZE_BALL_DAT && itr->kind != ITR_FORCEFIELD) {
                break;
            }

            if (itr->kind == ITR_CATCH && injured_file->type != TYPE_CHARACTER) {
                break;
            }

            if (itr->kind == ITR_NORMAL_ATTACK) {
                if (itr->effect == EFFECT_SHINING && injured_file->type == TYPE_CHARACTER) {
                    break;
                }
                if (itr->effect == EFFECT_FIRE_NO_SOUND &&
                    (injured_file->type != TYPE_CHARACTER ||
                     i_frame3->state == 18 || i_frame3->state == 19)) {
                    break;
                }
                if (itr->effect == EFFECT_FIRE_JULIAN && (i_frame3->state == 18 || i_frame3->state == 19)) {
                    break;
                }
                if (itr->effect == EFFECT_FREEZE && (i_frame_id1 >= 200 && i_frame_id1 <= 203)) {
                    break;
                }
                if (itr->effect == EFFECT_FIRE && a_frame3->state == 19 && i_frame3->state == 18) {
                    break;
                }
            }

            if (itr->kind == ITR_HEAL && injured_file->type != TYPE_CHARACTER) {
                break;
            }

            if (injured->invincible_time != 0 && itr->kind != ITR_HEAL && itr->kind != ITR_FREEZE) {
                break;
            }

            if (itr->kind < 4 || itr->kind == ITR_SUPER_PUNCH ||
                (itr->kind == ITR_FORCEFIELD && injured_file->type == TYPE_CHARACTER) ||
                itr->kind == ITR_FLUTE || itr->kind == ITR_FLOAT ||
                itr->kind == ITR_WHIRLWIND_ICE || itr->kind == ITR_WHIRLWIND_WIND) {

                if (i_frame1->state != STATE_ICE && i_frame1->state != STATE_PICKED_CAUGHT &&
                    (injured_file->id != FREEZE_COLUMN_DAT ||
                     (attacker_file->id == FREEZE_COLUMN_DAT && (i_frame_id1 % 10 != 5 || a_frame_id1 % 10 != 0)))) {

                    if (attacker->team == injured->team && attacker->team != 0 && itr->kind != ITR_HEAL &&
                        (a_frame1->state != STATE_BURNING || (itr->effect == EFFECT_FIRE_JULIAN || itr->effect == EFFECT_FIRE_EXPLODE)) &&
                        (attacker_file->type != TYPE_CHARACTER || injured_file->type != TYPE_ATTACK ||
                         attacker->facing == injured->facing) &&
                        (injured_file->type != TYPE_LIGHT_WEAPON && injured_file->type != TYPE_HEAVY_WEAPON &&
                         injured_file->type != TYPE_THROW_WEAPON && injured_file->type != TYPE_DRINK)) {
                        break;
                    }
                }
            }

            if (itr->kind == ITR_WEAPON_STRENGTH) {
                int32_t h_id = attacker->holder_id;
                if (h_id >= 0 && h_id < static_cast<int32_t>(MAX_OBJECTS) && is_object_exists[h_id]) {
                    object_t* holder = objects[h_id];
                    if (holder && holder->team == injured->team && holder->team != 0 &&
                        i_frame1->state != STATE_ICE &&
                        (injured_file->type != TYPE_LIGHT_WEAPON && injured_file->type != TYPE_HEAVY_WEAPON &&
                         injured_file->type != TYPE_THROW_WEAPON && injured_file->type != TYPE_DRINK) &&
                        (injured_file->id != FREEZE_COLUMN_DAT ||
                         (attacker_file->id == FREEZE_COLUMN_DAT && (i_frame_id1 % 10 != 5 || holder->frame_id1 % 10 != 0)))) {
                        break;
                    }
                }
            }

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

            int32_t zwidth = (itr->zwidth != 0) ? static_cast<int32_t>(itr->zwidth) : 15;
            int32_t diff_z = std::abs(attacker->z - injured->z);
            if (diff_z >= zwidth) {
                continue;
            }

            if (!is_itr_bdy_overlap(bdy_left, bdy_top, bdy->w, bdy->h,
                                    itr_left, itr_top, itr->w, itr->h)) {
                continue;
            }

            bool hit_fail = false;
            if (i_frame1->state == STATE_FALLING && itr->fall <= 40 &&
                itr->kind != ITR_FLUTE && itr->kind != ITR_FLOAT) {
                hit_fail = true;
            }

            if (mode == 1) {
                bool can_rescue = false;
                if ((attacker_file->type == TYPE_CHARACTER || attacker_file->id == HENRY_ARROW1_DAT ||
                     attacker_file->id == RUDOLF_WEAPON_DAT) && attacker->team != 5) {
                    can_rescue = true;
                }
                int32_t h_id = attacker->holder_id;
                if (attacker->weapon_type != 0 && h_id >= 0 && h_id < static_cast<int32_t>(MAX_OBJECTS) &&
                    is_object_exists[h_id]) {
                    object_t* holder = objects[h_id];
                    if (holder && holder->file->type == TYPE_CHARACTER && holder->team != 5) {
                        can_rescue = true;
                    }
                }
                if (bdy->kind >= 1000 && !can_rescue) {
                    hit_fail = true;
                }
            }

            if (itr->vrest != 0 || itr->kind == ITR_CATCH_INJURED || itr->kind == ITR_PICK_UP_WEAPON ||
                itr->kind == ITR_ROWING_PICK ||
                (i_frame4->state == 1004 && (attacker_file->type < 1 || attacker->weapon_type < 0)) ||
                hit_fail) {

                if (attacker->successful_attacks >= 20 || hit_fail) {
                    continue;
                }

                int32_t flag = 0;
                if (i_frame4->state == 1004 &&
                    (attacker_file->type < 1 || attacker->weapon_type < 0) &&
                    itr->kind != ITR_PICK_UP_WEAPON && itr->kind != ITR_ROWING_PICK && itr->kind != ITR_FLUTE) {
                    flag = 2;
                }

                if (itr->kind == ITR_CATCH_INJURED) {
                    int32_t dist_x = std::abs(attacker->x - injured->x);
                    if (dist_x < injured->vulnerable_distance ||
                        (dist_x == injured->vulnerable_distance && lf2_random(0x86, 2) == 0)) {
                        injured->vulnerable_distance = dist_x;
                    } else {
                        flag = 2;
                    }
                }

                if (itr->kind == ITR_THROWN &&
                    (attacker->thrown_injury != 0 || attacker->fall != 0) && flag != 2) {
                    flag = 1;
                }

                if (itr->kind == ITR_CATCH_INJURED &&
                    ((attacker->click_right && attacker->x < injured->x) ||
                     (attacker->click_left && injured->x <= attacker->x)) &&
                    i_frame1->state == STATE_FIRE) {
                    if (flag != 2) flag = 1;
                } else if (itr->kind != ITR_CATCH_INJURED && itr->kind != ITR_PICK_UP_WEAPON &&
                           itr->kind != ITR_ROWING_PICK) {
                    if (flag != 2) flag = 1;
                }

                if (itr->kind == ITR_PICK_UP_WEAPON) {
                    if (attacker->weapon_type == 0 && attacker->click_attack && !attacker->holding_attack &&
                        i_frame1->state == 1004 && flag != 2) {
                        flag = 1;
                    }
                    if (attacker->click_attack && !attacker->holding_attack &&
                        i_frame1->state == 2004 && flag != 2) {
                        flag = 1;
                    }
                }

                if ((itr->kind == ITR_ROWING_PICK && attacker->click_attack && !attacker->holding_attack &&
                     i_frame1->state == 1004 && flag != 2) || flag == 1) {

                    int32_t slot = attacker->successful_attacks;
                    attacker->injured_of_attack[slot] = static_cast<int32_t>(injured_id);
                    attacker->itr_of_attack[slot] = static_cast<uint8_t>(itr_id);
                    attacker->successful_attacks++;
                }
            } else {
                int32_t dist_x = attacker->x - injured->x;
                if (attacker->weapon_type < 0) {
                    int32_t h_id = attacker->holder_id;
                    if (static_cast<int32_t>(injured_id) != h_id && h_id >= 0 &&
                        h_id < static_cast<int32_t>(MAX_OBJECTS) && is_object_exists[h_id]) {
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

// 1:1 Lift of 0x0042E100: Full Combat Damage, Fall State, Knockback, Armor, Projectiles, Specials & Sparks
void global_t::attack_process(uint32_t attacker_id, int32_t counter_12)
{
    if (attacker_id >= MAX_OBJECTS || !is_object_exists[attacker_id]) {
        return;
    }

    object_t* attacker = objects[attacker_id];
    if (!attacker || !attacker->file || attacker->successful_attacks < 1) {
        return;
    }

    uint32_t a_frame_id4 = (attacker->frame_id4 < MAX_FRAMES) ? attacker->frame_id4 : attacker->frame_id1;
    if (a_frame_id4 >= MAX_FRAMES || attacker->frame_id1 >= MAX_FRAMES) {
        return;
    }
    const frame_t* a_frame4 = &attacker->file->frames[a_frame_id4];

    for (int32_t hit_idx = 0; hit_idx < attacker->successful_attacks && hit_idx < 20; ++hit_idx) {
        int32_t itr_idx = static_cast<int8_t>(attacker->itr_of_attack[hit_idx]);
        if (itr_idx < 0 || static_cast<uint32_t>(itr_idx) >= a_frame4->itrs_size || !a_frame4->itrs) {
            break;
        }

        int32_t injured_id = attacker->injured_of_attack[hit_idx];
        if (injured_id < 0 || injured_id >= static_cast<int32_t>(MAX_OBJECTS) || !objects[injured_id]) {
            continue;
        }

        object_t* injured = objects[injured_id];
        if (!injured->file || injured->frame_id1 >= MAX_FRAMES || injured->frame_id4 >= MAX_FRAMES) {
            continue;
        }

        if (static_cast<int8_t>(injured->vrest_of_objects[attacker_id]) > 0) {
            continue;
        }

        if (attacker->flag_eb != 0 && injured->file->type == TYPE_CHARACTER) {
            return;
        }

        const frame_t* inj_f4 = &injured->file->frames[injured->frame_id4];
        const frame_t* inj_f1 = &injured->file->frames[injured->frame_id1];
        if (inj_f4->cpoint.kind == 2) {
            int32_t c_id = injured->cpoint_caught;
            if (c_id >= 0 && c_id < static_cast<int32_t>(MAX_OBJECTS) && objects[c_id] &&
                objects[c_id]->cpoint_catcher == injured_id && objects[c_id]->file &&
                objects[c_id]->frame_id4 < MAX_FRAMES &&
                objects[c_id]->file->frames[objects[c_id]->frame_id4].cpoint.hurtable == 0) {
                continue;
            }
        }

        const itr_t& raw_itr = a_frame4->itrs[itr_idx];
        if (raw_itr.kind == ITR_NORMAL_ATTACK && raw_itr.effect == EFFECT_FIRE_JULIAN &&
            (inj_f1->state == STATE_BURNING || inj_f1->state == 19)) {
            return;
        }

        itr_t eff = raw_itr;
        if (raw_itr.kind == ITR_WEAPON_STRENGTH && attacker->weapon_type < 0) {
            int32_t h_id = attacker->holder_id;
            if (h_id >= 0 && h_id < static_cast<int32_t>(MAX_OBJECTS) && objects[h_id] &&
                objects[h_id]->file && objects[h_id]->weapon_id == static_cast<int32_t>(attacker_id)) {
                object_t* holder = objects[h_id];
                uint32_t hf = (holder->frame_id4 < MAX_FRAMES) ? holder->frame_id4 : holder->frame_id1;
                if (hf < MAX_FRAMES) {
                    uint32_t atk_idx = holder->file->frames[hf].wpoint.attacking;
                    if (atk_idx > 0 && atk_idx <= 4 && h_id != injured_id) {
                        const itr_t& src = attacker->file->attacking_itrs[atk_idx];
                        eff.kind = 0;
                        eff.dvx = src.dvx;
                        eff.dvy = src.dvy;
                        eff.fall = src.fall;
                        eff.arest = src.arest;
                        eff.vrest = src.vrest;
                        eff.respond = src.respond;
                        eff.effect = src.effect;
                        eff.catching_act_1 = src.catching_act_1;
                        eff.catching_act_2 = src.catching_act_2;
                        eff.caught_act_1 = src.caught_act_1;
                        eff.caught_act_2 = src.caught_act_2;
                        eff.bdefend = src.bdefend;
                        eff.injury = src.injury;
                        eff.zwidth = src.zwidth;
                        eff._unknown4C = src._unknown4C;
                    }
                }
            }
        }

        if (static_cast<int32_t>(attacker->thrown_injury) > 0 && eff.kind == ITR_THROWN) {
            eff.kind = ITR_NORMAL_ATTACK;
            if ((attacker->x_velocity > 0.0 && attacker->facing == FACING_LEFT) ||
                (attacker->x_velocity < 0.0 && attacker->facing == FACING_RIGHT)) {
                eff.dvx = -eff.dvx;
            }
        }

        // Force victim to drop heavy weapon on normal hit
        if (injured->weapon_type == 2 && eff.kind == ITR_NORMAL_ATTACK) {
            int32_t wid = injured->weapon_id;
            if (wid >= 0 && wid < static_cast<int32_t>(MAX_OBJECTS) && objects[wid]) {
                object_t* w = objects[wid];
                if (w->holder_id == injured_id && w->weapon_type == -2) {
                    attacker->vrest_of_objects[wid] = 45;
                    injured->weapon_type = 0;
                    injured->vrest_of_objects[wid] = 30;
                    w->weapon_type = 0;
                    w->frame_id1 = static_cast<uint32_t>(lf2_random(0xec, 6));
                    w->y_velocity = -1.0;
                }
            }
        }

        if (injured->file->type == TYPE_HEAVY_WEAPON) {
            eff.dvx /= 2;
            eff.dvy /= 2;
        }

        int32_t is_bleed = 0;
        if (eff.kind == ITR_FORCEFIELD &&
            (injured->file->type == TYPE_CHARACTER ||
             inj_f1->state == 1002 || inj_f1->state == 2000)) {
            eff.kind = ITR_NORMAL_ATTACK;
            if (injured->file->type == TYPE_CHARACTER) {
                attacker->hp = 0;
            }
        }

        if (eff.kind == ITR_NORMAL_ATTACK) {
            if (is_defended_hit(attacker, injured, inj_f1, inj_f4, eff) &&
                injured->file->type == TYPE_CHARACTER) {
                apply_defended_hit(this, attacker, attacker_id, injured, eff);
            } else {
                if (!apply_plain_hit(this, attacker, attacker_id, injured, injured_id, eff, is_bleed)) {
                    return;
                }
            }
            record_hit_spark(this, attacker, attacker_id, injured, injured_id, eff, is_bleed);
        } else {
            apply_non_zero_itr(this, attacker, attacker_id, injured, injured_id, eff, counter_12);
        }
    }
}

void global_t::process_all_attacks(uint32_t mode, int32_t counter_12)
{
    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!is_object_exists[i] || !objects[i]) continue;
        objects[i]->successful_attacks = 0;
        objects[i]->attackable_distance = 1000;
        objects[i]->vulnerable_distance = 1000;
        objects[i]->flag_eb = 0;
    }

    world_step_collisions(this, mode);

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (is_object_exists[i] && objects[i] && objects[i]->file &&
            objects[i]->file->type == TYPE_CHARACTER) {
            attack_process(i, counter_12);
        }
    }

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (is_object_exists[i] && objects[i] && objects[i]->file &&
            objects[i]->file->type > 0) {
            attack_process(i, counter_12);
        }
    }

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (is_object_exists[i] && objects[i]) {
            objects[i]->successful_attacks = 0;
        }
    }
}

int32_t global_t::spawn_projectile(uint32_t owner_id, uint32_t file_id, int32_t x, int32_t y, int32_t z, double dvx, double dvy, uint8_t facing)
{
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

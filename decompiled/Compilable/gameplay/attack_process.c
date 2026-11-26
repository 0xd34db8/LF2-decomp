#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdlib.h>

/*
 * Virtual Address: 0x0042E100
 * Function: lf2_attack_process / FUN_0042e100
 * Calling Convention: __thiscall (ECX = global_t*, param_1 = attacker slot index)
 *
 * Description:
 *   Clean 64-bit-safe 1:1 C11 translation of the combat attack processor.
 *   Resolves damage, armor defense, knockdown fall states, knockback impulses,
 *   projectile conversions/reflections, weapon drops/throws, catch grabs,
 *   heal/forcefield/whirlwind ITRs, and hit-spark records.
 */

static object_t *resolve_credit_owner(global_t *global, object_t *attacker)
{
    if (attacker->owner >= 0 && attacker->owner < MAX_OBJECTS &&
        global->objects[attacker->owner] != NULL) {
        return global->objects[attacker->owner];
    }
    return attacker;
}

static bool is_convertible_energy_ball(uint32_t fid)
{
    return (fid == ID_JOHN_BALL_DAT || fid == ID_DEEP_BALL_DAT ||
            fid == ID_DENNIS_BALL_DAT || fid == ID_WOODY_BALL_DAT ||
            fid == ID_DAVIS_BALL_DAT || fid == ID_DENNIS_CHASE_DAT ||
            fid == ID_JACK_BALL_DAT);
}

static void trigger_weapon_item_sound(int32_t world_x, int32_t sound_id, uint32_t sound_tag)
{
    if (sound_id >= 0) {
        FUN_00416fb0(world_x, sound_id);
    } else if (sound_tag != 0) {
        FUN_00416fb0(world_x, (int32_t)sound_tag);
    }
}

static void apply_catch_grab(object_t *attacker, int32_t attacker_id,
                             object_t *injured, int32_t injured_id,
                             const itr_t *eff)
{
    injured->x_velocity = 0.0;
    attacker->x_velocity = 0.0;
    attacker->facing = (injured->x < attacker->x) ? FACING_LEFT : FACING_RIGHT;
    injured->facing = (uint8_t)(1U - attacker->facing);

    uint32_t c_act = (eff->catching_act1 < MAX_FRAMES) ? eff->catching_act1 : 0;
    uint32_t v_act = (eff->caught_act1 < MAX_FRAMES) ? eff->caught_act1 : 0;
    attacker->frame_id1 = c_act;
    injured->frame_id1 = v_act;

    const frame_t *af = &attacker->file->frames[c_act];
    const frame_t *vf = &injured->file->frames[v_act];
    int32_t att_cx = af->cpoint.x;
    int32_t inj_cx = vf->cpoint.x;

    attacker->x_position = (double)attacker->x;
    attacker->y_position = (double)attacker->y;

    if (attacker->facing == FACING_RIGHT) {
        injured->x_position = (double)((attacker->x - af->centerx - vf->centerx) + inj_cx + att_cx);
    } else {
        injured->x_position = (double)((af->centerx + vf->centerx + attacker->x - inj_cx) - att_cx);
    }
    injured->y_position = (double)((vf->centery - af->centery) + attacker->y);

    double half_shift = ((double)injured->x - injured->x_position) * 0.5;
    injured->x_position += half_shift;
    attacker->x_position += half_shift;
    injured->x = (int32_t)injured->x_position;
    attacker->x = (int32_t)attacker->x_position;

    attacker->cpoint_catcher = injured_id;
    injured->cpoint_caught = attacker_id;
    attacker->cpoint_hurtable = 300;
    injured->fall = 0;
}

static bool should_defend_with_armor(const object_t *attacker, const object_t *injured,
                                     const frame_t *inj_f1, const itr_t *eff)
{
    uint32_t inj_f4_id = (injured->frame_id4 < MAX_FRAMES) ? injured->frame_id4 : injured->frame_id1;
    uint32_t inj_s4 = injured->file->frames[inj_f4_id].state;
    if (eff->bdefend == 100 || inj_s4 == 8 || inj_s4 == 11 || inj_s4 == 12 ||
        inj_s4 == 13 || inj_s4 == 14 || inj_s4 == 16 || inj_s4 == 18) {
        return false;
    }

    uint32_t inj_fid = injured->file->id;
    uint32_t att_fid = attacker->file->id;
    bool elem_or_pierce = (eff->effect / 10 == 2 || eff->effect / 10 == 3 ||
                           eff->effect == 2 || eff->effect == 3 ||
                           att_fid == ID_JOHN_BISCUIT_DAT || att_fid == ID_HENRY_ARROW2_DAT);

    if (inj_fid == ID_KNIGHT_DAT && injured->bdefend < 16 && !elem_or_pierce) {
        return true;
    }
    if (inj_fid == ID_LOUIS_DAT && injured->bdefend < 2 && !elem_or_pierce &&
        (injured->frame_id1 < 20 || inj_f1->state == 5 || inj_f1->state == 4 || inj_f1->state == 7)) {
        return true;
    }
    if (inj_fid == ID_JULIAN_DAT && injured->bdefend <= 15 &&
        att_fid != ID_JOHN_BISCUIT_DAT && att_fid != ID_HENRY_ARROW2_DAT) {
        return true;
    }
    return false;
}

static bool is_defended_hit(const object_t *attacker, const object_t *injured,
                            const frame_t *inj_f1, const frame_t *inj_f4, const itr_t *eff)
{
    if (should_defend_with_armor(attacker, injured, inj_f1, eff)) {
        return true;
    }

    uint32_t att_fid = attacker->file->id;
    if (inj_f4->state == STATE_DEFENDING && (int32_t)eff->bdefend < 61 &&
        (attacker->facing != injured->facing || eff->dvx < 0 ||
         att_fid == ID_BOOMERANG_DAT || att_fid == ID_JAN_CHASE_DAT ||
         att_fid == ID_FIRZEN_CHASEF_DAT || att_fid == ID_FIRZEN_CHASEI_DAT) &&
        injured->hp > 0) {
        return true;
    }
    return false;
}

static void apply_weapon_rebound_and_stick_boost(object_t *attacker, object_t *injured, const itr_t *eff)
{
    double dvx_d = (double)eff->dvx;
    double scaled_vx = (injured->x_velocity < 0.0)
        ? -(injured->x_velocity * 0.55)
        : (injured->x_velocity * 0.55);

    if (scaled_vx < dvx_d ||
        (attacker->facing == FACING_RIGHT && injured->pic_x_gain > 0.0) ||
        (attacker->facing == FACING_LEFT && injured->pic_x_gain < 0.0)) {
        if (attacker->facing == FACING_RIGHT) injured->pic_x_gain += dvx_d;
        if (attacker->facing == FACING_LEFT) injured->pic_x_gain -= dvx_d;
    } else if ((attacker->facing == FACING_LEFT && injured->x_velocity > 0.0) ||
               (attacker->facing == FACING_RIGHT && injured->x_velocity < 0.0)) {
        injured->pic_x_gain = -(injured->x_velocity * 0.55);
    }

    if (attacker->file->id == ID_STICK_DAT && attacker->weapon_type < 0) {
        injured->pic_x_gain *= 2.5;
        FUN_00417090(injured->x, 13);
        if (injured->pic_x_gain > 0.0 && injured->pic_x_gain < 10.0) injured->pic_x_gain = 10.0;
        if (injured->pic_x_gain < 0.0 && injured->pic_x_gain > -10.0) injured->pic_x_gain = -10.0;
    }
}

static void apply_struck_projectile_reaction(global_t *global, object_t *attacker,
                                             int32_t attacker_id, object_t *injured)
{
    const frame_t *att_f1 = &attacker->file->frames[attacker->frame_id1];
    const frame_t *inj_f1 = &injured->file->frames[injured->frame_id1];
    uint32_t inj_state = inj_f1->state;
    uint32_t att_state = att_f1->state;

    if (inj_state != 3005 && (inj_state != 3006 || att_state == 3005)) {
        if (attacker->weapon_type < 0 && attacker->holder_id >= 0 &&
            attacker->holder_id < MAX_OBJECTS && global->objects[attacker->holder_id]) {
            object_t *holder = global->objects[attacker->holder_id];
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
        if (att_fid == ID_FREEZE_BALL_DAT && is_convertible_energy_ball(inj_fid)) {
            injured->team = attacker->team;
            injured->owner = attacker->owner;
            injured->file = attacker->file;
            injured->frame_id1 = 40;
            injured->frame_id2 = 40;
            injured->frame_id3 = 40;
        } else {
            if ((attacker->file->type == TYPE_CHARACTER || attacker->weapon_type < 0) &&
                att_f1->itrs_size > 0 && att_f1->itrs &&
                att_f1->itrs[0].effect != EFFECT_FIRE && att_f1->itrs[0].effect != EFFECT_FLAME) {
                injured->frame_id1 = 30;
                if (att_fid == ID_FREEZE_DAT && is_convertible_energy_ball(inj_fid)) {
                    for (uint32_t k = 0; k < MAX_FILES; ++k) {
                        if (global->files[k] && global->files[k]->id == ID_FREEZE_BALL_DAT) {
                            injured->file = global->files[k];
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
                injured->move_counter = (uint32_t)attacker->holder_id;
                if (att_fid == ID_ICE_SWORD_DAT && is_convertible_energy_ball(inj_fid) &&
                    attacker->holder_id >= 0 && attacker->holder_id < MAX_OBJECTS &&
                    global->objects[attacker->holder_id]) {
                    object_t *holder = global->objects[attacker->holder_id];
                    for (uint32_t k = 0; k < MAX_FILES; ++k) {
                        if (global->files[k] && global->files[k]->id == ID_FREEZE_BALL_DAT) {
                            injured->file = global->files[k];
                            injured->frame_id2 = injured->frame_id1;
                            injured->frame_id3 = injured->frame_id1;
                            break;
                        }
                    }
                    injured->team = holder->team;
                    injured->owner = holder->owner;
                }
            } else {
                injured->move_counter = (uint32_t)attacker_id;
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
        attacker->holder_id < MAX_OBJECTS && global->objects[attacker->holder_id]) {
        if (global->objects[attacker->holder_id]->shaking > 0) {
            global->objects[attacker->holder_id]->shaking = -global->objects[attacker->holder_id]->shaking;
        }
    } else if (attacker->shaking > 0) {
        attacker->shaking = -attacker->shaking;
    }
}

static void record_hit_spark(global_t *global,
                             object_t *attacker, uint32_t attacker_id,
                             object_t *injured, int32_t injured_id,
                             const itr_t *eff, int32_t is_bleed)
{
    int32_t spark_owner_idx = injured_id;
    if (injured->z <= attacker->z && global->is_object_exists[attacker_id] != 0) {
        if (injured->z < attacker->z || injured_id < (int32_t)attacker_id) {
            spark_owner_idx = (int32_t)attacker_id;
        }
    }
    object_t *so = global->objects[spark_owner_idx];
    if (!so || so->ai_vars[0] < 0 || so->ai_vars[0] >= 9) return;

    int32_t idx = so->ai_vars[0];
    so->ai_vars[0] = idx + 1;
    so->ai_vars[21 + idx] = is_bleed * 20 + ((eff->fall < 61) ? 10 : 0);

    const frame_t *att_f1 = &attacker->file->frames[attacker->frame_id1];
    int32_t sx;
    if (attacker->facing == FACING_RIGHT) {
        sx = (attacker->x - att_f1->centerx) + eff->w + eff->x;
        if (injured->x < sx) sx = injured->x;
    } else {
        sx = ((att_f1->centerx - eff->w) - eff->x) + attacker->x;
        if (sx < injured->x) sx = injured->x;
    }

    int32_t sy = (eff->h / 2 + attacker->y + eff->y) - att_f1->centery;
    int32_t min_y = injured->y - att_f1->centery;
    if (sy < min_y || injured->y < sy) {
        int32_t clamp_y = (sy < min_y) ? min_y : injured->y;
        sy = (sy + clamp_y) / 2;
    }

    so->ai_vars[1 + idx] = sx + FUN_00417170(0, 9) - 4;
    so->ai_vars[11 + idx] = sy + attacker->z + FUN_00417170(0, 9) - 4;
}

static bool apply_plain_hit(global_t *global,
                            object_t *attacker, uint32_t attacker_id,
                            object_t *injured, int32_t injured_id,
                            const itr_t *eff, int32_t *out_is_bleed)
{
    injured->bdefend = 45;
    uint32_t injured_fid = injured->file->id;
    const frame_t *inj_f1 = &injured->file->frames[injured->frame_id1];
    const frame_t *inj_f3 = (injured->frame_id3 < MAX_FRAMES)
        ? &injured->file->frames[injured->frame_id3]
        : inj_f1;
    const frame_t *inj_f4 = &injured->file->frames[injured->frame_id4];
    const frame_t *att_f1 = &attacker->file->frames[attacker->frame_id1];

    if (injured_fid == ID_CRIMINAL_DAT) {
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
        int32_t dmg = eff->injury;
        if (injured->armor_multiplier > 0) {
            dmg = (dmg * 100) / injured->armor_multiplier;
        }
        object_t *credit = resolve_credit_owner(global, attacker);
        if (injured->hp > 0 && injured->hp <= dmg &&
            injured_type == TYPE_CHARACTER && injured->clone == -1) {
            credit->kills++;
            if (credit->player_index >= 0 && credit->player_index < 8) {
                DAT_00451b60_arr[credit->player_index]++;
            }
        }
        injured->hp -= dmg;
        injured->dark_hp -= dmg / 3;
        injured->hp_lost += dmg;
        if (injured_type == TYPE_CHARACTER && injured->clone == -1) {
            credit->total_attack += dmg;
            if (credit->player_index >= 0 && credit->player_index < 8) {
                DAT_00451b68_arr[credit->player_index] += dmg;
            }
        }
    }

    if (injured->hp < 1 || eff->effect == EFFECT_SHINING) {
        injured->fall = 80;
    }

    if (injured_type == TYPE_LIGHT_WEAPON || injured_type == TYPE_HEAVY_WEAPON ||
        injured_type == TYPE_THROW_WEAPON || injured_type == TYPE_DRINK) {
        injured->weapon_hp -= eff->injury;
        if (eff->bdefend == 100) {
            injured->weapon_hp = -1;
        }
    }

    if (injured_type != TYPE_HEAVY_WEAPON || eff->fall > 40) {
        injured->attacks++;
    }

    injured->fall += (eff->fall == 0) ? 20 : eff->fall;

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
        trigger_weapon_item_sound(attacker->x, attacker->file->weapon_broken_sound_id, attacker->file->weapon_broken_sound);
    }
    if (injured_type == TYPE_CHARACTER) {
        if (eff->effect == EFFECT_PUNCH) {
            FUN_00417090(injured->x, (injured->fall == 80) ? 2 : 0);
        } else if (eff->effect == EFFECT_BLEED) {
            *out_is_bleed = 1;
            FUN_00417090(injured->x, (injured->fall == 80) ? 12 : 11);
            FUN_00417090(injured->x, (injured->fall == 80) ? 2 : 0);
        }
    } else if (injured_type > 0) {
        trigger_weapon_item_sound(injured->x, injured->file->weapon_hit_sound_id, injured->file->weapon_hit_sound);
    }

    if (injured->fall == 80 && injured->x_velocity > -5.0 &&
        injured->x_velocity < 5.0 && eff->dvx == 0) {
        if (att_f1->state == 2000) {
            injured->pic_x_gain += 5.0;
        } else {
            injured->pic_x_gain += (attacker->facing == FACING_RIGHT) ? 5.0 : -5.0;
        }
    } else if (att_f1->state == 2000) {
        if (attacker->x < injured->x) injured->pic_x_gain += (double)eff->dvx;
        else injured->pic_x_gain -= (double)eff->dvx;
    } else if (injured_type == TYPE_THROW_WEAPON || injured_type == TYPE_DRINK) {
        apply_weapon_rebound_and_stick_boost(attacker, injured, eff);
    } else if (eff->effect == 22 || eff->effect == 23) {
        if (injured->x <= attacker->x) injured->pic_x_gain += (double)eff->dvx;
        else injured->pic_x_gain -= (double)eff->dvx;
    } else {
        if (attacker->facing == FACING_RIGHT) injured->pic_x_gain += (double)eff->dvx;
        else injured->pic_x_gain -= (double)eff->dvx;
    }

    if (att_f1->state == 3000 &&
        (injured_type == TYPE_CHARACTER ||
         attacker->file->id != ID_FREEZE_BALL_DAT ||
         (!is_convertible_energy_ball(injured_fid) &&
          !(injured_fid == ID_FREEZE_BALL_DAT && injured->frame_id1 != 40)))) {
        attacker->frame_id1 = 10;
        attacker->wait_counter = 0;
        attacker->x_velocity = 0.0;
        attacker->z_velocity = (double)attacker->file->frames[10].dvz;
    }

    if (injured->fall == 80) {
        if (eff->dvy == 0) {
            if ((injured_type != TYPE_HEAVY_WEAPON && injured_type != TYPE_ATTACK) || eff->fall > 40) {
                injured->y_accl -= 7.0;
            }
        } else {
            if ((injured_type != TYPE_HEAVY_WEAPON && injured_type != TYPE_ATTACK) || eff->fall > 40) {
                injured->y_accl += (double)eff->dvy;
            }
            if ((int32_t)((double)injured->y + injured->y_accl) > 0) {
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
            injured->weapon_id < MAX_OBJECTS &&
            global->objects[injured->weapon_id] &&
            injured_id == global->objects[injured->weapon_id]->holder_id) {
            attacker->vrest_of_objects[injured->weapon_id] = 45;
            injured->vrest_of_objects[injured->weapon_id] = 30;
        }
    }

    if (attacker->shaking >= 0) attacker->shaking = 3;
    injured->shaking = -3;

    attacker->arest = (eff->arest < 4 && eff->vrest == 0) ? 4 : (int32_t)eff->arest;
    if (eff->vrest > 0) {
        injured->vrest_of_objects[attacker_id] = (uint8_t)eff->vrest;
    }

    if (inj_f4->cpoint.kind == 2 && injured->fall != 80 && inj_f4->cpoint.fronthurtact != 0) {
        int32_t c_id = injured->cpoint_caught;
        if (c_id >= 0 && c_id < MAX_OBJECTS && global->objects[c_id] &&
            global->objects[c_id]->cpoint_catcher == injured_id) {
            int32_t h_act = (injured->facing == attacker->facing)
                ? inj_f4->cpoint.backhurtact
                : inj_f4->cpoint.fronthurtact;
            if (h_act >= 0 && h_act < MAX_FRAMES) {
                injured->frame_id1 = (uint32_t)h_act;
            }
        }
    }

    if (injured->fall == 80) injured->fall = 0;

    if (attacker->weapon_type < 0 && attacker->holder_id >= 0 &&
        attacker->holder_id < MAX_OBJECTS && global->objects[attacker->holder_id]) {
        global->objects[attacker->holder_id]->shaking = attacker->shaking;
    }

    if (att_f1->state == 1002) {
        attacker->frame_id1 = (uint32_t)FUN_00417170(0xee, 16);
        attacker->x_velocity = -(injured->pic_x_gain * 0.5);
        attacker->y_velocity = -4.0;
        if (attacker->file->type == TYPE_THROW_WEAPON && injured_type == TYPE_THROW_WEAPON) {
            attacker->pic_x_gain = -injured->pic_x_gain;
        }
    }

    if (injured_type == TYPE_LIGHT_WEAPON) {
        injured->flag_eb = 1;
        injured->frame_id1 = (uint32_t)FUN_00417170(0xef, 16);
        injured->team = attacker->team;
    }
    if (injured_type == TYPE_THROW_WEAPON || injured_type == TYPE_DRINK) {
        attacker->vrest_of_objects[injured_id] = 30;
        injured->flag_eb = 1;
        injured->frame_id1 = (uint32_t)FUN_00417170(0xf0, 16);
        injured->team = attacker->team;
    }
    if (injured_type == TYPE_HEAVY_WEAPON) {
        injured->flag_eb = 1;
        uint8_t h_vrest = (eff->fall < 41 && eff->effect != EFFECT_SHINING) ? 3 : 19;
        if (attacker->weapon_type == -2 && attacker->holder_id >= 0 &&
            attacker->holder_id < MAX_OBJECTS && global->objects[attacker->holder_id]) {
            global->objects[attacker->holder_id]->vrest_of_objects[injured_id] = h_vrest;
        } else if (attacker->file->type != TYPE_HEAVY_WEAPON) {
            attacker->vrest_of_objects[injured_id] = h_vrest;
        }
        injured->facing = attacker->facing;
        if (eff->fall < 41 && injured->y >= 0 && eff->effect != EFFECT_SHINING) {
            injured->frame_id1 = 20;
        } else {
            injured->frame_id1 = (uint32_t)FUN_00417170(0xf1, 6);
        }
        injured->team = attacker->team;
    }

    if (attacker->file->id == ID_HENRY_ARROW1_DAT && injured_type == TYPE_CHARACTER) {
        global->is_object_exists[attacker_id] = 0;
    }
    if (attacker->file->id == ID_JOHN_BISCUIT_DAT && injured_type == TYPE_CHARACTER) {
        attacker->hp = 0;
    }

    if (injured_type == TYPE_ATTACK) {
        apply_struck_projectile_reaction(global, attacker, (int32_t)attacker_id, injured);
    }

    if ((eff->effect == EFFECT_COLUMN || eff->effect == EFFECT_FREEZE) &&
        injured_type == TYPE_CHARACTER && inj_f3->state != STATE_ICE) {
        injured->frame_id1 = 200;
        injured->wait_counter = 0;
        FUN_00417090(injured->x, 14);
    }
    if ((eff->effect == EFFECT_FIRE || eff->effect == EFFECT_FIREN_EXPLODE || eff->effect == EFFECT_JULIAN_EXPLODE ||
         (eff->effect == EFFECT_FLAME && inj_f3->state != STATE_BURNING)) &&
        injured_type == TYPE_CHARACTER) {
        injured->frame_id1 = 203;
        injured->wait_counter = 0;
        FUN_00417090(injured->x, 16);
        injured->facing = (injured->pic_x_gain < 0.0) ? FACING_RIGHT : FACING_LEFT;
    }
    if (eff->effect == 23) {
        FUN_00417090(injured->x, 16);
    }

    return true;
}

static void apply_defended_hit(global_t *global,
                             object_t *attacker, uint32_t attacker_id,
                             object_t *injured,
                             const itr_t *eff)
{
    const frame_t *att_f1 = &attacker->file->frames[attacker->frame_id1];
    const frame_t *inj_f4 = &injured->file->frames[injured->frame_id4];
    uint32_t injured_fid = injured->file->id;
    uint32_t injured_type = injured->file->type;

    if (attacker->file->type == TYPE_ATTACK) {
        trigger_weapon_item_sound(attacker->x, attacker->file->weapon_broken_sound_id, attacker->file->weapon_broken_sound);
    } else if (injured_fid == ID_KNIGHT_DAT || injured_fid == ID_LOUIS_DAT) {
        FUN_00417090(injured->x, 17);
    } else {
        FUN_00417090(injured->x, 1);
    }

    if (injured_type != TYPE_DRINK) {
        int32_t scaled = eff->injury;
        if (injured->armor_multiplier > 0) {
            scaled = (scaled * 100) / injured->armor_multiplier;
        }
        int32_t dmg10 = scaled / 10;
        object_t *credit = resolve_credit_owner(global, attacker);
        if (injured->hp > 0 && injured->hp <= dmg10 &&
            injured_type == TYPE_CHARACTER && injured->clone == -1) {
            credit->kills++;
            if (credit->player_index >= 0 && credit->player_index < 8) {
                DAT_00451b60_arr[credit->player_index]++;
            }
        }
        injured->hp -= dmg10;
        injured->dark_hp -= dmg10 / 3;
        injured->hp_lost += dmg10;
        if (injured_type == TYPE_CHARACTER && injured->clone == -1) {
            credit->total_attack += dmg10;
            if (credit->player_index >= 0 && credit->player_index < 8) {
                DAT_00451b68_arr[credit->player_index] += dmg10;
            }
        }
    }

    if (injured_type == TYPE_LIGHT_WEAPON || injured_type == TYPE_HEAVY_WEAPON ||
        injured_type == TYPE_THROW_WEAPON || injured_type == TYPE_DRINK) {
        injured->weapon_hp -= eff->injury;
        if (eff->bdefend == 100) injured->weapon_hp = -1;
    }

    if (injured->hp < 1) injured->fall = 80;

    injured->wait_counter = 0;
    injured->bdefend += (int32_t)eff->bdefend;
    injured->attacks++;
    attacker->shaking = 3;
    injured->shaking = -5;

    if (injured->y == 0) {
        if (injured->bdefend >= 31 && inj_f4->state == STATE_DEFENDING) {
            injured->frame_id1 = 112;
        } else if (injured->frame_id1 == 110) {
            injured->frame_id1 = 111;
        }

        if (injured->fall == 80 && injured->x_velocity > -3.0 &&
            injured->x_velocity < 3.0 && eff->dvx == 0) {
            if (att_f1->state == 2000) injured->pic_x_gain += (attacker->x < injured->x) ? 6.0 : -6.0;
            else injured->pic_x_gain += (attacker->facing == FACING_RIGHT) ? 3.0 : -3.0;
        } else if (att_f1->state == 2000) {
            if (injured->x <= attacker->x) injured->pic_x_gain -= (double)eff->dvx;
            else injured->pic_x_gain += (double)eff->dvx;
        } else if (eff->effect == 22 || eff->effect == 23) {
            if (injured->x <= attacker->x) injured->pic_x_gain += (double)eff->dvx;
            else injured->pic_x_gain -= (double)eff->dvx;
        } else {
            if (attacker->facing == FACING_RIGHT) injured->pic_x_gain += (double)(eff->dvx / 2);
            else injured->pic_x_gain -= (double)(eff->dvx / 2);
        }
    } else {
        if (injured->fall == 80 && injured->x_velocity > -6.0 &&
            injured->x_velocity < 6.0 && eff->dvx <= 5) {
            injured->pic_x_gain += (attacker->facing == FACING_RIGHT) ? 6.0 : -6.0;
        } else if (eff->effect == 22 || eff->effect == 23) {
            if (injured->x <= attacker->x) injured->pic_x_gain += (double)eff->dvx;
            else injured->pic_x_gain -= (double)eff->dvx;
        } else {
            if (attacker->facing == FACING_RIGHT) injured->pic_x_gain += (double)eff->dvx;
            else injured->pic_x_gain -= (double)eff->dvx;
        }
    }

    if (eff->arest < 4 && eff->vrest == 0) attacker->arest = 4;
    else attacker->arest = (eff->arest < 12) ? (int32_t)eff->arest : 12;

    if (eff->vrest > 0) {
        int32_t vr = (eff->vrest < 5) ? 4 : ((eff->vrest < 12) ? (int32_t)eff->vrest : 12);
        injured->vrest_of_objects[attacker_id] = (uint8_t)vr;
    }

    if (attacker->weapon_type < 0 && attacker->holder_id >= 0 &&
        attacker->holder_id < MAX_OBJECTS && global->objects[attacker->holder_id]) {
        global->objects[attacker->holder_id]->shaking = attacker->shaking;
    }

    if (att_f1->state == 1002) {
        attacker->frame_id1 = (uint32_t)FUN_00417170(0xf3, 16);
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

static void apply_non_zero_itr(global_t *global,
                               object_t *attacker, uint32_t attacker_id,
                               object_t *injured, int32_t injured_id,
                               const itr_t *eff)
{
    uint32_t kind = eff->kind;
    uint32_t injured_type = injured->file->type;

    if (kind == ITR_KIND_SUPER_PUNCH) {
        injured->can_hit = 3;
        return;
    }

    if (kind == ITR_KIND_CATCH_INJURED || kind == ITR_KIND_CATCH) {
        apply_catch_grab(attacker, (int32_t)attacker_id, injured, injured_id, eff);
        return;
    }

    if (kind == ITR_KIND_ROWING_PICK && attacker->weapon_type == 0) {
        attacker->weapon_type = 1;
        injured->weapon_type = -1;
        injured->team = attacker->team;
        attacker->weapon_id = injured_id;
        injured->holder_id = (int32_t)attacker_id;
        injured->owner = (int32_t)attacker_id;
        attacker->get_weapon_counter++;
        uint32_t inj_fid = injured->file->id;
        if (inj_fid == ID_KNIFE_DAT || inj_fid == ID_BOOMERANG_DAT) {
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

    if (kind == ITR_KIND_PICKUP_WEAPON) {
        if (injured_type == TYPE_LIGHT_WEAPON) {
            attacker->frame_id1 = 115;
            attacker->weapon_type = (injured->file->id == ID_KNIFE_DAT || injured->file->id == ID_BOOMERANG_DAT) ? 101 : 1;
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
        injured->holder_id = (int32_t)attacker_id;
        injured->owner = (int32_t)attacker_id;
        attacker->get_weapon_counter++;
        attacker->wait_counter = 0;
        return;
    }

    if (kind == ITR_KIND_HEAL) {
        injured->curing_hp = eff->injury + 1000;
        if (eff->dvx >= 0 && eff->dvx < MAX_FRAMES) {
            attacker->frame_id1 = (uint32_t)eff->dvx;
        }
        attacker->x_position = injured->x_position;
        attacker->z_position = injured->z_position + 1.0;
        return;
    }

    if (kind == ITR_KIND_FORCEFIELD) {
        if (injured_type == TYPE_ATTACK) {
            trigger_weapon_item_sound(injured->x, injured->file->weapon_broken_sound_id, injured->file->weapon_broken_sound);
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

    if (kind == ITR_KIND_FLUTE ||
        (kind == ITR_KIND_FLOAT && injured->thrown_injury < 0)) {
        if (injured_type == TYPE_CHARACTER) {
            injured->thrown_injury = -20;
            if (injured->clone == -1 && DAT_00450bd0 == 0) {
                object_t *credit = resolve_credit_owner(global, attacker);
                credit->total_attack += 11;
                if (credit->player_index >= 0 && credit->player_index < 8) {
                    DAT_00451b68_arr[credit->player_index] += 11;
                }
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
            if (inj_fid != ID_HENRY_ARROW1_DAT && inj_fid != ID_RUDOLF_WEAPON_DAT) {
                if (injured->file->frames[injured->frame_id1].state != 1000) injured->frame_id1 = 0;
                injured->pic_x_gain = injured->x_velocity / 1.07;
                injured->x_velocity = injured->pic_x_gain;
                injured->z_accl = injured->z_velocity / 1.07;
                injured->z_velocity = injured->z_accl;
                if (injured->y > -3) { injured->y = -2; injured->y_velocity = -6.0; }
                if (injured->y_velocity > -6.0) {
                    injured->y_velocity -= 3.0;
                    injured->y_accl = injured->y_velocity;
                }
            }
        } else if (injured_type == TYPE_HEAVY_WEAPON) {
            if (injured->file->frames[injured->frame_id1].state != 2000) injured->frame_id1 = 0;
            injured->pic_x_gain = injured->x_velocity / 1.07;
            injured->x_velocity = injured->pic_x_gain;
            injured->z_accl = injured->z_velocity / 1.07;
            injured->z_velocity = injured->z_accl;
            if (injured->y > -3) { injured->y = -2; injured->y_velocity = -6.0; }
            if (injured->y_velocity > -6.0) {
                injured->y_velocity -= 2.3;
                injured->y_accl = injured->y_velocity;
            }
        }
        return;
    }

    if (kind == ITR_KIND_FREEZE) {
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

    if (kind == ITR_KIND_FLY || kind == ITR_KIND_FREEZE) {
        if (injured_type == TYPE_CHARACTER) {
            if (kind == ITR_KIND_FREEZE) {
                int32_t dmg = eff->injury;
                if (injured->armor_multiplier > 0) dmg = (dmg * 100) / injured->armor_multiplier;
                object_t *credit = resolve_credit_owner(global, attacker);
                if (injured->hp > 0 && injured->hp <= dmg && injured->clone == -1) {
                    credit->kills++;
                    if (credit->player_index >= 0 && credit->player_index < 8) {
                        DAT_00451b60_arr[credit->player_index]++;
                    }
                }
                injured->hp -= dmg;
                injured->dark_hp -= dmg / 3;
                injured->hp_lost += dmg;
                if (injured->clone == -1) {
                    credit->total_attack += dmg;
                    if (credit->player_index >= 0 && credit->player_index < 8) {
                        DAT_00451b68_arr[credit->player_index] += dmg;
                    }
                }
                injured->frame_id1 = 200;
                injured->wait_counter = 0;
                FUN_00417090(injured->x, 14);
                if ((int32_t)eff->vrest > 0) {
                    injured->vrest_of_objects[attacker_id] = (uint8_t)eff->vrest;
                }
                if (injured->weapon_type == 2 && injured->weapon_id >= 0 &&
                    injured->weapon_id < MAX_OBJECTS && global->objects[injured->weapon_id]) {
                    int32_t wid = injured->weapon_id;
                    object_t *w = global->objects[wid];
                    if (w->holder_id == injured_id && w->weapon_type == -2) {
                        attacker->vrest_of_objects[wid] = 45;
                        injured->weapon_type = 0;
                        injured->vrest_of_objects[wid] = 30;
                        w->weapon_type = 0;
                        w->frame_id1 = (uint32_t)FUN_00417170(0xf4, 6);
                        w->y_velocity = -1.0;
                    }
                }
            }
            if (kind == 15) {
                injured->pic_x_gain = (injured->x <= attacker->x)
                    ? (injured->x_velocity + 1.0)
                    : (injured->x_velocity - 1.0);
                injured->x_velocity = injured->pic_x_gain;
                injured->z_accl = (attacker->z < injured->z)
                    ? (injured->z_velocity - 0.5)
                    : (injured->z_velocity + 0.5);
                injured->z_velocity = injured->z_accl;
                injured->frame_id1 = 182;
                if (injured->y > -3) { injured->y = -2; injured->y_velocity = -6.0; }
                if (injured->y_velocity > -6.0) {
                    injured->y_velocity -= 3.0;
                    injured->y_accl = injured->y_velocity;
                }
            }
        } else if (injured_type == TYPE_LIGHT_WEAPON || injured_type == TYPE_THROW_WEAPON ||
                   injured_type == TYPE_DRINK) {
            uint32_t inj_fid = injured->file->id;
            if (inj_fid != ID_HENRY_ARROW1_DAT && inj_fid != ID_RUDOLF_WEAPON_DAT) {
                if (injured->file->frames[injured->frame_id1].state != 1000) injured->frame_id1 = 0;
                injured->pic_x_gain = (attacker->x < injured->x)
                    ? (injured->x_velocity - 1.0)
                    : (injured->x_velocity + 1.0);
                injured->x_velocity = injured->pic_x_gain;
                injured->z_accl = (attacker->z < injured->z)
                    ? (injured->z_velocity - 0.5)
                    : (injured->z_velocity + 0.5);
                injured->z_velocity = injured->z_accl;
                if (injured->y > -3) { injured->y = -2; injured->y_velocity = -6.0; }
                if (injured->y_velocity > -6.0) {
                    injured->y_velocity -= 3.0;
                    injured->y_accl = injured->y_velocity;
                }
            }
        } else if (injured_type == TYPE_HEAVY_WEAPON) {
            if (injured->file->frames[injured->frame_id1].state != 2000) injured->frame_id1 = 0;
            injured->pic_x_gain = (attacker->x < injured->x)
                ? (injured->x_velocity - 1.0)
                : (injured->x_velocity + 1.0);
            injured->x_velocity = injured->pic_x_gain;
            injured->z_accl = (attacker->z < injured->z)
                ? (injured->z_velocity - 0.5)
                : (injured->z_velocity + 0.5);
            injured->z_velocity = injured->z_accl;
            if (injured->y > -3) { injured->y = -2; injured->y_velocity = -6.0; }
            if (injured->y_velocity > -6.0) {
                injured->y_velocity -= 2.3;
                injured->y_accl = injured->y_velocity;
            }
        }
    }
}

// FUNCTION: LF2 0x0042e100
void lf2_attack_process(global_t *global, int attacker_id)
{
    if (!global || attacker_id < 0 || attacker_id >= MAX_OBJECTS || !global->is_object_exists[attacker_id]) {
        return;
    }

    object_t *attacker = global->objects[attacker_id];
    if (!attacker || !attacker->file || attacker->successful_attacks < 1) {
        return;
    }

    uint32_t a_frame_id4 = (attacker->frame_id4 < MAX_FRAMES) ? attacker->frame_id4 : attacker->frame_id1;
    if (a_frame_id4 >= MAX_FRAMES || attacker->frame_id1 >= MAX_FRAMES) {
        return;
    }
    const frame_t *a_frame4 = &attacker->file->frames[a_frame_id4];

    for (int32_t hit_idx = 0; hit_idx < attacker->successful_attacks && hit_idx < 20; ++hit_idx) {
        int32_t itr_idx = (int8_t)attacker->itr_of_attack[hit_idx];
        if (itr_idx < 0 || (uint32_t)itr_idx >= a_frame4->itrs_size || !a_frame4->itrs) {
            break;
        }

        int32_t injured_id = attacker->injured_of_attack[hit_idx];
        if (injured_id < 0 || injured_id >= MAX_OBJECTS || !global->objects[injured_id]) {
            continue;
        }

        object_t *injured = global->objects[injured_id];
        if (!injured->file || injured->frame_id1 >= MAX_FRAMES || injured->frame_id4 >= MAX_FRAMES) {
            continue;
        }

        if ((int8_t)injured->vrest_of_objects[attacker_id] > 0) {
            continue;
        }

        if (attacker->flag_eb != 0 && injured->file->type == TYPE_CHARACTER) {
            return;
        }

        const frame_t *inj_f4 = &injured->file->frames[injured->frame_id4];
        const frame_t *inj_f1 = &injured->file->frames[injured->frame_id1];
        if (inj_f4->cpoint.kind == 2) {
            int32_t c_id = injured->cpoint_caught;
            if (c_id >= 0 && c_id < MAX_OBJECTS && global->objects[c_id] &&
                global->objects[c_id]->cpoint_catcher == injured_id && global->objects[c_id]->file &&
                global->objects[c_id]->frame_id4 < MAX_FRAMES &&
                global->objects[c_id]->file->frames[global->objects[c_id]->frame_id4].cpoint.hurtable == 0) {
                continue;
            }
        }

        const itr_t *raw_itr = &a_frame4->itrs[itr_idx];
        if (raw_itr->kind == ITR_KIND_NORMAL && raw_itr->effect == EFFECT_FIREN_EXPLODE &&
            (inj_f1->state == STATE_BURNING || inj_f1->state == STATE_FIRE)) {
            return;
        }

        itr_t eff = *raw_itr;
        if (raw_itr->kind == 5 && attacker->weapon_type < 0) {
            int32_t h_id = attacker->holder_id;
            if (h_id >= 0 && h_id < MAX_OBJECTS && global->objects[h_id] &&
                global->objects[h_id]->file && global->objects[h_id]->weapon_id == attacker_id) {
                object_t *holder = global->objects[h_id];
                uint32_t hf = (holder->frame_id4 < MAX_FRAMES) ? holder->frame_id4 : holder->frame_id1;
                if (hf < MAX_FRAMES) {
                    uint32_t atk_idx = holder->file->frames[hf].wpoint.attacking;
                    if (atk_idx > 0 && atk_idx <= 4 && h_id != injured_id) {
                        const itr_t *src = &attacker->file->attacking_itrs[atk_idx];
                        eff.kind = 0;
                        eff.dvx = src->dvx;
                        eff.dvy = src->dvy;
                        eff.fall = src->fall;
                        eff.arest = src->arest;
                        eff.vrest = src->vrest;
                        eff.respond = src->respond;
                        eff.effect = src->effect;
                        eff.catching_act1 = src->catching_act1;
                        eff.catching_act2 = src->catching_act2;
                        eff.caught_act1 = src->caught_act1;
                        eff.caught_act2 = src->caught_act2;
                        eff.bdefend = src->bdefend;
                        eff.injury = src->injury;
                        eff.zwidth = src->zwidth;
                        eff._unknown1 = src->_unknown1;
                    }
                }
            }
        }

        if (attacker->thrown_injury > 0 && eff.kind == ITR_KIND_THROWN) {
            eff.kind = ITR_KIND_NORMAL;
            if ((attacker->x_velocity > 0.0 && attacker->facing == FACING_LEFT) ||
                (attacker->x_velocity < 0.0 && attacker->facing == FACING_RIGHT)) {
                eff.dvx = -eff.dvx;
            }
        }

        if (injured->weapon_type == 2 && eff.kind == ITR_KIND_NORMAL) {
            int32_t wid = injured->weapon_id;
            if (wid >= 0 && wid < MAX_OBJECTS && global->objects[wid]) {
                object_t *w = global->objects[wid];
                if (w->holder_id == injured_id && w->weapon_type == -2) {
                    attacker->vrest_of_objects[wid] = 45;
                    injured->weapon_type = 0;
                    injured->vrest_of_objects[wid] = 30;
                    w->weapon_type = 0;
                    w->frame_id1 = (uint32_t)FUN_00417170(0xec, 6);
                    w->y_velocity = -1.0;
                }
            }
        }

        if (injured->file->type == TYPE_HEAVY_WEAPON) {
            eff.dvx /= 2;
            eff.dvy /= 2;
        }

        int32_t is_bleed = 0;
        if (eff.kind == ITR_KIND_FORCEFIELD &&
            (injured->file->type == TYPE_CHARACTER ||
             inj_f1->state == 1002 || inj_f1->state == 2000)) {
            eff.kind = ITR_KIND_NORMAL;
            if (injured->file->type == TYPE_CHARACTER) {
                attacker->hp = 0;
            }
        }

        if (eff.kind == ITR_KIND_NORMAL) {
            if (is_defended_hit(attacker, injured, inj_f1, inj_f4, &eff) &&
                injured->file->type == TYPE_CHARACTER) {
                apply_defended_hit(global, attacker, (uint32_t)attacker_id, injured, &eff);
            } else {
                if (!apply_plain_hit(global, attacker, (uint32_t)attacker_id, injured, injured_id, &eff, &is_bleed)) {
                    return;
                }
            }
            record_hit_spark(global, attacker, (uint32_t)attacker_id, injured, injured_id, &eff, is_bleed);
        } else {
            apply_non_zero_itr(global, attacker, (uint32_t)attacker_id, injured, injured_id, &eff);
        }
    }
}

void FUN_0042e100(int param_1)
{
    lf2_attack_process((global_t *)in_ECX, param_1);
}

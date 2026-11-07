#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x00417400
 * Function: lf2_does_attack_success / 3D AABB Hitbox Intersection
 * Calling Convention: __thiscall (ECX = global_t*)
 *
 * Description:
 *   Evaluates geometric overlap and physical compatibility between the attacker's
 *   active interaction boxes (itr) and the victim's bounding boxes (bdy).
 *   Applies invincibility checks, team immunity rules, freeze-column exceptions,
 *   and records successful hit candidates into attacker's hit registry.
 */

void lf2_does_attack_success(global_t *global, uint32_t attacker_id, uint32_t injured_id, uint32_t mode)
{
    if (!global || attacker_id >= MAX_OBJECTS || injured_id >= MAX_OBJECTS) return;
    if (!global->is_object_exists[attacker_id] || !global->is_object_exists[injured_id]) return;

    object_t *attacker = global->objects[attacker_id];
    object_t *injured  = global->objects[injured_id];
    if (!attacker || !injured || !attacker->file || !injured->file) return;

    file_t *attacker_file = attacker->file;
    file_t *injured_file  = injured->file;

    frame_t *attacker_frame1 = &attacker_file->frames[attacker->frame_id1];
    frame_t *attacker_frame3 = &attacker_file->frames[attacker->frame_id3];
    frame_t *attacker_frame4 = &attacker_file->frames[attacker->frame_id4];

    frame_t *injured_frame1  = &injured_file->frames[injured->frame_id1];
    frame_t *injured_frame3  = &injured_file->frames[injured->frame_id3];
    frame_t *injured_frame4  = &injured_file->frames[injured->frame_id4];

    for (uint32_t itr_id = 0; itr_id < attacker_frame4->itrs_size; itr_id++) {
        itr_t *itr = &attacker_frame4->itrs[itr_id];

        for (uint32_t bdy_id = 0; bdy_id < injured_frame4->bdys_size; bdy_id++) {
            bdy_t *bdy = &injured_frame4->bdys[bdy_id];
            uint32_t att_fid = attacker_file->id;
            uint32_t inj_fid = injured_file->id;
            uint32_t kind    = itr->kind;
            int32_t  eff     = itr->effect;

            // 1. Freeze ball (209) cannot be attacked by standard projectiles unless forcefield (kind 9)
            if ((att_fid == ID_JOHN_BALL_DAT ||
                 att_fid == ID_DEEP_BALL_DAT ||
                 att_fid == ID_DENNIS_BALL_DAT ||
                 att_fid == ID_WOODY_BALL_DAT ||
                 att_fid == ID_DAVIS_BALL_DAT ||
                 att_fid == ID_DENNIS_CHASE_DAT ||
                 att_fid == ID_JACK_BALL_DAT) &&
                inj_fid == ID_FREEZE_BALL_DAT &&
                kind != ITR_KIND_FORCEFIELD) {
                break;
            }

            // 2. Catch-injured (kind 3) can only grab characters (type == 0)
            if (kind == ITR_KIND_CATCH_INJURED && injured_file->type != TYPE_CHARACTER) {
                break;
            }

            // 3. Normal attack (kind 0) state and effect filtering
            if (kind == ITR_KIND_NORMAL) {
                if (eff == EFFECT_SHINING && injured_file->type == TYPE_CHARACTER) {
                    break;
                }
                if (eff == EFFECT_FLAME &&
                    (injured_file->type != TYPE_CHARACTER ||
                     injured_frame3->state == STATE_BURNING ||
                     injured_frame3->state == STATE_FIRE)) {
                    break;
                }
                if (eff == EFFECT_FIREN_EXPLODE &&
                    (injured_frame3->state == STATE_BURNING ||
                     injured_frame3->state == STATE_FIRE)) {
                    break;
                }
                if (eff == EFFECT_COLUMN &&
                    injured->frame_id1 >= 200 && injured->frame_id1 < 203) {
                    break;
                }
                if (eff == EFFECT_FIRE &&
                    attacker_frame3->state == STATE_FIRE &&
                    injured_frame3->state == STATE_BURNING) {
                    break;
                }
            }

            // 4. Heal (kind 8) only affects characters; invincibility blocks all except heal (8) and obstacles (14)
            if (kind == ITR_KIND_HEAL && injured_file->type != TYPE_CHARACTER) {
                break;
            }
            if (injured->invincible_time != 0 &&
                kind != ITR_KIND_HEAL &&
                kind != ITR_KIND_SUPER_PUNCH) {
                break;
            }

            // 5. Team immunity checks for standard / special interaction kinds
            if ((kind < 4 || kind == 6 ||
                 (kind == 9 && injured_file->type == TYPE_CHARACTER) ||
                 kind == 10 || kind == 11 || kind == 15 || kind == 16) &&
                injured_frame1->state != STATE_ICE &&
                injured_frame1->state != STATE_CAUGHT &&
                (inj_fid != ID_FREEZE_COLUMN_DAT ||
                 (att_fid == ID_FREEZE_COLUMN_DAT &&
                  (injured->frame_id1 % 10 != 5 || attacker->frame_id1 % 10 != 0)))) {
                if (attacker->team == injured->team &&
                    attacker->team != 0 &&
                    kind != ITR_KIND_HEAL &&
                    (attacker_frame1->state != STATE_BURNING ||
                     eff == EFFECT_FIREN_EXPLODE ||
                     eff == EFFECT_JULIAN_EXPLODE) &&
                    (attacker_file->type != TYPE_CHARACTER ||
                     injured_file->type != TYPE_ATTACK ||
                     attacker->facing == injured->facing) &&
                    injured_file->type != TYPE_LIGHT_WEAPON &&
                    injured_file->type != TYPE_HEAVY_WEAPON &&
                    injured_file->type != TYPE_THROW_WEAPON &&
                    injured_file->type != TYPE_DRINK) {
                    break;
                }
            }

            // 6. Weapon strength (kind 5) holder team immunity check
            if (kind == 5 && attacker->holder_id >= 0 && attacker->holder_id < MAX_OBJECTS) {
                object_t *holder = global->objects[attacker->holder_id];
                if (holder &&
                    holder->team == injured->team &&
                    holder->team != 0 &&
                    injured_frame1->state != STATE_ICE &&
                    injured_file->type != TYPE_LIGHT_WEAPON &&
                    injured_file->type != TYPE_HEAVY_WEAPON &&
                    injured_file->type != TYPE_THROW_WEAPON &&
                    injured_file->type != TYPE_DRINK &&
                    (inj_fid != ID_FREEZE_COLUMN_DAT ||
                     (att_fid == ID_FREEZE_COLUMN_DAT &&
                      (injured->frame_id1 % 10 != 5 || attacker->frame_id1 % 10 != 0)))) {
                    break;
                }
            }

            // 7. 3D Bounding Box Calculation
            int32_t bdy_left = (injured->facing == FACING_RIGHT)
                ? (injured->x - injured_frame4->centerx + bdy->x)
                : (injured->x + injured_frame4->centerx - bdy->w - bdy->x);
            int32_t bdy_top  = injured->y - injured_frame4->centery + bdy->y;

            int32_t itr_left = (attacker->facing == FACING_RIGHT)
                ? (attacker->x - attacker_frame4->centerx + itr->x)
                : (attacker->x + attacker_frame4->centerx - itr->w - itr->x);
            int32_t itr_top  = attacker->y - attacker_frame4->centery + itr->y;

            int32_t zwidth = (itr->zwidth == 0) ? 15 : itr->zwidth;
            int32_t dz = attacker->z - injured->z;
            bool z_ok = (dz < zwidth && dz > -zwidth);

            int32_t overlap = FUN_004171c0(bdy_left, bdy_top, bdy->w, bdy->h,
                                           itr_left, itr_top, itr->w, itr->h);
            if (overlap != 0 && z_ok) {
                bool blocked = false;
                if (injured_frame1->state == STATE_FALLING &&
                    itr->fall < 41 &&
                    kind != ITR_KIND_FLUTE &&
                    kind != ITR_KIND_FLOAT) {
                    blocked = true;
                }

                // Criminal / hostage (bdy->kind > 999) rescue filter when mode == 1
                if (mode == 1) {
                    bool can_free_hostage = false;
                    if ((attacker_file->type == TYPE_CHARACTER ||
                         att_fid == ID_HENRY_ARROW1_DAT ||
                         att_fid == ID_RUDOLF_WEAPON_DAT) &&
                        attacker->team != 5) {
                        can_free_hostage = true;
                    }
                    if (attacker->weapon_type < 0 &&
                        attacker->holder_id >= 0 &&
                        attacker->holder_id < MAX_OBJECTS &&
                        global->is_object_exists[attacker->holder_id]) {
                        object_t *holder = global->objects[attacker->holder_id];
                        if (holder && holder->file &&
                            holder->file->type == TYPE_CHARACTER &&
                            holder->team != 5) {
                            can_free_hostage = true;
                        }
                    }
                    if (bdy->kind > 999 && !can_free_hostage) {
                        blocked = true;
                    }
                }

                // Multi-target (vrest != 0) or special catch/pickup kinds vs single-target (arest)
                if (itr->vrest != 0 ||
                    kind == ITR_KIND_CATCH ||
                    kind == ITR_KIND_PICKUP_WEAPON ||
                    kind == 7 ||
                    (injured_frame4->state == 1004 &&
                     (attacker_file->type < 1 || attacker->weapon_type < 0)) ||
                    blocked) {
                    if (attacker->successful_attacks <= 19 && !blocked) {
                        int32_t accept = 0;
                        if (injured_frame4->state == 1004 &&
                            (attacker_file->type < 1 || attacker->weapon_type < 0) &&
                            kind != ITR_KIND_PICKUP_WEAPON &&
                            kind != 7 &&
                            kind != ITR_KIND_FLUTE) {
                            accept = 2;
                        }
                        if (kind == ITR_KIND_CATCH) {
                            int32_t dist = attacker->x - injured->x;
                            if (dist < 0) dist = -dist;
                            if (dist < injured->vulnerable_distance ||
                                (dist == injured->vulnerable_distance && FUN_00417170(0x86, 2) == 0)) {
                                injured->vulnerable_distance = dist;
                            } else {
                                accept = 2;
                            }
                        }
                        if (kind == ITR_KIND_THROWN && attacker->fall != 0 && accept != 2) {
                            accept = 1;
                        }
                        if (kind == ITR_KIND_CATCH) {
                            if (((attacker->click_right != 0 && attacker->x < injured->x) ||
                                 (attacker->click_left != 0 && injured->x <= attacker->x)) &&
                                injured_frame1->state == STATE_INJURED_2) {
                                if (accept != 2) accept = 1;
                            }
                        } else if (kind == ITR_KIND_PICKUP_WEAPON) {
                            if (attacker->weapon_type == 0) {
                                if (attacker->click_attack != 0 &&
                                    attacker->holding_attack == 0 &&
                                    injured_frame1->state == 1004 &&
                                    accept != 2) {
                                    accept = 1;
                                }
                            }
                            if (attacker->click_attack != 0 &&
                                attacker->holding_attack == 0 &&
                                injured_frame1->state == 2004 &&
                                accept != 2) {
                                accept = 1;
                            }
                        } else if (kind != 7) {
                            if (accept != 2) accept = 1;
                        }

                        if ((kind == 7 &&
                             attacker->click_attack != 0 &&
                             attacker->holding_attack == 0 &&
                             injured_frame1->state == 1004 &&
                             accept != 2) ||
                            accept == 1) {
                            int32_t slot = attacker->successful_attacks;
                            attacker->injured_of_attack[slot] = (int32_t)injured_id;
                            attacker->itr_of_attack[slot] = (uint8_t)itr_id;
                            attacker->successful_attacks++;
                        }
                    }
                } else {
                    // Single-target (arest): pick closest victim in X
                    int32_t dist = attacker->x - injured->x;
                    if (attacker->weapon_type < 0) {
                        if ((int32_t)injured_id != attacker->holder_id &&
                            attacker->holder_id >= 0 &&
                            attacker->holder_id < MAX_OBJECTS &&
                            global->objects[attacker->holder_id]) {
                            dist = global->objects[attacker->holder_id]->x - injured->x;
                            if (dist < 0) dist = -dist;
                        } else {
                            dist = 2000;
                        }
                    } else if (dist < 0) {
                        dist = -dist;
                    }
                    if (dist < attacker->attackable_distance ||
                        (dist == attacker->attackable_distance && FUN_00417170(0x85, 2) == 0)) {
                        attacker->attackable_distance = dist;
                        attacker->injured_of_attack[0] = (int32_t)injured_id;
                        attacker->itr_of_attack[0] = (uint8_t)itr_id;
                        attacker->successful_attacks = 1;
                    }
                }
            }
        }
    }
}

// MSVC __thiscall symbol bridge for FUN_00417400
void FUN_00417400(int param_1, int param_2, int param_3)
{
    global_t *global = (global_t *)in_ECX;
    lf2_does_attack_success(global, (uint32_t)param_1, (uint32_t)param_2, (uint32_t)param_3);
}

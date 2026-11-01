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
    frame_t *attacker_frame4 = &attacker_file->frames[attacker->frame_id4];

    frame_t *injured_frame1  = &injured_file->frames[injured->frame_id1];
    frame_t *injured_frame3  = &injured_file->frames[injured->frame_id3];
    frame_t *injured_frame4  = &injured_file->frames[injured->frame_id4];

    for (uint32_t itr_id = 0; itr_id < attacker_frame4->itrs_size; itr_id++) {
        itr_t *itr = &attacker_frame4->itrs[itr_id];

        for (uint32_t bdy_id = 0; bdy_id < injured_frame4->bdys_size; bdy_id++) {
            bdy_t *bdy = &injured_frame4->bdys[bdy_id];

            // 1. Freeze ball cannot be attacked by standard projectiles (except forcefield)
            if ((attacker_file->id == ID_JOHN_BALL_DAT ||
                 attacker_file->id == ID_DEEP_BALL_DAT ||
                 attacker_file->id == ID_DENNIS_BALL_DAT ||
                 attacker_file->id == ID_WOODY_BALL_DAT ||
                 attacker_file->id == ID_DAVIS_BALL_DAT ||
                 attacker_file->id == ID_DENNIS_CHASE_DAT ||
                 attacker_file->id == ID_JACK_BALL_DAT) &&
                injured_file->id == ID_FREEZE_BALL_DAT &&
                itr->kind != ITR_KIND_FORCEFIELD) {
                break;
            }

            // 2. Catch attacks can only grab characters
            if (itr->kind == ITR_KIND_CATCH && injured_file->type != TYPE_CHARACTER) {
                break;
            }

            // 3. Normal attack state and effect filtering
            if (itr->kind == ITR_KIND_NORMAL) {
                if (itr->effect == EFFECT_FIRE_COLUMN && injured_file->type == TYPE_CHARACTER) {
                    break;
                }
                if (itr->effect == EFFECT_FIRE &&
                    (injured_file->type != TYPE_CHARACTER ||
                     injured_frame3->state == STATE_FIRE ||
                     injured_frame3->state == STATE_BURNING)) {
                    break;
                }
                if (itr->effect == EFFECT_BURN_RUN &&
                    (injured_frame3->state == STATE_FIRE ||
                     injured_frame3->state == STATE_BURNING)) {
                    break;
                }
                // Freeze column cannot attack an already-frozen entity
                if (itr->effect == EFFECT_COLUMN &&
                    injured->frame_id1 >= 200 && injured->frame_id1 <= 203) {
                    break;
                }
            }

            // 4. Invincibility check: only heal, stone, and box can interact with invincible entities
            if (injured->invincible_time != 0 &&
                itr->kind != ITR_KIND_HEAL &&
                itr->kind != ITR_KIND_CATCH_INJURED) {
                break;
            }

            // 5. Team immunity checks (cannot attack teammates unless frozen, burning, or specific projectiles)
            if (attacker->team == injured->team &&
                attacker->team != 0 &&
                itr->kind != ITR_KIND_HEAL &&
                (attacker_frame1->state != STATE_FIRE || itr->effect == EFFECT_FLAME || itr->effect == EFFECT_FIREN_EXPLODE) &&
                (attacker_file->type != TYPE_CHARACTER || injured_file->type != TYPE_ATTACK || attacker->facing == injured->facing) &&
                injured_file->type != TYPE_LIGHT_WEAPON &&
                injured_file->type != TYPE_HEAVY_WEAPON &&
                injured_file->type != TYPE_THROW_WEAPON &&
                injured_file->type != TYPE_DRINK) {
                break;
            }

            // 6. 3D Bounding Box Calculation
            int32_t bdy_left = (injured->facing == FACING_RIGHT)
                ? (injured->x - injured_frame4->centerx + bdy->x)
                : (injured->x + injured_frame4->centerx - bdy->w - bdy->x);
            int32_t bdy_top  = injured->y - injured_frame4->centery + bdy->y;

            int32_t itr_left = (attacker->facing == FACING_RIGHT)
                ? (attacker->x - attacker_frame4->centerx + itr->x)
                : (attacker->x + attacker_frame4->centerx - itr->w - itr->x);
            int32_t itr_top  = attacker->y - attacker_frame4->centery + itr->y;

            // Z-axis tolerance check
            int32_t zwidth = (itr->zwidth == 0) ? 15 : itr->zwidth;
            if (lf2_abs(attacker->z - injured->z) >= zwidth) {
                continue;
            }

            // 2D Box intersection check
            if (!lf2_overlap(bdy_left, bdy_top, bdy->w, bdy->h,
                             itr_left, itr_top, itr->w, itr->h)) {
                continue;
            }

            // 7. Successful hit registration
            if (attacker->successful_attacks < 20) {
                uint32_t slot = attacker->successful_attacks;
                attacker->injured_of_attack[slot] = injured_id;
                attacker->itr_of_attack[slot] = itr_id;
                attacker->successful_attacks++;
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

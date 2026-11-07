#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x004068B0
 * Function: lf2_grapple_sync / process_caught_state
 * Class / Subsystem: object_t / Combat & Physics
 *
 * Description:
 *   Synchronizes the position, velocity, and state of a caught entity (State 10)
 *   to its catcher's anchor coordinates defined in cpoint_t (kind 1). Handles
 *   directional flipping, hold timer decrement, and release upon throw initiation.
 */

void lf2_grapple_sync(global_t *global, uint32_t catcher_id)
{
    if (!global || catcher_id >= MAX_OBJECTS || !global->is_object_exists[catcher_id]) {
        return;
    }
    object_t *catcher = global->objects[catcher_id];
    if (!catcher || !catcher->file || catcher->cpoint_catcher == 0) {
        return;
    }

    uint32_t victim_id = catcher->cpoint_catcher;
    if (victim_id >= MAX_OBJECTS || !global->is_object_exists[victim_id]) {
        catcher->cpoint_catcher = 0;
        return;
    }

    object_t *victim = global->objects[victim_id];
    if (!victim || !victim->file) {
        catcher->cpoint_catcher = 0;
        return;
    }

    // Retrieve active animation frames
    frame_t *catcher_frame = &catcher->file->frames[catcher->frame_id1];
    cpoint_t *cpoint = &catcher_frame->cpoint;

    // 1. If catcher is currently executing throw impulse (throwv_x != 0 or throwv_y != 0)
    if (cpoint->throwv_x != 0 || cpoint->throwv_y != 0) {
        victim->x_velocity = (catcher->facing == FACING_LEFT) ? (double)-cpoint->throwv_x : (double)cpoint->throwv_x;
        victim->y_velocity = (double)cpoint->throwv_y;
        victim->fall = 80; // Standard LF2 knocked down state
        victim->frame_id1 = 180; // Knockdown tumble frame
        victim->hp -= cpoint->throw_injury;
        if (victim->hp < 0) victim->hp = 0;

        // Disconnect grapple links
        catcher->cpoint_catcher = 0;
        victim->cpoint_timer = 0;
        return;
    }

    // 2. Otherwise anchor victim to catcher's hand coordinates
    int32_t anchor_dx = cpoint->x - catcher_frame->centerx;
    int32_t anchor_dy = cpoint->y - catcher_frame->centery;

    victim->x = (catcher->facing == FACING_LEFT) ? catcher->x - anchor_dx : catcher->x + anchor_dx;
    victim->y = catcher->y + anchor_dy;
    victim->z = catcher->z;
    victim->x_position = (double)victim->x;
    victim->y_position = (double)victim->y;
    victim->z_position = (double)victim->z;

    // Caught entity faces opposite the catcher
    victim->facing = (catcher->facing == FACING_RIGHT) ? FACING_LEFT : FACING_RIGHT;

    // Zero victim velocities
    victim->x_velocity = 0.0;
    victim->y_velocity = 0.0;
    victim->z_velocity = 0.0;

    // Synchronize victim reaction frame if specified
    if (cpoint->v_action != 0) {
        victim->frame_id1 = cpoint->v_action;
    }

    // Decrement hold timer
    if (catcher->cpoint_timer > 0) {
        catcher->cpoint_timer--;
        if (catcher->cpoint_timer == 0) {
            // Timer expired: Break grapple
            catcher->cpoint_catcher = 0;
            victim->cpoint_timer = 0;
            victim->fall = 40;
        }
    }
}

// MSVC __thiscall bridge for FUN_004064d0 / FUN_004068b0
void FUN_004064d0(void)
{
    lf2_grapple_sync((global_t *)in_ECX, (uint32_t)(uintptr_t)in_ECX);
}

void FUN_004068b0(void)
{
    FUN_004064d0();
}

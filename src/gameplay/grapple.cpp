#include "gameplay/grapple.h"
#include <cstdlib>
#include <cstring>

namespace lf2 {

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

    // Victim cannot be caught if already held or if invincible
    if (victim->cpoint_timer != 0 || victim->invincible_time != 0) {
        return false;
    }

    // Link catcher and victim (0x0042E100 & 0x004068B0)
    catcher->cpoint_catcher = victim_id;
    victim->cpoint_timer = catcher_id;
    catcher->cpoint_timer = 300; // 300 ticks max hold time (10 seconds)

    // Reset victim fall and velocities
    victim->fall = 0;
    victim->wait_counter = 0;
    victim->x_velocity = 0.0;
    victim->y_velocity = 0.0;
    victim->z_velocity = 0.0;
    victim->frame_id1 = 230; // Standard LF2 caught frame (kind 2)

    return true;
}

void execute_throw(global_t* world, uint32_t catcher_id)
{
    if (!world || catcher_id >= MAX_OBJECTS || !world->is_object_exists[catcher_id]) {
        return;
    }
    object_t* catcher = world->objects[catcher_id];
    if (!catcher || !catcher->file || catcher->cpoint_catcher == 0) {
        return;
    }

    uint32_t victim_id = catcher->cpoint_catcher;
    if (victim_id >= MAX_OBJECTS || !world->is_object_exists[victim_id]) {
        catcher->cpoint_catcher = 0;
        return;
    }

    object_t* victim = world->objects[victim_id];
    if (!victim || !victim->file) {
        catcher->cpoint_catcher = 0;
        return;
    }

    uint32_t a_frame_id = (catcher->frame_id4 < MAX_FRAMES) ? catcher->frame_id4 : catcher->frame_id1;
    if (a_frame_id >= MAX_FRAMES) return;
    const frame_t* a_frame = &catcher->file->frames[a_frame_id];

    // Compute throw velocities from cpoint (0x004068B0)
    double tx = static_cast<double>(a_frame->cpoint.throwv_x);
    double ty = static_cast<double>(a_frame->cpoint.throwv_y);
    if (tx == 0.0) tx = 8.0;
    if (ty == 0.0) ty = -10.0;

    victim->x_velocity = (catcher->facing == FACING_LEFT) ? -tx : tx;
    victim->y_velocity = ty;
    victim->y_position = -1.0; // Airborne arc
    victim->fall = 80;         // Full knockdown
    victim->frame_id1 = 180;   // Standard falling frame
    victim->wait_counter = 0;

    // Apply throw injury
    int32_t injury = static_cast<int32_t>(a_frame->cpoint.throw_injury);
    if (injury > 0) {
        victim->hp -= injury;
        victim->hp_lost += injury;
        catcher->total_attack += injury;
    }

    // Sever grapple link
    catcher->cpoint_catcher = 0;
    victim->cpoint_timer = 0;
}

void release_grapple(global_t* world, uint32_t catcher_id)
{
    if (!world || catcher_id >= MAX_OBJECTS || !world->is_object_exists[catcher_id]) {
        return;
    }
    object_t* catcher = world->objects[catcher_id];
    if (!catcher) return;

    uint32_t victim_id = catcher->cpoint_catcher;
    if (victim_id < MAX_OBJECTS && world->is_object_exists[victim_id]) {
        object_t* victim = world->objects[victim_id];
        if (victim) {
            victim->cpoint_timer = 0;
            victim->frame_id1 = 0; // Return to standing frame
            victim->wait_counter = 0;
        }
    }
    catcher->cpoint_catcher = 0;
}

void process_grapple_sync(global_t* world, uint32_t catcher_id)
{
    if (!world || catcher_id >= MAX_OBJECTS || !world->is_object_exists[catcher_id]) {
        return;
    }
    object_t* catcher = world->objects[catcher_id];
    if (!catcher || !catcher->file || catcher->cpoint_catcher == 0) {
        return;
    }

    uint32_t victim_id = catcher->cpoint_catcher;
    if (victim_id >= MAX_OBJECTS || !world->is_object_exists[victim_id]) {
        catcher->cpoint_catcher = 0;
        return;
    }

    object_t* victim = world->objects[victim_id];
    if (!victim || !victim->file) {
        catcher->cpoint_catcher = 0;
        return;
    }

    // 1. If catcher takes damage or gets knocked down, release victim
    if (catcher->fall > 0 || catcher->hp <= 0) {
        release_grapple(world, catcher_id);
        return;
    }

    // 2. Decrement hold timer
    if (catcher->cpoint_timer > 0) {
        catcher->cpoint_timer--;
        if (catcher->cpoint_timer == 0) {
            release_grapple(world, catcher_id);
            return;
        }
    }

    uint32_t a_frame_id = (catcher->frame_id4 < MAX_FRAMES) ? catcher->frame_id4 : catcher->frame_id1;
    if (a_frame_id >= MAX_FRAMES) return;
    const frame_t* a_frame = &catcher->file->frames[a_frame_id];

    // 3. Check if current frame triggers a throw
    if (a_frame->cpoint.kind == 1 &&
        (a_frame->cpoint.throwv_x != 0 || a_frame->cpoint.throwv_y != 0)) {
        execute_throw(world, catcher_id);
        return;
    }

    // 4. Synchronize victim position to catcher's cpoint (0x004068B0)
    int32_t cx = a_frame->cpoint.x;
    int32_t cy = a_frame->cpoint.y;
    int32_t centerx = a_frame->centerx;
    int32_t centery = a_frame->centery;

    if (catcher->facing == FACING_RIGHT) {
        victim->x = catcher->x + (cx - centerx);
        victim->facing = FACING_LEFT;
    } else {
        victim->x = catcher->x - (cx - centerx);
        victim->facing = FACING_RIGHT;
    }

    victim->y = catcher->y + (cy - centery);
    victim->z = catcher->z;
    victim->x_position = static_cast<double>(victim->x);
    victim->y_position = static_cast<double>(victim->y);
    victim->z_position = static_cast<double>(victim->z);
    victim->x_velocity = 0.0;
    victim->y_velocity = 0.0;
    victim->z_velocity = 0.0;
    victim->fall = 0;

    // Synchronize victim reaction frame if specified in cpoint
    if (a_frame->cpoint.v_action != 0) {
        victim->frame_id1 = a_frame->cpoint.v_action;
    }
}

} // namespace lf2


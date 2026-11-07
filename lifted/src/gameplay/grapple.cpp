#include "gameplay/grapple.h"
#include "gameplay/entity.h"
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

    // Link catcher and victim (0x0042E100 & 0x004187B0)
    catcher->cpoint_catcher = static_cast<int32_t>(victim_id);
    victim->cpoint_timer = catcher_id;
    catcher->cpoint_timer = 300; // 300 ticks max hold time
    victim->cpoint_hurt = 63;    // Standard initial cpoint_hurt stamina

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
    if (!catcher || !catcher->file || catcher->cpoint_catcher <= 0) {
        return;
    }

    uint32_t victim_id = static_cast<uint32_t>(catcher->cpoint_catcher);
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

    // Compute throw velocities from cpoint (0x004187B0)
    int32_t raw_tvx = a_frame->cpoint.throwvx;
    double tx = (raw_tvx != 0 && raw_tvx != -0x21524111) ? static_cast<double>(raw_tvx) : 8.0;
    double ty = (a_frame->cpoint.throwvy != 0) ? static_cast<double>(a_frame->cpoint.throwvy) : -10.0;
    double tz = static_cast<double>(a_frame->cpoint.throwvz);

    victim->x_velocity = (catcher->facing == FACING_LEFT) ? -tx : tx;
    victim->y_velocity = ty;
    victim->z_velocity = tz;
    victim->y_position = -1.0; // Airborne arc
    victim->fall = 80;         // Full knockdown
    victim->frame_id1 = 180;   // Standard falling frame
    victim->wait_counter = 0;

    // Apply throw injury
    int32_t injury = a_frame->cpoint.throwinjury;
    if (injury != 0) {
        victim->cpoint_hurt_act = injury;
        if (injury > 0) {
            victim->hp -= injury;
            victim->hp_lost += static_cast<uint32_t>(injury);
            catcher->total_attack += static_cast<uint32_t>(injury);
        }
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

    int32_t victim_id = catcher->cpoint_catcher;
    if (victim_id >= 0 && victim_id < static_cast<int32_t>(MAX_OBJECTS) && world->is_object_exists[victim_id]) {
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
    if (!catcher || !catcher->file || catcher->cpoint_catcher <= 0) {
        return;
    }

    uint32_t victim_id = static_cast<uint32_t>(catcher->cpoint_catcher);
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
    const cpoint_t& cp = a_frame->cpoint;

    // 3. Input transitions during grapple (aaction, jaction, taction, dircontrol) from FUN_004187b0
    if (cp.kind == 1) {
        if (cp.dircontrol == 1) {
            if (catcher->holding_left && !catcher->holding_right) {
                catcher->facing = FACING_LEFT;
                if (cp.taction != 0) {
                    catcher->frame_id1 = static_cast<uint32_t>(cp.taction < 0 ? -cp.taction : cp.taction);
                    catcher->wait_counter = 0;
                }
            } else if (catcher->holding_right && !catcher->holding_left) {
                catcher->facing = FACING_RIGHT;
                if (cp.taction != 0) {
                    catcher->frame_id1 = static_cast<uint32_t>(cp.taction < 0 ? -cp.taction : cp.taction);
                    catcher->wait_counter = 0;
                }
            }
        }
        if (cp.aaction != 0 && catcher->click_attack && !catcher->holding_attack) {
            catcher->frame_id1 = static_cast<uint32_t>(cp.aaction);
            catcher->wait_counter = 0;
        }
        if (cp.jaction != 0 && catcher->click_jump && !catcher->holding_jump) {
            catcher->frame_id1 = static_cast<uint32_t>(cp.jaction);
            catcher->wait_counter = 0;
        }

        // Apply cpoint.injury and cpoint.decrease
        if (cp.injury > 0) {
            victim->hp -= cp.injury;
            victim->hp_lost += static_cast<uint32_t>(cp.injury);
            catcher->total_attack += static_cast<uint32_t>(cp.injury);
        }
        if (cp.decrease != 0) {
            victim->cpoint_hurt -= cp.decrease;
        }
    }

    // 4. Check if current frame triggers a throw
    if (cp.kind == 1 &&
        ((cp.throwvx != 0 && cp.throwvx != -0x21524111) || cp.throwvy != 0 || cp.throwvz != 0)) {
        execute_throw(world, catcher_id);
        return;
    }

    // 5. Synchronize victim position to catcher's cpoint (0x004187B0)
    int32_t cx = cp.x;
    int32_t cy = cp.y;
    int32_t centerx = a_frame->centerx;
    int32_t centery = a_frame->centery;

    if (catcher->facing == FACING_RIGHT) {
        victim->x = catcher->x + (cx - centerx);
        victim->facing = (cp.cover >= 20) ? FACING_RIGHT : FACING_LEFT;
    } else {
        victim->x = catcher->x - (cx - centerx);
        victim->facing = (cp.cover >= 20) ? FACING_LEFT : FACING_RIGHT;
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
    victim->cpoint_hurtable = cp.hurtable;

    // Synchronize victim reaction frame if specified in cpoint
    if (cp.vaction != 0) {
        victim->frame_id1 = static_cast<uint32_t>(cp.vaction);
    }
}

void process_firzen_fusion(global_t* world, uint32_t obj_id)
{
    if (!world || obj_id >= MAX_OBJECTS || !world->is_object_exists[obj_id]) return;
    object_t* self = world->objects[obj_id];
    if (!self || !self->file) return;

    // Firen (id 7) running into Freeze (id 8) -> Firzen (id 51) fusion (FUN_004064d0)
    if (self->file->id == FIREN_DAT && self->hp < self->dark_hp / 3 &&
        self->frame_id1 < MAX_FRAMES && self->file->frames[self->frame_id1].state == STATE_RUNNING) {
        for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
            if (!world->is_object_exists[i] || i == obj_id) continue;
            object_t* other = world->objects[i];
            if (!other || !other->file || other->file->id != FREEZE_DAT) continue;
            if (other->team != self->team || other->hp >= other->dark_hp / 3) continue;
            if (other->frame_id1 >= MAX_FRAMES || other->file->frames[other->frame_id1].state != STATE_RUNNING) continue;
            if (self->facing == other->facing) continue;
            if (std::abs(self->x - other->x) < 40 && std::abs(self->z - other->z) < 15) {
                for (uint32_t f = 0; f < MAX_FILES; ++f) {
                    if (world->files[f] && world->files[f]->id == FIRZEN_DAT) {
                        self->file = world->files[f];
                        self->frame_id1 = 295;
                        self->wait_counter = 0;
                        self->hp = 500;
                        self->dark_hp = 500;
                        self->mp = 500;
                        world->is_object_exists[i] = 0;
                        return;
                    }
                }
            }
        }
    }
}

} // namespace lf2

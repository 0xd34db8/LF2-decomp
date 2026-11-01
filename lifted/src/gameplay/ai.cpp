#include "gameplay/ai.h"
#include "core/random.h"
#include <cstdlib>
#include <cstring>
#include <cmath>

namespace lf2 {

uint32_t ai_find_nearest_target(const global_t* world, uint32_t ai_id)
{
    if (!world || ai_id >= MAX_OBJECTS || !world->is_object_exists[ai_id]) {
        return MAX_OBJECTS;
    }
    const object_t* self = world->objects[ai_id];
    if (!self || !self->file) return MAX_OBJECTS;

    uint32_t best_target = MAX_OBJECTS;
    int64_t min_dist_sq = INT64_MAX;

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!world->is_object_exists[i] || i == ai_id) continue;
        const object_t* candidate = world->objects[i];
        if (!candidate || !candidate->file) continue;

        // Target must be alive, enemy team, and a character or clone
        if (candidate->hp <= 0 || candidate->team == self->team) continue;
        if (candidate->file->type != TYPE_CHARACTER) continue;

        int64_t dx = static_cast<int64_t>(candidate->x - self->x);
        int64_t dy = static_cast<int64_t>(candidate->y - self->y);
        int64_t dz = static_cast<int64_t>(candidate->z - self->z);

        int64_t dist_sq = dx * dx + dy * dy + dz * dz;
        if (dist_sq < min_dist_sq) {
            min_dist_sq = dist_sq;
            best_target = i;
        }
    }

    return best_target;
}

input_state_t ai_evaluate_behavior(const global_t* world, uint32_t ai_id, ai_difficulty_t difficulty)
{
    input_state_t input{};

    if (!world || ai_id >= MAX_OBJECTS || !world->is_object_exists[ai_id]) {
        return input;
    }
    object_t* self = world->objects[ai_id];
    if (!self || !self->file || self->hp <= 0) return input;

    // Can only act if not flinching or knocked down
    if (self->fall > 0) return input;

    // Locate target
    uint32_t target_id = self->enemy;
    if (target_id >= MAX_OBJECTS || target_id == ai_id ||
        !world->is_object_exists[target_id] ||
        world->objects[target_id]->hp <= 0 ||
        world->objects[target_id]->team == self->team) {
        target_id = ai_find_nearest_target(world, ai_id);
        self->enemy = target_id;
    }

    if (target_id >= MAX_OBJECTS || !world->is_object_exists[target_id]) {
        return input; // No active targets
    }

    const object_t* target = world->objects[target_id];
    int32_t dx = target->x - self->x;
    int32_t dz = target->z - self->z;
    int32_t abs_dx = std::abs(dx);
    int32_t abs_dz = std::abs(dz);

    // 1. Defensive evaluation: If target is attacking towards us
    uint32_t t_frame_id = (target->frame_id4 < MAX_FRAMES) ? target->frame_id4 : target->frame_id1;
    if (t_frame_id < MAX_FRAMES && target->file) {
        const frame_t* t_frame = &target->file->frames[t_frame_id];
        if (t_frame->state == STATE_ATTACKING && abs_dx <= 80 && abs_dz <= 20) {
            uint32_t roll = lf2_random(0x99, 100);
            uint32_t defense_threshold = (difficulty == AI_CRAZY) ? 90 :
                                         (difficulty == AI_NORMAL) ? 60 : 25;
            if (roll < defense_threshold) {
                input.defend = true;
                if (difficulty == AI_CRAZY && (roll < 30)) {
                    input.jump = true; // Dodge roll
                }
                return input;
            }
        }
    }

    // 2. Melee combat range (|dx| <= 55 and |dz| <= 16)
    if (abs_dx <= 55 && abs_dz <= 16) {
        // Face opponent
        self->facing = (dx >= 0) ? FACING_RIGHT : FACING_LEFT;

        // Melee attack trigger
        input.attack = true;

        // High difficulty special move execution
        if (difficulty == AI_CRAZY && self->mp >= 100 && (lf2_random(0x9A, 4) == 0)) {
            input.defend = true;
            input.jump = true; // Uppercut / Special technique
        }
        return input;
    }

    // 3. Approach movement
    // Z-axis lane alignment
    if (dz > 10) {
        input.down = true;
    } else if (dz < -10) {
        input.up = true;
    }

    // X-axis lateral tracking
    if (dx > 45) {
        input.right = true;
        self->facing = FACING_RIGHT;
    } else if (dx < -45) {
        input.left = true;
        self->facing = FACING_LEFT;
    }

    // 4. Long-range projectile attack
    if (abs_dx > 120 && abs_dz <= 20 && self->mp >= 50) {
        uint32_t ranged_roll = lf2_random(0x9B, 100);
        uint32_t ranged_threshold = (difficulty == AI_CRAZY) ? 35 :
                                    (difficulty == AI_NORMAL) ? 15 : 5;
        if (ranged_roll < ranged_threshold) {
            input.defend = true;
            if (dx > 0) input.right = true; else input.left = true;
            input.attack = true;
        }
    }

    return input;
}

void ai_tick(global_t* world, uint32_t ai_id, ai_difficulty_t difficulty)
{
    if (!world || ai_id >= MAX_OBJECTS || !world->is_object_exists[ai_id]) {
        return;
    }
    object_t* self = world->objects[ai_id];
    if (!self || !self->file) return;

    input_state_t input = ai_evaluate_behavior(world, ai_id, difficulty);
    object_handle_input(self, input);
}

} // namespace lf2

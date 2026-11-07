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

bool ai_evaluate_character_special(object_t* self, const object_t* target, input_state_t& out_input)
{
    if (!self || !self->file || !target || !target->file) return false;

    int32_t dx = std::abs(target->x - self->x);
    int32_t dz = std::abs(target->z - self->z);
    uint32_t cid = self->file->id;

    switch (cid) {
        case DEEP_DAT:
            if (dx < 80 && dz < 16 && self->mp >= 75 && lf2_random(0x20, 6) == 0) {
                out_input.defend = true;
                out_input.down = true;
                out_input.attack = true;
                return true;
            }
            break;
        case JOHN_DAT:
        case DENNIS_DAT:
        case DAVIS_DAT:
        case FIREN_DAT:
        case FREEZE_DAT:
        case FIRZEN_DAT:
        case JULIAN_DAT:
            if (dx > 120 && dx < 380 && dz < 18 && self->mp >= 80 && lf2_random(0x21, 5) == 0) {
                out_input.defend = true;
                if (target->x > self->x) out_input.right = true;
                else out_input.left = true;
                out_input.attack = true;
                return true;
            }
            break;
        default:
            break;
    }
    return false;
}

bool ai_evaluate_weapon_decision(const global_t* world, uint32_t ai_id, uint32_t target_id, input_state_t& out_input)
{
    if (!world || ai_id >= MAX_OBJECTS || target_id >= MAX_OBJECTS) return false;
    const object_t* self = world->objects[ai_id];
    const object_t* target = world->objects[target_id];
    if (!self || !target || self->weapon_type == 0) return false;

    int32_t w_id = self->weapon_id;
    if (w_id < 0 || w_id >= static_cast<int32_t>(MAX_OBJECTS) || !world->is_object_exists[w_id]) return false;
    const object_t* weapon = world->objects[w_id];
    if (!weapon || !weapon->file) return false;

    uint32_t wid = weapon->file->id;
    int32_t dx = std::abs(target->x - self->x);
    int32_t dz = std::abs(target->z - self->z);

    if (wid == MILK_DAT || wid == BEER_DAT) {
        if (dx > 120 && lf2_random(0x34, 5) == 0) {
            out_input.attack = true;
            return true;
        }
        return false;
    }

    if ((wid == STONE_DAT || wid == WOODEN_BOX_DAT) && dx < 280 && dz < 12 && lf2_random(0x2D, 6) == 0) {
        out_input.attack = true;
        return true;
    }

    return false;
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
    int32_t target_id_signed = self->enemy;
    uint32_t target_id = (target_id_signed >= 0) ? static_cast<uint32_t>(target_id_signed) : MAX_OBJECTS;
    if (target_id >= MAX_OBJECTS || target_id == ai_id ||
        !world->is_object_exists[target_id] ||
        world->objects[target_id]->hp <= 0 ||
        world->objects[target_id]->team == self->team) {
        target_id = ai_find_nearest_target(world, ai_id);
        self->enemy = (target_id < MAX_OBJECTS) ? static_cast<int32_t>(target_id) : -1;
    }

    if (target_id >= MAX_OBJECTS || !world->is_object_exists[target_id]) {
        return input; // No active targets
    }

    const object_t* target = world->objects[target_id];
    self->ai_target_x = target->x;
    self->ai_target_z = target->z;

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

    // 3. Held weapon decision (0x00408CB0)
    if (ai_evaluate_weapon_decision(world, ai_id, target_id, input)) {
        return input;
    }

    // 4. Approach movement
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

    // 5. Character-specific & long-range projectile attack (0x00403A40 / 0x004094B0)
    if (ai_evaluate_character_special(self, target, input)) {
        return input;
    }

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

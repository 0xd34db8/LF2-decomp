#include "gameplay/weapon.h"
#include <cstdlib>
#include <cstring>

namespace lf2 {

bool try_pickup_weapon(global_t* world, uint32_t char_id)
{
    if (!world || char_id >= MAX_OBJECTS || !world->is_object_exists[char_id]) {
        return false;
    }
    object_t* character = world->objects[char_id];
    if (!character || !character->file || character->hp <= 0) {
        return false;
    }

    // Can only pick up if currently unarmed and not knocked down
    if (character->weapon_type != 0 || character->fall > 0) {
        return false;
    }

    // Search world for nearby dropped weapons (0x00408CE0 / 0x0040A6F0)
    for (uint32_t w_id = 0; w_id < MAX_OBJECTS; ++w_id) {
        if (!world->is_object_exists[w_id] || w_id == char_id) continue;
        object_t* weapon = world->objects[w_id];
        if (!weapon || !weapon->file) continue;

        // Must be unheld weapon
        if (weapon->holder_id != 0) continue;

        uint32_t w_type = weapon->file->type;
        if (w_type != TYPE_LIGHT_WEAPON && w_type != TYPE_HEAVY_WEAPON) {
            continue;
        }

        // Proximity check in 3D space
        int32_t dx = std::abs(character->x - weapon->x);
        int32_t dy = std::abs(character->y - weapon->y);
        int32_t dz = std::abs(character->z - weapon->z);

        if (dx <= 35 && dy <= 30 && dz <= 15) {
            // Pick up weapon!
            if (w_type == TYPE_LIGHT_WEAPON) {
                character->weapon_type = 1;
                weapon->weapon_type = static_cast<uint32_t>(-1);
            } else {
                character->weapon_type = 4;
                weapon->weapon_type = static_cast<uint32_t>(-4);
            }

            character->weapon_id = w_id;
            weapon->holder_id = char_id;
            weapon->owner = char_id;
            weapon->team = character->team;

            // Transition character to pickup animation frame
            character->frame_id1 = 115;
            character->wait_counter = 0;
            character->get_weapon_counter++;
            return true;
        }
    }

    return false;
}

void process_weapon_sync(global_t* world, uint32_t char_id)
{
    if (!world || char_id >= MAX_OBJECTS || !world->is_object_exists[char_id]) {
        return;
    }
    object_t* character = world->objects[char_id];
    if (!character || !character->file || character->weapon_type == 0) {
        return;
    }

    uint32_t w_id = character->weapon_id;
    if (w_id >= MAX_OBJECTS || !world->is_object_exists[w_id]) {
        character->weapon_type = 0;
        character->weapon_id = 0;
        return;
    }

    object_t* weapon = world->objects[w_id];
    if (!weapon || !weapon->file) {
        character->weapon_type = 0;
        character->weapon_id = 0;
        return;
    }

    // If character receives damage or enters knockdown, drop the weapon
    if (character->fall > 0 || character->hp <= 0) {
        drop_weapon(world, char_id);
        return;
    }

    uint32_t c_frame_id = (character->frame_id4 < MAX_FRAMES) ? character->frame_id4 : character->frame_id1;
    if (c_frame_id >= MAX_FRAMES) return;
    const frame_t* c_frame = &character->file->frames[c_frame_id];

    // Synchronize weapon coordinates to character hand (wpoint_t)
    const wpoint_t& wp = c_frame->wpoint;
    int32_t wx = wp.x;
    int32_t wy = wp.y;
    int32_t centerx = c_frame->centerx;
    int32_t centery = c_frame->centery;

    if (character->facing == FACING_RIGHT) {
        weapon->x = character->x + (wx - centerx);
    } else {
        weapon->x = character->x - (wx - centerx);
    }

    weapon->y = character->y + (wy - centery);
    weapon->z = character->z;
    weapon->facing = character->facing;
    weapon->x_position = static_cast<double>(weapon->x);
    weapon->y_position = static_cast<double>(weapon->y);
    weapon->z_position = static_cast<double>(weapon->z);
    weapon->x_velocity = 0.0;
    weapon->y_velocity = 0.0;
    weapon->z_velocity = 0.0;

    // Synchronize weapon animation frame to character action (weaponact)
    if (wp.weaponact != 0) {
        weapon->frame_id1 = wp.weaponact;
    }
}

void drop_weapon(global_t* world, uint32_t char_id)
{
    if (!world || char_id >= MAX_OBJECTS || !world->is_object_exists[char_id]) {
        return;
    }
    object_t* character = world->objects[char_id];
    if (!character) return;

    uint32_t w_id = character->weapon_id;
    if (w_id < MAX_OBJECTS && world->is_object_exists[w_id]) {
        object_t* weapon = world->objects[w_id];
        if (weapon) {
            weapon->holder_id = 0;
            weapon->weapon_type = 0;
            weapon->y_velocity = -4.0;
            weapon->x_velocity = (character->facing == FACING_LEFT) ? 2.0 : -2.0;
            weapon->y_position = -1.0;
        }
    }

    character->weapon_type = 0;
    character->weapon_id = 0;
}

void throw_weapon(global_t* world, uint32_t char_id)
{
    if (!world || char_id >= MAX_OBJECTS || !world->is_object_exists[char_id]) {
        return;
    }
    object_t* character = world->objects[char_id];
    if (!character || !character->file || character->weapon_type == 0) {
        return;
    }

    uint32_t w_id = character->weapon_id;
    if (w_id >= MAX_OBJECTS || !world->is_object_exists[w_id]) {
        character->weapon_type = 0;
        character->weapon_id = 0;
        return;
    }

    object_t* weapon = world->objects[w_id];
    if (!weapon || !weapon->file) {
        character->weapon_type = 0;
        character->weapon_id = 0;
        return;
    }

    uint32_t c_frame_id = (character->frame_id4 < MAX_FRAMES) ? character->frame_id4 : character->frame_id1;
    if (c_frame_id >= MAX_FRAMES) return;
    const frame_t* c_frame = &character->file->frames[c_frame_id];
    const wpoint_t& wp = c_frame->wpoint;

    double tvx = (wp.dvx != 0) ? static_cast<double>(wp.dvx) : 12.0;
    double tvy = (wp.dvy != 0) ? static_cast<double>(wp.dvy) : -3.0;

    weapon->holder_id = 0;
    weapon->weapon_type = 0;
    weapon->owner = char_id;
    weapon->x_velocity = (character->facing == FACING_LEFT) ? -tvx : tvx;
    weapon->y_velocity = tvy;
    weapon->y_position = -1.0;
    weapon->frame_id1 = (wp.weaponact != 0) ? wp.weaponact : 20; // Thrown frame
    weapon->thrown_injury = 35;

    character->weapon_type = 0;
    character->weapon_id = 0;
}

} // namespace lf2


#include "gameplay/weapon.h"
#include "core/random.h"
#include <cstdlib>
#include <algorithm>

namespace lf2 {

namespace {

void wpoint_sync_single(global_t* world, int32_t weapon_id)
{
    if (!world || weapon_id < 0 || weapon_id >= static_cast<int32_t>(MAX_OBJECTS) ||
        !world->is_object_exists[weapon_id]) {
        return;
    }

    object_t* weapon = world->objects[weapon_id];
    if (!weapon || !weapon->file || weapon->weapon_type >= 0) {
        return;
    }

    int32_t holder_id = weapon->holder_id;
    if (holder_id < 0 || holder_id >= static_cast<int32_t>(MAX_OBJECTS) ||
        !world->is_object_exists[holder_id] ||
        !world->objects[holder_id] ||
        !world->objects[holder_id]->file ||
        world->objects[holder_id]->weapon_id != weapon_id) {
        weapon->weapon_type = 0;
        return;
    }

    object_t* holder = world->objects[holder_id];
    if (holder->frame_id1 >= MAX_FRAMES) {
        return;
    }
    const frame_t* holder_frame = &holder->file->frames[holder->frame_id1];

    // 1. Drinking Milk (122) or Beer (123) in STATE_DRINKING (17)
    if (holder_frame->state == STATE_DRINKING) {
        if (weapon->file->id == MILK_DAT && weapon->hp > 0) {
            weapon->hp -= 1;
            if (weapon->hp % 5 == 0) {
                holder->dark_hp += 2;
                holder->hp += 4;
                if (holder->dark_hp > holder->max_hp) holder->dark_hp = holder->max_hp;
                if (holder->hp > holder->dark_hp) holder->hp = holder->dark_hp;
            }
            if (weapon->hp % 6 == 0) {
                holder->mp += 5;
                if (holder->mp > 500) holder->mp = 500;
            }
            if (weapon->hp < 1) {
                holder->weapon_type = 0;
                weapon->weapon_type = 0;
                holder->weapon_id = 0;
                weapon->holder_id = 0;
                weapon->frame_id1 = 0;
                weapon->y_velocity = -8.0;
                weapon->x_velocity = static_cast<double>(lf2_random(0x88, 7) - 3);
                holder->frame_id1 = 0;
                weapon->weapon_hp = 0;
                return;
            }
        }
        if (weapon->file->id == BEER_DAT && weapon->hp > 0) {
            weapon->hp -= 2;
            holder->mp += 3;
            if (holder->mp > 500) holder->mp = 500;
            if (weapon->clone > -1 && weapon->mp > 150) {
                holder->mp = 150;
            }
            if (weapon->hp < 1) {
                holder->weapon_type = 0;
                weapon->weapon_type = 0;
                holder->weapon_id = 0;
                weapon->holder_id = 0;
                weapon->frame_id1 = 0;
                weapon->y_velocity = -8.0;
                weapon->x_velocity = static_cast<double>(lf2_random(0x89, 7) - 3);
                holder->frame_id1 = 0;
                weapon->weapon_hp = 0;
                return;
            }
        }
    }

    // 2. Dual-anchor wpoint synchronization
    const wpoint_t& wp = holder_frame->wpoint;
    weapon->frame_id1 = (wp.weaponact < MAX_FRAMES) ? wp.weaponact : 0;
    weapon->facing = holder->facing;
    weapon->shaking = holder->shaking;

    int32_t world_wx = (holder->facing == FACING_RIGHT)
        ? (holder->x - holder_frame->centerx + wp.x)
        : (holder->x + holder_frame->centerx - wp.x);
    int32_t world_wy = holder->y - holder_frame->centery + wp.y;

    const frame_t* w_frame = &weapon->file->frames[weapon->frame_id1];
    if (weapon->facing == FACING_RIGHT) {
        weapon->x = (w_frame->centerx - w_frame->wpoint.x) + world_wx;
    } else {
        weapon->x = (w_frame->wpoint.x - w_frame->centerx) + world_wx;
    }
    weapon->y = (w_frame->centery - w_frame->wpoint.y) + world_wy;

    weapon->z = holder->z;
    if (wp.cover == 0) {
        weapon->z += 1;
        weapon->y -= 1;
    } else {
        weapon->z -= 1;
        weapon->y += 1;
    }

    weapon->z_position = static_cast<double>(weapon->z);
    weapon->x_position = static_cast<double>(weapon->x);
    weapon->y_position = static_cast<double>(weapon->y);

    // 3. Drop weapon when holder is falling (STATE_FALLING = 12) or caught (STATE_PICKED_CAUGHT = 10)
    if (holder_frame->state == STATE_FALLING || holder_frame->state == STATE_PICKED_CAUGHT) {
        holder->weapon_type = 0;
        weapon->weapon_type = 0;
        weapon->frame_id1 = static_cast<uint32_t>(lf2_random(0x8a, 16));
        if (holder->attacks == 1) {
            weapon->y_velocity = holder->y_accl;
            weapon->x_velocity = holder->pic_x_gain / 3.0;
        } else {
            weapon->y_velocity = holder->y_velocity;
            weapon->x_velocity = holder->x_velocity / 3.0;
        }
        if (-2.0 < weapon->y_position) {
            weapon->y_position = -2.0;
        }
    }

    // 4. Weapon throw impulse when wpoint.dvx != 0
    if (wp.dvx != 0) {
        uint32_t wtype = weapon->file->type;
        if (wtype == TYPE_LIGHT_WEAPON || wtype == TYPE_THROW_WEAPON || wtype == TYPE_DRINK) {
            weapon->weapon_throw_injury = holder_id;
            weapon->frame_id1 = 40;
            weapon->x_velocity = (holder->facing == FACING_RIGHT)
                ? static_cast<double>(wp.dvx)
                : static_cast<double>(-wp.dvx);
            weapon->y_velocity = static_cast<double>(wp.dvy);
            holder->weapon_type = 0;
            weapon->weapon_type = 0;
            if (holder->click_up != 0 && holder->click_down == 0) {
                weapon->z_velocity = static_cast<double>(-wp.dvz);
            } else if (holder->click_up == 0 && holder->click_down != 0) {
                weapon->z_velocity = static_cast<double>(wp.dvz);
            }
        }
        if (wtype == TYPE_HEAVY_WEAPON) {
            weapon->frame_id1 = static_cast<uint32_t>(lf2_random(0x8b, 6));
            weapon->x_velocity = (holder->facing == FACING_RIGHT)
                ? static_cast<double>(wp.dvx)
                : static_cast<double>(-wp.dvx);
            weapon->y_velocity = static_cast<double>(wp.dvy);
            holder->weapon_type = 0;
            weapon->weapon_type = 0;
            if (holder->click_up != 0 && holder->click_down == 0) {
                weapon->z_velocity = static_cast<double>(-wp.dvz);
            } else if (holder->click_up == 0 && holder->click_down != 0) {
                weapon->z_velocity = static_cast<double>(wp.dvz);
            }
        }
    }

    // 5. Explicit weapon drop (wpoint.kind == 3)
    if (wp.kind == 3) {
        weapon->weapon_type = 0;
        holder->weapon_type = 0;
        weapon->frame_id1 = static_cast<uint32_t>(lf2_random(0x8c, 6));
        weapon->x_velocity = static_cast<double>(lf2_random(0x8d, 7) - 3);
        weapon->y_velocity = static_cast<double>(-lf2_random(0x8e, 4));
        weapon->z_velocity = static_cast<double>(lf2_random(0x8f, 5) - 2) / 5.0;
    }
}

} // namespace

// VERIFIED: LF2 0x00417f80
void world_process_weapons(global_t* world)
{
    if (!world) return;
    for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
        if (world->is_object_exists[i] && world->objects[i] && world->objects[i]->file &&
            world->objects[i]->file->type == TYPE_CHARACTER) {
            world->objects[i]->z = static_cast<int32_t>(world->objects[i]->z_position);
        }
    }
    for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
        wpoint_sync_single(world, i);
    }
}

void world_validate_weapon_holders(global_t* world)
{
    if (!world) return;
    for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
        if (!world->is_object_exists[i] || !world->objects[i]) continue;
        object_t* holder = world->objects[i];
        if (holder->weapon_type > 0) {
            int32_t wid = holder->weapon_id;
            if (wid < 0 || wid >= static_cast<int32_t>(MAX_OBJECTS) ||
                !world->is_object_exists[wid] || !world->objects[wid] ||
                world->objects[wid]->holder_id != i) {
                holder->weapon_type = 0;
            }
        }
    }
}

bool try_pickup_weapon(global_t* world, uint32_t char_id)
{
    if (!world || char_id >= MAX_OBJECTS || !world->is_object_exists[char_id]) {
        return false;
    }
    object_t* character = world->objects[char_id];
    if (!character || !character->file || character->hp <= 0) {
        return false;
    }

    if (character->weapon_type != 0 || character->fall > 0) {
        return false;
    }

    for (uint32_t w_id = 0; w_id < MAX_OBJECTS; ++w_id) {
        if (!world->is_object_exists[w_id] || w_id == char_id) continue;
        object_t* weapon = world->objects[w_id];
        if (!weapon || !weapon->file) continue;

        if (weapon->holder_id != 0 || weapon->weapon_type < 0) continue;

        uint32_t w_type = weapon->file->type;
        if (w_type != TYPE_LIGHT_WEAPON && w_type != TYPE_HEAVY_WEAPON &&
            w_type != TYPE_THROW_WEAPON && w_type != TYPE_DRINK) {
            continue;
        }

        int32_t dx = std::abs(character->x - weapon->x);
        int32_t dy = std::abs(character->y - weapon->y);
        int32_t dz = std::abs(character->z - weapon->z);

        if (dx <= 35 && dy <= 30 && dz <= 15) {
            if (w_type == TYPE_LIGHT_WEAPON) {
                character->weapon_type =
                    (weapon->file->id == KNIFE_DAT || weapon->file->id == BOOMERANG_DAT) ? 101 : 1;
                character->frame_id1 = 115;
            } else if (w_type == TYPE_THROW_WEAPON) {
                character->weapon_type = 4;
                character->frame_id1 = 115;
            } else if (w_type == TYPE_DRINK) {
                if (weapon->hp < 1) {
                    character->weapon_type = 4;
                    weapon->weapon_hp = 0;
                } else {
                    character->weapon_type = 6;
                }
                character->frame_id1 = 115;
            } else {
                character->weapon_type = 2;
                character->frame_id1 = 116;
            }

            weapon->weapon_type = -character->weapon_type;
            character->weapon_id = static_cast<int32_t>(w_id);
            weapon->holder_id = static_cast<int32_t>(char_id);
            weapon->owner = static_cast<int32_t>(char_id);
            weapon->team = character->team;

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
    object_t* obj = world->objects[char_id];
    if (!obj) return;

    if (obj->weapon_type < 0) {
        wpoint_sync_single(world, static_cast<int32_t>(char_id));
    } else if (obj->weapon_type > 0 && obj->weapon_id >= 0 &&
               obj->weapon_id < static_cast<int32_t>(MAX_OBJECTS)) {
        wpoint_sync_single(world, obj->weapon_id);
    }
}

void drop_weapon(global_t* world, uint32_t char_id)
{
    if (!world || char_id >= MAX_OBJECTS || !world->is_object_exists[char_id]) {
        return;
    }
    object_t* character = world->objects[char_id];
    if (!character) return;

    int32_t w_id = character->weapon_id;
    if (w_id >= 0 && w_id < static_cast<int32_t>(MAX_OBJECTS) && world->is_object_exists[w_id]) {
        object_t* weapon = world->objects[w_id];
        if (weapon) {
            weapon->weapon_type = 0;
            weapon->frame_id1 = static_cast<uint32_t>(lf2_random(0x8c, 6));
            weapon->x_velocity = static_cast<double>(lf2_random(0x8d, 7) - 3);
            weapon->y_velocity = static_cast<double>(-lf2_random(0x8e, 4));
            weapon->z_velocity = static_cast<double>(lf2_random(0x8f, 5) - 2) / 5.0;
            if (-2.0 < weapon->y_position) {
                weapon->y_position = -2.0;
            }
        }
    }

    character->weapon_type = 0;
}

void throw_weapon(global_t* world, uint32_t char_id)
{
    if (!world || char_id >= MAX_OBJECTS || !world->is_object_exists[char_id]) {
        return;
    }
    object_t* character = world->objects[char_id];
    if (!character || !character->file || character->weapon_type <= 0) {
        return;
    }

    int32_t w_id = character->weapon_id;
    if (w_id < 0 || w_id >= static_cast<int32_t>(MAX_OBJECTS) || !world->is_object_exists[w_id]) {
        character->weapon_type = 0;
        return;
    }

    object_t* weapon = world->objects[w_id];
    if (!weapon || !weapon->file) {
        character->weapon_type = 0;
        return;
    }

    uint32_t c_frame_id = (character->frame_id1 < MAX_FRAMES) ? character->frame_id1 : 0;
    const wpoint_t& wp = character->file->frames[c_frame_id].wpoint;

    double tvx = (wp.dvx != 0) ? static_cast<double>(wp.dvx) : 12.0;
    double tvy = (wp.dvy != 0) ? static_cast<double>(wp.dvy) : -3.0;
    double tvz = static_cast<double>(wp.dvz);

    uint32_t wtype = weapon->file->type;
    if (wtype == TYPE_LIGHT_WEAPON || wtype == TYPE_THROW_WEAPON || wtype == TYPE_DRINK) {
        weapon->weapon_throw_injury = static_cast<int32_t>(char_id);
        weapon->frame_id1 = 40;
    } else {
        weapon->frame_id1 = static_cast<uint32_t>(lf2_random(0x8b, 6));
    }

    weapon->x_velocity = (character->facing == FACING_RIGHT) ? tvx : -tvx;
    weapon->y_velocity = tvy;
    if (character->click_up != 0 && character->click_down == 0) {
        weapon->z_velocity = -tvz;
    } else if (character->click_up == 0 && character->click_down != 0) {
        weapon->z_velocity = tvz;
    }

    character->weapon_type = 0;
    weapon->weapon_type = 0;
}

} // namespace lf2

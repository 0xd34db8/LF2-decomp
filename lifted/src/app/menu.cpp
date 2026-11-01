#include "app/menu.h"
#include "gameplay/entity.h"
#include "core/random.h"
#include <cstring>

namespace lf2 {

const std::vector<roster_entry_t>& get_game_roster() {
    static const std::vector<roster_entry_t> roster = {
        { 0,  "Random",   "data/davis.dat",    "RFACE",                  "sprite/sys/davis_s.bmp" },
        { 11, "Davis",    "data/davis.dat",    "sprite/sys/davis_f.bmp", "sprite/sys/davis_s.bmp" },
        { 10, "Woody",    "data/woody.dat",    "sprite/sys/woody_f.bmp", "sprite/sys/woody_s.bmp" },
        { 9,  "Dennis",   "data/dennis.dat",   "sprite/sys/dennis_f.bmp","sprite/sys/dennis_s.bmp" },
        { 8,  "Freeze",   "data/freeze.dat",   "sprite/sys/freeze_f.bmp","sprite/sys/freeze_s.bmp" },
        { 7,  "Firen",    "data/firen.dat",    "sprite/sys/firen_f.bmp", "sprite/sys/firen_s.bmp" },
        { 6,  "Louis",    "data/louis.dat",    "sprite/sys/louis_f.bmp", "sprite/sys/louis_s.bmp" },
        { 5,  "Rudolf",   "data/rudolf.dat",   "sprite/sys/rudolf_f.bmp","sprite/sys/rudolf_s.bmp" },
        { 4,  "Henry",    "data/henry.dat",    "sprite/sys/henry_f.bmp", "sprite/sys/henry_s.bmp" },
        { 2,  "John",     "data/john.dat",     "sprite/sys/john_f.bmp",  "sprite/sys/john_s.bmp" },
        { 1,  "Deep",     "data/deep.dat",     "sprite/sys/deep_f.bmp",  "sprite/sys/deep_s.bmp" },
        { 30, "Bandit",   "data/bandit.dat",   "sprite/sys/bandit_f.bmp","sprite/sys/bandit_s.bmp" },
        { 31, "Hunter",   "data/hunter.dat",   "sprite/sys/hunter_f.bmp","sprite/sys/hunter_s.bmp" },
        { 32, "Mark",     "data/mark.dat",     "sprite/sys/mark_f.bmp",  "sprite/sys/mark_s.bmp" },
        { 33, "Jack",     "data/jack.dat",     "sprite/sys/jack_f.bmp",  "sprite/sys/jack_s.bmp" },
        { 34, "Sorcerer", "data/sorcerer.dat", "sprite/sys/sorcerer_f.bmp","sprite/sys/sorcerer_s.bmp" },
        { 35, "Monk",     "data/monk.dat",     "sprite/sys/monk_f.bmp",  "sprite/sys/monk_s.bmp" },
        { 36, "Jan",      "data/jan.dat",      "sprite/sys/jan_f.bmp",   "sprite/sys/jan_s.bmp" },
        { 37, "Knight",   "data/knight.dat",   "sprite/sys/knight_f.bmp","sprite/sys/knight_s.bmp" },
        { 38, "Bat",      "data/bat.dat",      "sprite/sys/bat_f.bmp",   "sprite/sys/bat_s.bmp" },
        { 39, "Justin",   "data/justin.dat",   "sprite/sys/justin_f.bmp","sprite/sys/justin_s.bmp" },
        { 50, "LouisEX",  "data/louisEX.dat",  "sprite/sys/louisEX_f.bmp","sprite/sys/louisEX_s.bmp" },
        { 51, "Firzen",   "data/firzen.dat",   "sprite/sys/firzen_f.bmp","sprite/sys/firzen_s.bmp" },
        { 52, "Julian",   "data/julian.dat",   "sprite/sys/julian_f.bmp","sprite/sys/julian_s.bmp" },
    };
    return roster;
}

void setup_battle_characters(global_t* world, const std::vector<player_slot_t>& slots,
                             int32_t stage_min_x, int32_t stage_max_x,
                             int32_t stage_min_z, int32_t stage_max_z)
{
    if (!world) return;

    int32_t width = (stage_max_x > stage_min_x) ? (stage_max_x - stage_min_x) : 200;
    int32_t depth = (stage_max_z > stage_min_z) ? (stage_max_z - stage_min_z) : 150;

    for (size_t i = 0; i < slots.size() && i < MAX_OBJECTS; ++i) {
        const auto& slot = slots[i];
        if (!slot.active) continue;

        object_t* obj = world->objects[i];
        if (!obj) {
            obj = new object_t();
            world->objects[i] = obj;
        }

        object_init(obj);

        // 1:1 Parity with 0x00436900
        obj->hp = 500;
        obj->dark_hp = 500;
        obj->max_hp = 500;
        obj->mp = 500;
        obj->invincible_time = 75; // 0x4B
        obj->team = slot.team;

        // Spawn placement within stage bounds
        obj->x = stage_min_x + static_cast<int32_t>(lf2_random(0x10A + static_cast<uint32_t>(i), width));
        obj->y = 0;
        obj->z = stage_min_z + static_cast<int32_t>(lf2_random(0x10B + static_cast<uint32_t>(i), depth));
        obj->x_position = static_cast<double>(obj->x);
        obj->y_position = static_cast<double>(obj->y);
        obj->z_position = static_cast<double>(obj->z);

        // Orient facing towards stage center
        int32_t center_x = (stage_min_x + stage_max_x) / 2;
        obj->facing = (obj->x < center_x) ? FACING_RIGHT : FACING_LEFT;

        world->is_object_exists[i] = 1;
    }
}

} // namespace lf2

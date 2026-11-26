#include "entity.h"
#include "audio/audio.h"
#include "core/overlap.h"
#include "core/random.h"
#include "gameplay/grapple.h"
#include <cmath>
#include <cstring>
#include <algorithm>

namespace lf2 {

// VERIFIED: LF2 0x004061d0
void object_init(object_t* obj)
{
    if (!obj) return;

    std::memset(obj, 0, sizeof(object_t));

    // Exact ground-truth initializations from FUN_004061d0 (0x004061D0)
    obj->attackable_distance = 1000;   // 0x2E8
    obj->vulnerable_distance = 1000;   // 0x2EC
    obj->clone = -1;                   // 0x2F4
    obj->under_attack_distance = 1000; // 0x2F8

    obj->hp = 500;                     // 0x2FC
    obj->dark_hp = 500;                // 0x300
    obj->max_hp = 500;                 // 0x304
    obj->mp = 500;                     // 0x308

    obj->weapon_hp = 1000;             // 0x31C
    obj->uid = -1;                     // 0x324
    obj->_unknown34[0] = static_cast<uint32_t>(-1); // 0x328
    obj->owner = -1;                   // 0x354
    obj->enemy = -1;                   // 0x360

    obj->chase_target = -1;            // 0x3F8
    obj->ai_target_x = -1000;          // 0x3FC
    obj->ai_target_z = -1000;          // 0x400
}

// VERIFIED: LF2 0x00406a20
int32_t object_spawn_opoint(global_t* world, int32_t file_id, int32_t owner, int32_t frame_id,
                            int32_t team, int32_t x, int32_t y, int32_t z,
                            double vx, double vy, double vz, uint8_t facing)
{
    if (!world) return -1;

    int32_t slot = -1;
    for (int32_t i = 50; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
        if (world->is_object_exists[i] == 0) {
            slot = i;
            break;
        }
    }
    if (slot == -1) return -1;

    for (uint32_t f = 0; f < MAX_FILES; ++f) {
        file_t* file = world->files[f];
        if (file && static_cast<int32_t>(file->id) == file_id) {
            if (!world->objects[slot]) {
                world->objects[slot] = new object_t();
            }
            object_t* obj = world->objects[slot];
            object_init(obj);
            obj->file = file;
            obj->x_position = 580.0;
            obj->y_position = -200.0;
            obj->weapon_hp = file->weapon_hp;
            obj->z_position = 300.0;
            obj->owner = owner;
            obj->x = x;
            obj->y = y;
            obj->z = z;
            obj->team = static_cast<uint32_t>(team);
            obj->x_position = static_cast<double>(x);
            obj->y_position = static_cast<double>(y);
            obj->z_position = static_cast<double>(z);
            obj->frame_id1 = static_cast<uint32_t>(frame_id);
            obj->x_velocity = vx;
            obj->y_velocity = vy;
            obj->z_velocity = vz;
            obj->facing = facing;
            world->is_object_exists[slot] = 1;
            return slot;
        }
    }
    return -1;
}

// VERIFIED: LF2 0x00406ba0
void object_process_hit_fa(global_t* world, int32_t obj_idx)
{
    if (!world || obj_idx < 0 || obj_idx >= static_cast<int32_t>(MAX_OBJECTS) ||
        !world->is_object_exists[obj_idx]) {
        return;
    }
    object_t* obj = world->objects[obj_idx];
    if (!obj || !obj->file || obj->frame_id1 >= MAX_FRAMES) return;

    int32_t hit_fa = static_cast<int32_t>(obj->file->frames[obj->frame_id1].hit_Fa);
    int32_t team_i = static_cast<int32_t>(obj->team);

    if (hit_fa == 11) {
        object_spawn_opoint(world, FIREN_FLAME_DAT, obj->owner, 109, team_i, obj->x, obj->y, obj->z,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity, obj->facing);
        object_spawn_opoint(world, FIRZEN_CHASEF_DAT, obj->owner, 81, team_i, obj->x, obj->y - 100, obj->z,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity, obj->facing);
        object_spawn_opoint(world, FREEZE_COLUMN_DAT, obj->owner, 100, team_i, obj->x + 80, obj->y - 3, obj->z,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity - 7.0, FACING_RIGHT);
        object_spawn_opoint(world, FREEZE_COLUMN_DAT, obj->owner, 100, team_i, obj->x + 100, obj->y - 3, obj->z,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_RIGHT);
        object_spawn_opoint(world, FREEZE_COLUMN_DAT, obj->owner, 100, team_i, obj->x + 80, obj->y - 3, obj->z,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity + 7.0, FACING_RIGHT);
        object_spawn_opoint(world, FREEZE_COLUMN_DAT, obj->owner, 100, team_i, obj->x - 80, obj->y - 3, obj->z,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity - 7.0, FACING_LEFT);
        object_spawn_opoint(world, FREEZE_COLUMN_DAT, obj->owner, 100, team_i, obj->x - 100, obj->y - 3, obj->z,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_LEFT);
        object_spawn_opoint(world, FREEZE_COLUMN_DAT, obj->owner, 100, team_i, obj->x - 80, obj->y - 3, obj->z,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity + 7.0, FACING_LEFT);
        object_spawn_opoint(world, FIREN_FLAME_DAT, obj->owner, 50, team_i, obj->x - 30, obj->y - 1, obj->z - 5,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_LEFT);
        object_spawn_opoint(world, FIREN_FLAME_DAT, obj->owner, 50, team_i, obj->x + 30, obj->y - 1, obj->z - 5,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_LEFT);
        object_spawn_opoint(world, FIREN_FLAME_DAT, obj->owner, 50, team_i, obj->x - 30, obj->y - 1, obj->z + 2,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_RIGHT);
        object_spawn_opoint(world, FIREN_FLAME_DAT, obj->owner, 50, team_i, obj->x + 30, obj->y - 1, obj->z + 2,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_RIGHT);
        object_spawn_opoint(world, FIREN_FLAME_DAT, obj->owner, 50, team_i, obj->x, obj->y - 1, obj->z - 9,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_LEFT);
        object_spawn_opoint(world, FIREN_FLAME_DAT, obj->owner, 50, team_i, obj->x, obj->y - 1, obj->z + 6,
                            obj->x_velocity, obj->y_velocity, obj->z_velocity, FACING_RIGHT);
        world->is_object_exists[obj_idx] = 0;
        return;
    }

    if (hit_fa == 8) {
        int32_t candidates[MAX_OBJECTS];
        int32_t cand_count = 0;
        for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
            if (world->is_object_exists[i] && world->objects[i] && world->objects[i]->file) {
                object_t* cand = world->objects[i];
                if (cand->file->type == TYPE_CHARACTER && cand->team != obj->team && cand->hp > 0) {
                    candidates[cand_count++] = i;
                }
            }
        }
        int32_t amount = (cand_count > 4) ? ((cand_count - 3) / 2 + 3) : 3;
        while (amount > 0) {
            int32_t s = object_spawn_opoint(world, BAT_CHASE_DAT, obj->owner, 0, team_i,
                                            obj->x, obj->y, obj->z, 0.0, 0.0, 0.0, obj->facing);
            if (s != -1) {
                object_t* bat = world->objects[s];
                bat->x_velocity = static_cast<double>(lf2_random(4, 21) - 11);
                bat->y_velocity = 3.0 - static_cast<double>(lf2_random(5, 24)) * 0.25;
                bat->z_velocity = 3.0 - static_cast<double>(lf2_random(6, 24)) * 0.25;
                bat->chase_target = (cand_count == 0) ? obj_idx : candidates[lf2_random(7, cand_count)];
            }
            amount--;
        }
        world->is_object_exists[obj_idx] = 0;
        return;
    }

    if (hit_fa == 13) {
        int32_t candidates[MAX_OBJECTS];
        int32_t cand_count = 0;
        for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
            if (world->is_object_exists[i] && world->objects[i] && world->objects[i]->file) {
                object_t* cand = world->objects[i];
                if (cand->file->type == TYPE_CHARACTER && cand->team != obj->team && cand->hp > 0) {
                    candidates[cand_count++] = i;
                }
            }
        }
        int32_t s = object_spawn_opoint(world, JULIAN_BALL_DAT, obj->owner, 0, team_i,
                                        obj->x, obj->y, obj->z, obj->x_velocity, 0.0, 0.0, obj->facing);
        if (s != -1) {
            object_t* jb = world->objects[s];
            jb->y = lf2_random(8, 7) - 3 + obj->y;
            jb->x_position = obj->x_position;
            jb->y_position = obj->y_position;
            jb->z_position = obj->z_position;
            jb->z_velocity = (3.0 - static_cast<double>(lf2_random(11, 24)) * 0.25) + obj->z_velocity;
            jb->chase_target = (cand_count == 0) ? obj_idx : candidates[lf2_random(12, cand_count)];
        }
        world->is_object_exists[obj_idx] = 0;
        return;
    }

    if (hit_fa == 5) {
        for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
            if (world->is_object_exists[i] == 1 && world->objects[i] && world->objects[i]->file) {
                object_t* ally = world->objects[i];
                if (ally->file->type == TYPE_CHARACTER && ally->team == obj->team && ally->hp > 0) {
                    int32_t s = object_spawn_opoint(world, JAN_CHASEH_DAT, obj->owner, 0, team_i,
                                                    obj->x, obj->y, obj->z, 0.0, 0.0, 0.0, FACING_RIGHT);
                    if (s != -1) {
                        object_t* angel = world->objects[s];
                        angel->x_velocity = static_cast<double>((ally->x - angel->x) / 50);
                        angel->y_velocity = 0.0;
                        angel->z_velocity = 0.0;
                        angel->facing = FACING_RIGHT;
                        angel->chase_target = i;
                    }
                }
            }
        }
        world->is_object_exists[obj_idx] = 0;
        return;
    }

    if (hit_fa == 6 || hit_fa == 9) {
        int32_t minimum = (hit_fa == 9) ? 4 : 0;
        int32_t maximum = (hit_fa == 6) ? 7 : 10;
        int32_t spawned = 0;
        int32_t pass = 0;
        int32_t last_slot = -1;
        do {
            for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
                if (world->is_object_exists[i] == 1 && world->objects[i] && world->objects[i]->file) {
                    object_t* enemy = world->objects[i];
                    if (enemy->file->type == TYPE_CHARACTER && enemy->team != obj->team && enemy->hp > 0 &&
                        (spawned < minimum || pass == 0)) {
                        spawned++;
                        int32_t spawn_fid = (hit_fa == 6)
                            ? static_cast<int32_t>(JAN_CHASE_DAT)
                            : (static_cast<int32_t>(FIRZEN_CHASEF_DAT) + lf2_random(13, 2));
                        last_slot = object_spawn_opoint(world, spawn_fid, obj->owner, 0, team_i,
                                                        obj->x, obj->y, obj->z, 0.0, 0.0, 0.0, FACING_RIGHT);
                        if (last_slot == -1) break;
                        object_t* sp = world->objects[last_slot];
                        if (hit_fa == 6) {
                            sp->x_velocity = static_cast<double>((enemy->x - sp->x) / 50);
                            sp->y_velocity = static_cast<double>(-4 - lf2_random(14, 4));
                        } else {
                            sp->x_velocity = static_cast<double>(lf2_random(15, 21) - 11);
                            sp->y_velocity = -2.0 - static_cast<double>(lf2_random(16, 40)) / 6.0;
                        }
                        sp->z_velocity = 0.0;
                        sp->facing = FACING_RIGHT;
                        sp->chase_target = i;
                        if (spawned >= maximum) break;
                    }
                }
            }
            pass++;
        } while (spawned < minimum && spawned != 0 && last_slot != -1 && spawned < maximum);
        world->is_object_exists[obj_idx] = 0;
        return;
    }

    if (hit_fa == 7) {
        object_spawn_opoint(world, static_cast<int32_t>(obj->file->id), obj->owner, 40, team_i,
                            obj->x, obj->y, obj->z, 0.0, 0.0, 0.0, FACING_RIGHT);
    } else if (hit_fa == 10) {
        obj->x_velocity += (obj->x_velocity >= 0.0) ? 1.1 : -1.1;
        if (obj->x_velocity > 30.0) obj->x_velocity = 30.0;
        if (obj->x_velocity < -30.0) obj->x_velocity = -30.0;
        if (obj->y_position > 3.0) obj->y_position = 3.0;
        obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;
        return;
    }

    int32_t deflected_team = -1;
    if (obj->weapon_throw_injury >= 0 && obj->weapon_throw_injury < static_cast<int32_t>(MAX_OBJECTS) &&
        world->is_object_exists[obj->weapon_throw_injury] == 1 && world->objects[obj->weapon_throw_injury]) {
        deflected_team = static_cast<int32_t>(world->objects[obj->weapon_throw_injury]->team);
    }

    if (hit_fa != 4 && hit_fa != 5 && hit_fa != 6 && hit_fa != 7) {
        int32_t tid = obj->chase_target;
        bool valid_target = false;
        if (tid >= 0 && tid < static_cast<int32_t>(MAX_OBJECTS) && world->is_object_exists[tid] &&
            world->objects[tid] && world->objects[tid]->file &&
            world->objects[tid]->frame_id1 < MAX_FRAMES) {
            object_t* t = world->objects[tid];
            if (t->hp > 0 && t->file->frames[t->frame_id1].state != STATE_LYING &&
                std::abs(t->blink_time) < 3 &&
                t->team != obj->team && static_cast<int32_t>(t->team) != deflected_team) {
                valid_target = true;
            }
        }
        if (!valid_target) {
            int32_t best_dist = 10000;
            for (int32_t i = 0; i < static_cast<int32_t>(MAX_OBJECTS); ++i) {
                if (i == obj_idx || !world->is_object_exists[i] || !world->objects[i] || !world->objects[i]->file) {
                    continue;
                }
                object_t* cand = world->objects[i];
                if (cand->file->type == TYPE_CHARACTER && cand->team != obj->team &&
                    static_cast<int32_t>(cand->team) != deflected_team &&
                    cand->frame_id1 < MAX_FRAMES) {
                    if (cand->file->frames[cand->frame_id1].state == STATE_LYING ||
                        std::abs(cand->blink_time) > 2) {
                        if (obj->chase_target != -1) continue;
                    }
                    if (cand->hp > 0) {
                        int32_t d = std::abs(cand->z - obj->z) + std::abs(cand->x - obj->x);
                        if (d < best_dist) {
                            best_dist = d;
                            obj->chase_target = i;
                        }
                    }
                }
            }
            if (obj->chase_target == -1) {
                obj->hp = 0;
                return;
            }
        }
    }

    int32_t target_id = obj->chase_target;
    if (target_id < 0 || target_id >= static_cast<int32_t>(MAX_OBJECTS) || !world->objects[target_id]) return;
    object_t* target = world->objects[target_id];

    if (hit_fa == 1) {
        if (obj->x < target->x) obj->x_velocity += 0.85;
        if (target->x < obj->x) obj->x_velocity -= 0.85;
        if (obj->z + 7 < target->z) obj->z_velocity += 0.3;
        if (target->z < obj->z - 7) obj->z_velocity -= 0.3;
        obj->y_velocity /= 1.4;
        if (target->file && target->file->type == TYPE_CHARACTER) {
            if (obj->y_position + 10.0 < target->y_position) obj->y_position += 1.2;
            if (target->y_position < obj->y_position + 10.0) obj->y_position -= 1.2;
        } else if (obj->y_position > 0.0) {
            obj->y_position += 1.0;
        }
        if (obj->x_velocity > 13.0) obj->x_velocity = 13.0;
        if (obj->x_velocity < -13.0) obj->x_velocity = -13.0;
        if (obj->z_velocity > 2.0) obj->z_velocity = 2.0;
        if (obj->z_velocity < -2.0) obj->z_velocity = -2.0;
        if (obj->y_position > 1.0) obj->y_position = 1.0;
        obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;
        return;
    }

    if (hit_fa == 4 && target->hp > 0 &&
        target->x - 30 < obj->x && obj->x < target->x + 30 &&
        target->y - 80 < obj->y && obj->y < target->y &&
        target->z - 10 < obj->z && obj->z < target->z + 10) {
        obj->x_velocity = 0.0;
        obj->y_velocity = 0.0;
        obj->z_velocity = 0.0;
        obj->frame_id1 = 60;
        target->heal_timer = 100;
        return;
    }

    bool chasing = (hit_fa == 2 || hit_fa == 4 || hit_fa == 7 || hit_fa == 12 || hit_fa == 14);
    if (chasing && obj->hp > 0 && world->is_object_exists[obj_idx] == 1) {
        if (obj->x < target->x) obj->x_velocity += 0.7;
        if (target->x < obj->x) obj->x_velocity -= 0.7;
        if (hit_fa == 7) {
            if (obj->x < target->x) obj->x_velocity += 0.7;
            if (target->x < obj->x) obj->x_velocity -= 0.7;
        }
        if (obj->z + 5 < target->z) obj->z_velocity += 0.4;
        if (target->z < obj->z - 5) obj->z_velocity -= 0.4;

        if (hit_fa == 2 || hit_fa == 4 || hit_fa == 12) {
            obj->y_velocity /= 1.4;
            if (target->file && target->file->type == TYPE_CHARACTER) {
                if (obj->y_position + 40.0 < target->y_position) obj->y_position += 1.0;
                if (target->y_position < obj->y_position + 40.0) obj->y_position -= 1.0;
            } else if (obj->y_position > 0.0) {
                obj->y_position += 1.0;
            }
        } else if (hit_fa == 7) {
            if (obj->y_velocity < 4.0) obj->y_velocity += 0.4;
            obj->y_position += obj->y_velocity;
            if (obj->y > -25) {
                obj->frame_id1 = 60;
                obj->x_velocity = 0.0;
                obj->y_velocity = 0.0;
                obj->z_velocity = 0.0;
            }
        }

        if (obj->x_velocity > 14.0) obj->x_velocity = 14.0;
        if (obj->x_velocity < -14.0) obj->x_velocity = -14.0;
        if (obj->y_position > 1.4) obj->y_position = 1.4;
        double max_z = (hit_fa == 14) ? 1.5 : 2.2;
        if (obj->z_velocity > max_z) obj->z_velocity = max_z;
        if (obj->z_velocity < -max_z) obj->z_velocity = -max_z;
        obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;

        double speed = std::abs(obj->x_velocity);
        if (hit_fa == 14) {
            if (speed >= 8.0) {
                if (obj->frame_id1 >= 41) obj->frame_id1 -= 50;
            } else {
                if (obj->frame_id1 < 10) obj->frame_id1 += 50;
            }
            return;
        }
        if (hit_fa == 2) {
            if (speed > 14.0) {
                if (obj->frame_id1 != 5 && obj->frame_id1 != 6) obj->frame_id1 = 5;
            } else if (speed > 7.0) {
                if (obj->frame_id1 != 3 && obj->frame_id1 != 4) obj->frame_id1 = 3;
            } else if (obj->frame_id1 != 1 && obj->frame_id1 != 2) {
                obj->frame_id1 = 1;
            }
        }
        return;
    }

    if (chasing && (obj->hp <= 0 || world->is_object_exists[obj_idx] == 0)) {
        obj->x_velocity += (obj->x_velocity >= 0.0) ? 2.0 : -2.0;
        if (obj->x_velocity > 17.0) obj->x_velocity = 17.0;
        if (obj->x_velocity < -17.0) obj->x_velocity = -17.0;
        if (hit_fa == 2 || hit_fa == 4 || hit_fa == 14 || hit_fa == 12) {
            if (obj->y_position > 1.4) obj->y_position = 1.4;
        } else if (hit_fa == 7) {
            if (obj->y_velocity < 4.0) obj->y_velocity += 0.4;
            obj->y_position += obj->y_velocity;
            if (obj->y > -25) {
                obj->frame_id1 = 60;
                obj->y = -25;
                obj->x_velocity = 0.0;
                obj->y_velocity = 0.0;
                obj->z_velocity = 0.0;
            }
        }
        obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;
        double speed = std::abs(obj->x_velocity);
        if (hit_fa == 2) {
            if (speed > 14.0) {
                if (obj->frame_id1 != 5 && obj->frame_id1 != 6) obj->frame_id1 = 5;
            } else if (speed > 7.0) {
                if (obj->frame_id1 != 3 && obj->frame_id1 != 4) obj->frame_id1 = 3;
            } else if (obj->frame_id1 != 1 && obj->frame_id1 != 2) {
                obj->frame_id1 = 1;
            }
        }
        return;
    }

    if (hit_fa == 3) {
        if (obj->x < target->x) obj->x_velocity += 0.7;
        if (target->x < obj->x) obj->x_velocity -= 0.7;
        if (obj->z + 10 < target->z) obj->z_velocity += 0.17;
        if (target->z < obj->z - 10) obj->z_velocity -= 0.17;
        if (obj->x_velocity > 16.0) obj->x_velocity = 16.0;
        if (obj->x_velocity < -16.0) obj->x_velocity = -16.0;
        if (obj->z_velocity > 2.4) obj->z_velocity = 2.4;
        if (obj->z_velocity < -2.4) obj->z_velocity = -2.4;
    }
}

namespace {

constexpr uint32_t BINARY_STATE_FIRE = 19; // Binary 0x13 (legacy_types STATE_FIRE)
constexpr int32_t  HEAVY_WEAPON_TYPE = static_cast<int32_t>(TYPE_HEAVY_WEAPON);

void trigger_frame_sound(const object_t* obj, uint32_t fid)
{
    if (!obj || !obj->file || fid >= MAX_FRAMES) return;
    const frame_t& f = obj->file->frames[fid];
    if (f.sound_id >= 0) {
        get_audio_system().queue_item_sound(obj->x, f.sound_id);
    } else if (f.sound > 0) {
        get_audio_system().queue_item_sound(obj->x, static_cast<int32_t>(f.sound));
    }
}

void deduct_frame_mp(object_t* obj, int32_t fid, bool match_running)
{
    if (!match_running || fid < 0 || fid >= static_cast<int32_t>(MAX_FRAMES)) return;
    int32_t cost = obj->file->frames[fid].mp;
    obj->mp -= cost;
    if (obj->mp < 0) {
        obj->mp = 0;
    } else {
        obj->mp_used += static_cast<uint32_t>(cost);
    }
}

void run_standard_combo(object_t* obj, uint8_t& combo_stage,
                        uint8_t mid_press, char mid_key,
                        uint8_t final_press, char final_key,
                        uint32_t frame_t::* target_field,
                        int32_t override_facing, bool match_running)
{
    if (!obj || !obj->file) return;

    int32_t advanced = 0;
    if (combo_stage == 0 && obj->defend_press == 5) {
        combo_stage = 1;
        advanced = 1;
    }
    if (combo_stage == 1) {
        if (mid_press == 5) {
            combo_stage = 2;
            advanced = 1;
        } else if (object_combo_interrupted(obj, 'd', advanced) != 0) {
            combo_stage = 0;
        }
    }
    if (combo_stage == 2) {
        if (final_press == 5) {
            combo_stage = 3;
            advanced = 1;
        } else if (object_combo_interrupted(obj, mid_key, advanced) != 0) {
            combo_stage = 0;
        }
    }
    if (combo_stage == 3) {
        if (obj->frame_id1 < MAX_FRAMES) {
            int32_t target = static_cast<int32_t>(obj->file->frames[obj->frame_id1].*target_field);
            if (target != 0 && obj->weapon_type != HEAVY_WEAPON_TYPE) {
                object_frame_transition(obj, target, match_running);
                if (override_facing >= 0) {
                    obj->facing = static_cast<uint8_t>(override_facing);
                }
                combo_stage = 0;
                return;
            }
        }
        if (object_combo_interrupted(obj, final_key, advanced) != 0) {
            combo_stage = 0;
        }
    }
}

void step_grid_walk_cycle(object_t* obj, int32_t frame_rate, uint32_t base_frame, uint32_t peak_offset)
{
    int32_t mc = (static_cast<int32_t>(obj->move_counter) + 1) % (frame_rate * 6);
    obj->move_counter = static_cast<uint32_t>(mc);
    obj->frame_id1 = (mc < frame_rate * 4)
        ? (static_cast<uint32_t>(mc / frame_rate) + base_frame)
        : (base_frame + peak_offset - static_cast<uint32_t>(mc / frame_rate));
}

void step_grid_run_cycle(object_t* obj, int32_t frame_rate, uint32_t base_frame)
{
    int32_t mc = (static_cast<int32_t>(obj->move_counter) + 1) % (frame_rate * 4);
    obj->move_counter = static_cast<uint32_t>(mc);
    obj->frame_id1 = (mc < frame_rate * 3)
        ? (static_cast<uint32_t>(mc / frame_rate) + base_frame)
        : (base_frame + 1U);
}

void apply_ground_drag(double& vel, double friction)
{
    if (0.0001 < vel) {
        double nv = vel - friction;
        vel = (nv < 0.0001) ? 0.0 : nv;
    } else if (vel < -0.0001) {
        double nv = vel + friction;
        vel = (0.0001 < nv) ? 0.0 : nv;
    }
}

} // namespace

// 1:1 Lift of 0x0040E450: 5-entry input history shift register
// VERIFIED: LF2 0x0040e450
void object_input_history_push(object_t* obj, uint32_t key_code)
{
    if (!obj) return;
    obj->input_history[0] = obj->input_history[1];
    obj->input_history[1] = obj->input_history[2];
    obj->input_history[2] = obj->input_history[3];
    obj->input_history[3] = obj->input_history[4];
    obj->input_history[4] = static_cast<int32_t>(key_code);
}

// 1:1 Lift of 0x0040E170: Combo timer == 5 interruption check helper
// VERIFIED: LF2 0x0040e170
int32_t object_combo_interrupted(const object_t* obj, char expected_key, int32_t advanced)
{
    if (!obj) return 0;

    if (advanced == 0) {
        if (obj->attack_press == 5 || obj->jump_press == 5 || obj->defend_press == 5 ||
            obj->left_press == 5 || obj->up_press == 5 || obj->down_press == 5 ||
            obj->right_press == 5) {
            return 1;
        }
        return 0;
    }

    if (advanced != 1) {
        return 0;
    }

    switch (expected_key) {
    case 'U':
        return (obj->attack_press == 5 || obj->jump_press == 5 || obj->defend_press == 5 ||
                obj->left_press == 5 || obj->down_press == 5 || obj->right_press == 5) ? 1 : 0;
    case 'D':
        return (obj->attack_press == 5 || obj->jump_press == 5 || obj->defend_press == 5 ||
                obj->left_press == 5 || obj->up_press == 5 || obj->right_press == 5) ? 1 : 0;
    case 'L':
        return (obj->attack_press == 5 || obj->jump_press == 5 || obj->defend_press == 5 ||
                obj->up_press == 5 || obj->down_press == 5 || obj->right_press == 5) ? 1 : 0;
    case 'R':
        return (obj->attack_press == 5 || obj->jump_press == 5 || obj->defend_press == 5 ||
                obj->left_press == 5 || obj->up_press == 5 || obj->down_press == 5) ? 1 : 0;
    case 'd':
        return (obj->attack_press == 5 || obj->jump_press == 5 || obj->left_press == 5 ||
                obj->up_press == 5 || obj->down_press == 5 || obj->right_press == 5) ? 1 : 0;
    case 'j':
        return (obj->attack_press == 5 || obj->defend_press == 5 || obj->left_press == 5 ||
                obj->up_press == 5 || obj->down_press == 5 || obj->right_press == 5) ? 1 : 0;
    case 'a':
        return (obj->jump_press == 5 || obj->defend_press == 5 || obj->left_press == 5 ||
                obj->up_press == 5 || obj->down_press == 5 || obj->right_press == 5) ? 1 : 0;
    default:
        return 0;
    }
}

// 1:1 Lift of 0x0040E2D0: Frame transition & HP/MP cost helper
// VERIFIED: LF2 0x0040e2d0
int32_t object_frame_transition(object_t* obj, int32_t target_frame, bool match_running)
{
    if (!obj || !obj->file) return 0;

    bool flip_facing = (target_frame < 0);
    if (flip_facing) {
        target_frame = -target_frame;
    }
    if (target_frame == 999) {
        target_frame = 0;
    }
    if (target_frame < 0 || target_frame >= static_cast<int32_t>(MAX_FRAMES)) {
        return 0;
    }

    int32_t frame_byte_off = target_frame * static_cast<int32_t>(sizeof(frame_t));
    const frame_t& target = obj->file->frames[target_frame];
    if (target.present != 0) {
        if (!match_running) {
            obj->frame_id1 = static_cast<uint32_t>(target_frame);
            obj->jump_press = 0;
            obj->attack_press = 0;
            obj->defend_press = 0;
            obj->down_press = 0;
            obj->up_press = 0;
            obj->left_press = 0;
            obj->right_press = 0;
            return frame_byte_off;
        }
        int32_t hp_div = target.mp / 1000;
        if (target.mp % 1000 <= obj->mp) {
            int32_t hp_cost = hp_div * 10;
            if (hp_cost < obj->hp) {
                obj->hp += hp_div * -10;
                obj->mp -= target.mp % 1000;
                obj->hp_lost += static_cast<uint32_t>(hp_cost);
                int32_t raw_mp = target.mp;
                frame_byte_off = raw_mp / 1000;
                obj->frame_id1 = static_cast<uint32_t>(target_frame);
                obj->mp_used += static_cast<uint32_t>(raw_mp % 1000);
                if (flip_facing) {
                    obj->facing = static_cast<uint8_t>(1U - obj->facing);
                }
                obj->jump_press = 0;
                obj->attack_press = 0;
                obj->defend_press = 0;
                obj->down_press = 0;
                obj->up_press = 0;
                obj->left_press = 0;
                obj->right_press = 0;
            }
        }
        return frame_byte_off;
    }
    return frame_byte_off;
}

// 1:1 Lifts of 0x00412800..0x00412F40: 9 special-move combo recognizers
// VERIFIED: LF2 0x00412800
void object_combo_dra(object_t* obj, bool match_running)
{
    run_standard_combo(obj, obj->click_DRA, obj->right_press, 'R', obj->attack_press, 'a',
                       &frame_t::hit_Fa, FACING_RIGHT, match_running);
}

// VERIFIED: LF2 0x004128f0
void object_combo_dla(object_t* obj, bool match_running)
{
    run_standard_combo(obj, obj->click_DLA, obj->left_press, 'L', obj->attack_press, 'a',
                       &frame_t::hit_Fa, FACING_LEFT, match_running);
}

// VERIFIED: LF2 0x004129e0
void object_combo_dua(object_t* obj, bool match_running)
{
    run_standard_combo(obj, obj->click_DUA, obj->up_press, 'U', obj->attack_press, 'a',
                       &frame_t::hit_Ua, -1, match_running);
}

// VERIFIED: LF2 0x00412ac0
void object_combo_dda(object_t* obj, bool match_running)
{
    run_standard_combo(obj, obj->click_DDA, obj->down_press, 'D', obj->attack_press, 'a',
                       &frame_t::hit_Da, -1, match_running);
}

// VERIFIED: LF2 0x00412ba0
void object_combo_drj(object_t* obj, bool match_running)
{
    run_standard_combo(obj, obj->click_DRJ, obj->right_press, 'R', obj->jump_press, 'j',
                       &frame_t::hit_Fj, FACING_RIGHT, match_running);
}

// VERIFIED: LF2 0x00412c90
void object_combo_dlj(object_t* obj, bool match_running)
{
    run_standard_combo(obj, obj->click_DLJ, obj->left_press, 'L', obj->jump_press, 'j',
                       &frame_t::hit_Fj, FACING_LEFT, match_running);
}

// VERIFIED: LF2 0x00412d80
void object_combo_duj(object_t* obj, bool match_running)
{
    run_standard_combo(obj, obj->click_DUJ, obj->up_press, 'U', obj->jump_press, 'j',
                       &frame_t::hit_Uj, -1, match_running);
}

// VERIFIED: LF2 0x00412e60
void object_combo_ddj(object_t* obj, bool match_running)
{
    run_standard_combo(obj, obj->click_DDJ, obj->down_press, 'D', obj->jump_press, 'j',
                       &frame_t::hit_Dj, -1, match_running);
}

// VERIFIED: LF2 0x00412f40
void object_combo_dja(object_t* obj, bool match_running, int32_t unlock_chars)
{
    if (!obj || !obj->file) return;

    int32_t advanced = 0;
    if (obj->click_DJA == 0 && obj->defend_press == 5) {
        obj->click_DJA = 1;
        advanced = 1;
    }
    if (obj->click_DJA == 1) {
        if (obj->jump_press == 5) {
            obj->click_DJA = 2;
            advanced = 1;
        } else if (object_combo_interrupted(obj, 'd', advanced) != 0) {
            obj->click_DJA = 0;
        }
    }
    if (obj->click_DJA == 2) {
        if (obj->attack_press == 5) {
            obj->click_DJA = 3;
            advanced = 1;
        } else if (object_combo_interrupted(obj, 'j', advanced) != 0) {
            obj->click_DJA = 0;
        }
    }
    if (obj->click_DJA == 3 && obj->frame_id1 < MAX_FRAMES) {
        int32_t target = static_cast<int32_t>(obj->file->frames[obj->frame_id1].hit_ja);
        if (obj->file->id != LOUIS_DAT || target != 300 || obj->hp < 178 || unlock_chars != 0) {
            if (target != 0 && obj->uid == -1 && obj->weapon_type != HEAVY_WEAPON_TYPE) {
                object_frame_transition(obj, target, match_running);
                obj->click_DJA = 0;
                return;
            }
            if (static_cast<int32_t>(obj->_unknown34[0]) == 1) {
                obj->firen_counter = 0;
                return;
            }
            if (object_combo_interrupted(obj, 'a', advanced) != 0) {
                obj->click_DJA = 0;
            }
        }
    }
}

// 1:1 Lift of 0x0040D960: Per-object frame timer, sound trigger & frame.next advancement
// VERIFIED: LF2 0x0040d960
void object_frame_advance(object_t* obj, int32_t mode, int32_t obj_idx, int32_t difficulty, bool match_running)
{
    if (!obj || !obj->file) return;

    if (obj->shaking != 0 && obj->file->type != TYPE_ATTACK) {
        return;
    }
    if (obj->arest > 0) {
        obj->arest--;
    }
    if (obj->weapon_type < 0) {
        return;
    }
    if (obj->frame_id1 >= MAX_FRAMES) {
        return;
    }

    file_t* file = obj->file;
    const frame_t& cur = file->frames[obj->frame_id1];
    if (cur.cpoint.kind == 2) {
        return;
    }

    if (file->type == TYPE_ATTACK && static_cast<int32_t>(cur.hit_a) > 0) {
        obj->hp -= static_cast<int32_t>(cur.hit_a);
        if (obj->hp < 1) {
            obj->hp = 0;
            obj->frame_id1 = cur.hit_d;
        }
    }

    if (obj->blink_time > 0) {
        obj->blink_time--;
    }
    if (obj->blink_time < 0) {
        obj->blink_time++;
    }
    if (obj->fall > 0) {
        obj->fall--;
    }
    if (obj->bdefend > 0) {
        obj->bdefend--;
    }
    if (static_cast<int8_t>(obj->can_hit_flag) > 0) {
        obj->can_hit_flag--;
    }

    if (obj->frame_id1 != obj->frame_id2 && obj->frame_id1 < MAX_FRAMES) {
        trigger_frame_sound(obj, obj->frame_id1);
        obj->wait_counter = 0;
    }

    obj->wait_counter++;

    if (static_cast<int32_t>(file->type) >= 0 && obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == STATE_STANDING && obj->y < 0) {
        obj->frame_id1 = 212;
    }
    if (file->type == TYPE_HEAVY_WEAPON && obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == 2000 && obj->y == 0 &&
        obj->x_velocity < 0.1 && -0.1 < obj->x_velocity) {
        obj->frame_id1 = 20;
    }
    if (obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == STATE_LYING && obj->hp < 1) {
        if ((obj->clone >= 0 || obj->team == 5 || obj_idx > 19) && obj->blink_time < 1) {
            obj->blink_time = 30;
        }
        obj->wait_counter = 0;
    }
    if (obj->frame_id1 < MAX_FRAMES && file->frames[obj->frame_id1].state == 2000) {
        obj->facing = (obj->x_velocity <= 0.0) ? FACING_LEFT : FACING_RIGHT;
    }

    if (obj->frame_id1 < MAX_FRAMES &&
        obj->wait_counter > static_cast<int32_t>(file->frames[obj->frame_id1].wait)) {
        obj->wait_counter = 0;
        int32_t next_frame = file->frames[obj->frame_id1].next;
        if (next_frame != 0) {
            obj->frame_id1 = static_cast<uint32_t>(next_frame);
            if (static_cast<int32_t>(obj->frame_id1) < 0) {
                obj->facing = static_cast<uint8_t>(1U - obj->facing);
                obj->frame_id1 = static_cast<uint32_t>(-static_cast<int32_t>(obj->frame_id1));
            }
            bool airborne_from_999 = false;
            if (obj->frame_id1 == 999) {
                if (obj->y == 0 || file->type != TYPE_CHARACTER) {
                    obj->frame_id1 = 0;
                } else {
                    airborne_from_999 = true;
                    obj->frame_id1 = 212;
                }
            }
            if (static_cast<int32_t>(obj->frame_id1) < 0 || static_cast<int32_t>(obj->frame_id1) > 399) {
                return;
            }

            if (obj->frame_id2 < MAX_FRAMES &&
                file->frames[obj->frame_id2].state == STATE_LYING &&
                file->frames[obj->frame_id1].state != STATE_ICE &&
                (((obj->team != 5 && obj->player_index == 0) || difficulty != 2) &&
                 (((mode != 1 && mode != 4) ||
                   (obj->team != 5 && obj->player_index == 0)) ||
                  (static_cast<int32_t>(file->id) / 10 != 3 || file->id == BAT_DAT)))) {
                obj->blink_time = 15;
            }

            if (obj->frame_id1 == 212 && !airborne_from_999) {
                obj->y_velocity = file->jump_height;
                if (obj->click_right == 1 && obj->click_left == 0) {
                    obj->x_velocity = file->jump_distance;
                } else if (obj->click_left == 1 && obj->click_right == 0) {
                    obj->x_velocity = -file->jump_distance;
                }
                if (obj->click_up == 0) {
                    if (obj->click_down != 0) {
                        obj->z_velocity = file->jump_distancez;
                    }
                } else if (obj->click_down == 0) {
                    obj->z_velocity = -file->jump_distancez;
                }
            }

            if (obj->frame_id1 < MAX_FRAMES) {
                trigger_frame_sound(obj, obj->frame_id1);
                int32_t fmp = file->frames[obj->frame_id1].mp;
                if (fmp < 0 && match_running) {
                    if (obj->mp < fmp) {
                        obj->frame_id1 = file->frames[obj->frame_id1].hit_d;
                    } else {
                        obj->mp += fmp;
                        obj->mp_used -= static_cast<uint32_t>(fmp);
                    }
                    if (obj->frame_id1 < MAX_FRAMES) {
                        int32_t hd = static_cast<int32_t>(file->frames[obj->frame_id1].hit_d);
                        if (hd > 0) {
                            if (obj->click_left == 1 && obj->click_right == 0 &&
                                obj->y == 0 && obj->facing == FACING_RIGHT) {
                                obj->frame_id1 = static_cast<uint32_t>(hd);
                            }
                            if (obj->click_left == 0 && obj->click_right == 1 &&
                                obj->y == 0 && obj->facing == FACING_LEFT) {
                                obj->frame_id1 = static_cast<uint32_t>(hd);
                            }
                        }
                    }
                }
            }
        }
    }

    if (obj->frame_id1 == 110 || obj->frame_id1 == 114) {
        obj->defend_lock = 3;
    }
    if (obj->frame_id1 == 202) {
        obj->blink_time = 20;
    }
    obj->frame_id2 = obj->frame_id1;
}

// 1:1 Lift of 0x0040E490: Per-object physics, velocity integration, gravity & ground landing
// VERIFIED: LF2 0x0040e490
void object_physics_tick(object_t* obj, int32_t counter_12)
{
    if (!obj) return;

    if (obj->shaking != 0) {
        if (obj->shaking > 0) {
            obj->shaking--;
        }
        if (obj->shaking < 0) {
            obj->shaking++;
            return;
        }
        return;
    }

    if (obj->weapon_type < 0) {
        return;
    }
    if (!obj->file || obj->frame_id1 >= MAX_FRAMES) {
        return;
    }

    file_t* file = obj->file;
    const frame_t* cur = &file->frames[obj->frame_id1];
    if (cur->cpoint.kind == 2) {
        return;
    }

    if ((obj->x_velocity <= 0.0 || obj->blocked_right != 1) &&
        (0.0 <= obj->x_velocity || obj->blocked_left != 1)) {
        obj->x_position += obj->x_velocity;
    }
    if (file->type == TYPE_THROW_WEAPON || file->id == KNIFE_DAT) {
        obj->x_position += obj->x_velocity * 0.2;
    }
    if (file->id == HOE_DAT) {
        obj->x_position -= obj->x_velocity * 0.2;
    }

    if ((obj->z_velocity <= 0.0 || obj->blocked_down != 1) &&
        (0.0 <= obj->z_velocity || obj->blocked_up != 1)) {
        obj->z_position += obj->z_velocity;
    }
    obj->blocked_down = 0;
    obj->blocked_up = 0;
    obj->blocked_left = 0;
    obj->blocked_right = 0;

    if (file->type == TYPE_ATTACK && static_cast<int32_t>(cur->hit_j) > 0) {
        obj->z_position += static_cast<double>(static_cast<int32_t>(cur->hit_j) - 50);
    }

    if (obj->y >= 0) {
        apply_ground_drag(obj->x_velocity, 1.0);
        apply_ground_drag(obj->z_velocity, 1.0);
    }

    if ((file->type == TYPE_THROW_WEAPON || file->type == TYPE_DRINK) &&
        cur->state == 1000 &&
        (9.0 < obj->x_velocity || obj->x_velocity < -9.0)) {
        obj->frame_id1 = 40;
    }

    double new_y = obj->y_position + obj->y_velocity;
    obj->y_position = new_y;

    if (new_y < -0.0001) {
        uint32_t ftype = file->type;
        if (ftype != TYPE_ATTACK) {
            if (ftype == TYPE_DRINK) {
                obj->y_velocity += 1.1333333333333333;
            } else if (ftype == TYPE_THROW_WEAPON) {
                obj->y_velocity += 0.85;
            } else if (obj->frame_id1 < MAX_FRAMES && file->frames[obj->frame_id1].state == 1002) {
                if (file->id == BOOMERANG_DAT) {
                    obj->y_velocity += 0.16999999999999998;
                } else if (file->id == KNIFE_DAT) {
                    obj->y_velocity += 0.425;
                } else if (file->id == HOE_DAT) {
                    obj->y_velocity += 1.1333333333333333;
                } else {
                    obj->y_velocity += 0.5666666666666667;
                }
            } else {
                obj->y_velocity += 1.7;
            }
        }

        if (file->type == TYPE_CHARACTER && obj->frame_id1 < MAX_FRAMES) {
            int32_t fid = static_cast<int32_t>(obj->frame_id1);
            if (file->frames[fid].state == STATE_FALLING) {
                if (fid < 185) {
                    if (obj->y_velocity >= -8.0) {
                        if (obj->y_velocity >= 1.0) {
                            obj->frame_id1 = (obj->y_velocity >= 8.0) ? 183 : 182;
                        } else {
                            obj->frame_id1 = 181;
                        }
                    } else {
                        obj->frame_id1 = 180;
                    }
                    if (static_cast<int32_t>(obj->thrown_injury) < 0) {
                        obj->frame_id1 = (obj->y_velocity < 12.0 && counter_12 > 5) ? 182 : 181;
                    }
                } else if (fid > 185 && fid < 191) {
                    if (obj->y_velocity >= -8.0) {
                        if (obj->y_velocity >= 1.0) {
                            obj->frame_id1 = (obj->y_velocity >= 8.0) ? 189 : 188;
                        } else {
                            obj->frame_id1 = 187;
                        }
                    } else {
                        obj->frame_id1 = 186;
                    }
                }
            }
            if (obj->frame_id1 < MAX_FRAMES &&
                file->frames[obj->frame_id1].state == STATE_BURNING &&
                obj->frame_id1 < 205 && obj->y_velocity > 1.0) {
                obj->frame_id1 = 205;
            }
        }
    } else if (obj->frame_id1 < MAX_FRAMES) {
        cur = &file->frames[obj->frame_id1];
        if (cur->cpoint.kind != 2) {
            uint32_t ftype = file->type;
            if (ftype == TYPE_CHARACTER) {
                if (0.0001 < new_y && 0.0001 < obj->y_velocity && cur->state == STATE_ICE) {
                    if (17.0 < obj->y_velocity || 9.0 < obj->x_velocity || obj->x_velocity < -9.0) {
                        if (obj->armor_multiplier == 0) {
                            obj->hp -= 10;
                        } else {
                            obj->hp += static_cast<int32_t>(-1000LL / static_cast<long long>(obj->armor_multiplier));
                        }
                        obj->y_position = 0.0;
                        obj->y_velocity = -3.5;
                        if (7.0 < obj->x_velocity) obj->x_velocity = 7.0;
                        if (obj->x_velocity < -7.0) obj->x_velocity = -7.0;
                        obj->frame_id1 = 185;
                    } else {
                        obj->y_position = 0.0;
                        obj->y_velocity = 0.0;
                        obj->x_velocity /= 3.0;
                    }
                }

                bool crouch_land = false;
                uint32_t land_frame = obj->frame_id1;
                if (obj->y_position > 0.0 && obj->y_velocity == 0.0 && obj->frame_id1 == 212) {
                    land_frame = 212;
                    crouch_land = true;
                } else if (0.0001 < obj->y_position && 0.0001 < obj->y_velocity) {
                    uint32_t st = file->frames[obj->frame_id1].state;
                    if (st != STATE_FALLING && st != STATE_BURNING) {
                        land_frame = obj->frame_id1;
                        crouch_land = true;
                    }
                }

                if (crouch_land) {
                    obj->y_position = 0.0;
                    obj->y_velocity = 0.0;
                    obj->x_velocity /= 3.0;
                    uint32_t st = file->frames[land_frame].state;
                    if (st == 100) {
                        obj->frame_id1 = 94;
                    } else if (land_frame == 212 || st == STATE_ROWING) {
                        obj->frame_id1 = 215;
                    } else {
                        obj->frame_id1 = 219;
                    }
                    obj->wait_counter = 0;
                } else if (0.0001 < obj->y_position && 0.0001 < obj->y_velocity &&
                           (file->frames[obj->frame_id1].state == STATE_FALLING ||
                            file->frames[obj->frame_id1].state == STATE_BURNING)) {
                    get_audio_system().queue_fixed_sound(obj->x, 6);
                    int32_t dmg = static_cast<int32_t>(obj->thrown_injury);
                    if (dmg != 0) {
                        if (dmg < 0) {
                            dmg = -dmg;
                            obj->thrown_injury = static_cast<uint32_t>(dmg);
                        }
                        if (obj->armor_multiplier > 0) {
                            dmg = (dmg * 100) / static_cast<int32_t>(obj->armor_multiplier);
                        }
                        obj->hp -= dmg;
                        obj->dark_hp -= dmg;
                        obj->thrown_injury = 0;
                    }
                    if (11.0 < obj->y_velocity || 9.0 < obj->x_velocity || obj->x_velocity < -9.0 ||
                        file->frames[obj->frame_id1].state == STATE_BURNING) {
                        obj->y_position = 0.0;
                        obj->y_velocity = -3.5;
                        if (7.0 < obj->x_velocity) obj->x_velocity = 7.0;
                        if (obj->x_velocity < -7.0) obj->x_velocity = -7.0;
                        if (obj->frame_id1 < 186 ||
                            file->frames[obj->frame_id1].state == STATE_BURNING) {
                            obj->frame_id1 = 185;
                        } else {
                            obj->frame_id1 = 191;
                        }
                    } else {
                        obj->y_position = 0.0;
                        obj->y_velocity = 0.0;
                        obj->wait_counter = 0;
                        obj->frame_id1 = (obj->frame_id1 > 185) ? 231 : 230;
                        obj->x_velocity /= 3.0;
                    }
                }
            } else if (ftype == TYPE_LIGHT_WEAPON) {
                if (0.0001 < new_y && 0.0001 < obj->y_velocity) {
                    obj->y_position = 0.0;
                    obj->weapon_hp -= file->weapon_drop_hurt;
                    if (obj->y_velocity <= 9.9) {
                        obj->frame_id1 = (cur->state == 1002) ? 70 : 60;
                        obj->y_velocity = 0.0;
                        obj->wait_counter = 0;
                        obj->x_velocity *= 0.5;
                    } else if (cur->state == 1002) {
                        obj->frame_id1 = 7;
                        obj->y_velocity = -8.0;
                        obj->facing = static_cast<uint8_t>(1U - obj->facing);
                        obj->x_velocity *= 0.5;
                        if (file->weapon_drop_sound_id >= 0) {
                            get_audio_system().queue_item_sound(obj->x, file->weapon_drop_sound_id);
                        } else if (file->weapon_drop_sound > 0) {
                            get_audio_system().queue_item_sound(obj->x, static_cast<int32_t>(file->weapon_drop_sound));
                        }
                    } else {
                        obj->frame_id1 = 60;
                        obj->y_velocity = 0.0;
                        obj->wait_counter = 0;
                        obj->x_velocity *= 0.5;
                    }
                }
            } else if (ftype == TYPE_THROW_WEAPON || ftype == TYPE_DRINK) {
                if (0.0001 < new_y && 0.0001 < obj->y_velocity) {
                    obj->weapon_hp -= file->weapon_drop_hurt;
                    if (file->type == TYPE_DRINK && obj->hp < 1) {
                        obj->weapon_hp = -1;
                    }
                    obj->y_position = 0.0;
                    if ((obj->y_velocity <= 8.5 && -10.0 <= obj->x_velocity && obj->x_velocity <= 10.0) ||
                        (cur->state != 1002 && cur->state != 1000)) {
                        obj->y_velocity = 0.0;
                        obj->wait_counter = 0;
                        obj->x_velocity *= 0.7;
                        obj->frame_id1 = (cur->state == 1002) ? 70 : 60;
                    } else {
                        obj->frame_id1 = 0;
                        obj->y_velocity *= -0.7;
                        if (obj->y_velocity < -10.0) {
                            obj->y_velocity = -10.0;
                        }
                        obj->x_velocity *= 0.7;
                        if (file->weapon_drop_sound_id >= 0) {
                            get_audio_system().queue_item_sound(obj->x, file->weapon_drop_sound_id);
                        } else if (file->weapon_drop_sound > 0) {
                            get_audio_system().queue_item_sound(obj->x, static_cast<int32_t>(file->weapon_drop_sound));
                        }
                    }
                }
            } else if (ftype == TYPE_HEAVY_WEAPON) {
                if (0.0001 < new_y) {
                    obj->weapon_hp -= 1;
                    obj->y_position = 0.0;
                    if (9.0 < obj->y_velocity) {
                        if (file->weapon_drop_sound_id >= 0) {
                            get_audio_system().queue_item_sound(obj->x, file->weapon_drop_sound_id);
                        } else if (file->weapon_drop_sound > 0) {
                            get_audio_system().queue_item_sound(obj->x, static_cast<int32_t>(file->weapon_drop_sound));
                        }
                        obj->y_velocity = -5.0;
                        obj->facing = static_cast<uint8_t>(1U - obj->facing);
                        obj->x_velocity *= 0.5;
                    } else {
                        obj->weapon_hp -= file->weapon_drop_hurt;
                        if (obj->weapon_hp < 0) {
                            obj->weapon_hp = 0;
                        }
                        obj->frame_id1 = 20;
                        obj->y_velocity = 0.0;
                        obj->wait_counter = 0;
                        obj->x_velocity *= 0.5;
                    }
                }
            } else if (file->id == BROKEN_WEAPON_DAT && -0.0001 < new_y) {
                obj->y_position = 0.0;
                obj->frame_id1 = 101;
                obj->y_velocity = 0.0;
                obj->wait_counter = 0;
                obj->x_velocity = 0.0;
            }
        }
    }

    obj->x = static_cast<int32_t>(obj->x_position);
    obj->y = static_cast<int32_t>(obj->y_position);
    obj->z = static_cast<int32_t>(obj->z_position);
    if (obj->frame_id1 < MAX_FRAMES &&
        obj->file->frames[obj->frame_id1].state != STATE_FALLING) {
        obj->thrown_injury = 0;
    }
}

// 1:1 Lift of 0x00413080: Master per-object input/state tick & combo dispatcher
// VERIFIED: LF2 0x00413080
void object_input_tick(object_t* obj, bool match_running, int32_t unlock_chars)
{
    if (!obj || !obj->file || obj->frame_id1 >= MAX_FRAMES) return;

    if (static_cast<int8_t>(obj->right_press) > 0) obj->right_press--;
    if (static_cast<int8_t>(obj->left_press) > 0) obj->left_press--;
    if (static_cast<int8_t>(obj->up_press) > 0) obj->up_press--;
    if (static_cast<int8_t>(obj->down_press) > 0) obj->down_press--;
    if (static_cast<int8_t>(obj->jump_press) > 0) obj->jump_press--;
    if (static_cast<int8_t>(obj->attack_press) > 0) obj->attack_press--;
    if (static_cast<int8_t>(obj->defend_press) > 0) obj->defend_press--;
    if (static_cast<int8_t>(obj->defend_lock) > 0) obj->defend_lock--;

    if (obj->holding_right == 0 && obj->click_right == 1) {
        obj->right_press = 5;
        object_input_history_push(obj, 6);
    }
    if (obj->holding_left == 0 && obj->click_left == 1) {
        obj->left_press = 5;
        object_input_history_push(obj, 4);
    }
    if (obj->holding_up == 0 && obj->click_up == 1) {
        obj->up_press = 5;
        object_input_history_push(obj, 8);
    }
    if (obj->holding_down == 0 && obj->click_down == 1) {
        obj->down_press = 5;
        object_input_history_push(obj, 2);
    }
    if (obj->holding_defend == 0 && obj->click_defend == 1) {
        obj->defend_press = 5;
        object_input_history_push(obj, 9);
    }
    if (obj->holding_jump == 0 && obj->click_jump == 1) {
        obj->jump_press = 5;
        object_input_history_push(obj, 0);
    }
    if (obj->holding_attack == 0 && obj->click_attack == 1) {
        obj->attack_press = 5;
        object_input_history_push(obj, 5);
    }

    object_combo_dra(obj, match_running);
    object_combo_dla(obj, match_running);
    object_combo_dua(obj, match_running);
    object_combo_dda(obj, match_running);
    object_combo_drj(obj, match_running);
    object_combo_dlj(obj, match_running);
    object_combo_duj(obj, match_running);
    object_combo_ddj(obj, match_running);
    object_combo_dja(obj, match_running, unlock_chars);

    file_t* file = obj->file;
    if (obj->frame_id1 < MAX_FRAMES) {
        const frame_t& cur = file->frames[obj->frame_id1];
        if (cur.hit_a == 0 || static_cast<int8_t>(obj->attack_press) <= static_cast<int8_t>(obj->defend_press) ||
            static_cast<int8_t>(obj->attack_press) <= static_cast<int8_t>(obj->jump_press)) {
            if (cur.hit_d == 0 || static_cast<int8_t>(obj->defend_press) <= static_cast<int8_t>(obj->attack_press) ||
                static_cast<int8_t>(obj->defend_press) <= static_cast<int8_t>(obj->jump_press)) {
                if (cur.hit_j != 0 && static_cast<int8_t>(obj->attack_press) < static_cast<int8_t>(obj->jump_press) &&
                    static_cast<int8_t>(obj->defend_press) < static_cast<int8_t>(obj->jump_press)) {
                    object_frame_transition(obj, static_cast<int32_t>(cur.hit_j), match_running);
                    obj->jump_press = 0;
                }
            } else {
                object_frame_transition(obj, static_cast<int32_t>(cur.hit_d), match_running);
                obj->defend_press = 0;
            }
        } else {
            object_frame_transition(obj, static_cast<int32_t>(cur.hit_a), match_running);
            obj->attack_press = 0;
        }
    }

    if (obj->frame_id1 == 110) {
        if (obj->click_right == 1) obj->facing = FACING_RIGHT;
        if (obj->click_left == 1) obj->facing = FACING_LEFT;
    }

    if (obj->frame_id1 < MAX_FRAMES) {
        uint32_t st = file->frames[obj->frame_id1].state;
        if (st == 301 || st == BINARY_STATE_FIRE) {
            if (obj->click_up == 1 && obj->click_down == 0 && obj->y == 0) {
                obj->z_velocity = -file->running_speedz;
            }
            if (obj->click_down == 1 && obj->click_up == 0 && obj->y == 0) {
                obj->z_velocity = file->running_speedz;
            }
        }
    }

    int32_t wtype = obj->weapon_type;
    if (wtype != HEAVY_WEAPON_TYPE && obj->frame_id1 < MAX_FRAMES &&
        (file->frames[obj->frame_id1].state == STATE_STANDING ||
         file->frames[obj->frame_id1].state == STATE_WALKING)) {
        if (obj->dash_counter > 0) obj->dash_counter--;
        if (obj->dash_counter < 0) obj->dash_counter++;

        int32_t wfr = (file->walking_frame_rate > 0) ? static_cast<int32_t>(file->walking_frame_rate) : 1;

        if (obj->click_right == 1 && obj->click_left == 0 && obj->y == 0) {
            if (obj->facing == FACING_LEFT) obj->dash_counter = 0;
            obj->facing = FACING_RIGHT;
            step_grid_walk_cycle(obj, wfr, 5, 6);
            obj->x_velocity = file->walking_speed;
            if (obj->holding_right == 0) obj->dash_counter += 10;
            if (obj->dash_counter > 10) {
                obj->frame_id1 = 9;
                obj->move_counter = 0;
                obj->dash_counter = 0;
            }
        }
        if (obj->click_right == 0 && obj->click_left == 1 && obj->y == 0) {
            if (obj->facing == FACING_RIGHT) obj->dash_counter = 0;
            obj->facing = FACING_LEFT;
            step_grid_walk_cycle(obj, wfr, 5, 6);
            obj->x_velocity = -file->walking_speed;
            if (obj->holding_left == 0) obj->dash_counter -= 10;
            if (obj->dash_counter < -10) {
                obj->frame_id1 = 9;
                obj->move_counter = 0;
                obj->dash_counter = 0;
            }
        }
        if (obj->click_up == 1 && obj->click_down == 0 && obj->y == 0) {
            if ((obj->click_left == 0 && obj->click_right == 0) ||
                (obj->click_left != 0 && obj->click_right != 0)) {
                step_grid_walk_cycle(obj, wfr, 5, 6);
            }
            obj->z_velocity = -file->walking_speedz;
            obj->x_velocity /= 1.4;
        }
        if (obj->click_down == 1 && obj->click_up == 0 && obj->y == 0) {
            if ((obj->click_left == 0 && obj->click_right == 0) ||
                (obj->click_left != 0 && obj->click_right != 0)) {
                step_grid_walk_cycle(obj, wfr, 5, 6);
            }
            obj->z_velocity = file->walking_speedz;
            obj->x_velocity /= 1.4;
        }

        if (obj->click_attack == 1 && static_cast<int8_t>(obj->attack_press) > 0) {
            obj->dash_counter = 0;
            obj->wait_counter = 0;
            if (wtype == 0) {
                if (static_cast<int8_t>(obj->can_hit_flag) < 1) {
                    int32_t r = lf2_random(0x82, 2);
                    int32_t fid = (r + 12) * 5;
                    obj->frame_id1 = static_cast<uint32_t>(fid);
                    deduct_frame_mp(obj, fid, match_running);
                } else {
                    obj->frame_id1 = 70;
                }
            } else if (wtype % 100 == 1) {
                if (wtype == 101 &&
                    (obj->click_right != 0 || obj->click_left != 0 ||
                     obj->click_up != 0 || obj->click_down != 0)) {
                    obj->frame_id1 = 45;
                } else if (wtype == 101) {
                    obj->frame_id1 = static_cast<uint32_t>((lf2_random(0x83, 2) + 4) * 5);
                } else {
                    obj->frame_id1 = static_cast<uint32_t>((lf2_random(0x84, 2) + 4) * 5);
                }
            } else if (wtype == static_cast<int32_t>(TYPE_THROW_WEAPON)) {
                obj->frame_id1 = 45;
            } else if (wtype == static_cast<int32_t>(TYPE_DRINK)) {
                obj->frame_id1 = 55;
            }
        }
        if (obj->click_jump == 1 && static_cast<int8_t>(obj->jump_press) > 0) {
            obj->wait_counter = 0;
            obj->dash_counter = 0;
            obj->frame_id1 = 210;
        }
        if (obj->click_defend == 1 && obj->defend_lock == 0 && static_cast<int8_t>(obj->defend_press) > 0) {
            obj->dash_counter = 0;
            obj->wait_counter = 0;
            obj->frame_id1 = 110;
        }
    }

    wtype = obj->weapon_type;
    if (wtype == HEAVY_WEAPON_TYPE && obj->frame_id1 < MAX_FRAMES &&
        (file->frames[obj->frame_id1].state == STATE_STANDING ||
         file->frames[obj->frame_id1].state == STATE_WALKING)) {
        if (obj->dash_counter > 0) obj->dash_counter--;
        if (obj->dash_counter < 0) obj->dash_counter++;
        if (obj->frame_id1 < 12) obj->frame_id1 = 12;

        int32_t wfr = (file->walking_frame_rate > 0) ? static_cast<int32_t>(file->walking_frame_rate) : 1;

        if (obj->click_right == 1 && obj->click_left == 0 && obj->y == 0) {
            if (obj->facing == FACING_LEFT) obj->dash_counter = 0;
            obj->facing = FACING_RIGHT;
            step_grid_walk_cycle(obj, wfr, 12, 6);
            obj->x_velocity = file->heavy_walking_speed;
            if (obj->holding_right == 0) obj->dash_counter += 10;
            if (obj->dash_counter > 10) {
                obj->frame_id1 = 16;
                obj->move_counter = 0;
                obj->dash_counter = 0;
            }
        }
        if (obj->click_right == 0 && obj->click_left == 1 && obj->y == 0) {
            if (obj->facing == FACING_RIGHT) obj->dash_counter = 0;
            obj->facing = FACING_LEFT;
            step_grid_walk_cycle(obj, wfr, 12, 6);
            obj->x_velocity = -file->heavy_walking_speed;
            if (obj->holding_left == 0) obj->dash_counter -= 10;
            if (obj->dash_counter < -10) {
                obj->frame_id1 = 16;
                obj->move_counter = 0;
                obj->dash_counter = 0;
            }
        }
        if (obj->click_up == 1 && obj->click_down == 0 && obj->y == 0) {
            if ((obj->click_left == 0 && obj->click_right == 0) ||
                (obj->click_left != 0 && obj->click_right != 0)) {
                step_grid_walk_cycle(obj, wfr, 12, 6);
            }
            obj->z_velocity = -file->heavy_walking_speedz;
            obj->x_velocity /= 1.4;
        }
        if (obj->click_down == 1 && obj->click_up == 0 && obj->y == 0) {
            if ((obj->click_left == 0 && obj->click_right == 0) ||
                (obj->click_left != 0 && obj->click_right != 0)) {
                step_grid_walk_cycle(obj, wfr, 12, 6);
            }
            obj->z_velocity = file->heavy_walking_speedz;
            obj->x_velocity /= 1.4;
        }
        if (obj->click_attack == 1 && static_cast<int8_t>(obj->attack_press) > 0) {
            obj->dash_counter = 0;
            obj->wait_counter = 0;
            obj->frame_id1 = 50;
        }
    }

    if (obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == STATE_JUMPING && obj->y < 0) {
        if (obj->click_right == 1 && obj->click_left == 0) obj->facing = FACING_RIGHT;
        if (obj->click_left == 1 && obj->click_right == 0) obj->facing = FACING_LEFT;
        if (obj->click_attack != 0) {
            if (wtype == 0) {
                obj->wait_counter = 0;
                obj->frame_id1 = 80;
                deduct_frame_mp(obj, 80, match_running);
            } else if (wtype % 100 == 1) {
                obj->wait_counter = 0;
                if (obj->click_left == 0 && obj->click_right == 0 &&
                    obj->click_up == 0 && obj->click_down == 0) {
                    obj->frame_id1 = 30;
                } else {
                    obj->frame_id1 = 52;
                }
            } else if (wtype == static_cast<int32_t>(TYPE_THROW_WEAPON) ||
                       wtype == static_cast<int32_t>(TYPE_DRINK)) {
                obj->frame_id1 = 52;
            }
        }
    }

    if (obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == STATE_RUNNING && wtype != HEAVY_WEAPON_TYPE) {
        obj->wait_counter = 0;
        int32_t rfr = (file->running_frame_rate > 0) ? static_cast<int32_t>(file->running_frame_rate) : 1;
        step_grid_run_cycle(obj, rfr, 9);

        if (obj->facing == FACING_RIGHT) {
            obj->x_velocity = file->running_speed;
            if (obj->click_left == 1) obj->frame_id1 = 218;
        }
        if (obj->facing == FACING_LEFT) {
            obj->x_velocity = -file->running_speed;
            if (obj->click_right == 1) obj->frame_id1 = 218;
        }
        if (obj->click_up == 1 && obj->click_down == 0 && obj->y == 0) {
            obj->z_velocity = -file->running_speedz;
            obj->x_velocity /= 1.2;
        }
        if (obj->click_up == 0 && obj->click_down == 1 && obj->y == 0) {
            obj->z_velocity = file->running_speedz;
            obj->x_velocity /= 1.2;
        }

        if (obj->click_attack == 1 && static_cast<int8_t>(obj->attack_press) > 0) {
            if (wtype == 0) {
                if (!match_running) {
                    obj->frame_id1 = 85;
                } else if (file->frames[85].mp <= obj->mp) {
                    obj->mp -= file->frames[85].mp;
                    obj->mp_used += static_cast<uint32_t>(file->frames[85].mp);
                    obj->frame_id1 = 85;
                }
            } else if (wtype % 100 == 1) {
                if (obj->click_left == 0 && obj->click_right == 0 &&
                    obj->click_up == 0 && obj->click_down == 0) {
                    obj->frame_id1 = 35;
                } else {
                    obj->frame_id1 = 45;
                }
            } else if (obj->weapon_type == static_cast<int32_t>(TYPE_THROW_WEAPON)) {
                obj->frame_id1 = 45;
            } else if (obj->weapon_type == static_cast<int32_t>(TYPE_DRINK)) {
                if (obj->click_left == 0 && obj->click_right == 0 &&
                    obj->click_up == 0 && obj->click_down == 0) {
                    obj->frame_id1 = 55;
                } else {
                    obj->frame_id1 = 45;
                }
            }
        }
        if (obj->click_defend == 1 && static_cast<int8_t>(obj->defend_press) > 0) {
            obj->frame_id1 = 102;
        }
        if (obj->click_jump == 1 && static_cast<int8_t>(obj->jump_press) > 0) {
            get_audio_system().queue_fixed_sound(obj->x, 7);
            obj->dash_counter = 0;
            obj->frame_id1 = 213;
            obj->x_velocity = static_cast<double>(static_cast<int32_t>(obj->facing) * -2 + 1) * file->dash_distance;
            obj->y_velocity = file->dash_height;
            if (obj->click_up == 0) {
                if (obj->click_down != 0) {
                    obj->z_velocity = file->dash_distancez;
                }
            } else if (obj->click_down == 0) {
                obj->z_velocity = -file->dash_distancez;
            }
        }
    }

    if (obj->frame_id1 < MAX_FRAMES &&
        file->frames[obj->frame_id1].state == STATE_RUNNING &&
        obj->weapon_type == HEAVY_WEAPON_TYPE) {
        obj->wait_counter = 0;
        int32_t rfr = (file->running_frame_rate > 0) ? static_cast<int32_t>(file->running_frame_rate) : 1;
        step_grid_run_cycle(obj, rfr, 16);

        if (obj->facing == FACING_RIGHT) {
            obj->x_velocity = file->heavy_running_speed;
            if (obj->click_left == 1) obj->frame_id1 = 19;
        }
        if (obj->facing == FACING_LEFT) {
            obj->x_velocity = -file->heavy_running_speed;
            if (obj->click_right == 1) obj->frame_id1 = 19;
        }
        if (obj->click_up == 1 && obj->click_down == 0 && obj->y == 0) {
            obj->z_velocity = -file->heavy_running_speedz;
            obj->x_velocity /= 1.2;
        }
        if (obj->click_up == 0 && obj->click_down == 1 && obj->y == 0) {
            obj->z_velocity = file->heavy_running_speedz;
            obj->x_velocity /= 1.2;
        }
        if (obj->click_attack == 1 && static_cast<int8_t>(obj->attack_press) > 0) {
            obj->frame_id1 = 50;
        }
    }

    if (obj->frame_id1 == 215) {
        if (obj->click_defend == 1 && static_cast<int8_t>(obj->defend_press) > 0) {
            obj->frame_id1 = 102;
        }
        if (obj->click_jump != 0) {
            if ((obj->click_right != 0 || 0.001 < obj->x_velocity) &&
                static_cast<int8_t>(obj->jump_press) > 0) {
                get_audio_system().queue_fixed_sound(obj->x, 7);
                obj->frame_id1 = static_cast<uint32_t>(obj->facing) + 213U;
                obj->dash_counter = 0;
                obj->x_velocity = file->dash_distance;
                obj->y_velocity = file->dash_height;
            }
            if (obj->click_jump != 0 &&
                (obj->click_left != 0 || obj->x_velocity < -0.001) &&
                static_cast<int8_t>(obj->jump_press) > 0) {
                get_audio_system().queue_fixed_sound(obj->x, 7);
                obj->frame_id1 = 214U - static_cast<uint32_t>(obj->facing);
                obj->dash_counter = 0;
                obj->x_velocity = -file->dash_distance;
                obj->y_velocity = file->dash_height;
            }
        }
        if (obj->click_up == 0) {
            if (obj->click_down != 0) {
                obj->z_velocity = file->dash_distancez;
            }
        } else if (obj->click_down == 0) {
            obj->z_velocity = -file->dash_distancez;
        }
    }

    if ((obj->frame_id1 == 182 || obj->frame_id1 == 188) &&
        static_cast<int32_t>(obj->thrown_injury) >= 0 && obj->click_jump == 1 &&
        static_cast<int8_t>(obj->jump_press) > 0 && obj->hp > 0) {
        if ((obj->facing == FACING_RIGHT && obj->x_velocity <= 0.0) ||
            (obj->facing == FACING_LEFT && obj->x_velocity >= 0.0)) {
            obj->frame_id1 = 100;
        } else {
            obj->frame_id1 = 108;
        }
        obj->wait_counter = 0;
        if (file->rowing_height < obj->y_velocity) {
            obj->y_velocity = file->rowing_height;
        }
        if (1.0 <= obj->x_velocity || obj->x_velocity <= -1.0) {
            obj->x_velocity = (obj->x_velocity <= 0.0) ? -file->rowing_distance : file->rowing_distance;
        } else {
            obj->x_velocity = (obj->facing == FACING_LEFT) ? file->rowing_distance : -file->rowing_distance;
        }
    }

    if (obj->frame_id1 < MAX_FRAMES && file->frames[obj->frame_id1].state == STATE_DASHING) {
        if (obj->click_right == 1 && obj->click_left == 0) {
            obj->facing = FACING_RIGHT;
        }
        if (obj->facing == FACING_RIGHT && obj->frame_id1 != 217 && obj->x_velocity < 0.0) {
            obj->frame_id1 = 214;
        }
        if (obj->facing == FACING_RIGHT && obj->frame_id1 != 216 && 0.0 < obj->x_velocity) {
            obj->frame_id1 = 213;
        }
        if (obj->click_left == 1 && obj->click_right == 0) {
            obj->facing = FACING_LEFT;
        }
        if (obj->facing == FACING_LEFT) {
            if (obj->frame_id1 != 217 && 0.0 < obj->x_velocity) {
                obj->frame_id1 = 214;
            }
            if (obj->frame_id1 != 216 && obj->x_velocity < 0.0) {
                obj->frame_id1 = 213;
            }
        }
        if (((0.0 < obj->x_velocity && obj->facing == FACING_RIGHT) ||
             (obj->x_velocity < 0.0 && obj->facing == FACING_LEFT)) &&
            obj->click_attack != 0) {
            int32_t wt = obj->weapon_type;
            if (wt == 0) {
                if (!match_running) {
                    obj->frame_id1 = 90;
                } else if (file->frames[90].mp <= obj->mp) {
                    obj->mp -= file->frames[90].mp;
                    obj->mp_used += static_cast<uint32_t>(file->frames[90].mp);
                    obj->frame_id1 = 90;
                }
            } else if ((wt % 100 == 1) ||
                       ((wt == static_cast<int32_t>(TYPE_THROW_WEAPON) ||
                         wt == static_cast<int32_t>(TYPE_DRINK)) &&
                        (obj->click_left != 0 || obj->click_right != 0 ||
                         obj->click_up != 0 || obj->click_down != 0))) {
                obj->frame_id1 = (wt == static_cast<int32_t>(TYPE_THROW_WEAPON) ||
                                  wt == static_cast<int32_t>(TYPE_DRINK)) ? 52 : 40;
                obj->wait_counter = 0;
                obj->y_velocity -= 1.0;
            }
        }
    }

    if (obj->frame_id1 < MAX_FRAMES) {
        const frame_t& f = file->frames[obj->frame_id1];
        if (f.dvx < 501) {
            if (f.dvx > 0 && obj->x_velocity < static_cast<double>(f.dvx) && obj->facing == FACING_RIGHT) {
                obj->x_velocity = static_cast<double>(f.dvx);
            }
            if (f.dvx > 0 && -obj->x_velocity < static_cast<double>(f.dvx) && obj->facing == FACING_LEFT) {
                obj->x_velocity = -static_cast<double>(f.dvx);
            }
            if (f.dvx < 0 && static_cast<double>(f.dvx) < obj->x_velocity && obj->facing == FACING_RIGHT) {
                obj->x_velocity = static_cast<double>(f.dvx);
            }
            if (f.dvx < 0 && static_cast<double>(f.dvx) < -obj->x_velocity && obj->facing == FACING_LEFT) {
                obj->x_velocity = -static_cast<double>(f.dvx);
            }
        } else {
            obj->x_velocity = static_cast<double>(f.dvx - 550);
        }

        if (f.dvy != 0) {
            obj->y_velocity = (f.dvy < 501)
                ? (static_cast<double>(f.dvy) + obj->y_velocity)
                : static_cast<double>(f.dvy - 550);
        }

        if (f.dvz != 0) {
            if (f.dvz > 500) {
                obj->z_velocity = static_cast<double>(f.dvz - 550);
                return;
            }
            if (obj->click_up == 1 && static_cast<int8_t>(obj->down_press) <= static_cast<int8_t>(obj->up_press)) {
                obj->z_velocity = -static_cast<double>(f.dvz);
            }
            if (obj->click_down == 1 && static_cast<int8_t>(obj->up_press) <= static_cast<int8_t>(obj->down_press)) {
                obj->z_velocity = static_cast<double>(f.dvz);
            }
        }
    }
}

void object_update_motion(object_t* obj, int32_t stage_z_min, int32_t stage_z_max, int32_t stage_width)
{
    if (!obj) return;

    obj->x_position += obj->x_velocity;
    obj->y_position += obj->y_velocity;
    obj->z_position += obj->z_velocity;

    obj->blocked_up = 0;
    obj->blocked_down = 0;
    obj->blocked_left = 0;
    obj->blocked_right = 0;

    if (obj->z_position <= static_cast<double>(stage_z_min)) {
        obj->z_position = static_cast<double>(stage_z_min);
        obj->blocked_up = 1;
    } else if (obj->z_position >= static_cast<double>(stage_z_max)) {
        obj->z_position = static_cast<double>(stage_z_max);
        obj->blocked_down = 1;
    }

    if (obj->x_position <= 0.0) {
        obj->x_position = 0.0;
        obj->blocked_left = 1;
    } else if (obj->x_position >= static_cast<double>(stage_width)) {
        obj->x_position = static_cast<double>(stage_width);
        obj->blocked_right = 1;
    }

    if (obj->y_position >= 0.0) {
        obj->y_position = 0.0;
        if (obj->y_velocity > 0.0) {
            obj->y_velocity = 0.0;
        }
    }

    // Exact _ftol2_sse truncation
    obj->x = static_cast<int32_t>(obj->x_position);
    obj->y = static_cast<int32_t>(obj->y_position);
    obj->z = static_cast<int32_t>(obj->z_position);
}

void object_update_physics(object_t* obj)
{
    if (!obj) return;
    if (obj->file) {
        object_physics_tick(obj, 0);
        return;
    }

    // Fallback when called in unit tests with null file_t
    double new_y = obj->y_position + obj->y_velocity;
    obj->y_position = new_y;
    if (new_y < -0.0001) {
        obj->y_velocity += 1.7;
    } else {
        obj->y_position = 0.0;
        obj->y_velocity = 0.0;
    }
    obj->x = static_cast<int32_t>(obj->x_position);
    obj->y = static_cast<int32_t>(obj->y_position);
    obj->z = static_cast<int32_t>(obj->z_position);
}

void object_apply_ground_friction(object_t* obj, double friction)
{
    if (!obj) return;
    if (obj->y >= 0) {
        apply_ground_drag(obj->x_velocity, friction);
        apply_ground_drag(obj->z_velocity, friction);
    }
}

bool object_tick_frame(object_t* obj, int32_t mode, int32_t obj_idx, int32_t difficulty, bool match_running)
{
    if (!obj || !obj->file) return true;
    if (obj->frame_id1 >= MAX_FRAMES) {
        return false;
    }

    obj->frame_id4 = obj->frame_id3;
    obj->frame_id3 = obj->frame_id2;
    object_frame_advance(obj, mode, obj_idx, difficulty, match_running);
    return obj->frame_id1 < MAX_FRAMES;
}

void object_handle_input(object_t* obj, const input_state_t& input, bool match_running, int32_t unlock_chars)
{
    if (!obj || !obj->file || obj->frame_id1 >= MAX_FRAMES) return;

    obj->holding_up     = obj->click_up;
    obj->holding_down   = obj->click_down;
    obj->holding_left   = obj->click_left;
    obj->holding_right  = obj->click_right;
    obj->holding_attack = obj->click_attack;
    obj->holding_jump   = obj->click_jump;
    obj->holding_defend = obj->click_defend;

    obj->click_up     = input.up     ? 1 : 0;
    obj->click_down   = input.down   ? 1 : 0;
    obj->click_left   = input.left   ? 1 : 0;
    obj->click_right  = input.right  ? 1 : 0;
    obj->click_attack = input.attack ? 1 : 0;
    obj->click_jump   = input.jump   ? 1 : 0;
    obj->click_defend = input.defend ? 1 : 0;

    object_input_tick(obj, match_running, unlock_chars);
}

// 1:1 Lift of 0x00417200: Broad-phase 2D bounding box overlap check between attacker and injured
// VERIFIED: LF2 0x00417200
bool is_broadphase_overlap(const global_t* world, uint32_t attacker_id, uint32_t injured_id)
{
    if (!world || attacker_id >= MAX_OBJECTS || injured_id >= MAX_OBJECTS) {
        return false;
    }
    if (!world->is_object_exists[attacker_id] || !world->is_object_exists[injured_id]) {
        return false;
    }
    const object_t* attacker = world->objects[attacker_id];
    const object_t* injured = world->objects[injured_id];
    if (!attacker || !injured || !attacker->file || !injured->file) {
        return false;
    }
    if (attacker->frame_id1 >= MAX_FRAMES || injured->frame_id1 >= MAX_FRAMES ||
        attacker->frame_id4 >= MAX_FRAMES || injured->frame_id4 >= MAX_FRAMES) {
        return false;
    }

    const frame_t* att_f1 = &attacker->file->frames[attacker->frame_id1];
    const frame_t* inj_f1 = &injured->file->frames[injured->frame_id1];
    if (att_f1->itrs_size == 0 || inj_f1->bdys_size == 0 ||
        attacker->arest > 0 || static_cast<int8_t>(injured->vrest_of_objects[attacker_id]) > 0) {
        return false;
    }

    const frame_t* att_f4 = &attacker->file->frames[attacker->frame_id4];
    const frame_t* inj_f4 = &injured->file->frames[injured->frame_id4];
    if (att_f4->itrs_size == 0 || !att_f4->itrs || inj_f4->bdys_size == 0 || !inj_f4->bdys) {
        return false;
    }

    // Dynamic union AABB across injured bdys (0x8EC..0x8F8 in 0x0040ef70)
    int32_t bdy_min_x = inj_f4->bdys[0].x;
    int32_t bdy_min_y = inj_f4->bdys[0].y;
    int32_t bdy_max_x = inj_f4->bdys[0].x + inj_f4->bdys[0].w;
    int32_t bdy_max_y = inj_f4->bdys[0].y + inj_f4->bdys[0].h;
    for (uint32_t k = 1; k < inj_f4->bdys_size; ++k) {
        const bdy_t& b = inj_f4->bdys[k];
        if (b.x < bdy_min_x) bdy_min_x = b.x;
        if (b.y < bdy_min_y) bdy_min_y = b.y;
        if (b.x + b.w > bdy_max_x) bdy_max_x = b.x + b.w;
        if (b.y + b.h > bdy_max_y) bdy_max_y = b.y + b.h;
    }
    int32_t bdy_bw = bdy_max_x - bdy_min_x;
    int32_t bdy_bh = bdy_max_y - bdy_min_y;

    // Dynamic union AABB across attacker itrs (0x8DC..0x8E8 in 0x0040ef70)
    int32_t itr_min_x = att_f4->itrs[0].x;
    int32_t itr_min_y = att_f4->itrs[0].y;
    int32_t itr_max_x = att_f4->itrs[0].x + att_f4->itrs[0].w;
    int32_t itr_max_y = att_f4->itrs[0].y + att_f4->itrs[0].h;
    for (uint32_t k = 1; k < att_f4->itrs_size; ++k) {
        const itr_t& it = att_f4->itrs[k];
        if (it.x < itr_min_x) itr_min_x = it.x;
        if (it.y < itr_min_y) itr_min_y = it.y;
        if (it.x + it.w > itr_max_x) itr_max_x = it.x + it.w;
        if (it.y + it.h > itr_max_y) itr_max_y = it.y + it.h;
    }
    int32_t itr_bw = itr_max_x - itr_min_x;
    int32_t itr_bh = itr_max_y - itr_min_y;

    int32_t inj_left = (injured->facing == FACING_RIGHT)
        ? (bdy_min_x + (injured->x - inj_f4->centerx))
        : (((inj_f4->centerx + injured->x) - bdy_bw) - bdy_min_x);
    int32_t inj_top = bdy_min_y + (injured->y - inj_f4->centery);

    int32_t att_left = (attacker->facing == FACING_RIGHT)
        ? (itr_min_x + (attacker->x - att_f4->centerx))
        : (((att_f4->centerx + attacker->x) - itr_bw) - itr_min_x);
    int32_t att_top = itr_min_y + (attacker->y - att_f4->centery);

    return is_itr_bdy_overlap(inj_left, inj_top, bdy_bw, bdy_bh,
                              att_left, att_top, itr_bw, itr_bh);
}

// 1:1 Lift of 0x00419380: Per-frame frame_id4/arest reset, pairwise vrest decrement & collision dispatch
// VERIFIED: LF2 0x00419380
void world_step_collisions(global_t* world, uint32_t mode)
{
    if (!world) return;

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!world->is_object_exists[i]) continue;
        object_t* obj = world->objects[i];
        if (!obj || !obj->file) continue;

        obj->frame_id4 = obj->frame_id1;
        if (obj->frame_id1 < MAX_FRAMES) {
            const frame_t& f1 = obj->file->frames[obj->frame_id1];
            if (f1.itrs_size == 0) {
                obj->arest = 0;
            } else if (f1.state == 1001) {
                int32_t hid = obj->holder_id;
                if (hid >= 0 && hid < static_cast<int32_t>(MAX_OBJECTS) &&
                    world->objects[hid] && world->objects[hid]->file) {
                    const object_t* holder = world->objects[hid];
                    if (holder->frame_id1 < MAX_FRAMES &&
                        holder->file->frames[holder->frame_id1].wpoint.attacking == 0) {
                        obj->arest = 0;
                    }
                }
            }
        }
    }

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!world->is_object_exists[i]) continue;
        object_t* oi = world->objects[i];
        for (uint32_t j = i + 1; j < MAX_OBJECTS; ++j) {
            if (!world->is_object_exists[j]) continue;
            object_t* oj = world->objects[j];

            if (oi && static_cast<int8_t>(oi->vrest_of_objects[j]) > 0) {
                oi->vrest_of_objects[j]--;
            }
            if (oj && static_cast<int8_t>(oj->vrest_of_objects[i]) > 0) {
                oj->vrest_of_objects[i]--;
            }
            if (is_broadphase_overlap(world, i, j)) {
                world->does_attack_success(i, j, mode);
            }
            if (is_broadphase_overlap(world, j, i)) {
                world->does_attack_success(j, i, mode);
            }
        }
    }

    world_process_firzen_fusion(world, 0);
}

// 1:1 Lift of 0x004196F0: Physics velocity/impulse averaging pass across active objects
// VERIFIED: LF2 0x004196f0
void world_average_velocities(global_t* world)
{
    if (!world) return;

    for (uint32_t i = 0; i < MAX_OBJECTS; ++i) {
        if (!world->is_object_exists[i]) continue;
        object_t* obj = world->objects[i];
        if (!obj) continue;

        if (obj->shaking == 0) {
            if (obj->attacks != 0) {
                double factor = 2.0 / static_cast<double>(obj->attacks + 1);
                obj->x_velocity = obj->pic_x_gain * factor;
                obj->y_velocity = obj->y_accl * factor;
                obj->z_velocity = obj->z_accl * factor;
                obj->attacks = 0;
            }
            obj->pic_x_gain = 0.0;
            obj->y_accl = 0.0;
            obj->z_accl = 0.0;
        }
    }
}

// 1:1 Lift of 0x004197A0: Network / remote input bit unpacking and holding state latching
// VERIFIED: LF2 0x004197a0
void slot_unpack_network_inputs(global_t* world, const uint8_t* packet_bytes, int32_t clear_mode)
{
    if (!world) return;

    for (uint32_t i = 0; i < 8; ++i) {
        object_t* obj = world->objects[i];
        if (!obj) continue;

        // Shift current input into previous/holding input
        obj->holding_up     = obj->click_up;
        obj->holding_down   = obj->click_down;
        obj->holding_left   = obj->click_left;
        obj->holding_right  = obj->click_right;
        obj->holding_attack = obj->click_attack;
        obj->holding_jump   = obj->click_jump;
        obj->holding_defend = obj->click_defend;

        if (clear_mode == 0 && packet_bytes) {
            obj->click_up     = 0;
            obj->click_down   = 0;
            obj->click_left   = 0;
            obj->click_right  = 0;
            obj->click_attack = 0;
            obj->click_jump   = 0;
            obj->click_defend = 0;

            uint8_t b = packet_bytes[i];
            if (b & 0x80) obj->click_up     = 1;
            if (b & 0x40) obj->click_down   = 1;
            if (b & 0x20) obj->click_left   = 1;
            if (b & 0x10) obj->click_right  = 1;
            if (b & 0x08) obj->click_attack = 1;
            if (b & 0x04) obj->click_jump   = 1;
            if (b & 0x02) obj->click_defend = 1;
        }
    }
}

// 1:1 Lift of 0x004198F0: Local player input latching & replay recording
// VERIFIED: LF2 0x004198f0
void slot_latch_local_inputs(global_t* world, const int32_t* slot_types, const uint8_t* input_bytes,
                             int32_t clear_mode, bool record_replay, uint8_t* replay_out, size_t replay_idx)
{
    if (!world || !slot_types || !input_bytes) return;

    for (uint32_t i = 0; i < 8; ++i) {
        if (slot_types[i] == -1) { // Local player slot
            object_t* obj = world->objects[i];
            if (!obj) continue;

            obj->holding_up     = obj->click_up;
            obj->holding_down   = obj->click_down;
            obj->holding_left   = obj->click_left;
            obj->holding_right  = obj->click_right;
            obj->holding_attack = obj->click_attack;
            obj->holding_jump   = obj->click_jump;
            obj->holding_defend = obj->click_defend;

            if (clear_mode == 0) {
                obj->click_up     = 0;
                obj->click_down   = 0;
                obj->click_left   = 0;
                obj->click_right  = 0;
                obj->click_attack = 0;
                obj->click_jump   = 0;
                obj->click_defend = 0;

                uint8_t b = input_bytes[i];
                if (b & 0x80) obj->click_up     = 1;
                if (b & 0x40) obj->click_down   = 1;
                if (b & 0x20) obj->click_left   = 1;
                if (b & 0x10) obj->click_right  = 1;
                if (b & 0x08) obj->click_attack = 1;
                if (b & 0x04) obj->click_jump   = 1;
                if (b & 0x02) obj->click_defend = 1;

                if (record_replay && replay_out) {
                    replay_out[replay_idx] = b;
                }
            }
        }
    }
}

} // namespace lf2

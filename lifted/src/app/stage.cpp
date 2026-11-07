#include "app/stage.h"
#include "data/cipher.h"
#include "gameplay/entity.h"
#include "core/random.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace lf2 {

bool stage_manager_t::load_stages(const std::string& filepath)
{
    std::string decrypted;
    if (!cipher_t::decrypt_file(filepath, decrypted)) {
        return false;
    }
    return parse_stage_text(decrypted);
}

bool stage_manager_t::parse_stage_text(const std::string& text)
{
    std::istringstream stream(text);
    std::string line;

    stage_definition_t current_stage;
    stage_phase_t current_phase;
    bool in_stage = false;
    bool in_phase = false;

    while (std::getline(stream, line)) {
        // Strip comments after '#'
        size_t comment_pos = line.find('#');
        if (comment_pos != std::string::npos) {
            line = line.substr(0, comment_pos);
        }

        std::istringstream ls(line);
        std::string token;
        if (!(ls >> token)) continue;

        if (token == "<stage>") {
            if (in_stage) {
                m_stages[current_stage.id] = current_stage;
            }
            current_stage = stage_definition_t();
            in_stage = true;
            std::string key;
            while (ls >> key) {
                if (key == "id:") {
                    ls >> current_stage.id;
                }
            }
        } else if (token == "<stage_end>") {
            if (in_stage) {
                m_stages[current_stage.id] = current_stage;
                in_stage = false;
            }
        } else if (token == "<phase>") {
            current_phase = stage_phase_t();
            in_phase = true;
            std::string key;
            while (ls >> key) {
                if (key == "bound:") {
                    ls >> current_phase.bound;
                }
            }
        } else if (token == "<phase_end>") {
            if (in_phase && in_stage) {
                current_stage.phases.push_back(current_phase);
                in_phase = false;
            }
        } else if (in_phase) {
            if (token == "music:") {
                ls >> current_phase.music;
            } else if (token == "when_clear_goto_phase:") {
                ls >> current_phase.when_clear_goto_phase;
            } else if (token == "id:") {
                stage_enemy_spawn_t spawn;
                ls >> spawn.id;
                std::string param;
                while (ls >> param) {
                    if (param == "hp:") {
                        ls >> spawn.hp;
                    } else if (param == "times:") {
                        ls >> spawn.times;
                    } else if (param == "ratio:") {
                        ls >> spawn.ratio;
                    } else if (param == "boss:" || param == "boss" || param == "<boss>") {
                        spawn.is_boss = true;
                    } else if (param == "<soldier>") {
                        spawn.is_soldier = true;
                    } else if (param == "x:") {
                        ls >> spawn.spawn_x;
                    } else if (param == "act:") {
                        ls >> spawn.act;
                    } else if (param == "reserve:") {
                        ls >> spawn.reserve;
                    } else if (param == "join:") {
                        ls >> spawn.join;
                    } else if (param == "join_reserve:") {
                        ls >> spawn.join_reserve;
                    }
                }
                current_phase.enemies.push_back(spawn);
            }
        }
    }

    if (in_stage) {
        m_stages[current_stage.id] = current_stage;
    }

    return !m_stages.empty();
}

const stage_definition_t* stage_manager_t::get_stage(uint32_t stage_id) const
{
    auto it = m_stages.find(stage_id);
    if (it != m_stages.end()) {
        return &it->second;
    }
    return nullptr;
}

void stage_manager_t::start_stage(uint32_t stage_id, global_t* world)
{
    m_current_stage_id = stage_id;
    m_current_phase = 0;
    m_cleared = false;
    m_failed = false;
    m_phase_spawned = false;

    const stage_definition_t* stage = get_stage(stage_id);
    if (!stage || stage->phases.empty()) return;

    spawn_phase_enemies(world, stage->phases[0]);
    m_phase_spawned = true;
}

void stage_manager_t::spawn_phase_enemies(global_t* world, const stage_phase_t& phase)
{
    if (!world) return;

    // Enemy spawn slots start after players (slot 10+)
    uint32_t current_slot = 10;

    for (const auto& enemy : phase.enemies) {
        for (uint32_t t = 0; t < enemy.times; ++t) {
            while (current_slot < MAX_OBJECTS && world->is_object_exists[current_slot]) {
                current_slot++;
            }
            if (current_slot >= MAX_OBJECTS) break;

            object_t* obj = world->objects[current_slot];
            if (!obj) {
                obj = new object_t();
                world->objects[current_slot] = obj;
            }

            object_init(obj);
            obj->hp = enemy.hp;
            obj->max_hp = enemy.hp;
            obj->dark_hp = enemy.hp;
            obj->team = 5; // Authentic LF2 Stage Mode Enemy Team
            obj->facing = FACING_LEFT;

            // Spawn placement
            int32_t base_x = (enemy.spawn_x > 0) ? enemy.spawn_x : 600;
            obj->x = base_x + static_cast<int32_t>(lf2_random(0xC0 + current_slot, 200));
            obj->y = 0;
            obj->z = 150 + static_cast<int32_t>(lf2_random(0xD0 + current_slot, 150));
            obj->x_position = static_cast<double>(obj->x);
            obj->y_position = static_cast<double>(obj->y);
            obj->z_position = static_cast<double>(obj->z);

            world->is_object_exists[current_slot] = 1;
            current_slot++;
        }
    }
}

void stage_manager_t::update_stage(global_t* world, double camera_x)
{
    (void)camera_x;
    if (!world || m_cleared || m_failed) return;

    const stage_definition_t* stage = get_stage(m_current_stage_id);
    if (!stage || m_current_phase >= stage->phases.size()) return;

    // 1. Check if all player team (team != 5) entities are dead
    bool players_alive = false;
    for (uint32_t i = 0; i < 10; ++i) {
        if (world->is_object_exists[i] && world->objects[i] &&
            world->objects[i]->team != 5 && world->objects[i]->hp > 0) {
            players_alive = true;
            break;
        }
    }
    if (!players_alive) {
        m_failed = true;
        return;
    }

    // 2. Check if all enemies in current phase (team 5) are defeated
    bool enemies_alive = false;
    for (uint32_t i = 10; i < MAX_OBJECTS; ++i) {
        if (world->is_object_exists[i] && world->objects[i] &&
            world->objects[i]->team == 5 && world->objects[i]->hp > 0) {
            enemies_alive = true;
            break;
        }
    }

    // 3. If all enemies defeated, advance to next phase
    if (!enemies_alive) {
        m_current_phase++;
        if (m_current_phase >= stage->phases.size()) {
            m_cleared = true;
        } else {
            spawn_phase_enemies(world, stage->phases[m_current_phase]);
        }
    }
}

} // namespace lf2

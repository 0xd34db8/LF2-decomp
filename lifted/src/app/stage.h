#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include "core/global.h"

namespace lf2 {

struct stage_enemy_spawn_t {
    uint32_t id = 0;
    int32_t  hp = 50;
    uint32_t times = 1;
    double   ratio = 1.0;
    bool     is_boss = false;
    int32_t  spawn_x = 0;
};

struct stage_phase_t {
    uint32_t bound = 1500;
    std::string music;
    std::vector<stage_enemy_spawn_t> enemies;
};

struct stage_definition_t {
    uint32_t id = 0;
    std::string name;
    std::vector<stage_phase_t> phases;
};

// Stage mode progression engine: loads authentic stage.dat files and coordinates phase events
class stage_manager_t {
public:
    stage_manager_t() = default;

    bool load_stages(const std::string& filepath);
    bool parse_stage_text(const std::string& text);

    void start_stage(uint32_t stage_id, global_t* world);
    void update_stage(global_t* world, double camera_x);

    uint32_t get_current_stage_id() const { return m_current_stage_id; }
    uint32_t get_current_phase_index() const { return m_current_phase; }
    bool is_stage_cleared() const { return m_cleared; }
    bool is_stage_failed() const { return m_failed; }
    size_t get_stage_count() const { return m_stages.size(); }
    const stage_definition_t* get_stage(uint32_t stage_id) const;

private:
    void spawn_phase_enemies(global_t* world, const stage_phase_t& phase);

    std::unordered_map<uint32_t, stage_definition_t> m_stages;
    uint32_t m_current_stage_id = 0;
    uint32_t m_current_phase = 0;
    bool m_cleared = false;
    bool m_failed = false;
    bool m_phase_spawned = false;
};

} // namespace lf2


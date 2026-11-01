#include "battle.h"
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <set>

namespace lf2 {

std::string format_battle_multiplier(int32_t multiplier) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "x %d.%d", multiplier / 100, (multiplier % 100) / 10);
    return std::string(buf);
}

int32_t cycle_battle_multiplier_next(int32_t current) {
    current += BATTLE_MULTIPLIER_STEP;
    if (current > BATTLE_MULTIPLIER_MAX) {
        current = BATTLE_MULTIPLIER_MIN;
    }
    return current;
}

int32_t cycle_battle_multiplier_prev(int32_t current) {
    current -= BATTLE_MULTIPLIER_STEP;
    if (current < BATTLE_MULTIPLIER_MIN) {
        current = BATTLE_MULTIPLIER_MAX;
    }
    return current;
}

void calculate_squad_quota(int32_t base_active, int32_t base_total, int32_t scale_or_mult,
                           int32_t& out_active, int32_t& out_reserve) {
    // 1:1 with 0x00438B40 ratio distribution arithmetic
    int32_t scaled_total = (base_total * scale_or_mult) / 3;
    int32_t scaled_active = (base_active * scale_or_mult) / 3;

    if (scaled_active < 1 && scaled_total > 0) {
        scaled_active = 1;
    }

    int32_t reserve = scaled_total - scaled_active;
    if (reserve < 0) {
        reserve = 0;
    }

    out_active = scaled_active;
    out_reserve = reserve;
}

int32_t battle_army_t::get_total_active() const {
    int32_t sum = 0;
    for (const auto& slot : slots) {
        sum += slot.active_count;
    }
    return sum;
}

int32_t battle_army_t::get_total_reserve() const {
    int32_t sum = 0;
    for (const auto& slot : slots) {
        sum += slot.reserve_count;
    }
    return sum;
}

int32_t battle_army_t::get_total_troops() const {
    return get_total_active() + get_total_reserve();
}

int32_t battle_army_t::get_total_hp() const {
    int32_t sum = 0;
    for (const auto& slot : slots) {
        sum += slot.active_count * slot.unit_hp;
    }
    return sum;
}

bool battle_army_t::is_annihilated() const {
    return (get_total_active() == 0 && get_total_reserve() == 0);
}

void apply_archetype_preset(battle_army_t& army, battle_archetype_t archetype,
                            int32_t unit_type_count) {
    army.archetype = archetype;
    army.slots.clear();
    army.slots.resize(unit_type_count);

    if (archetype == battle_archetype_t::NONE) {
        for (int32_t i = 0; i < unit_type_count; ++i) {
            army.slots[i].unit_id = i;
            army.slots[i].active_count = 0;
            army.slots[i].reserve_count = 0;
            army.slots[i].total_quota = 0;
            army.slots[i].unit_hp = 500;
        }
        return;
    }

    // Base template quotas (base_active, base_total) before scaling
    int32_t base_active = 3;
    int32_t base_total = 9;
    int32_t hp = 500;

    switch (archetype) {
        case battle_archetype_t::INFERIOR:
            // Light fodder infantry / bandits / hunters: large squads, lower HP
            base_active = 6;
            base_total = 18;
            hp = 300;
            break;
        case battle_archetype_t::BALANCED:
            // Standard martial artists
            base_active = 3;
            base_total = 9;
            hp = 500;
            break;
        case battle_archetype_t::HEAVY_GIANT:
            // Heavy armored knights, bosses: elite small squads, high HP
            base_active = 2;
            base_total = 6;
            hp = 1000;
            break;
        case battle_archetype_t::CUSTOM_ALL_OUT:
            // 1:1 with 0x00438B40 custom all-out army: 30 reserves, 2 active
            for (int32_t i = 0; i < unit_type_count; ++i) {
                army.slots[i].unit_id = i;
                army.slots[i].active_count = 2;
                army.slots[i].reserve_count = 30;
                army.slots[i].total_quota = 32;
                army.slots[i].unit_hp = 500;
            }
            if (unit_type_count > 1) {
                army.slots[1].active_count = 1;
                army.slots[1].reserve_count = 15;
                army.slots[1].total_quota = 16;
            }
            if (unit_type_count > 3) {
                army.slots[3].active_count = 3;
                army.slots[3].reserve_count = 3;
                army.slots[3].total_quota = 6;
            }
            // Scale by multiplier
            if (army.multiplier != 100) {
                for (auto& s : army.slots) {
                    s.active_count = (s.active_count * army.multiplier) / 100;
                    s.reserve_count = (s.reserve_count * army.multiplier) / 100;
                    if (s.active_count < 1 && (s.active_count + s.reserve_count) > 0) {
                        s.active_count = 1;
                    }
                    s.total_quota = s.active_count + s.reserve_count;
                }
            }
            return;
        case battle_archetype_t::MELEE_DOMINANT:
            // Close combat heavy
            for (int32_t i = 0; i < unit_type_count; ++i) {
                army.slots[i].unit_id = i;
                if (i % 2 == 0) { // Melee
                    base_active = 5;
                    base_total = 15;
                    hp = 550;
                } else { // Support
                    base_active = 2;
                    base_total = 6;
                    hp = 400;
                }
                int32_t act = 0, res = 0;
                calculate_squad_quota(base_active, base_total, 3, act, res);
                act = (act * army.multiplier) / 100;
                res = (res * army.multiplier) / 100;
                if (act < 1 && (act + res) > 0) act = 1;
                army.slots[i].active_count = act;
                army.slots[i].reserve_count = res;
                army.slots[i].total_quota = act + res;
                army.slots[i].unit_hp = hp;
            }
            return;
        case battle_archetype_t::RANGED_DOMINANT:
            // Ranged heavy
            for (int32_t i = 0; i < unit_type_count; ++i) {
                army.slots[i].unit_id = i;
                if (i % 2 == 1) { // Ranged
                    base_active = 6;
                    base_total = 18;
                    hp = 400;
                } else { // Frontline guard
                    base_active = 2;
                    base_total = 6;
                    hp = 600;
                }
                int32_t act = 0, res = 0;
                calculate_squad_quota(base_active, base_total, 3, act, res);
                act = (act * army.multiplier) / 100;
                res = (res * army.multiplier) / 100;
                if (act < 1 && (act + res) > 0) act = 1;
                army.slots[i].active_count = act;
                army.slots[i].reserve_count = res;
                army.slots[i].total_quota = act + res;
                army.slots[i].unit_hp = hp;
            }
            return;
        case battle_archetype_t::RANDOM_ARMY:
        default:
            for (int32_t i = 0; i < unit_type_count; ++i) {
                army.slots[i].unit_id = i;
                int32_t act = 1 + (i % 4);
                int32_t res = 3 + (i * 2);
                act = (act * army.multiplier) / 100;
                res = (res * army.multiplier) / 100;
                if (act < 1 && (act + res) > 0) act = 1;
                army.slots[i].active_count = act;
                army.slots[i].reserve_count = res;
                army.slots[i].total_quota = act + res;
                army.slots[i].unit_hp = 500;
            }
            return;
    }

    // Apply standard archetype formula with multiplier scaling
    for (int32_t i = 0; i < unit_type_count; ++i) {
        army.slots[i].unit_id = i;
        army.slots[i].unit_hp = hp;

        int32_t act = 0, res = 0;
        calculate_squad_quota(base_active, base_total, 3, act, res);

        act = (act * army.multiplier) / 100;
        res = (res * army.multiplier) / 100;
        if (act < 1 && (act + res) > 0) {
            act = 1;
        }

        army.slots[i].active_count = act;
        army.slots[i].reserve_count = res;
        army.slots[i].total_quota = act + res;
    }
}

std::string format_battle_status_hud(int32_t man_count, int32_t hp, int32_t reserve_count) {
    char buf[128];
    if (reserve_count == 0) {
        std::snprintf(buf, sizeof(buf), "Man: %3d      HP: %4d", man_count, hp);
    } else {
        std::snprintf(buf, sizeof(buf), "Man: %3d      HP: %4d     Reserve: %3d",
                      man_count, hp, reserve_count);
    }
    return std::string(buf);
}

std::string format_stage_hud(int32_t stage_code) {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "STAGE %d-%d", stage_code / 10 + 1, stage_code % 10 + 1);
    return std::string(buf);
}

std::string format_survival_stage_hud(int32_t survival_stage) {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "Survival Stage: %d", survival_stage);
    return std::string(buf);
}

std::string format_battle_replay_filename(int32_t year, int32_t month, int32_t day,
                                          int32_t hour, int32_t minute, int32_t second) {
    char buf[128];
    std::snprintf(buf, sizeof(buf), "%04d%02d%02d_%02d%02d%02d_Battle.lfr",
                  year, month, day, hour, minute, second);
    return std::string(buf);
}

std::string format_current_battle_replay_filename() {
    std::time_t now = std::time(nullptr);
    std::tm* t = std::localtime(&now);
    if (!t) return "20260101_000000_Battle.lfr";
    return format_battle_replay_filename(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                                         t->tm_hour, t->tm_min, t->tm_sec);
}

void battle_skirmish_simulator_t::reset() {
    m_armies.clear();
    m_battle_over = false;
    m_winning_team = -1;
}

void battle_skirmish_simulator_t::add_army(const battle_army_t& army) {
    m_armies.push_back(army);
}

int32_t battle_skirmish_simulator_t::replenish_reinforcements(size_t army_idx) {
    if (army_idx >= m_armies.size()) return 0;
    auto& army = m_armies[army_idx];
    if (army.get_total_reserve() == 0) return 0;

    int32_t current_active = army.get_total_active();
    int32_t needed = army.target_max_active - current_active;
    if (needed <= 0) return 0;

    int32_t spawned = 0;
    for (auto& slot : army.slots) {
        while (slot.reserve_count > 0 && needed > 0) {
            slot.reserve_count--;
            slot.active_count++;
            spawned++;
            needed--;
        }
        if (needed <= 0) break;
    }
    return spawned;
}

void battle_skirmish_simulator_t::record_casualty(size_t army_idx, size_t slot_idx) {
    if (army_idx >= m_armies.size()) return;
    auto& army = m_armies[army_idx];
    if (slot_idx >= army.slots.size()) return;

    if (army.slots[slot_idx].active_count > 0) {
        army.slots[slot_idx].active_count--;
        army.casualties++;
    }

    // Try to replenish from reserve if slots are open
    replenish_reinforcements(army_idx);
}

bool battle_skirmish_simulator_t::is_battle_over() const {
    return m_battle_over;
}

int32_t battle_skirmish_simulator_t::get_winning_team() const {
    return m_winning_team;
}

void battle_skirmish_simulator_t::step_simulation() {
    if (m_battle_over) return;

    std::set<int32_t> active_teams;
    for (const auto& army : m_armies) {
        if (!army.is_annihilated()) {
            active_teams.insert(army.team_id);
        }
    }

    if (active_teams.empty()) {
        m_battle_over = true;
        m_winning_team = -1; // Mutual annihilation
    } else if (active_teams.size() == 1) {
        m_battle_over = true;
        m_winning_team = *active_teams.begin();
    }
}

} // namespace lf2


#include "tournament.h"
#include "core/random.h"
#include <algorithm>
#include <cstdio>
#include <ctime>

namespace lf2 {

tournament_manager_t::tournament_manager_t() {
    init(tournament_match_type_t::MATCH_1ON1, 8);
}

void tournament_manager_t::init(tournament_match_type_t match_type, uint32_t contestant_count) {
    m_match_type = match_type;
    m_state = tournament_state_t::RESET;

    uint32_t count = contestant_count;
    if (match_type == tournament_match_type_t::MATCH_2ON2) {
        if (count == 8) {
            // 4 teams of 2 start at SemiFinal (round 2)
            m_current_round = tournament_round_t::ROUND_SEMIFINAL;
        } else {
            // 8 teams of 2 (16 contestants) start at Prelminar (round 0)
            count = 16;
            m_current_round = tournament_round_t::ROUND_PRELIMINAR;
        }
    } else {
        if (count != 4 && count != 8 && count != 16) count = 8;
        if (count == 4) {
            m_current_round = tournament_round_t::ROUND_SEMIFINAL;
        } else {
            m_current_round = tournament_round_t::ROUND_PRELIMINAR;
        }
    }

    int32_t initial_progress = static_cast<int32_t>(m_current_round);
    m_contestants.resize(count);
    m_seed_order.resize(count);

    // 1:1 State 0x14: Reset contestant parameters
    for (uint32_t i = 0; i < count; ++i) {
        m_contestants[i].slot_id = static_cast<int32_t>(i);
        m_contestants[i].char_id = -1; // -1: Random
        m_contestants[i].controller = tournament_controller_t::COMPUTER;
        m_contestants[i].hp = 500;
        m_contestants[i].max_hp = 500;
        m_contestants[i].progress = initial_progress;
        m_contestants[i].is_boss = false;
        m_contestants[i].name = "Contestant " + std::to_string(i + 1);

        m_seed_order[i] = static_cast<int32_t>(i);
    }

    m_match_history.clear();
}

void tournament_manager_t::set_contestant(uint32_t slot, int32_t char_id,
                                         tournament_controller_t controller,
                                         bool is_boss,
                                         const std::string& name) {
    if (slot >= m_contestants.size()) return;
    m_contestants[slot].char_id = char_id;
    m_contestants[slot].controller = controller;
    m_contestants[slot].is_boss = is_boss;
    if (!name.empty()) {
        m_contestants[slot].name = name;
    }
}

const tournament_contestant_t& tournament_manager_t::get_contestant(uint32_t slot) const {
    return m_contestants.at(slot);
}

tournament_contestant_t& tournament_manager_t::get_contestant(uint32_t slot) {
    return m_contestants.at(slot);
}

void tournament_manager_t::shuffle_bracket() {
    // 1:1 Lift of State 0x17 (func_00432ab0_tournament.c: lines 565-573)
    // Exactly 50 random swap iterations using PRNG circular lookup
    int count = static_cast<int>(m_seed_order.size());
    if (count < 2) return;

    for (int i = 0; i < 50; ++i) {
        int s1 = lf2_random(0xf7, count);
        int s2 = lf2_random(0xf8, count);
        std::swap(m_seed_order[s1], m_seed_order[s2]);
    }

    m_state = tournament_state_t::SHUFFLE;
}

void tournament_manager_t::autofill_randoms(const std::vector<int32_t>& available_character_ids) {
    // 1:1 Lift of State 0x18: Autofill unassigned random slots
    if (available_character_ids.empty()) return;

    for (auto& contestant : m_contestants) {
        if (contestant.char_id < 0) {
            int idx = lf2_random(0xfe, static_cast<int>(available_character_ids.size()));
            contestant.char_id = available_character_ids[idx];
        }
    }

    m_state = tournament_state_t::AUTOFILL;
}

int32_t tournament_manager_t::calculate_cpu_degraded_hp(int32_t current_hp, tournament_difficulty_t difficulty) {
    // 1:1 Lift of State 0x1A HP degradation math (func_00432ab0_tournament.c: lines 717-724):
    // diff = _DAT_00450c30 (0=Difficult, 1=Normal, 2=Easy)
    // roll = FUN_00417170(0xfc, diff * 12 + 15)
    // hp = ((roll - diff * 12 + 85) * hp) / 100
    int32_t diff = static_cast<int32_t>(difficulty);
    if (diff < -1) diff = 0;

    int32_t roll = lf2_random(0xfc, diff * 12 + 15);
    int32_t degraded = ((roll - diff * 12 + 85) * current_hp) / 100;
    if (degraded < 1) degraded = 1;
    return degraded;
}

bool tournament_manager_t::find_next_match(tournament_match_t& out_match) {
    if (is_tournament_finished()) {
        return false;
    }

    int32_t target_progress = static_cast<int32_t>(m_current_round);
    uint32_t total_slots = static_cast<uint32_t>(m_seed_order.size());

    if (m_match_type == tournament_match_type_t::MATCH_1ON1) {
        // 1:1 with State 0x1A: Scan for 2 contestants with progress == current_round
        std::vector<int32_t> found_slots;
        for (uint32_t i = 0; i < total_slots; ++i) {
            int32_t slot = m_seed_order[i];
            if (m_contestants[slot].progress == target_progress) {
                found_slots.push_back(slot);
                if (found_slots.size() == 2) break;
            }
        }

        if (found_slots.size() == 2) {
            out_match.match_id = static_cast<int32_t>(m_match_history.size() + 1);
            out_match.round = m_current_round;
            out_match.team1_slots = { found_slots[0] };
            out_match.team2_slots = { found_slots[1] };
            out_match.is_cpu_vs_cpu = (m_contestants[found_slots[0]].controller == tournament_controller_t::COMPUTER &&
                                        m_contestants[found_slots[1]].controller == tournament_controller_t::COMPUTER);
            out_match.completed = false;
            out_match.winner_team = -1;
            out_match.replay_filename = generate_replay_filename(m_current_round);

            m_state = out_match.is_cpu_vs_cpu ? tournament_state_t::MATCH_SELECT : tournament_state_t::CONTROLLER_ASSIGN;
            return true;
        }
    } else {
        // 2-on-2 mode: scan for 4 contestants (2 per team) with progress == current_round
        std::vector<int32_t> found_slots;
        for (uint32_t i = 0; i < total_slots; ++i) {
            int32_t slot = m_seed_order[i];
            if (m_contestants[slot].progress == target_progress) {
                found_slots.push_back(slot);
                if (found_slots.size() == 4) break;
            }
        }

        if (found_slots.size() == 4) {
            out_match.match_id = static_cast<int32_t>(m_match_history.size() + 1);
            out_match.round = m_current_round;
            out_match.team1_slots = { found_slots[0], found_slots[1] };
            out_match.team2_slots = { found_slots[2], found_slots[3] };

            bool team1_cpu = (m_contestants[found_slots[0]].controller == tournament_controller_t::COMPUTER &&
                              m_contestants[found_slots[1]].controller == tournament_controller_t::COMPUTER);
            bool team2_cpu = (m_contestants[found_slots[2]].controller == tournament_controller_t::COMPUTER &&
                              m_contestants[found_slots[3]].controller == tournament_controller_t::COMPUTER);
            out_match.is_cpu_vs_cpu = (team1_cpu && team2_cpu);
            out_match.completed = false;
            out_match.winner_team = -1;
            out_match.replay_filename = generate_replay_filename(m_current_round);

            m_state = out_match.is_cpu_vs_cpu ? tournament_state_t::MATCH_SELECT : tournament_state_t::CONTROLLER_ASSIGN;
            return true;
        }
    }

    // No matches remaining at current round; advance round and try again
    advance_round_if_needed();
    if (!is_tournament_finished() && m_current_round != static_cast<tournament_round_t>(target_progress)) {
        return find_next_match(out_match);
    }

    return false;
}

bool tournament_manager_t::simulate_cpu_match(tournament_match_t& match) {
    if (match.team1_slots.empty() || match.team2_slots.empty()) return false;

    // 1:1 Lift of State 0x1A boss advantage evaluation
    int32_t winner_team = 1;

    if (m_match_type == tournament_match_type_t::MATCH_1ON1) {
        int32_t slot1 = match.team1_slots[0];
        int32_t slot2 = match.team2_slots[0];

        bool boss1 = m_contestants[slot1].is_boss;
        bool boss2 = m_contestants[slot2].is_boss;

        if (boss1 && !boss2) {
            winner_team = 1;
        } else if (!boss1 && boss2) {
            winner_team = 2;
        } else if (boss1 && boss2) {
            int roll = lf2_random(0xfb, 2);
            winner_team = (roll == 0) ? 1 : 2;
        } else {
            int roll = lf2_random(0xfa, 2);
            winner_team = (roll == 0) ? 1 : 2;
        }
    } else {
        int boss_count1 = 0;
        for (int32_t s : match.team1_slots) if (m_contestants[s].is_boss) ++boss_count1;
        int boss_count2 = 0;
        for (int32_t s : match.team2_slots) if (m_contestants[s].is_boss) ++boss_count2;

        if (boss_count1 > boss_count2) {
            winner_team = 1;
        } else if (boss_count2 > boss_count1) {
            winner_team = 2;
        } else {
            int roll = lf2_random(0xfa, 2);
            winner_team = (roll == 0) ? 1 : 2;
        }
    }

    // 1:1 Winner/loser progression & HP degradation
    auto& winning_slots = (winner_team == 1) ? match.team1_slots : match.team2_slots;
    auto& losing_slots  = (winner_team == 1) ? match.team2_slots : match.team1_slots;

    for (int32_t s : winning_slots) {
        m_contestants[s].progress += 2;
        if (m_contestants[s].progress == 6) {
            m_contestants[s].progress = 7; // Crowned Champion!
        }
        m_contestants[s].hp = calculate_cpu_degraded_hp(m_contestants[s].hp, m_difficulty);
    }

    for (int32_t s : losing_slots) {
        m_contestants[s].progress += 1; // Knocked out!
    }

    match.completed = true;
    match.winner_team = winner_team;
    m_match_history.push_back(match);

    advance_round_if_needed();
    return true;
}

void tournament_manager_t::complete_human_match(tournament_match_t& match, int32_t winner_team,
                                               const std::vector<int32_t>& survivor_hps) {
    if (winner_team != 1 && winner_team != 2) return;

    auto& winning_slots = (winner_team == 1) ? match.team1_slots : match.team2_slots;
    auto& losing_slots  = (winner_team == 1) ? match.team2_slots : match.team1_slots;

    // 1:1 Lift of State 0x1C: Save battle survivor HP
    for (size_t i = 0; i < winning_slots.size(); ++i) {
        int32_t s = winning_slots[i];
        m_contestants[s].progress += 2;
        if (m_contestants[s].progress == 6) {
            m_contestants[s].progress = 7;
        }
        if (i < survivor_hps.size() && survivor_hps[i] > 0) {
            m_contestants[s].hp = survivor_hps[i];
        }
    }

    for (int32_t s : losing_slots) {
        m_contestants[s].progress += 1;
    }

    match.completed = true;
    match.winner_team = winner_team;
    m_match_history.push_back(match);

    advance_round_if_needed();
}

void tournament_manager_t::advance_round_if_needed() {
    // Check if anyone has won the championship
    for (const auto& c : m_contestants) {
        if (c.progress == 7) {
            m_current_round = tournament_round_t::ROUND_CHAMPION;
            m_state = tournament_state_t::VICTORY;
            return;
        }
    }

    int32_t current_level = static_cast<int32_t>(m_current_round);
    size_t count_at_current = 0;
    for (const auto& c : m_contestants) {
        if (c.progress == current_level) {
            count_at_current++;
        }
    }

    size_t needed = (m_match_type == tournament_match_type_t::MATCH_1ON1) ? 2 : 4;
    if (count_at_current < needed) {
        // 1:1 State 0x1A: current_round += 2
        if (m_current_round == tournament_round_t::ROUND_PRELIMINAR) {
            m_current_round = tournament_round_t::ROUND_SEMIFINAL;
            m_state = tournament_state_t::MATCH_SELECT;
        } else if (m_current_round == tournament_round_t::ROUND_SEMIFINAL) {
            m_current_round = tournament_round_t::ROUND_FINAL;
            m_state = tournament_state_t::MATCH_SELECT;
        }
    }
}

int32_t tournament_manager_t::get_champion_slot() const {
    for (const auto& c : m_contestants) {
        if (c.progress == 7) {
            return c.slot_id;
        }
    }
    return -1;
}

bool tournament_manager_t::is_tournament_finished() const {
    return get_champion_slot() != -1;
}

std::string tournament_manager_t::generate_replay_filename(tournament_round_t round, const struct tm* timeinfo) const {
    // 1:1 Lift of 0x00432AB0 replay filename assembly (func_00432ab0_tournament.c: lines 890-924)
    struct tm t;
    if (timeinfo) {
        t = *timeinfo;
    } else {
        time_t rawtime;
        time(&rawtime);
#ifdef _WIN32
        localtime_s(&t, &rawtime);
#else
        localtime_r(&rawtime, &t);
#endif
    }

    char buf[64];
    snprintf(buf, sizeof(buf), "%04d%02d%02d_%02d%02d%02d",
             t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
             t.tm_hour, t.tm_min, t.tm_sec);

    std::string filename = buf;
    if (m_match_type == tournament_match_type_t::MATCH_1ON1) {
        filename += "_1on1_";
    } else {
        filename += "_2on2_";
    }

    // Authentic LF2 string naming (including original "Prelminar" spelling)
    if (round == tournament_round_t::ROUND_PRELIMINAR) {
        filename += "Prelminar";
    } else if (round == tournament_round_t::ROUND_SEMIFINAL) {
        filename += "SemiFinal";
    } else if (round == tournament_round_t::ROUND_FINAL) {
        filename += "Final";
    } else {
        filename += "Champion";
    }

    filename += ".lfr";
    return filename;
}

} // namespace lf2


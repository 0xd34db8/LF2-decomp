#include "app/survival.h"
#include <cstdio>
#include <ctime>
#include <algorithm>

namespace lf2 {

survival_manager_t::survival_manager_t(survival_difficulty_t difficulty)
    : m_difficulty(difficulty) {
    reset();
}

void survival_manager_t::reset() {
    m_current_wave = 1;
    m_curtain_state = 0;
    m_curtain_wipe = 0;
    m_curtain_wait = 0;
    m_anim_tick = 0;
}

void survival_manager_t::advance_wave() {
    m_current_wave++;
}

int32_t survival_manager_t::calculate_heal_amount() const {
    // 1:1 with 0x00436FC0: (_DAT_00450c30 + 2) * 50
    return (static_cast<int32_t>(m_difficulty) + 2) * 50;
}

void survival_manager_t::apply_wave_clear_vitals(std::vector<object_t*>& players) {
    int32_t heal_bonus = calculate_heal_amount();

    for (object_t* player : players) {
        if (!player) continue;

        if (player->hp < 1) {
            // Revive dead player (1:1 with 0x00437860 lines 197-241)
            player->hp = 5;
            player->dark_hp = 5;
            player->mp = 500;
        } else {
            // Heal surviving player (1:1 with 0x00436FC0)
            player->hp += heal_bonus;
            if (player->hp > player->max_hp) {
                player->hp = player->max_hp;
            }
            player->dark_hp = player->hp;
            player->mp = 500;
        }

        // Reset knockdown / falling states (1:1 with 0x00436FC0 lines 63-68)
        if (player->frame_id1 > 8 && player->frame_id1 < 12) {
            player->frame_id1 = 0;
        }
        if (player->frame_id1 > 15 && player->frame_id1 < 19) {
            player->frame_id1 = 12;
        }
    }
}

std::string survival_manager_t::get_milestone_bgm(uint32_t wave_number) {
    if (!is_boss_milestone(wave_number)) {
        uint32_t cycle = ((wave_number - 1) / 5) % 4 + 1;
        return "bgm\\stage" + std::to_string(cycle) + ".wma";
    }

    // Milestone Boss BGM: Julian (wave >= 50) and even milestones use boss2.wma; early odd milestones use boss1.wma
    if (wave_number >= 50 || wave_number % 20 == 0) {
        return "bgm\\boss2.wma";
    }
    return "bgm\\boss1.wma";
}

survival_wave_spec_t survival_manager_t::generate_wave(uint32_t wave_number) const {
    survival_wave_spec_t wave;
    wave.wave_number = wave_number;
    wave.is_boss_wave = is_boss_milestone(wave_number);
    wave.bgm = get_milestone_bgm(wave_number);

    // Scaling factors
    double hp_multiplier = 1.0 + static_cast<double>(wave_number - 1) * 0.05; // +5% HP per wave
    uint32_t bonus_fodder = (wave_number / 5);

    // Regular infantry: Bandits (ID 30) & Hunters (ID 31)
    stage_enemy_spawn_t bandits;
    bandits.id = 30;
    bandits.hp = static_cast<int32_t>(60.0 * hp_multiplier);
    bandits.times = 2 + bonus_fodder;
    bandits.ratio = 1.0;
    bandits.is_boss = false;
    bandits.spawn_x = 650;
    wave.spawns.push_back(bandits);

    stage_enemy_spawn_t hunters;
    hunters.id = 31;
    hunters.hp = static_cast<int32_t>(75.0 * hp_multiplier);
    hunters.times = 1 + (wave_number / 6);
    hunters.ratio = 1.0;
    hunters.is_boss = false;
    hunters.spawn_x = 720;
    wave.spawns.push_back(hunters);

    // Mid-tier martial artists (Wave 3+)
    if (wave_number >= 3) {
        stage_enemy_spawn_t martial_artist;
        martial_artist.id = static_cast<uint32_t>(1 + (wave_number % 5)); // Davis/Dennis/Woody
        martial_artist.hp = static_cast<int32_t>(120.0 * hp_multiplier);
        martial_artist.times = 1 + (wave_number / 8);
        martial_artist.ratio = 1.2;
        martial_artist.is_boss = false;
        martial_artist.spawn_x = 680;
        wave.spawns.push_back(martial_artist);
    }

    // Heavy units: Knights & Golems (Wave 6+)
    if (wave_number >= 6) {
        stage_enemy_spawn_t heavy;
        heavy.id = KNIGHT_DAT; // Knight (37)
        heavy.hp = static_cast<int32_t>(200.0 * hp_multiplier);
        heavy.times = 1 + (wave_number / 10);
        heavy.ratio = 1.5;
        heavy.is_boss = false;
        heavy.spawn_x = 750;
        wave.spawns.push_back(heavy);
    }

    // Milestone Boss Spawns
    if (wave.is_boss_wave) {
        stage_enemy_spawn_t boss;
        boss.is_boss = true;
        boss.times = 1;
        boss.spawn_x = 700;

        uint32_t milestone_tier = wave_number / 10;
        double boss_hp_scale = 1.0 + static_cast<double>(milestone_tier) * 0.25;

        switch (milestone_tier) {
            case 1:
                boss.id = FIRZEN_DAT; // Firzen (51)
                boss.hp = static_cast<int32_t>(500.0 * boss_hp_scale);
                break;
            case 2:
                boss.id = LOUISE_EX_DAT; // LouisEX (50)
                boss.hp = static_cast<int32_t>(700.0 * boss_hp_scale);
                break;
            case 3:
                boss.id = BAT_DAT; // Bat (38)
                boss.hp = static_cast<int32_t>(900.0 * boss_hp_scale);
                break;
            case 4:
                boss.id = FIRZEN_DAT; // Firzen Boss (51)
                boss.hp = static_cast<int32_t>(1100.0 * boss_hp_scale);
                break;
            case 5:
            default:
                boss.id = JULIAN_DAT; // Julian (52)
                boss.hp = static_cast<int32_t>(1500.0 * boss_hp_scale);
                break;
        }
        wave.spawns.push_back(boss);
    }

    // Total enemy count calculation
    wave.total_enemies = 0;
    for (const auto& sp : wave.spawns) {
        wave.total_enemies += sp.times;
    }

    return wave;
}

survival_wave_spec_t survival_manager_t::generate_wave_from_stage_data(const stage_manager_t& stage_mgr, uint32_t wave_number) const {
    const stage_definition_t* s50 = stage_mgr.get_stage(50);
    if (s50 && wave_number >= 1 && wave_number <= s50->phases.size()) {
        const auto& phase = s50->phases[wave_number - 1];
        survival_wave_spec_t wave;
        wave.wave_number = wave_number;
        wave.is_boss_wave = is_boss_milestone(wave_number);
        wave.bgm = !phase.music.empty() ? phase.music : get_milestone_bgm(wave_number);
        wave.spawns = phase.enemies;
        wave.total_enemies = 0;
        for (const auto& sp : wave.spawns) {
            wave.total_enemies += sp.times;
        }
        return wave;
    }
    return generate_wave(wave_number);
}

std::string survival_manager_t::format_hud() const {
    char buf[64];
    std::snprintf(buf, sizeof(buf), "Survival Stage: %d", m_current_wave);
    return std::string(buf);
}

std::string survival_manager_t::generate_replay_filename() const {
    std::time_t now = std::time(nullptr);
    std::tm* t = std::localtime(&now);
    char buf[128];
    if (t) {
        std::snprintf(buf, sizeof(buf), "%04d%02d%02d_%02d%02d%02d_Survival.lfr",
                      t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                      t->tm_hour, t->tm_min, t->tm_sec);
    } else {
        std::snprintf(buf, sizeof(buf), "20260101_000000_Survival.lfr");
    }
    return std::string(buf);
}

void survival_manager_t::update_curtain_step(bool action_key_pressed) {
    // 1:1 with 0x00437220 state machine
    m_anim_tick = (m_anim_tick + 1) % 10;

    if (m_difficulty == survival_difficulty_t::NORMAL || m_difficulty == survival_difficulty_t::EASY) {
        if (m_curtain_state == 1) {
            m_curtain_state = 2;
        }
    } else if (m_curtain_state == 0) {
        m_curtain_state = 1;
    }

    if (m_curtain_wipe < 13) {
        m_curtain_wipe++;
    } else if (m_curtain_wait == 0) {
        if (action_key_pressed) {
            m_curtain_wait = 1;
        }
    } else if (m_curtain_wait > 0) {
        m_curtain_wait++;
        if (m_curtain_wait > 12) {
            m_curtain_state++;
            m_curtain_wipe = 0;
            m_curtain_wait = 0;
        }
    }
}

} // namespace lf2

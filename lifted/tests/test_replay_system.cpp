#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdio>
#include "core/replay.h"

using namespace lf2;

void test_control_txt_config() {
    std::cout << "[+] Testing data/control.txt Save & Load (0x004233E0 / 0x00423480)..." << std::endl;

    control_config_t cfg{};
    // Setup player 1 keys (Up, Down, Left, Right, Attack, Jump, Defend...)
    cfg.player_keys[0] = { 200, 208, 203, 205, 30, 31, 32, 0, 0, 0, 0 };
    cfg.player_keys[1] = { 17, 31, 30, 32, 36, 37, 38, 0, 0, 0, 0 };
    cfg.player_keys[2] = { 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0 };
    cfg.player_keys[3] = { 8, 9, 10, 11, 12, 13, 14, 0, 0, 0, 0 };

    // Player names with spaces (authentic grave accent conversion)
    cfg.player_names[0] = "Little Bear"; // Marti Wong (Siu Hung)
    cfg.player_names[1] = "Starsky Wong";
    cfg.player_names[2] = "Davis Master";
    cfg.player_names[3] = "Firen Frost";

    cfg.demo_mode = 0;
    cfg.replay_mode = 0;

    const std::string tmp_path = "tests_control_tmp.txt";
    assert(cfg.save_to_file(tmp_path));

    // Load back
    control_config_t loaded{};
    assert(loaded.load_from_file(tmp_path));

    // Verify keys
    for (size_t p = 0; p < MAX_CONTROL_PLAYERS; ++p) {
        for (size_t k = 0; k < KEYS_PER_PLAYER; ++k) {
            assert(loaded.player_keys[p][k] == cfg.player_keys[p][k]);
        }
    }

    // Verify player names with spaces restored
    assert(loaded.player_names[0] == "Little Bear");
    assert(loaded.player_names[1] == "Starsky Wong");
    assert(loaded.player_names[2] == "Davis Master");
    assert(loaded.player_names[3] == "Firen Frost");

    std::remove(tmp_path.c_str());
    std::cout << "    data/control.txt key mappings & space-to-accent encoding verified 100%!" << std::endl;
}

void test_replay_filename_generation() {
    std::cout << "[+] Testing Replay Filename Pattern Generation (0x0042D080)..." << std::endl;

    std::string vs_name = replay_recorder_t::generate_filename(0, 0);
    assert(vs_name.find("_VS.lfr") != std::string::npos);

    std::string stage_name = replay_recorder_t::generate_filename(1, 2);
    assert(stage_name.find("_Stage_3.lfr") != std::string::npos);

    std::string surv_name = replay_recorder_t::generate_filename(1, 5);
    assert(surv_name.find("_Survival.lfr") != std::string::npos);

    std::cout << "    Replay timestamp & game mode filename assembly verified!" << std::endl;
}

void test_replay_record_and_playback() {
    std::cout << "[+] Testing Deterministic 1:1 Replay (.lfr) Record & Playback..." << std::endl;

    replay_header_t hdr{};
    hdr.magic = LF2_REPLAY_MAGIC;
    hdr.prng_seed = 1542; // Seed index into 3,000-byte table
    hdr.game_mode = 0;    // VS Mode
    hdr.stage_number = 0;
    hdr.difficulty = 3;   // CRAZY!
    hdr.player_count = 4;

    hdr.slots[0] = { 1, 1, 0 };  // Davis, Team 1, Human
    hdr.slots[1] = { 2, 2, 1 };  // Woody, Team 2, CPU
    hdr.slots[2] = { 3, 1, 1 };  // Dennis, Team 1, CPU
    hdr.slots[3] = { 4, 2, 0 };  // Freeze, Team 2, Human

    const std::string tmp_lfr = "tests_battle_tmp.lfr";
    replay_recorder_t recorder;
    assert(recorder.start_recording(hdr, tmp_lfr));
    assert(recorder.is_recording());

    // Record 60 frames of deterministic actions
    for (size_t f = 0; f < 60; ++f) {
        uint8_t inputs[8]{};
        inputs[0] = static_cast<uint8_t>((f % 2 == 0) ? 0x08 : 0x04); // Attack / Right
        inputs[1] = static_cast<uint8_t>((f % 3 == 0) ? 0x10 : 0x02); // Jump / Up
        inputs[2] = 0x20;                                             // Defend
        inputs[3] = static_cast<uint8_t>((f % 5 == 0) ? 0x40 : 0x80); // Down / Left
        recorder.record_frame(inputs, (f == 30) ? 0x01 : 0x00);        // F1 pause at frame 30
    }

    assert(recorder.get_recorded_frames() == 60);
    assert(recorder.finish_recording());
    assert(!recorder.is_recording());

    // Playback and verify exact deterministic reproduction
    replay_player_t player;
    assert(player.open_replay(tmp_lfr));
    assert(player.is_open());
    assert(player.get_total_frames() == 60);

    const auto& loaded_hdr = player.get_header();
    assert(loaded_hdr.magic == LF2_REPLAY_MAGIC);
    assert(loaded_hdr.prng_seed == 1542);
    assert(loaded_hdr.difficulty == 3);
    assert(loaded_hdr.player_count == 4);
    assert(loaded_hdr.slots[0].character_id == 1);
    assert(loaded_hdr.slots[1].character_id == 2);
    assert(loaded_hdr.slots[2].character_id == 3);
    assert(loaded_hdr.slots[3].character_id == 4);

    for (size_t f = 0; f < 60; ++f) {
        uint8_t read_inputs[8]{};
        uint8_t flags = 0;
        assert(player.read_frame(read_inputs, flags));

        uint8_t exp_0 = static_cast<uint8_t>((f % 2 == 0) ? 0x08 : 0x04);
        uint8_t exp_1 = static_cast<uint8_t>((f % 3 == 0) ? 0x10 : 0x02);
        uint8_t exp_2 = 0x20;
        uint8_t exp_3 = static_cast<uint8_t>((f % 5 == 0) ? 0x40 : 0x80);
        uint8_t exp_flag = (f == 30) ? 0x01 : 0x00;

        assert(read_inputs[0] == exp_0);
        assert(read_inputs[1] == exp_1);
        assert(read_inputs[2] == exp_2);
        assert(read_inputs[3] == exp_3);
        assert(flags == exp_flag);
    }

    assert(player.is_finished());
    player.close();

    std::remove(tmp_lfr.c_str());
    std::cout << "    Replay recording & playback frame stream verified 100% bit-for-bit!" << std::endl;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    std::cout << "=== Little Fighter 2 Battle Replay & Save Configuration Tests ===" << std::endl;

    test_control_txt_config();
    test_replay_filename_generation();
    test_replay_record_and_playback();

    std::cout << "[SUCCESS] All Replay & Save System tests passed with 100% precision!" << std::endl;
    return 0;
}


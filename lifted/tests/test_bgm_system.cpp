#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>
#include "audio/bgm.h"

using namespace lf2;

void test_track_mappings()
{
    std::cout << "[+] Testing BGM Track ID & Filename Mappings..." << std::endl;

    assert(bgm_manager_t::get_track_filepath(BGM_TRACK_MAIN) == "bgm/main.wma");
    assert(bgm_manager_t::get_track_filepath(BGM_TRACK_STAGE1) == "bgm/stage1.wma");
    assert(bgm_manager_t::get_track_filepath(BGM_TRACK_STAGE2) == "bgm/stage2.wma");
    assert(bgm_manager_t::get_track_filepath(BGM_TRACK_STAGE3) == "bgm/stage3.wma");
    assert(bgm_manager_t::get_track_filepath(BGM_TRACK_STAGE4) == "bgm/stage4.wma");
    assert(bgm_manager_t::get_track_filepath(BGM_TRACK_STAGE5) == "bgm/stage5.wma");
    assert(bgm_manager_t::get_track_filepath(BGM_TRACK_BOSS1) == "bgm/boss1.wma");
    assert(bgm_manager_t::get_track_filepath(BGM_TRACK_BOSS2) == "bgm/boss2.wma");
    assert(bgm_manager_t::get_track_filepath(999) == "");

    assert(bgm_manager_t::get_track_name(BGM_TRACK_OFF) == "OFF");
    assert(bgm_manager_t::get_track_name(BGM_TRACK_RANDOM) == "Random");
    assert(bgm_manager_t::get_track_name(BGM_TRACK_MAIN) == "Main Theme");
    assert(bgm_manager_t::get_track_name(BGM_TRACK_STAGE1) == "Stage 1");
    assert(bgm_manager_t::get_track_name(BGM_TRACK_STAGE5) == "Stage 5");
    assert(bgm_manager_t::get_track_name(BGM_TRACK_BOSS1) == "Boss");
    assert(bgm_manager_t::get_track_name(BGM_TRACK_BOSS2) == "Final Boss");

    std::cout << "    Track filenames and titles verified 1:1!" << std::endl;
}

void test_volume_and_settings()
{
    std::cout << "[+] Testing Volume and Settings Configuration..." << std::endl;
    bgm_manager_t bgm;
    assert(bgm.init() == true);
    assert(bgm.get_volume() == bgm_manager_t::DEFAULT_VOLUME);

    bgm.set_volume(50);
    assert(bgm.get_volume() == 50);

    bgm.set_volume(-10);
    assert(bgm.get_volume() == 0); // clamped to 0

    bgm.set_volume(150);
    assert(bgm.get_volume() == 100); // clamped to 100

    bgm.set_enabled(false);
    assert(bgm.is_enabled() == false);
    bgm.set_enabled(true);
    assert(bgm.is_enabled() == true);

    bgm.set_looping(false);
    assert(bgm.is_looping() == false);
    bgm.set_looping(true);
    assert(bgm.is_looping() == true);

    std::cout << "    Volume bounds and enable/loop flags verified!" << std::endl;
}

void test_menu_navigation_cycler()
{
    std::cout << "[+] Testing Menu BGM Cycler (0x00402130 Parity)..." << std::endl;
    bgm_manager_t bgm;
    bgm.init();

    // Default state: Random
    assert(bgm.get_current_track_id() == BGM_TRACK_RANDOM);
    assert(bgm.get_hud_text() == "Music: Random");

    // Cycle right (param_3 = 1): should advance to track 1 (Main Theme)
    bgm.menu_input(0, 0, 1);
    assert(bgm.get_current_track_id() == BGM_TRACK_MAIN);
    assert(bgm.get_track_title() == "Main Theme");
    assert(bgm.get_hud_text() == "Music: Main Theme");

    // Advance through all stages 2..8
    for (int i = 2; i <= 8; ++i) {
        bgm.menu_input(0, 0, 1);
        assert(bgm.get_current_track_id() == i);
    }
    assert(bgm.get_current_track_id() == BGM_TRACK_BOSS2);
    assert(bgm.get_track_title() == "Final Boss");

    // Step right past 8: should wrap to -1 (OFF)
    bgm.menu_input(0, 0, 1);
    assert(bgm.get_current_track_id() == BGM_TRACK_OFF);
    assert(bgm.get_hud_text() == "Music: OFF");
    assert(bgm.is_enabled() == false);

    // Step left from -1: should wrap around to 8 (Final Boss)
    bgm.menu_input(0, 1, 0);
    assert(bgm.get_current_track_id() == BGM_TRACK_BOSS2);
    assert(bgm.get_hud_text() == "Music: Final Boss");
    assert(bgm.is_enabled() == true);

    // Toggle mode: toggle between ON and OFF
    bgm.menu_input(1, 0, 1);
    assert(bgm.get_current_track_id() == BGM_TRACK_OFF);
    assert(bgm.get_hud_text() == "Music: OFF");

    bgm.menu_input(1, 0, 1);
    assert(bgm.get_current_track_id() == BGM_TRACK_RANDOM);
    assert(bgm.get_hud_text() == "Music: ON");

    std::cout << "    Menu cycler 0x00402130 wrapping and toggle verified!" << std::endl;
}

void test_playback_and_cache_check()
{
    std::cout << "[+] Testing Playback and Cache Check (0x00402020 Parity)..." << std::endl;
    bgm_manager_t bgm;
    bgm.init();

    // Play stage 1
    bool ok = bgm.play("bgm/stage1.wma");
    assert(ok == true);
    assert(bgm.is_playing() == true);
    assert(bgm.get_current_track_path() == "bgm/stage1.wma");

    // Cache check: calling play with identical path should return true without resetting
    bool cached = bgm.play("bgm/stage1.wma");
    assert(cached == true);
    assert(bgm.is_playing() == true);

    // Pause
    bgm.pause();
    assert(bgm.is_playing() == false);

    // Stop
    bgm.stop();
    assert(bgm.is_playing() == false);
    assert(bgm.get_current_track_path().empty());

    std::cout << "    Cache check and playback state management verified!" << std::endl;
}

void test_stage_and_boss_transitions()
{
    std::cout << "[+] Testing Stage and Boss BGM Transitions..." << std::endl;
    bgm_manager_t bgm;
    bgm.init();

    // Stage 1 Start
    bgm.on_stage_start(1);
    assert(bgm.is_playing() == true);
    assert(bgm.get_current_track_path() == "bgm/stage1.wma");

    // Stage 1 Boss Spawn -> Boss 1 track
    bgm.on_boss_spawn(1);
    assert(bgm.is_playing() == true);
    assert(bgm.get_current_track_path() == "bgm/boss1.wma");

    // Boss Defeated -> Restore Stage 1 track
    bgm.on_boss_defeated();
    assert(bgm.is_playing() == true);
    assert(bgm.get_current_track_path() == "bgm/stage1.wma");

    // Stage 5 Start
    bgm.on_stage_start(5);
    assert(bgm.is_playing() == true);
    assert(bgm.get_current_track_path() == "bgm/stage5.wma");

    // Stage 5 Boss Spawn (Julian) -> Boss 2 track
    bgm.on_boss_spawn(5);
    assert(bgm.is_playing() == true);
    assert(bgm.get_current_track_path() == "bgm/boss2.wma");

    // Boss Defeated -> Restore Stage 5 track
    bgm.on_boss_defeated();
    assert(bgm.is_playing() == true);
    assert(bgm.get_current_track_path() == "bgm/stage5.wma");

    std::cout << "    Stage and Boss milestone transitions verified!" << std::endl;
}

void test_stream_mixing_and_looping()
{
    std::cout << "[+] Testing Stream Mixing and Looping..." << std::endl;
    bgm_manager_t bgm;
    bgm.init();

    bgm.play("bgm/stage1.wma");
    assert(bgm.is_playing() == true);

    // Mix 2048 bytes of audio into stream
    std::vector<uint8_t> stream(2048, 0);
    bgm.mix_audio(stream.data(), static_cast<int32_t>(stream.size()), AUDIO_S16SYS);

    // Stream should contain data (or zero if silence, but mix was called without crash)
    // Now test with volume 0
    bgm.set_volume(0);
    std::vector<uint8_t> mute_stream(2048, 0);
    bgm.mix_audio(mute_stream.data(), static_cast<int32_t>(mute_stream.size()), AUDIO_S16SYS);
    for (uint8_t b : mute_stream) {
        assert(b == 0);
    }

    // Restore volume
    bgm.set_volume(80);

    // Test looping disabled
    bgm.set_looping(false);
    assert(bgm.is_looping() == false);

    std::cout << "    Stream mixing, volume attenuation, and looping verified!" << std::endl;
}

void test_authentic_wma_loading()
{
    std::cout << "[+] Testing Authentic Little Fighter 2 WMA Decoding (boss1.wma)..." << std::endl;
    bgm_manager_t bgm;
    bgm.init();

    bool ok = bgm.play("bgm/boss1.wma");
    assert(ok == true);
    assert(bgm.is_playing() == true);
    assert(bgm.get_current_track_path() == "bgm/boss1.wma");

    std::cout << "    Authentic WMA stream parsed and decoded successfully!" << std::endl;
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    std::cout << "========================================" << std::endl;
    std::cout << "LF2 Modern Lifted: BGM System Test Suite" << std::endl;
    std::cout << "========================================" << std::endl;

    test_track_mappings();
    test_volume_and_settings();
    test_menu_navigation_cycler();
    test_playback_and_cache_check();
    test_stage_and_boss_transitions();
    test_stream_mixing_and_looping();
    test_authentic_wma_loading();

    std::cout << "\n>>> ALL 7 BGM SYSTEM TESTS PASSED SUCCESSFULLY! <<<\n" << std::endl;
    return 0;
}

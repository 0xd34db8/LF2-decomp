#include <iostream>
#include <cassert>
#include <cstring>
#include <filesystem>
#include "app/options.h"
#include "app/app.h"

using namespace lf2;

static int g_tests_passed = 0;

#define TEST_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "FAILED: " << msg << " (" << #cond << ") at line " << __LINE__ << std::endl; \
            std::exit(1); \
        } \
    } while(0)

void test_key_name_and_width() {
    std::cout << "[TEST] Running Test 1: get_key_name & get_key_name_width_adj parity (0x00422B00)..." << std::endl;

    // Special keys
    TEST_ASSERT(get_key_name(0x20) == "Space", "Space key name");
    TEST_ASSERT(get_key_name_width_adj(0x20) == 10, "Space key width adj");

    TEST_ASSERT(get_key_name(0x0D) == "Enter", "Enter key name");
    TEST_ASSERT(get_key_name_width_adj(0x0D) == 10, "Enter key width adj");

    // Letters
    TEST_ASSERT(get_key_name('A') == "A", "Key A name");
    TEST_ASSERT(get_key_name_width_adj('A') == 0, "Key A width adj");
    TEST_ASSERT(get_key_name('W') == "W", "Key W name");
    TEST_ASSERT(get_key_name('Z') == "Z", "Key Z name");

    // Keypad numbers
    TEST_ASSERT(get_key_name(0x60) == "Keypad: 0", "Keypad 0 name");
    TEST_ASSERT(get_key_name_width_adj(0x60) == 15, "Keypad 0 width adj");
    TEST_ASSERT(get_key_name(0x68) == "Keypad: 8", "Keypad 8 name");
    TEST_ASSERT(get_key_name_width_adj(0x68) == 15, "Keypad 8 width adj");

    // Keypad symbols
    TEST_ASSERT(get_key_name(0x6B) == "Keypad: +", "Keypad + name");
    TEST_ASSERT(get_key_name_width_adj(0x6B) == 15, "Keypad + width adj");
    TEST_ASSERT(get_key_name(0x6D) == "Keypad: -", "Keypad - name");
    TEST_ASSERT(get_key_name(0x6A) == "Keypad: *", "Keypad * name");
    TEST_ASSERT(get_key_name(0x6F) == "Keypad: /", "Keypad / name");
    TEST_ASSERT(get_key_name(0x6E) == "Keypad: .", "Keypad . name");

    // Digits
    TEST_ASSERT(get_key_name('0') == "0", "Digit 0 name");
    TEST_ASSERT(get_key_name('9') == "9", "Digit 9 name");

    // Punctuation and OEM keys
    TEST_ASSERT(get_key_name(0xBD) == "-", "Minus key name");
    TEST_ASSERT(get_key_name(0xBB) == "=", "Equals key name");
    TEST_ASSERT(get_key_name(0xDB) == "[", "Left bracket key name");
    TEST_ASSERT(get_key_name(0xDD) == "]", "Right bracket key name");
    TEST_ASSERT(get_key_name(0xBA) == ";", "Semicolon key name");
    TEST_ASSERT(get_key_name(0xDE) == "'", "Quote key name");
    TEST_ASSERT(get_key_name(0xDC) == "\\", "Backslash key name");
    TEST_ASSERT(get_key_name(0xBC) == ",", "Comma key name");
    TEST_ASSERT(get_key_name(0xBE) == ".", "Period key name");
    TEST_ASSERT(get_key_name(0xBF) == "/", "Slash key name");
    TEST_ASSERT(get_key_name(0xC0) == "`", "Backtick key name");

    // Modifiers & Navigation
    TEST_ASSERT(get_key_name(0x11) == "Ctrl", "Ctrl key name");
    TEST_ASSERT(get_key_name_width_adj(0x11) == 7, "Ctrl width adj");
    TEST_ASSERT(get_key_name(0x10) == "Shift", "Shift key name");
    TEST_ASSERT(get_key_name_width_adj(0x10) == 7, "Shift width adj");
    TEST_ASSERT(get_key_name(0x09) == "Tab", "Tab key name");
    TEST_ASSERT(get_key_name_width_adj(0x09) == 5, "Tab width adj");
    TEST_ASSERT(get_key_name(0x08) == "Backspace", "Backspace key name");
    TEST_ASSERT(get_key_name_width_adj(0x08) == 13, "Backspace width adj");
    TEST_ASSERT(get_key_name(0x14) == "CapsLock", "CapsLock key name");
    TEST_ASSERT(get_key_name_width_adj(0x14) == 16, "CapsLock width adj");
    TEST_ASSERT(get_key_name(0x26) == "Up", "Up key name");
    TEST_ASSERT(get_key_name_width_adj(0x26) == 2, "Up width adj");
    TEST_ASSERT(get_key_name(0x28) == "Down", "Down key name");
    TEST_ASSERT(get_key_name_width_adj(0x28) == 5, "Down width adj");
    TEST_ASSERT(get_key_name(0x25) == "Left", "Left key name");
    TEST_ASSERT(get_key_name_width_adj(0x25) == 4, "Left width adj");
    TEST_ASSERT(get_key_name(0x27) == "Right", "Right key name");
    TEST_ASSERT(get_key_name_width_adj(0x27) == 6, "Right width adj");

    // Gamepad synthetic buttons
    TEST_ASSERT(get_key_name(1000) == "Btn 1", "Gamepad button 1 name");
    TEST_ASSERT(get_key_name(1005) == "Btn 6", "Gamepad button 6 name");
    TEST_ASSERT(get_key_name(1015) == "Btn 16", "Gamepad button 16 name");

    // Unknown key
    TEST_ASSERT(get_key_name(0) == "none", "Unknown key name");

    g_tests_passed++;
    std::cout << "  -> PASSED" << std::endl;
}

void test_vk_to_ascii() {
    std::cout << "[TEST] Running Test 2: vk_to_ascii evaluation (0x00422F60)..." << std::endl;

    // Letters without shift or caps -> lowercase
    TEST_ASSERT(vk_to_ascii('A', false, false) == 'a', "vk_to_ascii 'A' lower");
    TEST_ASSERT(vk_to_ascii('Z', false, false) == 'z', "vk_to_ascii 'Z' lower");

    // Letters with shift -> UPPERCASE
    TEST_ASSERT(vk_to_ascii('A', true, false) == 'A', "vk_to_ascii 'A' Shift UPPER");
    TEST_ASSERT(vk_to_ascii('Z', true, false) == 'Z', "vk_to_ascii 'Z' Shift UPPER");

    // Letters with caps -> UPPERCASE
    TEST_ASSERT(vk_to_ascii('A', false, true) == 'A', "vk_to_ascii 'A' Caps UPPER");

    // Letters with shift and caps -> lowercase
    TEST_ASSERT(vk_to_ascii('A', true, true) == 'a', "vk_to_ascii 'A' Shift+Caps lower");

    // Numbers without shift
    TEST_ASSERT(vk_to_ascii('0', false, false) == '0', "vk_to_ascii '0'");
    TEST_ASSERT(vk_to_ascii('1', false, false) == '1', "vk_to_ascii '1'");
    TEST_ASSERT(vk_to_ascii('9', false, false) == '9', "vk_to_ascii '9'");

    // Numbers with shift
    TEST_ASSERT(vk_to_ascii('1', true, false) == '!', "vk_to_ascii '1' Shift");
    TEST_ASSERT(vk_to_ascii('2', true, false) == '@', "vk_to_ascii '2' Shift");
    TEST_ASSERT(vk_to_ascii('3', true, false) == '#', "vk_to_ascii '3' Shift");
    TEST_ASSERT(vk_to_ascii('4', true, false) == '$', "vk_to_ascii '4' Shift");
    TEST_ASSERT(vk_to_ascii('5', true, false) == '%', "vk_to_ascii '5' Shift");
    TEST_ASSERT(vk_to_ascii('6', true, false) == '^', "vk_to_ascii '6' Shift");
    TEST_ASSERT(vk_to_ascii('7', true, false) == '&', "vk_to_ascii '7' Shift");
    TEST_ASSERT(vk_to_ascii('8', true, false) == '*', "vk_to_ascii '8' Shift");
    TEST_ASSERT(vk_to_ascii('9', true, false) == '(', "vk_to_ascii '9' Shift");
    TEST_ASSERT(vk_to_ascii('0', true, false) == ')', "vk_to_ascii '0' Shift");

    // Space
    TEST_ASSERT(vk_to_ascii(0x20, false, false) == ' ', "vk_to_ascii Space");
    TEST_ASSERT(vk_to_ascii(0x20, true, false) == ' ', "vk_to_ascii Space Shift");

    // Keypad numbers 0..9 (0x60..0x69)
    for (int k = 0; k <= 9; ++k) {
        TEST_ASSERT(vk_to_ascii(0x60 + k, false, false) == ('0' + k), "vk_to_ascii Keypad digit");
        TEST_ASSERT(vk_to_ascii(0x60 + k, true, false) == ('0' + k), "vk_to_ascii Keypad digit with shift");
    }

    // Punctuation keys
    TEST_ASSERT(vk_to_ascii(0xBD, false, false) == '-', "vk_to_ascii minus");
    TEST_ASSERT(vk_to_ascii(0xBD, true, false) == '_', "vk_to_ascii minus shifted");
    TEST_ASSERT(vk_to_ascii(0xBB, false, false) == '=', "vk_to_ascii equals");
    TEST_ASSERT(vk_to_ascii(0xBB, true, false) == '+', "vk_to_ascii equals shifted");
    TEST_ASSERT(vk_to_ascii(0xBC, false, false) == ',', "vk_to_ascii comma");
    TEST_ASSERT(vk_to_ascii(0xBC, true, false) == '<', "vk_to_ascii comma shifted");
    TEST_ASSERT(vk_to_ascii(0xBE, false, false) == '.', "vk_to_ascii period");
    TEST_ASSERT(vk_to_ascii(0xBE, true, false) == '>', "vk_to_ascii period shifted");
    TEST_ASSERT(vk_to_ascii(0xBF, false, false) == '/', "vk_to_ascii slash");
    TEST_ASSERT(vk_to_ascii(0xBF, true, false) == '?', "vk_to_ascii slash shifted");
    TEST_ASSERT(vk_to_ascii(0xC0, false, false) == '`', "vk_to_ascii backtick");
    TEST_ASSERT(vk_to_ascii(0xC0, true, false) == '~', "vk_to_ascii tilde shifted");

    g_tests_passed++;
    std::cout << "  -> PASSED" << std::endl;
}

void test_control_file_roundtrip() {
    std::cout << "[TEST] Running Test 3: control.txt round-trip save and load (0x00423230)..." << std::endl;

    std::filesystem::create_directories("build");
    const std::string test_file = "build/test_control_roundtrip.txt";

    options_ui_t ui;
    ui.reset_to_defaults();

    // Customize controls
    auto& cfg = ui.get_config();
    cfg.players[0].keys[1] = 0x57; // 'W' Up
    cfg.players[0].keys[2] = 0x53; // 'S' Down
    cfg.players[0].keys[3] = 0x41; // 'A' Left
    cfg.players[0].keys[4] = 0x44; // 'D' Right
    cfg.players[0].keys[5] = 0x4A; // 'J' Attack
    cfg.players[0].keys[6] = 0x4B; // 'K' Jump
    cfg.players[0].keys[7] = 0x4C; // 'L' Defend

    // Set player names with spaces (must encode to '`')
    std::strcpy(cfg.players[0].name, "Hero Davis");
    std::strcpy(cfg.players[1].name, "Woody 2");
    std::strcpy(cfg.players[2].name, "Dennis");
    std::strcpy(cfg.players[3].name, "Freeze Ice");

    cfg.demo_mode = 0;
    cfg.replay_mode = 1;

    ui.set_profile_name("Marti Wong");
    ui.set_profile_email("marti@lf2.net");
    ui.set_profile_info("Creator of LF2");

    bool saved = ui.save_controls(test_file);
    TEST_ASSERT(saved, "save_controls succeeded");

    // Load into a fresh controller
    options_ui_t loaded_ui;
    bool loaded = loaded_ui.reload_controls(test_file);
    TEST_ASSERT(loaded, "reload_controls succeeded");

    const auto& lcfg = loaded_ui.get_config();
    TEST_ASSERT(lcfg.players[0].keys[1] == 0x57, "Loaded P1 Up key");
    TEST_ASSERT(lcfg.players[0].keys[2] == 0x53, "Loaded P1 Down key");
    TEST_ASSERT(lcfg.players[0].keys[5] == 0x4A, "Loaded P1 Attack key");
    TEST_ASSERT(lcfg.players[0].keys[6] == 0x4B, "Loaded P1 Jump key");
    TEST_ASSERT(lcfg.players[0].keys[7] == 0x4C, "Loaded P1 Defend key");

    // Check name decoding: '`' turned back into ' '
    TEST_ASSERT(std::string(lcfg.players[0].name) == "Hero Davis", "Loaded P1 name decoded");
    TEST_ASSERT(std::string(lcfg.players[1].name) == "Woody 2", "Loaded P2 name decoded");
    TEST_ASSERT(std::string(lcfg.players[2].name) == "Dennis", "Loaded P3 name decoded");
    TEST_ASSERT(std::string(lcfg.players[3].name) == "Freeze Ice", "Loaded P4 name decoded");

    TEST_ASSERT(lcfg.demo_mode == 0, "Loaded demo mode");
    TEST_ASSERT(lcfg.replay_mode == 1, "Loaded replay mode");
    TEST_ASSERT(loaded_ui.is_auto_record_enabled() == true, "Loaded auto-record query");

    TEST_ASSERT(loaded_ui.get_profile_name() == "Marti Wong", "Loaded profile name");
    TEST_ASSERT(loaded_ui.get_profile_email() == "marti@lf2.net", "Loaded profile email");
    TEST_ASSERT(loaded_ui.get_profile_info() == "Creator of LF2", "Loaded profile info");

    std::filesystem::remove(test_file);

    g_tests_passed++;
    std::cout << "  -> PASSED" << std::endl;
}

void test_interactive_rebind_state_machine() {
    std::cout << "[TEST] Running Test 4: Interactive key rebinding state machine..." << std::endl;

    options_ui_t ui;
    ui.reset_to_defaults();

    TEST_ASSERT(!ui.is_rebinding(), "Initial rebinding state false");

    // Start rebinding Player 1 (index 0) Attack key (action 5)
    ui.start_rebind(0, 5);
    TEST_ASSERT(ui.is_rebinding(), "is_rebinding is true");
    TEST_ASSERT(ui.get_rebinding_player() == 0, "Rebinding player is 0");
    TEST_ASSERT(ui.get_rebinding_action() == 5, "Rebinding action is 5");

    // Apply key: VK 'Z' (0x5A)
    ui.apply_rebind(0x5A);
    TEST_ASSERT(!ui.is_rebinding(), "is_rebinding false after apply");
    TEST_ASSERT(ui.get_config().players[0].keys[5] == 0x5A, "Key updated to 0x5A ('Z')");

    // Test cancel rebinding
    ui.start_rebind(1, 6);
    TEST_ASSERT(ui.is_rebinding(), "is_rebinding true");
    ui.cancel_rebind();
    TEST_ASSERT(!ui.is_rebinding(), "is_rebinding false after cancel");

    // Test rebinding via SDL_Event (handle_event)
    ui.start_rebind(2, 7); // Player 3 Defend
    SDL_Event key_ev;
    std::memset(&key_ev, 0, sizeof(key_ev));
    key_ev.type = SDL_KEYDOWN;
    key_ev.key.keysym.sym = SDLK_x;

    bool handled = ui.handle_event(key_ev, nullptr);
    TEST_ASSERT(handled, "handle_event handled rebind key");
    TEST_ASSERT(!ui.is_rebinding(), "Rebinding finished after event");
    TEST_ASSERT(ui.get_config().players[2].keys[7] == 0x58, "P3 Defend updated to 'X' (0x58)");

    // Test rebinding with Escape key cancels rebinding
    ui.start_rebind(3, 1);
    key_ev.key.keysym.sym = SDLK_ESCAPE;
    handled = ui.handle_event(key_ev, nullptr);
    TEST_ASSERT(handled, "handle_event handled ESC cancel");
    TEST_ASSERT(!ui.is_rebinding(), "Rebinding cancelled via ESC");

    g_tests_passed++;
    std::cout << "  -> PASSED" << std::endl;
}

void test_player_name_editing() {
    std::cout << "[TEST] Running Test 5: Player name typing & backspace editing..." << std::endl;

    options_ui_t ui;
    ui.reset_to_defaults();

    TEST_ASSERT(!ui.is_editing_name(), "Initially not editing name");

    ui.start_editing_name(0);
    TEST_ASSERT(ui.is_editing_name(), "is_editing_name is true");
    TEST_ASSERT(ui.get_editing_player() == 0, "Editing player 0");

    // Simulate typing: Backspace removes '1'
    SDL_Event ev;
    std::memset(&ev, 0, sizeof(ev));
    ev.type = SDL_KEYDOWN;
    ev.key.keysym.sym = SDLK_BACKSPACE;
    ui.handle_event(ev, nullptr);
    TEST_ASSERT(std::string(ui.get_config().players[0].name) == "", "Name empty after backspace");

    // Type 'A' -> 'a'
    ev.key.keysym.sym = SDLK_a;
    ui.handle_event(ev, nullptr);
    TEST_ASSERT(std::string(ui.get_config().players[0].name) == "a", "Typed 'a'");

    // Type 'B' with Shift -> 'B'
    ev.key.keysym.sym = SDLK_b;
    ev.key.keysym.mod = KMOD_SHIFT;
    ui.handle_event(ev, nullptr);
    TEST_ASSERT(std::string(ui.get_config().players[0].name) == "aB", "Typed 'B' with Shift");

    // Commit with Return
    ev.key.keysym.sym = SDLK_RETURN;
    ev.key.keysym.mod = 0;
    ui.handle_event(ev, nullptr);
    TEST_ASSERT(!ui.is_editing_name(), "Editing name finished after Return");
    TEST_ASSERT(std::string(ui.get_config().players[0].name) == "aB", "Final committed name is 'aB'");

    g_tests_passed++;
    std::cout << "  -> PASSED" << std::endl;
}

void test_substates_and_options_flags() {
    std::cout << "[TEST] Running Test 6: Substates & Options Flags (Auto-Record, Fullscreen, Defaults)..." << std::endl;

    options_ui_t ui;
    ui.reset_to_defaults();

    // Default substate is CONTROL_SETTINGS
    TEST_ASSERT(ui.get_substate() == options_substate_t::CONTROL_SETTINGS, "Default substate");

    // Switch substate to PROFILE_SETTINGS
    ui.set_substate(options_substate_t::PROFILE_SETTINGS);
    TEST_ASSERT(ui.get_substate() == options_substate_t::PROFILE_SETTINGS, "Switched to PROFILE_SETTINGS");

    // Toggle auto record replay flag
    ui.set_auto_record(true);
    TEST_ASSERT(ui.is_auto_record_enabled() == true, "Auto-record enabled");
    TEST_ASSERT(ui.get_config().replay_mode == 1, "Config replay_mode is 1");

    ui.set_auto_record(false);
    TEST_ASSERT(ui.is_auto_record_enabled() == false, "Auto-record disabled");
    TEST_ASSERT(ui.get_config().replay_mode == 0, "Config replay_mode is 0");

    // Test mouse click toggle on auto record button (380, 440, 150, 32)
    ui.set_substate(options_substate_t::CONTROL_SETTINGS);
    SDL_Event click_ev;
    std::memset(&click_ev, 0, sizeof(click_ev));
    click_ev.type = SDL_MOUSEBUTTONDOWN;
    click_ev.button.button = SDL_BUTTON_LEFT;
    click_ev.button.x = 400;
    click_ev.button.y = 450;
    ui.handle_event(click_ev, nullptr);
    TEST_ASSERT(ui.is_auto_record_enabled() == true, "Auto record toggled via mouse click");

    // Test mouse click on Defaults button (70, 440, 110, 32)
    click_ev.button.x = 100;
    click_ev.button.y = 450;
    ui.handle_event(click_ev, nullptr);
    TEST_ASSERT(ui.get_config().players[0].keys[1] == 104, "P1 Up key reset to authentic Numpad 8");
    TEST_ASSERT(ui.get_config().players[1].keys[1] == 87, "P2 Up key reset to authentic 'W'");

    g_tests_passed++;
    std::cout << "  -> PASSED" << std::endl;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    std::cout << "===========================================================" << std::endl;
    std::cout << " Little Fighter 2 - Phase 17 Lifted Options & Control Tests" << std::endl;
    std::cout << "===========================================================" << std::endl;

    test_key_name_and_width();
    test_vk_to_ascii();
    test_control_file_roundtrip();
    test_interactive_rebind_state_machine();
    test_player_name_editing();
    test_substates_and_options_flags();

    std::cout << "===========================================================" << std::endl;
    std::cout << " ALL " << g_tests_passed << " OPTION & CONTROL TESTS PASSED SUCCESSFULLY!" << std::endl;
    std::cout << "===========================================================" << std::endl;

    return 0;
}

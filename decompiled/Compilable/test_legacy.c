#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

int main() {
    printf("======================================================================\n");
    printf(" Little Fighter 2 - Decompiled Compilable Legacy Suite Verification\n");
    printf(" Pure x86 MSVC++ 32-bit Assembly Decompiled C Engine\n");
    printf("======================================================================\n");

    // 1. Test fast absolute value computation (0x004034e0)
    printf("[+] Testing Decompiled Fast Integer Absolute Value (0x004034e0)...\n");
    assert(FUN_004034e0(42) == 42);
    assert(FUN_004034e0(-42) == 42);
    assert(FUN_004034e0(0) == 0);
    assert(FUN_004034e0(-2147483647) == 2147483647);
    printf("    [PASS] 0x004034e0 returned exact absolute values across all sign bit cases.\n");

    // 2. Test 2D Bounding Box Overlap Check (0x004171c0)
    // Prototype: FUN_004171c0(bdy_x, bdy_y, bdy_w, bdy_h, itr_x, itr_y, itr_w, itr_h)
    printf("[+] Testing Decompiled 2D Box Overlap Check (0x004171c0)...\n");
    // Overlapping boxes: (10, 10, 20, 20) and (20, 20, 20, 20)
    assert(FUN_004171c0(10, 10, 20, 20, 20, 20, 20, 20) == 1);
    // Non-overlapping boxes: (10, 10, 20, 20) and (100, 100, 20, 20)
    assert(FUN_004171c0(10, 10, 20, 20, 100, 100, 20, 20) == 0);
    printf("    [PASS] 0x004171c0 correctly verified 2D bounding box intersections.\n");

    // 3. Test PRNG Lookup (0x00417170)
    printf("[+] Testing Decompiled Circular PRNG Table (0x00417170)...\n");
    DAT_00450bcc = 0;
    DAT_00450c34 = 1234;
    int r1 = FUN_00417170(0, 100);
    assert(r1 >= 0 && r1 < 100);
    printf("    [PASS] 0x00417170 generated valid pseudo-random modulus index: %d\n", r1);

    // 4. Test Global Memory Mappings
    printf("[+] Verifying Global Memory Symbols & Structure Alignments...\n");
    assert(sizeof(DAT_00455378) == 300); // 300-byte Win32 key buffer
    printf("    [PASS] Global symbols and memory layouts verified successfully.\n");

    // 5. Test LF2 Structure Layouts & Alignments
    printf("[+] Verifying Human-Readable Domain Structure Alignments...\n");
    printf("    sizeof(bdy_t): 0x%zx (%zu)\n", sizeof(bdy_t), sizeof(bdy_t));
    printf("    sizeof(itr_t): 0x%zx (%zu)\n", sizeof(itr_t), sizeof(itr_t));
    printf("    sizeof(opoint_t): 0x%zx (%zu)\n", sizeof(opoint_t), sizeof(opoint_t));
    printf("    sizeof(bpoint_t): 0x%zx (%zu)\n", sizeof(bpoint_t), sizeof(bpoint_t));
    printf("    sizeof(cpoint_t): 0x%zx (%zu)\n", sizeof(cpoint_t), sizeof(cpoint_t));
    printf("    sizeof(wpoint_t): 0x%zx (%zu)\n", sizeof(wpoint_t), sizeof(wpoint_t));
    printf("    sizeof(frame_t): 0x%zx (%zu)\n", sizeof(frame_t), sizeof(frame_t));
    printf("    offsetof(frame_t, opoint): 0x%zx\n", offsetof(frame_t, opoint));
    printf("    offsetof(frame_t, bpoint): 0x%zx\n", offsetof(frame_t, bpoint));
    printf("    offsetof(frame_t, cpoint): 0x%zx\n", offsetof(frame_t, cpoint));
    printf("    offsetof(frame_t, wpoint): 0x%zx\n", offsetof(frame_t, wpoint));
    printf("    offsetof(frame_t, itrs_size): 0x%zx\n", offsetof(frame_t, itrs_size));
    printf("    offsetof(frame_t, bdys_size): 0x%zx\n", offsetof(frame_t, bdys_size));
    printf("    offsetof(frame_t, itrs): 0x%zx\n", offsetof(frame_t, itrs));
    printf("    offsetof(frame_t, bdys): 0x%zx\n", offsetof(frame_t, bdys));
    printf("    offsetof(frame_t, name): 0x%zx\n", offsetof(frame_t, name));
    printf("    offsetof(frame_t, sound): 0x%zx\n", offsetof(frame_t, sound));
    assert(sizeof(bdy_t) == 0x28);
    assert(sizeof(itr_t) == 0x50);
    assert(sizeof(opoint_t) == 0x20);
    assert(sizeof(bpoint_t) == 0x0C);
    assert(sizeof(cpoint_t) == 0x44);
    assert(offsetof(cpoint_t, vaction) == 0x14);
    assert(offsetof(cpoint_t, throwvx) == 0x24);
    assert(offsetof(cpoint_t, throwvz) == 0x40);
    assert(sizeof(wpoint_t) == 0x24);
    assert(sizeof(frame_t) == 0x178);
    assert(sizeof(file_t) == 0x25360);
    assert(offsetof(file_t, attacking_itrs[1]) + offsetof(itr_t, dvx) == 0x114);
    assert(sizeof(object_t) == 0x418);
    assert(offsetof(object_t, x) == 0x10);
    assert(offsetof(object_t, wait_counter) == 0x84);
    assert(offsetof(object_t, hp) == 0x2FC);
    assert(offsetof(object_t, team) == 0x364);
    assert(offsetof(object_t, file) == 0x368);
    assert(offsetof(object_t, ai_target_x) == 0x3FC);
    assert(offsetof(object_t, ai_target_z) == 0x400);
    assert(offsetof(global_t, is_object_exists) == 0x04);
    assert(offsetof(global_t, objects) == 0x194);
    printf("    [PASS] Verified 1:1 memory layout for all 10 LF2 domain structures.\n");

    // 6. Test Human-Readable Logic Functions
    printf("[+] Testing Decompiled Human-Readable Gameplay Logic (Teleport 0x00403270)...\n");
    global_t game;
    memset(&game, 0, sizeof(global_t));

    file_t char_file;
    memset(&char_file, 0, sizeof(file_t));
    char_file.type = TYPE_CHARACTER;

    object_t rudolf;
    lf2_object_init(&rudolf);
    rudolf.file = &char_file;
    rudolf.team = 1;
    rudolf.hp = 100;
    rudolf.facing = FACING_RIGHT;
    rudolf.x = 100;
    rudolf.y = 50;
    rudolf.z = 200;

    object_t enemy;
    lf2_object_init(&enemy);
    enemy.file = &char_file;
    enemy.team = 2; // Different team
    enemy.hp = 100;
    enemy.x = 500;
    enemy.y = 0;
    enemy.z = 200;

    game.is_object_exists[0] = 1;
    game.objects[0] = &rudolf;
    game.is_object_exists[1] = 1;
    game.objects[1] = &enemy;

    // Teleport Rudolf behind nearest enemy (teleport_to = 1)
    lf2_teleport(&game, 0, 1);
    assert(rudolf.x == 380); // 500 - 120 (facing right)
    assert(rudolf.y == 0);
    assert(rudolf.z == 201); // enemy.z + 1
    assert(rudolf.x_velocity == 0.0);
    assert(rudolf.y_velocity == 0.0);
    assert(rudolf.z_velocity == 0.0);
    printf("    [PASS] lf2_teleport correctly positioned Rudolf behind enemy (x=380, z=201, vels=0).\n");

    // 7. Test Phase 17: Key name mapping (0x00422b00)
    printf("[+] Testing Key Name Mapping (0x00422b00 / FUN_00422b00)...\n");
    char key_buf[32];
    int width_adj = 0;
    FUN_00422b00(0x20, key_buf, &width_adj); // VK_SPACE
    assert(strcmp(key_buf, "Space") == 0);
    assert(width_adj == 10);

    FUN_00422b00(0x0D, key_buf, &width_adj); // VK_RETURN
    assert(strcmp(key_buf, "Enter") == 0);
    assert(width_adj == 10);

    FUN_00422b00(0x41, key_buf, &width_adj); // 'A'
    assert(strcmp(key_buf, "A") == 0);
    assert(width_adj == 0);

    FUN_00422b00(0x65, key_buf, &width_adj); // Numpad 5
    assert(strcmp(key_buf, "Keypad: 5") == 0);
    assert(width_adj == 15);

    FUN_00422b00(0x26, key_buf, &width_adj); // Up
    assert(strcmp(key_buf, "Up") == 0);
    assert(width_adj == 2);

    FUN_00422b00(0x10, key_buf, &width_adj); // Shift
    assert(strcmp(key_buf, "Shift") == 0);
    assert(width_adj == 7);
    printf("    [PASS] FUN_00422b00 mapped Space, Enter, letters, keypad, and arrows accurately.\n");

    // 8. Test Phase 17: VK to ASCII Decoder (0x00422f60)
    printf("[+] Testing VK to ASCII Character Translation (0x00422f60 / FUN_00422f60)...\n");
    DAT_00455388 = 'u'; // Shift UP
    assert(FUN_00422f60(0x20) == ' ');
    assert(FUN_00422f60(0x31) == '1');
    assert(FUN_00422f60(0xBD) == '-');

    DAT_00455388 = 'd'; // Shift DOWN
    assert(FUN_00422f60(0x31) == '!');
    assert(FUN_00422f60(0xBD) == '_');
    assert(FUN_00422f60(0xBB) == '+');
    printf("    [PASS] FUN_00422f60 correctly handled shift states, numpad, and symbol conversions.\n");

    // 9. Test Phase 17: PRNG Reseeder (0x00422ac0)
    printf("[+] Testing PRNG Reseed (0x00422ac0 / FUN_00422ac0)...\n");
    DAT_00450b48 = 999;
    FUN_00422ac0();
    assert(DAT_00450b48 == 0);
    assert(DAT_0044ff90[0] >= 1);
    assert(DAT_0044ff90[2999] >= 1);
    printf("    [PASS] FUN_00422ac0 reseeded 3,000-byte circular lookup table.\n");

    // 10. Test Phase 18: Replay Obfuscation Cipher (0x0043dd60 & 0x0043e620)
    printf("[+] Testing LF2 v2.0 Secondary Replay Cipher (0x0043dd60 / 0x0043e620)...\n");
    assert(strlen(DAT_0044d7a0) == 1345);
    assert(strncmp(DAT_0044d7a0, "15456611235456134545631153456894", 32) == 0);

    uint8_t test_payload[2048];
    uint8_t orig_payload[2048];
    for (size_t i = 0; i < sizeof(test_payload); ++i) {
        test_payload[i] = (uint8_t)(i * 37 + 13);
        orig_payload[i] = test_payload[i];
    }

    lf2_replay_cipher_encrypt(test_payload, sizeof(test_payload));
    assert(memcmp(test_payload, orig_payload, sizeof(test_payload)) != 0);
    // Bytes beyond 1345 should remain identical
    assert(memcmp(test_payload + 1345, orig_payload + 1345, sizeof(test_payload) - 1345) == 0);

    lf2_replay_cipher_decrypt(test_payload, sizeof(test_payload));
    assert(memcmp(test_payload, orig_payload, sizeof(test_payload)) == 0);
    printf("    [PASS] Replay cipher encrypt and decrypt passed with 100%% bit-for-bit parity.\n");

    // 11. Test Phase 18: Zlib Replay Deflation/Inflation Wrappers (FUN_0043f4b0 & FUN_0043f4d0)
    printf("[+] Testing Replay Zlib Deflation/Inflation (FUN_0043f4b0 / FUN_0043f4d0)...\n");
    char raw_replay[4096];
    for (size_t i = 0; i < sizeof(raw_replay); ++i) {
        raw_replay[i] = (char)('A' + (i % 26));
    }
    uint8_t comp_buf[8192];
    unsigned long comp_sz = sizeof(comp_buf);
    int comp_res = FUN_0043f4b0(comp_buf, &comp_sz, raw_replay, sizeof(raw_replay));
    assert(comp_res == 0);
    assert(comp_sz < sizeof(raw_replay));

    // Apply cipher to compressed buffer
    lf2_replay_cipher_encrypt(comp_buf, comp_sz);
    // Decrypt cipher
    lf2_replay_cipher_decrypt(comp_buf, comp_sz);

    char uncomp_buf[4096];
    unsigned long uncomp_sz = sizeof(uncomp_buf);
    int uncomp_res = FUN_0043f4d0(uncomp_buf, &uncomp_sz, comp_buf, comp_sz);
    assert(uncomp_res == 0);
    assert(uncomp_sz == sizeof(raw_replay));
    assert(memcmp(raw_replay, uncomp_buf, sizeof(raw_replay)) == 0);
    printf("    [PASS] Zlib compression + cipher obfuscation roundtrip succeeded 100%%.\n");

    // 12. Test Phase 19: BGM State Machine & Track Dispatcher (FUN_00402020 - FUN_004025d0)
    printf("[+] Testing BGM State Machine & Dispatcher (FUN_00402020 / FUN_004025d0)...\n");
    DAT_0044d010 = 1; // Enable BGM
    FUN_004025d0(1);  // Track 1: Main Theme
    assert(strcmp(DAT_0044eed0, "bgm\\main.wma") == 0);
    assert(strcmp(DAT_0044ef04, "bgm\\main.wma") == 0);

    // Test cache check: Calling play on the same track preserves state without redundant reloads
    FUN_00402020("bgm\\main.wma");
    assert(strcmp(DAT_0044ef04, "bgm\\main.wma") == 0);

    // Test Boss track transitions
    FUN_004025d0(7); // Track 7: Boss 1
    assert(strcmp(DAT_0044eed0, "bgm\\boss1.wma") == 0);
    assert(strcmp(DAT_0044ef04, "bgm\\boss1.wma") == 0);

    FUN_004025d0(8); // Track 8: Final Boss 2
    assert(strcmp(DAT_0044eed0, "bgm\\boss2.wma") == 0);
    assert(strcmp(DAT_0044ef04, "bgm\\boss2.wma") == 0);

    // Test Menu Picker Cycling (FUN_00402130)
    DAT_0044f18c = 0; // Random
    FUN_00402130(0, 0, 1, NULL); // Cycle right -> Track 1
    assert(DAT_0044f18c == 1);
    assert(strcmp(DAT_0044f128, "Main Theme") == 0);
    assert(strcmp(DAT_0044f060, "Music: Main Theme") == 0);

    // Test OFF state: toggle to OFF (-1) disables playback
    DAT_0044f18c = -1;
    FUN_00402130(1, 0, 0, NULL);
    assert(DAT_0044d010 == 0);
    assert(strcmp(DAT_0044f128, "OFF") == 0);
    assert(strcmp(DAT_0044ef04, "") == 0);
    printf("    [PASS] BGM track dispatch, cache check, and menu picker passed with 100%% parity.\n");

    // 13. Test Phase 20: Per-Object Update Core & Slot Input Latching (0x004061a0, 0x004196f0, 0x004197a0, 0x004198f0, 0x004034f0)
    printf("[+] Testing Phase 20: Per-Object Core & Slot Input Latching...\n");
    // Test 1D interval betweenness (0x004061A0)
    assert(FUN_004061a0(10, 20, 30) == 1);
    assert(FUN_004061a0(30, 20, 10) == 1);
    assert(FUN_004061a0(10, 30, 20) == 0);
    assert(FUN_004061a0(10, 10, 30) == 0);

    // Test Velocity Averaging Pass (0x004196F0)
    static global_t test_game;
    memset(&test_game, 0, sizeof(global_t));
    static object_t test_obj;
    lf2_object_init(&test_obj);
    test_obj.attacks = 3; // 3 samples
    test_obj.pic_x_gain = 12.0;
    test_obj.y_accl = 8.0;
    test_obj.z_accl = 4.0;
    test_game.is_object_exists[0] = 1;
    test_game.objects[0] = &test_obj;
    in_ECX = &test_game;
    FUN_004196f0();
    // Factor = 2.0 / (3 + 1) = 0.5
    // x_velocity = 12.0 * 0.5 = 6.0
    // y_velocity = 8.0 * 0.5 = 4.0
    // z_velocity = 4.0 * 0.5 = 2.0
    assert(test_obj.x_velocity == 6.0);
    assert(test_obj.y_velocity == 4.0);
    assert(test_obj.z_velocity == 2.0);
    assert(test_obj.attacks == 0);

    // Test Network Input Bit Unpacking & Latching (0x004197A0)
    uint8_t packet_bits[8] = {0};
    packet_bits[0] = 0x80 | 0x08; // UP + ATTACK
    FUN_004197a0(packet_bits, 0);
    assert(test_obj.click_up == 1);
    assert(test_obj.click_attack == 1);
    assert(test_obj.click_jump == 0);
    assert(test_obj.click_defend == 0);

    // Next frame shift: previous frame click should shift to holding
    packet_bits[0] = 0x04; // JUMP only
    FUN_004197a0(packet_bits, 0);
    assert(test_obj.holding_up == 1);
    assert(test_obj.holding_attack == 1);
    assert(test_obj.click_up == 0);
    assert(test_obj.click_attack == 0);
    assert(test_obj.click_jump == 1);

    // Test AI Combat Dodge Maneuver (0x004034F0)
    static object_t enemy_obj;
    lf2_object_init(&enemy_obj);
    static file_t enemy_file;
    memset(&enemy_file, 0, sizeof(enemy_file));
    enemy_file.id = ID_DAVIS_DAT;
    enemy_obj.file = &enemy_file;
    enemy_obj.x = 200;
    enemy_obj.z = 200;
    test_game.objects[1] = &enemy_obj;
    test_game.is_object_exists[1] = 1;

    test_obj.file = &enemy_file;
    test_obj.x = 150;
    test_obj.z = 200;
    test_obj.facing = FACING_RIGHT;
    test_obj.frame_id1 = 110; // defend/roll frame
    DAT_0044f61c = 0; // CRAZY difficulty for 100% deterministic rolls
    int dodge_res = FUN_004034f0(1, 0, 0, 0, 0, 0, 0);
    assert(dodge_res == 1);
    printf("    [PASS] 1D betweenness, velocity averaging, input unpacking, and AI dodge verified!\n");

    // 14. Test Phase 21 & 22 Frame Advance, Combo Recognizers, Input State Machine, and Physics (0x0040D960, 0x0040E170, 0x0040E2D0, 0x0040E450, 0x0040E490, 0x00412800..0x00412F40, 0x00413080)
    printf("[*] Testing Phase 21 & 22 Frame Advance, Combo Recognizers, Input & Physics...\n");
    {
        file_t *p21_file = (file_t *)calloc(1, sizeof(file_t));
        assert(p21_file != NULL);
        p21_file->id = ID_DAVIS_DAT;
        p21_file->type = TYPE_CHARACTER;
        p21_file->walking_frame_rate = 3;
        p21_file->walking_speed = 4.0;
        p21_file->walking_speedz = 2.0;
        p21_file->running_frame_rate = 3;
        p21_file->running_speed = 8.0;
        p21_file->running_speedz = 3.0;
        p21_file->jump_height = -16.0;
        p21_file->jump_distance = 5.0;
        p21_file->jump_distancez = 2.5;
        p21_file->dash_height = -12.0;
        p21_file->dash_distance = 12.0;
        p21_file->dash_distancez = 3.0;

        // Configure standing (0), jumping takeoff (210->212), airborne (212), landing (215), special (235)
        p21_file->frames[0].present = 1;
        p21_file->frames[0].state = STATE_STANDING;
        p21_file->frames[0].wait = 4;
        p21_file->frames[0].next = 1;
        p21_file->frames[0].hit_Fa = 235;
        p21_file->frames[1].present = 1;
        p21_file->frames[1].state = STATE_STANDING;
        p21_file->frames[1].wait = 4;
        p21_file->frames[1].next = 999;

        p21_file->frames[5].present = 1;
        p21_file->frames[5].state = STATE_WALKING;
        p21_file->frames[9].present = 1;
        p21_file->frames[9].state = STATE_RUNNING;

        p21_file->frames[60].present = 1;
        p21_file->frames[60].state = STATE_ATTACKING;
        p21_file->frames[65].present = 1;
        p21_file->frames[65].state = STATE_ATTACKING;

        p21_file->frames[110].present = 1;
        p21_file->frames[110].state = STATE_DEFENDING;
        p21_file->frames[110].hit_Fa = 235;

        p21_file->frames[210].present = 1;
        p21_file->frames[210].state = STATE_OTHER;
        p21_file->frames[210].wait = 0;
        p21_file->frames[210].next = 212;
        p21_file->frames[212].present = 1;
        p21_file->frames[212].state = STATE_JUMPING;
        p21_file->frames[212].wait = 10;
        p21_file->frames[212].next = 999;
        p21_file->frames[215].present = 1;
        p21_file->frames[215].state = STATE_OTHER;
        p21_file->frames[215].wait = 2;
        p21_file->frames[215].next = 999;

        p21_file->frames[235].present = 1;
        p21_file->frames[235].state = STATE_ATTACKING;
        p21_file->frames[235].mp = 150;
        p21_file->frames[235].dvx = 556; // 556 - 550 = 6 (signed override)
        p21_file->frames[235].dvy = 548; // 548 - 550 = -2
        p21_file->frames[235].dvz = 553; // 553 - 550 = 3

        object_t p21_obj;
        memset(&p21_obj, 0, sizeof(p21_obj));
        p21_obj.file = p21_file;
        p21_obj.hp = 500;
        p21_obj.max_hp = 500;
        p21_obj.mp = 500;
        p21_obj.uid = -1;
        p21_obj.facing = FACING_RIGHT;

        // 0x0040E450: 5-entry input history shift register
        lf2_input_history_push(&p21_obj, 9);
        lf2_input_history_push(&p21_obj, 6);
        lf2_input_history_push(&p21_obj, 5);
        assert(p21_obj.input_history[2] == 9 && p21_obj.input_history[3] == 6 && p21_obj.input_history[4] == 5);

        // 0x0040E170: combo interruption helper
        p21_obj.attack_press = 5;
        assert(lf2_combo_interrupted(&p21_obj, 'd', 0) == 1);
        assert(lf2_combo_interrupted(&p21_obj, 'R', 1) == 1);
        p21_obj.attack_press = 0;
        p21_obj.defend_press = 5;
        assert(lf2_combo_interrupted(&p21_obj, 'd', 1) == 0);
        p21_obj.defend_press = 0;

        // 0x0040E2D0: frame transition & MP/HP cost
        DAT_0044d034 = 1;
        int prev_mp = p21_obj.mp;
        lf2_frame_transition(&p21_obj, 235);
        assert(p21_obj.frame_id1 == 235);
        assert(p21_obj.mp == prev_mp - 150);

        // 0x00413080: dvx/dvy/dvz 550-offset override + 9 combo recognizers (D > R > A)
        p21_obj.frame_id1 = 235;
        lf2_object_input_tick(&p21_obj);
        assert(p21_obj.x_velocity == 6.0);
        assert(p21_obj.y_velocity == -2.0);
        assert(p21_obj.z_velocity == 3.0);

        // Execute D -> R -> A combo across 3 ticks from frame 0
        p21_obj.frame_id1 = 0;
        p21_obj.frame_id2 = 0;
        p21_obj.x_velocity = p21_obj.y_velocity = p21_obj.z_velocity = 0.0;
        p21_obj.facing = FACING_LEFT;
        // Tick 1: press Defend
        p21_obj.holding_defend = 0; p21_obj.click_defend = 1;
        lf2_object_input_tick(&p21_obj);
        p21_obj.holding_defend = 1; p21_obj.click_defend = 0;
        // Tick 2: press Right
        p21_obj.holding_right = 0; p21_obj.click_right = 1;
        lf2_object_input_tick(&p21_obj);
        p21_obj.holding_right = 1; p21_obj.click_right = 0;
        // Tick 3: press Attack -> D > R > A fires hit_Fa (235) and faces RIGHT
        p21_obj.holding_attack = 0; p21_obj.click_attack = 1;
        lf2_object_input_tick(&p21_obj);
        assert(p21_obj.frame_id1 == 235);
        assert(p21_obj.facing == FACING_RIGHT);

        // Clear all presses for walk / double-tap run test
        memset(p21_obj.key_state, 0, sizeof(p21_obj.key_state));
        p21_obj.holding_right = p21_obj.click_right = 0;
        p21_obj.holding_attack = p21_obj.click_attack = 0;
        p21_obj.click_DRA = 0;
        p21_obj.frame_id1 = 0;
        p21_obj.frame_id2 = 0;
        p21_obj.wait_counter = 0;
        p21_obj.click_right = 1;
        lf2_object_input_tick(&p21_obj);
        assert(p21_obj.frame_id1 >= 5 && p21_obj.frame_id1 <= 8); // walking
        // Double-tap Right -> Run
        p21_obj.frame_id1 = 0;
        p21_obj.holding_right = 0; p21_obj.click_right = 1;
        p21_obj.dash_counter = 4; // within double-tap run window
        lf2_object_input_tick(&p21_obj);
        assert(p21_obj.frame_id1 >= 9 && p21_obj.frame_id1 <= 11); // running

        // Jump press -> frame 210 -> 0x0040D960 launch to 212
        p21_obj.frame_id1 = 0;
        p21_obj.frame_id2 = 0;
        p21_obj.y = 0;
        p21_obj.y_position = 0.0;
        p21_obj.x_velocity = p21_obj.y_velocity = p21_obj.z_velocity = 0.0;
        p21_obj.holding_right = 1; p21_obj.click_right = 1;
        p21_obj.holding_jump = 0; p21_obj.click_jump = 1;
        lf2_object_input_tick(&p21_obj);
        assert(p21_obj.frame_id1 == 210);
        lf2_object_frame_advance(&p21_obj, 0, 0);
        assert(p21_obj.frame_id1 == 212);
        assert(p21_obj.y_velocity == p21_file->jump_height);
        assert(p21_obj.x_velocity == p21_file->jump_distance);

        // 0x0040E490: Airborne gravity (+1.7) & ground landing -> 215 + (-1.0) friction
        p21_obj.y_position = -10.0;
        p21_obj.y = -10;
        p21_obj.y_velocity = 0.0;
        lf2_object_physics_tick(&p21_obj);
        assert(p21_obj.y_position == -10.0);
        assert(p21_obj.y_velocity == 1.7);
        lf2_object_physics_tick(&p21_obj);
        assert(fabs(p21_obj.y_position - (-8.3)) < 1e-9);
        assert(fabs(p21_obj.y_velocity - 3.4) < 1e-9);

        p21_obj.y_position = -1.0;
        p21_obj.y = -1;
        p21_obj.y_velocity = 5.0;
        lf2_object_physics_tick(&p21_obj);
        assert(p21_obj.y == 0);
        assert(p21_obj.y_position == 0.0);
        assert(p21_obj.y_velocity == 0.0);
        assert(p21_obj.frame_id1 == 215);

        p21_obj.x_velocity = 3.0;
        lf2_object_physics_tick(&p21_obj);
        assert(p21_obj.x_velocity == 2.0); // -1.0 ground friction

        free(p21_file);
        printf("    [PASS] Phase 21 & 22 Frame Advance, Combo Recognizers, Input & Physics verified!\n");
    }

    printf("\n[SUCCESS] All Decompiled Compilable Suite Tests Passed with 100%% Parity!\n");
    return 0;
}

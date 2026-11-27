#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#ifdef _WIN32
#include <direct.h>
#endif
#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/* Unported Win32/DirectDraw graphics & UI hooks required when linking static library objects into test_legacy */
void FUN_00415160(int x, int y, int w, int h, int color) {
    (void)x; (void)y; (void)w; (void)h; (void)color;
}
int FUN_0043f010(int x, int y, int idx, int trans, int flag, void *dst) {
    (void)x; (void)y; (void)idx; (void)trans; (void)flag; (void)dst;
    return 0;
}
int FUN_0043ee50(int bpp, const char *path, int mirror) {
    (void)bpp; (void)path; (void)mirror;
    if (in_ECX != NULL) {
        free(in_ECX);
    }
    return 1;
}
void FUN_004242e0(const char *path, int arg) {
    (void)path; (void)arg;
}
void FUN_0043e940(uintptr_t handle) {
    (void)handle;
}
void FUN_0043d230(void) {
}

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
    assert(sizeof(object_t) == 0x420);
    assert(offsetof(object_t, x) == 0x10);
    assert(offsetof(object_t, wait_counter) == 0x88);
    assert(offsetof(object_t, input_history) == 0x408);
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

    // 15. Test Phase 21: wpoint_sync (0x00417F80), cpoint_sync (0x004187B0), cpoint_chain (0x00418C30), Firzen fusion (0x004064D0)
    printf("[*] Testing Phase 21 Weapon Sync, Cpoint Grapple/Chain, and Firzen Fusion...\n");
    {
        static global_t g15;
        memset(&g15, 0, sizeof(g15));
        in_ECX = &g15;

        file_t *cfile = (file_t *)calloc(1, sizeof(file_t));
        file_t *vfile = (file_t *)calloc(1, sizeof(file_t));
        file_t *milk_file = (file_t *)calloc(1, sizeof(file_t));
        file_t *beer_file = (file_t *)calloc(1, sizeof(file_t));
        file_t *bat_file = (file_t *)calloc(1, sizeof(file_t));
        file_t *firen_file = (file_t *)calloc(1, sizeof(file_t));
        file_t *freeze_file = (file_t *)calloc(1, sizeof(file_t));
        file_t *firzen_file = (file_t *)calloc(1, sizeof(file_t));
        assert(cfile && vfile && milk_file && beer_file && bat_file && firen_file && freeze_file && firzen_file);

        cfile->id = ID_RUDOLF_DAT;
        cfile->type = TYPE_CHARACTER;
        vfile->id = ID_DENNIS_DAT;
        vfile->type = TYPE_CHARACTER;
        milk_file->id = ID_MILK_DAT;
        milk_file->type = TYPE_DRINK;
        beer_file->id = ID_BEER_DAT;
        beer_file->type = TYPE_DRINK;
        bat_file->id = ID_STICK_DAT;
        bat_file->type = TYPE_LIGHT_WEAPON;
        firen_file->id = ID_FIREN_DAT;
        firen_file->type = TYPE_CHARACTER;
        freeze_file->id = ID_FREEZE_DAT;
        freeze_file->type = TYPE_CHARACTER;
        firzen_file->id = ID_FIRZEN_DAT;
        firzen_file->type = TYPE_CHARACTER;

        // 15a: FUN_00417f80 (Milk/Beer drinking, dual-anchor wpoint, falling -2.0 clamp, throw, kind==3 / 5.0 drop)
        cfile->frames[10].state = STATE_DRINKING;
        cfile->frames[10].centerx = 40;
        cfile->frames[10].centery = 40;
        cfile->frames[10].wpoint.kind = 1;
        cfile->frames[10].wpoint.x = 45;
        cfile->frames[10].wpoint.y = 30;
        cfile->frames[10].wpoint.weaponact = 2;
        cfile->frames[10].wpoint.cover = 0;

        cfile->frames[11].state = STATE_STANDING;
        cfile->frames[11].centerx = 40;
        cfile->frames[11].centery = 40;
        cfile->frames[11].wpoint.kind = 1;
        cfile->frames[11].wpoint.x = 50;
        cfile->frames[11].wpoint.y = 35;
        cfile->frames[11].wpoint.weaponact = 3;
        cfile->frames[11].wpoint.cover = 1;

        cfile->frames[12].state = STATE_FALLING;
        cfile->frames[13].state = STATE_ATTACKING;
        cfile->frames[13].wpoint.kind = 1;
        cfile->frames[13].wpoint.weaponact = 3;
        cfile->frames[13].wpoint.dvx = 12;
        cfile->frames[13].wpoint.dvy = -3;
        cfile->frames[13].wpoint.dvz = 2;
        cfile->frames[14].state = STATE_STANDING;
        cfile->frames[14].wpoint.kind = 3;
        cfile->frames[14].wpoint.weaponact = 3;

        milk_file->frames[2].centerx = 10; milk_file->frames[2].centery = 15;
        milk_file->frames[2].wpoint.x = 10; milk_file->frames[2].wpoint.y = 15;
        beer_file->frames[2].centerx = 10; beer_file->frames[2].centery = 15;
        beer_file->frames[2].wpoint.x = 10; beer_file->frames[2].wpoint.y = 15;
        bat_file->frames[3].centerx = 20; bat_file->frames[3].centery = 20;
        bat_file->frames[3].wpoint.x = 15; bat_file->frames[3].wpoint.y = 18;

        object_t holder, milk, beer, bat;
        lf2_object_init(&holder);
        lf2_object_init(&milk);
        lf2_object_init(&beer);
        lf2_object_init(&bat);

        holder.file = cfile;
        holder.x = 100; holder.y = 0; holder.z = 200;
        holder.x_position = 100.0; holder.y_position = 0.0; holder.z_position = 200.0;
        holder.facing = FACING_RIGHT;
        holder.frame_id1 = 10;
        holder.hp = 400; holder.dark_hp = 450; holder.max_hp = 500; holder.mp = 100;
        holder.weapon_type = 6;
        holder.weapon_id = 1;

        milk.file = milk_file;
        milk.weapon_type = -6;
        milk.holder_id = 0;
        milk.hp = 11;
        milk.clone = -1;
        milk.weapon_hp = 1000;

        g15.objects[0] = &holder; g15.is_object_exists[0] = 1;
        g15.objects[1] = &milk;   g15.is_object_exists[1] = 1;

        FUN_00417f80();
        assert(milk.hp == 10);
        assert(holder.dark_hp == 452);
        assert(holder.hp == 404);
        assert(milk.x == 105 && milk.y == -11 && milk.z == 201);

        milk.hp = 1;
        FUN_00417f80();
        assert(milk.hp == 0);
        assert(holder.weapon_type == 0 && milk.weapon_type == 0);
        assert(holder.weapon_id == 0 && milk.holder_id == 0);
        assert(holder.frame_id1 == 0 && milk.weapon_hp == 0);
        assert(milk.y_velocity == -8.0);

        // Beer drinking + empty toss
        g15.is_object_exists[1] = 0;
        beer.file = beer_file;
        beer.weapon_type = -6;
        beer.holder_id = 0;
        beer.hp = 2;
        beer.clone = -1;
        g15.objects[2] = &beer; g15.is_object_exists[2] = 1;
        holder.weapon_type = 6;
        holder.weapon_id = 2;
        holder.frame_id1 = 10;
        holder.mp = 499;
        FUN_00417f80();
        assert(holder.mp == 500); // clamped
        assert(beer.hp == 0);
        assert(beer.y_velocity == -8.0);
        assert(holder.weapon_type == 0 && beer.weapon_type == 0);
        g15.is_object_exists[2] = 0;

        // Dual-anchor cover==1 + falling -2.0 clamp + dvx throw + kind==3 / 5.0 drop
        bat.file = bat_file;
        bat.weapon_type = -1;
        bat.holder_id = 0;
        g15.objects[3] = &bat; g15.is_object_exists[3] = 1;
        holder.weapon_type = 1;
        holder.weapon_id = 3;
        holder.frame_id1 = 11;
        holder.z_position = 200.0;
        FUN_00417f80();
        assert(bat.frame_id1 == 3);
        assert(bat.x == 115 && bat.y == -2 && bat.z == 199);

        holder.frame_id1 = 12; // STATE_FALLING
        holder.y = 40;
        holder.x_velocity = 9.0;
        holder.y_velocity = -4.0;
        FUN_00417f80();
        assert(holder.weapon_type == 0 && bat.weapon_type == 0);
        assert(bat.x_velocity == 3.0 && bat.y_velocity == -4.0);
        assert(bat.y_position == -2.0); // 0x4479d8 clamp

        holder.y = 0;
        holder.weapon_type = 1;
        bat.weapon_type = -1;
        holder.frame_id1 = 13;
        holder.click_up = 1; holder.click_down = 0;
        FUN_00417f80();
        assert(bat.frame_id1 == 40);
        assert(bat.weapon_throw_injury == 0);
        assert(bat.x_velocity == 12.0 && bat.y_velocity == -3.0 && bat.z_velocity == -2.0);
        assert(holder.weapon_type == 0 && bat.weapon_type == 0);

        holder.weapon_type = 1;
        bat.weapon_type = -1;
        holder.frame_id1 = 14; // wpoint.kind == 3
        holder.click_up = 0;
        FUN_00417f80();
        assert(holder.weapon_type == 0 && bat.weapon_type == 0);
        assert(fabs(bat.z_velocity) <= 0.4 + 1e-9);
        g15.is_object_exists[3] = 0;

        // 15b: FUN_004187b0 & FUN_00418c30 (cpoint sync, injury, chain, breakout, dircontrol, throw, Rudolf transform, orphan)
        cfile->frames[120].state = STATE_CATCHING;
        cfile->frames[120].centerx = 40; cfile->frames[120].centery = 40;
        cfile->frames[120].cpoint.kind = 1;
        cfile->frames[120].cpoint.x = 60; cfile->frames[120].cpoint.y = 35;
        cfile->frames[120].cpoint.injury = 30;
        cfile->frames[120].cpoint.cover = 21;
        cfile->frames[120].cpoint.vaction = 230;
        cfile->frames[120].cpoint.aaction = 121;
        cfile->frames[120].cpoint.taction = 122;
        cfile->frames[120].cpoint.jaction = 123;
        cfile->frames[120].cpoint.hurtable = 1;
        cfile->frames[120].cpoint.decrease = -10;
        cfile->frames[120].cpoint.dircontrol = 1;

        cfile->frames[121].cpoint.kind = 1; cfile->frames[121].cpoint.vaction = 231;
        cfile->frames[122].cpoint.kind = 1; cfile->frames[122].cpoint.vaction = 232;
        cfile->frames[123].cpoint.kind = 1; cfile->frames[123].cpoint.vaction = 233;

        cfile->frames[125].state = STATE_CATCHING;
        cfile->frames[125].centerx = 40; cfile->frames[125].centery = 40;
        cfile->frames[125].next = 0;
        cfile->frames[125].cpoint.kind = 1;
        cfile->frames[125].cpoint.x = 65; cfile->frames[125].cpoint.y = 30;
        cfile->frames[125].cpoint.vaction = 180;
        cfile->frames[125].cpoint.throwvx = 14;
        cfile->frames[125].cpoint.throwvy = -8;
        cfile->frames[125].cpoint.throwvz = 3;
        cfile->frames[125].cpoint.throwinjury = 45;

        cfile->frames[126].state = STATE_CATCHING;
        cfile->frames[126].centerx = 40; cfile->frames[126].centery = 40;
        cfile->frames[126].next = 0;
        cfile->frames[126].cpoint.kind = 1;
        cfile->frames[126].cpoint.vaction = 180;
        cfile->frames[126].cpoint.throwvx = 10;
        cfile->frames[126].cpoint.throwinjury = -1;

        for (int f = 230; f <= 233; ++f) {
            vfile->frames[f].centerx = 30;
            vfile->frames[f].centery = 40;
            vfile->frames[f].cpoint.kind = 2;
            vfile->frames[f].cpoint.x = 30;
            vfile->frames[f].cpoint.y = 40;
        }

        object_t catcher, victim, clone_obj;
        lf2_object_init(&catcher);
        lf2_object_init(&victim);
        lf2_object_init(&clone_obj);

        catcher.file = cfile;
        catcher.owner = 0;
        catcher.x = 200; catcher.y = 0; catcher.z = 150;
        catcher.facing = FACING_RIGHT;
        catcher.frame_id1 = 120; catcher.frame_id4 = 120;
        catcher.cpoint_catcher = 1;
        catcher.cpoint_hurtable = 300;
        catcher.wait_counter = 0;

        victim.file = vfile;
        victim.x = 220; victim.y = 0; victim.z = 150;
        victim.facing = FACING_RIGHT;
        victim.frame_id1 = 230; victim.frame_id4 = 230;
        victim.cpoint_caught = 0;
        victim.clone = -1;

        clone_obj.file = cfile;
        clone_obj.clone = 0;

        g15.objects[0] = &catcher; g15.is_object_exists[0] = 1;
        g15.objects[1] = &victim;  g15.is_object_exists[1] = 1;
        g15.objects[2] = &clone_obj; g15.is_object_exists[2] = 1;

        FUN_004187b0();
        assert(victim.hp == 470);
        assert(victim.dark_hp == 490);
        assert(catcher.wait_counter == 1);
        assert(catcher.shaking == 2 && victim.shaking == -3);
        assert(catcher.total_attack == 30);
        assert(victim.z == 151); // cover % 10 == 1
        assert(victim.facing == FACING_LEFT); // cover / 10 == 2
        // Second call while wait_counter == 1 does not deal duplicate injury
        victim.shaking = 0;
        FUN_004187b0();
        assert(victim.hp == 470);

        // Chain actions + dircontrol + decrease breakout
        catcher.shaking = 0;
        catcher.wait_counter = 2;
        catcher.click_left = 1; catcher.click_right = 0;
        catcher.click_attack = 0; catcher.click_jump = 0;
        FUN_00418c30();
        assert(catcher.facing == FACING_LEFT);

        catcher.frame_id1 = 120; catcher.frame_id4 = 120;
        catcher.click_left = 0; catcher.click_attack = 1; catcher.attack_press = 1;
        catcher.cpoint_hurtable = 300;
        FUN_00418c30();
        assert(catcher.frame_id1 == 121 && victim.frame_id1 == 231);
        assert(catcher.wait_counter == 0 && victim.wait_counter == 0);

        catcher.frame_id1 = 120; catcher.frame_id4 = 120;
        catcher.click_left = 1; catcher.click_attack = 1; catcher.attack_press = 1;
        catcher.cpoint_hurtable = 300;
        FUN_00418c30();
        assert(catcher.frame_id1 == 122 && victim.frame_id1 == 232);

        catcher.frame_id1 = 120; catcher.frame_id4 = 120;
        catcher.click_attack = 0; catcher.click_jump = 1; catcher.jump_press = 1;
        catcher.cpoint_hurtable = 300;
        FUN_00418c30();
        assert(catcher.frame_id1 == 123 && victim.frame_id1 == 233);

        // Breakout (cpoint_hurtable + decrease < 0)
        catcher.frame_id1 = 120; catcher.frame_id4 = 120;
        victim.frame_id1 = 230; victim.frame_id4 = 230;
        catcher.click_jump = 0; catcher.click_left = 0;
        catcher.cpoint_hurtable = 5;
        FUN_00418c30();
        assert(catcher.frame_id1 == 0 && victim.frame_id1 == 181);
        assert(victim.attacks == 1 && victim.y_accl == -3.0 && victim.pic_x_gain == 4.0);

        // Throw launch (frame 125)
        catcher.frame_id1 = 125; catcher.frame_id4 = 125;
        catcher.facing = FACING_RIGHT; catcher.click_up = 1;
        victim.frame_id1 = 230; victim.frame_id4 = 230;
        victim.y_velocity = 0.0; victim.z_velocity = 0.0;
        FUN_00418c30();
        assert(victim.x_velocity == 14.0 && victim.y_velocity == -8.0 && victim.z_velocity == -3.0);
        assert(victim.thrown_injury == 45 && victim.frame_id1 == 180 && catcher.frame_id1 == 0);

        // Rudolf transform (frame 126, throwinjury == -1)
        catcher.file = cfile;
        clone_obj.file = cfile;
        catcher.frame_id1 = 126; catcher.frame_id4 = 126;
        victim.frame_id1 = 230; victim.frame_id4 = 230;
        FUN_00418c30();
        assert(catcher.file == vfile);
        assert(catcher.uid == (int32_t)ID_RUDOLF_DAT);
        assert(catcher._unknown39 == (int32_t)ID_DENNIS_DAT);
        assert(clone_obj.file == vfile);

        // Orphan caught victim release -> 212
        catcher.file = cfile;
        catcher.frame_id1 = 0; catcher.frame_id4 = 0;
        victim.frame_id1 = 230; victim.frame_id4 = 230;
        victim.y_position = 0.0; victim.y_velocity = 0.0;
        FUN_00418c30();
        assert(victim.frame_id1 == 212 && victim.y_velocity == -3.0 && victim.y_position == -2.0);
        g15.is_object_exists[2] = 0;

        // 15c: FUN_004064d0 (Firen + Freeze -> Firzen fusion & defusion)
        memset(&g15, 0, sizeof(g15));
        g15.files[0] = firen_file;
        g15.files[1] = freeze_file;
        g15.files[2] = firzen_file;
        firen_file->frames[9].state = STATE_RUNNING;
        freeze_file->frames[9].state = STATE_RUNNING;

        object_t firen, freeze;
        lf2_object_init(&firen);
        lf2_object_init(&freeze);
        firen.file = firen_file;  firen.hp = 150;  firen.frame_id1 = 9;  firen.x = 120; firen.z = 200; firen.team = 1;
        freeze.file = freeze_file; freeze.hp = 140; freeze.frame_id1 = 9; freeze.x = 100; freeze.z = 200; freeze.team = 1;
        g15.objects[0] = &firen;  g15.is_object_exists[0] = 1;
        g15.objects[1] = &freeze; g15.is_object_exists[1] = 1;

        FUN_004064d0();
        assert(firen.file == firzen_file);
        assert(firen.frame_id1 == 290);
        assert(firen.hp == 290);
        assert(firen.mp == 500);
        assert(firen.firen_counter == 4500);
        assert(firen._unknown34_rest[0] == 1);
        assert(g15.is_object_exists[1] == 0);

        // Defusion back to Firen + Freeze when firen_counter reaches 0
        firen.frame_id1 = 0;
        firen.firen_counter = 1;
        FUN_004064d0();
        assert(firen._unknown34_rest[0] == -1);
        assert(firen.file == firen_file && freeze.file == freeze_file);
        assert(g15.is_object_exists[1] == 1);
        assert(firen.hp == 145 && freeze.hp == 145);
        assert(firen.frame_id1 == 112 && freeze.frame_id1 == 112);
        assert(firen.mp == 0 && freeze.mp == 0);
        assert(firen.firen_counter == 900);
        assert(freeze.facing == (uint8_t)(1 - firen.facing));

        free(cfile); free(vfile); free(milk_file); free(beer_file);
        free(bat_file); free(firen_file); free(freeze_file); free(firzen_file);
        printf("    [PASS] Phase 21 Weapon Sync, Cpoint Grapple/Chain, and Firzen Fusion verified!\n");
    }

    // =========================================================================
    // Test 16: Phase 20 AI Controller, opoint Spawner, hit_Fa & Weapon Decisions
    // =========================================================================
    printf("[16] Testing Phase 20 opoint Spawner (0x406A20), hit_Fa (0x406BA0), Weapon AI (0x408CB0), Specials (0x403A40), Dodge (0x4034F0) & AI Core (0x4094B0)...\n");
    {
        global_t *g16 = (global_t *)calloc(1, sizeof(global_t));
        void *prev_ecx16 = in_ECX;
        in_ECX = g16;

        // Save globals touched by AI functions
        int saved_c2c = DAT_00450c2c;
        int saved_c30 = DAT_00450c30;
        int saved_bb4 = DAT_00450bb4;
        int saved_bac = DAT_00450bac;
        int saved_zmin = lf2_bg_zmin;
        int saved_zmax = lf2_bg_zmax;
        int saved_bcc = DAT_00450bcc;
        int saved_c34 = DAT_00450c34;

        for (int s = 0; s < MAX_OBJECTS; ++s) {
            g16->objects[s] = (object_t *)calloc(1, sizeof(object_t));
            lf2_object_init(g16->objects[s]);
        }

        // Helper macro-like local file allocation for IDs used across tests
        file_t *files16[24] = {0};
        const int fids16[24] = {
            ID_JOHN_DAT, ID_DEEP_DAT, ID_HENRY_DAT, ID_FIREN_DAT, ID_FREEZE_DAT,
            ID_DENNIS_DAT, ID_WOODY_DAT, ID_DAVIS_DAT, ID_MARK_DAT, ID_JAN_DAT,
            ID_BAT_DAT, ID_FIRZEN_DAT, ID_JULIAN_DAT, ID_SORCERER_DAT,
            ID_STICK_DAT, ID_MILK_DAT, ID_BOOMERANG_DAT, ID_STONE_DAT,
            ID_JOHN_BALL_DAT, ID_FIREN_FLAME_DAT, ID_FREEZE_COLUMN_DAT,
            ID_JAN_CHASEH_DAT, ID_JAN_CHASE_DAT, ID_BAT_CHASE_DAT
        };
        file_t *f_chasef = (file_t *)calloc(1, sizeof(file_t));
        f_chasef->id = ID_FIRZEN_CHASEF_DAT;
        f_chasef->type = 3;
        file_t *f_chasei = (file_t *)calloc(1, sizeof(file_t));
        f_chasei->id = ID_FIRZEN_CHASEF_DAT + 1;
        f_chasei->type = 3;
        file_t *f_jball = (file_t *)calloc(1, sizeof(file_t));
        f_jball->id = ID_JULIAN_BALL_DAT;
        f_jball->type = 3;

        for (int i = 0; i < 24; ++i) {
            files16[i] = (file_t *)calloc(1, sizeof(file_t));
            files16[i]->id = (uint32_t)fids16[i];
            if (fids16[i] < 100) files16[i]->type = TYPE_CHARACTER;
            else if (fids16[i] < 200) files16[i]->type = (fids16[i] == ID_STONE_DAT) ? 4 : 1;
            else files16[i]->type = 3;
            g16->files[i] = files16[i];
        }
        g16->files[24] = f_chasef;
        g16->files[25] = f_chasei;
        g16->files[26] = f_jball;
        files16[14]->weapon_hp = 85; // STICK_DAT weapon_hp

        // File lookup helper indices matching files16 array above:
        // 0:JOHN 1:DEEP 2:HENRY 3:FIREN 4:FREEZE 5:DENNIS 6:WOODY 7:DAVIS 8:MARK 9:JAN
        // 10:BAT 11:FIRZEN 12:JULIAN 13:SORCERER 14:STICK 15:MILK 16:BOOMERANG 17:STONE
        // 18:JOHN_BALL 19:FIREN_FLAME 20:FREEZE_COLUMN 21:JAN_CHASEH 22:JAN_CHASE 23:BAT_CHASE

        // 16A. FUN_00406a20 (0x00406A20 opoint spawner)
        int sp_slot = FUN_00406a20(ID_STICK_DAT, 2, 10, 1, 320, -15, 220, 4.5, -2.0, 0.5, FACING_LEFT);
        assert(sp_slot == 50);
        assert(g16->is_object_exists[50] == 1);
        assert(g16->objects[50]->file == files16[14]);
        assert(g16->objects[50]->owner == 2 && g16->objects[50]->team == 1);
        assert(g16->objects[50]->chase_target == -1 && g16->objects[50]->weapon_hp == 85);
        assert(g16->objects[50]->x == 320 && g16->objects[50]->y == -15 && g16->objects[50]->z == 220);
        assert(g16->objects[50]->x_velocity == 4.5 && g16->objects[50]->facing == FACING_LEFT);
        g16->is_object_exists[50] = 0;

        // 16B. FUN_00406ba0 (0x00406BA0 hit_Fa modes 1..14)
        lf2_object_init(g16->objects[0]);
        g16->objects[0]->file = files16[0]; g16->objects[0]->team = 1; g16->objects[0]->hp = 500;
        g16->objects[0]->x = 200; g16->objects[0]->y = 0; g16->objects[0]->z = 200;
        g16->objects[0]->x_position = 200.0; g16->objects[0]->z_position = 200.0;
        g16->is_object_exists[0] = 1;

        lf2_object_init(g16->objects[1]);
        g16->objects[1]->file = files16[5]; g16->objects[1]->team = 2; g16->objects[1]->hp = 500;
        g16->objects[1]->x = 500; g16->objects[1]->y = 0; g16->objects[1]->z = 220;
        g16->objects[1]->x_position = 500.0; g16->objects[1]->z_position = 220.0;
        g16->is_object_exists[1] = 1;

        // hit_Fa == 11: Firzen Artic Volcano (14 child spawns + self removed)
        files16[19]->frames[1].hit_Fa = 11;
        lf2_object_init(g16->objects[50]);
        g16->objects[50]->file = files16[19]; g16->objects[50]->frame_id1 = 1;
        g16->objects[50]->owner = 0; g16->objects[50]->team = 1;
        g16->objects[50]->x = 300; g16->objects[50]->y = 0; g16->objects[50]->z = 200;
        g16->is_object_exists[50] = 1;
        FUN_00406ba0(50);
        assert(g16->is_object_exists[50] == 0);
        int volcano_children = 0;
        for (int s = 51; s <= 64; ++s) {
            if (g16->is_object_exists[s] == 1) volcano_children++;
            g16->is_object_exists[s] = 0;
        }
        assert(volcano_children == 14);
        files16[19]->frames[1].hit_Fa = 0;

        // hit_Fa == 8: Bat multi-seeker (3 with 1 enemy, (5-3)/2+3 = 4 with 5 enemies)
        files16[23]->frames[2].hit_Fa = 8;
        lf2_object_init(g16->objects[50]);
        g16->objects[50]->file = files16[23]; g16->objects[50]->frame_id1 = 2;
        g16->objects[50]->team = 1; g16->objects[50]->x = 220; g16->objects[50]->z = 200;
        g16->is_object_exists[50] = 1;
        FUN_00406ba0(50);
        assert(g16->is_object_exists[50] == 0);
        int bat_count = 0;
        for (int s = 51; s < 60; ++s) {
            if (g16->is_object_exists[s] == 1) {
                assert(g16->objects[s]->file->id == ID_BAT_CHASE_DAT);
                assert(g16->objects[s]->chase_target == 1);
                bat_count++;
                g16->is_object_exists[s] = 0;
            }
        }
        assert(bat_count == 3);
        for (int e = 2; e <= 5; ++e) {
            lf2_object_init(g16->objects[e]);
            g16->objects[e]->file = files16[5]; g16->objects[e]->team = 2; g16->objects[e]->hp = 400;
            g16->is_object_exists[e] = 1;
        }
        g16->is_object_exists[50] = 1;
        FUN_00406ba0(50);
        int bat_count5 = 0;
        for (int s = 51; s < 65; ++s) {
            if (g16->is_object_exists[s] == 1) { bat_count5++; g16->is_object_exists[s] = 0; }
        }
        assert(bat_count5 == 4);
        for (int e = 2; e <= 5; ++e) g16->is_object_exists[e] = 0;
        files16[23]->frames[2].hit_Fa = 0;

        // hit_Fa == 13: Julian Big Bang seeker spawn
        f_jball->frames[2].hit_Fa = 13;
        lf2_object_init(g16->objects[50]);
        g16->objects[50]->file = f_jball; g16->objects[50]->frame_id1 = 2;
        g16->objects[50]->team = 1; g16->objects[50]->x_velocity = 5.0;
        g16->is_object_exists[50] = 1;
        FUN_00406ba0(50);
        assert(g16->is_object_exists[50] == 0 && g16->is_object_exists[51] == 1);
        assert(g16->objects[51]->file->id == ID_JULIAN_BALL_DAT && g16->objects[51]->chase_target == 1);
        g16->is_object_exists[51] = 0;
        f_jball->frames[2].hit_Fa = 0;

        // hit_Fa == 5 (Jan heal), 6 (Jan chase), 9 (Firzen disaster)
        files16[21]->frames[1].hit_Fa = 5;
        lf2_object_init(g16->objects[50]);
        g16->objects[50]->file = files16[21]; g16->objects[50]->frame_id1 = 1; g16->objects[50]->team = 1;
        g16->is_object_exists[50] = 1;
        FUN_00406ba0(50);
        assert(g16->is_object_exists[50] == 0 && g16->is_object_exists[51] == 1);
        assert(g16->objects[51]->file->id == ID_JAN_CHASEH_DAT && g16->objects[51]->chase_target == 0);
        g16->is_object_exists[51] = 0;
        files16[21]->frames[1].hit_Fa = 0;

        files16[22]->frames[1].hit_Fa = 6;
        g16->is_object_exists[50] = 1;
        g16->objects[50]->file = files16[22]; g16->objects[50]->frame_id1 = 1;
        FUN_00406ba0(50);
        assert(g16->is_object_exists[50] == 0 && g16->is_object_exists[51] == 1);
        assert(g16->objects[51]->file->id == ID_JAN_CHASE_DAT && g16->objects[51]->chase_target == 1);
        g16->is_object_exists[51] = 0;
        files16[22]->frames[1].hit_Fa = 0;

        f_chasef->frames[1].hit_Fa = 9;
        g16->is_object_exists[50] = 1;
        g16->objects[50]->file = f_chasef; g16->objects[50]->frame_id1 = 1; g16->objects[50]->team = 1;
        FUN_00406ba0(50);
        assert(g16->is_object_exists[50] == 0);
        int dis_cnt = 0;
        for (int s = 51; s < 65; ++s) {
            if (g16->is_object_exists[s] == 1) {
                uint32_t sfid = g16->objects[s]->file->id;
                assert(sfid == ID_FIRZEN_CHASEF_DAT || sfid == ID_FIRZEN_CHASEF_DAT + 1);
                dis_cnt++;
                g16->is_object_exists[s] = 0;
            }
        }
        assert(dis_cnt == 4);
        f_chasef->frames[1].hit_Fa = 0;

        // hit_Fa == 4: Jan heal angel impact sets target->heal_timer = 100
        files16[21]->frames[2].hit_Fa = 4;
        lf2_object_init(g16->objects[50]);
        g16->objects[50]->file = files16[21]; g16->objects[50]->frame_id1 = 2;
        g16->objects[50]->chase_target = 0;
        g16->objects[50]->x = 200; g16->objects[50]->y = -20; g16->objects[50]->z = 200;
        g16->is_object_exists[50] = 1;
        g16->objects[0]->heal_timer = 0;
        FUN_00406ba0(50);
        assert(g16->objects[50]->frame_id1 == 60 && g16->objects[0]->heal_timer == 100);
        g16->is_object_exists[50] = 0;
        files16[21]->frames[2].hit_Fa = 0;

        // hit_Fa == 7 (meteor trail + ground impact), 10 (accel clamp), 2/14 (speed frame switch), 1/3 (steer)
        f_chasef->frames[3].hit_Fa = 7;
        lf2_object_init(g16->objects[50]);
        g16->objects[50]->file = f_chasef; g16->objects[50]->frame_id1 = 3;
        g16->objects[50]->team = 1; g16->objects[50]->chase_target = 1;
        g16->objects[50]->x = 250; g16->objects[50]->y = -10; g16->objects[50]->z = 200;
        g16->is_object_exists[50] = 1;
        FUN_00406ba0(50);
        assert(g16->is_object_exists[51] == 1 && g16->objects[51]->frame_id1 == 40);
        assert(g16->objects[50]->frame_id1 == 60 && g16->objects[50]->x_velocity == 0.0);
        g16->is_object_exists[50] = 0; g16->is_object_exists[51] = 0;
        f_chasef->frames[3].hit_Fa = 0;

        files16[19]->frames[3].hit_Fa = 10;
        lf2_object_init(g16->objects[50]);
        g16->objects[50]->file = files16[19]; g16->objects[50]->frame_id1 = 3;
        g16->objects[50]->team = 1; g16->objects[50]->x_velocity = 29.5;
        g16->is_object_exists[50] = 1;
        FUN_00406ba0(50);
        assert(g16->objects[50]->x_velocity == 30.0 && g16->objects[50]->facing == FACING_RIGHT);
        g16->is_object_exists[50] = 0;
        files16[19]->frames[3].hit_Fa = 0;

        files16[22]->frames[3].hit_Fa = 14;
        lf2_object_init(g16->objects[50]);
        g16->objects[50]->file = files16[22]; g16->objects[50]->frame_id1 = 3;
        g16->objects[50]->team = 1; g16->objects[50]->chase_target = 1;
        g16->objects[50]->x_velocity = 4.0; g16->objects[50]->y_position = 3.0;
        g16->is_object_exists[50] = 1;
        FUN_00406ba0(50);
        assert(g16->objects[50]->frame_id1 == 53 && g16->objects[50]->y_position == 1.4);
        files16[22]->frames[3].hit_Fa = 2;
        g16->objects[50]->frame_id1 = 3; g16->objects[50]->x_velocity = 11.0;
        FUN_00406ba0(50);
        assert(g16->objects[50]->frame_id1 == 3);
        g16->is_object_exists[50] = 0;
        files16[22]->frames[3].hit_Fa = 0;

        // 16C. FUN_00408cb0 (0x00408CB0 held weapon & drink decisions)
        DAT_00450c2c = 0; DAT_00450c30 = -1;
        DAT_0044f60c = 0; DAT_0044f61c = 0; DAT_0044f618 = 0; DAT_0044f614 = 0; DAT_0044f610 = 0;
        DAT_0044f604 = 800; DAT_0044f608 = 0;
        lf2_bg_zmin = 0; lf2_bg_zmax = 400;

        lf2_object_init(g16->objects[2]);
        g16->objects[2]->file = files16[14]; // STICK_DAT
        g16->objects[2]->x = 200; g16->objects[2]->z = 200;
        g16->is_object_exists[2] = 1;

        lf2_object_init(g16->objects[3]);
        g16->objects[3]->file = files16[0]; g16->objects[3]->team = 1; g16->objects[3]->hp = 500;
        g16->objects[3]->x = 300; g16->objects[3]->z = 200;
        g16->is_object_exists[3] = 1;

        // Self holding stick, velocity lead target->x - 2*x_velocity = 500 - 20 = 480, dx_lead = 80 < 115
        g16->objects[0]->weapon_type = 1; g16->objects[0]->weapon_id = 2;
        g16->objects[0]->x = 400; g16->objects[0]->z = 220; g16->objects[0]->x_velocity = 10.0;
        g16->objects[1]->x = 500; g16->objects[1]->z = 220; g16->objects[1]->team = 2;
        int got_w_atk = 0;
        for (int t = 0; t < 48; ++t) {
            g16->objects[0]->click_attack = 0;
            FUN_00408cb0(1, 0, 0, 0, 0, 0);
            if (g16->objects[0]->click_attack == 1) { got_w_atk = 1; break; }
        }
        assert(got_w_atk == 1);

        // ally_in_line check requires target->team == self->team alongside ally->team != 0
        g16->objects[1]->team = 1; g16->objects[1]->x = 600; g16->objects[1]->z = 200;
        g16->objects[0]->x = 200; g16->objects[0]->z = 200;
        g16->objects[3]->x = 400; g16->objects[3]->z = 200;
        int got_jump_over = 0;
        for (int t = 0; t < 64; ++t) {
            g16->objects[0]->click_jump = 0;
            FUN_00408cb0(1, 0, STATE_RUNNING, 0, 0, 0);
            if (g16->objects[0]->click_jump == 1) { got_jump_over = 1; break; }
        }
        assert(got_jump_over == 1);

        // Milk corner escape & John shield
        g16->objects[2]->file = files16[15]; // MILK_DAT
        g16->objects[1]->team = 2;
        g16->objects[0]->x = 50; g16->objects[0]->z = 200; g16->objects[0]->follow_order = 0;
        g16->objects[1]->x = 150; g16->objects[1]->z = 200;
        FUN_00408cb0(1, 0, 0, 0, 0, 0);
        assert(g16->objects[0]->click_right == 1 && g16->objects[0]->click_up == 1);

        g16->objects[0]->x = 200; g16->objects[0]->z = 200; g16->objects[0]->mp = 300;
        g16->objects[1]->x = 750; g16->objects[1]->z = 200;
        int got_shield = 0;
        for (int t = 0; t < 64; ++t) {
            g16->objects[0]->click_DRJ = 0;
            if (FUN_00408cb0(1, 0, 0, 0, 0, 0) == 1 && g16->objects[0]->click_DRJ == 3) {
                got_shield = 1; break;
            }
        }
        assert(got_shield == 1);
        g16->is_object_exists[2] = 0; g16->is_object_exists[3] = 0;
        g16->objects[0]->weapon_type = 0; g16->objects[0]->weapon_id = 0;

        // 16D. FUN_00403a40 (0x00403A40 character specials) + FUN_004034f0 (0x004034F0 dodge)
        // Firen blaze cancel (deterministic)
        g16->objects[0]->file = files16[3]; g16->objects[0]->frame_id1 = 257;
        g16->objects[0]->facing = FACING_RIGHT; g16->objects[0]->x = 400; g16->objects[0]->z = 200;
        g16->objects[1]->x = 200; g16->objects[1]->z = 200;
        g16->objects[0]->click_defend = 0;
        assert(FUN_00403a40(1, 0, 0, 0, 0, 200, 0) == 1 && g16->objects[0]->click_defend == 1);

        // Firzen cannon cancel (deterministic)
        g16->objects[0]->file = files16[11]; g16->objects[0]->frame_id1 = 270;
        g16->objects[1]->z = 230; g16->objects[0]->click_defend = 0;
        assert(FUN_00403a40(1, 0, 0, 0, 0, 200, 0) == 1 && g16->objects[0]->click_defend == 1);

        // Jan ally blessing scan 0..99
        g16->objects[0]->file = files16[9]; g16->objects[0]->frame_id1 = 0;
        g16->objects[0]->mp = 300; g16->objects[0]->team = 1;
        g16->objects[3]->hp = 100; g16->objects[3]->dark_hp = 400; g16->objects[3]->team = 1;
        g16->is_object_exists[3] = 1;
        int got_jan_heal = 0;
        for (int t = 0; t < 48; ++t) {
            g16->objects[0]->click_DUJ = 0;
            if (FUN_00403a40(1, 0, 0, 0, 0, 200, 0) == 1 && g16->objects[0]->click_DUJ == 3) {
                got_jan_heal = 1; break;
            }
        }
        assert(got_jan_heal == 1);
        g16->is_object_exists[3] = 0;

        // FUN_004034f0 dodge roll on frame 110
        g16->objects[0]->file = files16[7]; // DAVIS_DAT
        g16->objects[0]->frame_id1 = 110; g16->objects[0]->facing = FACING_RIGHT;
        g16->objects[0]->x = 200; g16->objects[0]->z = 200;
        g16->objects[1]->x = 350; g16->objects[1]->z = 200;
        g16->objects[0]->click_right = 0; g16->objects[0]->click_attack = 0;
        assert(FUN_004034f0(1, 0, 0, 0, 0, 0, 0) == 1);
        assert(g16->objects[0]->click_right == 1 && g16->objects[0]->click_attack == 1);

        // 16E. FUN_004094b0 (0x004094B0 master AI controller)
        DAT_00450bac = 1; DAT_00450bb4 = 2000;
        g16->objects[0]->ai_target_x = -1000; g16->objects[0]->blocked_right = 1;
        FUN_004094b0(0, 1);
        assert(g16->objects[0]->click_right == 1 && g16->objects[0]->click_attack == 1);
        DAT_00450bac = 0; g16->objects[0]->blocked_right = 0;

        // Waypoint arrival clears ai_target_x / ai_target_z
        g16->objects[0]->ai_target_x = 220; g16->objects[0]->ai_target_z = 200;
        FUN_004094b0(0, 0);
        assert(g16->objects[0]->ai_target_x == -1000 && g16->objects[0]->ai_target_z == -1000);

        // Defend oncoming flying ball (state 3000)
        files16[18]->frames[0].state = 3000;
        lf2_object_init(g16->objects[50]);
        g16->objects[50]->file = files16[18]; g16->objects[50]->frame_id1 = 0;
        g16->objects[50]->team = 2; g16->objects[50]->hp = 500;
        g16->objects[50]->x = 300; g16->objects[50]->z = 200; g16->objects[50]->x_velocity = -10.0;
        g16->is_object_exists[50] = 1; g16->is_object_exists[1] = 0;
        g16->objects[0]->x = 200; g16->objects[0]->z = 200; g16->objects[0]->facing = FACING_RIGHT;
        g16->objects[0]->frame_id1 = 0; g16->objects[0]->click_defend = 0;
        FUN_004094b0(0, 0);
        assert(g16->objects[0]->click_defend == 1);
        g16->is_object_exists[50] = 0; files16[18]->frames[0].state = 0;

        // Firen flame hazard avoidance & no-target cancel
        files16[19]->frames[0].state = STATE_BURNING;
        lf2_object_init(g16->objects[50]);
        g16->objects[50]->file = files16[19]; g16->objects[50]->frame_id1 = 0;
        g16->objects[50]->x = 240; g16->objects[50]->z = 210;
        g16->is_object_exists[50] = 1;
        g16->objects[1]->x = 400; g16->objects[1]->z = 210; g16->is_object_exists[1] = 1;
        g16->objects[0]->x = 200; g16->objects[0]->z = 200;
        FUN_004094b0(0, 0);
        assert(g16->objects[0]->click_down == 1);
        g16->is_object_exists[50] = 0; g16->is_object_exists[1] = 0; files16[19]->frames[0].state = 0;

        g16->objects[0]->file = files16[3]; g16->objects[0]->frame_id1 = 258;
        g16->objects[0]->click_defend = 0;
        FUN_004094b0(0, 0);
        assert(g16->objects[0]->click_defend == 1);

        // Cleanup and restore globals
        for (int i = 0; i < 24; ++i) free(files16[i]);
        free(f_chasef); free(f_chasei); free(f_jball);
        for (int s = 0; s < MAX_OBJECTS; ++s) free(g16->objects[s]);
        free(g16);

        DAT_00450c2c = saved_c2c;
        DAT_00450c30 = saved_c30;
        DAT_00450bb4 = saved_bb4;
        DAT_00450bac = saved_bac;
        lf2_bg_zmin = saved_zmin;
        lf2_bg_zmax = saved_zmax;
        DAT_00450bcc = saved_bcc;
        DAT_00450c34 = saved_c34;
        in_ECX = prev_ecx16;
        printf("    [PASS] Phase 20 AI Controller, opoint, hit_Fa, Weapons, Specials & Dodge verified!\n");
    }

    // ------------------------------------------------------------------------
    // TEST 17: Master Battle Frame Loop (0x0041BC90) & Supporting Helpers
    // ------------------------------------------------------------------------
    printf("\n[+] Test 17: Master Battle Frame Loop (0x0041BC90) & Helpers...\n");
    {
        void *prev_ecx17 = in_ECX;
        int saved_d020 = DAT_0044d020;
        int saved_d02c = DAT_0044d02c;
        int saved_d034 = DAT_0044d034;
        int saved_b80 = DAT_00450b80;
        int saved_b84 = DAT_00450b84;
        int saved_b88 = DAT_00450b88;
        int saved_b8c = DAT_00450b8c;
        int saved_b90 = DAT_00450b90;
        int saved_bb4 = DAT_00450bb4;
        int saved_bb8 = DAT_00450bb8;
        int saved_bbc = DAT_00450bbc;
        int saved_bc0 = DAT_00450bc0;
        int saved_bc4 = DAT_00450bc4;
        int saved_bd0 = DAT_00450bd0;
        int saved_bd4 = DAT_00450bd4;
        int saved_bd8 = DAT_00450bd8;
        int saved_bdc = DAT_00450bdc;
        int saved_be4 = DAT_00450be4;
        int saved_bfc = DAT_00450bfc;
        int saved_fb60 = DAT_0044fb60;
        int saved_fcb0 = DAT_0044fcb0;
        int saved_c28 = DAT_00450c28;
        int saved_c2c = DAT_00450c2c;
        int saved_c30 = DAT_00450c30;
        int saved_8428 = DAT_00458428;
        int saved_842c = DAT_0045842c;
        int saved_eecc = DAT_0044eecc;
        int saved_d000 = DAT_0044d000;
        int saved_f1af = DAT_0044f1af;
        int saved_d05c = DAT_0044d05c;

        // 17A. 0x0040D940 frame present & 0x00419E40 global_ctor
        global_t *g17 = (global_t *)calloc(1, sizeof(global_t));
        g17->game_state = 99;
        memset(g17->is_object_exists, 1, MAX_OBJECTS);
        in_ECX = g17;
        FUN_00419e40();
        assert(g17->game_state == 0 && g17->is_object_exists[0] == 0 && g17->is_object_exists[399] == 0);

        for (int s = 0; s < MAX_OBJECTS; ++s) {
            g17->objects[s] = (object_t *)calloc(1, sizeof(object_t));
            lf2_object_init(g17->objects[s]);
        }

        file_t *f_davis = (file_t *)calloc(1, sizeof(file_t));
        file_t *f_rudolf = (file_t *)calloc(1, sizeof(file_t));
        file_t *f_firen = (file_t *)calloc(1, sizeof(file_t));
        file_t *f_freeze = (file_t *)calloc(1, sizeof(file_t));
        file_t *f_firzen = (file_t *)calloc(1, sizeof(file_t));
        file_t *f_ball = (file_t *)calloc(1, sizeof(file_t));
        file_t *f_stick = (file_t *)calloc(1, sizeof(file_t));
        file_t *f_bw = (file_t *)calloc(1, sizeof(file_t));
        file_t *f_etc = (file_t *)calloc(1, sizeof(file_t));

        f_davis->id = ID_DAVIS_DAT; f_davis->type = TYPE_CHARACTER; f_davis->walking_frame_rate = 10;
        f_rudolf->id = ID_RUDOLF_DAT; f_rudolf->type = TYPE_CHARACTER;
        f_firen->id = ID_FIREN_DAT; f_firen->type = TYPE_CHARACTER;
        f_freeze->id = ID_FREEZE_DAT; f_freeze->type = TYPE_CHARACTER;
        f_firzen->id = ID_FIRZEN_DAT; f_firzen->type = TYPE_CHARACTER;
        f_ball->id = ID_JOHN_BALL_DAT; f_ball->type = TYPE_ATTACK;
        f_stick->id = ID_STICK_DAT; f_stick->type = TYPE_LIGHT_WEAPON; f_stick->weapon_hp = 100; f_stick->weapon_broken_sound_id = 3;
        f_bw->id = ID_BROKEN_WEAPON_DAT; f_bw->type = TYPE_ATTACK;
        f_etc->id = ID_ETC_DAT; f_etc->type = TYPE_ATTACK;

        for (int k = 0; k < 50; ++k) {
            f_davis->frames[k].wait = 5;
            f_rudolf->frames[k].wait = 5;
            f_ball->frames[k].wait = 5;
            f_bw->frames[k].wait = 5;
            f_etc->frames[k].wait = 5;
        }
        f_davis->frames[5].present = 1;
        f_davis->frames[6].present = 0;
        in_ECX = f_davis;
        assert(FUN_0040d940(5) == true && FUN_0040d940(6) == false);

        g17->files[0] = f_davis; g17->files[1] = f_rudolf; g17->files[2] = f_firen;
        g17->files[3] = f_freeze; g17->files[4] = f_firzen; g17->files[5] = f_ball;
        g17->files[6] = f_stick; g17->files[7] = f_bw; g17->files[8] = f_etc;

        // 17B. Function keys F1-F9 & cheat unlocks (0x416C70 - 0x416F60)
        uint8_t rec10[10] = {0};
        DAT_0044d020 = 0; DAT_00450bfc = 0; DAT_0044fb60 = 0; DAT_0044fcb0 = 0;
        DAT_00450c28 = 0; DAT_0044d02c = 1; DAT_0044d034 = 1; DAT_00450bdc = 0;
        DAT_00458428 = 0; DAT_0045842c = 0; DAT_00450bb8 = 0; DAT_00450bc0 = 0;
        DAT_00450b84 = 0; DAT_00450b88 = 0; DAT_00450b80 = 0; DAT_00450be4 = 0;

        int mode17 = 0; // VS Mode
        FUN_00416c70(rec10);
        assert(DAT_00458428 == 1 && (rec10[9] & 1) != 0);
        FUN_00416ca0(rec10);
        assert(DAT_0045842c == 1 && (rec10[9] & 2) != 0);
        FUN_00416dd0(&DAT_0044d020);
        assert(DAT_0044fb60 == 1 && DAT_0044fcb0 == 1);
        FUN_00416df0(&DAT_0044d020);
        assert(DAT_0044fcb0 == 1 && DAT_0044fb60 == 0);
        FUN_00416e30(0, &DAT_0044d020);
        assert(DAT_0044d02c == 0 && DAT_004553ec == 'u');
        FUN_00416e60(rec10, &DAT_0044d020, &mode17);
        assert(DAT_0044d034 == 0 && (rec10[8] & 0x10) != 0 && DAT_00450c28 == 1);
        FUN_00416eb0(rec10, &DAT_0044d020, &mode17);
        assert(DAT_00450bc0 == 1 && (rec10[8] & 0x20) != 0);
        FUN_00416f10(rec10, &DAT_0044d020, &mode17);
        assert(DAT_00450bb8 == 1 && (rec10[8] & 0x40) != 0);
        FUN_00416f60(rec10, &DAT_0044d020, &mode17);
        assert(DAT_00450bb8 == 2 && (rec10[8] & 0x80) != 0);
        FUN_00416e10(rec10, &DAT_0044d020);
        assert(DAT_00450c28 == 2 && (rec10[8] & 0x04) != 0);
        // Locked F-keys must not modify F6
        int prev_mp_flag = DAT_0044d034;
        FUN_00416e60(rec10, &DAT_0044d020, &mode17);
        assert(DAT_0044d034 == prev_mp_flag);
        // F4 exit in VS mode
        DAT_00450c28 = 0; DAT_00450bc0 = 0; DAT_00450bb8 = 0; DAT_00450bfc = 0; DAT_0044fb60 = 0; DAT_0044fcb0 = 0;
        FUN_00416cd0(&DAT_0044d020, &mode17);
        assert(DAT_00450bdc == 350);
        DAT_00450bdc = 0;

        // 17C. 0x00419E60 Spatialized Sound Flush math check
        DAT_0044eecc = 1;
        DAT_0044d000 = 80;
        DAT_00450bc4 = 0;
        memset(DAT_00457588, 0, sizeof(DAT_00457588));
        memset(DAT_00453e10, 0, sizeof(DAT_00453e10));
        // Queue item sound 3 at x = 600 -> left_dist = 400 (vol 0), right_dist = 0 (vol 100)
        FUN_00416fb0(600, 3);
        // Queue fixed sound 15 at x = 200 -> left_dist = 0 (vol 100), right_dist = 400 (vol 0)
        FUN_00417090(200, 15);
        FUN_00419e60();
        assert(DAT_00457588[3] == 0 && DAT_00453e10[15] == 0);
        assert(lf2_last_item_pan[3] == 1500);
        assert(lf2_last_item_vol[3] == -760);
        assert(lf2_last_fixed_pan[15] == -1500);
        assert(lf2_last_fixed_vol[15] == -760);

        // 17D. 0x0043DB40 / 0x0043DC50 / 0x0043DF00 / 0x0043D2A0 Replay 10-byte write/read & restore
        DAT_004588a8 = calloc(1, 0x630e18);
        DAT_004588ac = (intptr_t)(uintptr_t)calloc(1, 0x630e18);
        DAT_00450b8c = 42;
        uint8_t wr[10] = { 0x81, 0x41, 0x21, 0x11, 0x09, 0x05, 0x03, 0x01, 0x30, 0x01 };
        uint8_t rd[10] = {0};
        FUN_0043db40(wr);
        memcpy((uint8_t *)(uintptr_t)DAT_004588ac + 0x2b38 + 42 * 10, wr, 10);
        FUN_0043dc50(rd);
        assert(memcmp(wr, rd, 10) == 0);

        DAT_0045877c = 2;
        strcpy(DAT_00458850, "HeroOne");
        strcpy(DAT_004587e8, "Alice");
        strcpy(DAT_00458588, "Info");
        strcpy(DAT_00458780, "alice@lf2.test");
        FUN_0043df00();
        assert(DAT_00450c30 == 2 && strcmp(DAT_0044fcc0, "HeroOne") == 0);
        assert(strcmp(DAT_0044fd18, "Alice") == 0 && strcmp(DAT_0044f900, "Info") == 0);
        assert(strcmp(DAT_0044f890, "alice@lf2.test") == 0);
        FUN_0043d2a0();
        assert(DAT_004588a8 == NULL && DAT_004588ac == 0);

        // 17E. Master Battle Frame Loop (FUN_0041bc90):
        // Setup 2 characters on opposite teams, opoint group spawn, broken weapon shards, ice shatter, & healing
        memset(g17->is_object_exists, 0, MAX_OBJECTS);
        lf2_object_init(g17->objects[0]);
        lf2_object_init(g17->objects[1]);
        g17->is_object_exists[0] = 1;
        g17->is_object_exists[1] = 1;
        g17->objects[0]->file = f_davis; g17->objects[0]->team = 1; g17->objects[0]->x = 200; g17->objects[0]->z = 200;
        g17->objects[0]->x_position = 200.0; g17->objects[0]->z_position = 200.0;
        g17->objects[0]->x_velocity = 0.0; g17->objects[0]->y_velocity = 0.0; g17->objects[0]->z_velocity = 0.0;
        g17->objects[1]->file = f_davis; g17->objects[1]->team = 2; g17->objects[1]->x = 500; g17->objects[1]->z = 200;
        g17->objects[1]->x_position = 500.0; g17->objects[1]->z_position = 200.0;
        g17->objects[1]->x_velocity = 0.0; g17->objects[1]->y_velocity = 0.0; g17->objects[1]->z_velocity = 0.0;

        // Configure frame 14 -> frame 15 transition so FUN_0040d960 enters frame 15 with wait_counter == 0,
        // firing opoint to spawn 3 projectiles (facing = 30)
        f_davis->frames[14].wait = 1;
        f_davis->frames[14].next = 15;
        f_davis->frames[15].wait = 5;
        f_davis->frames[15].next = 0;
        f_davis->frames[15].opoint.kind = 1;
        f_davis->frames[15].opoint.oid = ID_JOHN_BALL_DAT;
        f_davis->frames[15].opoint.facing = 30;
        f_davis->frames[15].opoint.dvx = 6;
        g17->objects[0]->frame_id1 = 14;
        g17->objects[0]->frame_id2 = 14;
        g17->objects[0]->wait_counter = 1;

        // Put broken stick in slot 50 & ice-leaving object in slot 1 (pf = frame 20 -> state 13 -> frame 0)
        lf2_object_init(g17->objects[50]);
        g17->is_object_exists[50] = 1;
        g17->objects[50]->file = f_stick;
        g17->objects[50]->weapon_hp = -1;
        g17->objects[50]->x = 300; g17->objects[50]->z = 220;

        f_davis->frames[20].state = STATE_ICE;
        f_davis->frames[20].wait = 1;
        f_davis->frames[20].next = 999;
        g17->objects[1]->frame_id1 = 20;
        g17->objects[1]->frame_id2 = 20;
        g17->objects[1]->frame_id3 = 20;
        g17->objects[1]->wait_counter = 1; // Advances from 20 -> 999 -> 0 -> triggers ice shatter

        // Put state 1700 self-heal & whirlwind bleed setup: test Jan heal_timer
        g17->objects[0]->hp = 400;
        g17->objects[0]->dark_hp = 500;
        g17->objects[0]->heal_timer = 17; // decrements to 16 (% 8 == 0 -> +8 HP)

        DAT_00450b90 = 1; DAT_0044d020 = 0; DAT_0044f1af = 0; DAT_0044d05c = 0;
        DAT_00450b80 = 0; DAT_00450b84 = 0; DAT_00450b88 = 0; DAT_00450bbc = 0;
        DAT_00450bd0 = 0; DAT_00450bd4 = 0; DAT_00450bd8 = 0; DAT_00450bdc = 0;
        DAT_00451160 = 0; DAT_00450bb4 = 800; DAT_00453e10[15] = 0;
        lf2_last_fixed_played[15] = 0;

        in_ECX = g17;
        int rc17 = FUN_0041bc90();
        assert(rc17 == 0);
        assert(DAT_00450b90 == 0);
        assert(DAT_00450bbc == 1);
        // Weapon stick broke into 5 shards, opoint spawned 3 balls, ice shattered into 15 shards + data\066.wav
        assert(g17->is_object_exists[50] == 0); // broken weapon removed
        int shard_count = 0, ball_count = 0;
        for (int s = 50; s < MAX_OBJECTS; ++s) {
            if (g17->is_object_exists[s] && g17->objects[s] && g17->objects[s]->file) {
                if (g17->objects[s]->file->id == ID_BROKEN_WEAPON_DAT) shard_count++;
                if (g17->objects[s]->file->id == ID_JOHN_BALL_DAT) ball_count++;
            }
        }
        assert(ball_count == 3);
        assert(shard_count == 20); // 5 stick shards + 15 ice shards
        assert(lf2_last_fixed_played[15] == 1); // data\066.wav flushed on ice shatter
        assert(g17->objects[0]->hp >= 408); // Jan heal +8 applied

        // Test team order D-J-D-J (9,0,9,0) on slot 2 -> sets ally ai_target_x/z and spawns ID_ETC_DAT marker
        memset(g17->is_object_exists, 0, MAX_OBJECTS);
        lf2_object_init(g17->objects[0]); lf2_object_init(g17->objects[1]); lf2_object_init(g17->objects[2]);
        g17->is_object_exists[0] = 1; g17->is_object_exists[1] = 1; g17->is_object_exists[2] = 1;
        g17->objects[0]->file = f_davis; g17->objects[0]->team = 1; g17->objects[0]->x = 250; g17->objects[0]->z = 210;
        g17->objects[0]->x_velocity = 0.0; g17->objects[0]->y_velocity = 0.0; g17->objects[0]->z_velocity = 0.0;
        g17->objects[1]->file = f_davis; g17->objects[1]->team = 1;
        g17->objects[1]->x_velocity = 0.0; g17->objects[1]->y_velocity = 0.0; g17->objects[1]->z_velocity = 0.0;
        g17->objects[2]->file = f_davis; g17->objects[2]->team = 2; // enemy alive
        g17->objects[2]->x_velocity = 0.0; g17->objects[2]->y_velocity = 0.0; g17->objects[2]->z_velocity = 0.0;
        g17->objects[0]->input_history[1] = 9;
        g17->objects[0]->input_history[2] = 9;
        g17->objects[0]->input_history[3] = 9;
        g17->objects[0]->input_history[4] = 9; // D-D-D-D -> follow_order = 1
        in_ECX = g17;
        FUN_0041bc90();
        assert(g17->objects[1]->follow_order == 1);

        // Test round_counter >= 350 Firzen & Rudolf revert
        memset(g17->is_object_exists, 0, MAX_OBJECTS);
        lf2_object_init(g17->objects[0]);
        g17->is_object_exists[0] = 1;
        g17->objects[0]->file = f_firzen;
        g17->objects[0]->fusion_state = 1;
        g17->objects[0]->fusion_partner = 1;
        g17->objects[0]->fusion_self_id = ID_FIREN_DAT;
        g17->objects[0]->fusion_partner_id = ID_FREEZE_DAT;
        g17->objects[0]->hp = 100; g17->objects[0]->dark_hp = 100;
        DAT_00450bdc = 350;
        DAT_0044d020 = 0;
        DAT_00450b90 = 1;
        in_ECX = g17;
        int end_rc = FUN_0041bc90();
        assert(end_rc == 2);
        assert(g17->objects[0]->file->id == ID_FIREN_DAT);
        assert(g17->is_object_exists[1] == 1 && g17->objects[1]->file->id == ID_FREEZE_DAT);

        for (int s = 0; s < MAX_OBJECTS; ++s) free(g17->objects[s]);
        free(g17);
        free(f_davis); free(f_rudolf); free(f_firen); free(f_freeze);
        free(f_firzen); free(f_ball); free(f_stick); free(f_bw); free(f_etc);

        DAT_0044d020 = saved_d020; DAT_0044d02c = saved_d02c; DAT_0044d034 = saved_d034;
        DAT_00450b80 = saved_b80; DAT_00450b84 = saved_b84; DAT_00450b88 = saved_b88;
        DAT_00450b8c = saved_b8c; DAT_00450b90 = saved_b90; DAT_00450bb4 = saved_bb4;
        DAT_00450bb8 = saved_bb8; DAT_00450bbc = saved_bbc; DAT_00450bc0 = saved_bc0;
        DAT_00450bc4 = saved_bc4; DAT_00450bd0 = saved_bd0; DAT_00450bd4 = saved_bd4;
        DAT_00450bd8 = saved_bd8; DAT_00450bdc = saved_bdc; DAT_00450be4 = saved_be4;
        DAT_00450bfc = saved_bfc; DAT_0044fb60 = saved_fb60; DAT_0044fcb0 = saved_fcb0;
        DAT_00450c28 = saved_c28; DAT_00450c2c = saved_c2c; DAT_00450c30 = saved_c30;
        DAT_00458428 = saved_8428; DAT_0045842c = saved_842c;
        DAT_0044eecc = saved_eecc; DAT_0044d000 = saved_d000;
        DAT_0044f1af = saved_f1af; DAT_0044d05c = saved_d05c;
        in_ECX = prev_ecx17;
        printf("    [PASS] Master Battle Frame Loop, F-keys, Sound Flush & Replay Helpers verified!\n");
    }

    // 25. Test Camera & Stage Bounds (0x0041b5d0 / FUN_0041b5d0)
    printf("[+] Testing Camera & Stage Bounds (0x0041b5d0 / lf2_camera_stage_bounds)...\n");
    {
        int saved_d024 = DAT_0044d024;
        int saved_b4c[8];
        for (int i = 0; i < 8; ++i) saved_b4c[i] = DAT_00450b4c[i];
        int saved_bb0 = DAT_00450bb0, saved_bb4 = DAT_00450bb4;
        int saved_bc4 = DAT_00450bc4, saved_bc8 = DAT_00450bc8;
        int saved_b74 = DAT_00450b74, saved_b7c = DAT_00450b7c, saved_b84 = DAT_00450b84;
        int saved_b94 = DAT_00450b94;
        void *prev_ecx25 = in_ECX;

        global_t *g25 = (global_t *)calloc(1, sizeof(global_t));
        uint8_t *bg_mgr = (uint8_t *)calloc(1, 0x4d46800);
        file_t *f_char = (file_t *)calloc(1, sizeof(file_t));
        file_t *f_atk  = (file_t *)calloc(1, sizeof(file_t));
        file_t *f_milk = (file_t *)calloc(1, sizeof(file_t));
        file_t *f_stk  = (file_t *)calloc(1, sizeof(file_t));
        object_t *p0 = (object_t *)calloc(1, sizeof(object_t));
        object_t *e5 = (object_t *)calloc(1, sizeof(object_t));
        object_t *c25 = (object_t *)calloc(1, sizeof(object_t));
        object_t *proj = (object_t *)calloc(1, sizeof(object_t));
        object_t *milk = (object_t *)calloc(1, sizeof(object_t));
        object_t *stick_oob = (object_t *)calloc(1, sizeof(object_t));
        assert(g25 && bg_mgr && f_char && f_atk && f_milk && f_stk && p0 && e5 && c25 && proj && milk && stick_oob);

        f_char->type = TYPE_CHARACTER;
        f_char->frames[0].state = STATE_STANDING;
        f_atk->type = TYPE_ATTACK;
        f_milk->type = TYPE_DRINK; f_milk->id = ID_MILK_DAT;
        f_stk->type = TYPE_LIGHT_WEAPON; f_stk->id = ID_STICK_DAT;

        DAT_0044d024 = 0;
        *(int32_t *)(bg_mgr + 0x4d45db0) = 2400; /* bg_width */
        *(int32_t *)(bg_mgr + 0x4d45db4) = 300;  /* bg_zmin */
        *(int32_t *)(bg_mgr + 0x4d45db8) = 450;  /* bg_zmax */
        *(int32_t *)(bg_mgr + 0x4d45dcc) = 0;    /* layer_count = 0 (skip draw blits) */
        g25->files[0] = (file_t *)(uintptr_t)bg_mgr;

        /* Slot 0: team 1 player below X=0 and Z<zmin, facing right */
        lf2_object_init(p0); p0->file = f_char; p0->hp = 500; p0->team = 1;
        p0->facing = FACING_RIGHT; p0->x_position = -20.0; p0->z_position = 250.0;
        g25->is_object_exists[0] = 1; g25->objects[0] = p0;

        /* Slot 1: team 5 enemy allowed down to -300 */
        lf2_object_init(e5); e5->file = f_char; e5->hp = 500; e5->team = 5;
        e5->x_position = -250.0; e5->z_position = 500.0;
        g25->is_object_exists[1] = 1; g25->objects[1] = e5;

        /* Slot 25: character >= 20 clamped by DAT_00450bb4 when not blinking */
        lf2_object_init(c25); c25->file = f_char; c25->hp = 500; c25->team = 1; c25->blink_time = 0;
        c25->x_position = 1100.0; c25->z_position = 350.0;
        g25->is_object_exists[25] = 1; g25->objects[25] = c25;

        /* Slot 50: projectile beyond bg_width + 300 despawns */
        lf2_object_init(proj); proj->file = f_atk;
        proj->x_position = 2701.0; proj->z_position = 290.0;
        g25->is_object_exists[50] = 1; g25->objects[50] = proj;

        /* Slot 51: Milk in survival stage (50..59) clamped to [10, width - 10] and Z extended +-1 */
        lf2_object_init(milk); milk->file = f_milk; milk->player_index = 0;
        milk->x_position = 2.0; milk->z_position = 295.0;
        g25->is_object_exists[51] = 1; g25->objects[51] = milk;

        /* Slot 52: Dropped stick out of bounds at y==0 despawns */
        lf2_object_init(stick_oob); stick_oob->file = f_stk; stick_oob->y = 0;
        stick_oob->x_position = -5.0; stick_oob->z_position = 460.0;
        g25->is_object_exists[52] = 1; g25->objects[52] = stick_oob;

        DAT_00450b4c[0] = 1;
        for (int i = 1; i < 8; ++i) DAT_00450b4c[i] = -1;
        DAT_00450bb4 = 900;
        DAT_00450bb0 = 0;
        DAT_00450bc4 = 0;
        DAT_00450bc8 = 0;
        DAT_00450b74 = 0; DAT_00450b84 = 0;
        DAT_00450b94 = 50; /* Survival stage 5-1 */

        in_ECX = g25;
        FUN_0041b5d0(NULL, 1);

        assert(p0->z == 300 && p0->x == 0);
        assert(e5->z == 450 && e5->x == -250);
        assert(c25->x == 900);
        assert(g25->is_object_exists[50] == 0);
        assert(milk->z == 299 && milk->x == 10);
        assert(g25->is_object_exists[52] == 0);

        /* Verify camera target with lying player + DAT_00450bb0 phase camera lock */
        p0->x_position = 1500.0; p0->x = 1500;
        f_char->frames[0].state = STATE_LYING;
        DAT_00450bb4 = 0;
        DAT_00450bb0 = 700;
        DAT_00450bc4 = 0; DAT_00450bc8 = 0;
        lf2_camera_stage_bounds(g25, NULL, 0);
        assert(DAT_00450bc8 == 7); /* ((700 - 0) / 14 + 0) / 7 = 50 / 7 = 7 */
        assert(DAT_00450bc4 == 7);

        free(p0); free(e5); free(c25); free(proj); free(milk); free(stick_oob);
        free(f_char); free(f_atk); free(f_milk); free(f_stk);
        free(bg_mgr); free(g25);

        DAT_0044d024 = saved_d024;
        for (int i = 0; i < 8; ++i) DAT_00450b4c[i] = saved_b4c[i];
        DAT_00450bb0 = saved_bb0; DAT_00450bb4 = saved_bb4;
        DAT_00450bc4 = saved_bc4; DAT_00450bc8 = saved_bc8;
        DAT_00450b74 = saved_b74; DAT_00450b7c = saved_b7c; DAT_00450b84 = saved_b84;
        DAT_00450b94 = saved_b94;
        in_ECX = prev_ecx25;
        printf("    [PASS] Camera & Stage Bounds (0x0041b5d0) verified!\n");
    }

    // 26. Test Core Joystick Slot Layout & Ad-Thread State Linkage (0x0043bf10..0x0043c450)
    printf("[+] Testing Core Joystick Layout & WinINet Ad-Thread State Guard (0x0043bf10..0x0043c450)...\n");
    {
        assert(sizeof(lf2_joy_slot_t) == 0x30);
        assert((char *)&lf2_joy_slots[0].up == DAT_00453ff0);
        assert((char *)&lf2_joy_slots[1].up == DAT_00453ff0 + 0x30);

        /* Pre-seed slot calibration & button bytes, invoke FUN_0043bf10, verify reset semantics */
        lf2_joy_slots[0].left = 'd';
        lf2_joy_slots[0].buttons[2] = 'd';
        lf2_joy_slots[2].left = 'u';
        lf2_joy_slots[2].connected = 1;
        lf2_joy_slots[2].xcenter = 32768;
        lf2_joy_slots[2].ycenter = 32768;
        lf2_joy_slots[2].buttons[0] = 'd';
        lf2_joy_slots[2].buttons[5] = 'd';
        FUN_0043bf10();
        assert(lf2_joy_slots[2].connected == 0);
        assert(lf2_joy_slots[2].xcenter == 0 && lf2_joy_slots[2].ycenter == 0);
        assert(lf2_joy_slots[2].up == 'u' && lf2_joy_slots[2].down == 'u' &&
               lf2_joy_slots[2].right == 'u' && lf2_joy_slots[2].left == 'u');
        assert(lf2_joy_slots[2].buttons[0] == 0 && lf2_joy_slots[2].buttons[5] == 0);

        /* Verify ad_thread_start respects non-zero DAT_00458424 without spawning a network thread */
#ifdef _WIN32
        InitializeCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
        int saved_ad_state = DAT_00458424;
        DAT_00458424 = 2;
        FUN_0043c450();
        assert(DAT_00458424 == 2);
        DAT_00458424 = saved_ad_state;
        DeleteCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
#endif
        /* Reference http_download symbol so linker pulls in 0x0043c0c0 cleanly without live HTTP */
        assert(FUN_0043c0c0(NULL, NULL, NULL) == 0);
        printf("    [PASS] Core joystick slots & HTTP ad-thread linkage verified!\n");
    }

    // 27. Test Remaining Data Loaders & Cipher CLI (0x0040bd90, 0x00414450, 0x00414b70, 0x0040c160, 0x0040c910, 0x004122f0)
    printf("[+] Testing Remaining Data Loaders & Cipher CLI (0x0040bd90..0x00414b70)...\n");
    {
        /* 27a. load_dat_sound_slot (0x0040bd90) deduplication */
        int saved_sound_cnt = DAT_00458438;
        int saved_eecc = DAT_0044eecc;
        DAT_00458438 = 0;
        DAT_0044eecc = 0;
        memset(DAT_00455638, 0, sizeof(DAT_00455638));

        int slot_a = -1, slot_b = -1, slot_a2 = -1;
        FUN_0040bd90("data\\001.wav", &slot_a);
        FUN_0040bd90("data\\002.wav", &slot_b);
        FUN_0040bd90("data\\001.wav", &slot_a2);
        assert(slot_a == 0 && slot_b == 1 && slot_a2 == 0);
        assert(DAT_00458438 == 2);
        assert(strcmp(&DAT_00455638[0], "data\\001.wav") == 0);
        assert(strcmp(&DAT_00455638[20], "data\\002.wav") == 0);

        DAT_00458438 = saved_sound_cnt;
        DAT_0044eecc = saved_eecc;

        /* 27b. cipher_cli_vk_to_char (0x00414450) */
        char saved_shift = DAT_00455388;
        DAT_00455388 = 'u';
        assert(FUN_00414450(' ') == ' ');
        assert(FUN_00414450(0x65) == '5');
        assert(FUN_00414450(0x6b) == '+');
        assert(FUN_00414450(0xbd) == '-');
        assert(FUN_00414450('3') == '3');
        DAT_00455388 = 'd';
        assert(FUN_00414450('A') == 'A');
        assert(FUN_00414450('2') == '@');
        assert(FUN_00414450(0xbd) == '_');
        assert(FUN_00414450(0xbc) == '<');
        DAT_00455388 = saved_shift;

        /* 27c. dat_cipher_cli (0x00414b70) state machine & encrypt/decrypt round-trip + bg/stage/data loaders */
#ifdef _WIN32
        _mkdir("data");
#endif
        int had_orig_stage = 0;
        char *orig_stage_buf = NULL;
        size_t orig_stage_len = 0;
        {
            FILE *existing_stage = fopen("data\\stage.dat", "rb");
            if (existing_stage) {
                had_orig_stage = 1;
                fseek(existing_stage, 0, SEEK_END);
                long sz = ftell(existing_stage);
                fseek(existing_stage, 0, SEEK_SET);
                if (sz > 0) {
                    orig_stage_len = (size_t)sz;
                    orig_stage_buf = (char *)malloc(orig_stage_len);
                    assert(orig_stage_buf != NULL);
                    size_t got = fread(orig_stage_buf, 1, orig_stage_len, existing_stage);
                    assert(got == orig_stage_len);
                }
                fclose(existing_stage);
            }
        }

        const char *cli_txt = "data\\_test_cli_in.txt";
        const char *cli_dat = "data\\_test_cli_in.dat";
        {
            FILE *f = fopen(cli_txt, "w");
            assert(f != NULL);
            fprintf(f, "name: test_cli\n");
            fclose(f);
        }

        int saved_f820 = DAT_0044f820;
        int saved_f81c = DAT_0044f81c;
        char saved_keys[300];
        memcpy(saved_keys, DAT_00455378, sizeof(saved_keys));

        memset(DAT_00455378, 'u', sizeof(DAT_00455378));
        DAT_00455388 = 'u';
        DAT_0044f820 = 0;
        DAT_004553bd = 'd'; /* 'E' -> enter encrypt mode */
        FUN_00414b70();
        assert(DAT_0044f820 == 1);

        /* Type cli_txt + dummy char + backspace via DAT_00455378, then VK_RETURN */
        for (size_t i = 0; i < strlen(cli_txt); ++i) {
            char c = cli_txt[i];
            memset(DAT_00455378, 'u', sizeof(DAT_00455378));
            if (c >= 'a' && c <= 'z') {
                DAT_00455388 = 'u';
                DAT_00455378[(unsigned char)(c - 'a' + 'A')] = 'd';
            } else if (c == '\\') {
                DAT_00455388 = 'u';
                DAT_00455378[0xdc] = 'd';
            } else if (c == '_') {
                DAT_00455388 = 'd';
                DAT_00455378[0xbd] = 'd';
            } else if (c == '.') {
                DAT_00455388 = 'u';
                DAT_00455378[0xbe] = 'd';
            }
            FUN_00414b70();
        }
        /* Extra char + VK_BACK removes extra char */
        DAT_00455388 = 'u';
        DAT_00455378['X'] = 'd';
        FUN_00414b70();
        DAT_00455378[8] = 'd';
        FUN_00414b70();
        assert(strcmp(DAT_0044f628, cli_txt) == 0);

        DAT_00455385 = 'd'; /* VK_RETURN -> encrypt */
        FUN_00414b70();
        assert(DAT_0044f820 == 0);

        /* Decrypt via CLI mode 2 */
        memset(DAT_00455378, 'u', sizeof(DAT_00455378));
        DAT_004553bc = 'd'; /* 'D' -> enter decrypt mode */
        FUN_00414b70();
        assert(DAT_0044f820 == 2);
        strcpy(DAT_0044f628, cli_dat);
        DAT_0044f81c = (int)strlen(cli_dat);
        DAT_00455385 = 'd';
        FUN_00414b70();
        assert(DAT_0044f820 == 0);
        {
            FILE *dec = fopen("data\\temporary.txt", "r");
            assert(dec != NULL);
            char buf[64] = {0};
            fgets(buf, sizeof(buf), dec);
            fclose(dec);
            assert(strstr(buf, "name: test_cli") != NULL);
        }

        memcpy(DAT_00455378, saved_keys, sizeof(saved_keys));
        DAT_00455388 = saved_shift;
        DAT_0044f820 = saved_f820;
        DAT_0044f81c = saved_f81c;
        remove(cli_txt);
        remove(cli_dat);

        /* 27d. load_bg_dat (0x0040c160), stage_dat_loader (0x0040c910), load_data_txt (0x004122f0) */
        const char *bg_test_path = "data\\_test_bg.txt";
        const char *stage_test_txt = "data\\_test_stage.txt";
        const char *manifest_test_path = "data\\_test_data.txt";
        {
            FILE *f = fopen(bg_test_path, "w");
            assert(f != NULL);
            fprintf(f,
                "name: Lion_Forest\n"
                "width: 1600\n"
                "zboundary: 320 480\n"
                "perspective: 10 20\n"
                "layer:\n"
                "bg\\test.bmp\n"
                "transparency: 1\n"
                "width: 800\n"
                "x: 15\n"
                "y: 25\n"
                "height: 120\n"
                "rect: 2016\n"
                "loop: 200\n"
                "cc: 10\n"
                "c1: 2\n"
                "c2: 8\n"
                "layer_end\n");
            fclose(f);
        }
        {
            FILE *f = fopen(stage_test_txt, "w");
            assert(f != NULL);
            fprintf(f,
                "<stage>\n"
                "id: 0\n"
                "<phase>\n"
                "bound: 900\n"
                "music: bgm\\stage1.wma\n"
                "id: 30 hp: 350 x: 960 y: 0 times: 2 reserve: 1 join: 100 join_reserve: 1 act: 12 ratio: 0.5 <boss>\n"
                "id: 31 <soldier>\n"
                "when_clear_goto_phase: 2\n"
                "<phase_end>\n"
                "<stage_end>\n");
            fclose(f);
            FUN_004146b0(stage_test_txt);
            remove("data\\stage.dat");
            rename("data\\_test_stage.dat", "data\\stage.dat");
        }
        {
            FILE *f = fopen(manifest_test_path, "w");
            assert(f != NULL);
            fprintf(f,
                "<object>\n"
                "<object_end>\n"
                "<background>\n"
                "id: 0 file: %s\n"
                "<background_end>\n",
                bg_test_path);
            fclose(f);
        }

        uint8_t *mgr = (uint8_t *)calloc(1, 0x4d82500);
        assert(mgr != NULL);
        int saved_f620 = DAT_0044f620;
        void *prev_ecx27 = in_ECX;
        in_ECX = mgr;
        DAT_0044f620 = 0;

        FUN_004122f0(manifest_test_path, 0);

        /* Verify default arena slot 99 */
        assert(*(int32_t *)(mgr + 0x4d81060) == 2400);
        assert(*(int32_t *)(mgr + 0x4d81064) == 350);
        assert(*(int32_t *)(mgr + 0x4d81068) == 470);
        assert(strcmp((char *)(mgr + 0x4d8142c), "Lee On Road") == 0);
        assert(strcmp((char *)(mgr + 0x4d81dbc), "Random") == 0);
        assert(*(int32_t *)(mgr + 0x4d82384) == 1); /* 1 background parsed */

        /* Verify parsed background slot 0 */
        assert(strcmp((char *)(mgr + 0x4d4617c), "Lion Forest") == 0);
        assert(*(int32_t *)(mgr + 0x4d45db0) == 1600);
        assert(*(int32_t *)(mgr + 0x4d45db4) == 320);
        assert(*(int32_t *)(mgr + 0x4d45db8) == 480);
        assert(*(int32_t *)(mgr + 0x4d45dbc) == 10);
        assert(*(int32_t *)(mgr + 0x4d45dc0) == 20);
        assert(*(int32_t *)(mgr + 0x4d45dcc) == 1);
        assert(*(int32_t *)(mgr + 0x4d4619c) == 1); /* transparency */
        assert(*(int32_t *)(mgr + 0x4d46214) == 800); /* layer width */
        assert(*(int32_t *)(mgr + 0x4d4628c) == 15); /* x */
        assert(*(int32_t *)(mgr + 0x4d46304) == 25); /* y */
        assert(*(int32_t *)(mgr + 0x4d4637c) == 120); /* height */
        assert(*(int32_t *)(mgr + 0x4d463f4) == 200); /* loop */
        assert(*(int32_t *)(mgr + 0x4d4655c) == 10); /* cc */
        assert(*(int32_t *)(mgr + 0x4d4646c) == 2); /* c1 */
        assert(*(int32_t *)(mgr + 0x4d464e4) == 8); /* c2 */
        /* rect: 2016 (0x07e0, G6=63) -> (63 * 0x400) + 0x070707 = 0x00080307 */
        assert(*(uint32_t *)(mgr + 0x4d4664c) == 0x00080307U);
        assert(DAT_0044f620 != 0);

        /* Verify parsed stage 0 phase 0 */
        assert(*(int32_t *)(mgr + 0x7d0) == 1); /* 1 phase */
        assert(*(int32_t *)(mgr + 0x7d8) == 900); /* bound */
        assert(strcmp((char *)(mgr + 0x7dc), "bgm\\stage1.wma") == 0);
        assert(*(int32_t *)(mgr + 0x3c90) == 2); /* when_clear_goto_phase */
        assert(*(int32_t *)(mgr + 0x8bc) == 30); /* spawn 0 id */
        assert(*(int32_t *)(mgr + 0x8c0) == 960); /* spawn 0 x */
        assert(*(int32_t *)(mgr + 0x8c4) == 350); /* spawn 0 hp */
        assert(*(int32_t *)(mgr + 0x8c8) == 2);   /* spawn 0 times */
        assert(*(int32_t *)(mgr + 0x8cc) == 1);   /* spawn 0 reserve */
        assert(*(int32_t *)(mgr + 0x8d0) == 100); /* spawn 0 join */
        assert(*(int32_t *)(mgr + 0x8d4) == 1);   /* spawn 0 join_reserve */
        assert(*(int32_t *)(mgr + 0x8d8) == 12);  /* spawn 0 act */
        assert(*(int32_t *)(mgr + 0x8e8) == 2);   /* spawn 0 boss role */
        assert(fabs(*(double *)(mgr + 0x8e0) - 0.5) < 1e-9);
        assert(*(int32_t *)(mgr + 0x8bc + 0xe0) == 31);  /* spawn 1 id */
        assert(*(int32_t *)(mgr + 0x8c0 + 0xe0) == 980); /* bound + 80 default x */
        assert(*(int32_t *)(mgr + 0x8c8 + 0xe0) == 50);  /* soldier times=50 */
        assert(*(int32_t *)(mgr + 0x8e8 + 0xe0) == 1);   /* soldier role=1 */

        free(mgr);
        in_ECX = prev_ecx27;
        DAT_0044f620 = saved_f620;

        remove(bg_test_path);
        remove(stage_test_txt);
        remove(manifest_test_path);
        remove("data\\temporary.txt");
        if (had_orig_stage) {
            FILE *restore = fopen("data\\stage.dat", "wb");
            if (restore && orig_stage_buf) {
                fwrite(orig_stage_buf, 1, orig_stage_len, restore);
                fclose(restore);
            }
            free(orig_stage_buf);
        } else {
            remove("data\\stage.dat");
        }
        printf("    [PASS] Sound slot cache, BG/Stage/Data loaders & Cipher CLI verified!\n");
    }

    printf("\n[SUCCESS] All Decompiled Compilable Suite Tests Passed with 100%% Parity!\n");
    return 0;
}

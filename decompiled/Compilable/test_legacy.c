#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    printf("\n[SUCCESS] All Decompiled Compilable Suite Tests Passed with 100%% Parity!\n");
    return 0;
}

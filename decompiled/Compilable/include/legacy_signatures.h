#ifndef LEGACY_SIGNATURES_H
#define LEGACY_SIGNATURES_H

#include "legacy_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Human-readable function signatures
int  lf2_abs(int val);
int  lf2_random(unsigned int seed_hint, int range);
int  lf2_overlap(int bdy_x, int bdy_y, int bdy_w, int bdy_h,
                 int itr_x, int itr_y, int itr_w, int itr_h);
void lf2_teleport(global_t *global, int teleported_id, int teleport_to);
void lf2_object_init(object_t *obj);
void lf2_grapple_sync(global_t *global, uint32_t catcher_id);
void lf2_weapon_sync(global_t *global, uint32_t char_id);
void lf2_does_attack_success(global_t *global, uint32_t attacker_id, uint32_t injured_id, uint32_t mode);
void lf2_frame_ctor(frame_t *frame);
int  lf2_file_ctor(file_t *file, undefined4 param_1, undefined4 param_2, const char *dat_path);
void lf2_menu_check_player_join_input(global_t *global);
void lf2_menu_reset_input_and_keys(global_t *global);
int *lf2_stage_advance(global_t *global);

// Comprehensive inventory of all decompiled function signatures
int  FUN_00401000();
int  FUN_004011d0();
int  FUN_00401250();
int  FUN_00401300();
int  FUN_004014e0();
int  FUN_00401970();
void FUN_00401a30();
void FUN_00401ae0();
HWND FUN_00401b00();
HWND FUN_00401bf0();
int  FUN_00401c90(void);
void FUN_00401d30(void);
void FUN_00401da0(const char *param_1);
void FUN_00401e90(void);
int  FUN_00401f30(int vol);
void FUN_00402000(void);
void FUN_00402020(const char *param_1);
void FUN_004028a0(void);
int  FUN_00402980();
void FUN_00402b60(HWND);
int  FUN_00402b80();
void FUN_00403270();
int  FUN_004034e0();
void FUN_004061d0();
void FUN_004064d0(void);
void FUN_004068b0();
void FUN_00406ba0();
void FUN_00408cb0(void);
void FUN_00408ce0();
void FUN_0040bbf0();
void FUN_0040bd90();
void FUN_0040be70();
void FUN_0040d0a0();
void FUN_0040ef70();
int  FUN_004143d0();
void FUN_004146b0();
void FUN_004148a0();
void FUN_00414a30();
void FUN_00414b70();
void FUN_004151d0();
void FUN_00415d00();
void FUN_00416fb0();
void FUN_00417090();
int  FUN_00417170();
int  FUN_004171c0(int, int, int, int, int, int, int, int);
void FUN_00417400();
int  FUN_0041a250(void);
int  FUN_0041a2dd();
int  FUN_0041bc90(void);
int  FUN_0041c5f0();
int  FUN_00423480();
void FUN_004242e0();
void FUN_004246b0();
void FUN_00429730(void);
void FUN_0042d080();
void FUN_0042e100();
void FUN_00436900();
long FUN_0043b3d0();
undefined4 FUN_0043bdd0();
undefined4 FUN_0043bec0();
int  FUN_0043bf10();
int  FUN_0043c4a0();
int  FUN_0043c690();
int  FUN_0043c780();
int  FUN_0043cc60();
undefined4 FUN_0043cf40();
void FUN_0043d230();
void FUN_0043e890();
int  FUN_0043e8e0();
int  FUN_0043e9a0();
int  FUN_0043ee50();
int  FUN_0043ef70();
int  FUN_0043f010();
void FUN_00401290();
void FUN_004019b0();
void FUN_00402100(void);
void FUN_00402130(int param_1, int param_2, int param_3, void *param_4);
void FUN_004025b0(void);
void FUN_004025d0(int track_id);
void func_00402020_bgm_play(const char *filepath);
void func_004025d0_bgm_select(int track_id);
void FUN_0040c030();
void FUN_0040c0e0();
void FUN_00415160();
void FUN_00422b00();
void FUN_004236d0();
void FUN_00423840();
void FUN_00423910();
void FUN_00423b00();
void FUN_00431b70();
void FUN_00431c70();
void FUN_00431d10();
void FUN_00432ab0();
void FUN_0043d280();
void FUN_0043d2c0();
void FUN_0043dd60(void);
int  FUN_0043e620(char *param_1);
void FUN_0043dfa0();
int  FUN_0043f4b0(void *dst, unsigned long *dst_len, const void *src, unsigned long src_len);
int  FUN_0043f4d0(void *dst, unsigned long *dst_len, const void *src, unsigned long src_len);
void lf2_replay_cipher_encrypt(uint8_t *buffer, size_t size);
void lf2_replay_cipher_decrypt(uint8_t *buffer, size_t size);
int  FUN_004450d0();
void FUN_00434ab0();
int* FUN_00436fc0();
void FUN_00437220(undefined4 param_1, undefined4 *param_2);
void FUN_00437400();
void FUN_00437860();
void FUN_004389a0();
void FUN_00438ad0();
void FUN_00438b40();

// Phase 17: Key Reconfiguration & Display Options
void lf2_get_key_name(int key_code, char *out_name, int *out_width_adj);
char lf2_vk_to_ascii(int key_code);
void lf2_options_screen(void *param_1);
int  FUN_00422ac0(void);
void FUN_00422b00(int key_code, char *out_name, int *out_width_adj);
char FUN_00422f60(int key_code);
void FUN_00423230(void);
void FUN_004237e0(void);
void FUN_00423940(char *str, int x, int y, int max_chars, int max_lines, int mode, int cursor);
void FUN_00423a70(char *str, int x, int y, int max_chars, int max_lines, int mode, int cursor);
int  func_00423480_load_control_txt(void);
int  func_004233e0_save_control_txt(void);

#ifdef __cplusplus
}
#endif

#endif // LEGACY_SIGNATURES_H

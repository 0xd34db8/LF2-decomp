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
bool lf2_frame_is_present(const file_t *file, int frame_id);
bool FUN_0040d940(int frame_id);
void lf2_global_ctor(global_t *global);
void FUN_00419e40(void);
void FUN_00419e60(void);
int  lf2_file_ctor(file_t *file, undefined4 param_1, undefined4 param_2, const char *dat_path);
void lf2_menu_check_player_join_input(global_t *global);
void lf2_menu_reset_input_and_keys(global_t *global);
int *lf2_stage_advance(global_t *global);
void lf2_object_frame_advance(object_t *obj, int mode, int obj_idx);
int  lf2_combo_interrupted(const object_t *obj, char expected_key, int advanced);
int  lf2_frame_transition(object_t *obj, int target_frame);
void lf2_input_history_push(object_t *obj, uint32_t key_code);
void lf2_object_physics_tick(object_t *obj);
void lf2_object_input_tick(object_t *obj);

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
void FUN_00402810(int param_1);
void FUN_004028a0(void);
int  FUN_00402980();
int  FUN_00402ad0(char **addr_list);
void FUN_00402b60(HWND);
int  FUN_00402b80();
void FUN_00403270();
int  FUN_004034e0();
int  FUN_004034f0(int target_id, int self_id, int param_3, int param_4, int param_5, int param_6, int param_7);
int  FUN_00403a40();
int  FUN_004061a0(int a, int b, int c);
void FUN_004061d0();
void FUN_004064d0(void);
void FUN_004068b0();
int  FUN_00406a20();
void FUN_00406ba0();
int  FUN_00408cb0();
void FUN_00408ce0();
void FUN_004094b0();
void FUN_0040bbf0();
void FUN_0040bd90();
void FUN_0040be70();
int  FUN_0040bf30(int frame_id);
void FUN_0040d0a0();
void FUN_0040d960(int param_1, int param_2);
void FUN_0040de30(int camera_x, void *dest_surface, int shake_dir);
int  FUN_0040e170(char param_1, int param_2);
int  FUN_0040e2d0(int param_1);
void FUN_0040e450(undefined4 param_1);
void FUN_0040e490(void);
void FUN_0040ef70();
void FUN_00412800(void);
void FUN_004128f0(void);
void FUN_004129e0(void);
void FUN_00412ac0(void);
void FUN_00412ba0(void);
void FUN_00412c90(void);
void FUN_00412d80(void);
void FUN_00412e60(void);
void FUN_00412f40(void);
void FUN_00413080(undefined4 param_1, undefined4 param_2);
int  FUN_004143d0();
void FUN_004146b0();
void FUN_004148a0();
void FUN_00414a30();
void FUN_00414b70();
void FUN_004151d0();
void FUN_00415d00();
void FUN_00416c70(uint8_t *replay_rec);
void FUN_00416ca0(uint8_t *replay_rec);
void FUN_00416cd0(int *out_ret, int *game_mode);
void FUN_00416dd0(int *net_blocked);
void FUN_00416df0(int *net_blocked);
void FUN_00416e10(uint8_t *replay_rec, int *net_blocked);
void FUN_00416e30(undefined4 unused, int *net_blocked);
void FUN_00416e60(uint8_t *replay_rec, int *net_blocked, int *game_mode);
void FUN_00416eb0(uint8_t *replay_rec, int *net_blocked, int *game_mode);
void FUN_00416f10(uint8_t *replay_rec, int *net_blocked, int *game_mode);
void FUN_00416f60(uint8_t *replay_rec, int *net_blocked, int *game_mode);
void FUN_00416fb0();
void FUN_00417090();
int  FUN_00417170();
int  FUN_004171c0(int, int, int, int, int, int, int, int);
int  FUN_00417200(int param_1, int param_2);
void FUN_00417400();
void FUN_00417f80();
void FUN_004187b0();
void FUN_00418c30();
void FUN_00419380(int param_1);
void FUN_004196f0(void);
void FUN_004197a0(const uint8_t *param_1, int param_2);
void FUN_004198f0(uint8_t *param_1, int param_2, int param_3);
void FUN_00419a60(int param_1, int param_2, uint8_t *param_3);
int  FUN_0041a250();
int  FUN_0041a2dd();
void FUN_0041a5a0(void *param_1, int param_2);
int  FUN_0041bc90(void);
int  lf2_battle_frame_tick(global_t *global, int *game_mode);
int  FUN_0041c5f0();
int  FUN_00423480();
void FUN_004242e0();
void FUN_004246b0();
void FUN_00429730(void);
void FUN_0042d080();
void lf2_attack_process(global_t *global, int attacker_id);
void FUN_0042e100(int param_1);
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
void FUN_0043d280(void *ptr_slot);
void FUN_0043d2a0(void);
void FUN_0043d2c0();
void FUN_0043db40(const uint8_t *frame_bytes);
void FUN_0043dc50(uint8_t *out_frame_bytes);
void FUN_0043dd60(void);
int  FUN_0043e620(char *param_1);
void FUN_0043df00(void);
void FUN_0043dfa0(int *param_1, char *param_2, void *param_3, void *param_4);
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

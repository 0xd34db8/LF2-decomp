# Untouched Ghidra Exports

This dir contains the **pristine, unmodified decompiler output** extracted directly from `lf2.exe` (v1.9c / v2.0a, 32-bit x86 MSVC++) using Ghidra and REA.

Every file in this directory corresponds 1:1 to a verified procedure entry point in the binary, validated by the automated verifier `verify_raw_entries.py`. All files preserve authentic decompiler semantics as forensic ground truth without hand-written shortcuts.

---

## Directory Structure

```text
decompiled/RAW/
├── app/         # Window management, WinMain, WindowProc, game state transitions, replay setup
├── audio/       # DirectSound initialization, WAV streaming, 32-voice sound buffer management
├── core/        # Precomputed circular PRNG, mathematical utility routines, collision overlap
├── data/        # File I/O, Vigenère data decryption, stage/frame data loaders, control.txt
├── gameplay/    # Entity physics, state machines, combat hitbox collision, AI behavior trees
├── graphics/    # DirectDraw blitting, viewport clipping, parallax background scrolling
└── net/         # WinSock lockstep network protocol, packet serialization, desync verification
```

---

## Technical Characteristics & Ghidra Artifacts

Because these files are direct exports from the decompiler, they exhibit standard decompilation artifacts:
- **`in_ECX` Register Convention:** Functions utilizing the MSVC `__thiscall` convention receive the object pointer in the `ECX` register. In raw decompiler output, this appears as an uninitialized local variable `int in_ECX;`.
- **Global Data References (`DAT_`):** Absolute memory addresses referenced in the executable (e.g., `DAT_00451d48`, `DAT_00458438`) appear as undefined external symbols without explicit type declarations.
- **Synthetic Types:** Types such as `undefined1`, `undefined4`, `undefined8`, `byte`, and `float10` represent generic memory blocks or x87 floating-point registers.
- **Standard Library Inlining:** Several runtime calls (such as `_time64`, `sprintf`, `operator new`) are referenced directly with MSVC CRT mangling.

For a buildable C target with all synthetic types, calling convention shims, and global memory mappings resolved, refer to the sibling [`decompiled/Compilable/`](../Compilable/) suite. For the modernized, cross-platform C++20 SDL2 implementation, refer to [`lifted/`](../../lifted/).

---

## Function Index (72 Decompiled Routines)

| Virtual Address | File Path | Subsystem | Original Routine Description |
| :--- | :--- | :--- | :--- |
| `0x004014e0` | [`audio/func_004014e0_sound_load_wav.c`](audio/func_004014e0_sound_load_wav.c) | Audio | RIFF WAVE audio parser & secondary buffer allocation |
| `0x00401970` | [`audio/func_00401970_sound_init.c`](audio/func_00401970_sound_init.c) | Audio | DirectSound subsystem initialization |
| `0x00401a30` | [`audio/func_00401a30_sound_play.c`](audio/func_00401a30_sound_play.c) | Audio | Sound buffer playback cursor reset & voice trigger |
| `0x00401c90` | [`audio/func_00401c90_bgm_init.c`](audio/func_00401c90_bgm_init.c) | Audio | DirectShow COM Filter Graph & Interface Init |
| `0x00401d30` | [`audio/func_00401d30_bgm_close.c`](audio/func_00401d30_bgm_close.c) | Audio | DirectShow Graph Release & Cleanup |
| `0x00401da0` | [`audio/func_00401da0_bgm_load.c`](audio/func_00401da0_bgm_load.c) | Audio | DirectShow Media File Render & `graph.log` diagnostics |
| `0x00401e90` | [`audio/func_00401e90_bgm_loop.c`](audio/func_00401e90_bgm_loop.c) | Audio | DirectShow Media Seeking & Track Loop Check |
| `0x00401f30` | [`audio/func_00401f30_bgm_volume.c`](audio/func_00401f30_bgm_volume.c) | Audio | DirectShow Audio Volume Control (dB calculation) |
| `0x00402000` | [`audio/func_00402000_bgm_stop.c`](audio/func_00402000_bgm_stop.c) | Audio | DirectShow Playback Stop |
| `0x00402020` | [`audio/func_00402020_bgm_play.c`](audio/func_00402020_bgm_play.c) | Audio | DirectShow Playback Run & Graph Init Dispatch |
| `0x00402100` | [`audio/func_00402100_bgm_pause.c`](audio/func_00402100_bgm_pause.c) | Audio | DirectShow Playback Pause |
| `0x00402130` | [`audio/func_00402130_bgm_menu.c`](audio/func_00402130_bgm_menu.c) | Audio | BGM Track Selection HUD & Menu Input Handling |
| `0x004025b0` | [`audio/func_004025b0_bgm_play_current.c`](audio/func_004025b0_bgm_play_current.c) | Audio | Play Current Track Selection |
| `0x004025d0` | [`audio/func_004025d0_bgm_select.c`](audio/func_004025d0_bgm_select.c) | Audio | Stage / Boss / Random Track Selection |
| `0x004028a0` | [`app/func_004028a0_recording_notify.c`](app/func_004028a0_recording_notify.c) | App | Recording screen HUD notifications & volume |
| `0x00402b60` | [`net/func_00402b60_net_init.c`](net/func_00402b60_net_init.c) | Network | WinSock initialization, socket binding & WSAAsyncSelect |
| `0x00403270` | [`gameplay/func_00403270_teleport.c`](gameplay/func_00403270_teleport.c) | Gameplay | Rudolf team teleportation coordinate resolution |
| `0x004034e0` | [`core/func_004034e0_abs.c`](core/func_004034e0_abs.c) | Core | Fast integer absolute value computation |
| `0x004061d0` | [`gameplay/func_004061d0_object_init.c`](gameplay/func_004061d0_object_init.c) | Gameplay | Entity constructor & default state initialization |
| `0x004064d0` | [`gameplay/func_004064d0_grapple_catch.c`](gameplay/func_004064d0_grapple_catch.c) | Gameplay | Grapple caught-target coordinate sync & throw release |
| `0x00406ba0` | [`gameplay/func_00406ba0_ai_process.c`](gameplay/func_00406ba0_ai_process.c) | Gameplay | AI combat decision tree & virtual key input synthesis |
| `0x00408cb0` | [`gameplay/func_00408cb0_weapon_process.c`](gameplay/func_00408cb0_weapon_process.c) | Gameplay | Weapon attachment point sync, drop & throw physics |
| `0x0040bbf0` | [`data/func_0040bbf0_frame_ctor.c`](data/func_0040bbf0_frame_ctor.c) | Data | Frame structure constructor & zeroing |
| `0x0040be70` | [`data/func_0040be70_calc_frame_coords.c`](data/func_0040be70_calc_frame_coords.c) | Data | Sprite sheet UV cell coordinate calculator |
| `0x0040d0a0` | [`data/func_0040d0a0_save_dat.c`](data/func_0040d0a0_save_dat.c) | Data | Character `.dat` file serializer |
| `0x0040ef70` | [`data/func_0040ef70_load_dat.c`](data/func_0040ef70_load_dat.c) | Data | Master `.dat` script lexer & block parser |
| `0x004143d0` | [`data/func_004143d0_file_ctor.c`](data/func_004143d0_file_ctor.c) | Data | Character file data structure constructor |
| `0x004148a0` | [`data/func_004148a0_decrypt_dat.c`](data/func_004148a0_decrypt_dat.c) | Data | 123-byte header skip & Vigenère cipher decrypter |
| `0x004151d0` | [`graphics/func_004151d0_frame_debugger.c`](graphics/func_004151d0_frame_debugger.c) | Graphics | Frame debugger HUD, sprite rendering dispatch & box overlay |
| `0x00417170` | [`core/func_00417170_random.c`](core/func_00417170_random.c) | Core | 3,000-byte precomputed circular PRNG lookup |
| `0x004171c0` | [`core/func_004171c0_overlap.c`](core/func_004171c0_overlap.c) | Core | 1D coordinate interval overlap detector |
| `0x00417400` | [`gameplay/func_00417400_does_attack_success.c`](gameplay/func_00417400_does_attack_success.c) | Gameplay | 3D AABB hitbox intersection testing (`itr` vs `bdy`) |
| `0x0041a250` | [`graphics/func_0041a250_background_update.c`](graphics/func_0041a250_background_update.c) | Graphics | Background update, parallax scrolling layer calculation & camera bounds |
| `0x0041bc90` | [`net/func_0041bc90_battle_main_loop.c`](net/func_0041bc90_battle_main_loop.c) | Network | Master battle main loop, lockstep frame pacing & input sampling |
| `0x00422ac0` | [`core/func_00422ac0_prng_seed.c`](core/func_00422ac0_prng_seed.c) | Core | PRNG lookup table re-seed & linear congruential init |
| `0x00422b00` | [`app/func_00422b00_key_name.c`](app/func_00422b00_key_name.c) | App | Virtual Key to text name translation & width adjust |
| `0x00422f60` | [`app/func_00422f60_vk_to_char.c`](app/func_00422f60_vk_to_char.c) | App | Virtual Key to ASCII char translation with shift/caps |
| `0x00423230` | [`data/func_00423230_control_save.c`](data/func_00423230_control_save.c) | Data | Save key configuration to `control.txt` |
| `0x00423480` | [`data/func_00423480_control_txt.c`](data/func_00423480_control_txt.c) | Data | Player key config & grave-accent serializer (`control.txt`) |
| `0x004236d0` | [`graphics/func_004236d0_display_mode.c`](graphics/func_004236d0_display_mode.c) | Graphics | Display mode enumeration & resolution check |
| `0x004237e0` | [`graphics/func_004237e0_display_validate.c`](graphics/func_004237e0_display_validate.c) | Graphics | Windowed display mode validation |
| `0x00423840` | [`app/func_00423840_menu_bg.c`](app/func_00423840_menu_bg.c) | App | Menu background image loader & DirectDraw surface cache |
| `0x00423910` | [`app/func_00423910_menu_bg_free.c`](app/func_00423910_menu_bg_free.c) | App | Menu background surface deallocation & release |
| `0x00423940` | [`graphics/func_00423940_text_box.c`](graphics/func_00423940_text_box.c) | Graphics | In-game text box string rendering with shadow |
| `0x00423a70` | [`graphics/func_00423a70_text_shadow.c`](graphics/func_00423a70_text_shadow.c) | Graphics | Drop-shadowed text blit helper |
| `0x004246b0` | [`app/func_004246b0_options_screen.c`](app/func_004246b0_options_screen.c) | App | Options & control configuration screen state machine |
| `0x00429730` | [`app/func_00429730_charmenu_flow.c`](app/func_00429730_charmenu_flow.c) | App | Character select menu flow, replay filename formatting & mode transitions |
| `0x0042e100` | [`gameplay/func_0042e100_attack_process.c`](gameplay/func_0042e100_attack_process.c) | Gameplay | Master 4,000-line combat attack effect dispatcher |
| `0x00431b70` | [`app/func_00431b70_menu_input.c`](app/func_00431b70_menu_input.c) | App | Menu player join & controller input polling |
| `0x00431c70` | [`app/func_00431c70_menu_reset.c`](app/func_00431c70_menu_reset.c) | App | Menu input reset & keyboard buffer restore |
| `0x00431d10` | [`app/func_00431d10_menu_main.c`](app/func_00431d10_menu_main.c) | App | Main menu navigation, replay loader & links |
| `0x00432ab0` | [`app/func_00432ab0_tournament.c`](app/func_00432ab0_tournament.c) | App | Championship tournament bracket state machine |
| `0x00434ab0` | [`app/func_00434ab0_tournament_2on2.c`](app/func_00434ab0_tournament_2on2.c) | App | 2-on-2 championship tournament state machine |
| `0x00436fc0` | [`app/func_00436fc0_stage_advance.c`](app/func_00436fc0_stage_advance.c) | App | Stage/survival wave advance & player vitals recovery |
| `0x00437220` | [`app/func_00437220_survival_curtain.c`](app/func_00437220_survival_curtain.c) | App | Stage clear / survival game-over transition curtain |
| `0x00437400` | [`app/func_00437400_spawn_unit.c`](app/func_00437400_spawn_unit.c) | App | Unit spawn allocation & world object table insert |
| `0x00437860` | [`app/func_00437860_battle_status.c`](app/func_00437860_battle_status.c) | App | Battle status HUD, reinforcement waves & survival timer |
| `0x004389a0` | [`app/func_004389a0_draw_select_rect.c`](app/func_004389a0_draw_select_rect.c) | Graphics | Selection cursor animated border renderer |
| `0x00438ad0` | [`app/func_00438ad0_draw_border_rect.c`](app/func_00438ad0_draw_border_rect.c) | Graphics | Outlined rectangle border renderer |
| `0x00438b40` | [`app/func_00438b40_battle_mode.c`](app/func_00438b40_battle_mode.c) | App | Master Battle Mode army & skirmish squad manager |
| `0x0043b3d0` | [`app/func_0043b3d0_wndproc.c`](app/func_0043b3d0_wndproc.c) | App | Win32 WindowProc, key table & cheat code recognizers |
| `0x0043bdd0` | [`app/func_0043bdd0_create_window.c`](app/func_0043bdd0_create_window.c) | App | Win32 `CreateWindowEx` setup |
| `0x0043bec0` | [`graphics/func_0043bec0_init_display.c`](graphics/func_0043bec0_init_display.c) | Graphics | DirectDraw 6 display mode initialization |
| `0x0043cf40` | [`app/func_0043cf40_winmain.c`](app/func_0043cf40_winmain.c) | App | WinMain entry point & 30.3 FPS game loop |
| `0x0043dd60` | [`data/func_0043dd60_replay_save.c`](data/func_0043dd60_replay_save.c) | Data | Replay file save, zlib compression & secondary cipher |
| `0x0043dfa0` | [`data/func_0043dfa0_replay_unpack.c`](data/func_0043dfa0_replay_unpack.c) | Data | Replay memory buffer state unpacking & entity restoration |
| `0x0043e620` | [`data/func_0043e620_replay_load.c`](data/func_0043e620_replay_load.c) | Data | Replay file load, secondary cipher de-obfuscation & inflation |
| `0x0043e9a0` | [`app/func_0043e9a0_game_mode_mgr.c`](app/func_0043e9a0_game_mode_mgr.c) | App | Game mode setup & developer cheat switches |
| `0x0043ef70` | [`graphics/func_0043ef70_clip_rect.c`](graphics/func_0043ef70_clip_rect.c) | Graphics | 2D software clipping against screen boundaries |
| `0x0043f010` | [`graphics/func_0043f010_surface_blit.c`](graphics/func_0043f010_surface_blit.c) | Graphics | DirectDraw surface blit wrapper |
| `0x0043f4b0` | [`data/func_0043f4b0_zlib_compress.c`](data/func_0043f4b0_zlib_compress.c) | Data | zlib `compress` buffer wrapper |
| `0x0043f4d0` | [`data/func_0043f4d0_zlib_uncompress.c`](data/func_0043f4d0_zlib_uncompress.c) | Data | zlib `uncompress` buffer wrapper |


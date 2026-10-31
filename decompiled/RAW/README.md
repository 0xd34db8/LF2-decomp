# Untouched Ghidra Exports

This dir contains the **pristine, unmodified decompiler output** extracted directly from `lf2.exe` (v1.9c / v2.0a, 32-bit x86 MSVC++) using Ghidra and REA.

These files are preserved byte-for-byte as forensic ground truth without any synthetic headers, typing corrections, or build-system modifications.

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

For a buildable C target with all synthetic types, calling convention shims, and global memory mappings resolved, refer to the sibling [`decompiled/Compilable/`](../Compilable/) suite. For the modernized, cross-platform C++20 SDL2 implementation, refer to [`src/`](../../src/).

---

## Function Index (35 Core Routines)

| Virtual Address | File Path | Subsystem | Original Routine Description |
| :--- | :--- | :--- | :--- |
| `0x004014e0` | [`audio/func_004014e0_sound_load_wav.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/audio/func_004014e0_sound_load_wav.c) | Audio | RIFF WAVE audio parser & secondary buffer allocation |
| `0x00401970` | [`audio/func_00401970_sound_init.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/audio/func_00401970_sound_init.c) | Audio | DirectSound subsystem initialization |
| `0x00401a30` | [`audio/func_00401a30_sound_play.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/audio/func_00401a30_sound_play.c) | Audio | Sound buffer playback cursor reset & voice trigger |
| `0x00402980` | [`app/func_00402980_replay_notify.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_00402980_replay_notify.c) | App | Replay recording screen HUD notifications |
| `0x00402b80` | [`net/func_00402b80_net_init.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/net/func_00402b80_net_init.c) | Network | WinSock initialization, socket binding & WSAAsyncSelect |
| `0x00403270` | [`gameplay/func_00403270_teleport.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/gameplay/func_00403270_teleport.c) | Gameplay | Rudolf team teleportation coordinate resolution |
| `0x004034e0` | [`core/func_004034e0_abs.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/core/func_004034e0_abs.c) | Core | Fast integer absolute value computation |
| `0x004061d0` | [`gameplay/func_004061d0_object_init.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/gameplay/func_004061d0_object_init.c) | Gameplay | Entity constructor & default state initialization |
| `0x004068b0` | [`gameplay/func_004068b0_grapple_sync.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/gameplay/func_004068b0_grapple_sync.c) | Gameplay | Grapple caught-target coordinate sync & throw release |
| `0x00406ba0` | [`gameplay/func_00406ba0_ai_process.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/gameplay/func_00406ba0_ai_process.c) | Gameplay | AI combat decision tree & virtual key input synthesis |
| `0x00408ce0` | [`gameplay/func_00408ce0_weapon_sync.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/gameplay/func_00408ce0_weapon_sync.c) | Gameplay | Weapon attachment point sync, drop & throw physics |
| `0x0040bbf0` | [`data/func_0040bbf0_frame_ctor.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/data/func_0040bbf0_frame_ctor.c) | Data | Frame structure constructor & zeroing |
| `0x0040be70` | [`data/func_0040be70_calc_frame_coords.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/data/func_0040be70_calc_frame_coords.c) | Data | Sprite sheet UV cell coordinate calculator |
| `0x0040d0a0` | [`data/func_0040d0a0_save_dat.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/data/func_0040d0a0_save_dat.c) | Data | Character `.dat` file serializer |
| `0x0040ef70` | [`data/func_0040ef70_load_dat.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/data/func_0040ef70_load_dat.c) | Data | Master `.dat` script lexer & block parser |
| `0x004143d0` | [`data/func_004143d0_file_ctor.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/data/func_004143d0_file_ctor.c) | Data | Character file data structure constructor |
| `0x004148a0` | [`data/func_004148a0_decrypt_dat.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/data/func_004148a0_decrypt_dat.c) | Data | 123-byte header skip & Vigenère cipher decrypter |
| `0x00415d00` | [`graphics/func_00415d00_draw_object.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/graphics/func_00415d00_draw_object.c) | Graphics | Entity screen projection & mirror blit dispatch |
| `0x00417170` | [`core/func_00417170_random.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/core/func_00417170_random.c) | Core | 3,000-byte precomputed circular PRNG lookup |
| `0x004171c0` | [`core/func_004171c0_overlap.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/core/func_004171c0_overlap.c) | Core | 1D coordinate interval overlap detector |
| `0x00417400` | [`gameplay/func_00417400_does_attack_success.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/gameplay/func_00417400_does_attack_success.c) | Gameplay | 3D AABB hitbox intersection testing (`itr` vs `bdy`) |
| `0x0041a2dd` | [`graphics/func_0041a2dd_parallax_calc.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/graphics/func_0041a2dd_parallax_calc.c) | Graphics | Background parallax layer offset & seam wrapping |
| `0x0041c5f0` | [`net/func_0041c5f0_net_lockstep.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/net/func_0041c5f0_net_lockstep.c) | Network | 22-byte lockstep packet send/recv & desync validation |
| `0x00423480` | [`data/func_00423480_control_txt.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/data/func_00423480_control_txt.c) | Data | Player key config & grave-accent serializer (`control.txt`) |
| `0x0042d080` | [`app/func_0042d080_replay_filename.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_0042d080_replay_filename.c) | App | Timestamped `.lfr` replay filename generator |
| `0x0042e100` | [`gameplay/func_0042e100_attack_process.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/gameplay/func_0042e100_attack_process.c) | Gameplay | Master 4,000-line combat attack effect dispatcher |
| `0x00431b70` | [`app/func_00431b70_menu_input.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_00431b70_menu_input.c) | App | Menu player join & controller input polling |
| `0x00431c70` | [`app/func_00431c70_menu_reset.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_00431c70_menu_reset.c) | App | Menu input reset & keyboard buffer restore |
| `0x00431d10` | [`app/func_00431d10_menu_main.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_00431d10_menu_main.c) | App | Main menu navigation, replay loader & links |
| `0x00432ab0` | [`app/func_00432ab0_tournament.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_00432ab0_tournament.c) | App | Championship tournament bracket state machine |
| `0x00434ab0` | [`app/func_00434ab0_tournament_2on2.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_00434ab0_tournament_2on2.c) | App | 2-on-2 championship tournament state machine |
| `0x00436900` | [`app/func_00436900_battle_setup.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_00436900_battle_setup.c) | App | Player/CPU entity spawn initialization & battle setup |
| `0x00437400` | [`app/func_00437400_spawn_unit.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_00437400_spawn_unit.c) | App | Unit spawn allocation & world object table insert |
| `0x00437860` | [`app/func_00437860_battle_status.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_00437860_battle_status.c) | App | Battle status HUD, reinforcement waves & survival timer |
| `0x004389a0` | [`app/func_004389a0_draw_select_rect.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_004389a0_draw_select_rect.c) | Graphics | Selection cursor animated border renderer |
| `0x00438ad0` | [`app/func_00438ad0_draw_border_rect.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_00438ad0_draw_border_rect.c) | Graphics | Outlined rectangle border renderer |
| `0x00438b40` | [`app/func_00438b40_battle_mode.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_00438b40_battle_mode.c) | App | Master Battle Mode army & skirmish squad manager |
| `0x0043b3d0` | [`app/func_0043b3d0_wndproc.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_0043b3d0_wndproc.c) | App | Win32 WindowProc, key table & cheat code recognizers |
| `0x0043bdd0` | [`app/func_0043bdd0_create_window.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_0043bdd0_create_window.c) | App | Win32 `CreateWindowEx` setup |
| `0x0043bec0` | [`graphics/func_0043bec0_init_display.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/graphics/func_0043bec0_init_display.c) | Graphics | DirectDraw 6 display mode initialization |
| `0x0043cf40` | [`app/func_0043cf40_winmain.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_0043cf40_winmain.c) | App | WinMain entry point & 30.3 FPS game loop |
| `0x0043e9a0` | [`app/func_0043e9a0_game_mode_mgr.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/app/func_0043e9a0_game_mode_mgr.c) | App | Game mode setup & developer cheat switches |
| `0x0043ef70` | [`graphics/func_0043ef70_clip_rect.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/graphics/func_0043ef70_clip_rect.c) | Graphics | 2D software clipping against screen boundaries |
| `0x0043f010` | [`graphics/func_0043f010_surface_blit.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/RAW/graphics/func_0043f010_surface_blit.c) | Graphics | DirectDraw surface blit wrapper |


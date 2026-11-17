# Decompiled Archive (Ghidra & x86 Disassembly)

This directory contains the decompiled logic and ground-truth pseudocode extracted from `lf2.exe` (v1.9c / v2.0a, 32-bit x86 MSVC++) using Ghidra and REA.

The archive contains the following suites and extracted artifacts:

```text
decompiled/
├── README.md        # Master directory index & architectural overview
├── RAW/             # Pristine, untouched Ghidra decompiler exports
│   ├── README.md    # Dedicated documentation for the raw forensic suite
│   ├── app/
│   ├── audio/
│   ├── core/
│   ├── data/
│   ├── gameplay/
│   ├── graphics/
│   └── net/
├── Compilable/      # Self-contained, compilable legacy C suite
│   ├── README.md    # Dedicated documentation, compilation instructions & type map
│   ├── include/     # legacy_types.h, legacy_globals.h, legacy_signatures.h
│   ├── app/
│   ├── audio/
│   ├── core/        # legacy_globals.c + core math routines
│   ├── data/
│   ├── gameplay/
│   ├── graphics/
│   └── net/
└── resources/       # Embedded PE resources extracted from the binary
    ├── icon/        # Application icon (lf2.ico)
    ├── manifest/    # Assembly dependency manifest (lf2.exe.manifest)
    └── ui/          # Bitmap image assets extracted from the PE resource table
```

---

## Suite Summary & Documentation

- **[`decompiled/RAW/`](RAW/README.md):**
  Houses the 112 pristine decompiler exports directly as emitted by Ghidra, verified 1:1 against genuine function entry points in `lf2.exe` via `verify_raw_entries.py`. Preserves raw `DAT_` pointers, synthetic registers (`in_ECX`), and original formatting without hand-written shortcuts. Serves as immutable forensic evidence for mathematical validation.
  *Read the full guide: [RAW/README.md](RAW/README.md)*

- **[`decompiled/Compilable/`](Compilable/README.md):**
  Houses the complete compilable legacy suite (54 library translation units + test runner) with synthetic types (`legacy_types.h`), calling convention bridges, external global memory declarations (`legacy_globals.h`), and zeroed static allocations (`legacy_globals.c`). Compiles with 0 syntax or symbol errors under GCC and Clang.
  *Read the full guide: [Compilable/README.md](Compilable/README.md)*

- **[`decompiled/resources/`](resources/):**
  Houses raw resources extracted directly from inside the `lf2.exe` executable binary's Portable Executable (PE) `.rsrc` section:
  - **[`ui/`](resources/ui/):** Raw bitmap assets embedded internally within the binary's `RT_BITMAP` resource directory (unlike loose disk assets like `data/`, `bg/`, or `sprite/`).
  - **[`icon/`](resources/icon/):** Authentic 32x32 application icon (`lf2.ico`) reconstructed from the binary's `RT_GROUP_ICON` and `RT_ICON` tables.
  - **[`manifest/`](resources/manifest/):** Original CRT and MFC dependency manifest (`lf2.exe.manifest`) extracted from `RT_MANIFEST`.

- **Modern C++20 Port ([`lifted/`](../lifted/)):**
  The production engine rewrite in `lifted/` lifts the mathematical and physical state machine logic from these decompiled routines into clean, modern, portable C++20 with SDL2, completely independent of legacy Win32, DirectDraw, and DirectSound.

---

## Master Function & Memory Address Index

| Virtual Address | Subsystem | Function / Purpose | RAW Suite | Compilable Suite |
| :--- | :--- | :--- | :--- | :--- |
| `0x004014e0` | Audio | RIFF WAVE audio parser & buffer allocation | [`RAW/audio`](RAW/audio/func_004014e0_sound_load_wav.c) | [`Compilable/audio`](Compilable/audio/sound_load_wav.c) |
| `0x00401970` | Audio | DirectSound subsystem initialization | [`RAW/audio`](RAW/audio/func_00401970_sound_init.c) | [`Compilable/audio`](Compilable/audio/sound_init.c) |
| `0x004019b0` | Audio | DirectSound device release & buffer destruction | [`RAW/audio`](RAW/audio/func_004019b0_sound_cleanup.c) | [`Compilable/audio`](Compilable/audio/sound_init.c) |
| `0x00401a30` | Audio | Voice trigger & playback cursor reset | [`RAW/audio`](RAW/audio/func_00401a30_sound_play.c) | [`Compilable/audio`](Compilable/audio/sound_play.c) |
| `0x00401a80` | Graphics | DirectDraw surface release & interface cleanup | [`RAW/graphics`](RAW/graphics/func_00401a80_ddraw_release.c) | — |
| `0x00401ae0` | Graphics | Win32 main window destruction | [`RAW/graphics`](RAW/graphics/func_00401ae0_window_destroy.c) | — |
| `0x00401b00` | Graphics | Windowed display mode creation & viewport setup | [`RAW/graphics`](RAW/graphics/func_00401b00_create_window_windowed.c) | — |
| `0x00401bf0` | Graphics | Fullscreen exclusive display mode window creation | [`RAW/graphics`](RAW/graphics/func_00401bf0_create_window_fullscreen.c) | — |
| `0x00401c90` | Audio | DirectShow COM Filter Graph & Interface Init | [`RAW/audio`](RAW/audio/func_00401c90_bgm_init.c) | [`Compilable/audio`](Compilable/audio/bgm_manager.c) |
| `0x00401d30` | Audio | DirectShow Graph Release & Cleanup | [`RAW/audio`](RAW/audio/func_00401d30_bgm_close.c) | [`Compilable/audio`](Compilable/audio/bgm_manager.c) |
| `0x00401da0` | Audio | DirectShow Media File Render & `graph.log` diagnostics | [`RAW/audio`](RAW/audio/func_00401da0_bgm_load.c) | [`Compilable/audio`](Compilable/audio/bgm_manager.c) |
| `0x00401e90` | Audio | DirectShow Media Seeking & Track Loop Check | [`RAW/audio`](RAW/audio/func_00401e90_bgm_loop.c) | [`Compilable/audio`](Compilable/audio/bgm_manager.c) |
| `0x00401f30` | Audio | DirectShow Audio Volume Control (dB calculation) | [`RAW/audio`](RAW/audio/func_00401f30_bgm_volume.c) | [`Compilable/audio`](Compilable/audio/bgm_manager.c) |
| `0x00402000` | Audio | DirectShow Playback Stop | [`RAW/audio`](RAW/audio/func_00402000_bgm_stop.c) | [`Compilable/audio`](Compilable/audio/bgm_manager.c) |
| `0x00402020` | Audio | DirectShow Playback Run & Graph Init Dispatch | [`RAW/audio`](RAW/audio/func_00402020_bgm_play.c) | [`Compilable/audio`](Compilable/audio/bgm_manager.c) |
| `0x00402100` | Audio | DirectShow Playback Pause | [`RAW/audio`](RAW/audio/func_00402100_bgm_pause.c) | [`Compilable/audio`](Compilable/audio/bgm_manager.c) |
| `0x00402130` | Audio | BGM Track Selection HUD & Menu Input Handling | [`RAW/audio`](RAW/audio/func_00402130_bgm_menu.c) | [`Compilable/audio`](Compilable/audio/bgm_manager.c) |
| `0x004025b0` | Audio | Play Current Track Selection | [`RAW/audio`](RAW/audio/func_004025b0_bgm_play_current.c) | [`Compilable/audio`](Compilable/audio/bgm_manager.c) |
| `0x004025d0` | Audio | Stage / Boss / Random Track Selection | [`RAW/audio`](RAW/audio/func_004025d0_bgm_select.c) | [`Compilable/audio`](Compilable/audio/bgm_manager.c) |
| `0x00402810` | Audio | Master sound effects volume attenuator | [`RAW/audio`](RAW/audio/func_00402810_volume_adjust.c) | [`Compilable/audio`](Compilable/audio/sound_play.c) |
| `0x004028a0` | App | Recording screen HUD notifications & volume | [`RAW/app`](RAW/app/func_004028a0_recording_notify.c) | [`Compilable/app`](Compilable/app/replay_notify.c) |
| `0x00402b60` | Network | WinSock init, socket setup & WSAAsyncSelect | [`RAW/net`](RAW/net/func_00402b60_net_init.c) | [`Compilable/net`](Compilable/net/net_init.c) |
| `0x00403270` | Gameplay | Rudolf team teleportation targeting | [`RAW/gameplay`](RAW/gameplay/func_00403270_teleport.c) | [`Compilable/gameplay`](Compilable/gameplay/teleport.c) |
| `0x004034e0` | Core | Fast integer absolute value computation | [`RAW/core`](RAW/core/func_004034e0_abs.c) | [`Compilable/core`](Compilable/core/abs.c) |
| `0x004034f0` | Gameplay | AI combat dodge & evasive roll maneuver | [`RAW/gameplay`](RAW/gameplay/func_004034f0_ai_dodge.c) | [`Compilable/gameplay`](Compilable/gameplay/ai_process.c) |
| `0x00403a40` | Gameplay | AI character-specific special move decision tree | [`RAW/gameplay`](RAW/gameplay/func_00403a40_ai_char_special.c) | [`Compilable/gameplay`](Compilable/gameplay/ai_process.c) |
| `0x004061a0` | Gameplay | 1D interval betweenness test | [`RAW/gameplay`](RAW/gameplay/func_004061a0_is_between.c) | [`Compilable/gameplay`](Compilable/gameplay/object_init.c) |
| `0x004061d0` | Gameplay | Entity constructor & default state init | [`RAW/gameplay`](RAW/gameplay/func_004061d0_object_init.c) | [`Compilable/gameplay`](Compilable/gameplay/object_init.c) |
| `0x004064d0` | Gameplay | Firen + Freeze -> Firzen fusion check & transformation | [`RAW/gameplay`](RAW/gameplay/func_004064d0_firzen_fusion.c) | [`Compilable/gameplay`](Compilable/gameplay/grapple_sync.c) |
| `0x00406a20` | Gameplay | Dynamic world object, projectile & particle spawner (slots 50..399) | [`RAW/gameplay`](RAW/gameplay/func_00406a20_opoint_spawn.c) | [`Compilable/gameplay`](Compilable/gameplay/ai_process.c) |
| `0x00406ba0` | Gameplay | `hit_Fa` homing projectile & chase physics | [`RAW/gameplay`](RAW/gameplay/func_00406ba0_hit_fa_chase.c) | [`Compilable/gameplay`](Compilable/gameplay/ai_process.c) |
| `0x00408cb0` | Gameplay | AI weapon pickup, throw & drink decision helper | [`RAW/gameplay`](RAW/gameplay/func_00408cb0_ai_weapon_decision.c) | [`Compilable/gameplay`](Compilable/gameplay/weapon_sync.c) |
| `0x004094b0` | Gameplay | Primary AI controller, target acquisition & state machine | [`RAW/gameplay`](RAW/gameplay/func_004094b0_ai_controller.c) | [`Compilable/gameplay`](Compilable/gameplay/ai_process.c) |
| `0x0040bbf0` | Data | Frame structure constructor & zeroing | [`RAW/data`](RAW/data/func_0040bbf0_frame_ctor.c) | [`Compilable/data`](Compilable/data/frame_ctor.c) |
| `0x0040be70` | Data | Sprite sheet UV coordinate calculation | [`RAW/data`](RAW/data/func_0040be70_calc_frame_coords.c) | [`Compilable/data`](Compilable/data/calc_frame_coords.c) |
| `0x0040d0a0` | Data | Character `.dat` file serializer | [`RAW/data`](RAW/data/func_0040d0a0_save_dat.c) | [`Compilable/data`](Compilable/data/save_dat.c) |
| `0x0040de30` | Graphics | Sprite entity rendering, facing flip & palette blit | [`RAW/graphics`](RAW/graphics/func_0040de30_draw_entity.c) | [`Compilable/graphics`](Compilable/graphics/draw_object.c) |
| `0x0040e2d0` | Gameplay | Frame transition, MP cost deduction & hit-state reset helper | [`RAW/gameplay`](RAW/gameplay/func_0040e2d0_frame_transition.c) | — |
| `0x0040e450` | Gameplay | 5-entry object input history shift register (`+0x408..+0x418`) | [`RAW/gameplay`](RAW/gameplay/func_0040e450_input_history_push.c) | — |
| `0x0040e490` | Gameplay | Per-object physics, velocity integration, gravity, landing & opoint tick | [`RAW/gameplay`](RAW/gameplay/func_0040e490_object_physics_tick.c) | — |
| `0x0040ef70` | Data | Master `.dat` script lexer & parser | [`RAW/data`](RAW/data/func_0040ef70_load_dat.c) | [`Compilable/data`](Compilable/data/load_dat.c) |
| `0x00413080` | Gameplay | Master per-object input/state tick & combo recognizer dispatcher | [`RAW/gameplay`](RAW/gameplay/func_00413080_object_input_tick.c) | — |
| `0x004143d0` | Data | Master character file data constructor | [`RAW/data`](RAW/data/func_004143d0_file_ctor.c) | [`Compilable/data`](Compilable/data/file_ctor.c) |
| `0x004146b0` | Data | Character `.dat` encryption cipher serializer | [`RAW/data`](RAW/data/func_004146b0_encrypt_dat.c) | [`Compilable/data`](Compilable/data/decrypt_dat.c) |
| `0x004148a0` | Data | 123-byte header skip & Vigenère decrypter | [`RAW/data`](RAW/data/func_004148a0_decrypt_dat.c) | [`Compilable/data`](Compilable/data/decrypt_dat.c) |
| `0x00414a30` | Data | Decrypted `.dat` file exporter | [`RAW/data`](RAW/data/func_00414a30_decrypt_dat_to_file.c) | [`Compilable/data`](Compilable/data/decrypt_dat.c) |
| `0x00414b70` | Data | Interactive `.dat` encrypt/decrypt CLI tool (`helpme`) | [`RAW/data`](RAW/data/func_00414b70_stage_dat_loader.c) | — |
| `0x004151d0` | Graphics | Frame debugger HUD, sprite rendering dispatch & box overlay | [`RAW/graphics`](RAW/graphics/func_004151d0_frame_debugger.c) | — |
| `0x00416fb0` | Audio | Positional audio panning calculator pass 1 | [`RAW/audio`](RAW/audio/func_00416fb0_sound_pan_calc_1.c) | [`Compilable/audio`](Compilable/audio/sound_play.c) |
| `0x00417090` | Audio | Positional audio panning calculator pass 2 | [`RAW/audio`](RAW/audio/func_00417090_sound_pan_calc_2.c) | [`Compilable/audio`](Compilable/audio/sound_play.c) |
| `0x00417170` | Core | 3,000-byte precomputed circular PRNG | [`RAW/core`](RAW/core/func_00417170_random.c) | [`Compilable/core`](Compilable/core/random.c) |
| `0x004171c0` | Core | 1D coordinate interval overlap check | [`RAW/core`](RAW/core/func_004171c0_overlap.c) | [`Compilable/core`](Compilable/core/overlap.c) |
| `0x00417200` | Gameplay | Broad-phase `itr` vs `bdy` 2D bounding box overlap pre-check | [`RAW/gameplay`](RAW/gameplay/func_00417200_broadphase_overlap.c) | [`Compilable/gameplay`](Compilable/gameplay/slot_input.c) |
| `0x00417400` | Gameplay | 3D AABB hitbox intersection testing | [`RAW/gameplay`](RAW/gameplay/func_00417400_does_attack_success.c) | [`Compilable/gameplay`](Compilable/gameplay/does_attack_success.c) |
| `0x00417f80` | Gameplay | Held weapon `wpoint` anchor sync, Milk/Beer drinking & throw | [`RAW/gameplay`](RAW/gameplay/func_00417f80_wpoint_process.c) | [`Compilable/gameplay`](Compilable/gameplay/weapon_sync.c) |
| `0x004187b0` | Gameplay | Grapple `cpoint` caught anchor synchronization | [`RAW/gameplay`](RAW/gameplay/func_004187b0_cpoint_process.c) | [`Compilable/gameplay`](Compilable/gameplay/grapple_sync.c) |
| `0x00418c30` | Gameplay | Grapple `cpoint` throw release & damage chaining | [`RAW/gameplay`](RAW/gameplay/func_00418c30_cpoint_chain.c) | [`Compilable/gameplay`](Compilable/gameplay/grapple_sync.c) |
| `0x00419380` | Gameplay | Master 400x400 pairwise collision pass & rest-timer reset | [`RAW/gameplay`](RAW/gameplay/func_00419380_entity_tick.c) | [`Compilable/gameplay`](Compilable/gameplay/slot_input.c) |
| `0x004196f0` | Gameplay | 400-object velocity/impulse averaging pass | [`RAW/gameplay`](RAW/gameplay/func_004196f0_velocity_average.c) | [`Compilable/gameplay`](Compilable/gameplay/slot_input.c) |
| `0x004197a0` | Gameplay | Remote/network input unpacking & latching | [`RAW/gameplay`](RAW/gameplay/func_004197a0_input_unpack_net.c) | [`Compilable/gameplay`](Compilable/gameplay/slot_input.c) |
| `0x004198f0` | Gameplay | Local player input latching & replay recording | [`RAW/gameplay`](RAW/gameplay/func_004198f0_input_latch_local.c) | [`Compilable/gameplay`](Compilable/gameplay/slot_input.c) |
| `0x00419a60` | Gameplay | Master per-slot controller / AI input loop | [`RAW/gameplay`](RAW/gameplay/func_00419a60_input_ai_dispatch.c) | [`Compilable/gameplay`](Compilable/gameplay/slot_input.c) |
| `0x0041a250` | Graphics | Background update, parallax scrolling layer calculation & camera bounds | [`RAW/graphics`](RAW/graphics/func_0041a250_background_update.c) | [`Compilable/graphics`](Compilable/graphics/parallax_calc.c) |
| `0x0041a5a0` | Graphics | Master scene rendering dispatcher & Z-sorting pass | [`RAW/graphics`](RAW/graphics/func_0041a5a0_render_scene.c) | [`Compilable/graphics`](Compilable/graphics/draw_object.c) |
| `0x0041ae60` | Graphics | In-game HUD HP/MP gauge bar renderer | [`RAW/graphics`](RAW/graphics/func_0041ae60_render_hud_bars.c) | — |
| `0x0041b130` | Graphics | In-game HUD player status & score renderer | [`RAW/graphics`](RAW/graphics/func_0041b130_render_hud_status.c) | — |
| `0x0041b5d0` | Gameplay | Stage camera bounds, phase scroll lock & enemy wave spawner | [`RAW/gameplay`](RAW/gameplay/func_0041b5d0_camera_stage_bounds.c) | — |
| `0x0041bc90` | Network | Master battle main loop, lockstep frame pacing & input sampling | [`RAW/net`](RAW/net/func_0041bc90_battle_main_loop.c) | [`Compilable/net`](Compilable/net/net_lockstep.c) |
| `0x00422ac0` | Core | PRNG lookup table re-seed & linear congruential init | [`RAW/core`](RAW/core/func_00422ac0_prng_seed.c) | [`Compilable/core`](Compilable/core/random.c) |
| `0x00422b00` | App | Virtual Key to text name translation & width adjust | [`RAW/app`](RAW/app/func_00422b00_key_name.c) | [`Compilable/app`](Compilable/app/key_name.c) |
| `0x00422f60` | App | Virtual Key to ASCII char translation with shift/caps | [`RAW/app`](RAW/app/func_00422f60_vk_to_char.c) | [`Compilable/app`](Compilable/app/vk_to_char.c) |
| `0x00423230` | Data | Save key configuration to `control.txt` | [`RAW/data`](RAW/data/func_00423230_control_save.c) | [`Compilable/data`](Compilable/data/control_txt.c) |
| `0x00423480` | Data | Key config & name serializer (`control.txt`) | [`RAW/data`](RAW/data/func_00423480_control_txt.c) | [`Compilable/data`](Compilable/data/control_txt.c) |
| `0x004236d0` | Graphics | Display mode enumeration & resolution check | [`RAW/graphics`](RAW/graphics/func_004236d0_display_mode.c) | — |
| `0x004237e0` | Graphics | Windowed display mode validation | [`RAW/graphics`](RAW/graphics/func_004237e0_display_validate.c) | — |
| `0x00423840` | Graphics | Menu bitmap background loading & surface cache | [`RAW/app`](RAW/app/func_00423840_menu_bg.c) | — |
| `0x00423910` | Graphics | Menu background surface deallocation & release | [`RAW/app`](RAW/app/func_00423910_menu_bg_free.c) | — |
| `0x00423940` | Graphics | In-game text box string rendering with shadow | [`RAW/graphics`](RAW/graphics/func_00423940_text_box.c) | [`Compilable/graphics`](Compilable/graphics/text_box.c) |
| `0x00423a70` | Graphics | Drop-shadowed text blit helper | [`RAW/graphics`](RAW/graphics/func_00423a70_text_shadow.c) | [`Compilable/graphics`](Compilable/graphics/text_box.c) |
| `0x004246b0` | App | Options & control configuration screen state machine | [`RAW/app`](RAW/app/func_004246b0_options_screen.c) | [`Compilable/app`](Compilable/app/options_screen.c) |
| `0x00429730` | App | Character select menu flow, replay filename formatting & mode transitions | [`RAW/app`](RAW/app/func_00429730_charmenu_flow.c) | [`Compilable/app`](Compilable/app/replay_filename.c) |
| `0x0042e100` | Gameplay | Master 4,000-line combat attack dispatcher | [`RAW/gameplay`](RAW/gameplay/func_0042e100_attack_process.c) | [`Compilable/gameplay`](Compilable/gameplay/attack_process.c) |
| `0x00431b70` | App | Menu player join & controller input polling | [`RAW/app`](RAW/app/func_00431b70_menu_input.c) | [`Compilable/app`](Compilable/app/menu_input.c) |
| `0x00431c70` | App | Menu input reset & keyboard buffer restore | [`RAW/app`](RAW/app/func_00431c70_menu_reset.c) | [`Compilable/app`](Compilable/app/menu_reset.c) |
| `0x00431d10` | App | Main menu navigation, replay loader & links | [`RAW/app`](RAW/app/func_00431d10_menu_main.c) | [`Compilable/app`](Compilable/app/menu_main.c) |
| `0x00432ab0` | App | Championship tournament bracket state machine | [`RAW/app`](RAW/app/func_00432ab0_tournament.c) | [`Compilable/app`](Compilable/app/tournament.c) |
| `0x00434ab0` | App | 2-on-2 championship tournament state machine | [`RAW/app`](RAW/app/func_00434ab0_tournament_2on2.c) | [`Compilable/app`](Compilable/app/tournament_2on2.c) |
| `0x00436fc0` | App | Stage/survival wave advance & player vitals recovery | [`RAW/app`](RAW/app/func_00436fc0_stage_advance.c) | [`Compilable/app`](Compilable/app/stage_advance.c) |
| `0x00437220` | App | Stage clear / survival game-over transition curtain | [`RAW/app`](RAW/app/func_00437220_survival_curtain.c) | [`Compilable/app`](Compilable/app/survival_curtain.c) |
| `0x00437400` | App | Unit spawn allocation & world object table insert | [`RAW/app`](RAW/app/func_00437400_spawn_unit.c) | [`Compilable/app`](Compilable/app/spawn_unit.c) |
| `0x00437860` | App | Battle status HUD, reinforcement waves & survival timer | [`RAW/app`](RAW/app/func_00437860_battle_status.c) | [`Compilable/app`](Compilable/app/battle_status.c) |
| `0x004389a0` | Graphics | Selection cursor animated border renderer | [`RAW/app`](RAW/app/func_004389a0_draw_select_rect.c) | [`Compilable/app`](Compilable/app/draw_select_rect.c) |
| `0x00438ad0` | Graphics | Outlined rectangle border renderer | [`RAW/app`](RAW/app/func_00438ad0_draw_border_rect.c) | [`Compilable/app`](Compilable/app/draw_border_rect.c) |
| `0x00438b40` | App | Master Battle Mode army & skirmish squad manager | [`RAW/app`](RAW/app/func_00438b40_battle_mode.c) | [`Compilable/app`](Compilable/app/battle_mode.c) |
| `0x0043b3d0` | App | Win32 WindowProc & cheat recognizers | [`RAW/app`](RAW/app/func_0043b3d0_wndproc.c) | [`Compilable/app`](Compilable/app/wndproc.c) |
| `0x0043bdd0` | App | Win32 `CreateWindowEx` setup | [`RAW/app`](RAW/app/func_0043bdd0_create_window.c) | [`Compilable/app`](Compilable/app/create_window.c) |
| `0x0043bec0` | Graphics | DirectDraw 6 display mode initialization | [`RAW/graphics`](RAW/graphics/func_0043bec0_init_display.c) | [`Compilable/graphics`](Compilable/graphics/init_display.c) |
| `0x0043bf10` | Core | DirectInput joystick controller initialization | [`RAW/core`](RAW/core/func_0043bf10_joystick_init.c) | — |
| `0x0043c0c0` | Core | WinINet HTTP background update downloader | [`RAW/core`](RAW/core/func_0043c0c0_http_download.c) | — |
| `0x0043c450` | Core | Advertising banner worker thread starter | [`RAW/core`](RAW/core/func_0043c450_ad_thread_start.c) | — |
| `0x0043c780` | Graphics | Embedded UI bitmap surface loader | [`RAW/graphics`](RAW/graphics/func_0043c780_load_ui_surfaces.c) | — |
| `0x0043cc60` | Graphics | Embedded UI secondary surface cache loader | [`RAW/graphics`](RAW/graphics/func_0043cc60_load_ui_2_surface.c) | — |
| `0x0043cf40` | App | WinMain entry point & 30.3 FPS game loop | [`RAW/app`](RAW/app/func_0043cf40_winmain.c) | [`Compilable/app`](Compilable/app/winmain.c) |
| `0x0043dd60` | Data | Replay file save, zlib compression & secondary cipher | [`RAW/data`](RAW/data/func_0043dd60_replay_save.c) | [`Compilable/data`](Compilable/data/replay_cipher.c) |
| `0x0043dfa0` | Data | Replay memory buffer state unpacking & entity restoration | [`RAW/data`](RAW/data/func_0043dfa0_replay_unpack.c) | — |
| `0x0043e620` | Data | Replay file load, secondary cipher de-obfuscation & inflation | [`RAW/data`](RAW/data/func_0043e620_replay_load.c) | [`Compilable/data`](Compilable/data/replay_cipher.c) |
| `0x0043e890` | Graphics | DirectDraw surface restoration handler | [`RAW/graphics`](RAW/graphics/func_0043e890_ddraw_restore.c) | — |
| `0x0043e9a0` | App | Game mode setup & developer cheat switches | [`RAW/app`](RAW/app/func_0043e9a0_game_mode_mgr.c) | [`Compilable/app`](Compilable/app/game_mode_mgr.c) |
| `0x0043ef70` | Graphics | 2D software clipping against viewport | [`RAW/graphics`](RAW/graphics/func_0043ef70_clip_rect.c) | [`Compilable/graphics`](Compilable/graphics/clip_rect.c) |
| `0x0043f010` | Graphics | DirectDraw surface blit wrapper | [`RAW/graphics`](RAW/graphics/func_0043f010_surface_blit.c) | [`Compilable/graphics`](Compilable/graphics/surface_blit.c) |
| `0x0043f4b0` | Data | zlib `compress` buffer wrapper | [`RAW/data`](RAW/data/func_0043f4b0_zlib_compress.c) | [`Compilable/data`](Compilable/data/replay_cipher.c) |
| `0x0043f4d0` | Data | zlib `uncompress` buffer wrapper | [`RAW/data`](RAW/data/func_0043f4d0_zlib_uncompress.c) | [`Compilable/data`](Compilable/data/replay_cipher.c) |

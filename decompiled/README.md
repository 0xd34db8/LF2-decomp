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
  Houses the untouched decompiler exports directly as emitted by Ghidra. Preserves raw `DAT_` pointers, synthetic registers (`in_ECX`), and original formatting without patches. Serves as immutable forensic evidence for mathematical validation.
  *Read the full guide: [RAW/README.md](RAW/README.md)*

- **[`decompiled/Compilable/`](Compilable/README.md):**
  Houses the complete 46-routine suite with synthetic types (`legacy_types.h`), calling convention bridges, external global memory declarations (`legacy_globals.h`), and zeroed static allocations (`legacy_globals.c`). Compiles with 0 syntax or symbol errors under GCC and Clang.
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
| `0x00401a30` | Audio | Voice trigger & playback cursor reset | [`RAW/audio`](RAW/audio/func_00401a30_sound_play.c) | [`Compilable/audio`](Compilable/audio/sound_play.c) |
| `0x00402980` | App | Replay recording screen HUD notifications | [`RAW/app`](RAW/app/func_00402980_replay_notify.c) | [`Compilable/app`](Compilable/app/replay_notify.c) |
| `0x00402b80` | Network | WinSock init, socket setup & WSAAsyncSelect | [`RAW/net`](RAW/net/func_00402b80_net_init.c) | [`Compilable/net`](Compilable/net/net_init.c) |
| `0x00403270` | Gameplay | Rudolf team teleportation targeting | [`RAW/gameplay`](RAW/gameplay/func_00403270_teleport.c) | [`Compilable/gameplay`](Compilable/gameplay/teleport.c) |
| `0x004034e0` | Core | Fast integer absolute value computation | [`RAW/core`](RAW/core/func_004034e0_abs.c) | [`Compilable/core`](Compilable/core/abs.c) |
| `0x004061d0` | Gameplay | Entity constructor & default state init | [`RAW/gameplay`](RAW/gameplay/func_004061d0_object_init.c) | [`Compilable/gameplay`](Compilable/gameplay/object_init.c) |
| `0x004068b0` | Gameplay | Grapple caught-target coordinate sync | [`RAW/gameplay`](RAW/gameplay/func_004068b0_grapple_sync.c) | [`Compilable/gameplay`](Compilable/gameplay/grapple_sync.c) |
| `0x00406ba0` | Gameplay | AI combat decision tree & input synthesis | [`RAW/gameplay`](RAW/gameplay/func_00406ba0_ai_process.c) | [`Compilable/gameplay`](Compilable/gameplay/ai_process.c) |
| `0x00408ce0` | Gameplay | Weapon attachment point sync, drop & throw | [`RAW/gameplay`](RAW/gameplay/func_00408ce0_weapon_sync.c) | [`Compilable/gameplay`](Compilable/gameplay/weapon_sync.c) |
| `0x0040bbf0` | Data | Frame structure constructor & zeroing | [`RAW/data`](RAW/data/func_0040bbf0_frame_ctor.c) | [`Compilable/data`](Compilable/data/frame_ctor.c) |
| `0x0040be70` | Data | Sprite sheet UV coordinate calculation | [`RAW/data`](RAW/data/func_0040be70_calc_frame_coords.c) | [`Compilable/data`](Compilable/data/calc_frame_coords.c) |
| `0x0040d0a0` | Data | Character `.dat` file serializer | [`RAW/data`](RAW/data/func_0040d0a0_save_dat.c) | [`Compilable/data`](Compilable/data/save_dat.c) |
| `0x0040ef70` | Data | Master `.dat` script lexer & parser | [`RAW/data`](RAW/data/func_0040ef70_load_dat.c) | [`Compilable/data`](Compilable/data/load_dat.c) |
| `0x004143d0` | Data | Master character file data constructor | [`RAW/data`](RAW/data/func_004143d0_file_ctor.c) | [`Compilable/data`](Compilable/data/file_ctor.c) |
| `0x004148a0` | Data | 123-byte header skip & Vigenère decrypter | [`RAW/data`](RAW/data/func_004148a0_decrypt_dat.c) | [`Compilable/data`](Compilable/data/decrypt_dat.c) |
| `0x00415d00` | Graphics | Entity screen projection & mirror blit | [`RAW/graphics`](RAW/graphics/func_00415d00_draw_object.c) | [`Compilable/graphics`](Compilable/graphics/draw_object.c) |
| `0x00417170` | Core | 3,000-byte precomputed circular PRNG | [`RAW/core`](RAW/core/func_00417170_random.c) | [`Compilable/core`](Compilable/core/random.c) |
| `0x004171c0` | Core | 1D coordinate interval overlap check | [`RAW/core`](RAW/core/func_004171c0_overlap.c) | [`Compilable/core`](Compilable/core/overlap.c) |
| `0x00417400` | Gameplay | 3D AABB hitbox intersection testing | [`RAW/gameplay`](RAW/gameplay/func_00417400_does_attack_success.c) | [`Compilable/gameplay`](Compilable/gameplay/does_attack_success.c) |
| `0x0041a2dd` | Graphics | Background parallax layer offset & wrap | [`RAW/graphics`](RAW/graphics/func_0041a2dd_parallax_calc.c) | [`Compilable/graphics`](Compilable/graphics/parallax_calc.c) |
| `0x0041c5f0` | Network | 22-byte lockstep packet send/recv & desync | [`RAW/net`](RAW/net/func_0041c5f0_net_lockstep.c) | [`Compilable/net`](Compilable/net/net_lockstep.c) |
| `0x00423480` | Data | Key config & name serializer (`control.txt`)| [`RAW/data`](RAW/data/func_00423480_control_txt.c) | [`Compilable/data`](Compilable/data/control_txt.c) |
| `0x0042d080` | App | Replay timestamped `.lfr` filename assembly| [`RAW/app`](RAW/app/func_0042d080_replay_filename.c) | [`Compilable/app`](Compilable/app/replay_filename.c) |
| `0x0042e100` | Gameplay | Master 4,000-line combat attack dispatcher | [`RAW/gameplay`](RAW/gameplay/func_0042e100_attack_process.c) | [`Compilable/gameplay`](Compilable/gameplay/attack_process.c) |
| `0x00431b70` | App | Menu player join & controller input polling | [`RAW/app`](RAW/app/func_00431b70_menu_input.c) | [`Compilable/app`](Compilable/app/menu_input.c) |
| `0x00431c70` | App | Menu input reset & keyboard buffer restore | [`RAW/app`](RAW/app/func_00431c70_menu_reset.c) | [`Compilable/app`](Compilable/app/menu_reset.c) |
| `0x00431d10` | App | Main menu navigation, replay loader & links | [`RAW/app`](RAW/app/func_00431d10_menu_main.c) | [`Compilable/app`](Compilable/app/menu_main.c) |
| `0x00432ab0` | App | Championship tournament bracket state machine | [`RAW/app`](RAW/app/func_00432ab0_tournament.c) | [`Compilable/app`](Compilable/app/tournament.c) |
| `0x00434ab0` | App | 2-on-2 championship tournament state machine | [`RAW/app`](RAW/app/func_00434ab0_tournament_2on2.c) | [`Compilable/app`](Compilable/app/tournament_2on2.c) |
| `0x00436900` | App | Character spawn & battle setup | [`RAW/app`](RAW/app/func_00436900_battle_setup.c) | [`Compilable/app`](Compilable/app/battle_setup.c) |
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
| `0x0043cf40` | App | WinMain entry point & 30.3 FPS game loop | [`RAW/app`](RAW/app/func_0043cf40_winmain.c) | [`Compilable/app`](Compilable/app/winmain.c) |
| `0x0043e9a0` | App | Game mode setup & developer cheat switches | [`RAW/app`](RAW/app/func_0043e9a0_game_mode_mgr.c) | [`Compilable/app`](Compilable/app/game_mode_mgr.c) |
| `0x0043ef70` | Graphics | 2D software clipping against viewport | [`RAW/graphics`](RAW/graphics/func_0043ef70_clip_rect.c) | [`Compilable/graphics`](Compilable/graphics/clip_rect.c) |
| `0x0043f010` | Graphics | DirectDraw surface blit wrapper | [`RAW/graphics`](RAW/graphics/func_0043f010_surface_blit.c) | [`Compilable/graphics`](Compilable/graphics/surface_blit.c) |

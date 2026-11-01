# Compilable Legacy C (Human-Readable)

This directory contains a **self-contained, human-readable & compilable C translation** of the core routines extracted from `lf2.exe`.

While the pristine decompiler output is preserved untouched in [`decompiled/RAW/`](../RAW/) as forensic evidence, this suite:
1. Replaces raw byte pointer arithmetic (`*(int *)(obj + 0x2fc)`) with authentic, verified C structs (`obj->hp`, `obj->x`, `global->objects[i]`).
2. Eliminates obscure decompiler register artifacts (`in_ECX = (int)(intptr_t)in_ECX;`, `iVar1`, `uVar5`, `local_4`) in favor of descriptive variables and typed parameters (`global`, `self`, `min_dist`).
3. Preserves 100% mathematical and flag parity with the original MSVC x86 binary.
4. Provides both descriptive function interfaces (`lf2_teleport`, `lf2_does_attack_success`) and legacy MSVC calling convention bridges (`FUN_00403270`, `FUN_00417400`) for seamless interoperability.

---

## Directory Structure

```text
decompiled/Compilable/
├── include/
│   ├── legacy_types.h       # Ghidra synthetic primitives, math macros, Win32 structs
│   ├── legacy_globals.h     # External declarations for all 46 DAT_ global variables
│   └── legacy_signatures.h  # Forward prototypes for all 35 decompiled routines
├── app/                     # Window management, WinMain, WindowProc, game loop
├── audio/                   # DirectSound WAV loading, voice allocation, playback
├── core/
│   ├── legacy_globals.c     # Static allocation & zero-initialization of all global symbols
│   ├── func_004034e0_abs.c
│   ├── func_00417170_random.c
│   └── func_004171c0_overlap.c
├── data/                    # Dat lexer, Vigenère cipher, frame ctor, control.txt
├── gameplay/                # Combat dispatcher, hitbox checks, grapple, AI logic
├── graphics/                # DirectDraw initialization, blits, clipping, parallax
└── net/                     # Lockstep networking, socket initialization, packets
```

---

## Technical Infrastructure

To enable standard C compilers (GCC, Clang, MSVC) to compile the raw assembly pseudocode without rewriting its logic:

1. **Synthetic Type Definitions ([`legacy_types.h`](include/legacy_types.h)):**
   - Ghidra primitives: `undefined1`, `undefined2`, `undefined4`, `undefined8`, `byte`, `uint`, `ulonglong`, `float10` (80-bit x87 mapped to IEEE double).
   - Decompiler math macros: `NAN(x)`, `SBORROW4(a, b)`, `CARRY4(a, b)`.
   - Calling convention shims: `THISCALL` macro adapting MSVC `__thiscall` across compilers.
   - Compatibility headers: `tagMSG`, `struct tm`, WinSock and Win32 multimedia types.

2. **Global Symbol Allocation ([`legacy_globals.c`](core/legacy_globals.c)):**
   - Allocates and zero-initializes all 46 external `DAT_...` global memory locations (such as character table pointers, background scroll state, and tick counters).
   - Allocates the 3,000-byte circular PRNG table `DAT_004589c8`.

3. **Compiler Diagnostics & Register Fixes:**
   - **`in_ECX` Pointer Initialization:** In MSVC `__thiscall` routines, `in_ECX` is the incoming `this` pointer. Initialized as `undefined1 *in_ECX = (undefined1*)in_ECX;` across 6 member functions to silence modern compiler uninitialized-variable diagnostics while preserving 100% of member offset arithmetic.
   - **Pointer Width Safety:** In `load_dat.c`, file descriptor `local_4e8` is typed as `FILE *` instead of `undefined4` to ensure 64-bit file handle safety on modern architectures.
   - **String Format Casts:** In `winmain.c`, `&DAT_00451d48` and `&DAT_00458350` are cast to `(char*)` to satisfy `sprintf`.

---

## Compilation Instructions

Any individual file or the entire suite can be compiled into object files using standard GCC (UCRT64/MinGW) or Clang:

```powershell
# Compile a single routine
gcc -c -Iinclude gameplay/func_0042e100_attack_process.c -o attack_process.o

# Verify all 47 C translation units compile cleanly
Get-ChildItem -Recurse -Filter *.c | ForEach-Object {
    gcc -c -Iinclude $_.FullName -o ($_.BaseName + ".o")
}
Remove-Item *.o
```

---

## Routine Inventory

| Virtual Address | File Path | Subsystem | Function Name / Description |
| :--- | :--- | :--- | :--- |
| `0x004014e0` | [`audio/sound_load_wav.c`](audio/sound_load_wav.c) | Audio | RIFF WAVE sound buffer loader |
| `0x00401970` | [`audio/sound_init.c`](audio/sound_init.c) | Audio | DirectSound subsystem initialization |
| `0x00401a30` | [`audio/sound_play.c`](audio/sound_play.c) | Audio | DirectSound voice trigger |
| `0x00402980` | [`app/replay_notify.c`](app/replay_notify.c) | App | Replay recording screen notifications |
| `0x00402b80` | [`net/net_init.c`](net/net_init.c) | Network | WinSock initialization & socket setup |
| `0x00403270` | [`gameplay/teleport.c`](gameplay/teleport.c) | Gameplay | Rudolf teleportation targeting logic |
| `0x004034e0` | [`core/abs.c`](core/abs.c) | Core | Fast integer absolute value computation |
| `0x004061d0` | [`gameplay/object_init.c`](gameplay/object_init.c) | Gameplay | Entity constructor & default state initialization |
| `0x004068b0` | [`gameplay/grapple_sync.c`](gameplay/grapple_sync.c) | Gameplay | Grapple caught-target coordinate sync & throw release |
| `0x00406ba0` | [`gameplay/ai_process.c`](gameplay/ai_process.c) | Gameplay | AI combat decision tree & virtual key input synthesis |
| `0x00408ce0` | [`gameplay/weapon_sync.c`](gameplay/weapon_sync.c) | Gameplay | Weapon attachment point sync, drop & throw physics |
| `0x0040bbf0` | [`data/frame_ctor.c`](data/frame_ctor.c) | Data | Frame structure constructor & zeroing |
| `0x0040be70` | [`data/calc_frame_coords.c`](data/calc_frame_coords.c) | Data | Sprite sheet UV cell coordinate calculator |
| `0x0040d0a0` | [`data/save_dat.c`](data/save_dat.c) | Data | Character `.dat` file serializer |
| `0x0040ef70` | [`data/load_dat.c`](data/load_dat.c) | Data | Master `.dat` script lexer & block parser |
| `0x004143d0` | [`data/file_ctor.c`](data/file_ctor.c) | Data | Character file data structure constructor |
| `0x004148a0` | [`data/decrypt_dat.c`](data/decrypt_dat.c) | Data | 123-byte header skip & Vigenère cipher decrypter |
| `0x00415d00` | [`graphics/draw_object.c`](graphics/draw_object.c) | Graphics | Entity screen projection & mirror blit dispatch |
| `0x00417170` | [`core/random.c`](core/random.c) | Core | 3,000-byte precomputed circular PRNG lookup |
| `0x004171c0` | [`core/overlap.c`](core/overlap.c) | Core | 1D coordinate interval overlap detector |
| `0x00417400` | [`gameplay/does_attack_success.c`](gameplay/does_attack_success.c) | Gameplay | 3D AABB hitbox intersection testing (`itr` vs `bdy`) |
| `0x0041a2dd` | [`graphics/parallax_calc.c`](graphics/parallax_calc.c) | Graphics | Background parallax layer offset & seam wrapping |
| `0x0041c5f0` | [`net/net_lockstep.c`](net/net_lockstep.c) | Network | 22-byte lockstep packet send/recv & desync validation |
| `0x00423480` | [`data/control_txt.c`](data/control_txt.c) | Data | Player key config & grave-accent serializer (`control.txt`) |
| `0x0042d080` | [`app/replay_filename.c`](app/replay_filename.c) | App | Timestamped `.lfr` replay filename generator |
| `0x0042e100` | [`gameplay/attack_process.c`](gameplay/attack_process.c) | Gameplay | Master 4,000-line combat attack effect dispatcher |
| `0x00431b70` | [`app/menu_input.c`](app/menu_input.c) | App | Menu player join & controller input polling |
| `0x00431c70` | [`app/menu_reset.c`](app/menu_reset.c) | App | Menu input reset & keyboard buffer restore |
| `0x00431d10` | [`app/menu_main.c`](app/menu_main.c) | App | Main menu navigation, replay loader & links |
| `0x00432ab0` | [`app/tournament.c`](app/tournament.c) | App | Championship tournament bracket state machine |
| `0x00434ab0` | [`app/tournament_2on2.c`](app/tournament_2on2.c) | App | 2-on-2 championship tournament state machine |
| `0x00436900` | [`app/battle_setup.c`](app/battle_setup.c) | App | Player/CPU entity spawn initialization & battle setup |
| `0x00436fc0` | [`app/stage_advance.c`](app/stage_advance.c) | App | Stage/survival wave advance & player vitals recovery |
| `0x00437220` | [`app/survival_curtain.c`](app/survival_curtain.c) | App | Stage clear / survival game-over transition curtain |
| `0x00437400` | [`app/spawn_unit.c`](app/spawn_unit.c) | App | Unit spawn allocation & world object table insert |
| `0x00437860` | [`app/battle_status.c`](app/battle_status.c) | App | Battle status HUD, reinforcement waves & survival timer |
| `0x004389a0` | [`app/draw_select_rect.c`](app/draw_select_rect.c) | Graphics | Selection cursor animated border renderer |
| `0x00438ad0` | [`app/draw_border_rect.c`](app/draw_border_rect.c) | Graphics | Outlined rectangle border renderer |
| `0x00438b40` | [`app/battle_mode.c`](app/battle_mode.c) | App | Master Battle Mode army & skirmish squad manager |
| `0x0043b3d0` | [`app/wndproc.c`](app/wndproc.c) | App | Win32 WindowProc, key table & cheat code recognizers |
| `0x0043bdd0` | [`app/create_window.c`](app/create_window.c) | App | Win32 `CreateWindowEx` setup |
| `0x0043bec0` | [`graphics/init_display.c`](graphics/init_display.c) | Graphics | DirectDraw 6 display mode initialization |
| `0x0043cf40` | [`app/winmain.c`](app/winmain.c) | App | WinMain entry point & 30.3 FPS game loop |
| `0x0043e9a0` | [`app/game_mode_mgr.c`](app/game_mode_mgr.c) | App | Game mode setup & developer cheat switches |
| `0x0043ef70` | [`graphics/clip_rect.c`](graphics/clip_rect.c) | Graphics | 2D software clipping against screen boundaries |
| `0x0043f010` | [`graphics/surface_blit.c`](graphics/surface_blit.c) | Graphics | DirectDraw surface blit wrapper |


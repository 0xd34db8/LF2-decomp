# Compilable Legacy C

This dir contains a **self-contained, compilable C translation** of all 35 routines extracted from `lf2.exe`.

While the pristine decompiler output is preserved untouched in [`decompiled/RAW/`](../RAW/), this suite resolves all missing types, calling convention semantics, and global memory mappings, allowing every routine to compile cleanly as native C with zero syntax or symbol errors.

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

1. **Synthetic Type Definitions ([`legacy_types.h`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/include/legacy_types.h)):**
   - Ghidra primitives: `undefined1`, `undefined2`, `undefined4`, `undefined8`, `byte`, `uint`, `ulonglong`, `float10` (80-bit x87 mapped to IEEE double).
   - Decompiler math macros: `NAN(x)`, `SBORROW4(a, b)`, `CARRY4(a, b)`.
   - Calling convention shims: `THISCALL` macro adapting MSVC `__thiscall` across compilers.
   - Compatibility headers: `tagMSG`, `struct tm`, WinSock and Win32 multimedia types.

2. **Global Symbol Allocation ([`legacy_globals.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/core/legacy_globals.c)):**
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

# Verify all 35 C translation units compile cleanly
Get-ChildItem -Recurse -Filter *.c | ForEach-Object {
    gcc -c -Iinclude $_.FullName -o ($_.BaseName + ".o")
}
Remove-Item *.o
```

---

## Routine Inventory

| Virtual Address | File Path | Subsystem | Function Name / Description |
| :--- | :--- | :--- | :--- |
| `0x004014e0` | [`audio/func_004014e0_sound_load_wav.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/audio/func_004014e0_sound_load_wav.c) | Audio | RIFF WAVE sound buffer loader |
| `0x00401970` | [`audio/func_00401970_sound_init.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/audio/func_00401970_sound_init.c) | Audio | DirectSound subsystem initialization |
| `0x00401a30` | [`audio/func_00401a30_sound_play.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/audio/func_00401a30_sound_play.c) | Audio | DirectSound voice trigger |
| `0x00402980` | [`app/func_00402980_replay_notify.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/app/func_00402980_replay_notify.c) | App | Replay recording screen notifications |
| `0x00402b80` | [`net/func_00402b80_net_init.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/net/func_00402b80_net_init.c) | Network | WinSock initialization & socket setup |
| `0x00403270` | [`gameplay/func_00403270_teleport.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/gameplay/func_00403270_teleport.c) | Gameplay | Rudolf teleportation targeting logic |
| `0x004034e0` | [`core/func_004034e0_abs.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/core/func_004034e0_abs.c) | Core | Fast integer absolute value computation |
| `0x004061d0` | [`gameplay/func_004061d0_object_init.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/gameplay/func_004061d0_object_init.c) | Gameplay | Entity constructor & default state initialization |
| `0x004068b0` | [`gameplay/func_004068b0_grapple_sync.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/gameplay/func_004068b0_grapple_sync.c) | Gameplay | Grapple caught-target coordinate sync & throw release |
| `0x00406ba0` | [`gameplay/func_00406ba0_ai_process.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/gameplay/func_00406ba0_ai_process.c) | Gameplay | AI combat decision tree & virtual key input synthesis |
| `0x00408ce0` | [`gameplay/func_00408ce0_weapon_sync.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/gameplay/func_00408ce0_weapon_sync.c) | Gameplay | Weapon attachment point sync, drop & throw physics |
| `0x0040bbf0` | [`data/func_0040bbf0_frame_ctor.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/data/func_0040bbf0_frame_ctor.c) | Data | Frame structure constructor & zeroing |
| `0x0040be70` | [`data/func_0040be70_calc_frame_coords.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/data/func_0040be70_calc_frame_coords.c) | Data | Sprite sheet UV cell coordinate calculator |
| `0x0040d0a0` | [`data/func_0040d0a0_save_dat.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/data/func_0040d0a0_save_dat.c) | Data | Character `.dat` file serializer |
| `0x0040ef70` | [`data/func_0040ef70_load_dat.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/data/func_0040ef70_load_dat.c) | Data | Master `.dat` script lexer & block parser |
| `0x004143d0` | [`data/func_004143d0_file_ctor.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/data/func_004143d0_file_ctor.c) | Data | Character file data structure constructor |
| `0x004148a0` | [`data/func_004148a0_decrypt_dat.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/data/func_004148a0_decrypt_dat.c) | Data | 123-byte header skip & Vigenère cipher decrypter |
| `0x00415d00` | [`graphics/func_00415d00_draw_object.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/graphics/func_00415d00_draw_object.c) | Graphics | Entity screen projection & mirror blit dispatch |
| `0x00417170` | [`core/func_00417170_random.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/core/func_00417170_random.c) | Core | 3,000-byte precomputed circular PRNG lookup |
| `0x004171c0` | [`core/func_004171c0_overlap.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/core/func_004171c0_overlap.c) | Core | 1D coordinate interval overlap detector |
| `0x00417400` | [`gameplay/func_00417400_does_attack_success.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/gameplay/func_00417400_does_attack_success.c) | Gameplay | 3D AABB hitbox intersection testing (`itr` vs `bdy`) |
| `0x0041a2dd` | [`graphics/func_0041a2dd_parallax_calc.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/graphics/func_0041a2dd_parallax_calc.c) | Graphics | Background parallax layer offset & seam wrapping |
| `0x0041c5f0` | [`net/func_0041c5f0_net_lockstep.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/net/func_0041c5f0_net_lockstep.c) | Network | 22-byte lockstep packet send/recv & desync validation |
| `0x00423480` | [`data/func_00423480_control_txt.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/data/func_00423480_control_txt.c) | Data | Player key config & grave-accent serializer (`control.txt`) |
| `0x0042d080` | [`app/func_0042d080_replay_filename.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/app/func_0042d080_replay_filename.c) | App | Timestamped `.lfr` replay filename generator |
| `0x0042e100` | [`gameplay/func_0042e100_attack_process.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/gameplay/func_0042e100_attack_process.c) | Gameplay | Master 4,000-line combat attack effect dispatcher |
| `0x00436900` | [`app/func_00436900_battle_setup.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/app/func_00436900_battle_setup.c) | App | Player/CPU entity spawn initialization & battle setup |
| `0x0043b3d0` | [`app/func_0043b3d0_wndproc.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/app/func_0043b3d0_wndproc.c) | App | Win32 WindowProc, key table & cheat code recognizers |
| `0x0043bdd0` | [`app/func_0043bdd0_create_window.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/app/func_0043bdd0_create_window.c) | App | Win32 `CreateWindowEx` setup |
| `0x0043bec0` | [`graphics/func_0043bec0_init_display.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/graphics/func_0043bec0_init_display.c) | Graphics | DirectDraw 6 display mode initialization |
| `0x0043cf40` | [`app/func_0043cf40_winmain.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/app/func_0043cf40_winmain.c) | App | WinMain entry point & 30.3 FPS game loop |
| `0x0043e9a0` | [`app/func_0043e9a0_game_mode_mgr.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/app/func_0043e9a0_game_mode_mgr.c) | App | Game mode setup & developer cheat switches |
| `0x0043ef70` | [`graphics/func_0043ef70_clip_rect.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/graphics/func_0043ef70_clip_rect.c) | Graphics | 2D software clipping against screen boundaries |
| `0x0043f010` | [`graphics/func_0043f010_surface_blit.c`](file:///a:/Work/Visual Studio Projects/LF2/decompiled/Compilable/graphics/func_0043f010_surface_blit.c) | Graphics | DirectDraw surface blit wrapper |


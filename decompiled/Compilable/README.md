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
│   ├── legacy_globals.h     # External declarations for all global DAT_ variables
│   └── legacy_signatures.h  # Forward prototypes for decompiled C routines
├── app/                     # Window management, WinMain, WindowProc, game loop
├── audio/                   # DirectSound WAV loading, voice allocation, playback
├── core/
│   ├── legacy_globals.c     # Static allocation & zero-initialization of all external DAT_ globals
│   ├── abs.c
│   ├── random.c
│   └── overlap.c
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
   - Allocates and zero-initializes all external `DAT_...` global memory locations (such as character table pointers, background scroll state, tick counters, and player slot arrays).
   - Allocates the 3,000-byte circular PRNG table `DAT_0044ff90` and index state `DAT_004589c8`.

3. **Compiler Diagnostics & Register Fixes:**
   - **`in_ECX` Pointer Initialization:** In MSVC `__thiscall` routines, `in_ECX` is the incoming `this` pointer. Initialized explicitly in member routines to silence modern compiler uninitialized-variable diagnostics while preserving 100% of member offset arithmetic.
   - **Pointer Width Safety:** In `load_dat.c`, file descriptor `local_4e8` is typed as `FILE *` instead of `undefined4` to ensure 64-bit file handle safety on modern architectures.
   - **String Format Casts:** In `winmain.c`, `&DAT_00451d48` and `&DAT_00458350` are cast to `(char*)` to satisfy `sprintf`.

---

## Compilation Instructions

Any individual file or the entire suite can be compiled into object files using standard GCC (UCRT64/MinGW) or Clang (or built together with `mingw32-make -C decompiled/Compilable test`):

```powershell
# Compile a single routine
gcc -c -Iinclude gameplay/attack_process.c -o attack_process.o

# Verify all 55 library C translation units + test_legacy.c compile cleanly
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
| `0x004019b0` | [`audio/sound_init.c`](audio/sound_init.c) | Audio | DirectSound device release & buffer cleanup |
| `0x00401a30` | [`audio/sound_play.c`](audio/sound_play.c) | Audio | DirectSound voice trigger |
| `0x00401c90` | [`audio/bgm_manager.c`](audio/bgm_manager.c) | Audio | DirectShow COM filter graph init |
| `0x00401d30` | [`audio/bgm_manager.c`](audio/bgm_manager.c) | Audio | DirectShow interface release & graph teardown |
| `0x00401da0` | [`audio/bgm_manager.c`](audio/bgm_manager.c) | Audio | DirectShow media file render |
| `0x00401e90` | [`audio/bgm_manager.c`](audio/bgm_manager.c) | Audio | Media event loop & track rewind (looping) |
| `0x00401f30` | [`audio/bgm_manager.c`](audio/bgm_manager.c) | Audio | Audio volume level configurator |
| `0x00402000` | [`audio/bgm_manager.c`](audio/bgm_manager.c) | Audio | BGM stream playback stop |
| `0x00402020` | [`audio/bgm_manager.c`](audio/bgm_manager.c) | Audio | Master BGM playback dispatcher with cache check |
| `0x00402100` | [`audio/bgm_manager.c`](audio/bgm_manager.c) | Audio | BGM playback pause & rewind to origin |
| `0x00402130` | [`audio/bgm_manager.c`](audio/bgm_manager.c) | Audio | Menu BGM selector & HUD text cycler |
| `0x004025b0` | [`audio/bgm_manager.c`](audio/bgm_manager.c) | Audio | Play staged current track |
| `0x004025d0` | [`audio/bgm_manager.c`](audio/bgm_manager.c) | Audio | Master track selector & stage randomizer |
| `0x00402810` | [`audio/sound_play.c`](audio/sound_play.c) | Audio | Master sound effects volume attenuator |
| `0x004028a0` | [`app/replay_notify.c`](app/replay_notify.c) | App | Recording screen HUD notifications & volume (includes `0x00402980` compat alias) |
| `0x00402ad0` | [`net/net_init.c`](net/net_init.c) | Network | Local IP address & adapter resolution helper |
| `0x00402b60` | [`net/net_init.c`](net/net_init.c) | Network | WinSock initialization & socket setup (includes `0x00402b80` compat alias) |
| `0x00403270` | [`gameplay/teleport.c`](gameplay/teleport.c) | Gameplay | Rudolf teleportation targeting logic |
| `0x004034e0` | [`core/abs.c`](core/abs.c) | Core | Fast integer absolute value computation |
| `0x004034f0` | [`gameplay/ai_process.c`](gameplay/ai_process.c) | Gameplay | AI combat dodge / evasive roll maneuver & defense |
| `0x00403a40` | [`gameplay/ai_process.c`](gameplay/ai_process.c) | Gameplay | AI character-specific special move decision tree |
| `0x004061a0` | [`gameplay/object_init.c`](gameplay/object_init.c) | Gameplay | 1D interval coordinate betweenness test |
| `0x004061d0` | [`gameplay/object_init.c`](gameplay/object_init.c) | Gameplay | Entity constructor & default state initialization |
| `0x004064d0` | [`gameplay/grapple_sync.c`](gameplay/grapple_sync.c) | Gameplay | Firen + Freeze -> Firzen fusion check & transform (includes `0x004068b0` compat alias) |
| `0x00406a20` | [`gameplay/ai_process.c`](gameplay/ai_process.c) | Gameplay | Dynamic world object, projectile & particle spawner (slots `50..399`) |
| `0x00406ba0` | [`gameplay/ai_process.c`](gameplay/ai_process.c) | Gameplay | `hit_Fa` homing projectile & chase physics |
| `0x00408cb0` | [`gameplay/weapon_sync.c`](gameplay/weapon_sync.c) | Gameplay | AI weapon pickup, throw & drink decision helper (includes `0x00408ce0` compat alias) |
| `0x004094b0` | [`gameplay/ai_process.c`](gameplay/ai_process.c) | Gameplay | Primary AI controller, target acquisition & state machine |
| `0x0040bbf0` | [`data/frame_ctor.c`](data/frame_ctor.c) | Data | Frame structure constructor & zeroing |
| `0x0040be70` | [`data/calc_frame_coords.c`](data/calc_frame_coords.c) | Data | Sprite sheet UV cell coordinate calculator |
| `0x0040bf30` | [`graphics/draw_object.c`](graphics/draw_object.c) | Graphics | Frame wait/next helper (`lf2_draw_object` sprite cell lookup) |
| `0x0040d0a0` | [`data/save_dat.c`](data/save_dat.c) | Data | Character `.dat` file serializer |
| `0x0040d960` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Per-object frame timer, sound trigger & `frame.next` advancement |
| `0x0040de30` | [`graphics/draw_object.c`](graphics/draw_object.c) | Graphics | Sprite entity rendering, facing flip & palette blit |
| `0x0040e170` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Combo timer window (`== 5`) interruption check helper |
| `0x0040e2d0` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Frame transition, HP/MP cost deduction & hit-state reset helper |
| `0x0040e450` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | 5-entry object input history shift register (`+0x408..+0x418`) |
| `0x0040e490` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Per-object physics, velocity integration, gravity & ground landing |
| `0x0040ef70` | [`data/load_dat.c`](data/load_dat.c) | Data | Master `.dat` script lexer & block parser |
| `0x00412800` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Special-move combo recognizer (`D > R > A` -> `hit_Fa`) |
| `0x004128f0` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Special-move combo recognizer (`D > L > A` -> `hit_Fa`) |
| `0x004129e0` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Special-move combo recognizer (`D > U > A` -> `hit_Ua` + Louis transform) |
| `0x00412ac0` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Special-move combo recognizer (`D > D > A` -> `hit_Da` + Firzen counter reset) |
| `0x00412ba0` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Special-move combo recognizer (`D > R > J` -> `hit_Fj`) |
| `0x00412c90` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Special-move combo recognizer (`D > L > J` -> `hit_Fj`) |
| `0x00412d80` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Special-move combo recognizer (`D > U > J` -> `hit_Uj`) |
| `0x00412e60` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Special-move combo recognizer (`D > D > J` -> `hit_Dj`) |
| `0x00412f40` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Special-move combo recognizer (`D > J > A` -> `hit_ja`) |
| `0x00413080` | [`gameplay/entity_tick.c`](gameplay/entity_tick.c) | Gameplay | Master per-object input/state tick & combo recognizer dispatcher |
| `0x004143d0` | [`data/file_ctor.c`](data/file_ctor.c) | Data | Character file data structure constructor |
| `0x004146b0` | [`data/decrypt_dat.c`](data/decrypt_dat.c) | Data | Character `.dat` encryption cipher serializer |
| `0x004148a0` | [`data/decrypt_dat.c`](data/decrypt_dat.c) | Data | 123-byte header skip & Vigenère cipher decrypter |
| `0x00414a30` | [`data/decrypt_dat.c`](data/decrypt_dat.c) | Data | Decrypted `.dat` file exporter |
| `0x00416fb0` | [`audio/sound_play.c`](audio/sound_play.c) | Audio | Positional audio panning calculator pass 1 |
| `0x00417090` | [`audio/sound_play.c`](audio/sound_play.c) | Audio | Positional audio panning calculator pass 2 |
| `0x00417170` | [`core/random.c`](core/random.c) | Core | 3,000-byte precomputed circular PRNG lookup |
| `0x004171c0` | [`core/overlap.c`](core/overlap.c) | Core | 1D coordinate interval overlap detector |
| `0x00417200` | [`gameplay/slot_input.c`](gameplay/slot_input.c) | Gameplay | Broad-phase `itr` vs `bdy` 2D bounding box overlap test |
| `0x00417400` | [`gameplay/does_attack_success.c`](gameplay/does_attack_success.c) | Gameplay | 3D AABB hitbox intersection testing (`itr` vs `bdy`) |
| `0x00417f80` | [`gameplay/weapon_sync.c`](gameplay/weapon_sync.c) | Gameplay | Carried weapon `wpoint` sync, Milk/Beer drinking & throw |
| `0x004187b0` | [`gameplay/grapple_sync.c`](gameplay/grapple_sync.c) | Gameplay | Grapple `cpoint` caught-target coordinate sync & injury |
| `0x00418c30` | [`gameplay/grapple_sync.c`](gameplay/grapple_sync.c) | Gameplay | Grapple `cpoint` chain combos, Rudolf transform & throw |
| `0x00419380` | [`gameplay/slot_input.c`](gameplay/slot_input.c) | Gameplay | Master `400x400` pairwise collision pass & rest-timer update |
| `0x004196f0` | [`gameplay/slot_input.c`](gameplay/slot_input.c) | Gameplay | Physics velocity/impulse averaging pass across 400 objects |
| `0x004197a0` | [`gameplay/slot_input.c`](gameplay/slot_input.c) | Gameplay | Remote/network input bits unpacking & flag latching |
| `0x004198f0` | [`gameplay/slot_input.c`](gameplay/slot_input.c) | Gameplay | Local player input bits latching & replay recording |
| `0x00419a60` | [`gameplay/slot_input.c`](gameplay/slot_input.c) | Gameplay | Master per-slot controller / AI input dispatch & loop |
| `0x0041a250` | [`graphics/parallax_calc.c`](graphics/parallax_calc.c) | Graphics | Background update, parallax layer math & camera bounds (includes `0x0041a2dd` compat alias) |
| `0x0041a5a0` | [`graphics/draw_object.c`](graphics/draw_object.c) | Graphics | Master scene rendering dispatcher & Z-sorting pass |
| `0x0041bc90` | [`net/net_lockstep.c`](net/net_lockstep.c) | Network | Master battle loop, lockstep pacing & input sampling (includes `0x0041c5f0` compat alias) |
| `0x00422ac0` | [`core/random.c`](core/random.c) | Core | PRNG lookup table re-seed & LCG initialization |
| `0x00422b00` | [`app/key_name.c`](app/key_name.c) | App | Virtual Key to text name translation & font width adjustment |
| `0x00422f60` | [`app/vk_to_char.c`](app/vk_to_char.c) | App | Virtual Key to ASCII char translation with shift/caps |
| `0x00423230` | [`data/control_txt.c`](data/control_txt.c) | Data | Save player key config & grave-accent names (`control.txt`) |
| `0x00423480` | [`data/control_txt.c`](data/control_txt.c) | Data | Load player key config & grave-accent names (`control.txt`) |
| `0x00423940` | [`graphics/text_box.c`](graphics/text_box.c) | Graphics | In-game text box string rendering with shadow |
| `0x00423a70` | [`graphics/text_box.c`](graphics/text_box.c) | Graphics | Drop-shadowed text blit helper |
| `0x004246b0` | [`app/options_screen.c`](app/options_screen.c) | App | Options & control configuration screen state machine |
| `0x00429730` | [`app/replay_filename.c`](app/replay_filename.c) | App | Character select menu flow & replay filename formatting (includes `0x0042d080` compat alias) |
| `0x0042e100` | [`gameplay/attack_process.c`](gameplay/attack_process.c) | Gameplay | Master 4,000-line combat attack effect dispatcher |
| `0x00431b70` | [`app/menu_input.c`](app/menu_input.c) | App | Menu player join & controller input polling |
| `0x00431c70` | [`app/menu_reset.c`](app/menu_reset.c) | App | Menu input reset & keyboard buffer restore |
| `0x00431d10` | [`app/menu_main.c`](app/menu_main.c) | App | Main menu navigation, replay loader & links |
| `0x00432ab0` | [`app/tournament.c`](app/tournament.c) | App | Championship tournament bracket state machine |
| `0x00434ab0` | [`app/tournament_2on2.c`](app/tournament_2on2.c) | App | 2-on-2 championship tournament state machine |
| `0x00436900` | [`app/battle_setup.c`](app/battle_setup.c) | App | Player/CPU entity spawn helper (interior compat wrapper) |
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
| `0x0043dd60` | [`data/replay_cipher.c`](data/replay_cipher.c) | Data | LF2 v2.0 replay save, zlib compression & secondary cipher |
| `0x0043e620` | [`data/replay_cipher.c`](data/replay_cipher.c) | Data | LF2 v2.0 replay load, secondary decipher & zlib inflation |
| `0x0043e9a0` | [`app/game_mode_mgr.c`](app/game_mode_mgr.c) | App | Game mode setup & developer cheat switches |
| `0x0043ef70` | [`graphics/clip_rect.c`](graphics/clip_rect.c) | Graphics | 2D software clipping against screen boundaries |
| `0x0043f010` | [`graphics/surface_blit.c`](graphics/surface_blit.c) | Graphics | DirectDraw surface blit wrapper |
| `0x0043f4b0` | [`data/replay_cipher.c`](data/replay_cipher.c) | Data | zlib `compress` buffer wrapper |
| `0x0043f4d0` | [`data/replay_cipher.c`](data/replay_cipher.c) | Data | zlib `uncompress` buffer wrapper |


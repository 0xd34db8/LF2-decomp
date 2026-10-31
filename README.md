# Little Fighter 2 | 1:1 C++ Source Lift

A true 1:1 C++20 source decompilation and modernization of the original *Little Fighter 2* (`lf2.exe`, version 1.9c / 2.0a, x86-32 MSVC++).

This project is a systems programming and binary reverse engineering exercise designed to extract, lift, and preserve the authentic game logic (state machines, frame-accurate timings, hitbox collision mathematics, and data-driven file loading) while shedding legacy DirectDraw 6 and Win32 dependencies in favor of a modern cross-platform architecture.

---

## Prior Art vs. What We Are Doing

Over the last two decades, the Little Fighter 2 community has attempted several ambitious projects to modernize or recreate the game. To understand our mission, it is vital to distinguish between modding, clean-room rewrites, and true binary source lifting:

### What Other Projects Did

* **External Scripting Rewrites:**
* *Their Approach:* Building a modern engine from scratch and delegating game logic to an external scripting engine, loosely inspired by the original mechanics.
* *Why it differs:* It is a from-scratch recreation that abandons the original compiled execution flow, state transitions, and arithmetic quirks.


* **Dynamic Memory Patching & DLL Hijacking:**
* *Their Approach:* Intercepting legacy graphics API calls via proxy wrappers and injecting custom logic hooks directly into the closed-source process at runtime.
* *Why it differs:* This is dynamic memory modding. It still depends entirely on running the closed-source legacy executable in the background rather than freeing the source code from the binary.


* **Clean-Room Interpretation Clones:**
* *Their Approach:* Building an engine clone from scratch by applying modern object-oriented software engineering principles and design patterns.
* *Why it differs:* While architecturally elegant, these represent a high-level interpretation of how the game *should* work, rather than extracting how the shipped binary actually operates.


* **Open-Source Engine Reimplementations:**
* *Their Approach:* Modern clean-room clones built with contemporary frameworks and libraries specifically to load legacy asset files.
* *Why it differs:* These independent reimplementations approximate the game's mechanics but lack the authentic assembly state machines, deterministic random generators, and timing quirks.


* **Manual Decompilation Attempts:**
* *Their Approach:* Translating raw disassembly into intermediate scripting languages or partial C stubs function-by-function.
* *Why it differs:* Historically, these massive forensic undertakings suffer from burnout and are abandoned before a compilable, fully modernized game engine is completed, leaving behind uncorrected offset errors and partial stubs.



### What WE Are Doing: True 1:1 Source Lifting

1. **Extracting, Not Guessing:** We do not invent custom OOP hierarchies, we do not guess class offsets, and we do not write high-level approximations. We decompile the compiled x86-32 MSVC++ machine code directly from the original executable and reconstruct the authentic logic in modern C++.
2. **Byte-Level Mathematical Fidelity:** Collision detection, axis-aligned bounding box projections, directional facing mirrors, velocity integrations, deterministic lookup tables, and frame state machines are mathematically identical to the original assembly.
3. **Liberation & Modernization:** We strip away deprecated Win32 message pumps and legacy DirectDraw 6 surface management, replacing them with a portable modern C++20 / SDL2 architecture that compiles and runs cleanly across modern 32-bit and 64-bit operating systems.

---

## Architecture & Project Layout

```text
LF2/
├── decompiled/                 # Ground-truth raw C decompilations from Ghidra
│   ├── func_00403270_teleport.c
│   ├── func_004034e0_abs.c
│   ├── func_0040bbf0_frame_ctor.c
│   ├── func_0040d0a0_save_dat.c
│   ├── func_0040ef70_load_dat.c
│   ├── func_004143d0_file_ctor.c
│   ├── func_004148a0_decrypt_dat.c
│   ├── func_00417170_random.c
│   ├── func_004171c0_overlap.c
│   ├── func_00417400_does_attack_success.c
│   ├── func_0042e100_attack_process.c
│   ├── func_0043b3d0_wndproc.c
│   ├── func_0043bdd0_create_window.c
│   ├── func_0043bec0_init_display.c
│   ├── func_0043cf40_winmain.c
│   └── func_0043e9a0_game_mode_mgr.c
├── constants.h                 # File IDs, object types, states, weapon IDs
├── types.h                     # Portable native pointer definitions
├── bdy.h                       # Bounding box collision struct (0x28 / 40 bytes)
├── itr.h                       # Interaction hitbox struct (0x50 / 80 bytes)
├── frame.h                     # Frame state machine (0x178 / 376 bytes)
├── file.h                      # Character / weapon definition (0x25360 / 152,416 bytes)
├── object.h                    # World entity instance (0x370 / 880 bytes)
├── global.h                    # World manager state & method interfaces
├── overlap.h                   # 2D axis-aligned bounding box intersection math (0x4171C0)
├── random_table.h              # 3,000-byte precomputed PRNG table extracted from .data
├── random.h / random.cpp       # Deterministic PRNG implementation (0x417170)
├── teleport.cpp                # 1:1 Rudolf teleportation logic (0x403270)
├── attack.cpp                  # 1:1 Hitbox collision & attack queueing (0x417400)
├── cipher.h / cipher.cpp       # Authentic Vigenère .dat cipher & decryptor (0x4148a0)
├── data_txt.h / data_txt.cpp   # Manifest parser for data/data.txt
├── dat_loader.h / dat_loader.cpp # Full .dat script tokenizer and loader (0x40ef70)
├── app.h / app.cpp             # Modern SDL2 lifecycle, fixed 30 FPS pacing, input table
├── main.cpp                    # Application entry point & headless test harness
├── verify_memory_maps.cpp      # Memory map & collision math verification suite
├── test_data_loader.cpp        # Data-driven core & cipher verification suite
├── REFERENCE_ERRORS.md         # Documented inaccuracies in prior decompilation attempts
└── Makefile                    # Automated build script (MSYS2 UCRT64 GCC)
```

---

## Core Directives & Verification
1. **Never Guess Offsets:** Every struct size and member variable offset is verified against Ghidra decompiler pseudocode and backed by compile-time `static_assert` statements.
2. **Strict Adherence to Math:** Floating-point velocity integrations, hitbox coordinates, and frame timers are mathematically identical to the original x86 disassembly.
3. **Dual-Target Portability:** Pointers and struct layouts are designed to maintain byte-offset parity on 32-bit compilation targets while running without memory truncation or segmentation faults on modern 64-bit systems.

---

## Data Structure Memory Maps

| Structure | Size (Hex) | Size (Bytes) | Description |
| :--- | :--- | :--- | :--- |
| `bdy_t` | `0x28` | 40 | Bounding box / physical collision boundary |
| `itr_t` | `0x50` | 80 | Interaction zone / attack hitbox / throw / catch |
| `opoint_t` | `0x20` | 32 | Projectile / weapon / particle spawn coordinate |
| `bpoint_t` | `0x0C` | 12 | Damage blood / impact particle coordinate |
| `cpoint_t` | `0x44` | 68 | Catch & throw interaction point |
| `wpoint_t` | `0x24` | 36 | Weapon attachment & holding position |
| `frame_t` | `0x178` | 376 | Animation frame state machine & hitbox arrays |
| `file_t` | `0x25360` | 152,416 | Character / weapon definition file (400 frames) |
| `object_t` | `0x370` | 880 | Monolithic entity instance in game world |
| `global_t` | `0x8D8`* | 2,264* | World manager (`0x458B00` static address) |

*\* Note: On 64-bit targets, pointers expand to 8 bytes, cleanly adjusting pointer table sizes in `global_t` without shifting fixed-offset member fields.*

---

## Building and Testing

### Prerequisites
- MSYS2 UCRT64 GCC 14.2.0 (or any modern C++20 compiler)
- `make` or `mingw32-make`

### Build & Run Tests
```bash
# Build the static library (liblf2.a) and test suite (verify_memory_maps.exe)
mingw32-make

# Execute all static and runtime verification tests
mingw32-make test
```

### Expected Output
```text
=== Little Fighter 2 Memory Map Verification ===
[+] bdy_t size:    0x28 (40 bytes)
[+] itr_t size:    0x50 (80 bytes)
[+] opoint_t size: 0x20 (32 bytes)
[+] bpoint_t size: 0xc (12 bytes)
[+] cpoint_t size: 0x44 (68 bytes)
[+] wpoint_t size: 0x24 (36 bytes)
[+] frame_t size:  0x178 (376 bytes)
[+] file_t size:   0x25360 (152416 bytes)
[+] object_t size: 0x370 (880 bytes)
[+] global_t size: 0x101c (4124 bytes)

[+] Testing 1:1 lifted teleport logic...
    Rudolf pos: (380, 0, 221)

[+] Testing 1:1 lifted does_attack_success collision logic...
    Attacks registered: 1
    Z-out-of-bounds correctly ignored: 0

[SUCCESS] All data structures, binary alignments, and lifted logic verified 100%!

=== Little Fighter 2 Data-Driven Core Verification ===
[+] Testing Cipher Encryption & Decryption Round-Trip...
    Round-trip successfully restored exact plaintext!
[+] Testing Decryption of Authentic .legacy/data/template.dat...
    template.dat decrypted successfully (53588 bytes)!
[+] Testing Parser for Authentic .legacy/data/data.txt...
    data.txt loaded 65 objects and 12 backgrounds.
[+] Testing Full .dat Parser on .legacy/data/davis.dat...
    davis.dat parsed successfully:
      Name: Davis
      Head: sprite\sys\davis_f.bmp
      Walking speed: 5
      Frame 0: pic=0, bdy=(43x62)
      Frame 5: pic=4, catch itr=(25x65)
[+] Testing Serialization to String & Re-parsing...
[SUCCESS] All Data-Driven Core tests passed with 100% precision!

==================================================
 Little Fighter 2 - Modern C++ Source Lift
 Authentic 1:1 Logic & SDL2 Modern Execution Core
==================================================
[LF2] Initializing Application Core (794x550)...
[LF2] Window & Renderer initialized successfully.
[LF2] Fixed frame pacing: 33 ms (~30.3 FPS), 100 ms lag clamp.
[LF2] Input mapping: 256-byte Win32-compatible key state table.
[LF2] Running in automated verification test mode for 30 frames...
[LF2 TEST SUCCESS] 'lf2.net' cheat successfully detected and unlocked!
[LF2 TEST SUCCESS] 'herofighter.com' cheat successfully detected and unlocked!
[LF2 TEST SUCCESS] 'ABC' developer mode cheat successfully detected and unlocked!
[LF2 TEST SUCCESS] Frame pacing and event loop executed 30 frames cleanly.
```

---

## Reverse-Engineered Secrets, Ciphers & Easter Eggs

Ghidra decompilation and binary disassembly revealed several fascinating, historic internal mechanics and easter eggs embedded directly into the machine code of `lf2.exe`:

### 1. The Legendary Resource Decryption Key: `"SiuHungIsAGoodBearBecauseHeIsVeryGood"`
* **Memory Location:** Hardcoded in the `.rdata` section at virtual address `0x0044892c` (file offset `0x4792c`).
* **Origin & Fun Fact:** "Siu Hung" (小熊) is the Cantonese pseudonym of Marti Wong (黃小熊), co-creator of Little Fighter 2 alongside Starsky Wong. Translated from Cantonese, it means:
  > *"Little Bear is a good bear because he is very good."*
* **The Cipher Architecture:** LF2 encodes all game resources (`.dat` files) using a byte-wise additive/subtractive variant of the Vigenère cipher operating modulo 256.
* **The 123-Byte Header Trick:** Every `.dat` file begins with a 123-byte (`0x7B`) padding header. In `FUN_004148a0`, the decryptor steps through the key `(key_idx + 1) % 37` for each of the 123 dummy bytes before decrypting any payload data. Since `123 % 37 = 12`, payload decryption always begins at key index `12` (the character `'G'` in `"GoodBear..."`):
  $$\text{plaintext\_byte} = (\text{cipher\_byte} - \text{key}[k] + 256) \pmod{256}$$
* **Modding Community Nostalgia:** For over two decades, this hardcoded string has been celebrated among LF2 modders who reverse-engineered the binary to create data decrypters (e.g. *LF2 Data Changer*).

### 2. Secret Cheat Code State Machines in WindowProc (`0x0043b3d0`)
The original window procedure maintains static state counters that detect sequential keystrokes typed anywhere in the application:
* **`"lf2.net"` (Roster Unlock):** Typing `L` -> `F` -> `2` -> `.` -> `N` -> `E` -> `T` increments state tracker `DAT_0045857c` and sets `DAT_00455471 = 'd'` (ASCII 0x64). This unlocks Julian, Firzen, and LouisEX on the character selection screen along with other enemy characters, which are non playable by default.
* **`"herofighter.com"` (Sequel Easter Egg):** Typing `H` -> `E` -> `R` -> `O` -> `F` -> `I` -> `G` -> `H` -> `T` -> `E` -> `R` -> `.` -> `C` -> `O` -> `M` advances tracker `DAT_00458578` and sets `DAT_00455470 = 'd'`. Marti Wong embedded this secret domain name in later versions of LF2 as a nod to his next major project, *Hero Fighter*! It enables the user to use function keys in the Stage mode of the game.
* **`"ABC"` (Internal Data Debugger):** In `FUN_0043e9a0`, pressing `A` -> `B` -> `C` sequentially sets `DAT_00450bec = 1`, unlocking mode switching via keys `'1'`, `'2'`, `'3'` to access the built-in frame/weapon inspector mode.

### 3. Window & Platform Identity Artifacts
* **Window Class Name:** The Win32 window class is registered as `"Marti"` at `0x00447634`.
* **Window Title:** Defined as `"Little Fighter 2"` at `0x00447620`.
* **Authentic Viewport Resolution:** Hardcoded in the `.data` segment at `DAT_0044d78c` (width = `794`) and `DAT_0044d790` (height = `550`).

### 4. Deterministic Multiplayer PRNG Table
* Standard C library `rand()` implementations vary across compiler runtimes, which would desynchronize peer-to-peer multiplayer.
* LF2 completely avoids `rand()` during gameplay: at `0x0044FF90` in `.data`, it embeds a static, precomputed 3,000-byte pseudo-random table.
* The PRNG routine (`0x00417170`) simply advances a circular index:
  $$\text{index} = (\text{index} + 1) \pmod{3000}$$
  guaranteeing 100% deterministic lockstep synchronization across network clients.

### 5. Fixed-Step 30 FPS Timing & Spiral-of-Death Protection (`0x0043cf40`)
* **Tick Step:** In battle (`DAT_0044d02c != 0`), the step is `33 ms` (`0x21`), yielding ~30.3 FPS. In menus, it steps at `3 ms`.
* **Spiral of Death Clamp:** If system lag causes the accumulator to fall behind by more than `100 ms`, the game drops excess accumulated time:
  $$\text{if } (\text{now} - \text{last\_time} > 100) \implies \text{last\_time} = \text{now} - 100$$
* **CPU Yielding:** To prevent 100% CPU core starvation, the timing loop yields via sleep in chunks of at most `5 ms`.
* **Key State Table:** A raw 256-byte static array at `0x00455378` is initialized to `'u'` (`0x75` = up) in `WinMain` and toggled to `'d'` (`0x64` = down) on `WM_KEYDOWN`.

---

## References & Acknowledgments

This source lift builds upon the foundation of knowledge created by decades of dedicated Little Fighter 2 community developers and reverse engineers:

- **Marti Wong & Starsky Wong:** The original creators of *Little Fighter 2* (1999–2002). Their iconic beat-'em-up engine, fluid sprite animations, and brilliant emergent combat design remain unmatched.
- **xsoameix ([`xsoameix/lf2`](https://github.com/xsoameix/lf2) and [`xsoameix/openlf2`](https://github.com/xsoameix/openlf2)):** The true pioneer of LF2 decompilation. Over twelve years ago, `xsoameix` took on the monumental task of manually disassembling `lf2.exe` function-by-function into Ruby, decoded complex compiler-optimized arithmetic (such as integer division via magic multiplication constants), and drafted the initial C struct layouts. This work serves as our indispensable "Rosetta Stone".
- **Mesujin ([`LF2-Enchanted-4th`](https://github.com/Mesujin/LF2-Enchanted-4th), [`LF2-Modified_DDraw`](https://github.com/Mesujin/LF2-Modified_DDraw)):** For pioneering research into DirectDraw hook wrappers and modernizing LF2 runtime scripting.
- **Ori Vered ([`Little-Fighter-2---Rebuild`](https://github.com/OriVered/Little-Fighter-2---Rebuild)):** For clean-room architectural analysis and modern OOP reconstruction of LF2 combat mechanics.
- **OpenLF2 Team ([`OpenLF2/OpenLF2`](https://github.com/OpenLF2/OpenLF2)):** For exploring cross-platform engine architecture and modern SDL integration.
- **LF2 Empire & The Modding Community:** For decades of comprehensive documentation regarding character `.dat` scripting, interaction tags (`itr`, `bdy`, `wpoint`), and sprite mechanics.
- **NSA Ghidra:** For providing modern, high-fidelity headless disassembly, decompilation, and reverse engineering instrumentation.

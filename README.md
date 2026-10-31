<div align="center">

<img src="assets/hero.png" alt="Little Fighter 2 Banner" width="600" />

# Little Fighter 2 | 1:1 C++ Source Lift

A true 1:1 C++20 source decompilation and modernization of the original *Little Fighter 2* (`lf2.exe`, version 1.9c / 2.0a, x86-32 MSVC++).

</div>

This project is a systems programming and binary reverse engineering exercise designed to extract, lift, and preserve the authentic game logic (state machines, frame-accurate timings, hitbox collision mathematics, and data-driven file loading) while shedding legacy DirectDraw 6 and Win32 dependencies in favor of a modern cross-platform architecture.

---

## Prior Art vs. This Project

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



### This Project

1. **Extracting, Not Guessing:** We do not invent custom OOP hierarchies, we do not guess class offsets, and we do not write high-level approximations. We decompile the compiled x86-32 MSVC++ machine code directly from the original executable and reconstruct the authentic logic in modern C++.
2. **Byte-Level Mathematical Fidelity:** Collision detection, axis-aligned bounding box projections, directional facing mirrors, velocity integrations, deterministic lookup tables, and frame state machines are mathematically identical to the original assembly.
3. **Liberation & Modernization:** We strip away deprecated Win32 message pumps and legacy DirectDraw 6 surface management, replacing them with a portable modern C++20 / SDL2 architecture that compiles and runs cleanly across modern 32-bit and 64-bit operating systems.

---

## Architecture & Project Layout

```text
LF2/
├── assets/                     # Media assets for this repo
├── decompiled/                 # Ground-truth raw C decompilations from Ghidra
│   ├── app/                    # WinMain, WindowProc, message pumping, cheat recognizers
│   ├── core/                   # Fixed PRNG circular table, fast abs, AABB primitives
│   ├── data/                   # Vigenère decryption, .dat loading/saving, struct ctors
│   ├── gameplay/               # Rudolf teleport, attack processing, collision detection, object ctor
│   ├── graphics/               # DirectDraw display init, blitting, 2D clipping, parallax math
│   └── README.md               # Memory address cross-reference & function index
├── src/                        # Lifted & modernized C++20 source code
│   ├── core/                   # Memory maps, game data structures & PRNG table
│   │   ├── constants.h         # File IDs, object types, states, weapon IDs
│   │   ├── types.h             # Portable native pointer definitions
│   │   ├── bdy.h               # Bounding box collision struct (0x28 / 40 bytes)
│   │   ├── itr.h               # Interaction hitbox struct (0x50 / 80 bytes)
│   │   ├── frame.h             # Frame state machine (0x178 / 376 bytes)
│   │   ├── file.h              # Character / weapon definition (0x25360 / 152,416 bytes)
│   │   ├── object.h            # World entity instance (0x370 / 880 bytes)
│   │   ├── global.h            # World manager state & method interfaces
│   │   ├── overlap.h           # 2D axis-aligned bounding box intersection math (0x4171C0)
│   │   ├── random_table.h      # 3,000-byte precomputed PRNG table extracted from .data
│   │   └── random.h / .cpp     # Deterministic PRNG implementation (0x417170)
│   ├── gameplay/               # Lifted gameplay logic routines
│   │   ├── teleport.cpp        # 1:1 Rudolf teleportation logic (0x403270)
│   │   ├── attack.cpp          # 1:1 Hitbox collision & attack queueing (0x417400)
│   │   └── entity.h / .cpp     # 1:1 Entity init (0x4061d0), 3D motion, gravity, wait counters
│   ├── data/                   # Resource loaders & crypto
│   │   ├── cipher.h / .cpp     # Authentic Vigenère .dat cipher & decryptor (0x4148a0)
│   │   ├── data_txt.h / .cpp   # Manifest parser for data/data.txt
│   │   └── dat_loader.h / .cpp # Full .dat script tokenizer and loader (0x40ef70)
│   ├── graphics/               # Visual rendering pipeline & camera
│   │   ├── background.h / .cpp # Multi-layer parallax background loader & geometry
│   │   └── renderer.h / .cpp   # Modern SDL2 renderer, texture cache, color keying, clipping
│   └── app/                    # Platform application & loop timing
│       ├── app.h / .cpp        # Modern SDL2 lifecycle, fixed 30 FPS pacing, input table
│       └── main.cpp            # Application entry point & headless test harness
├── tests/                      # Automated verification test suites
│   ├── verify_memory_maps.cpp  # Memory map & collision math verification suite
│   ├── test_data_loader.cpp    # Data-driven core & cipher verification suite
│   ├── test_graphics.cpp       # Graphics, sprite slicing & camera verification suite
│   └── test_entity_physics.cpp # Entity lifecycle, gravity, friction & frame animation suite
├── third_party/                # Self-contained vendor dependencies (SDL2 development kit)
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

## Building, Setup & Playing the Real Game

### 1. Prerequisites
- **Compiler:** Modern C++20 compiler (GCC 13+ / MSYS2 UCRT64 GCC 14.2+ / Clang 15+)
- **Build Tool:** GNU `make` or `mingw32-make`
- **SDL2:** The repository includes self-contained MinGW-w64 SDL2 development libraries in `third_party/SDL2/` and runtime `SDL2.dll` in root, enabling immediate compilation with zero external setup.

---

### 2. Acquiring and Setting Up Authentic Game Assets

Because *Little Fighter 2* artwork, sprite sheets, sound effects, and stage backgrounds are proprietary freeware created by Marti Wong and Starsky Wong, they are not distributed in this source code repository.

To experience the full game with authentic visuals and music:

1. Download the official game installer or archive from [lf2.net](https://lf2.net) or [LF-Empire](https://lf-empire.de) (LF2 v1.9c, v2.0, or v2.0a).
2. Copy the authentic game asset directories from your LF2 installation into the project root:
   ```text
   LF2/
   ├── data/           # Game manifest (data.txt) & encrypted character/weapon scripts (.dat)
   ├── sprite/         # Sprite sheets for all characters, projectiles, and weapons (.bmp)
   ├── bg/             # Multi-layer stage backgrounds & parallax layers (.dat, .bmp)
   ├── bgm/            # Background music tracks (.wma)
   └── sound/          # Audio effect samples (.wav)
   ```
   *(Alternatively, simply copy the compiled `lf2.exe` and `SDL2.dll` directly into your existing Little Fighter 2 game installation folder!)*

---

### 3. Compiling the Game

To build the static engine library (`liblf2.a`), the game executable (`lf2.exe`), and all test harnesses:

```bash
make
```

To clean intermediate build artifacts:
```bash
make clean
```

---

### 4. Running and Playing

```bash
# Launch in authentic 794x550 windowed mode
./lf2.exe

# Launch directly in fullscreen mode
./lf2.exe --fullscreen
```

* **Fullscreen Toggle:** Press `Alt + Enter` at any time during gameplay to seamlessly switch between windowed and fullscreen display.
* **Secret Character Unlock:** Type `lf2.net` on the main menu to unlock Julian, Firzen, LouisEX, and all other enemy characters.
* **Stage Function Keys:** Type `herofighter.com` to enable stage debug function keys.
* **Frame Inspector:** Type `ABC` to unlock the internal frame and hitbox inspector.

---

### 5. Automated Verification Test Suites

To verify memory offsets, mathematical collision fidelity, cipher decryption, sprite sheet slicing, and 30-frame simulation:

```bash
make test
```

### Expected Test Output
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

=== Little Fighter 2 Graphics, Sprite & Camera Pipeline Verification ===
[+] Testing Software 2D Clipping (0x0043ef70)...
    2D Software Clipping passed all edge cases.
[+] Testing Sprite Sheet Slicing with 1-Pixel Separator Gutter...
    Sprite Sheet Slicing verified with exact 1-pixel separator gutter.
[+] Testing Entity Centering & Screen Projection Math (0x00415d00)...
    Centering math correctly offsets both facing directions and ground elevation.
[+] Testing Authentic Parallax Formula on .legacy/bg/template/1/bg.dat...
    Parallax horizontal positioning exactly aligns layer edges with screen viewport.
[+] Testing Decryption of .legacy/bg/sys/hkc/bg.dat...
    HK_Coliseum stage loaded with 12 layers.
[+] Testing SDL2 Texture Loading & Black (0,0,0) Color Key...
    SDL2 Texture Loader and Color Keying executed without error.
[SUCCESS] All Graphics, Sprite Management & Camera Pipeline tests passed 100%!

=== Little Fighter 2 Entity Physics & State Machine Tests ===
[+] Testing object_init (0x004061d0 1:1 parity)...
    object_init passed: all offsets, vitals, and tables verified!
[+] Testing 3D motion integration and stage boundaries...
    3D motion and boundary clamping verified!
[+] Testing jump physics, gravitational acceleration, and landing...
    Jump arc completed in 20 ticks and landed cleanly at y = 0!
[+] Testing ground friction deceleration...
    Ground friction successfully halted sliding velocities!
[+] Testing frame advancement, wait counters, and history shifting...
    Frame state progression and particle expiration verified 100%!
[+] Testing player input state transitions (Walk, Jump, Attack, Defend)...
    Input state machine transitions verified 100%!
[SUCCESS] All Entity Physics & Lifecycle tests passed with 100% precision!

=== Little Fighter 2 Combat Engine & Action Dispatcher Tests ===
[+] Testing 1:1 combat damage calculation and flinch response (0x0042E100)...
    Damage (25 HP), front flinch frame 222, and vrest protection verified!
[+] Testing knockdown fall state and airborne arc (fall >= 60)...
    Knockdown fall state 80, falling frame 180, and trajectory verified!
[+] Testing projectile instantiation into world object table...
    Projectile spawned cleanly into slot 10 with correct velocity!
[SUCCESS] All Combat Engine & Action Dispatcher tests passed with 100% precision!

=== Little Fighter 2 Grapple, Throw & Weapon Mechanics Tests ===
[+] Testing Grapple Catch Initiation & Anchor Sync (0x004068B0)...
    Grapple initiation and anchor synchronization verified!
[+] Testing Grapple Throw Execution & Launch Arc...
    Throw launch velocities, knockdown (fall 80), and injury verified!
[+] Testing Weapon Pickup & wpoint Synchronization (0x00408CE0)...
    Weapon pickup and hand anchor synchronization verified!
[+] Testing Weapon Drop upon Damage & Weapon Throw...
    Weapon drop upon damage and throw impulse verified!
[SUCCESS] All Grapple, Throw & Weapon Mechanics tests passed with 100% precision!

=== Little Fighter 2 Artificial Intelligence Controller Tests ===
[+] Testing AI target selection & team filtering (0x00406BA0)...
    AI successfully targeted closest enemy (slot 3) ignoring teammates!
[+] Testing AI tracking & approach movement generation...
    AI correctly synthesized Right + Down approach vector!
[+] Testing AI melee range attack synthesis...
    AI successfully triggered melee attack and transitioned to punch frame 60!
[SUCCESS] All AI Controller tests passed with 100% precision!

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
  $$\text{plaintext}[i] = (\text{ciphertext}[i] - \text{key}[k] + 256) \pmod{256}$$
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
  $$\text{if } (t_{\text{now}} - t_{\text{last}} > 100\text{ ms}) \implies t_{\text{last}} = t_{\text{now}} - 100\text{ ms}$$
* **CPU Yielding:** To prevent 100% CPU core starvation, the timing loop yields via sleep in chunks of at most `5 ms`.
* **Key State Table:** A raw 256-byte static array at `0x00455378` is initialized to `'u'` (`0x75` = up) in `WinMain` and toggled to `'d'` (`0x64` = down) on `WM_KEYDOWN`.

---

## Engine Quirks, Desyncs & Known Binary Bugs

Through Ghidra decompilation and binary disassembly of `lf2.exe`, we reverse-engineered the exact root causes of legendary Little Fighter 2 engine quirks, multiplayer desync crashes, and long-standing community mysteries:

### 1. The Anatomy of the Infamous "Synchronisation Error!" (`0x0041CAD9` / `0x0041CCB5`)
For over two decades, Little Fighter 2 players experienced sudden match freezes with a `"Synchronisation Error!"` modal dialog. Disassembly of the lockstep network routine in `0x0041C5F0` revealed the exact mechanism:
* **The 22-Byte Lockstep Packet:** At `0x0041CB80`, every frame exchange transmits a compact 22-byte packet (`net_packet_t`) containing 8 packed player controller states (Up `0x02`, Right `0x04`, Attack `0x08`, Jump `0x10`, Defend `0x20`, Down `0x40`, Left `0x80`), the circular PRNG table index, and a cumulative 16-bit HP checksum.
* **The Cumulative HP Checksum:** At `0x0041CAD9`, the host iterates through all active character slots and accumulates their current health points (`object_t` offset `0x2FC`):
  $$\text{checksum} = \sum_{i=0}^{\text{active}-1} \text{HP}_i$$
* **Instant Desync Trigger:** If remote and local HP checksums differ by even 1 HP (due to a dropped frame, projectile spawn timing jitter, or floating-point rounding deviation), `0x0041CCB5` immediately halts execution with `"Synchronisation Error!"` (`0x00449384`). Frame sequence counter deviations trigger `"Connection Lost!"` (`0x004493B4`), while packet header protocol mismatches report `"Version not matched!"` (`0x0044939C`).

### 2. The 100-Slot World Object Array & Screen Overflow Crash (`0x0042E100` / `0x004061D0`)
* **Static Allocation Ceiling:** Little Fighter 2 manages all entities on screen through a fixed static global array capped at exactly **100 object slots** (`object_t* g_objects[100]` at `0x00450BE0`).
* **Shared Pool Competition:** Characters, enemy minions, dropped weapons (knives, baseball bats, rocks), projectiles (energy balls, ice swords), and transient particle effects (blood splatters, smoke puffs) all compete for these same 100 slots.
* **The Crash Mechanism:** In heavy Stage Mode battles (e.g. Stage 5 with dozens of bandits or Firzen/LouisEX casting large multi-part special moves), the object spawner at `0x0042E100` scans the 100 slots looking for a free slot (`slot->type == TYPE_NULL`). If all 100 slots are exhausted, newly spawned projectiles or weapon drops fail silently or return a null pointer that subsequent rendering and physics passes attempt to dereference, triggering an instant Crash-to-Desktop (CTD).

### 3. The Rudolf Stage Boundary Teleportation Glitch (`0x00403270`)
* In `func_00403270`, Rudolf’s catch-and-teleport move calculates destination coordinates behind the victim:
  $$x_{\text{dest}} = x_{\text{victim}} + (\text{facing} == 0 \ ? \ -40 : +40)$$
* **Missing Boundary Clamp:** The original assembly directly commits `x_position = x_dest` without clamping against camera boundaries or the stage limits (`z_min = 0, z_max = 400`, `x_min = 0, x_max = stage_width`). If an opponent is grabbed near the far-left or far-right edge of the stage, Rudolf teleports into negative space outside the playable world, causing the character to enter an infinite falling trajectory or become permanently unplayable.

### 4. Player Name Grave Accent Substitution in `control.txt` (`0x004233E0` / `0x0042353A`)
* **The Parser Whitespace Dilemma:** In `data/control.txt`, player profiles, 11 keyboard mapping scan codes per player, and custom player names are serialized via standard C runtime `fscanf` / `fprintf`. Because `fscanf("%s")` delimits tokens on whitespace, any player name containing spaces (e.g. `"Little Bear"`) would corrupt line parsing.
* **The Clever Workaround:** At `0x004233E0`, Marti Wong implemented a character substitution loop that replaces every space (`' '`, ASCII `0x20`) with a grave accent character (`` '`' ``, ASCII `0x60`) before writing to disk:
  ```text
  Little`Bear Starsky`Wong Davis`Master Freeze`Knight
  ```
* At `0x0042353A`, during game boot, the parser reads the string and converts every `` '`' `` back to a space (`' '`). Players who opened `control.txt` in Notepad over the years often wondered why mysterious backticks appeared in their usernames!

### 5. Deterministic Battle Replay Recording (`.lfr` at `0x0042D080` / `0x00402980`)
* **100% Deterministic Playback:** Rather than saving full video or large coordinate streams, LF2 replays (`.lfr` files) record only the initial 3,000-byte circular PRNG table seed (`0x0044D024`), character choices, and 8 bytes of packed controller input states per frame.
* **On-Screen HUD Indicators:** At `0x00402980`, the engine uses DirectDraw to render color-coded notification banners at the bottom of the viewport ($y = 531$ / `0x213`):
  * **Orange (`0x00FF7800`):** `"Start recording '%s'..."` upon match commencement.
  * **Green (`0x0000FF00`):** `"Recording file '%s' saved!"` upon successful match conclusion.
  * **Red (`0x000000FF`):** `"Recording canceled!"` if the match is aborted prematurely.

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

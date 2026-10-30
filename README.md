# Little Fighter 2 — 1:1 C++ Source Lift

A true 1:1 decompiled C++20 source port and modernization of the original *Little Fighter 2* (`lf2.exe`, version 1.9c / 2.0a, x86-32 MSVC++).

This project is a systems programming and binary reverse engineering exercise designed to extract, lift, and preserve the authentic game logic (state machines, frame-accurate timings, hitbox collision mathematics, and data-driven file loading) while shedding legacy DirectDraw 6 and Win32 dependencies in favor of a modern cross-platform architecture.

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
│   ├── func_00417170_random.c
│   ├── func_004171c0_overlap.c
│   ├── func_00417400_does_attack_success.c
│   ├── func_0042e100_attack_process.c
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
├── verify_memory_maps.cpp      # Comprehensive memory map & gameplay test suite
├── REFERENCE_ERRORS.md         # Documented inaccuracies in prior decompilation attempts
├── Makefile                    # Automated build script (MSYS2 UCRT64 GCC)
└── PLAN.md                     # Technical roadmap across phases 1–6
```

---

## Core Directives & Verification

The operational directives followed:

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
```

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

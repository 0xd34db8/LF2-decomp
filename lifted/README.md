# Modern C++ Source Lift

This directory contains the modernized **C++20 / SDL2 Source Lift** of *Little Fighter 2* (`lf2.exe`), porting the verified game state machines, deterministic battle frame loop, spatial stereo audio, 10-byte `.lfr` replays, and lockstep networking off Win32 and DirectDraw 6.

See the [root repository documentation](../README.md) and the [decompiled binary archive](../decompiled/README.md) for reverse-engineering references and memory address mappings.

---

## Directory Structure

```text
lifted/
├── src/                # Modern C++20 game engine source
│   ├── app/            # SDL2 window/input, scenes, battle loop, stage/survival/tournament modes
│   ├── audio/          # DirectSound & DirectShow to SDL2 audio mixer, stereo pan & BGM streamer
│   ├── core/           # Memory layouts (object_t/global_t/frame_t), PRNG tables, constants, replay
│   ├── data/           # .dat lexer, Vigenère cipher decrypter & control.txt parser
│   ├── gameplay/       # Combat dispatcher, hitbox intersection, entity physics, AI & weapons
│   ├── graphics/       # Software renderer, parallax background & embedded UI bitmaps
│   └── net/            # Lockstep network synchronization & 22-byte packets
├── tests/              # 16 unit test suites (+ 30-frame engine verification)
├── tools/              # Embedded UI asset generation pipeline
├── third_party/        # Self-contained MinGW-w64 SDL2 development headers & libraries
├── Makefile            # Independent build system for the lifted engine
└── README.md           # Documentation for the modern source lift
```

---

## Building and Running

From the repository root (or inside `lifted/`):

```bash
# Build the modern game executable (lifted/build/lf2.exe)
mingw32-make -C lifted

# Run all 16 unit test suites and the 30-frame verification test (17 tests total)
mingw32-make -C lifted test

# Launch windowed, fullscreen, or run automated 30-frame verification
cd lifted && ./build/lf2.exe
cd lifted && ./build/lf2.exe --fullscreen
cd lifted && ./build/lf2.exe --test --frames 30

# Clean all build artifacts
mingw32-make -C lifted clean
```

### Game Asset Placement

Authentic game data folders (`data/`, `bg/`, `sprite/`, `sound/`, `bgm/`) should be placed in `lifted/build/` (or run inside an existing authentic LF2 game directory) to enable full asset and character loading during gameplay.
All frontend UI bitmaps are pre-baked directly into the binary (`src/graphics/embedded_ui.cpp`) mirroring the authentic Win32 PE `.rsrc` resource architecture.

# Modern C++ Source Lift

This directory contains an attempt at a modernized C++20 / SDL2 source lift of Little Fighter 2.

---

## Directory Structure

```text
lifted/
├── src/                # Modern C++20 game engine source
│   ├── app/            # Application lifecycle, SDL2 window/input, scenes, game loop
│   ├── audio/          # DirectSound to SDL2 audio pipeline & mixer
│   ├── core/           # Memory layouts, PRNG tables, constants, replay
│   ├── data/           # Dat lexer, Vigenère decrypter, control.txt parser
│   ├── gameplay/       # Combat dispatcher, hitbox intersection, AI, weapons
│   ├── graphics/       # Software renderer, parallax background, embedded UI
│   └── net/            # Lockstep network synchronization & packets
├── tests/              # 14 comprehensive unit test suites
├── tools/              # Embedded UI asset generation pipeline
├── third_party/        # Self-contained MinGW-w64 SDL2 development headers & libraries
├── data/               # UI source assets and control configuration
└── Makefile            # Independent build system for the lifted engine
```

---

## Building and Running

From within the `lifted/` directory (or from the repository root via `-C lifted`):

```bash
# Build the modern game executable (build/lf2.exe)
mingw32-make -C lifted

# Run all 14 unit test suites and the 30-frame verification test (15 tests total)
mingw32-make -C lifted test

# Clean all build artifacts
mingw32-make -C lifted clean
```

### Game Asset Placement

Authentic game data folders (`data/`, `bg/`, `sprite/`) should be placed in `lifted/build/` (or inside an existing authentic LF2 game directory) to enable full asset and character loading during gameplay.
All frontend UI bitmaps are pre-baked directly into the binary (`src/graphics/embedded_ui.cpp`) mirroring authentic Win32 PE `.rsrc` resource architecture.

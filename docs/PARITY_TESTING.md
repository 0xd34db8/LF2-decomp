# Parity & Headless Verification Architecture

`LF2-decomp` verifies mathematical and state-machine parity with `lf2.exe` without distributing proprietary freeware game assets (`data/`, `sprite/`, `bg/`, `sound/`, `bgm/`) in the repository or requiring an interactive desktop session in CI.

---

## 1. Current Verification Layers

### Compilable Legacy Archive (`decompiled/Compilable/test_legacy.c`)
- Exercises decompiled C routines directly against verified struct layouts (`sizeof` and `offsetof` assertions for `bdy_t`, `itr_t`, `opoint_t`, `bpoint_t`, `cpoint_t`, `wpoint_t`, `frame_t`, `file_t`, `object_t`, and `global_t`), circular PRNG (`0x00417170`), `zlib` + secondary replay cipher (`0x0043dd60` / `0x0043e620`), Rudolf teleport (`0x00403270`), AI decisions, combo recognizers, and the `0x0041bc90` battle frame tick.
- Executed via `mingw32-make -C decompiled/Compilable test`.

### Modernized Source Lift (`lifted/tests/` + 30-Frame Smoke Test)
- **16 standalone C++20 unit test binaries** (`verify_memory_maps`, `test_data_loader`, `test_graphics`, `test_entity_physics`, `test_combat_system`, `test_grapple_weapon`, `test_ai_controller`, `test_audio_system`, `test_bgm_system`, `test_stage_menu`, `test_network_sync`, `test_replay_system`, `test_tournament`, `test_battle_mode`, `test_survival_mode`, `test_options_control`) construct synthetic in-memory `file_t`, `frame_t`, `object_t`, and `global_t` fixtures to test deterministic behavior without proprietary `.dat` files on disk.
- **Headless 30-frame engine smoke test:** `lf2.exe --test --frames 30` initializes the SDL2 `app_t` core, validates cheat-code state machines (`lf2.net`, `herofighter.com`, `ABC`), and steps 30 frames cleanly under `SDL_VIDEODRIVER=dummy` and `SDL_AUDIODRIVER=dummy`.

---

## 2. Deterministic `.lfr` Replay Parity Roadmap

Little Fighter 2's replay format (`.lfr`, `0x0043dd60` / `0x0043e620`) is naturally suited for headless differential parity testing modeled on deterministic replay harnesses such as OpenRCT2's `ReplayTests`:

1. **Self-Contained Replay State:**
   - Every `.lfr` stream encodes the initial 3,000-byte circular PRNG table (`0x0044ff90`), slot/character configuration, **10-byte per-frame input records** (`+0x2B38 + frame * 10`), and periodic **150-frame cumulative active-HP checksums** (`+0x14B8 + (frame / 150) * 4`).
2. **Synthetic Headless Replay Runner:**
   - Construct minimal synthetic `file_t` character definitions in memory (no proprietary sprites required), record or load a deterministic `.lfr` fixture in `lifted/tests/`, step `step_battle_frame()` in headless mode without rendering, and assert frame-by-frame equivalence against the `decompiled/Compilable/` C reference implementation (`lf2_battle_frame_tick`).
3. **Mismatch Detection:**
   - Any divergence in HP checksums, object coordinates `(x, y, z)`, velocities, or `frame_id1` immediately surfaces the exact frame index and entity slot where lifted C++ behavior diverges from the decompiled x86 reference.

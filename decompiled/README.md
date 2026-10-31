# Decompiled Forensic Archive (Ghidra & x86 Disassembly)

This directory houses raw, ground-truth pseudocode and disassembly extracted from `lf2.exe` (v1.9c / v2.0a, x86-32 MSVC++). These files are strictly observational references used to guide the 1:1 C++ source lift in `src/`.

The files are organized to mirror the modern engine architecture and original class boundaries:

```
decompiled/
├── app/          # WinMain, WindowProc, message pumping, cheat state machines
├── audio/        # DirectSound init, secondary buffer allocation, sound effect playback
├── core/         # Fixed-table PRNG, abs, 1D/3D AABB overlap primitives
├── data/         # Vigenère decryption, .dat loading/saving, file_t & frame_t ctors
├── gameplay/     # Rudolf teleportation, collision check, attack dispatcher
├── graphics/     # DirectDraw init, blitting, 2D clipping, parallax math, object projection
└── net/          # WinSock init, non-blocking lockstep packet loop, desync validation
```

### Memory Address & Function Index

| Virtual Address | File Path | Class / Domain | Description |
| :--- | :--- | :--- | :--- |
| `0x004014e0` | `audio/func_004014e0_sound_load_wav.c` | DirectSound | RIFF WAVE parser & secondary buffer allocation |
| `0x00401970` | `audio/func_00401970_sound_init.c` | DirectSound | DirectSound subsystem initialization |
| `0x00401a30` | `audio/func_00401a30_sound_play.c` | DirectSound | Sound buffer playback cursor reset & play |
| `0x00402b80` | `net/func_00402b80_net_init.c` | WinSock | WinSock init, gethostname, socket & WSAAsyncSelect |
| `0x00403270` | `gameplay/func_00403270_teleport.c` | `object_t` / Rudolf | Team teleportation coordinate resolution |
| `0x004034e0` | `core/func_004034e0_abs.c` | Math | Fast absolute value computation |
| `0x004061d0` | `gameplay/func_004061d0_object_init.c` | `object_t` | Entity constructor & state initialization |
| `0x004068b0` | `gameplay/func_004068b0_grapple_sync.c`| `object_t` / Grapple | Caught target position anchor & throw release |
| `0x00406ba0` | `gameplay/func_00406ba0_ai_process.c` | `object_t` / AI | AI combat evaluation & virtual key input synthesis |
| `0x00408ce0` | `gameplay/func_00408ce0_weapon_sync.c` | `object_t` / Weapon | Weapon hand anchor sync, drop & throw physics |
| `0x0040bbf0` | `data/func_0040bbf0_frame_ctor.c` | `frame_t` | Frame data structure initialization |
| `0x0040be70` | `data/func_0040be70_calc_frame_coords.c` | `frame_t` | Sprite sheet UV coordinate calculation |
| `0x0040d0a0` | `data/func_0040d0a0_save_dat.c` | `file_t` | Character `.dat` serializer |
| `0x0040ef70` | `data/func_0040ef70_load_dat.c` | `file_t` | Full `.dat` lexer/tokenizer |
| `0x004143d0` | `data/func_004143d0_file_ctor.c` | `file_t` | Master file structure initialization |
| `0x004148a0` | `data/func_004148a0_decrypt_dat.c` | Cipher | 123-byte header skip + Vigenère decryption |
| `0x00415d00` | `graphics/func_00415d00_draw_object.c` | Renderer | Entity screen projection & mirror blit |
| `0x00417170` | `core/func_00417170_random.c` | Determinism | 3,000-byte precomputed circular PRNG lookup |
| `0x004171c0` | `core/func_004171c0_overlap.c` | Physics | 1D interval overlap test |
| `0x00417400` | `gameplay/func_00417400_does_attack_success.c`| Combat | 3D AABB hitbox collision check |
| `0x0041a2dd` | `graphics/func_0041a2dd_parallax_calc.c`| Background | Layer offset & wrapping calculation |
| `0x0041c5f0` | `net/func_0041c5f0_net_lockstep.c` | Lockstep Net | 22-byte lockstep packet send/recv, non-blocking ioctlsocket & desync checks |
| `0x0042e100` | `gameplay/func_0042e100_attack_process.c`| Combat | Full attack damage & effect dispatcher |
| `0x00436900` | `app/func_00436900_battle_setup.c` | App / Battle | Player/CPU entity spawn initialization & battle setup |
| `0x0043b3d0` | `app/func_0043b3d0_wndproc.c` | App | Win32 WindowProc & cheat code recognizers |
| `0x0043bdd0` | `app/func_0043bdd0_create_window.c`| App | Win32 `CreateWindowEx` setup |
| `0x0043bec0` | `graphics/func_0043bec0_init_display.c` | Renderer | DirectDraw 6 display mode initialization |
| `0x0043cf40` | `app/func_0043cf40_winmain.c` | App | WinMain entry point & 30 FPS timing loop |
| `0x0043e9a0` | `app/func_0043e9a0_game_mode_mgr.c` | App | Developer cheat & game mode manager |
| `0x0043ef70` | `graphics/func_0043ef70_clip_rect.c` | Renderer | 2D software clipping against viewport |
| `0x0043f010` | `graphics/func_0043f010_surface_blit.c` | Renderer | DirectDraw surface blit wrapper |

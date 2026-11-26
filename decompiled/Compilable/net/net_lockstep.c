#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <winsock.h>
#endif

/*
 * Virtual Addresses:
 *   0x00416C70: FUN_00416c70 (Secret lf2.net character unlock toggle + replay flag)
 *   0x00416CA0: FUN_00416ca0 (Secret herofighter.com F-key unlock toggle + replay flag)
 *   0x00416CD0: FUN_00416cd0 (F4 match exit / recording cancel / replay end)
 *   0x00416DD0: FUN_00416dd0 (F1 pause toggle)
 *   0x00416DF0: FUN_00416df0 (F2 single-frame step)
 *   0x00416E10: FUN_00416e10 (F3 lock function keys)
 *   0x00416E30: FUN_00416e30 (F5 simulation speed toggle)
 *   0x00416E60: FUN_00416e60 (F6 unlimited MP toggle)
 *   0x00416EB0: FUN_00416eb0 (F7 HP/MP full recovery)
 *   0x00416F10: FUN_00416f10 (F8 sky weapon drop trigger)
 *   0x00416F60: FUN_00416f60 (F9 destroy items / kill non-criminal stage enemies)
 *   0x0041BC90: FUN_0041bc90 / lf2_battle_frame_tick (Master battle frame loop + lockstep)
 *   0x0041C5F0: func_0041c5f0_net_lockstep (22-byte packet lockstep block)
 */

#define PACKET_SIZE 22 /* 0x16 */

#pragma pack(push, 1)
typedef struct {
    unsigned char player_inputs[8]; /* +0..+7: Packed player 0..7 inputs */
    unsigned char control_flags;    /* +8: Base 0x01 */
    unsigned char seq_counter;      /* +9: Modulo 50 sequence counter ("Connection Lost!") */
    unsigned char func_keys_1;      /* +10: F1/F2/F4/F5/F6/F7/F9 bits */
    unsigned char version_tag;      /* +11: Version tag ("Version not matched!") */
    unsigned char func_keys_2;      /* +12: F3/F8/unlock bits */
    unsigned char hp_checksum;      /* +13: (hp_sum % 100) + 1 ("Synchronisation Error!") */
    unsigned char data_crc_lo;      /* +14: Low byte of DAT_0044f620 */
    unsigned char data_crc_hi;      /* +15: Arithmetic-shifted high byte of DAT_0044f620 */
    unsigned char payload[6];       /* +16..+21: {1, 1, 1, 1, 0, 0} */
} lf2_net_packet_t;
#pragma pack(pop)

SOCKET g_connected_socket = INVALID_SOCKET;
lf2_net_packet_t g_outgoing_packet = {0}; /* 0x0044D040 */
lf2_net_packet_t g_incoming_packet = {0}; /* 0x0044F198 */
unsigned int g_current_frame = 0;

/* 0x00416C70: Toggle unlocked characters (lf2.net) & set replay record byte 9 |= 0x01 */
// FUNCTION: LF2 0x00416c70
void FUN_00416c70(uint8_t *param_1)
{
    if (param_1) {
        param_1[9] |= 1u;
    }
    DAT_00458428 = 1 - DAT_00458428;
    FUN_00401a30();
}

/* 0x00416CA0: Toggle unlocked stage F-keys (herofighter.com) & set replay record byte 9 |= 0x02 */
// FUNCTION: LF2 0x00416ca0
void FUN_00416ca0(uint8_t *param_1)
{
    if (param_1) {
        param_1[9] |= 2u;
    }
    DAT_0045842c = 1 - DAT_0045842c;
    FUN_00401a30();
}

/* 0x00416CD0: F4 exit match, cancel replay recording, or restore config after replay */
// FUNCTION: LF2 0x00416cd0
void FUN_00416cd0(int *param_1, int *param_2)
{
    if (!param_1 || !param_2) return;
    if (*param_1 == 0) {
        DAT_00450bfc = 0;
        DAT_0044fb60 = 0;
        DAT_0044fcb0 = 0;
        DAT_00450c2c = 0;
        DAT_0044d02c = 1;
        if (*param_2 != 5 && DAT_00450be4 != 0 && DAT_00450b80 != 0) {
            DAT_00450b80 = 0;
            if (DAT_00450bdc < 0x65) {
                DAT_00450b70 = 3;
                DAT_00450b6c = 0;
            }
        }
        if (DAT_00450b88 != 0) {
            *param_2 = 6;
            if (DAT_004588ac != 0 && DAT_00450b88 != 0) {
                FUN_0043df00();
                const uint8_t *rep = (const uint8_t *)(uintptr_t)DAT_004588ac;
                DAT_00458428 = *(const int32_t *)(rep + 0x630bb8);
                DAT_0045842c = *(const int32_t *)(rep + 0x630bbc);
            }
            DAT_00450b88 = 0;
            DAT_00450b84 = 0;
            *param_1 = 10;
            DAT_00450bdc = 0;
            return;
        }
        if (*param_2 != 2 && *param_2 != 3) {
            DAT_00450bdc = 0x15e;
            return;
        }
        DAT_00450bdc = 0;
        *param_1 = 10;
        DAT_00457580 = 0;
    }
}

/* 0x00416DD0: F1 pause toggle */
// FUNCTION: LF2 0x00416dd0
void FUN_00416dd0(int *param_1)
{
    if (param_1 && *param_1 == 0) {
        DAT_0044fb60 = 1 - DAT_00450bfc;
        DAT_0044fcb0 = DAT_0044fb60;
    }
}

/* 0x00416DF0: F2 single-frame step while paused */
// FUNCTION: LF2 0x00416df0
void FUN_00416df0(int *param_1)
{
    if (param_1 && *param_1 == 0) {
        DAT_0044fcb0 = 1;
        DAT_0044fb60 = 0;
    }
}

/* 0x00416E10: F3 lock function keys */
// FUNCTION: LF2 0x00416e10
void FUN_00416e10(uint8_t *param_1, int *param_2)
{
    if (param_2 && *param_2 == 0) {
        if (param_1) {
            param_1[8] |= 4u;
        }
        DAT_00450c28 = 2;
    }
}

/* 0x00416E30: F5 toggle normal/fast speed */
// FUNCTION: LF2 0x00416e30
void FUN_00416e30(undefined4 param_1, int *param_2)
{
    (void)param_1;
    if (param_2 && *param_2 == 0) {
        DAT_0044d02c = 1 - DAT_0044d02c;
        DAT_004553ec = 0x75;
    }
}

/* 0x00416E60: F6 unlimited MP toggle */
// FUNCTION: LF2 0x00416e60
void FUN_00416e60(uint8_t *param_1, int *param_2, int *param_3)
{
    if (!param_2 || !param_3) return;
    if (DAT_00450c28 < 2 && (*param_3 == 0 || DAT_0045842c == 1) && *param_2 == 0) {
        if (param_1) {
            param_1[8] |= 0x10u;
        }
        DAT_0044d034 = 1 - DAT_0044d034;
        DAT_00450c18 = DAT_00450c18 + 1;
        DAT_00450c28 = 1;
    }
}

/* 0x00416EB0: F7 recover full HP & MP */
// FUNCTION: LF2 0x00416eb0
void FUN_00416eb0(uint8_t *param_1, int *param_2, int *param_3)
{
    if (!param_2 || !param_3) return;
    if (DAT_00450c28 < 2 && (*param_3 == 0 || DAT_0045842c == 1) && *param_2 == 0) {
        if (param_1) {
            param_1[8] |= 0x20u;
        }
        if (DAT_00450bdc == 0) {
            DAT_00450bc0 = 1 - DAT_00450bc0;
            DAT_00450c1c = DAT_00450c1c + 1;
            DAT_00450c28 = 1;
        }
    }
}

/* 0x00416F10: F8 drop weapons from sky */
// FUNCTION: LF2 0x00416f10
void FUN_00416f10(uint8_t *param_1, int *param_2, int *param_3)
{
    if (!param_2 || !param_3) return;
    if (DAT_00450c28 < 2 && (*param_3 == 0 || DAT_0045842c == 1) && *param_2 == 0) {
        if (param_1) {
            param_1[8] |= 0x40u;
        }
        if (DAT_00450bdc == 0) {
            DAT_00450c20 = DAT_00450c20 + 1;
            DAT_00450bb8 = 1;
            DAT_00450c28 = 1;
        }
    }
}

/* 0x00416F60: F9 destroy all items / stage enemies */
// FUNCTION: LF2 0x00416f60
void FUN_00416f60(uint8_t *param_1, int *param_2, int *param_3)
{
    if (!param_2 || !param_3) return;
    if (DAT_00450c28 < 2 && (*param_3 == 0 || DAT_0045842c == 1) && *param_2 == 0) {
        if (param_1) {
            param_1[8] |= 0x80u;
        }
        if (DAT_00450bdc == 0) {
            DAT_00450c24 = DAT_00450c24 + 1;
            DAT_00450bb8 = 2;
            DAT_00450c28 = 1;
        }
    }
}

/* Helper: lookup loaded file_t by ID inside global->files[0..MAX_FILES-1] */
static file_t *find_loaded_file_by_id(const global_t *global, uint32_t file_id)
{
    if (!global) return NULL;
    for (int i = 0; i < MAX_FILES; ++i) {
        if (global->files[i] != NULL && global->files[i]->id == file_id) {
            return global->files[i];
        }
    }
    return NULL;
}

/* Helper: allocate free slot in [50..399] */
static int find_free_dynamic_slot(const global_t *global)
{
    if (!global) return -1;
    for (int i = 50; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0 && global->objects[i] != NULL) {
            return i;
        }
    }
    return -1;
}

/* Helper: clear symmetric 0x50-slot vrest against newly spawned dynamic slot */
static void clear_vrest_for_slot(global_t *global, int new_slot)
{
    for (int s = 0; s < 400; ++s) {
        if (global->is_object_exists[s] != 0 && global->objects[s] != NULL) {
            global->objects[s]->vrest_of_objects[new_slot] = 0;
        }
    }
}

/* Helper: compute 20-slot active character HP sum for network & replay checksums */
static int compute_slot20_hp_sum(const global_t *global)
{
    int hp_sum = 0;
    if (!global) return 0;
    for (int i = 0; i < 20; ++i) {
        if (global->is_object_exists[i] == 1 && global->objects[i] != NULL) {
            hp_sum += global->objects[i]->hp;
        }
    }
    return hp_sum;
}

/* Shared 22-byte lockstep exchange & verification (0x0041C5F0 - 0x0041CCD0) */
static int run_lockstep_exchange(global_t *global, int use_global_buffers)
{
    u_long non_blocking = 0;
    int bytes_received = 0;
    uint8_t *out_bytes = use_global_buffers ? DAT_0044d040 : (uint8_t *)&g_outgoing_packet;
    uint8_t *in_bytes = use_global_buffers ? DAT_0044f198 : (uint8_t *)&g_incoming_packet;
    SOCKET sock = (g_connected_socket != INVALID_SOCKET)
        ? g_connected_socket
        : (SOCKET)DAT_0044f46c;

    if (sock != INVALID_SOCKET) {
        ioctlsocket(sock, FIONBIO, &non_blocking);
    }

    int hp_sum = compute_slot20_hp_sum(global);
    DAT_00450bf4 = hp_sum - (hp_sum / 100) * 100 + 1;
    DAT_00450bf0 = (DAT_00450bf0 + 1) % 50;

    out_bytes[9]  = (uint8_t)DAT_00450bf0;
    out_bytes[11] = (uint8_t)DAT_0044d03c;
    out_bytes[13] = (uint8_t)DAT_00450bf4;
    out_bytes[14] = (uint8_t)(DAT_0044f620 & 0xFF);
    out_bytes[15] = (uint8_t)((DAT_0044f620 + ((DAT_0044f620 < 0) ? 0xFF : 0)) >> 8);

    if (sock != INVALID_SOCKET) {
        if (DAT_0044f1af == 2) {
            /* Client: recv first, then send */
            bytes_received = recv(sock, (char *)in_bytes, PACKET_SIZE, 0);
            while (bytes_received > 0 && bytes_received < PACKET_SIZE) {
                int more = recv(sock, (char *)(in_bytes + bytes_received),
                                PACKET_SIZE - bytes_received, 0);
                if (more <= 0) break;
                bytes_received += more;
            }
            send(sock, (const char *)out_bytes, PACKET_SIZE, 0);
        } else {
            /* Host: send first, then recv */
            send(sock, (const char *)out_bytes, PACKET_SIZE, 0);
            bytes_received = recv(sock, (char *)in_bytes, PACKET_SIZE, 0);
            while (bytes_received > 0 && bytes_received < PACKET_SIZE) {
                int more = recv(sock, (char *)(in_bytes + bytes_received),
                                PACKET_SIZE - bytes_received, 0);
                if (more <= 0) break;
                bytes_received += more;
            }
        }
    }

    if ((int)(signed char)in_bytes[9] != DAT_00450bf0) {
        MessageBoxA((HWND)0, "Connection Lost!", "Error", 0);
        return -1;
    }
    if ((int)(signed char)in_bytes[11] != DAT_0044d03c) {
        const char *ver_msg = (DAT_0044f1af == 2) ? "Version not matched!" : "Version not matched! ";
        MessageBoxA((HWND)0, ver_msg, "Error", 0);
        return -2;
    }
    if ((int)(signed char)in_bytes[13] != DAT_00450bf4) {
        MessageBoxA((HWND)0, "Synchronisation Error!", "Error", 0);
        return -3;
    }
    if ((signed char)in_bytes[14] != (signed char)out_bytes[14] ||
        (signed char)in_bytes[15] != (signed char)out_bytes[15]) {
        MessageBoxA((HWND)0, "Data Error! You and your opponent have different set of data files.", "Error", 0);
        return -4;
    }

    return 0;
}

// COMPAT: LF2 0x0041c5f0
int func_0041c5f0_net_lockstep(void)
{
    return run_lockstep_exchange((global_t *)in_ECX, 0);
}

/*
 * Virtual Address: 0x0041BC90
 * Function: lf2_battle_frame_tick
 * Master 1:1 battle loop orchestrating input phase, pause/F-keys, lockstep,
 * replay record/playback, round-end counter, control/physics ticks, combat,
 * transforms, regeneration, opoint spawner, weapon break shards, team orders,
 * ice/fire FX, and end-of-frame spatialized sound dispatch.
 */
// FUNCTION: LF2 0x0041bc90
int lf2_battle_frame_tick(global_t *global, int *game_mode)
{
    if (!global || !game_mode) {
        return func_0041c5f0_net_lockstep();
    }

    void *prev_ecx = in_ECX;
    in_ECX = global;

    /* 1. Two-frame input phase alternation (0 <-> 1) & pause latch */
    DAT_00450b90 = (DAT_00450b90 + 1) & 1;
    if (DAT_00450b90 == 0) {
        DAT_00450bfc = DAT_0044fb60;
        DAT_0044fb60 = DAT_0044fcb0;
    }
    int paused = (DAT_00450bfc == 1) ? 1 : 0;

    /* 2. Replay viewer HUD toggle (F6) and manual camera pan (Left/Right/Down) */
    if (DAT_00450b84 != 0) {
        if (DAT_004553ed == 'd') {
            DAT_0044d030 = 1 - DAT_0044d030;
            DAT_004553ed = 'u';
        }
        if (DAT_00455378[0x25] == 'd' || DAT_00455378[0x27] == 'd') {
            if (DAT_00450b74 == 0) {
                DAT_00450b7c = DAT_00450bc4;
                DAT_00450b74 = 1;
                DAT_00450b78 = DAT_00450bc8;
            }
            if (DAT_00455378[0x25] == 'd') DAT_00450b78 -= 5;
            if (DAT_00455378[0x27] == 'd') DAT_00450b78 += 5;
        }
        if (DAT_00455378[0x28] == 'd') {
            DAT_00450b74 = 0;
            DAT_00450b78 = 0;
        } else if (DAT_00450b74 != 0) {
            DAT_00450b7c += DAT_00450b78;
            DAT_00450b78 = (DAT_00450b78 * 6) / 7;
        } else {
            DAT_00450b78 = 0;
        }
    }

    uint8_t local_rec[10];
    uint8_t playback_rec[10];
    memset(local_rec, 0, sizeof(local_rec));
    memset(playback_rec, 0, sizeof(playback_rec));

    if (DAT_00450b84 != 0 && paused == 0 && DAT_00450b90 == 0) {
        FUN_0043dc50(playback_rec);
    }

    /* Reset outgoing 22-byte lockstep packet defaults (0x01010101) */
    memset(DAT_0044d040, 0x01, 20);
    DAT_0044d040[20] = 0;
    DAT_0044d040[21] = 0;

    if (paused == 0) {
        FUN_00419a60(DAT_00450b90, *game_mode, local_rec);
    }

    /* 3. Phase-0 F-keys, secret unlocks & network lockstep */
    if (DAT_00450b90 == 0) {
        if (DAT_0044f1af == 0) {
            if (DAT_00450b88 != 0) {
                /* Replay playback F-keys come from playback_rec; F1/F2/F4/F5 from local keys */
                if (DAT_004553eb == 'd') {
                    DAT_004553eb = 'u';
                    FUN_00416cd0(&DAT_0044d020, game_mode);
                    FUN_00431c70();
                }
                if (DAT_004553ec == 'd') {
                    DAT_004553ec = 'u';
                    FUN_00416e30(0, &DAT_0044d020);
                }
                if (playback_rec[9] & 1u) FUN_00416c70(local_rec);
                if (playback_rec[9] & 2u) FUN_00416ca0(local_rec);
                if (DAT_004553e8 == 'd') {
                    DAT_004553e8 = 'u';
                    FUN_00416dd0(&DAT_0044d020);
                }
                if (DAT_004553e9 == 'd') {
                    DAT_004553e9 = 'u';
                    FUN_00416df0(&DAT_0044d020);
                }
                if (playback_rec[8] & 0x04u) FUN_00416e10(local_rec, &DAT_0044d020);
                if (playback_rec[8] & 0x10u) FUN_00416e60(local_rec, &DAT_0044d020, game_mode);
                if (playback_rec[8] & 0x20u) FUN_00416eb0(local_rec, &DAT_0044d020, game_mode);
                if (playback_rec[8] & 0x40u) FUN_00416f10(local_rec, &DAT_0044d020, game_mode);
                if (playback_rec[8] & 0x80u) FUN_00416f60(local_rec, &DAT_0044d020, game_mode);
            } else {
                if (DAT_00455471 == 'd') { DAT_00455471 = 'u'; FUN_00416c70(local_rec); }
                if (DAT_00455470 == 'd') { DAT_00455470 = 'u'; FUN_00416ca0(local_rec); }
                if (DAT_004553eb == 'd' && DAT_0044d020 == 0) { DAT_004553eb = 'u'; FUN_00416cd0(&DAT_0044d020, game_mode); }
                int blocked = DAT_0044d020;
                if (DAT_004553e8 == 'd' && blocked == 0) { DAT_004553e8 = 'u'; FUN_00416dd0(&DAT_0044d020); }
                if (DAT_004553e9 == 'd' && blocked == 0) { DAT_004553e9 = 'u'; FUN_00416df0(&DAT_0044d020); }
                if (DAT_004553ea == 'd' && blocked == 0) { DAT_004553ea = 'u'; FUN_00416e10(local_rec, &DAT_0044d020); }
                if (DAT_004553ec == 'd' && blocked == 0) { DAT_004553ec = 'u'; FUN_00416e30(0, &DAT_0044d020); }
                if (DAT_004553ed == 'd') { DAT_004553ed = 'u'; FUN_00416e60(local_rec, &DAT_0044d020, game_mode); }
                if (DAT_004553ee == 'd') { DAT_004553ee = 'u'; FUN_00416eb0(local_rec, &DAT_0044d020, game_mode); }
                if (DAT_004553ef == 'd') { DAT_004553ef = 'u'; FUN_00416f10(local_rec, &DAT_0044d020, game_mode); }
                if (DAT_004553f0 == 'd') { DAT_004553f0 = 'u'; FUN_00416f60(local_rec, &DAT_0044d020, game_mode); }
            }
        } else {
            int blocked = DAT_0044d020;
            if (DAT_00455471 == 'd') { DAT_0044d040[12] |= 0x08u; DAT_00455471 = 'u'; }
            if (DAT_00455470 == 'd') { DAT_0044d040[12] |= 0x10u; DAT_00455470 = 'u'; }
            if (DAT_004553e8 == 'd' && blocked == 0) { DAT_0044d040[10] |= 0x02u; DAT_004553e8 = 'u'; }
            if (DAT_004553e9 == 'd' && blocked == 0) { DAT_0044d040[10] |= 0x40u; DAT_004553e9 = 'u'; }
            if (DAT_004553ea == 'd' && blocked == 0) { DAT_0044d040[12] |= 0x02u; DAT_004553ea = 'u'; }
            if (DAT_004553eb == 'd' && blocked == 0) { DAT_0044d040[10] |= 0x04u; DAT_004553eb = 'u'; }
            if (DAT_004553ec == 'd' && blocked == 0) { DAT_0044d040[10] |= 0x08u; DAT_004553ec = 'u'; }
            if (DAT_004553ed == 'd' && blocked == 0) { DAT_0044d040[10] |= 0x10u; DAT_004553ed = 'u'; }
            if (DAT_004553ee == 'd' && blocked == 0) { DAT_0044d040[10] |= 0x20u; DAT_004553ee = 'u'; }
            if (DAT_004553ef == 'd' && blocked == 0) { DAT_0044d040[12] |= 0x04u; DAT_004553ef = 'u'; }
            if (DAT_004553f0 == 'd' && blocked == 0) { DAT_0044d040[10] |= 0x80u; DAT_004553f0 = 'u'; }

            int sync_rc = run_lockstep_exchange(global, 1);
            if (sync_rc != 0) {
                in_ECX = prev_ecx;
                return sync_rc;
            }

            if ((DAT_0044f198[10] & 0x02u) || (DAT_0044d040[10] & 0x02u)) FUN_00416dd0(&DAT_0044d020);
            if ((DAT_0044f198[10] & 0x40u) || (DAT_0044d040[10] & 0x40u)) FUN_00416df0(&DAT_0044d020);
            if ((DAT_0044f198[10] & 0x04u) || (DAT_0044d040[10] & 0x04u)) FUN_00416cd0(&DAT_0044d020, game_mode);
            if ((DAT_0044f198[10] & 0x08u) || (DAT_0044d040[10] & 0x08u)) FUN_00416e30(0, &DAT_0044d020);
            if ((DAT_0044f198[12] & 0x02u) || (DAT_0044d040[12] & 0x02u)) FUN_00416e10(local_rec, &DAT_0044d020);
            if ((DAT_0044f198[12] & 0x08u) || (DAT_0044d040[12] & 0x08u)) FUN_00416c70(local_rec);
            if ((DAT_0044f198[12] & 0x10u) || (DAT_0044d040[12] & 0x10u)) FUN_00416ca0(local_rec);
            if ((DAT_0044f198[10] & 0x10u) || (DAT_0044d040[10] & 0x10u)) FUN_00416e60(local_rec, &DAT_0044d020, game_mode);
            if ((DAT_0044f198[10] & 0x20u) || (DAT_0044d040[10] & 0x20u)) FUN_00416eb0(local_rec, &DAT_0044d020, game_mode);
            if ((DAT_0044f198[12] & 0x04u) || (DAT_0044d040[12] & 0x04u)) FUN_00416f10(local_rec, &DAT_0044d020, game_mode);
            if ((DAT_0044f198[10] & 0x80u) || (DAT_0044d040[10] & 0x80u)) FUN_00416f60(local_rec, &DAT_0044d020, game_mode);
        }
    }

    /* 4. Remote/playback input unpacking & 150-frame replay checksum */
    if (paused == 0) {
        FUN_004198f0(DAT_0044f198, DAT_00450b90, (int)(local_rec - DAT_0044f198));
        if (DAT_00450b84 != 0) {
            FUN_004197a0(playback_rec, DAT_00450b90);
            if (DAT_00450b8c % 150 == 0 && DAT_004588ac != 0) {
                int hp_sum = compute_slot20_hp_sum(global);
                const uint8_t *rep = (const uint8_t *)(uintptr_t)DAT_004588ac;
                int expected_sum = *(const int32_t *)(rep + 0x14b8 + (DAT_00450b8c / 150) * 4);
                if (hp_sum != expected_sum) {
                    MessageBoxA((HWND)0, "Recording file error! Replaying canceled!", (LPCSTR)0, 0);
                    FUN_00431c70();
                    if (DAT_00450b84 != 0 && DAT_0044d020 != 10) {
                        *game_mode = 6;
                        if (DAT_004588ac != 0 && DAT_00450b88 != 0) {
                            FUN_0043df00();
                            DAT_00458428 = *(const int32_t *)(rep + 0x630bb8);
                            DAT_0045842c = *(const int32_t *)(rep + 0x630bbc);
                        }
                        DAT_00450b88 = 0;
                        DAT_00450b84 = 0;
                        DAT_0044d020 = 10;
                    }
                    in_ECX = prev_ecx;
                    return DAT_0044d020;
                }
            }
        }
    }

    if (DAT_00450b80 != 0 && paused == 0) {
        const uint8_t *src_rec = (DAT_00450b84 == 0) ? local_rec : playback_rec;
        FUN_0043db40(src_rec);
        if (DAT_00450b8c % 150 == 0 && DAT_004588a8 != NULL) {
            int hp_sum = compute_slot20_hp_sum(global);
            *(int32_t *)((uint8_t *)DAT_004588a8 + 0x14b8 + (DAT_00450b8c / 150) * 4) = hp_sum;
        }
        if (DAT_00450b8c < 0x9e33f) {
            DAT_00450b8c++;
            if (DAT_00450b8c > 0x9e33e) {
                DAT_00450b8c = 0x9e33f;
            }
        } else {
            DAT_00450b8c = 0x9e33f;
            DAT_00450b80 = 0;
        }
    } else if (DAT_00450b84 != 0 && paused == 0) {
        if (DAT_00450b8c < 0x9e33f) {
            DAT_00450b8c++;
        } else {
            DAT_00450b8c = 0x9e33f;
        }
    }

    DAT_00450c00 = (DAT_00450bfc == 2) ? 1 : 0;

    if (paused != 0) {
        DAT_0044d02c = 1;
        in_ECX = prev_ecx;
        return DAT_0044d020;
    }

    if (DAT_00450bfc == 2) {
        DAT_00450bfc = 1;
    }

    /* 5. Frame modulo counters & alive-team round-end check */
    DAT_00450bd8 = 1 - DAT_00450bd8;
    DAT_00450bd0 = (DAT_00450bd0 + 1) % 12;
    DAT_00450bd4 = (DAT_00450bd4 + 1) % 3;

    int stage_all_players_dead = 0;
    if (*game_mode == 1) {
        if (DAT_0044d020 == 0) {
            stage_all_players_dead = 1;
            for (int i = 0; i < MAX_OBJECTS; ++i) {
                if (global->is_object_exists[i] != 0 && global->objects[i] != NULL &&
                    global->objects[i]->file != NULL &&
                    global->objects[i]->hp > 0 &&
                    global->objects[i]->file->type == TYPE_CHARACTER &&
                    global->objects[i]->team > 0 && global->objects[i]->team < 40 &&
                    global->objects[i]->team != 5) {
                    stage_all_players_dead = 0;
                    break;
                }
            }
            if (stage_all_players_dead == 1 || DAT_00450ba8 > 0) {
                DAT_00450bdc++;
                if (DAT_00450ba8 < 1 && DAT_00450bdc == 0x50) {
                    DAT_0044d02c = 1;
                    FUN_00402100();
                    FUN_00401a30();
                }
            }
        }
    } else {
        int team_counts[40];
        memset(team_counts, 0, sizeof(team_counts));
        for (int i = 0; i < MAX_OBJECTS; ++i) {
            if (global->is_object_exists[i] != 0 && global->objects[i] != NULL &&
                global->objects[i]->file != NULL &&
                global->objects[i]->hp > 0 &&
                global->objects[i]->file->type == TYPE_CHARACTER) {
                int t = global->objects[i]->team;
                if (t > 0 && t < 40 && t != 5) {
                    team_counts[t]++;
                }
            }
        }
        int alive_teams = 0;
        for (int t = 0; t < 40; ++t) {
            if (team_counts[t] > 0) {
                DAT_00450bf8 = t;
                alive_teams++;
            }
        }
        if (alive_teams < 2 && DAT_0044d020 == 0 && (DAT_00451b7c == 1 || *game_mode != 4)) {
            if (alive_teams == 0) {
                DAT_00450bf8 = -1;
            }
            DAT_00450bdc++;
            if (DAT_00450bdc == 0x50) {
                if (*game_mode != 0 && *game_mode != 2 && *game_mode != 3 && *game_mode != 4 && *game_mode != 5) {
                    FUN_00402100();
                }
                if (*game_mode != 5) {
                    DAT_0044d02c = 1;
                }
                FUN_00401a30();
            }
        } else if (*game_mode != 2 && *game_mode != 3) {
            DAT_00450bf8 = -1;
        }
    }

    if (DAT_00450bdc == 0x91) {
        if (DAT_00450c2c == 0) {
            DAT_00450bdc = 0x90;
        }
    } else if (DAT_00450bdc > 0x15d) {
        /* Revert transformations on match completion */
        for (int i = 0; i < MAX_OBJECTS; ++i) {
            if (global->is_object_exists[i] == 0 || global->objects[i] == NULL || !global->objects[i]->file) continue;
            object_t *obj = global->objects[i];
            if (obj->uid < 0) {
                if (obj->file->id == ID_LOUISE_EX_DAT && DAT_00458428 == 0) {
                    file_t *louis = find_loaded_file_by_id(global, ID_LOUIS_DAT);
                    if (louis) obj->file = louis;
                } else if (obj->fusion_state >= 0) {
                    int partner_slot = obj->fusion_partner;
                    obj->fusion_state = -1;
                    obj->firen_counter = 900;
                    file_t *self_file = find_loaded_file_by_id(global, (uint32_t)obj->fusion_self_id);
                    file_t *partner_file = find_loaded_file_by_id(global, (uint32_t)obj->fusion_partner_id);
                    if (self_file) obj->file = self_file;
                    if (partner_slot >= 0 && partner_slot < MAX_OBJECTS && global->objects[partner_slot]) {
                        object_t *partner = global->objects[partner_slot];
                        lf2_object_init(partner);
                        if (partner_file) {
                            partner->file = partner_file;
                            partner->weapon_hp = partner_file->weapon_hp;
                        }
                        global->is_object_exists[partner_slot] = 1;
                        partner->hp = obj->hp / 2;
                        partner->dark_hp = obj->dark_hp / 2;
                        obj->hp /= 2;
                        obj->dark_hp /= 2;
                        partner->x = obj->x;
                        partner->z = obj->z;
                        partner->y = 0;
                        partner->x_position = (double)partner->x;
                        partner->z_position = (double)partner->z;
                        partner->y_position = 0.0;
                        obj->x_velocity = 0.0;
                        partner->x_velocity = 0.0;
                        partner->facing = 1 - obj->facing;
                        obj->frame_id1 = 112;
                        partner->frame_id1 = 112;
                        obj->mp = 0;
                        partner->mp = 0;
                        partner->team = obj->team;
                    }
                }
            } else {
                file_t *orig = find_loaded_file_by_id(global, (uint32_t)obj->uid);
                if (orig) {
                    obj->file = orig;
                    obj->uid = -1;
                }
            }
        }
        if (*game_mode == 2) DAT_0044d020 = 0x1c;
        else if (*game_mode == 3) DAT_0044d020 = 0x80;
        else if (*game_mode == 4) DAT_0044d020 = 0xca;
        else DAT_0044d020 = 2;

        DAT_00450bdc = 0;
        FUN_00431c70();
        if (DAT_00450b88 != 0 && DAT_0044d020 != 10) {
            *game_mode = 6;
            if (DAT_004588ac != 0) {
                FUN_0043df00();
                const uint8_t *rep = (const uint8_t *)(uintptr_t)DAT_004588ac;
                DAT_00458428 = *(const int32_t *)(rep + 0x630bb8);
                DAT_0045842c = *(const int32_t *)(rep + 0x630bbc);
            }
            DAT_00450b88 = 0;
            DAT_00450b84 = 0;
            DAT_0044d020 = 10;
        }
        in_ECX = prev_ecx;
        return DAT_0044d020;
    }

    if (DAT_0044d020 == 0 && DAT_00450bdc >= 0x90) {
        for (int i = 0; i < 8; ++i) {
            if (global->objects[i] && (global->objects[i]->click_attack == 1 || global->objects[i]->click_jump == 1)) {
                if (DAT_00450c2c != 0 || *game_mode != 1 || DAT_00450ba8 == 0 || DAT_00450ba8 == 1 || DAT_00450ba8 == 2 || DAT_00450ba8 == 3) {
                    if (*game_mode == 1 && DAT_00450c2c == 0 && DAT_00450ba8 == 1) {
                        DAT_00450ba8 = 3;
                    }
                    DAT_00450b94 = (DAT_00450b94 / 10) * 10;
                    DAT_00450c2c = 0;
                    DAT_00450bdc = 0x15e;
                    break;
                }
            }
        }
    }

    /* 6. Per-object Loop 1: control input tick + post-control teleport/transform (0..399) */
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0 || !global->objects[i] || !global->objects[i]->file) continue;
        object_t *obj = global->objects[i];

        in_ECX = obj;
        FUN_00413080(*game_mode, i);
        in_ECX = global;

        uint32_t fid = obj->frame_id1;
        if (fid < MAX_FRAMES) {
            int32_t state = (int32_t)obj->file->frames[fid].state;
            if (state == 400 && DAT_00450bd8 == 0) {
                FUN_00403270(i, 1);
            } else if (state == 401 && DAT_00450bd8 == 0) {
                FUN_00403270(i, 2);
            }
            if (state == 500 && (obj->transformed_to_id == -1 || obj->uid > -1)) {
                obj->frame_id1 = 0;
            }
            if (state == 501 && obj->transformed_to_id > -1) {
                file_t *target = find_loaded_file_by_id(global, (uint32_t)obj->transformed_to_id);
                if (target) {
                    obj->uid = (int32_t)obj->file->id;
                    obj->file = target;
                    obj->frame_id1 = 0;
                    for (int c = 0; c < MAX_OBJECTS; ++c) {
                        if (global->is_object_exists[c] != 0 && global->objects[c] &&
                            global->objects[c]->clone == i && global->objects[c]->hp > 0) {
                            global->objects[c]->file = target;
                            global->objects[c]->frame_id1 = (global->objects[c]->y < 0) ? 212 : 0;
                        }
                    }
                }
            }
        }
    }

    /* 7. Per-object Loop 2: physics tick + removal, join_hp/reserve respawn, transform revert */
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0 || !global->objects[i] || !global->objects[i]->file) continue;
        object_t *obj = global->objects[i];

        in_ECX = obj;
        FUN_0040e490();
        in_ECX = global;

        if (obj->frame_id1 < MAX_FRAMES && obj->file->frames[obj->frame_id1].state == 9998) {
            global->is_object_exists[i] = 0;
            continue;
        }

        if (obj->frame_id1 < MAX_FRAMES &&
            obj->file->frames[obj->frame_id1].state == STATE_LYING &&
            obj->hp <= 0 &&
            (obj->clone >= 0 || obj->team == 5 || i >= 20) &&
            obj->blink_time > 0 && obj->blink_time < 5) {
            if (obj->join_hp > 0) {
                obj->team = 1;
                obj->spawn_reserve = obj->join_reserve;
                obj->max_hp = obj->join_hp;
                obj->dark_hp = obj->join_hp;
                obj->hp = obj->join_hp;
                obj->join_hp = 0;
                obj->mp = 0;
                if (obj->file->id >= 30 && obj->file->id <= 36) {
                    obj->pic_no_gain = 140;
                }
                obj->frame_id1 = 219;
                obj->shaking = 10;
                int marker = find_free_dynamic_slot(global);
                file_t *etc_file = find_loaded_file_by_id(global, ID_ETC_DAT);
                if (marker != -1 && etc_file != NULL) {
                    object_t *m = global->objects[marker];
                    lf2_object_init(m);
                    m->file = etc_file;
                    m->weapon_hp = etc_file->weapon_hp;
                    m->x = obj->x;
                    m->y = obj->y;
                    m->z = obj->z + 1;
                    m->team = obj->team;
                    m->x_position = (double)m->x;
                    m->y_position = (double)m->y;
                    m->z_position = (double)m->z;
                    m->frame_id1 = 6;
                    m->x_velocity = 0.0;
                    m->y_velocity = 0.0;
                    m->z_velocity = 0.0;
                    m->facing = FACING_RIGHT;
                    global->is_object_exists[marker] = 1;
                }
            } else if (obj->spawn_reserve < 2) {
                global->is_object_exists[i] = 0;
                continue;
            } else {
                obj->spawn_reserve--;
                int sum_x = 0, sum_z = 0, count = 0;
                for (int t = 0; t < MAX_OBJECTS; ++t) {
                    if (global->is_object_exists[t] != 0 && global->objects[t] &&
                        global->objects[t]->team == obj->team && global->objects[t]->hp > 0) {
                        sum_x += global->objects[t]->x;
                        sum_z += global->objects[t]->z;
                        count++;
                    }
                }
                if (count > 0) {
                    int rx = (sum_x / count) + FUN_00417170(0, 51) - 26;
                    int rz = (sum_z / count) + FUN_00417170(0, 31) - 16;
                    obj->x = rx;
                    obj->z = rz;
                    obj->x_position = (double)rx;
                    obj->z_position = (double)rz;
                }
                obj->y = -300;
                obj->y_position = -300.0;
                obj->mp = 500;
                obj->dark_hp = obj->max_hp;
                obj->hp = obj->max_hp;
                obj->blink_time = 20;
                obj->frame_id1 = 212;
                obj->y_velocity = 0.0;
            }
        }

        if (obj->uid > -1 && obj->click_DJA == 3 && obj->y == 0 && obj->hp > 0) {
            obj->click_DJA = 0;
            file_t *orig = find_loaded_file_by_id(global, (uint32_t)obj->uid);
            if (orig) {
                obj->file = orig;
                obj->frame_id1 = 245;
                obj->uid = -1;
                for (int c = 0; c < MAX_OBJECTS; ++c) {
                    if (global->is_object_exists[c] != 0 && global->objects[c] &&
                        global->objects[c]->clone == i && global->objects[c]->hp > 0) {
                        global->objects[c]->file = orig;
                        global->objects[c]->frame_id1 = (global->objects[c]->y < 0) ? 212 : 0;
                    }
                }
            }
        }
    }

    /* 8. Mid-frame combat & sky weapon drop */
    FUN_00417f80();
    if (DAT_0044d05c == 2) {
        DAT_0044d05c = 0;
    } else {
        FUN_00419380(*game_mode);
    }

    DAT_0045115c = 0;
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0 || !global->objects[i] || !global->objects[i]->file) continue;
        uint32_t t = global->objects[i]->file->type;
        if (t == TYPE_LIGHT_WEAPON || t == TYPE_HEAVY_WEAPON || t == TYPE_THROW_WEAPON || t == TYPE_DRINK) {
            DAT_0045115c++;
        }
        if (t == TYPE_CHARACTER) {
            FUN_0042e100(i);
        }
    }

    /* Background random sky weapon drop when weapon count < 4 and PRNG(200) == 0 */
    if (DAT_0045115c < 4 && FUN_00417170(0, 200) == 0) {
        int cand_files[64];
        int cand_count = 0;
        for (int f = 0; f < MAX_FILES && cand_count < 64; ++f) {
            if (global->files[f] != NULL) {
                uint32_t id = global->files[f]->id;
                if (id >= 100 && id < 200) {
                    if ((id != ID_MILK_DAT && id != ID_BEER_DAT) ||
                        (FUN_00417170(0, 2) != 0 && *game_mode != 1 && *game_mode != 2 && *game_mode != 3 && *game_mode != 4)) {
                        cand_files[cand_count++] = f;
                    }
                }
            }
        }
        int free_slot = find_free_dynamic_slot(global);
        if (cand_count > 0 && free_slot != -1) {
            file_t *wf = global->files[cand_files[FUN_00417170(0, cand_count)]];
            object_t *w = global->objects[free_slot];
            int sw = (DAT_00450bb4 > 0) ? DAT_00450bb4 : 800;
            int sx = FUN_00417170(0, 30) + 30 + FUN_00417170(0, 30) * ((sw - 60) / 30);
            int zw = (lf2_bg_zmax > lf2_bg_zmin + 60) ? (lf2_bg_zmax - lf2_bg_zmin - 60) : 60;
            int sz = FUN_00417170(0, 30) + lf2_bg_zmin + 30 + FUN_00417170(0, 30) * (zw / 30);

            lf2_object_init(w);
            w->file = wf;
            w->weapon_hp = wf->weapon_hp;
            w->x = sx;
            w->y = -500;
            w->z = sz;
            w->x_position = (double)sx;
            w->y_position = -500.0;
            w->z_position = (double)sz;
            w->x_velocity = 0.0;
            w->y_velocity = 0.0;
            w->z_velocity = 0.0;
            w->owner = 99;
            if (wf->id == ID_MILK_DAT) {
                w->hp = 200;
            }
            global->is_object_exists[free_slot] = 1;
            clear_vrest_for_slot(global, free_slot);
        }
    }

    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0 || !global->objects[i] || !global->objects[i]->file) continue;
        if (global->objects[i]->file->type > TYPE_CHARACTER) {
            FUN_0042e100(i);
        }
    }

    FUN_00418c30();
    FUN_004187b0();

    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0 || !global->objects[i]) continue;
        object_t *holder = global->objects[i];
        if (holder->weapon_type > 0) {
            int wid = holder->weapon_id;
            if (wid < 0 || wid >= MAX_OBJECTS || global->is_object_exists[wid] == 0 ||
                !global->objects[wid] || global->objects[wid]->holder_id != i) {
                holder->weapon_type = 0;
            }
        }
    }

    FUN_00417f80();
    FUN_004196f0();

    /* 9. Per-object Loop 3: transforms, regen, frame advance, opoint/weapon/team/FX (0..399) */
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0 || !global->objects[i] || !global->objects[i]->file) continue;
        object_t *obj = global->objects[i];

        if (obj->frame_id1 < MAX_FRAMES) {
            int32_t pre_state = (int32_t)obj->file->frames[obj->frame_id1].state;
            if (obj->file->type == TYPE_CHARACTER && pre_state == 9995) {
                file_t *lex = find_loaded_file_by_id(global, ID_LOUISE_EX_DAT);
                if (lex) obj->file = lex;
                obj->frame_id1 = 0;
            } else if (pre_state > 7999 && pre_state < 9000) {
                file_t *tf = find_loaded_file_by_id(global, (uint32_t)(pre_state - 8000));
                if (tf) obj->file = tf;
                obj->frame_id1 = 0;
                obj->pic_no_gain = 140;
            } else if (obj->file->type == TYPE_CHARACTER && pre_state == 9996 && obj->wait_counter == 1) {
                /* Louis armor shatter: 4 wristers (217) + 1 armour (218) */
                for (int p = 0; p < 5; ++p) {
                    int s = find_free_dynamic_slot(global);
                    if (s == -1) break;
                    file_t *pf = find_loaded_file_by_id(global, (p == 4) ? ID_LOUIS_ARMOUR_DAT : ID_LOUIS_WRISTER_DAT);
                    if (!pf) continue;
                    object_t *sh = global->objects[s];
                    lf2_object_init(sh);
                    sh->file = pf;
                    sh->weapon_hp = pf->weapon_hp;
                    sh->x = obj->x + FUN_00417170(0x9b, 7) - 3;
                    sh->y = obj->y + FUN_00417170(0x9c, 7) - 9;
                    sh->z = obj->z + 1;
                    sh->x_position = (double)sh->x;
                    sh->y_position = (double)sh->y;
                    sh->z_position = (double)sh->z;
                    sh->y_velocity = -(double)(FUN_00417170(0x9d, 15) / 2) - 5.0;
                    sh->arest = 6;
                    if (p == 0 || p == 2) sh->z_velocity = (double)FUN_00417170(0, 4) + 3.0;
                    else if (p == 1 || p == 3) sh->z_velocity = -3.0 - (double)FUN_00417170(0, 4);
                    else sh->z_velocity = 1.0;

                    if (p < 2) sh->x_velocity = -10.0 - (double)FUN_00417170(0, 4);
                    else if (p < 4) sh->x_velocity = (double)FUN_00417170(0, 4) + 10.0;
                    else sh->x_velocity = (double)FUN_00417170(0, 7) - 3.0;

                    sh->frame_id1 = (uint32_t)FUN_00417170(0, 4);
                    sh->facing = (uint8_t)FUN_00417170(0, 2);
                    global->is_object_exists[s] = 1;
                }
            }
        }

        /* Character HP, whirlwind, and MP regeneration */
        if (obj->file->type == TYPE_CHARACTER) {
            if (obj->hp > 0 && obj->hp < obj->dark_hp && DAT_00450bd0 == 0) {
                obj->hp++;
            }
            if (obj->thrown_injury < 0 && DAT_00450bd0 == 0) {
                int loss = (obj->armor_multiplier > 0) ? (900 / obj->armor_multiplier) : 9;
                obj->hp -= loss;
                obj->dark_hp -= loss / 3;
                if (obj->hp < 0) obj->hp = 0;
                if (obj->dark_hp < 0) obj->dark_hp = 0;
                obj->hp_lost += 9;
            }
            if ((obj->clone == -1 || obj->mp < 150) &&
                obj->mp < 500 && DAT_00450bd4 == 0 && obj->blink_time >= 0) {
                int eff_hp = (obj->hp > 500) ? 500 : obj->hp;
                if (obj->file->id == ID_FIRZEN_DAT || obj->file->id == ID_JULIAN_DAT) {
                    eff_hp /= 2;
                }
                obj->mp += (500 - eff_hp) / 100 + 1;
            }
        }

        in_ECX = obj;
        FUN_0040d960(*game_mode, i);
        in_ECX = global;

        int32_t curr_f = (int32_t)obj->frame_id1;
        if (curr_f / 100 == 11 || curr_f / 100 == 12) {
            for (int c = 0; c < MAX_OBJECTS; ++c) {
                if (global->is_object_exists[c] == 1 && global->objects[c] && global->objects[c]->clone == i) {
                    global->objects[c]->blink_time = 1100 - curr_f;
                }
            }
            obj->blink_time = 1100 - curr_f;
            obj->frame_id1 = 0;
            continue;
        }

        if (curr_f < 0 || curr_f > 399) {
            obj->frame_id1 = 0;
            global->is_object_exists[i] = 0;
            continue;
        }

        if (obj->file->type == TYPE_CHARACTER && obj->hp < 1 &&
            (curr_f < 12 || curr_f == 110 || curr_f == 111)) {
            obj->frame_id1 = 186;
            obj->y_velocity = -3.0;
            obj->y_accl = -3.0;
            obj->y_position = -1.0;
            obj->y = -1;
            curr_f = 186;
        }

        if (obj->file->type == TYPE_CHARACTER && obj->y == 0 &&
            obj->y_position == 0.0 && obj->y_velocity == 0.0 && obj->y_accl == 0.0 &&
            ((curr_f > 179 && curr_f < 190 && curr_f != 184) || (curr_f > 211 && curr_f < 215))) {
            obj->frame_id1 = 186;
            obj->y_velocity = -3.0;
            obj->y_accl = -3.0;
            obj->y_position = -1.0;
            obj->y = -1;
            curr_f = 186;
        }

        frame_t *cf = &obj->file->frames[obj->frame_id1];
        if (cf->opoint.kind > 0 && cf->opoint.oid > 0 && obj->wait_counter == 0 &&
            !(obj->shaking != 0 && obj->file->type == TYPE_CHARACTER)) {
            int count = 1;
            int face_mode = (int)cf->opoint.facing;
            if (face_mode > 10) {
                count = face_mode / 10;
                face_mode = face_mode % 10;
            }
            int spawned_slots[16];
            int spawned_count = 0;

            for (int k = 0; k < count && spawned_count < 16; ++k) {
                int ns = find_free_dynamic_slot(global);
                file_t *of = find_loaded_file_by_id(global, cf->opoint.oid);
                if (ns == -1 || !of) break;

                spawned_slots[spawned_count++] = ns;
                object_t *no = global->objects[ns];
                lf2_object_init(no);
                no->file = of;
                no->weapon_hp = of->weapon_hp;
                no->owner = obj->owner;
                clear_vrest_for_slot(global, ns);
                global->is_object_exists[ns] = 1;

                if (obj->facing == FACING_RIGHT) {
                    no->x = (obj->x - cf->centerx) + cf->opoint.x;
                } else {
                    no->x = (cf->centerx - cf->opoint.x) + obj->x;
                }
                no->y = (obj->y - cf->centery) + cf->opoint.y;
                no->team = obj->team;
                no->z_position = obj->z_position + 1.0;
                no->y_position = (double)no->y;
                no->x_position = (double)no->x;
                no->z = (int32_t)no->z_position;
                no->frame_id1 = cf->opoint.action;
                no->y_velocity = (double)cf->opoint.dvy;
                no->z_velocity = 0.0;

                if (no->frame_id1 < MAX_FRAMES) {
                    uint32_t nstate = of->frames[no->frame_id1].state;
                    if ((nstate == 3000 || nstate == 1002 || nstate == 3006) &&
                        of->id != 223 && of->id != 224) {
                        if (obj->click_up != 0 && obj->click_down == 0) no->z_velocity = -2.5;
                        else if (obj->click_down != 0) no->z_velocity = 2.5;
                        if (of->id == 211) no->z_velocity *= 0.25;
                    }
                }

                if (of->type == TYPE_CHARACTER) {
                    no->clone = (obj->clone < 0) ? i : obj->clone;
                    no->blink_time = obj->blink_time;
                }

                if (face_mode == 0) no->facing = obj->facing;
                else if (face_mode == 1) no->facing = (uint8_t)(1 - obj->facing);
                else no->facing = FACING_RIGHT;

                no->x_velocity = (no->facing == FACING_RIGHT)
                    ? (double)cf->opoint.dvx
                    : -(double)cf->opoint.dvx;

                if (count > 1) {
                    double spread = ((double)k * 10.0) / ((double)count - 1.0) - 5.0;
                    no->z_velocity += spread;
                    if (no->x_velocity > 0.0 && spread > 0.0) {
                        no->x_velocity -= spread;
                    } else if (no->x_velocity < 0.0 && spread < 0.0) {
                        no->x_velocity -= spread;
                    } else {
                        no->x_velocity += spread;
                    }
                }

                if (obj->file->type == TYPE_ATTACK && obj->frame_id1 < MAX_FRAMES &&
                    obj->file->frames[obj->frame_id1].state == 3003) {
                    no->vrest_of_objects[i] = 10;
                }

                if (of->id == ID_RUDOLF_DAT || of->id == ID_JULIAN_DAT) {
                    no->hp = 10;
                    no->max_hp = 10;
                    no->dark_hp = 10;
                    no->mp = 5;
                }

                if (cf->opoint.kind == 2) {
                    obj->weapon_type = 1;
                    no->weapon_type = -1;
                    obj->weapon_id = ns;
                    no->holder_id = i;
                    no->team = obj->team;
                }
            }

            if (spawned_count > 1) {
                for (int a = 0; a < spawned_count; ++a) {
                    int sid = spawned_slots[a];
                    if ((spawned_count & 1) == 0) {
                        if (a < spawned_count / 2 - 1) {
                            global->objects[sid]->arest = (spawned_count / 2 - a) * 2 - 2;
                        } else if (a > spawned_count / 2) {
                            global->objects[sid]->arest = (a - spawned_count / 2) * 2;
                        }
                    } else {
                        if (a < spawned_count / 2) {
                            global->objects[sid]->arest = (spawned_count / 2 - a) * 2;
                        } else if (a > spawned_count / 2) {
                            global->objects[sid]->arest = (a - spawned_count / 2) * 2;
                        }
                    }
                    for (int b = 0; b < a; ++b) {
                        int prev_sid = spawned_slots[b];
                        global->objects[sid]->vrest_of_objects[prev_sid] = 40;
                        global->objects[prev_sid]->vrest_of_objects[sid] = 40;
                    }
                }
            }
        } else if ((obj->file->type == TYPE_LIGHT_WEAPON || obj->file->type == TYPE_HEAVY_WEAPON ||
                    obj->file->type == TYPE_THROW_WEAPON || obj->file->type == TYPE_DRINK) &&
                   obj->weapon_hp < 0) {
            obj->weapon_hp = 0;
            uint32_t wid = obj->file->id;
            int pieces = 0;
            if (wid == ID_HOE_DAT || wid == ID_LOUIS_ARMOUR_DAT) pieces = 7;
            else if (wid == ID_STICK_DAT || wid == ID_ICE_SWORD_DAT || wid == ID_LOUIS_WRISTER_DAT) pieces = 5;
            else if (wid == ID_HENRY_ARROW1_DAT || wid == ID_KNIFE_DAT || wid == ID_BOOMERANG_DAT) pieces = 3;
            else if (wid == ID_STONE_DAT) pieces = 13;
            else if (wid == ID_WOODEN_BOX_DAT) pieces = 15;
            else if (wid == ID_BASEBALL_DAT) pieces = 4;
            else if (wid == ID_MILK_DAT || wid == ID_BEER_DAT) pieces = 9;

            if (obj->file->weapon_broken_sound_id > -1) {
                FUN_00416fb0(obj->x, obj->file->weapon_broken_sound_id);
            }
            file_t *bw = find_loaded_file_by_id(global, ID_BROKEN_WEAPON_DAT);
            if (bw) {
                for (int p = 0; p < pieces; ++p) {
                    int s = find_free_dynamic_slot(global);
                    if (s == -1) break;
                    object_t *sh = global->objects[s];
                    lf2_object_init(sh);
                    sh->file = bw;
                    sh->weapon_hp = bw->weapon_hp;
                    sh->x = obj->x + FUN_00417170(0, 7) - 3;
                    sh->y = obj->y + FUN_00417170(0, 7) - 3;
                    sh->z = obj->z;
                    sh->x_position = (double)sh->x;
                    sh->y_position = (double)sh->y;
                    sh->z_position = (double)sh->z;
                    sh->x_velocity = (double)FUN_00417170(0, 11) - 5.0;
                    if (wid == ID_STONE_DAT || wid == ID_WOODEN_BOX_DAT || wid == ID_ICE_SWORD_DAT) {
                        sh->y_velocity = -(double)(FUN_00417170(0, 11) / 2) - 8.0;
                    } else if (wid == ID_STICK_DAT || wid == ID_HOE_DAT || wid == ID_HENRY_ARROW1_DAT ||
                               wid == ID_KNIFE_DAT || wid == ID_BASEBALL_DAT || wid == ID_MILK_DAT ||
                               wid == ID_BEER_DAT || wid == ID_BOOMERANG_DAT || wid == ID_LOUIS_WRISTER_DAT ||
                               wid == ID_LOUIS_ARMOUR_DAT) {
                        sh->y_velocity = -(double)(FUN_00417170(0, 11) / 2) - 6.0;
                    }
                    if (wid == ID_STONE_DAT) sh->frame_id1 = (p < 5) ? (uint32_t)FUN_00417170(0, 4) : (uint32_t)(FUN_00417170(0, 4) + 4);
                    else if (wid == ID_STICK_DAT) sh->frame_id1 = (p < 2) ? (uint32_t)(FUN_00417170(0, 4) + 10) : (uint32_t)(FUN_00417170(0, 4) + 14);
                    else if (wid == ID_ICE_SWORD_DAT) sh->frame_id1 = (p < 2) ? (uint32_t)(FUN_00417170(0, 4) + 150) : (uint32_t)(FUN_00417170(0, 4) + 154);
                    else if (wid == ID_HOE_DAT) sh->frame_id1 = (p < 5) ? (uint32_t)(FUN_00417170(0, 2) * 4 + 20 + FUN_00417170(0, 2)) : (uint32_t)(FUN_00417170(0, 2) + 30);
                    else if (wid == ID_WOODEN_BOX_DAT) {
                        if (p < 2) sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 40);
                        else if (p < 5) sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 44);
                        else if (p < 8) sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 50);
                        else sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 54);
                    } else if (wid == ID_KNIFE_DAT) {
                        if (p < 2) sh->frame_id1 = (uint32_t)(FUN_00417170(0, 2) + 54);
                        else sh->frame_id1 = (uint32_t)(FUN_00417170(0, 2) + 30);
                    } else if (wid == ID_BOOMERANG_DAT) sh->frame_id1 = (uint32_t)(FUN_00417170(0, 2) + 170);
                    else if (wid == ID_BASEBALL_DAT) sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 60);
                    else if (wid == ID_MILK_DAT) {
                        if (p < 1) sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 70);
                        else if (p < 3) sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 80);
                        else { sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 74); sh->y_velocity = -(double)(FUN_00417170(0, 11) / 2) - 4.0; }
                    } else if (wid == ID_BEER_DAT) {
                        if (p < 1) sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 160);
                        else if (p < 3) sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 164);
                        else { sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 74); sh->y_velocity = -(double)(FUN_00417170(0, 11) / 2) - 4.0; }
                    } else if (wid == ID_LOUIS_WRISTER_DAT || wid == ID_LOUIS_ARMOUR_DAT) {
                        sh->frame_id1 = (uint32_t)(FUN_00417170(0, 4) + 174);
                    }
                    global->is_object_exists[s] = 1;
                }
            }
            global->is_object_exists[i] = 0;
        } else if (i < 10 && obj->hp > 0 && obj->file->type == TYPE_CHARACTER) {
            int cmd = 0;
            if (obj->input_history[1] == 9) {
                if (obj->input_history[2] == 0 && obj->input_history[3] == 9 && obj->input_history[4] == 0) {
                    cmd = 100; /* D-J-D-J: Come / Move here */
                } else if (obj->input_history[2] == 9 && obj->input_history[3] == 9 && obj->input_history[4] == 9) {
                    cmd = 102; /* D-D-D-D: Stay / Follow */
                } else if (obj->input_history[2] == 5 && obj->input_history[3] == 9 && obj->input_history[4] == 5) {
                    cmd = 104; /* D-A-D-A: Free / Cancel follow */
                }
            }
            if (cmd != 0) {
                memset(obj->input_history, 0, sizeof(obj->input_history));
                int ms = find_free_dynamic_slot(global);
                file_t *etc_f = find_loaded_file_by_id(global, ID_ETC_DAT);
                if (ms != -1 && etc_f != NULL) {
                    object_t *m = global->objects[ms];
                    lf2_object_init(m);
                    m->file = etc_f;
                    m->weapon_hp = etc_f->weapon_hp;
                    m->x = obj->x;
                    m->y = 0;
                    m->z = obj->z;
                    m->frame_id1 = (uint32_t)(cmd - 100);
                    m->x_position = (double)m->x;
                    m->y_position = 0.0;
                    m->z_position = (double)m->z;
                    m->x_velocity = 0.0;
                    m->y_velocity = 0.0;
                    global->is_object_exists[ms] = 1;
                    for (int t = 0; t < MAX_OBJECTS; ++t) {
                        if (global->is_object_exists[t] == 1 && global->objects[t] &&
                            global->objects[t]->hp > 0 && global->objects[t]->file &&
                            global->objects[t]->file->type == TYPE_CHARACTER &&
                            global->objects[t]->team == obj->team) {
                            if (cmd == 100) {
                                global->objects[t]->ai_target_x = m->x + FUN_00417170(0, 81) - 40;
                                global->objects[t]->ai_target_z = m->z + FUN_00417170(0, 81) - 40;
                            } else if (cmd == 102) {
                                global->objects[t]->follow_order = 1;
                            } else if (cmd == 104) {
                                global->objects[t]->follow_order = 0;
                            }
                        }
                    }
                }
            }
        }

        /* Ice shatter & fire smoke particle FX comparing frame_id3 (previous) vs frame_id1 (current) */
        uint32_t pf = obj->frame_id3;
        if (pf < MAX_FRAMES) {
            uint32_t pstate = obj->file->frames[pf].state;
            uint32_t cstate = obj->file->frames[obj->frame_id1].state;
            if ((pstate == STATE_ICE || pf == 200) && cstate != STATE_ICE && obj->frame_id1 != 200) {
                FUN_00417090(obj->x, 15); /* data\066.wav */
                file_t *bw = find_loaded_file_by_id(global, ID_BROKEN_WEAPON_DAT);
                if (bw) {
                    for (int k = 0; k < 15; ++k) {
                        int s = find_free_dynamic_slot(global);
                        if (s == -1) break;
                        object_t *sh = global->objects[s];
                        lf2_object_init(sh);
                        sh->file = bw;
                        sh->weapon_hp = bw->weapon_hp;
                        sh->x = obj->x;
                        sh->y = obj->y;
                        sh->z = obj->z;
                        sh->x_position = (double)(FUN_00417170(200, 39) - 19) + obj->x_position;
                        sh->y_position = obj->y_position - (double)FUN_00417170(199, 29);
                        sh->z_position = obj->z_position;
                        sh->y_velocity = -(double)(FUN_00417170(201, 20) / 2) - 8.0;
                        sh->x_velocity = obj->pic_x_gain * 0.5 + ((double)FUN_00417170(202, 11) - 5.0);
                        if (k < 2) sh->frame_id1 = 120;
                        else if (k < 5) sh->frame_id1 = 130;
                        else if (k < 9) sh->frame_id1 = 125;
                        else sh->frame_id1 = 135;
                        global->is_object_exists[s] = 1;
                    }
                }
            }
            if (pstate == STATE_BURNING || pstate == STATE_FIRE) {
                int puffs = 0;
                if (cstate == STATE_BURNING || cstate == STATE_FIRE) {
                    if (FUN_00417170(0, 4) == 0) puffs = 1;
                } else {
                    puffs = 7;
                }
                if (puffs > 0) {
                    file_t *bw = find_loaded_file_by_id(global, ID_BROKEN_WEAPON_DAT);
                    if (bw) {
                        for (int k = 0; k < puffs; ++k) {
                            int s = find_free_dynamic_slot(global);
                            if (s == -1) break;
                            object_t *sm = global->objects[s];
                            lf2_object_init(sm);
                            sm->file = bw;
                            sm->weapon_hp = bw->weapon_hp;
                            sm->x = obj->x;
                            sm->y = obj->y;
                            sm->z = obj->z;
                            sm->x_position = (double)(FUN_00417170(0xcd, 59) - 29) + obj->x_position;
                            sm->y_position = obj->y_position - (double)FUN_00417170(0xcc, 29);
                            sm->z_position = obj->z_position;
                            sm->y_velocity = -1.0;
                            sm->x_velocity = ((double)FUN_00417170(0xce, 11) - 5.0) + obj->x_velocity;
                            sm->frame_id1 = (uint32_t)(FUN_00417170(0xcf, 2) + 140);
                            global->is_object_exists[s] = 1;
                        }
                    }
                }
            }
        }
        obj->frame_id3 = obj->frame_id1;
    }

    /* 10. F8 sky weapon fill */
    if (DAT_00450bb8 == 1) {
        for (int f = 0; f < MAX_FILES; ++f) {
            if (!global->files[f]) continue;
            uint32_t id = global->files[f]->id;
            if (id >= 100 && id < 200 && (id != ID_MILK_DAT || FUN_00417170(0, 2) != 0)) {
                int s = find_free_dynamic_slot(global);
                if (s == -1) break;
                file_t *wf = global->files[f];
                object_t *w = global->objects[s];
                int sw = (DAT_00450bb4 > 0) ? DAT_00450bb4 : 800;
                int sx = FUN_00417170(0xd2, 30) + 30 + FUN_00417170(0xd1, 30) * ((sw - 60) / 30);
                int zw = (lf2_bg_zmax > lf2_bg_zmin + 60) ? (lf2_bg_zmax - lf2_bg_zmin - 60) : 60;
                int sz = FUN_00417170(0xd4, 30) + lf2_bg_zmin + 30 + FUN_00417170(0xd3, 30) * (zw / 30);

                lf2_object_init(w);
                w->file = wf;
                w->weapon_hp = wf->weapon_hp;
                w->x = sx;
                w->y = -500;
                w->z = sz;
                w->x_position = (double)sx;
                w->y_position = -500.0;
                w->z_position = (double)sz;
                w->x_velocity = 0.0;
                w->y_velocity = 0.0;
                w->z_velocity = 0.0;
                if (wf->id == ID_MILK_DAT) w->hp = 200;
                global->is_object_exists[s] = 1;
                clear_vrest_for_slot(global, s);
            }
        }
    }

    /* 11. Per-object Loop 4: F9 destroy, F7 recover, state 1700 self-heal, Jan heal, distance/hit reset */
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0 || !global->objects[i] || !global->objects[i]->file) continue;
        object_t *obj = global->objects[i];

        if (DAT_00450bb8 == 2) {
            uint32_t t = obj->file->type;
            if (t == TYPE_LIGHT_WEAPON || t == TYPE_HEAVY_WEAPON || t == TYPE_THROW_WEAPON || t == TYPE_DRINK) {
                obj->weapon_hp = -1;
            } else if (*game_mode == 1 && obj->team == 5 && t == TYPE_CHARACTER && obj->file->id != ID_CRIMINAL_DAT) {
                obj->hp = 0;
                obj->mp = 0;
            }
        }

        if (DAT_00450bc0 == 1 && (*game_mode != 1 || (i < 8 && obj->team == 1))) {
            if (obj->max_hp < 500) obj->max_hp = 500;
            obj->dark_hp = obj->max_hp;
            obj->hp = obj->dark_hp;
            obj->mp = 500;
            FUN_00402000();
        }

        if (obj->curing_hp / 1000 == 1 && obj->hp > 0) {
            obj->curing_hp--;
            if (obj->curing_hp % 8 == 0) {
                if (obj->hp < obj->dark_hp) {
                    obj->hp = (obj->hp < obj->dark_hp - 8) ? (obj->hp + 8) : obj->dark_hp;
                } else {
                    obj->curing_hp = 0;
                }
            }
            if (obj->curing_hp % 1000 == 0) {
                obj->curing_hp = 0;
            }
        }

        if (obj->heal_timer > 0 && obj->hp > 0) {
            obj->heal_timer--;
            if (obj->heal_timer % 8 == 0 && obj->hp < obj->dark_hp) {
                obj->hp += 8;
                if (obj->hp > obj->dark_hp) {
                    obj->hp = obj->dark_hp;
                    obj->heal_timer = 0;
                }
            }
        }

        if (obj->frame_id1 < MAX_FRAMES && obj->file->frames[obj->frame_id1].state == 1700) {
            obj->curing_hp = 1100;
        }

        obj->attackable_distance = 1000;
        obj->vulnerable_distance = 1000;
        obj->_unknown29 = 1000;
        obj->successful_attacks = 0;
        obj->flag_eb = 0;
    }

    DAT_00450bc0 = 0;
    DAT_00450bb8 = 0;

    if (DAT_00450bdc < 100) {
        DAT_00450bbc++;
    }

    if (DAT_00450bdc == 101 && DAT_00450be4 != 0 && DAT_00450b80 != 0 && DAT_00450b84 == 0) {
        if (DAT_004588a8 != NULL) {
            uint8_t *buf = (uint8_t *)DAT_004588a8;
            *(int32_t *)(buf + 0x144) = DAT_00450bbc;
            *(int32_t *)(buf + 0x8ac) = (int32_t)DAT_0044fb6c;
            *(int32_t *)(buf + 0x8b0) = DAT_00450c18;
            *(int32_t *)(buf + 0x8b4) = DAT_00450c1c;
            *(int32_t *)(buf + 0x8b8) = DAT_00450c20;
            *(int32_t *)(buf + 0x8bc) = DAT_00450c24;
        }
        DAT_00450b6c = 0;
        DAT_00450b70 = 2;
        if (DAT_004588ac != 0 && DAT_00450b88 != 0) {
            FUN_0043df00();
            const uint8_t *rep = (const uint8_t *)(uintptr_t)DAT_004588ac;
            DAT_00458428 = *(const int32_t *)(rep + 0x630bb8);
            DAT_0045842c = *(const int32_t *)(rep + 0x630bbc);
        }
        FUN_0043dd60();
        DAT_00450b80 = 0;
        DAT_00450b84 = 0;
    }

    /* 12. Flush spatialized sounds */
    FUN_00419e60();

    in_ECX = prev_ecx;
    return DAT_0044d020;
}

int FUN_0041bc90(void)
{
    if (in_ECX != NULL) {
        return lf2_battle_frame_tick((global_t *)in_ECX, &DAT_00451160);
    }
    return func_0041c5f0_net_lockstep();
}

int FUN_0041c5f0(void)
{
    return func_0041c5f0_net_lockstep();
}

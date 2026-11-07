#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <windows.h>
#include <winsock.h>

/*
 * Function: Lockstep Network Packet Processing & Synchronization
 * Original Virtual Address: 0x0041BC90 (FUN_0041bc90, lockstep block at 0x0041C5F0 - 0x0041CC90)
 *
 * Description: Real-time non-blocking 22-byte packet transmission and reception
 * for synchronous multiplayer. Gathers 8 player controller inputs, computes
 * active character HP checksums across the 20 character slots (objects[0..19]),
 * verifies the 16-bit data file checksum (DAT_0044f620), and halts execution
 * upon desynchronization ("Connection Lost!", "Version not matched! ",
 * "Synchronisation Error!", or "Data Error! You and your opponent have different set of data files.").
 */

#define PACKET_SIZE 22 /* 0x16 */

#pragma pack(push, 1)
typedef struct {
    unsigned char player_inputs[8]; /* +0..+7: Packed player 0..7 inputs (1 + 2^(X+1)) */
    unsigned char control_flags;    /* +8: Function key flags */
    unsigned char seq_counter;      /* +9: Frame sequence counter modulo 50 (DAT_00450bf0 -> "Connection Lost!") */
    unsigned char func_keys_1;      /* +10: F-key flags byte 1 */
    unsigned char version_tag;      /* +11: Version tag (DAT_0044d03c -> "Version not matched! ") */
    unsigned char func_keys_2;      /* +12: F-key flags byte 2 */
    unsigned char hp_checksum;      /* +13: Active character HP checksum ((sum % 100) + 1 == DAT_00450bf4 -> "Synchronisation Error!") */
    unsigned char data_crc_lo;      /* +14: Low byte of DAT_0044f620 */
    unsigned char data_crc_hi;      /* +15: High byte of DAT_0044f620 */
    unsigned char payload[6];       /* +16..+21: Sub-frame synchronization */
} lf2_net_packet_t;
#pragma pack(pop)

SOCKET g_connected_socket = INVALID_SOCKET;
lf2_net_packet_t g_outgoing_packet = {0}; /* 0x0044D040 */
lf2_net_packet_t g_incoming_packet = {0}; /* 0x0044F198 */
unsigned int g_current_frame = 0;

int func_0041c5f0_net_lockstep(void)
{
    u_long non_blocking = 0;
    int bytes_received = 0;
    global_t *global = (global_t *)in_ECX;

    /* 0x0041C626: Configure socket mode via ioctlsocket (FIONBIO = 0x8004667E) */
    ioctlsocket(g_connected_socket, FIONBIO, &non_blocking);

    /* 0x0041CAD9: Compute HP checksum across the 20 active character slots (objects[0..19]) */
    int hp_sum = 0;
    if (global != NULL) {
        for (int i = 0; i < 20; ++i) {
            if (global->is_object_exists[i] == 1 && global->objects[i] != NULL) {
                hp_sum += global->objects[i]->hp;
            }
        }
    }

    DAT_00450bf4 = hp_sum - (hp_sum / 100) * 100 + 1;
    DAT_00450bf0 = (DAT_00450bf0 + 1) % 50;

    g_outgoing_packet.seq_counter = (unsigned char)DAT_00450bf0;
    g_outgoing_packet.version_tag = (unsigned char)DAT_0044d03c;
    g_outgoing_packet.hp_checksum = (unsigned char)DAT_00450bf4;
    g_outgoing_packet.data_crc_lo = (unsigned char)(DAT_0044f620 & 0xFF);
    g_outgoing_packet.data_crc_hi = (unsigned char)((DAT_0044f620 / 256) & 0xFF);

    /* 0x0041CBD0: send(DAT_0044f46c, &DAT_0044d040, 0x16, 0) */
    send(g_connected_socket, (const char *)&g_outgoing_packet, PACKET_SIZE, 0);

    /* 0x0041CBE9: recv(DAT_0044f46c, &DAT_0044f198, 0x16, 0) */
    bytes_received = recv(g_connected_socket, (char *)&g_incoming_packet, PACKET_SIZE, 0);

    /* 0x0041CC00: Re-receive until full 22-byte packet arrives */
    while (bytes_received > 0 && bytes_received < PACKET_SIZE) {
        int more = recv(g_connected_socket, ((char *)&g_incoming_packet) + bytes_received,
                        PACKET_SIZE - bytes_received, 0);
        if (more <= 0) break;
        bytes_received += more;
    }

    /* Check 1 (Offset +9): Sequence counter modulo 50 match */
    if ((int)(signed char)g_incoming_packet.seq_counter != DAT_00450bf0) {
        MessageBoxA((HWND)0, "Connection Lost!", "Error", 0);
        return -1;
    }

    /* Check 2 (Offset +11): Version match */
    if ((int)(signed char)g_incoming_packet.version_tag != DAT_0044d03c) {
        MessageBoxA((HWND)0, "Version not matched! ", "Error", 0);
        return -2;
    }

    /* Check 3 (Offset +13): Deterministic HP checksum match */
    if ((int)(signed char)g_incoming_packet.hp_checksum != DAT_00450bf4) {
        MessageBoxA((HWND)0, "Synchronisation Error!", "Error", 0);
        return -3;
    }

    /* Check 4 (Offsets +14..+15): Data file checksum match */
    if ((signed char)g_incoming_packet.data_crc_lo != (signed char)(DAT_0044f620 & 0xFF) ||
        (signed char)g_incoming_packet.data_crc_hi != (signed char)((DAT_0044f620 / 256) & 0xFF)) {
        MessageBoxA((HWND)0, "Data Error! You and your opponent have different set of data files.", "Error", 0);
        return -4;
    }

    return 0;
}

int FUN_0041bc90(void)
{
    return func_0041c5f0_net_lockstep();
}

int FUN_0041c5f0(void)
{
    return FUN_0041bc90();
}


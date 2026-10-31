/*
 * Function: Lockstep Network Packet Processing & Synchronization
 * Original Virtual Address: 0x0041C5F0 / 0x0041CB80
 *
 * Description: Real-time non-blocking 22-byte packet transmission and reception
 * for synchronous multiplayer. Gathers 8 player controller inputs, computes
 * active character HP checksums, and halts execution upon desynchronization
 * ("Connection Lost!", "Version not matched!", or "Synchronisation Error!").
 */

#include <windows.h>
#include <winsock.h>

#define PACKET_SIZE 22 // 0x16

#pragma pack(push, 1)
typedef struct {
    unsigned char player_inputs[8]; // +0..+7: Packed player 0..7 inputs (1 + 2^(X+1))
    unsigned char control_flags;    // +8: F1 pause / F2 frame step / function keys
    unsigned char seq_counter;      // +9: Frame sequence counter modulo 50 (checked -> "Connection Lost!")
    unsigned char pad_10;           // +10: Sub-sequence padding
    unsigned char version_tag;      // +11: Version tag (checked against DAT_0044d03c -> "Version not matched!")
    unsigned char pad_12;           // +12: Sub-frame sync padding
    unsigned char hp_checksum;      // +13: Active player cumulative HP checksum (checked against DAT_00450bf4 -> "Synchronisation Error!")
    unsigned char prng_tag;         // +14: PRNG high bits / sub-frame tag
    unsigned char sub_sync;         // +15: Sub-frame sync tag
    unsigned char payload[6];       // +16..+21: Trailing PRNG indices and sub-frame synchronization
} lf2_net_packet_t;
#pragma pack(pop)

extern SOCKET g_connected_socket;
extern lf2_net_packet_t g_outgoing_packet; // 0x0044D040
extern lf2_net_packet_t g_incoming_packet; // 0x0044F198
extern unsigned int g_current_frame;
extern void* g_objects[400]; // Active object table (400 slots in global_t)

int func_0041c5f0_net_lockstep(void) {
    u_long non_blocking = 1;
    int bytes_sent = 0;
    int bytes_received = 0;

    // 0x0041C626: Set non-blocking mode via ioctlsocket (FIONBIO = 0x8004667E)
    ioctlsocket(g_connected_socket, FIONBIO, &non_blocking);

    // 0x0041C6C7 - 0x0041CAAC: Pack local keyboard inputs into packet:
    // Bit 0 (0x01): Active Idle
    // Bit 1 (0x02): Up
    // Bit 2 (0x04): Right
    // Bit 3 (0x08): Attack
    // Bit 4 (0x10): Jump
    // Bit 5 (0x20): Defend
    // Bit 6 (0x40): Down
    // Bit 7 (0x80): Left

    // 0x0041CAD9: Compute HP checksum of active players
    unsigned int hp_sum = 0;
    for (int i = 0; i < 8; ++i) {
        // if player slot active:
        // hp_sum += object[i]->hp; (offset 0x2fc)
    }
    g_outgoing_packet.hp_checksum = (unsigned char)(hp_sum & 0xFF);
    g_outgoing_packet.seq_counter = (unsigned char)(g_current_frame % 50);

    // 0x0041CBD0: send(socket, buffer=0x0044D040, len=22, flags=0)
    bytes_sent = send(g_connected_socket, (const char*)&g_outgoing_packet, PACKET_SIZE, 0);

    // 0x0041CBE9: recv(socket, buffer=0x0044F198, len=22, flags=0)
    bytes_received = recv(g_connected_socket, (char*)&g_incoming_packet, PACKET_SIZE, 0);

    // 0x0041CC00: Re-receive if partial packet
    while (bytes_received > 0 && bytes_received < PACKET_SIZE) {
        int more = recv(g_connected_socket, ((char*)&g_incoming_packet) + bytes_received,
                        PACKET_SIZE - bytes_received, 0);
        if (more <= 0) break;
        bytes_received += more;
    }

    // 0x0041CC27: Desynchronization verification
    // Check 1 (Offset +9): Sequence counter modulo 50 match
    if (g_incoming_packet.seq_counter != g_outgoing_packet.seq_counter) {
        MessageBoxA(NULL, "Connection Lost!", "Error", MB_OK); // 0x004493B4
        return -1;
    }

    // Check 2 (Offset +11): Version / mode match
    if (g_incoming_packet.version_tag != g_outgoing_packet.version_tag) {
        MessageBoxA(NULL, "Version not matched!", "Error", MB_OK); // 0x0044939C
        return -2;
    }

    // Check 3 (Offset +13): Deterministic HP checksum match
    if (g_incoming_packet.hp_checksum != g_outgoing_packet.hp_checksum) {
        MessageBoxA(NULL, "Synchronisation Error!", "Error", MB_OK); // 0x00449384
        return -3;
    }

    return 0;
}

#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <array>
#include "gameplay/entity.h"

namespace lf2 {

// LF2 standard default network port (0x00402D36 / 0x004284ED: push 0x3039 / 12345)
constexpr uint16_t LF2_DEFAULT_PORT = 12345;

// Handshake constants
constexpr std::string_view LF2_HANDSHAKE_MSG = "u can connect";
constexpr size_t LF2_HANDSHAKE_LEN = 14;          // "u can connect\0" (13 ASCII chars + null terminator)
constexpr size_t LF2_HANDSHAKE_77_LEN = 77;       // Slot negotiation & player names
constexpr size_t LF2_PRNG_SEED_LEN = 3001;        // 1-byte header + 3,000-byte PRNG table

// 22-byte Lockstep Packet Size
constexpr size_t LF2_PACKET_SIZE = 22; // 0x16

// Input bitmask definitions (0x0041C9D4 - 0x0041CAAC)
// Formula: 1 + 2^(X+1), where bit 0 is active idle (0x01)
enum NetInputBits : uint8_t {
    NET_KEY_IDLE    = 0x01,
    NET_KEY_UP      = 0x02,
    NET_KEY_RIGHT   = 0x04,
    NET_KEY_ATTACK  = 0x08,
    NET_KEY_JUMP    = 0x10,
    NET_KEY_DEFEND  = 0x20,
    NET_KEY_DOWN    = 0x40,
    NET_KEY_LEFT    = 0x80,
};

// 1:1 Binary Layout of the 22-byte Network Packet (0x0044D040 / 0x0044F198)
// Verified via disassembly at 0x0041CB50 - 0x0041CCD0:
#pragma pack(push, 1)
struct net_packet_t {
    uint8_t  player_inputs[8]; // +0..+7: Packed inputs for player slots 0..7
    uint8_t  control_flags;    // +8: System control / function keys (F1 pause, F2 step)
    uint8_t  seq_counter;      // +9: Frame sequence counter modulo 50 (checked -> "Connection Lost!")
    uint8_t  _pad10;           // +10: Sub-sequence padding
    uint8_t  version_tag;      // +11: Protocol/version byte (checked -> "Version not matched!")
    uint8_t  _pad12;           // +12: Sub-frame sync padding
    uint8_t  hp_checksum;      // +13: Active player cumulative HP checksum (checked -> "Synchronisation Error!")
    uint8_t  prng_tag;         // +14: PRNG high bits / sub-frame tag
    uint8_t  sub_sync;         // +15: Sub-frame sync tag
    uint8_t  payload[6];       // +16..+21: Trailing PRNG indices and sub-frame synchronization
};
#pragma pack(pop)

static_assert(sizeof(net_packet_t) == LF2_PACKET_SIZE, "net_packet_t must be exactly 22 bytes (0x16)");
static_assert(offsetof(net_packet_t, seq_counter) == 9, "seq_counter must be at offset 9");
static_assert(offsetof(net_packet_t, version_tag) == 11, "version_tag must be at offset 11");
static_assert(offsetof(net_packet_t, hp_checksum) == 13, "hp_checksum must be at offset 13");

// 77-byte Slot & Name Handshake Packet
#pragma pack(push, 1)
struct net_handshake_77_t {
    char slot_mask[8];       // +0..+7: "00001111" (Client slots 5-8) or "11110000" (Host slots 1-4)
    char padding_zeros[24];  // +8..+31: 24 bytes of zero padding ('0')
    char player_names[44];   // +32..+75: 4 * (10 bytes name + 1 byte '_')
    char null_terminator;    // +76: ending '\0'
};
#pragma pack(pop)

static_assert(sizeof(net_handshake_77_t) == LF2_HANDSHAKE_77_LEN, "net_handshake_77_t must be exactly 77 bytes");

// 3,001-byte PRNG Seed Packet
#pragma pack(push, 1)
struct net_prng_seed_packet_t {
    uint8_t tag;               // +0: 0x01
    uint8_t seed_table[3000];  // +1..+3000: 3,000-byte precomputed circular PRNG table
};
#pragma pack(pop)

static_assert(sizeof(net_prng_seed_packet_t) == LF2_PRNG_SEED_LEN, "net_prng_seed_packet_t must be exactly 3001 bytes");

// Network Synchronization Result Codes
enum class SyncResult {
    OK = 0,
    CONNECTION_LOST   = 1, // 0x004493B4: "Connection Lost!" (Offset +9 sequence mismatch)
    VERSION_MISMATCH  = 2, // 0x0044939C: "Version not matched!" (Offset +11 version mismatch)
    DESYNCHRONIZATION = 3  // 0x00449384: "Synchronisation Error!" (Offset +13 HP checksum mismatch)
};

// Network Session Mode
enum class NetMode {
    OFFLINE,
    HOST,
    CLIENT
};

class network_manager_t {
public:
    network_manager_t();
    ~network_manager_t();

    // Initialize socket subsystem (WinSock / BSD)
    static bool initialize_subsystem();
    static void shutdown_subsystem();

    // Connection management
    bool start_host(uint16_t port = LF2_DEFAULT_PORT);
    bool accept_connection();
    bool connect_to_host(const std::string& host_ip, uint16_t port = LF2_DEFAULT_PORT);
    void disconnect();

    // Handshake communication
    bool send_handshake_14();
    bool receive_handshake_14();
    bool send_slots_77(const net_handshake_77_t& packet);
    bool receive_slots_77(net_handshake_77_t& out_packet);
    bool send_prng_seed_3001(const uint8_t* table_3000);
    bool receive_prng_seed_3001(uint8_t* out_table_3000);

    // 22-byte lockstep transmission & reception (non-blocking)
    bool send_packet(const net_packet_t& packet);
    bool receive_packet(net_packet_t& out_packet);

    // 1:1 Lifted Helper Routines
    static uint8_t pack_input(const input_state_t& input);
    static void unpack_input(uint8_t packed, input_state_t& out_input);
    static uint8_t compute_hp_checksum(const object_t* const* objects, int count);

    // 1:1 Lifted Desync Verifier (0x0041CC27 - 0x0041CCD0)
    static SyncResult verify_sync(const net_packet_t& local_pkt, const net_packet_t& remote_pkt);

    // Get human-readable error string matching authentic LF2 modal dialogs
    static const char* get_sync_error_string(SyncResult result);

    // State queries
    NetMode get_mode() const { return m_mode; }
    bool is_connected() const { return m_connected; }
    uint16_t get_port() const { return m_port; }

private:
    NetMode m_mode = NetMode::OFFLINE;
    bool m_connected = false;
    uint16_t m_port = LF2_DEFAULT_PORT;
    intptr_t m_socket = -1;
    intptr_t m_listen_socket = -1;

    void set_non_blocking(intptr_t sock);
};

} // namespace lf2

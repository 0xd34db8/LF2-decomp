#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <array>
#include "gameplay/entity.h"

namespace lf2 {

// LF2 standard default network port
constexpr uint16_t LF2_DEFAULT_PORT = 12328;

// Handshake constants
constexpr std::string_view LF2_HANDSHAKE_MSG = "u can connect";
constexpr size_t LF2_HANDSHAKE_LEN = 14;

// 22-byte Lockstep Packet Size
constexpr size_t LF2_PACKET_SIZE = 22; // 0x16

// Input bitmask definitions (0x0041C9D4 - 0x0041CAAC)
enum NetInputBits : uint8_t {
    NET_KEY_UP      = 0x02,
    NET_KEY_RIGHT   = 0x04,
    NET_KEY_ATTACK  = 0x08,
    NET_KEY_JUMP    = 0x10,
    NET_KEY_DEFEND  = 0x20,
    NET_KEY_DOWN    = 0x40,
    NET_KEY_LEFT    = 0x80,
};

// 1:1 Binary Layout of the 22-byte Network Packet (0x0044D040 / 0x0044F198)
#pragma pack(push, 1)
struct net_packet_t {
    uint8_t  player_inputs[8]; // +0..+7: Packed inputs for player slots 0..7
    uint8_t  control_flags;    // +8: System control flags (F1 pause, F2 step)
    uint32_t frame_index;      // +9..+12: Frame tick counter
    uint8_t  sync_state[3];    // +13..+15: Sub-frame sync / protocol tags
    uint32_t prng_index;       // +16..+19: Circular 3,000-byte PRNG table index
    uint16_t hp_checksum;      // +20..+21: Cumulative active player HP checksum
};
#pragma pack(pop)

static_assert(sizeof(net_packet_t) == LF2_PACKET_SIZE, "net_packet_t must be exactly 22 bytes (0x16)");

// Network Synchronization Result Codes
enum class SyncResult {
    OK = 0,
    CONNECTION_LOST   = 1, // 0x004493B4: "Connection Lost!"
    VERSION_MISMATCH  = 2, // 0x0044939C: "Version not matched!"
    DESYNCHRONIZATION = 3  // 0x00449384: "Synchronisation Error!"
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

    // Packet transmission & reception (non-blocking)
    bool send_packet(const net_packet_t& packet);
    bool receive_packet(net_packet_t& out_packet);

    // 1:1 Lifted Helper Routines
    static uint8_t pack_input(const input_state_t& input);
    static void unpack_input(uint8_t packed, input_state_t& out_input);
    static uint16_t compute_hp_checksum(const object_t* const* objects, int count);

    // 1:1 Lifted Desync Verifier (0x0041CC27)
    static SyncResult verify_sync(const net_packet_t& local_pkt, const net_packet_t& remote_pkt);

    // Get human-readable error string matching LF2 dialogs
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

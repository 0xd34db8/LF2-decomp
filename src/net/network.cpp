#include "network.h"
#include <cstring>
#include <iostream>

#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
typedef int socklen_t;
#define CLOSE_SOCKET(s) closesocket(s)
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#define CLOSE_SOCKET(s) ::close(s)
#endif

namespace lf2 {

network_manager_t::network_manager_t() = default;

network_manager_t::~network_manager_t() {
    disconnect();
}

bool network_manager_t::initialize_subsystem() {
#if defined(_WIN32)
    WSADATA wsa_data;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    return (err == 0);
#else
    return true;
#endif
}

void network_manager_t::shutdown_subsystem() {
#if defined(_WIN32)
    WSACleanup();
#endif
}

void network_manager_t::set_non_blocking(intptr_t sock) {
#if defined(_WIN32)
    u_long mode = 1;
    ioctlsocket(static_cast<SOCKET>(sock), FIONBIO, &mode);
#else
    int flags = fcntl(static_cast<int>(sock), F_GETFL, 0);
    if (flags != -1) {
        fcntl(static_cast<int>(sock), F_SETFL, flags | O_NONBLOCK);
    }
#endif
}

bool network_manager_t::start_host(uint16_t port) {
    disconnect();

    initialize_subsystem();

    SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_sock == INVALID_SOCKET) {
        return false;
    }

    int opt = 1;
    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(listen_sock, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        CLOSE_SOCKET(listen_sock);
        return false;
    }

    if (listen(listen_sock, 1) == SOCKET_ERROR) {
        CLOSE_SOCKET(listen_sock);
        return false;
    }

    set_non_blocking(static_cast<intptr_t>(listen_sock));

    m_listen_socket = static_cast<intptr_t>(listen_sock);
    m_port = port;
    m_mode = NetMode::HOST;
    m_connected = false;

    return true;
}

bool network_manager_t::connect_to_host(const std::string& host_ip, uint16_t port) {
    disconnect();

    initialize_subsystem();

    SOCKET client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_sock == INVALID_SOCKET) {
        return false;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host_ip.c_str(), &server_addr.sin_addr) <= 0) {
        // Fallback to gethostbyname
        struct hostent* he = gethostbyname(host_ip.c_str());
        if (!he) {
            CLOSE_SOCKET(client_sock);
            return false;
        }
        memcpy(&server_addr.sin_addr, he->h_addr_list[0], he->h_length);
    }

    if (connect(client_sock, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        CLOSE_SOCKET(client_sock);
        return false;
    }

    // Set non-blocking for gameplay lockstep
    set_non_blocking(static_cast<intptr_t>(client_sock));

    m_socket = static_cast<intptr_t>(client_sock);
    m_port = port;
    m_mode = NetMode::CLIENT;
    m_connected = true;

    return true;
}

void network_manager_t::disconnect() {
    if (m_socket != -1) {
        CLOSE_SOCKET(static_cast<SOCKET>(m_socket));
        m_socket = -1;
    }
    if (m_listen_socket != -1) {
        CLOSE_SOCKET(static_cast<SOCKET>(m_listen_socket));
        m_listen_socket = -1;
    }
    m_connected = false;
    m_mode = NetMode::OFFLINE;
}

bool network_manager_t::send_packet(const net_packet_t& packet) {
    if (m_socket == -1) return false;

    int sent = send(static_cast<SOCKET>(m_socket),
                    reinterpret_cast<const char*>(&packet),
                    LF2_PACKET_SIZE, 0);

    return (sent == static_cast<int>(LF2_PACKET_SIZE));
}

bool network_manager_t::accept_connection() {
    if (m_listen_socket == -1) return false;

    sockaddr_in client_addr{};
    socklen_t addr_len = sizeof(client_addr);
    SOCKET accepted = accept(static_cast<SOCKET>(m_listen_socket),
                             (sockaddr*)&client_addr, &addr_len);
    if (accepted == INVALID_SOCKET) {
        return false;
    }

    set_non_blocking(static_cast<intptr_t>(accepted));
    m_socket = static_cast<intptr_t>(accepted);
    m_connected = true;
    return true;
}

bool network_manager_t::receive_packet(net_packet_t& out_packet) {
    if (m_mode == NetMode::HOST && !m_connected && m_listen_socket != -1) {
        if (!accept_connection()) {
            return false;
        }
    }

    if (m_socket == -1 || !m_connected) return false;

    int total_read = 0;
    char* buf = reinterpret_cast<char*>(&out_packet);

    int read_bytes = recv(static_cast<SOCKET>(m_socket), buf, LF2_PACKET_SIZE, 0);
    if (read_bytes <= 0) {
        return false;
    }
    total_read += read_bytes;

    // Accumulate full 22-byte packet
    while (total_read < static_cast<int>(LF2_PACKET_SIZE)) {
        int more = recv(static_cast<SOCKET>(m_socket), buf + total_read,
                        LF2_PACKET_SIZE - total_read, 0);
        if (more <= 0) break;
        total_read += more;
    }

    return (total_read == static_cast<int>(LF2_PACKET_SIZE));
}

uint8_t network_manager_t::pack_input(const input_state_t& input) {
    uint8_t packed = 0;
    if (input.up)     packed |= NET_KEY_UP;
    if (input.right)  packed |= NET_KEY_RIGHT;
    if (input.attack) packed |= NET_KEY_ATTACK;
    if (input.jump)   packed |= NET_KEY_JUMP;
    if (input.defend) packed |= NET_KEY_DEFEND;
    if (input.down)   packed |= NET_KEY_DOWN;
    if (input.left)   packed |= NET_KEY_LEFT;
    return packed;
}

void network_manager_t::unpack_input(uint8_t packed, input_state_t& out_input) {
    out_input.up     = (packed & NET_KEY_UP) != 0;
    out_input.right  = (packed & NET_KEY_RIGHT) != 0;
    out_input.attack = (packed & NET_KEY_ATTACK) != 0;
    out_input.jump   = (packed & NET_KEY_JUMP) != 0;
    out_input.defend = (packed & NET_KEY_DEFEND) != 0;
    out_input.down   = (packed & NET_KEY_DOWN) != 0;
    out_input.left   = (packed & NET_KEY_LEFT) != 0;
}

uint16_t network_manager_t::compute_hp_checksum(const object_t* const* objects, int count) {
    if (!objects || count <= 0) return 0;

    uint32_t hp_sum = 0;
    for (int i = 0; i < count && i < 8; ++i) {
        if (objects[i]) {
            hp_sum += static_cast<uint32_t>(objects[i]->hp);
        }
    }
    return static_cast<uint16_t>(hp_sum & 0xFFFF);
}

SyncResult network_manager_t::verify_sync(const net_packet_t& local_pkt, const net_packet_t& remote_pkt) {
    // 0x0041CC27: Frame sequence check
    if (local_pkt.frame_index != remote_pkt.frame_index) {
        return SyncResult::CONNECTION_LOST;
    }

    // 0x0041CC78: Version / Protocol tag check
    if (local_pkt.sync_state[0] != remote_pkt.sync_state[0]) {
        return SyncResult::VERSION_MISMATCH;
    }

    // 0x0041CCB5: Deterministic HP checksum check
    if (local_pkt.hp_checksum != remote_pkt.hp_checksum) {
        return SyncResult::DESYNCHRONIZATION;
    }

    return SyncResult::OK;
}

const char* network_manager_t::get_sync_error_string(SyncResult result) {
    switch (result) {
        case SyncResult::OK:
            return "OK";
        case SyncResult::CONNECTION_LOST:
            return "Connection Lost!";
        case SyncResult::VERSION_MISMATCH:
            return "Version not matched!";
        case SyncResult::DESYNCHRONIZATION:
            return "Synchronisation Error!";
        default:
            return "Unknown Error";
    }
}

} // namespace lf2

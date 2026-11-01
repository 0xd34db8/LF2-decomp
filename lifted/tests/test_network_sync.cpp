#include <iostream>
#include <cassert>
#include <cstring>
#include <thread>
#include <chrono>

#include "net/network.h"
#include "core/random.h"

using namespace lf2;

void test_packet_structure() {
    std::cout << "[+] Testing Network Packet Binary Layouts (0x0041CB50 - 0x0041CCD0)..." << std::endl;
    
    // 1. 22-byte gameplay lockstep packet
    static_assert(sizeof(net_packet_t) == 22, "net_packet_t size must be exactly 22 bytes!");
    static_assert(offsetof(net_packet_t, player_inputs) == 0);
    static_assert(offsetof(net_packet_t, control_flags) == 8);
    static_assert(offsetof(net_packet_t, seq_counter)   == 9);
    static_assert(offsetof(net_packet_t, version_tag)   == 11);
    static_assert(offsetof(net_packet_t, hp_checksum)   == 13);
    assert(sizeof(net_packet_t) == 22);

    // 2. 77-byte slot handshake packet
    static_assert(sizeof(net_handshake_77_t) == 77, "net_handshake_77_t size must be exactly 77 bytes!");
    static_assert(offsetof(net_handshake_77_t, slot_mask) == 0);
    static_assert(offsetof(net_handshake_77_t, padding_zeros) == 8);
    static_assert(offsetof(net_handshake_77_t, player_names) == 32);
    static_assert(offsetof(net_handshake_77_t, null_terminator) == 76);
    assert(sizeof(net_handshake_77_t) == 77);

    // 3. 3,001-byte PRNG seed exchange packet
    static_assert(sizeof(net_prng_seed_packet_t) == 3001, "net_prng_seed_packet_t size must be 3001 bytes!");
    static_assert(offsetof(net_prng_seed_packet_t, tag) == 0);
    static_assert(offsetof(net_prng_seed_packet_t, seed_table) == 1);
    assert(sizeof(net_prng_seed_packet_t) == 3001);

    std::cout << "    22-byte lockstep, 77-byte slot, and 3001-byte PRNG packet layouts verified 100%!" << std::endl;
}

void test_input_packing() {
    std::cout << "[+] Testing 1:1 Controller Input Bit Packing (0x0041C9C0 - 0x0041CAAC)..." << std::endl;

    input_state_t in{};
    in.up = true;
    in.right = true;
    in.attack = true;
    in.jump = false;
    in.defend = false;
    in.down = false;
    in.left = false;

    uint8_t packed = network_manager_t::pack_input(in);
    // Base Idle (0x01) | Up (0x02) | Right (0x04) | Attack (0x08) = 0x0F (15)
    // Matches mfc formula: 1 + 2^(1) + 2^(2) + 2^(3) = 15
    assert((packed & NET_KEY_IDLE) != 0);
    assert((packed & NET_KEY_UP) != 0);
    assert((packed & NET_KEY_RIGHT) != 0);
    assert((packed & NET_KEY_ATTACK) != 0);

    input_state_t unpacked{};
    network_manager_t::unpack_input(packed, unpacked);
    assert(unpacked.up == true);
    assert(unpacked.right == true);
    assert(unpacked.attack == true);
    assert(unpacked.jump == false);
    assert(unpacked.defend == false);
    assert(unpacked.down == false);
    assert(unpacked.left == false);

    // Test all flags active: 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 = 255 (0xFF)
    input_state_t all_keys{};
    all_keys.up = true;
    all_keys.down = true;
    all_keys.left = true;
    all_keys.right = true;
    all_keys.attack = true;
    all_keys.jump = true;
    all_keys.defend = true;

    uint8_t all_packed = network_manager_t::pack_input(all_keys);
    assert(all_packed == 255); // 0xFF exactly as documented in LFE forum

    input_state_t all_unpacked{};
    network_manager_t::unpack_input(all_packed, all_unpacked);
    assert(all_unpacked.up == true);
    assert(all_unpacked.down == true);
    assert(all_unpacked.left == true);
    assert(all_unpacked.right == true);
    assert(all_unpacked.attack == true);
    assert(all_unpacked.jump == true);
    assert(all_unpacked.defend == true);

    std::cout << "    Input bit packing & unpacking round-trip verified 100% (All keys = 255)!" << std::endl;
}

void test_checksum_and_sync() {
    std::cout << "[+] Testing HP Checksumming & Desynchronization Verifier (0x0041CC27 - 0x0041CCD0)..." << std::endl;

    // Mock 4 objects
    object_t obj0{}, obj1{}, obj2{}, obj3{};
    obj0.hp = 500;
    obj1.hp = 350;
    obj2.hp = 480;
    obj3.hp = 200;

    const object_t* objects[4] = { &obj0, &obj1, &obj2, &obj3 };
    uint8_t checksum = network_manager_t::compute_hp_checksum(objects, 4);
    assert(checksum == static_cast<uint8_t>((500 + 350 + 480 + 200) & 0xFF));

    // Construct local packet matching authentic binary fields
    net_packet_t local_pkt{};
    local_pkt.seq_counter = 12; // Modulo 50 counter
    local_pkt.version_tag = 0x01; // Version tag
    local_pkt.hp_checksum = checksum;

    // Test OK condition
    net_packet_t remote_pkt = local_pkt;
    assert(network_manager_t::verify_sync(local_pkt, remote_pkt) == SyncResult::OK);

    // Test Sequence mismatch at Offset +9 -> Connection Lost! (0x0041CC27)
    remote_pkt.seq_counter = 11;
    assert(network_manager_t::verify_sync(local_pkt, remote_pkt) == SyncResult::CONNECTION_LOST);
    assert(std::strcmp(network_manager_t::get_sync_error_string(SyncResult::CONNECTION_LOST), "Connection Lost!") == 0);

    // Test Version mismatch at Offset +11 -> Version not matched! (0x0041CC78)
    remote_pkt = local_pkt;
    remote_pkt.version_tag = 0x02;
    assert(network_manager_t::verify_sync(local_pkt, remote_pkt) == SyncResult::VERSION_MISMATCH);
    assert(std::strcmp(network_manager_t::get_sync_error_string(SyncResult::VERSION_MISMATCH), "Version not matched!") == 0);

    // Test HP divergence at Offset +13 -> Synchronisation Error! (0x0041CCB5)
    remote_pkt = local_pkt;
    remote_pkt.hp_checksum = static_cast<uint8_t>(checksum - 5);
    assert(network_manager_t::verify_sync(local_pkt, remote_pkt) == SyncResult::DESYNCHRONIZATION);
    assert(std::strcmp(network_manager_t::get_sync_error_string(SyncResult::DESYNCHRONIZATION), "Synchronisation Error!") == 0);

    std::cout << "    Desync verifier matched all 3 authentic LF2 error dialog states!" << std::endl;
}

void test_live_loopback_lockstep() {
    std::cout << "[+] Testing Live Handshake & 22-Byte Lockstep Transmission..." << std::endl;

    constexpr uint16_t test_port = 12349;
    network_manager_t host;
    network_manager_t client;

    bool host_ok = host.start_host(test_port);
    assert(host_ok);
    assert(host.get_mode() == NetMode::HOST);

    // Connect client to 127.0.0.1
    bool client_ok = client.connect_to_host("127.0.0.1", test_port);
    assert(client_ok);
    assert(client.get_mode() == NetMode::CLIENT);

    // Host accepts incoming client connection
    bool accepted = host.accept_connection();
    assert(accepted);
    assert(host.is_connected());

    // 1. Handshake Phase 1: Host sends 14-byte "u can connect\0"
    assert(host.send_handshake_14());
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    assert(client.receive_handshake_14());

    // 2. Handshake Phase 2: Slot & Name Negotiation (77 bytes)
    net_handshake_77_t client_slots{};
    std::memcpy(client_slots.slot_mask, "00001111", 8);
    std::memset(client_slots.padding_zeros, '0', 24);
    std::snprintf(client_slots.player_names, 44, "Player---1_Player---2_Player---3_Player---4_");
    client_slots.null_terminator = '\0';

    assert(client.send_slots_77(client_slots));
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    net_handshake_77_t host_recv_slots{};
    assert(host.receive_slots_77(host_recv_slots));
    assert(std::memcmp(host_recv_slots.slot_mask, "00001111", 8) == 0);

    // 3. Handshake Phase 3: 3,001-byte PRNG Seed Table
    uint8_t prng_mock[3000];
    for (int i = 0; i < 3000; ++i) prng_mock[i] = static_cast<uint8_t>(i & 0xFF);
    assert(host.send_prng_seed_3001(prng_mock));
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    uint8_t client_recv_prng[3000];
    assert(client.receive_prng_seed_3001(client_recv_prng));
    assert(std::memcmp(prng_mock, client_recv_prng, 3000) == 0);

    // 4. Gameplay Loop: 22-byte lockstep frame packets
    net_packet_t send_pkt{};
    send_pkt.player_inputs[0] = NET_KEY_IDLE | NET_KEY_ATTACK | NET_KEY_RIGHT;
    send_pkt.player_inputs[1] = NET_KEY_IDLE | NET_KEY_DEFEND;
    send_pkt.control_flags = 0;
    send_pkt.seq_counter = 1;
    send_pkt.version_tag = 0x01;
    send_pkt.hp_checksum = 120;

    assert(client.send_packet(send_pkt));
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    net_packet_t recv_pkt{};
    assert(host.receive_packet(recv_pkt));

    assert(recv_pkt.player_inputs[0] == send_pkt.player_inputs[0]);
    assert(recv_pkt.player_inputs[1] == send_pkt.player_inputs[1]);
    assert(recv_pkt.seq_counter == send_pkt.seq_counter);
    assert(recv_pkt.version_tag == send_pkt.version_tag);
    assert(recv_pkt.hp_checksum == send_pkt.hp_checksum);

    host.disconnect();
    client.disconnect();

    std::cout << "    Full 14-byte, 77-byte, 3001-byte handshake and 22-byte lockstep loop verified 100%!" << std::endl;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    std::cout << "=== Little Fighter 2 Lockstep Network & Synchronization Tests ===" << std::endl;

    test_packet_structure();
    test_input_packing();
    test_checksum_and_sync();
    test_live_loopback_lockstep();

    std::cout << "[SUCCESS] All Network Sync & Lockstep Protocol tests passed with 100% precision!" << std::endl;
    return 0;
}

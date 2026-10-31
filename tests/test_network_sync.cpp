#include <iostream>
#include <cassert>
#include <cstring>
#include <thread>
#include <chrono>

#include "net/network.h"
#include "core/random.h"

using namespace lf2;

void test_packet_structure() {
    std::cout << "[+] Testing 22-Byte Lockstep Packet Layout (0x0044D040 / 0x0044F198)..." << std::endl;
    static_assert(sizeof(net_packet_t) == 22, "net_packet_t size must be exactly 22 bytes!");
    assert(sizeof(net_packet_t) == 22);

    net_packet_t pkt{};
    assert(sizeof(pkt.player_inputs) == 8);
    assert(sizeof(pkt.control_flags) == 1);
    assert(sizeof(pkt.frame_index) == 4);
    assert(sizeof(pkt.sync_state) == 3);
    assert(sizeof(pkt.prng_index) == 4);
    assert(sizeof(pkt.hp_checksum) == 2);

    std::cout << "    net_packet_t 22-byte binary layout verified!" << std::endl;
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
    // Up (0x02) | Right (0x04) | Attack (0x08) = 0x0E
    assert(packed == (NET_KEY_UP | NET_KEY_RIGHT | NET_KEY_ATTACK));

    input_state_t unpacked{};
    network_manager_t::unpack_input(packed, unpacked);
    assert(unpacked.up == true);
    assert(unpacked.right == true);
    assert(unpacked.attack == true);
    assert(unpacked.jump == false);
    assert(unpacked.defend == false);
    assert(unpacked.down == false);
    assert(unpacked.left == false);

    // Test all flags active
    input_state_t all_keys{};
    all_keys.up = true;
    all_keys.down = true;
    all_keys.left = true;
    all_keys.right = true;
    all_keys.attack = true;
    all_keys.jump = true;
    all_keys.defend = true;

    uint8_t all_packed = network_manager_t::pack_input(all_keys);
    assert((all_packed & NET_KEY_UP) != 0);
    assert((all_packed & NET_KEY_DOWN) != 0);
    assert((all_packed & NET_KEY_LEFT) != 0);
    assert((all_packed & NET_KEY_RIGHT) != 0);
    assert((all_packed & NET_KEY_ATTACK) != 0);
    assert((all_packed & NET_KEY_JUMP) != 0);
    assert((all_packed & NET_KEY_DEFEND) != 0);

    input_state_t all_unpacked{};
    network_manager_t::unpack_input(all_packed, all_unpacked);
    assert(all_unpacked.up == true);
    assert(all_unpacked.down == true);
    assert(all_unpacked.left == true);
    assert(all_unpacked.right == true);
    assert(all_unpacked.attack == true);
    assert(all_unpacked.jump == true);
    assert(all_unpacked.defend == true);

    std::cout << "    Input bit packing & unpacking round-trip verified 100%!" << std::endl;
}

void test_checksum_and_sync() {
    std::cout << "[+] Testing HP Checksumming & Desynchronization Verifier (0x0041CC27)..." << std::endl;

    // Mock 4 objects
    object_t obj0{}, obj1{}, obj2{}, obj3{};
    obj0.hp = 500;
    obj1.hp = 350;
    obj2.hp = 480;
    obj3.hp = 200;

    const object_t* objects[4] = { &obj0, &obj1, &obj2, &obj3 };
    uint16_t checksum = network_manager_t::compute_hp_checksum(objects, 4);
    assert(checksum == (500 + 350 + 480 + 200));

    // Construct local packet
    net_packet_t local_pkt{};
    local_pkt.frame_index = 120;
    local_pkt.sync_state[0] = 0x4C; // 'L'
    local_pkt.prng_index = 542;
    local_pkt.hp_checksum = checksum;

    // Test OK condition
    net_packet_t remote_pkt = local_pkt;
    assert(network_manager_t::verify_sync(local_pkt, remote_pkt) == SyncResult::OK);

    // Test Frame desync -> Connection Lost!
    remote_pkt.frame_index = 119;
    assert(network_manager_t::verify_sync(local_pkt, remote_pkt) == SyncResult::CONNECTION_LOST);
    assert(std::strcmp(network_manager_t::get_sync_error_string(SyncResult::CONNECTION_LOST), "Connection Lost!") == 0);

    // Test Version mismatch -> Version not matched!
    remote_pkt = local_pkt;
    remote_pkt.sync_state[0] = 0x58;
    assert(network_manager_t::verify_sync(local_pkt, remote_pkt) == SyncResult::VERSION_MISMATCH);
    assert(std::strcmp(network_manager_t::get_sync_error_string(SyncResult::VERSION_MISMATCH), "Version not matched!") == 0);

    // Test HP divergence -> Synchronisation Error!
    remote_pkt = local_pkt;
    remote_pkt.hp_checksum = checksum - 15; // 15 HP desync
    assert(network_manager_t::verify_sync(local_pkt, remote_pkt) == SyncResult::DESYNCHRONIZATION);
    assert(std::strcmp(network_manager_t::get_sync_error_string(SyncResult::DESYNCHRONIZATION), "Synchronisation Error!") == 0);

    std::cout << "    Desync verifier matched all 3 authentic LF2 error dialog states!" << std::endl;
}

void test_live_loopback_lockstep() {
    std::cout << "[+] Testing Live Local Loopback 22-Byte Lockstep Transmission..." << std::endl;

    constexpr uint16_t test_port = 12348;
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

    // Prepare packet from client
    net_packet_t send_pkt{};
    send_pkt.player_inputs[0] = NET_KEY_ATTACK | NET_KEY_RIGHT;
    send_pkt.player_inputs[1] = NET_KEY_DEFEND;
    send_pkt.control_flags = 0;
    send_pkt.frame_index = 1;
    send_pkt.sync_state[0] = 0x4C;
    send_pkt.prng_index = 100;
    send_pkt.hp_checksum = 1000;

    // Small delay for socket handshake
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Client sends packet
    bool sent = client.send_packet(send_pkt);
    assert(sent);

    // Host receives packet (accepts connection on first receive call)
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    net_packet_t recv_pkt{};
    bool received = host.receive_packet(recv_pkt);
    assert(received);

    // Verify packet payload integrity
    assert(recv_pkt.player_inputs[0] == send_pkt.player_inputs[0]);
    assert(recv_pkt.player_inputs[1] == send_pkt.player_inputs[1]);
    assert(recv_pkt.frame_index == send_pkt.frame_index);
    assert(recv_pkt.prng_index == send_pkt.prng_index);
    assert(recv_pkt.hp_checksum == send_pkt.hp_checksum);

    // Host sends response packet
    recv_pkt.frame_index = 2;
    recv_pkt.prng_index = 101;
    assert(host.send_packet(recv_pkt));

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    net_packet_t client_recv{};
    assert(client.receive_packet(client_recv));
    assert(client_recv.frame_index == 2);
    assert(client_recv.prng_index == 101);

    host.disconnect();
    client.disconnect();

    std::cout << "    Live 22-byte lockstep round-trip transmission verified 100%!" << std::endl;
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

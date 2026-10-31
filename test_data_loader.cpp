#include <iostream>
#include <cassert>
#include <cstring>
#include "cipher.h"
#include "data_txt.h"
#include "dat_loader.h"

int main() {
    std::cout << "=== Little Fighter 2 Data-Driven Core Verification ===" << std::endl;

    // -------------------------------------------------------------
    // Test 1: Cipher In-Memory Round-Trip
    // -------------------------------------------------------------
    std::cout << "[+] Testing Cipher Encryption & Decryption Round-Trip..." << std::endl;
    const std::string original_text = "LF2_TEST_PAYLOAD: <frame> 0 standing\n   pic: 0  state: 0  wait: 5\n<frame_end>\n";
    std::vector<uint8_t> encrypted = lf2::cipher_t::encrypt(original_text);
    assert(encrypted.size() == lf2::CIPHER_HEADER_SIZE + original_text.size());

    std::string decrypted = lf2::cipher_t::decrypt(encrypted);
    assert(decrypted == original_text);
    std::cout << "    Round-trip successfully restored exact plaintext!" << std::endl;

    // -------------------------------------------------------------
    // Test 2: Decrypt Authentic .legacy/data/template.dat
    // -------------------------------------------------------------
    std::cout << "[+] Testing Decryption of Authentic .legacy/data/template.dat..." << std::endl;
    std::string template_text;
    bool dec_ok = lf2::cipher_t::decrypt_file(".legacy/data/template.dat", template_text);
    assert(dec_ok && !template_text.empty());
    assert(template_text.find("<bmp_begin>") != std::string::npos);
    assert(template_text.find("name: Template") != std::string::npos);
    assert(template_text.find("<bmp_end>") != std::string::npos);
    std::cout << "    template.dat decrypted successfully (" << template_text.size() << " bytes)!" << std::endl;

    // -------------------------------------------------------------
    // Test 3: Parse Authentic .legacy/data/data.txt
    // -------------------------------------------------------------
    std::cout << "[+] Testing Parser for Authentic .legacy/data/data.txt..." << std::endl;
    lf2::data_txt_t data_manifest;
    bool manifest_ok = data_manifest.load_from_file(".legacy/data/data.txt");
    assert(manifest_ok);
    assert(!data_manifest.get_objects().empty());
    assert(!data_manifest.get_backgrounds().empty());

    // Davis (ID 11)
    const lf2::object_entry_t* davis_entry = data_manifest.find_object(11);
    assert(davis_entry != nullptr);
    assert(davis_entry->type == 0);
    assert(davis_entry->file == "data\\davis.dat");

    // Julian (ID 52)
    const lf2::object_entry_t* julian_entry = data_manifest.find_object(52);
    assert(julian_entry != nullptr);
    assert(julian_entry->type == 0);
    assert(julian_entry->file == "data\\julian.dat");

    // Stick weapon (ID 100)
    const lf2::object_entry_t* stick_entry = data_manifest.find_object(100);
    assert(stick_entry != nullptr);
    assert(stick_entry->type == 1);
    assert(stick_entry->file == "data\\weapon0.dat");

    std::cout << "    data.txt loaded " << data_manifest.get_objects().size() << " objects and " 
              << data_manifest.get_backgrounds().size() << " backgrounds." << std::endl;

    // -------------------------------------------------------------
    // Test 4: Full Parse of Authentic .legacy/data/davis.dat into file_t
    // -------------------------------------------------------------
    std::cout << "[+] Testing Full .dat Parser on .legacy/data/davis.dat..." << std::endl;
    lf2::file_t* davis_file = new lf2::file_t();
    bool load_ok = lf2::dat_loader_t::load_file(davis_file, ".legacy/data/davis.dat", 11, 0);
    assert(load_ok);

    // Verify header metadata
    assert(std::string(davis_file->name) == "Davis");
    assert(std::string(davis_file->head) == "sprite\\sys\\davis_f.bmp");
    assert(std::string(davis_file->small) == "sprite\\sys\\davis_s.bmp");
    assert(davis_file->walking_frame_rate == 3);
    assert(davis_file->walking_speed == 5.0);
    assert(davis_file->walking_speedz == 2.5);
    assert(davis_file->running_speed == 10.0);
    assert(davis_file->jump_height == -16.299999);

    // Verify Sprite Sheet metadata
    assert(davis_file->bmp_count == 3);
    assert(std::string(davis_file->bmp_paths[0]) == "sprite\\sys\\davis_0.bmp");
    assert(davis_file->sheet_start[0] == 0 && davis_file->sheet_w[0] == 79 && davis_file->sheet_h[0] == 79);
    assert(davis_file->sheet_row[0] == 10 && davis_file->sheet_col[0] == 7);
    assert(std::string(davis_file->bmp_paths[1]) == "sprite\\sys\\davis_1.bmp");
    assert(davis_file->sheet_start[1] == 70);
    assert(std::string(davis_file->bmp_paths[2]) == "sprite\\sys\\davis_2.bmp");
    assert(davis_file->sheet_start[2] == 140);

    // Verify Frame 0 (Standing)
    const lf2::frame_t& f0 = davis_file->frames[0];
    assert(f0.present == 1);
    assert(f0.pic == 0);
    assert(f0.state == 0);
    assert(f0.wait == 5);
    assert(f0.next == 1);
    assert(f0.centerx == 39);
    assert(f0.centery == 79);
    assert(f0.bpoint.x == 39 && f0.bpoint.y == 34);
    assert(f0.wpoint.kind == 1 && f0.wpoint.x == 23 && f0.wpoint.y == 55);
    assert(f0.bdys_size == 1);
    assert(f0.bdys != nullptr);
    assert(f0.bdys[0].x == 21 && f0.bdys[0].y == 18 && f0.bdys[0].w == 43 && f0.bdys[0].h == 62);

    // Verify Frame 5 (Walking with catch itr)
    const lf2::frame_t& f5 = davis_file->frames[5];
    assert(f5.present == 1);
    assert(f5.pic == 4);
    assert(f5.state == 1);
    assert(f5.wait == 3);
    assert(f5.next == 999);
    assert(f5.itrs_size == 1);
    assert(f5.itrs != nullptr);
    assert(f5.itrs[0].kind == 1); // itr_catch
    assert(f5.itrs[0].x == 40 && f5.itrs[0].y == 16 && f5.itrs[0].w == 25 && f5.itrs[0].h == 65);
    assert(f5.itrs[0].catching_act_1 == 120);
    assert(f5.itrs[0].caught_act_1 == 130);

    std::cout << "    davis.dat parsed successfully:" << std::endl;
    std::cout << "      Name: " << davis_file->name << std::endl;
    std::cout << "      Head: " << davis_file->head << std::endl;
    std::cout << "      Walking speed: " << davis_file->walking_speed << std::endl;
    std::cout << "      Frame 0: pic=" << f0.pic << ", bdy=(" << f0.bdys[0].w << "x" << f0.bdys[0].h << ")" << std::endl;
    std::cout << "      Frame 5: pic=" << f5.pic << ", catch itr=(" << f5.itrs[0].w << "x" << f5.itrs[0].h << ")" << std::endl;

    // -------------------------------------------------------------
    // Test 5: Serialization & Re-Parsing Verification
    // -------------------------------------------------------------
    std::cout << "[+] Testing Serialization to String & Re-parsing..." << std::endl;
    std::string serialized = lf2::dat_loader_t::serialize_to_string(davis_file);
    assert(!serialized.empty());

    lf2::file_t* reloaded_file = new lf2::file_t();
    bool reparse_ok = lf2::dat_loader_t::parse_content(reloaded_file, serialized, 11, 0);
    assert(reparse_ok);
    assert(std::string(reloaded_file->name) == "Davis");
    assert(reloaded_file->frames[0].bdys_size == 1);
    assert(reloaded_file->frames[0].bdys[0].w == 43);
    assert(reloaded_file->frames[5].itrs[0].kind == 1);

    lf2::dat_loader_t::free_file_resources(davis_file);
    delete davis_file;
    lf2::dat_loader_t::free_file_resources(reloaded_file);
    delete reloaded_file;

    std::cout << "[SUCCESS] All Data-Driven Core tests passed with 100% precision!" << std::endl;
    return 0;
}


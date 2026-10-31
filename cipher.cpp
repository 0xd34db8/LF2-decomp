#include "cipher.h"
#include <fstream>
#include <iostream>

namespace lf2 {

std::string cipher_t::decrypt(const uint8_t* data, size_t size) {
    if (!data || size <= CIPHER_HEADER_SIZE) {
        return {};
    }

    const size_t key_len = CIPHER_KEY.size();
    // In lf2.exe (0x004148a0 / 0x00414a30):
    // The key index starts at 0 and advances for every byte of the 123-byte header
    size_t key_idx = CIPHER_HEADER_SIZE % key_len; // 123 % 37 = 12

    const size_t payload_len = size - CIPHER_HEADER_SIZE;
    std::string result;
    result.resize(payload_len);

    const uint8_t* payload = data + CIPHER_HEADER_SIZE;
    for (size_t i = 0; i < payload_len; ++i) {
        int ch = static_cast<int>(payload[i]) - static_cast<int>(CIPHER_KEY[key_idx]);
        if (ch < 0) {
            ch += 256;
        }
        result[i] = static_cast<char>(ch);
        key_idx = (key_idx + 1) % key_len;
    }

    return result;
}

std::string cipher_t::decrypt(const std::vector<uint8_t>& data) {
    return decrypt(data.data(), data.size());
}

std::vector<uint8_t> cipher_t::encrypt(const std::string_view plaintext) {
    const size_t key_len = CIPHER_KEY.size();
    std::vector<uint8_t> result;
    result.reserve(CIPHER_HEADER_SIZE + plaintext.size());

    // Write authentic 123-byte header (spaces/padding)
    for (size_t i = 0; i < CIPHER_HEADER_SIZE; ++i) {
        result.push_back(static_cast<uint8_t>(' '));
    }

    size_t key_idx = CIPHER_HEADER_SIZE % key_len;
    for (char c : plaintext) {
        int enc = (static_cast<uint8_t>(c) + static_cast<uint8_t>(CIPHER_KEY[key_idx])) % 256;
        result.push_back(static_cast<uint8_t>(enc));
        key_idx = (key_idx + 1) % key_len;
    }

    return result;
}

bool cipher_t::decrypt_file(const std::string& dat_path, std::string& out_plaintext) {
    std::ifstream file(dat_path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    file.seekg(0, std::ios::end);
    size_t size = static_cast<size_t>(file.tellg());
    file.seekg(0, std::ios::beg);

    if (size <= CIPHER_HEADER_SIZE) {
        return false;
    }

    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        return false;
    }

    out_plaintext = decrypt(buffer);
    return true;
}

bool cipher_t::decrypt_file_to_file(const std::string& dat_path, const std::string& out_txt_path) {
    std::string plaintext;
    if (!decrypt_file(dat_path, plaintext)) {
        return false;
    }

    std::ofstream out(out_txt_path, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }

    out.write(plaintext.data(), plaintext.size());
    return true;
}

bool cipher_t::encrypt_file_to_dat(const std::string& txt_path, const std::string& out_dat_path) {
    std::ifstream in(txt_path, std::ios::binary);
    if (!in.is_open()) {
        return false;
    }

    in.seekg(0, std::ios::end);
    size_t size = static_cast<size_t>(in.tellg());
    in.seekg(0, std::ios::beg);

    std::string plaintext;
    plaintext.resize(size);
    if (!in.read(&plaintext[0], size)) {
        return false;
    }

    std::vector<uint8_t> encrypted = encrypt(plaintext);

    std::ofstream out(out_dat_path, std::ios::binary);
    if (!out.is_open()) {
        return false;
    }

    out.write(reinterpret_cast<const char*>(encrypted.data()), encrypted.size());
    return true;
}

} // namespace lf2


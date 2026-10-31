#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <string_view>

namespace lf2 {

// The authentic LF2 XOR/additive cipher key from 0x0044892c in lf2.exe
inline constexpr std::string_view CIPHER_KEY = "SiuHungIsAGoodBearBecauseHeIsVeryGood";
inline constexpr size_t CIPHER_HEADER_SIZE = 123; // 0x7B header bytes in .dat files

class cipher_t {
public:
    // In-memory decryption of raw .dat buffer into plaintext string/bytes
    static std::string decrypt(const uint8_t* data, size_t size);
    static std::string decrypt(const std::vector<uint8_t>& data);

    // In-memory encryption of plaintext string into .dat binary format (with authentic 123-byte header)
    static std::vector<uint8_t> encrypt(const std::string_view plaintext);

    // File-based decryption and encryption operations
    static bool decrypt_file(const std::string& dat_path, std::string& out_plaintext);
    static bool decrypt_file_to_file(const std::string& dat_path, const std::string& out_txt_path);
    static bool encrypt_file_to_dat(const std::string& txt_path, const std::string& out_dat_path);
};

} // namespace lf2


#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include "file.h"

namespace lf2 {

class dat_loader_t {
public:
    // Load a .dat or .txt file directly into an authentic file_t structure
    static bool load_file(file_t* file, const std::string& path, uint32_t id = 0, uint32_t type = 0);

    // Parse from decrypted in-memory plaintext string
    static bool parse_content(file_t* file, const std::string& content, uint32_t id = 0, uint32_t type = 0);

    // Save a file_t structure to an authentic plaintext LF2 format string
    static std::string serialize_to_string(const file_t* file);

    // Save to an authentic plaintext .txt or encrypted .dat file
    static bool save_file(const file_t* file, const std::string& path, bool encrypt = false);

    // Cleanup dynamically allocated frame itrs and bdys
    static void free_file_resources(file_t* file);

private:
    static void init_file(file_t* file, uint32_t id, uint32_t type);
};

} // namespace lf2


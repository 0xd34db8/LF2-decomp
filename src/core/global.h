#pragma once

#include <cstdint>
#include <cstddef>
#include "constants.h"
#include "types.h"
#include "object.h"
#include "file.h"

namespace lf2 {

#pragma pack(push, 4)

// Global game manager state (static address in original binary: 0x458B00)
// On 32-bit: Total Size: 0x8D8 (2,264 bytes)
struct global_t {
    uint32_t    game_state;                      // 0x000
    uint8_t     is_object_exists[MAX_OBJECTS];  // 0x004 - 0x194 (400 bytes)
    object_t*   objects[MAX_OBJECTS];           // 0x194 (400 pointers)
    file_t*     files[MAX_FILES];               // (65 pointers)

    // Lifted game logic methods
    void teleport(uint32_t teleported_id, uint32_t teleport_to);
    void does_attack_success(uint32_t attacker_id, uint32_t injured_id, uint32_t mode);
    void attack_process(uint32_t attacker_id);
    void process_all_attacks();
    int32_t spawn_projectile(uint32_t owner_id, uint32_t file_id, int32_t x, int32_t y, int32_t z, double dvx, double dvy, uint8_t facing);
};

#pragma pack(pop)

static_assert(offsetof(global_t, is_object_exists) == 0x004, "global_t::is_object_exists offset mismatch");
static_assert(offsetof(global_t, objects) == 0x194, "global_t::objects offset mismatch");

#if INTPTR_MAX == INT32_MAX
static_assert(sizeof(global_t) == 0x8D8, "global_t size must be 0x8D8 (2264 bytes) on 32-bit");
static_assert(offsetof(global_t, files) == 0x7D4, "global_t::files offset mismatch");
#endif

} // namespace lf2

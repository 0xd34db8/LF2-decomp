#pragma once

#include <cstdint>
#include <cstddef>

namespace lf2 {

#pragma pack(push, 4)
// Body collision box (bdy: receives attacks and defines physical boundary)
// Total Size: 0x28 (40 bytes)
struct bdy_t {
    uint32_t kind;       // 0x00
    int32_t  x;          // 0x04
    int32_t  y;          // 0x08
    int32_t  w;          // 0x0C
    int32_t  h;          // 0x10
    uint32_t _unknown1;  // 0x14
    uint32_t _unknown2;  // 0x18
    uint32_t _unknown3;  // 0x1C
    uint32_t _unknown4;  // 0x20
    uint32_t _unknown5;  // 0x24
};
#pragma pack(pop)

static_assert(sizeof(bdy_t) == 0x28, "bdy_t size must be 0x28 (40 bytes)");
static_assert(offsetof(bdy_t, kind) == 0x00, "bdy_t::kind offset mismatch");
static_assert(offsetof(bdy_t, x) == 0x04, "bdy_t::x offset mismatch");
static_assert(offsetof(bdy_t, y) == 0x08, "bdy_t::y offset mismatch");
static_assert(offsetof(bdy_t, w) == 0x0C, "bdy_t::w offset mismatch");
static_assert(offsetof(bdy_t, h) == 0x10, "bdy_t::h offset mismatch");

} // namespace lf2


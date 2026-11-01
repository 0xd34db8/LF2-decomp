#pragma once

#include <cstdint>
#include <cstddef>

namespace lf2 {

#pragma pack(push, 4)
// Interaction / Hitbox (itr: deals damage, catches, picks up items)
// Total Size: 0x50 (80 bytes)
struct itr_t {
    uint32_t kind;           // 0x00
    int32_t  x;              // 0x04
    int32_t  y;              // 0x08
    int32_t  w;              // 0x0C
    int32_t  h;              // 0x10
    int32_t  dvx;            // 0x14
    int32_t  dvy;            // 0x18
    uint32_t fall;           // 0x1C
    uint32_t arest;          // 0x20
    uint32_t vrest;          // 0x24
    uint32_t respond;        // 0x28
    uint32_t effect;         // 0x2C
    uint32_t catching_act_1; // 0x30
    uint32_t catching_act_2; // 0x34
    uint32_t caught_act_1;   // 0x38
    uint32_t caught_act_2;   // 0x3C
    uint32_t bdefend;        // 0x40
    int32_t  injury;         // 0x44
    uint32_t zwidth;         // 0x48
    uint32_t _unknown4C;     // 0x4C
};
#pragma pack(pop)

static_assert(sizeof(itr_t) == 0x50, "itr_t size must be 0x50 (80 bytes)");
static_assert(offsetof(itr_t, kind) == 0x00, "itr_t::kind offset mismatch");
static_assert(offsetof(itr_t, x) == 0x04, "itr_t::x offset mismatch");
static_assert(offsetof(itr_t, y) == 0x08, "itr_t::y offset mismatch");
static_assert(offsetof(itr_t, w) == 0x0C, "itr_t::w offset mismatch");
static_assert(offsetof(itr_t, h) == 0x10, "itr_t::h offset mismatch");
static_assert(offsetof(itr_t, dvx) == 0x14, "itr_t::dvx offset mismatch");
static_assert(offsetof(itr_t, dvy) == 0x18, "itr_t::dvy offset mismatch");
static_assert(offsetof(itr_t, fall) == 0x1C, "itr_t::fall offset mismatch");
static_assert(offsetof(itr_t, arest) == 0x20, "itr_t::arest offset mismatch");
static_assert(offsetof(itr_t, vrest) == 0x24, "itr_t::vrest offset mismatch");
static_assert(offsetof(itr_t, respond) == 0x28, "itr_t::respond offset mismatch");
static_assert(offsetof(itr_t, effect) == 0x2C, "itr_t::effect offset mismatch");
static_assert(offsetof(itr_t, catching_act_1) == 0x30, "itr_t::catching_act_1 offset mismatch");
static_assert(offsetof(itr_t, bdefend) == 0x40, "itr_t::bdefend offset mismatch");
static_assert(offsetof(itr_t, injury) == 0x44, "itr_t::injury offset mismatch");
static_assert(offsetof(itr_t, zwidth) == 0x48, "itr_t::zwidth offset mismatch");

} // namespace lf2


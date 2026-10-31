#pragma once

#include <cstdint>
#include <cstddef>

namespace lf2 {

// Native pointer wrapper / alias for LF2 source lifting.
// Native pointers allow compiling cleanly on both 32-bit and 64-bit architectures
// without truncating memory addresses or risking segfaults.
template <typename T>
using ptr_t = T*;

} // namespace lf2

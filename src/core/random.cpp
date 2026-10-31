#include "random.h"
#include "random_table.h"

namespace lf2 {

// LF2 static random state (original static addresses 0x450C34 and 0x450BCC)
static uint32_t s_random_i = 0;
static uint32_t s_random_j = 0;

int lf2_random([[maybe_unused]] uint32_t unused, int range) {
    if (range < 1) {
        return 0;
    }
    s_random_i = (s_random_i + 1) % 1234;
    s_random_j = (s_random_j + 1) % 3000;
    return static_cast<int>((static_cast<uint32_t>(RANDOM_TABLE[s_random_j]) + s_random_i) % static_cast<uint32_t>(range));
}

} // namespace lf2


#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <string.h>

/*
 * Virtual Address: 0x0040BD90
 * Function: load_dat_sound_slot (FUN_0040bd90)
 * Class / Subsystem: Data / Sound Slot Cache Loader
 *
 * Description:
 *   Looks up sound_path in the 20-byte-stride path cache DAT_00455638[0..DAT_00458438-1].
 *   On hit, writes the cached index to *out_slot. When *out_slot remains -1, assigns
 *   DAT_00458438, loads the WAV buffer via FUN_004014e0 and attenuates it (-10000) when
 *   DirectSound (DAT_0044eecc) is active, caches the path in DAT_00455638, and
 *   increments DAT_00458438.
 */

// FUNCTION: LF2 0x0040bd90
void FUN_0040bd90(const char *sound_path, int *out_slot)
{
    if (!sound_path || !out_slot) {
        return;
    }

    int idx = 0;
    if (DAT_00458438 > 0) {
        const char *entry = DAT_00455638;
        do {
            if (strcmp(sound_path, entry) == 0) {
                *out_slot = idx;
                break;
            }
            idx++;
            entry += 0x14;
        } while (idx < DAT_00458438);
    }

    if (*out_slot == -1) {
        *out_slot = DAT_00458438;
        if (DAT_0044eecc != 0) {
            FUN_004014e0(sound_path);
#ifdef _WIN32
            if (DAT_00458438 >= 0 && DAT_00458438 < MAX_OBJECTS && DAT_00452948_arr[DAT_00458438] != 0) {
                typedef int (__stdcall *dsb_setvol_fn)(void *self, long volume);
                void *dsb = (void *)(uintptr_t)DAT_00452948_arr[DAT_00458438];
                void **vtable = *(void ***)dsb;
                ((dsb_setvol_fn)vtable[15])(dsb, -10000L /* 0xffffd8f0 */);
            }
#endif
        }

        if (DAT_00458438 >= 0 && DAT_00458438 < MAX_OBJECTS) {
            char *dst = &DAT_00455638[DAT_00458438 * 0x14];
            size_t i = 0;
            do {
                dst[i] = sound_path[i];
            } while (sound_path[i++] != '\0');
        }
        DAT_00458438 = DAT_00458438 + 1;
    }
}

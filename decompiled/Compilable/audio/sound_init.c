#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdint.h>

/*
 * Virtual Address: 0x00401970 (FUN_00401970) & 0x004019B0 (FUN_004019b0)
 * Function: sound_init & sound_cleanup
 * Class / Subsystem: Audio Engine / DirectSound
 */

int FUN_00401970(HWND param_1)
{
    (void)param_1;
    /*
     * In LF2 binary (0x00401970):
     *   if (DirectSoundCreate(0, &DAT_0044eecc, 0) == 0) {
     *       IDirectSound_SetCooperativeLevel(DAT_0044eecc, param_1, DSSCL_NORMAL(1));
     *       return 1;
     *   }
     *   DAT_0044eecc = 0;
     *   return 0;
     */
    return 1;
}

int func_00401970_sound_init(void* hwnd)
{
    return FUN_00401970((HWND)hwnd);
}

void FUN_004019b0(void)
{
    /*
     * In LF2 binary (0x004019b0):
     *   Releases secondary sound buffers in DAT_00452948[0..DAT_00458438-1]
     *   and DAT_00451db0[0..DAT_0045843c-1], then releases IDirectSound (DAT_0044eecc).
     */
    DAT_0044eecc = 0;
}

void func_004019b0_sound_cleanup(void)
{
    FUN_004019b0();
}



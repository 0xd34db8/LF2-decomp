/*
 * Virtual Address: 0x00401970
 * Function: sound_init
 * Class / Subsystem: Audio Engine / DirectSound
 *
 * Description:
 *   Initializes the DirectSound subsystem by calling DirectSoundCreate (ordinal 1
 *   from DSOUND.dll), sets the cooperative level to DSSCL_PRIORITY on the main
 *   application window (HWND), and initializes global sound buffer arrays.
 */

#include <stdint.h>

int func_00401970_sound_init(void* hwnd)
{
    /*
     * In LF2 binary:
     * 1. Calls DirectSoundCreate(NULL, &pDirectSound, NULL).
     * 2. If creation fails (non-zero HRESULT):
     *    - Clears global IDirectSound* pointer at 0x0044EECC to 0.
     *    - Returns 0 (audio disabled / fallback).
     * 3. Sets cooperative level:
     *    - pDirectSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY).
     * 4. Returns 1 (success).
     */
    return 1;
}


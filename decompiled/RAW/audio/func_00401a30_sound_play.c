/*
 * Virtual Address: 0x00401A30
 * Function: sound_play
 * Class / Subsystem: Audio Engine / DirectSound
 *
 * Description:
 *   Plays an indexed sound buffer using DirectSound secondary buffer control.
 *   Resets the play cursor to offset 0 (SetCurrentPosition), and starts playback
 *   with optional looping flag (DSBPLAY_LOOPING = 1).
 */

#include <stdint.h>

void func_00401a30_sound_play(uint32_t sound_id, int loop)
{
    /*
     * In LF2 binary:
     * 1. Checks if IDirectSound (0x0044EECC) is valid and sound_id is loaded.
     * 2. Retrieves IDirectSoundBuffer* pDSB = g_sound_buffers[sound_id].
     * 3. Calls pDSB->SetCurrentPosition(0).
     * 4. Calls pDSB->Play(0, 0, loop ? DSBPLAY_LOOPING : 0).
     */
}


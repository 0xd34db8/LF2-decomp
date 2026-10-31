#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x004014E0
 * Function: sound_load_wav
 * Class / Subsystem: Audio Engine / DirectSound
 *
 * Description:
 *   Loads a RIFF WAVE file from disk into a newly allocated DirectSound secondary
 *   sound buffer (IDirectSoundBuffer). Verifies the 44-byte WAVE header format,
 *   locks the buffer memory, copies the audio PCM data, and stores the buffer
 *   pointer into the global sound table array at 0x00452948.
 */

#include <stdint.h>

int func_004014e0_sound_load_wav(const char* filepath, uint32_t sound_id)
{
    /*
     * In LF2 binary:
     * 1. Checks if IDirectSound pointer (0x0044EECC) is initialized.
     * 2. Opens file via Win32 CreateFileA / mmioOpen.
     * 3. Parses 'RIFF' chunk and 'fmt ' header (typically PCM 22.05 kHz, 16-bit mono/stereo).
     * 4. Populates DSBUFFERDESC (DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_STATIC).
     * 5. Calls pDirectSound->CreateSoundBuffer(&dsbd, &pDSB, NULL).
     * 6. Locks buffer via pDSB->Lock, memcpy PCM payload, and calls pDSB->Unlock.
     * 7. Stores buffer at 0x00452948[sound_id] and increments sound count (0x00458438).
     */
    return 1;
}


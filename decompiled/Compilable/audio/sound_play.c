#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdint.h>

/*
 * Virtual Addresses:
 *   - 0x00401A30: FUN_00401a30 - Play DirectSound secondary buffer (__thiscall on sound slot)
 *   - 0x00402810: FUN_00402810 - Master volume adjustment (clamps DAT_0044d000 to 0..100)
 *   - 0x00416FB0: FUN_00416fb0 - Spatial stereo sound pan/attenuation calculator 1
 *   - 0x00417090: FUN_00417090 - Spatial stereo sound pan/attenuation calculator 2
 */

void FUN_00401a30(void)
{
    int **slot = (int **)in_ECX;
    if (DAT_0044eecc != 0 && slot != NULL && *slot != NULL) {
        /*
         * In LF2 binary (0x00401a30):
         *   IDirectSoundBuffer_Stop(*slot);               // vtable + 0x48
         *   IDirectSoundBuffer_SetCurrentPosition(*slot, 0); // vtable + 0x34
         *   IDirectSoundBuffer_Play(*slot, 0, 0, 1);      // vtable + 0x30
         */
    }
}

void func_00401a30_sound_play(uint32_t sound_id, int loop)
{
    (void)sound_id;
    (void)loop;
    FUN_00401a30();
}

void FUN_00402810(int param_1)
{
    DAT_0044d000 += param_1;
    if (DAT_0044d000 < 101) {
        if (DAT_0044d000 < 0) {
            DAT_0044d000 = 0;
        }
    } else {
        DAT_0044d000 = 100;
    }
    FUN_00401f30(DAT_0044d000);
}

void FUN_00416fb0(int param_1, int param_2)
{
    if (param_2 < 0 || param_2 >= 400) return;

    int left_dist = (param_1 - DAT_00450bc4) - 200;
    if (left_dist < 0) left_dist = -left_dist;
    int left_vol;
    if (left_dist < 200) {
        left_vol = 100;
    } else if (left_dist < 400) {
        left_vol = ((400 - left_dist) * 100) / 200;
    } else {
        left_vol = 0;
    }

    int right_dist = (param_1 - DAT_00450bc4) - 600;
    if (right_dist < 0) right_dist = -right_dist;
    int right_vol;
    if (right_dist < 200) {
        right_vol = 100;
    } else if (right_dist < 400) {
        right_vol = ((400 - right_dist) * 100) / 200;
    } else {
        right_vol = 0;
    }

    if (DAT_00457588[param_2] == 0) {
        DAT_00457bc8[param_2] = 0;
        DAT_00452170[param_2] = 0;
    }
    DAT_00457bc8[param_2] += left_vol;
    DAT_00452170[param_2] += right_vol;
    DAT_00457588[param_2] = 1;
}

void FUN_00417090(int param_1, int param_2)
{
    if (param_2 < 0 || param_2 >= 400) return;

    int left_dist = (param_1 - DAT_00450bc4) - 200;
    if (left_dist < 0) left_dist = -left_dist;
    int left_vol;
    if (left_dist < 200) {
        left_vol = 100;
    } else if (left_dist < 400) {
        left_vol = ((400 - left_dist) * 100) / 200;
    } else {
        left_vol = 0;
    }

    int right_dist = (param_1 - DAT_00450bc4) - 600;
    if (right_dist < 0) right_dist = -right_dist;
    int right_vol;
    if (right_dist < 200) {
        right_vol = 100;
    } else if (right_dist < 400) {
        right_vol = ((400 - right_dist) * 100) / 200;
    } else {
        right_vol = 0;
    }

    if (DAT_00453e10[param_2] == 0) {
        DAT_004527e8[param_2] = 0;
        DAT_004554c8[param_2] = 0;
    }
    DAT_004527e8[param_2] += left_vol;
    DAT_004554c8[param_2] += right_vol;
    DAT_00453e10[param_2] = 1;
}



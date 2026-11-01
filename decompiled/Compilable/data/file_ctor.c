#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x004143D0
 * Function: lf2_file_ctor / Character File Data Constructor
 * Calling Convention: __thiscall (ECX = file_t*)
 *
 * Initializes all 400 animation frames with frame_ctor (0x0040BBF0),
 * then invokes master dat script parser (0x0040EF70).
 */

int lf2_file_ctor(file_t *file, undefined4 param_1, undefined4 param_2, const char *dat_path)
{
    if (!file) return 0;

    // 0x004143DC: Initialize all 400 animation frames
    for (int i = 0; i < MAX_FRAMES; ++i) {
        lf2_frame_ctor(&file->frames[i]);
    }

    // 0x00414400: Invoke master dat script loader
    FUN_0040ef70(param_1, param_2, (char *)(uintptr_t)dat_path, 0);
    return (int)(uintptr_t)file;
}

// MSVC __thiscall bridge for FUN_004143d0
int FUN_004143d0(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
    return lf2_file_ctor((file_t *)in_ECX, param_1, param_2, (const char *)(uintptr_t)param_3);
}

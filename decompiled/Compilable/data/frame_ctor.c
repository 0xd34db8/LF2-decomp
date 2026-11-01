#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x0040BBF0
 * Function: lf2_frame_ctor / Animation Frame Zeroing & Initialization
 * Calling Convention: __thiscall (ECX = frame_t*)
 */

void lf2_frame_ctor(frame_t *frame)
{
    if (!frame) return;
    memset(frame, 0, sizeof(frame_t));
}

// MSVC __thiscall bridge for FUN_0040bbf0
void FUN_0040bbf0(void)
{
    lf2_frame_ctor((frame_t *)in_ECX);
}

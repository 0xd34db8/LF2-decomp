#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x0040BBF0
 * Function: lf2_frame_ctor / Animation Frame Zeroing & Initialization
 * Calling Convention: __thiscall (ECX = frame_t*)
 */

// FUNCTION: LF2 0x0040bbf0
void lf2_frame_ctor(frame_t *frame)
{
    if (!frame) return;
    memset(frame, 0, sizeof(frame_t));
    frame->sound_id = -1;
}

// MSVC __thiscall bridge for FUN_0040bbf0
void FUN_0040bbf0(void)
{
    lf2_frame_ctor((frame_t *)in_ECX);
}

/*
 * Virtual Address: 0x0040D940
 * Function: lf2_frame_is_present / Frame slot presence check
 * Calling Convention: __thiscall (ECX = const file_t*)
 */
// FUNCTION: LF2 0x0040d940
bool lf2_frame_is_present(const file_t *file, int frame_id)
{
    if (!file || frame_id < 0 || frame_id >= MAX_FRAMES) {
        return false;
    }
    return *(const char *)&file->frames[frame_id].present == '\x01';
}

bool FUN_0040d940(int param_1)
{
    return lf2_frame_is_present((const file_t *)in_ECX, param_1);
}

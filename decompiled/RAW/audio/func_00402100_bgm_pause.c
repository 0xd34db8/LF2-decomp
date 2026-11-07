/*
 * Procedure: FUN_00402100
 * Address: 0x00402100 - 0x0040212b (Length: 44 bytes)
 * Purpose: DirectShow BGM Playback Pause & Rewind to Origin (IMediaControl::Pause + SetPositions 0)
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>

void FUN_00402100(void)

{
  if (DAT_0044f04c != (int *)0x0) {
    (**(code **)(*DAT_0044f044 + 0x24))(DAT_0044f044);
    (**(code **)(*DAT_0044f04c + 0x20))(DAT_0044f04c,0);
  }
  return;
}

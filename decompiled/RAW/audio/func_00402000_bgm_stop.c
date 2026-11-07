/*
 * Procedure: FUN_00402000
 * Address: 0x00402000 - 0x00402011 (Length: 18 bytes)
 * Purpose: DirectShow BGM Stream Playback Stop (IMediaControl::Stop)
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>

void FUN_00402000(void)

{
  if (DAT_0044f044 != (int *)0x0) {
    (**(code **)(*DAT_0044f044 + 0x1c))(DAT_0044f044);
  }
  return;
}

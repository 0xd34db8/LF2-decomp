/*
 * Function: Multi-line Formatted Text Box Renderer with Cursor
 * Virtual Address: 0x00423940
 * Calling Convention: __cdecl
 *
 * Parameters:
 *   param_1: Text string (char*)
 *   param_2: X screen coordinate (int)
 *   param_3: Y screen coordinate (int)
 *   param_4: Max characters per line (int)
 *   param_5: Max lines (int)
 *   param_6: Rendering mode (int: 0, 1, 2)
 *   param_7: Blinking cursor flag (int: 1 for visible cursor '_', 0 for none)
 *
 * Description:
 *   Iterates through characters in param_1, blitting each glyph using FUN_0043f010
 *   at 8-pixel horizontal increments and 16-pixel vertical line increments.
 *   Handles newline characters ('\n') and line width wraps.
 *   Appends a cursor glyph ('_' / 0x5F) if param_7 is non-zero.
 */

#include <string.h>

extern void* DAT_00455608; // Render target / screen surface
extern void FUN_0043f010(int x, int y, int glyph, int mode, int extra, void* target);

void FUN_00423940(char *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;

  iVar6 = param_3;
  iVar4 = 0;
  iVar3 = 0;
  param_3 = 0;
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar5 = param_2;
  if (0 < (int)pcVar2 - (int)(param_1 + 1)) {
    do {
      if (param_5 <= iVar4) break;
      if (param_1[param_3] == '\n') {
        if (param_5 - 1 <= iVar4) break;
LAB_00423a0e:
        iVar6 = iVar6 + 0x10;
        iVar4 = iVar4 + 1;
        iVar3 = 0;
        iVar5 = param_2;
      }
      else {
        iVar3 = iVar3 + 1;
        if (((param_6 == 0) || (param_6 == 1)) || (param_6 == 2)) {
          FUN_0043f010(iVar5, iVar6, (int)param_1[param_3], 1, 0, DAT_00455608);
        }
        iVar5 = iVar5 + 8;
        if (param_4 <= iVar3) {
          if (iVar4 < param_5 - 1) goto LAB_00423a0e;
          param_3 = param_3 + 1;
          break;
        }
      }
      param_3 = param_3 + 1;
      pcVar2 = param_1;
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
    } while (param_3 < (int)pcVar2 - (int)(param_1 + 1));
  }
  param_1[param_3] = '\0';
  if (param_7 != 0) {
    FUN_0043f010(iVar5, iVar6, 0x5f, 1, 0, DAT_00455608);
  }
}


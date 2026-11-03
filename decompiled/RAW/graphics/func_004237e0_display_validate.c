/*
 * Function: Display Refresh / Mode Validation
 * Virtual Address: 0x004237E0
 * Calling Convention: __cdecl
 *
 * Description:
 *   Validates current display settings and timings, calling FUN_0043c450
 *   to refresh the display when conditions require.
 */

#include <windows.h>
#include <stdbool.h>

extern int DAT_0044d788;
extern char DAT_004527b0;
extern unsigned char DAT_00451d48;

extern void FUN_0043c450(void);

void FUN_004237e0(void)
{
  unsigned char bVar1;
  unsigned char *pbVar2;
  int iVar3;
  unsigned char *pbVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;

  if (DAT_0044d788 != -99) {
    iVar3 = 4;
    bVar7 = true;
    pcVar5 = &DAT_004527b0;
    pcVar6 = "now";
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 - 1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (!bVar7) {
      pbVar4 = &DAT_00451d48;
      pbVar2 = (unsigned char*)&DAT_004527b0;
      do {
        bVar1 = *pbVar2;
        bVar7 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_00423830:
          iVar3 = (1 - (unsigned int)bVar7) - (unsigned int)(bVar7 != 0);
          goto LAB_00423835;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar7 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_00423830;
        pbVar2 = pbVar2 + 2;
        pbVar4 = pbVar4 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_00423835:
      if (0 < iVar3) {
        return;
      }
    }
  }
  FUN_0043c450();
  return;
}


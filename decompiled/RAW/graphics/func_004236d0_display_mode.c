/*
 * Function: Fullscreen / Windowed Display Mode Toggle
 * Virtual Address: 0x004236D0
 * Calling Convention: __cdecl
 *
 * Description:
 *   Handles switching between windowed and fullscreen display modes.
 *   Modifies display flag DAT_0044d784 (1 - mode & 1), calls DirectDraw
 *   surface teardown and recreate functions FUN_0043c780 and FUN_0043cc60.
 */

#include <windows.h>

extern CRITICAL_SECTION DAT_004554a4;
extern int DAT_00458424;
extern int DAT_0044d778;
extern int DAT_0044d77c;
extern int DAT_0044d784;
extern char DAT_00458350;
extern char DAT_004527b0;

extern int FUN_0043c780(void);
extern int FUN_0043cc60(void);
extern void FUN_0043c690(void);
extern void FUN_0043c710(void);

void FUN_004236d0(void)
{
  char *pcVar1;
  int iVar2;

  EnterCriticalSection(&DAT_004554a4);
  if (DAT_00458424 != 2) goto LAB_004237c8;
  DAT_00458424 = 0;
  if (DAT_0044d778 < DAT_0044d77c) {
    DAT_0044d784 = (1 - DAT_0044d784) & 0x80000001;
    if (DAT_0044d784 < 0) {
      DAT_0044d784 = (DAT_0044d784 - 1 | 0xfffffffe) + 1;
    }
    iVar2 = FUN_0043c780();
    if (iVar2 == 0) {
      DAT_0044d784 = (1 - DAT_0044d784) & 0x80000001;
      if (DAT_0044d784 < 0) {
        DAT_0044d784 = (DAT_0044d784 - 1 | 0xfffffffe) + 1;
      }
      iVar2 = FUN_0043c780();
    }
    else {
      iVar2 = FUN_0043cc60();
      if (iVar2 != 0) goto LAB_004237a0;
      DAT_0044d784 = (1 - DAT_0044d784) & 0x80000001;
      if (DAT_0044d784 < 0) {
        DAT_0044d784 = (DAT_0044d784 - 1 | 0xfffffffe) + 1;
      }
      iVar2 = FUN_0043c780();
    }
    if ((iVar2 == 0) || (iVar2 = FUN_0043cc60(), iVar2 == 0)) {
      FUN_0043c690();
      FUN_0043c710();
      LeaveCriticalSection(&DAT_004554a4);
      return;
    }
  }
  else {
LAB_004237a0:
    iVar2 = 0;
    do {
      pcVar1 = &DAT_00458350 + iVar2;
      (&DAT_004527b0)[iVar2] = *pcVar1;
      iVar2 = iVar2 + 1;
    } while (*pcVar1 != '\0');
  }
  FUN_0043c710();
LAB_004237c8:
  LeaveCriticalSection(&DAT_004554a4);
  return;
}


/*
 * Function: Load Random Menu Background Image
 * Virtual Address: 0x00423840
 * Calling Convention: __cdecl
 *
 * Description:
 *   Loads a random menu background bitmap from "MENU_BACK1" to "MENU_BACK13"
 *   based on timeGetTime() % 13 + 1, allocating a 0x1F50 sprite sheet descriptor
 *   via operator new and storing the pointer in DAT_004511ac.
 */

#include <windows.h>
#include <stdio.h>

extern void* DAT_004511ac; // Pointer to active menu background sprite structure
extern void* operator_new(size_t size);
extern void* FUN_0043ee50(int param_1, const char* param_2, int param_3);

void FUN_00423840(void)
{
  DWORD DVar2;
  void *local_24;
  char local_20[16];

  strncpy(local_20, "MENU_BACK0000", 14);
  DVar2 = timeGetTime();
  sprintf(local_20, "MENU_BACK%d", (int)(DVar2 % 13 + 1));
  local_24 = operator_new(0x1f50);
  if (local_24 == NULL) {
    DAT_004511ac = NULL;
  }
  else {
    DAT_004511ac = FUN_0043ee50(0x40, local_20, 0);
  }
}


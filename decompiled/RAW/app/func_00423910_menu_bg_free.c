/*
 * Function: Free Menu Background Surface
 * Virtual Address: 0x00423910
 * Calling Convention: __cdecl
 *
 * Description:
 *   Releases the allocated menu background texture/surface descriptor
 *   at DAT_004511ac, invoking FUN_0043ef50 destructor and freeing memory.
 */

#include <stdlib.h>

extern void* DAT_004511ac;
extern void FUN_0043ef50(void);

void FUN_00423910(void)
{
  if (DAT_004511ac != NULL) {
    FUN_0043ef50();
    free(DAT_004511ac);
    DAT_004511ac = NULL;
  }
}


#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x00431B70
 * Function: menu_check_player_join_input
 * Class / Subsystem: Application / Menu & Input Polling
 *
 * Description:
 *   Scans player controllers 1 through 8 (at world offset +0x194) for button presses
 *   (Up, Down, Left, Right, Attack, Jump, Defend at offsets 0xCD..0xD3).
 *   Updates the active human player bitfield (DAT_00451320..DAT_00451340)
 *   and signals new-player-join transition flags (DAT_004513a4..DAT_004513bc).
 */

void FUN_00431b70(void)
{
  int iVar1;
  int *piVar2;
  int in_ECX_local = (int)(intptr_t)in_ECX;
  int *piVar3;
  
  DAT_004513bc = 0;
  DAT_004513b8 = 0;
  DAT_004513b4 = 0;
  DAT_004513b0 = 0;
  DAT_004513ac = 0;
  DAT_004513a8 = 0;
  DAT_004513a4 = 0;
  piVar2 = (int *)&DAT_00451320;
  piVar3 = (int *)(in_ECX_local + 0x194);
  do {
    iVar1 = *piVar3;
    if (*(char *)(iVar1 + 0xcd) == '\0') {
      if (*(char *)(iVar1 + 0xce) == '\0') {
        if (*(char *)(iVar1 + 0xd0) == '\0') {
          if (*(char *)(iVar1 + 0xcf) == '\0') {
            if (*(char *)(iVar1 + 0xd1) == '\0') {
              if (*(char *)(iVar1 + 0xd2) == '\0') {
                if (*(char *)(iVar1 + 0xd3) == '\0') {
                  *piVar2 = 0;
                }
                else {
                  if (*piVar2 == 0) {
                    DAT_004513bc = 1;
                  }
                  *piVar2 = 1;
                }
              }
              else {
                if (*piVar2 == 0) {
                  DAT_004513b8 = 1;
                }
                *piVar2 = 1;
              }
            }
            else {
              if (*piVar2 == 0) {
                DAT_004513b4 = 1;
              }
              *piVar2 = 1;
            }
          }
          else {
            if (*piVar2 == 0) {
              DAT_004513ac = 1;
            }
            *piVar2 = 1;
          }
        }
        else {
          if (*piVar2 == 0) {
            DAT_004513b0 = 1;
          }
          *piVar2 = 1;
        }
      }
      else {
        if (*piVar2 == 0) {
          DAT_004513a8 = 1;
        }
        *piVar2 = 1;
      }
    }
    else {
      if (*piVar2 == 0) {
        DAT_004513a4 = 1;
      }
      *piVar2 = 1;
    }
    piVar2 = piVar2 + 1;
    piVar3 = piVar3 + 1;
  } while ((uintptr_t)piVar2 < (uintptr_t)&DAT_00451340);
  return;
}


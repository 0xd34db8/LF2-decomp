/*
 * Virtual Address: 0x00431C70
 * Function: menu_reset_input_and_keys
 * Class / Subsystem: Application / Menu & Input Management
 *
 * Description:
 *   Resets all player menu inputs and restores the global keyboard state array
 *   (DAT_00455378) to 'u' (0x75, key up) across 300 bytes.
 *   Clears active player flags and input signals.
 */

void FUN_00431c70(void)
{
  int iVar1;
  int *piVar2;
  int in_ECX;
  undefined4 *puVar3;
  
  DAT_004513bc = 0;
  DAT_004513b8 = 0;
  DAT_004513b4 = 0;
  DAT_004513b0 = 0;
  DAT_004513ac = 0;
  DAT_004513a8 = 0;
  DAT_004513a4 = 0;
  puVar3 = &DAT_00451320;
  piVar2 = (int *)(in_ECX + 0x194);
  do {
    *puVar3 = 0;
    *(undefined1 *)(*piVar2 + 0xd3) = 0;
    *(undefined1 *)(*piVar2 + 0xd2) = 0;
    *(undefined1 *)(*piVar2 + 0xd1) = 0;
    *(undefined1 *)(*piVar2 + 0xcf) = 0;
    *(undefined1 *)(*piVar2 + 0xd0) = 0;
    *(undefined1 *)(*piVar2 + 0xce) = 0;
    iVar1 = *piVar2;
    puVar3 = puVar3 + 1;
    piVar2 = piVar2 + 1;
    *(undefined1 *)(iVar1 + 0xcd) = 0;
  } while ((int)puVar3 < 0x451340);
  memset(&DAT_00455378,0x75,300);
  return;
}


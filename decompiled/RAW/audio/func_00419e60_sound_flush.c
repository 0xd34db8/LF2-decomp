/* Function: FUN_00419e60 */
/* Address: 0x00419e60 */

void FUN_00419e60(void)

{
  int iVar1;
  int iVar2;
  
  if (DAT_0044eecc != 0) {
    iVar1 = 0;
    do {
      if (0 < *(int *)((int)&DAT_00457588 + iVar1)) {
        iVar2 = *(int *)((int)&DAT_00457bc8 + iVar1) + *(int *)((int)&DAT_00452170 + iVar1);
        *(undefined4 *)((int)&DAT_00457588 + iVar1) = 0;
        if (iVar2 < 0x65) {
          if (iVar2 < 1) goto LAB_00419f4d;
        }
        else {
          iVar2 = 100;
        }
        (**(code **)(**(int **)((int)&DAT_00452948 + iVar1) + 0x40))
                  (*(int **)((int)&DAT_00452948 + iVar1),
                   ((*(int *)((int)&DAT_00452170 + iVar1) - *(int *)((int)&DAT_00457bc8 + iVar1)) *
                   0x5dc) / 100);
        (**(code **)(**(int **)((int)&DAT_00452948 + iVar1) + 0x3c))
                  (*(int **)((int)&DAT_00452948 + iVar1),
                   ((DAT_0044d000 + -100) * 0xed8) / 100 + ((iVar2 + -100) * 2000) / 100);
        if (0 < DAT_0044d000) {
          FUN_00401a30(0);
        }
      }
LAB_00419f4d:
      iVar1 = iVar1 + 4;
    } while (iVar1 < 0x640);
    iVar1 = 0;
    do {
      if (0 < *(int *)((int)&DAT_00453e10 + iVar1)) {
        iVar2 = *(int *)((int)&DAT_004527e8 + iVar1) + *(int *)((int)&DAT_004554c8 + iVar1);
        *(undefined4 *)((int)&DAT_00453e10 + iVar1) = 0;
        if (iVar2 < 0x65) {
          if (iVar2 < 1) goto LAB_0041a02d;
        }
        else {
          iVar2 = 100;
        }
        (**(code **)(**(int **)((int)&DAT_00451db0 + iVar1) + 0x40))
                  (*(int **)((int)&DAT_00451db0 + iVar1),
                   ((*(int *)((int)&DAT_004554c8 + iVar1) - *(int *)((int)&DAT_004527e8 + iVar1)) *
                   0x5dc) / 100);
        (**(code **)(**(int **)((int)&DAT_00451db0 + iVar1) + 0x3c))
                  (*(int **)((int)&DAT_00451db0 + iVar1),
                   ((DAT_0044d000 + -100) * 0xed8) / 100 + ((iVar2 + -100) * 2000) / 100);
        if (0 < DAT_0044d000) {
          FUN_00401a30(0);
        }
      }
LAB_0041a02d:
      iVar1 = iVar1 + 4;
    } while (iVar1 < 0x140);
  }
  return;
}

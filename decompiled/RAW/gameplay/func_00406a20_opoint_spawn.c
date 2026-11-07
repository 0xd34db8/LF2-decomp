/* Function: FUN_00406a20 */
/* Address: 0x00406a20 */

int FUN_00406a20(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,
                int param_6,int param_7,undefined8 param_8,undefined8 param_9,undefined8 param_10,
                undefined1 param_11)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int in_ECX;
  int *piVar5;
  int iVar6;
  
  iVar4 = 0x32;
  iVar6 = -1;
  do {
    if (*(char *)(in_ECX + 4 + iVar4) == '\0') {
      iVar6 = iVar4;
      break;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 400);
  if (iVar6 != -1) {
    piVar5 = *(int **)(in_ECX + 0x7d4);
    piVar1 = piVar5 + 0x13608e0;
    iVar4 = 0;
    if (0 < *piVar1) {
      do {
        if (*(int *)(*piVar5 + 0x6f4) == param_1) {
          if (iVar4 == -1) {
            return -1;
          }
          iVar2 = *(int *)(in_ECX + 0x194 + iVar6 * 4);
          iVar4 = *(int *)(*(int *)(in_ECX + 0x7d4) + iVar4 * 4);
          FUN_004061d0();
          *(int *)(iVar2 + 0x368) = iVar4;
          uVar3 = *(undefined4 *)(iVar4 + 0x90);
          *(undefined8 *)(iVar2 + 0x58) = 0x4082200000000000;
          *(undefined8 *)(iVar2 + 0x60) = 0xc069000000000000;
          *(undefined4 *)(iVar2 + 0x31c) = uVar3;
          *(undefined8 *)(iVar2 + 0x68) = 0x4072c00000000000;
          *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x354) = param_2;
          *(int *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x10) = param_5;
          *(int *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x14) = param_6;
          *(int *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x18) = param_7;
          *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x364) = param_4;
          *(double *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x58) = (double)param_5;
          *(double *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x60) = (double)param_6;
          *(double *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x68) = (double)param_7;
          *(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x70) = param_3;
          *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x40) = param_8;
          *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x48) = param_9;
          *(undefined8 *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x50) = param_10;
          *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar6 * 4) + 0x80) = param_11;
          *(undefined1 *)(iVar6 + 4 + in_ECX) = 1;
          return iVar6;
        }
        iVar4 = iVar4 + 1;
        piVar5 = piVar5 + 1;
      } while (iVar4 < *piVar1);
    }
  }
  return -1;
}

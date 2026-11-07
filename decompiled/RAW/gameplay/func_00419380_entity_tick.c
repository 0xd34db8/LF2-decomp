/* Function: FUN_00419380 */
/* Address: 0x00419380 */

void FUN_00419380(undefined4 param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  char *in_ECX;
  int iVar6;
  int *local_4;
  
  piVar4 = (int *)(in_ECX + 0x198);
  local_4 = (int *)0x50;
  pcVar1 = in_ECX;
  do {
    if ((pcVar1[4] != '\0') &&
       ((*(undefined4 *)(piVar4[-1] + 0x7c) = *(undefined4 *)(piVar4[-1] + 0x70),
        *(int *)(*(int *)(piVar4[-1] + 0x70) * 0x178 + 0x8cc + *(int *)(piVar4[-1] + 0x368)) == 0 ||
        ((*(int *)(*(int *)(piVar4[-1] + 0x70) * 0x178 + 0x7ac + *(int *)(piVar4[-1] + 0x368)) ==
          0x3e9 && (*(int *)(*(int *)(*(int *)(in_ECX + *(int *)(piVar4[-1] + 0xa0) * 4 + 0x194) +
                                     0x70) * 0x178 + 0x88c +
                            *(int *)(*(int *)(in_ECX + *(int *)(piVar4[-1] + 0xa0) * 4 + 0x194) +
                                    0x368)) == 0)))))) {
      *(undefined4 *)(piVar4[-1] + 0xec) = 0;
    }
    if ((pcVar1[5] != '\0') &&
       ((*(undefined4 *)(*piVar4 + 0x7c) = *(undefined4 *)(*piVar4 + 0x70),
        *(int *)(*(int *)(*piVar4 + 0x70) * 0x178 + 0x8cc + *(int *)(*piVar4 + 0x368)) == 0 ||
        ((*(int *)(*(int *)(*piVar4 + 0x70) * 0x178 + 0x7ac + *(int *)(*piVar4 + 0x368)) == 0x3e9 &&
         (*(int *)(*(int *)(*(int *)(in_ECX + *(int *)(*piVar4 + 0xa0) * 4 + 0x194) + 0x70) * 0x178
                   + 0x88c +
                  *(int *)(*(int *)(in_ECX + *(int *)(*piVar4 + 0xa0) * 4 + 0x194) + 0x368)) == 0)))
        ))) {
      *(undefined4 *)(*piVar4 + 0xec) = 0;
    }
    if ((pcVar1[6] != '\0') &&
       ((*(undefined4 *)(piVar4[1] + 0x7c) = *(undefined4 *)(piVar4[1] + 0x70),
        *(int *)(*(int *)(piVar4[1] + 0x70) * 0x178 + 0x8cc + *(int *)(piVar4[1] + 0x368)) == 0 ||
        ((*(int *)(*(int *)(piVar4[1] + 0x70) * 0x178 + 0x7ac + *(int *)(piVar4[1] + 0x368)) ==
          0x3e9 && (*(int *)(*(int *)(*(int *)(in_ECX + *(int *)(piVar4[1] + 0xa0) * 4 + 0x194) +
                                     0x70) * 0x178 + 0x88c +
                            *(int *)(*(int *)(in_ECX + *(int *)(piVar4[1] + 0xa0) * 4 + 0x194) +
                                    0x368)) == 0)))))) {
      *(undefined4 *)(piVar4[1] + 0xec) = 0;
    }
    if ((pcVar1[7] != '\0') &&
       ((*(undefined4 *)(piVar4[2] + 0x7c) = *(undefined4 *)(piVar4[2] + 0x70),
        *(int *)(*(int *)(piVar4[2] + 0x70) * 0x178 + 0x8cc + *(int *)(piVar4[2] + 0x368)) == 0 ||
        ((*(int *)(*(int *)(piVar4[2] + 0x70) * 0x178 + 0x7ac + *(int *)(piVar4[2] + 0x368)) ==
          0x3e9 && (*(int *)(*(int *)(*(int *)(in_ECX + *(int *)(piVar4[2] + 0xa0) * 4 + 0x194) +
                                     0x70) * 0x178 + 0x88c +
                            *(int *)(*(int *)(in_ECX + *(int *)(piVar4[2] + 0xa0) * 4 + 0x194) +
                                    0x368)) == 0)))))) {
      *(undefined4 *)(piVar4[2] + 0xec) = 0;
    }
    if ((pcVar1[8] != '\0') &&
       ((*(undefined4 *)(piVar4[3] + 0x7c) = *(undefined4 *)(piVar4[3] + 0x70),
        *(int *)(*(int *)(piVar4[3] + 0x70) * 0x178 + 0x8cc + *(int *)(piVar4[3] + 0x368)) == 0 ||
        ((*(int *)(*(int *)(piVar4[3] + 0x70) * 0x178 + 0x7ac + *(int *)(piVar4[3] + 0x368)) ==
          0x3e9 && (*(int *)(*(int *)(*(int *)(in_ECX + *(int *)(piVar4[3] + 0xa0) * 4 + 0x194) +
                                     0x70) * 0x178 + 0x88c +
                            *(int *)(*(int *)(in_ECX + *(int *)(piVar4[3] + 0xa0) * 4 + 0x194) +
                                    0x368)) == 0)))))) {
      *(undefined4 *)(piVar4[3] + 0xec) = 0;
    }
    piVar4 = piVar4 + 5;
    local_4 = (int *)((int)local_4 + -1);
    pcVar1 = pcVar1 + 5;
  } while (local_4 != (int *)0x0);
  local_4 = (int *)(in_ECX + 0x194);
  iVar6 = 0;
  do {
    piVar4 = local_4;
    iVar3 = iVar6;
    if (in_ECX[iVar6 + 4] != '\0') {
      while (iVar2 = iVar3 + 1, iVar2 < 400) {
        piVar4 = piVar4 + 1;
        iVar5 = iVar3 + 5;
        iVar3 = iVar2;
        if (in_ECX[iVar5] != '\0') {
          if ('\0' < *(char *)(*local_4 + 0xf0 + iVar2)) {
            pcVar1 = (char *)(*local_4 + 0xf0 + iVar2);
            *pcVar1 = *pcVar1 + -1;
          }
          if ('\0' < *(char *)(*piVar4 + 0xf0 + iVar6)) {
            pcVar1 = (char *)(*piVar4 + 0xf0 + iVar6);
            *pcVar1 = *pcVar1 + -1;
          }
          iVar5 = FUN_00417200(iVar6,iVar2);
          if (iVar5 != 0) {
            FUN_00417400(iVar6,iVar2,param_1);
          }
          iVar5 = FUN_00417200(iVar2,iVar6);
          if (iVar5 != 0) {
            FUN_00417400(iVar2,iVar6,param_1);
          }
        }
      }
    }
    iVar6 = iVar6 + 1;
    local_4 = local_4 + 1;
  } while (iVar6 < 400);
  FUN_004064d0();
  return;
}

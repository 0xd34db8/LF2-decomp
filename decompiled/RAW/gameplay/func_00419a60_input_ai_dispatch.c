/* Function: FUN_00419a60 */
/* Address: 0x00419a60 */

void FUN_00419a60(int param_1,undefined4 param_2,byte *param_3)

{
  int *piVar1;
  int in_ECX;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  pbVar2 = param_3;
  if (DAT_00450b84 == 0) {
    param_3 = (byte *)&DAT_00450b4c;
    piVar1 = (int *)(in_ECX + 0x194);
    iVar5 = (int)&DAT_0044d040 - (int)pbVar2;
    do {
      if (0 < *(int *)param_3) {
        *(undefined1 *)(*piVar1 + 0xc6) = *(undefined1 *)(*piVar1 + 0xcd);
        *(undefined1 *)(*piVar1 + 199) = *(undefined1 *)(*piVar1 + 0xce);
        *(undefined1 *)(*piVar1 + 200) = *(undefined1 *)(*piVar1 + 0xcf);
        *(undefined1 *)(*piVar1 + 0xc9) = *(undefined1 *)(*piVar1 + 0xd0);
        *(undefined1 *)(*piVar1 + 0xca) = *(undefined1 *)(*piVar1 + 0xd1);
        *(undefined1 *)(*piVar1 + 0xcb) = *(undefined1 *)(*piVar1 + 0xd2);
        *(undefined1 *)(*piVar1 + 0xcc) = *(undefined1 *)(*piVar1 + 0xd3);
        if (param_1 == 0) {
          *(undefined1 *)(*piVar1 + 0xd3) = 0;
          *(undefined1 *)(*piVar1 + 0xd2) = 0;
          *(undefined1 *)(*piVar1 + 0xd1) = 0;
          *(undefined1 *)(*piVar1 + 0xd0) = 0;
          *(undefined1 *)(*piVar1 + 0xcf) = 0;
          *(undefined1 *)(*piVar1 + 0xce) = 0;
          *(undefined1 *)(*piVar1 + 0xcd) = 0;
          if (*(int *)param_3 - 1U < 4) {
            iVar4 = *(int *)param_3 * 0x50;
            iVar3 = *(int *)(&DAT_0044fb20 + iVar4);
            if (iVar3 == 0) {
              if (((&DAT_00455378)[*(int *)(&DAT_0044fb24 + iVar4)] == 'd') &&
                 (*(undefined1 *)(*piVar1 + 0xcd) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 0x80;
              }
              if (((&DAT_00455378)[*(int *)(&DAT_0044fb28 + iVar4)] == 'd') &&
                 (*(undefined1 *)(*piVar1 + 0xce) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 0x40;
              }
              if (((&DAT_00455378)[*(int *)(&DAT_0044fb2c + iVar4)] == 'd') &&
                 (*(undefined1 *)(*piVar1 + 0xcf) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 0x20;
              }
              if (((&DAT_00455378)[*(int *)(&DAT_0044fb30 + iVar4)] == 'd') &&
                 (*(undefined1 *)(*piVar1 + 0xd0) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 0x10;
              }
              if (((&DAT_00455378)[*(int *)(&DAT_0044fb34 + iVar4)] == 'd') &&
                 (*(undefined1 *)(*piVar1 + 0xd1) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 8;
              }
              if (((&DAT_00455378)[*(int *)(&DAT_0044fb38 + iVar4)] == 'd') &&
                 (*(undefined1 *)(*piVar1 + 0xd2) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 4;
              }
              if (((&DAT_00455378)[*(int *)(&DAT_0044fb3c + iVar4)] == 'd') &&
                 (*(undefined1 *)(*piVar1 + 0xd3) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 2;
              }
            }
            else if (0 < iVar3) {
              iVar3 = (iVar3 * 3 + -3) * 0x10;
              if (((&DAT_00453ff0)[iVar3] != '\0') &&
                 (*(undefined1 *)(*piVar1 + 0xcd) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 0x80;
              }
              if (((&DAT_00453ff1)[iVar3] != '\0') &&
                 (*(undefined1 *)(*piVar1 + 0xce) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 0x40;
              }
              if (((&DAT_00453ff3)[iVar3] != '\0') &&
                 (*(undefined1 *)(*piVar1 + 0xcf) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 0x20;
              }
              if (((&DAT_00453ff2)[iVar3] != '\0') &&
                 (*(undefined1 *)(*piVar1 + 0xd0) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 0x10;
              }
              if ((*(char *)((int)&DAT_00453ff4 + *(int *)(&DAT_0044fb40 + iVar4) + iVar3) != '\0')
                 && (*(undefined1 *)(*piVar1 + 0xd1) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 8;
              }
              if ((*(char *)((int)&DAT_00453ff4 + *(int *)(&DAT_0044fb44 + iVar4) + iVar3) != '\0')
                 && (*(undefined1 *)(*piVar1 + 0xd2) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 4;
              }
              if ((*(char *)((int)&DAT_00453ff4 + iVar3 + *(int *)(&DAT_0044fb48 + iVar4)) != '\0')
                 && (*(undefined1 *)(*piVar1 + 0xd3) = 1, DAT_00450b80 != 0)) {
                *pbVar2 = *pbVar2 | 2;
              }
            }
          }
          if ('\0' < DAT_0044f1af) {
            if (*(char *)(*piVar1 + 0xcd) != '\0') {
              pbVar2[iVar5] = pbVar2[iVar5] | 0x80;
            }
            if (*(char *)(*piVar1 + 0xce) != '\0') {
              pbVar2[iVar5] = pbVar2[iVar5] | 0x40;
            }
            if (*(char *)(*piVar1 + 0xcf) != '\0') {
              pbVar2[iVar5] = pbVar2[iVar5] | 0x20;
            }
            if (*(char *)(*piVar1 + 0xd0) != '\0') {
              pbVar2[iVar5] = pbVar2[iVar5] | 0x10;
            }
            if (*(char *)(*piVar1 + 0xd1) != '\0') {
              pbVar2[iVar5] = pbVar2[iVar5] | 8;
            }
            if (*(char *)(*piVar1 + 0xd2) != '\0') {
              pbVar2[iVar5] = pbVar2[iVar5] | 4;
            }
            if (*(char *)(*piVar1 + 0xd3) != '\0') {
              pbVar2[iVar5] = pbVar2[iVar5] | 2;
            }
          }
        }
      }
      param_3 = (byte *)((int)param_3 + 4);
      piVar1 = piVar1 + 1;
      pbVar2 = pbVar2 + 1;
    } while ((int)param_3 < 0x450b6c);
  }
  iVar5 = 10;
  piVar1 = (int *)(in_ECX + 0x1bc);
  do {
    if (*(char *)(in_ECX + 4 + iVar5) != '\0') {
      iVar3 = *piVar1;
      if (*(int *)(*(int *)(iVar3 + 0x368) + 0x6f8) == 0) {
        FUN_004094b0(iVar5,param_2);
      }
      else if (0 < *(int *)(*(int *)(iVar3 + 0x70) * 0x178 + 0x7d4 + *(int *)(iVar3 + 0x368))) {
        FUN_00406ba0(iVar5);
      }
    }
    iVar5 = iVar5 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar5 < 400);
  return;
}


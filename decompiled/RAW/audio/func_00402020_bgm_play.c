/* Function: FUN_00402020 */
/* Address: 0x00402020 */

void FUN_00402020(byte *param_1)

{
  byte bVar1;
  int *piVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  char *lpText;
  
  if (DAT_0044d010 == 0) {
    return;
  }
  pbVar3 = &DAT_0044ef04;
  pbVar5 = param_1;
  do {
    bVar1 = *pbVar3;
    bVar6 = bVar1 < *pbVar5;
    if (bVar1 != *pbVar5) {
LAB_00402060:
      iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
      goto LAB_00402065;
    }
    if (bVar1 == 0) break;
    bVar1 = pbVar3[1];
    bVar6 = bVar1 < pbVar5[1];
    if (bVar1 != pbVar5[1]) goto LAB_00402060;
    pbVar3 = pbVar3 + 2;
    pbVar5 = pbVar5 + 2;
  } while (bVar1 != 0);
  iVar4 = 0;
LAB_00402065:
  if (iVar4 == 0) {
    if (DAT_0044f044 == (int *)0x0) {
      return;
    }
    (**(code **)(*DAT_0044f044 + 0x1c))(DAT_0044f044);
    return;
  }
  FUN_00401d30();
  iVar4 = FUN_00401c90();
  if (iVar4 == 0) {
    iVar4 = FUN_00401da0(param_1);
    if (iVar4 == 0) goto LAB_004020bd;
    lpText = "Could not create a filter graph for this file!";
  }
  else {
    lpText = "Could not initialize DirectShow!";
  }
  MessageBoxA((HWND)0x0,lpText,"ERROR",0);
LAB_004020bd:
  FUN_00401f30(DAT_0044d000);
  piVar2 = DAT_0044f044;
  if (DAT_0044f044 != (int *)0x0) {
    iVar4 = (int)&DAT_0044ef04 - (int)param_1;
    do {
      bVar1 = *param_1;
      param_1[iVar4] = bVar1;
      param_1 = param_1 + 1;
    } while (bVar1 != 0);
    (**(code **)(*piVar2 + 0x1c))(piVar2);
  }
  return;
}

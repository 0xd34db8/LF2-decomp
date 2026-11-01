/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int * FUN_00436fc0(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int in_ECX;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int local_58 [21];
  
  DAT_00450b94 = DAT_00450b94 + 1;
  local_58[0] = 0;
  local_58[1] = 0;
  local_58[2] = 0;
  local_58[3] = 0;
  local_58[4] = 0;
  local_58[5] = 0;
  local_58[6] = 0;
  local_58[7] = 0;
  local_58[8] = 0;
  local_58[9] = 0;
  local_58[10] = 0;
  local_58[0xb] = 0;
  local_58[0xc] = 0;
  local_58[0xd] = 0;
  local_58[0xe] = 0;
  local_58[0xf] = 0;
  local_58[0x10] = 0;
  local_58[0x11] = 0;
  local_58[0x12] = 0;
  local_58[0x13] = 0;
  DAT_00450b9c = 0x46;
  DAT_00450ba8 = 0;
  DAT_00450bac = 0;
  DAT_0044fb6c = 0xffffffff;
  DAT_0044f880 = 0xffffffff;
  DAT_00450bc8 = 0;
  DAT_00450bc4 = 0;
  iVar5 = 0;
  piVar2 = (int *)(in_ECX + 0x194);
  do {
    if ((*(char *)(in_ECX + 4 + iVar5) != '\0') &&
       (*(int *)(*(int *)(*piVar2 + 0x368) + 0x6f8) == 0)) {
      iVar1 = FUN_00417170(0x10d,0x1e);
      *(int *)(*piVar2 + 0x10) = iVar1 + 0x32;
      *(double *)(*piVar2 + 0x58) = (double)*(int *)(*piVar2 + 0x10);
      *(int *)(*piVar2 + 0x300) = *(int *)(*piVar2 + 0x300) + (_DAT_00450c30 + 2) * 0x32;
      iVar1 = *piVar2;
      if (*(int *)(iVar1 + 0x304) < *(int *)(iVar1 + 0x300)) {
        *(undefined4 *)(iVar1 + 0x300) = *(undefined4 *)(iVar1 + 0x304);
      }
      *(undefined4 *)(*piVar2 + 0x2fc) = *(undefined4 *)(*piVar2 + 0x300);
      *(undefined4 *)(*piVar2 + 0x308) = 500;
      iVar1 = *piVar2;
      if ((8 < *(int *)(iVar1 + 0x70)) && (*(int *)(iVar1 + 0x70) < 0xc)) {
        *(undefined4 *)(iVar1 + 0x70) = 0;
      }
      iVar1 = *(int *)(*piVar2 + 0x70);
      if ((0xf < iVar1) && (iVar1 < 0x13)) {
        *(undefined4 *)(*piVar2 + 0x70) = 0xc;
      }
      iVar1 = FUN_00417170(0x10e,*(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d45db8 +
                                         DAT_0044d024 * 0x990) -
                                 *(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d45db4 +
                                         DAT_0044d024 * 0x990));
      *(int *)(*piVar2 + 0x18) =
           iVar1 + *(int *)(DAT_0044d024 * 0x990 + 0x4d45db4 + *(int *)(in_ECX + 0x7d4));
      *(double *)(*piVar2 + 0x68) = (double)*(int *)(*piVar2 + 0x18);
    }
    iVar5 = iVar5 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar5 < 400);
  piVar2 = (int *)(in_ECX + 0x194);
  iVar5 = 400;
  do {
    iVar4 = iVar5;
    *(undefined4 *)(*piVar2 + 0x3fc) = 0xfffffc18;
    iVar1 = *piVar2;
    piVar2 = piVar2 + 1;
    iVar5 = iVar4 + -1;
    *(undefined4 *)(iVar1 + 0x400) = 0xfffffc18;
  } while (iVar5 != 0);
  pcVar6 = (char *)(in_ECX + 0x18);
  piVar2 = (int *)(in_ECX + 0x1e4);
  iVar5 = 0x17c;
  do {
    if (((*pcVar6 == '\0') || (piVar3 = (int *)*piVar2, *(int *)(piVar3[0xda] + 0x6f8) < 1)) ||
       (piVar3[0x26] < 0)) {
      piVar3 = *(int **)(*piVar2 + 0x2f4);
      if ((-1 < (int)piVar3) && ((int)piVar3 < 0x14)) {
        if (iVar4 + 1 <= local_58[(int)piVar3]) goto LAB_004371fe;
        local_58[(int)piVar3] = local_58[(int)piVar3] + 1;
        piVar3 = local_58 + (int)piVar3;
      }
    }
    else {
LAB_004371fe:
      *pcVar6 = '\0';
    }
    piVar2 = piVar2 + 1;
    pcVar6 = pcVar6 + 1;
    iVar5 = iVar5 + -1;
    if (iVar5 == 0) {
      return piVar3;
    }
  } while( true );
}


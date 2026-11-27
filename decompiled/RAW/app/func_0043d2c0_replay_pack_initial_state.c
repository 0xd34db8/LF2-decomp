/* Function: FUN_0043d2c0 */
/* Address: 0x0043d2c0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043d2c0(undefined4 param_1,int param_2,int param_3)

{
  char cVar1;
  int *piVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int local_98;
  
  FUN_0043d280(&DAT_004588a8);
  DAT_004588a8 = calloc(1,0x630e18);
  DAT_00450b8c = 0;
  DAT_00450b80 = 1;
  *DAT_004588a8 = _DAT_00450c30;
  DAT_004588a8[2] = DAT_00458428;
  DAT_004588a8[3] = DAT_0045842c;
  DAT_004588a8[1] = DAT_00450b94;
  DAT_004588a8[0x52] = param_1;
  iVar6 = 0;
  do {
    pcVar3 = &DAT_0044fcc0 + iVar6;
    pcVar4 = (char *)(iVar6 + 0x14c + (int)DAT_004588a8);
    do {
      cVar1 = *pcVar3;
      *pcVar4 = cVar1;
      pcVar3 = pcVar3 + 1;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    iVar6 = iVar6 + 0xb;
  } while (iVar6 < 0x58);
  pcVar3 = &DAT_0044fd18;
  pcVar4 = (char *)(DAT_004588a8 + 0x18c2f0);
  do {
    cVar1 = *pcVar3;
    *pcVar4 = cVar1;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar3 = &DAT_0044f900;
  pcVar4 = (char *)(DAT_004588a8 + 0x18c309);
  do {
    cVar1 = *pcVar3;
    *pcVar4 = cVar1;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar3 = &DAT_0044f890;
  pcVar4 = (char *)(DAT_004588a8 + 0x18c36d);
  do {
    cVar1 = *pcVar3;
    *pcVar4 = cVar1;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  DAT_004588a8[0x69] = DAT_0044d024;
  pcVar3 = (char *)(param_2 + 1);
  piVar2 = (int *)(param_3 + 8);
  local_98 = 6;
  do {
    *(undefined4 *)((int)piVar2 + (0x1a0 - param_3) + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-2] + 0x364);
    *(undefined4 *)((int)piVar2 + (0x1e8 - param_3) + (int)DAT_004588a8) =
         *(undefined4 *)(*(int *)(piVar2[-2] + 0x368) + 0x6f4);
    *(int *)((0x230 - param_3) + (int)piVar2 + (int)DAT_004588a8) = (int)pcVar3[-1];
    *(undefined4 *)((0x278 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-2] + 8);
    *(undefined4 *)((0x2c0 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-2] + 0x10);
    *(undefined4 *)((0x308 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-2] + 0x14);
    *(undefined4 *)((0x350 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-2] + 0x18);
    *(undefined4 *)((0x398 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-2] + 0x308);
    *(undefined4 *)((0x3e0 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-2] + 0x354);
    *(undefined4 *)((0x428 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-2] + 0x304);
    *(undefined4 *)((0x470 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-2] + 0x33c);
    *(undefined4 *)((0x4b8 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-2] + 0x344);
    *(undefined4 *)((0x500 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-2] + 0x340);
    *(undefined4 *)((0x1a4 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-1] + 0x364);
    *(undefined4 *)((0x1ec - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*(int *)(piVar2[-1] + 0x368) + 0x6f4);
    *(int *)((0x234 - param_3) + (int)piVar2 + (int)DAT_004588a8) = (int)*pcVar3;
    *(undefined4 *)((0x27c - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-1] + 8);
    *(undefined4 *)((0x2c4 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-1] + 0x10);
    *(undefined4 *)((0x30c - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-1] + 0x14);
    *(undefined4 *)((0x354 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-1] + 0x18);
    *(undefined4 *)((0x39c - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-1] + 0x308);
    *(undefined4 *)((0x3e4 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-1] + 0x354);
    *(undefined4 *)((0x42c - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-1] + 0x304);
    *(undefined4 *)((0x474 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-1] + 0x33c);
    *(undefined4 *)((0x4bc - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-1] + 0x344);
    *(undefined4 *)((0x504 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(piVar2[-1] + 0x340);
    *(undefined4 *)((0x1a8 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*piVar2 + 0x364);
    *(undefined4 *)((0x1f0 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*(int *)(*piVar2 + 0x368) + 0x6f4);
    *(int *)((0x238 - param_3) + (int)piVar2 + (int)DAT_004588a8) = (int)pcVar3[1];
    *(undefined4 *)((0x280 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*piVar2 + 8);
    *(undefined4 *)((0x2c8 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*piVar2 + 0x10);
    *(undefined4 *)((0x310 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*piVar2 + 0x14);
    *(undefined4 *)((0x358 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*piVar2 + 0x18);
    *(undefined4 *)((0x3a0 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*piVar2 + 0x308);
    *(undefined4 *)((1000 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*piVar2 + 0x354);
    *(undefined4 *)((0x430 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*piVar2 + 0x304);
    *(undefined4 *)((0x478 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*piVar2 + 0x33c);
    *(undefined4 *)((0x4c0 - param_3) + (int)piVar2 + (int)DAT_004588a8) =
         *(undefined4 *)(*piVar2 + 0x344);
    iVar6 = *piVar2;
    iVar5 = (0x508 - param_3) + (int)piVar2;
    pcVar3 = pcVar3 + 3;
    piVar2 = piVar2 + 3;
    local_98 = local_98 + -1;
    *(undefined4 *)(iVar5 + (int)DAT_004588a8) = *(undefined4 *)(iVar6 + 0x340);
  } while (local_98 != 0);
  pcVar3 = &DAT_0044eed0;
  pcVar4 = (char *)(DAT_004588a8 + 0x154);
  do {
    cVar1 = *pcVar3;
    *pcVar4 = cVar1;
    pcVar3 = pcVar3 + 1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  DAT_004588a8[0x1d1] = DAT_0044f620;
  DAT_004588a8[0x1d2] = DAT_0044d03c;
  iVar6 = 0x74c;
  do {
    *(undefined4 *)(iVar6 + (int)DAT_004588a8) = *(undefined4 *)(&UNK_0044ceac + iVar6);
    *(undefined4 *)(iVar6 + 0x58 + (int)DAT_004588a8) = *(undefined4 *)(&UNK_0044cf04 + iVar6);
    *(undefined4 *)(iVar6 + 0xb0 + (int)DAT_004588a8) = *(undefined4 *)(&UNK_0044cf5c + iVar6);
    *(undefined4 *)(iVar6 + 0x108 + (int)DAT_004588a8) = *(undefined4 *)(&UNK_0044cfb4 + iVar6);
    iVar6 = iVar6 + 4;
  } while (iVar6 < 0x7a4);
  DAT_004588a8[0x231] = DAT_00450bcc;
  iVar6 = 0;
  do {
    *(undefined1 *)((int)DAT_004588a8 + iVar6 + 0x8c8) = (&DAT_0044ff90)[iVar6];
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0xbb9);
  DAT_004588a8[0x522] = DAT_0044d324;
  DAT_004588a8[0x523] = DAT_0044d328;
  DAT_004588a8[0x524] = DAT_0044d32c;
  DAT_004588a8[0x525] = DAT_0044d330;
  DAT_004588a8[0x526] = DAT_0044d334;
  DAT_004588a8[0x527] = DAT_0044d338;
  DAT_004588a8[0x528] = DAT_0044d33c;
  DAT_004588a8[0x529] = DAT_0044d340;
  DAT_004588a8[0x52a] = DAT_0044d344;
  DAT_004588a8[0x52b] = DAT_0044d348;
  DAT_004588a8[0x52c] = DAT_0044d34c;
  DAT_004588a8[0x52d] = DAT_00450b90;
  DAT_00450c34 = 0;
  DAT_00450bd0 = 0;
  DAT_00450bd4 = 0;
  DAT_00450bd8 = 0;
  return;
}


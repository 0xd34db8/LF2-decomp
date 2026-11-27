/* Function: FUN_0041b390 */
/* Address: 0x0041b390 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041b390(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  undefined4 *puVar5;
  char *pcVar6;
  undefined4 *puVar7;
  bool bVar8;
  
  iVar3 = 0x85;
  if (param_1 == 4) {
    iVar3 = 0x9b;
  }
  iVar1 = 10;
  bVar8 = true;
  pcVar4 = &DAT_0044fd18;
  pcVar6 = "<No name>";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar8 = *pcVar4 == *pcVar6;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  } while (bVar8);
  if (!bVar8) {
    DAT_00450f60 = 'A';
    DAT_00450f60_1._0_1_ = 'u';
    DAT_00450f60_1._1_1_ = 't';
    DAT_00450f60_1._2_1_ = 'h';
    DAT_00450f64 = 'o';
    DAT_00450f64_1._0_1_ = 'r';
    DAT_00450f64_1._1_1_ = ':';
    DAT_00450f64_1._2_1_ = '\0';
    FUN_00423a70(&DAT_00450f60,10,iVar3,0x40,1,0,0);
    FUN_00423a70(&DAT_0044fd18,0x4b,iVar3,0x40,1,0,0);
    iVar3 = iVar3 + 0x16;
  }
  iVar1 = 10;
  bVar8 = true;
  pcVar4 = &DAT_0044f900;
  pcVar6 = "<No info>";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar8 = *pcVar4 == *pcVar6;
    pcVar4 = pcVar4 + 1;
    pcVar6 = pcVar6 + 1;
  } while (bVar8);
  if (!bVar8) {
    DAT_00450f60 = ' ';
    DAT_00450f60_1._0_1_ = ' ';
    DAT_00450f60_1._1_1_ = 'I';
    DAT_00450f60_1._2_1_ = 'n';
    DAT_00450f64 = 'f';
    DAT_00450f64_1._0_1_ = 'o';
    DAT_00450f64_1._1_1_ = ':';
    DAT_00450f64_1._2_1_ = '\0';
    FUN_00423a70(&DAT_00450f60,10,iVar3,0x40,4,0,0);
    FUN_00423a70(&DAT_0044f900,0x4b,iVar3,0x40,4,0,0);
  }
  iVar3 = (param_3 + 0xf) / 0x1e;
  if (iVar3 < 0xe10) {
    sprintf(&DAT_00450e98,"%02d:%02d",iVar3 / 0x3c,iVar3 % 0x3c);
  }
  else {
    sprintf(&DAT_00450e98,"%02d:%02d:%02d",iVar3 / 0xe10,(iVar3 % 0xe10) / 0x3c,
            (iVar3 % 0xe10) % 0x3c);
  }
  iVar3 = (param_2 + 0xf) / 0x1e;
  if (iVar3 < 0xe10) {
    sprintf(&DAT_00450e30," / %02d:%02d",iVar3 / 0x3c,iVar3 % 0x3c);
  }
  else {
    sprintf(&DAT_00450e30," / %02d:%02d:%02d",iVar3 / 0xe10,(iVar3 % 0xe10) / 0x3c,
            (iVar3 % 0xe10) % 0x3c);
  }
  pcVar4 = &DAT_00450e30;
  do {
    pcVar6 = pcVar4;
    pcVar4 = pcVar6 + 1;
  } while (*pcVar6 != '\0');
  puVar7 = (undefined4 *)0x450e97;
  do {
    pcVar4 = (char *)((int)puVar7 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  } while (*pcVar4 != '\0');
  puVar5 = (undefined4 *)&DAT_00450e30;
  for (uVar2 = (uint)(pcVar6 + -0x450e2f) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar7 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar7 = puVar7 + 1;
  }
  for (uVar2 = (uint)(pcVar6 + -0x450e2f) & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *(undefined1 *)puVar7 = *(undefined1 *)puVar5;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  FUN_00423a70(&DAT_00450e98,5,0x1fe,0x40,4,0,0);
  return;
}


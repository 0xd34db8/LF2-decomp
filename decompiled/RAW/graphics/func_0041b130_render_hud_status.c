/* Function: FUN_0041b130 */
/* Address: 0x0041b130 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041b130(int param_1,int param_2)

{
  undefined4 *puVar1;
  char *pcVar2;
  undefined4 *puVar3;
  char *pcVar4;
  undefined4 uVar5;
  
  if (param_1 == 0) {
    DAT_00450c38._0_1_ = 'V';
    DAT_00450c38._1_1_ = 'S';
    DAT_00450c38._2_1_ = ' ';
    DAT_00450c38._3_1_ = 'm';
    DAT_00450c3c._0_1_ = 'o';
    DAT_00450c3c._1_1_ = 'd';
    DAT_00450c3c._2_1_ = 'e';
    DAT_00450c3c._3_1_ = ' ';
    DAT_00450c40 = DAT_00450c40 & 0xffffff00;
  }
  else if (param_1 == 1) {
    DAT_00450c38._0_1_ = 'S';
    DAT_00450c38._1_1_ = 't';
    DAT_00450c38._2_1_ = 'a';
    DAT_00450c38._3_1_ = 'g';
    DAT_00450c3c._0_1_ = 'e';
    DAT_00450c3c._1_1_ = ' ';
    DAT_00450c3c._2_1_ = 'm';
    DAT_00450c3c._3_1_ = 'o';
    DAT_00450c40._0_1_ = 'd';
    DAT_00450c40._1_1_ = 'e';
    DAT_00450c40._2_1_ = ' ';
    DAT_00450c40._3_1_ = '\0';
    if (DAT_00450b94 / 10 == 5) {
      DAT_00450c3c._0_1_ = 'i';
      DAT_00450c3c._1_1_ = 'v';
      DAT_00450c3c._2_1_ = 'a';
      DAT_00450c3c._3_1_ = 'l';
      DAT_00450c40._0_1_ = ' ';
      DAT_00450c40._1_1_ = 'S';
      DAT_00450c40._2_1_ = 't';
      DAT_00450c40._3_1_ = 'a';
      DAT_00450c38._0_1_ = 'S';
      DAT_00450c38._1_1_ = 'u';
      DAT_00450c38._2_1_ = 'r';
      DAT_00450c38._3_1_ = 'v';
      DAT_00450c44 = 'g';
      DAT_00450c44_1._0_1_ = 'e';
      DAT_00450c44_1._1_1_ = ' ';
      DAT_00450c44_1._2_1_ = '\0';
    }
  }
  else if (param_1 == 2) {
    DAT_00450c38._0_1_ = '1';
    DAT_00450c38._1_1_ = ' ';
    DAT_00450c38._2_1_ = 'o';
    DAT_00450c38._3_1_ = 'n';
    DAT_00450c3c._0_1_ = ' ';
    DAT_00450c3c._1_1_ = '1';
    DAT_00450c3c._2_1_ = ' ';
    DAT_00450c3c._3_1_ = '\0';
  }
  else if (param_1 == 3) {
    DAT_00450c38._0_1_ = '2';
    DAT_00450c38._1_1_ = ' ';
    DAT_00450c38._2_1_ = 'o';
    DAT_00450c38._3_1_ = 'n';
    DAT_00450c3c._0_1_ = ' ';
    DAT_00450c3c._1_1_ = '2';
    DAT_00450c3c._2_1_ = ' ';
    DAT_00450c3c._3_1_ = '\0';
  }
  else if (param_1 == 4) {
    DAT_00450c3c._0_1_ = 'l';
    DAT_00450c3c._1_1_ = 'e';
    DAT_00450c3c._2_1_ = ' ';
    DAT_00450c3c._3_1_ = 'm';
    DAT_00450c40._0_1_ = 'o';
    DAT_00450c40._1_1_ = 'd';
    DAT_00450c40._2_1_ = 'e';
    DAT_00450c40._3_1_ = ' ';
    DAT_00450c38._0_1_ = 'B';
    DAT_00450c38._1_1_ = 'a';
    DAT_00450c38._2_1_ = 't';
    DAT_00450c38._3_1_ = 't';
    _DAT_00450c44 = _DAT_00450c44 & 0xffffff00;
  }
  if (_DAT_00450c30 == 0) {
    pcVar2 = (char *)((int)&DAT_00450c34 + 3);
    do {
      pcVar4 = pcVar2;
      pcVar2 = pcVar4 + 1;
    } while (pcVar4[1] != '\0');
    builtin_strncpy(pcVar4 + 1,"(Difficult)",0xc);
    goto LAB_0041b309;
  }
  if (_DAT_00450c30 == 1) {
    pcVar2 = (char *)((int)&DAT_00450c34 + 3);
    do {
      pcVar4 = pcVar2;
      pcVar2 = pcVar4 + 1;
    } while (pcVar4[1] != '\0');
    uVar5._0_1_ = 'm';
    uVar5._1_1_ = 'a';
    uVar5._2_1_ = 'l';
    uVar5._3_1_ = ')';
    builtin_strncpy(pcVar4 + 1,"(Nor",4);
  }
  else {
    if (_DAT_00450c30 == 2) {
      puVar1 = (undefined4 *)((int)&DAT_00450c34 + 3);
      do {
        puVar3 = puVar1;
        puVar1 = (undefined4 *)((int)puVar3 + 1);
      } while (*(char *)((int)puVar3 + 1) != '\0');
      *(undefined4 *)((int)puVar3 + 1) = 0x73614528;
      *(undefined2 *)((int)puVar3 + 5) = 0x2979;
      *(undefined1 *)((int)puVar3 + 7) = 0;
      goto LAB_0041b309;
    }
    if (_DAT_00450c30 != -1) goto LAB_0041b309;
    pcVar2 = (char *)((int)&DAT_00450c34 + 3);
    do {
      pcVar4 = pcVar2;
      pcVar2 = pcVar4 + 1;
    } while (pcVar4[1] != '\0');
    uVar5._0_1_ = 'Z';
    uVar5._1_1_ = 'Y';
    uVar5._2_1_ = '!';
    uVar5._3_1_ = ')';
    builtin_strncpy(pcVar4 + 1,"(CRA",4);
  }
  *(undefined4 *)(pcVar2 + 4) = uVar5;
  pcVar2[8] = '\0';
LAB_0041b309:
  pcVar2 = (char *)&DAT_00450c38;
  if (param_2 == 0) {
    do {
      pcVar4 = pcVar2;
      pcVar2 = pcVar4 + 1;
    } while (*pcVar4 != '\0');
    FUN_00423a70(&DAT_00450c38,(int)(pcVar4 + -0x450c38) * -8 + 0x316,0x213,0x40,4,0,0);
    return;
  }
  do {
    pcVar4 = pcVar2;
    pcVar2 = pcVar4 + 1;
  } while (*pcVar4 != '\0');
  FUN_00423a70(&DAT_00450c38,(int)(pcVar4 + -0x450c38) * -8 + 0x316,0x1fe,0x40,4,0,0);
  return;
}

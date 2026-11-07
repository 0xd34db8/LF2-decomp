/* Function: FUN_00423940 */
/* Address: 0x00423940 */

void FUN_00423940(char *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = param_3;
  iVar4 = 0;
  iVar3 = 0;
  param_3 = 0;
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar5 = param_2;
  if (0 < (int)pcVar2 - (int)(param_1 + 1)) {
    do {
      if (param_5 <= iVar4) break;
      if (param_1[param_3] == '\n') {
        if (param_5 + -1 <= iVar4) break;
LAB_00423a0e:
        iVar6 = iVar6 + 0x10;
        iVar4 = iVar4 + 1;
        iVar3 = 0;
        iVar5 = param_2;
      }
      else {
        iVar3 = iVar3 + 1;
        if (((param_6 == 0) || (param_6 == 1)) || (param_6 == 2)) {
          FUN_0043f010(iVar5,iVar6,(int)param_1[param_3],1,0,DAT_00455608);
        }
        iVar5 = iVar5 + 8;
        if (param_4 <= iVar3) {
          if (iVar4 < param_5 + -1) goto LAB_00423a0e;
          param_3 = param_3 + 1;
          break;
        }
      }
      param_3 = param_3 + 1;
      pcVar2 = param_1;
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
    } while (param_3 < (int)pcVar2 - (int)(param_1 + 1));
  }
  param_1[param_3] = '\0';
  if (param_7 != 0) {
    FUN_0043f010(iVar5,iVar6,0x5f,1,0,DAT_00455608);
  }
  return;
}

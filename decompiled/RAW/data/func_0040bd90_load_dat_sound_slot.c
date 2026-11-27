/* Function: FUN_0040bd90 */
/* Address: 0x0040bd90 */

void FUN_0040bd90(byte *param_1,int *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  bool bVar7;
  
  iVar5 = 0;
  if (0 < DAT_00458438) {
    pbVar6 = &DAT_00455638;
    do {
      pbVar2 = param_1;
      pbVar4 = pbVar6;
      do {
        bVar1 = *pbVar2;
        bVar7 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_0040bdd4:
          iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_0040bdd9;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar2[1];
        bVar7 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_0040bdd4;
        pbVar2 = pbVar2 + 2;
        pbVar4 = pbVar4 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_0040bdd9:
      if (iVar3 == 0) {
        *param_2 = iVar5;
        break;
      }
      iVar5 = iVar5 + 1;
      pbVar6 = pbVar6 + 0x14;
    } while (iVar5 < DAT_00458438);
  }
  if (*param_2 == -1) {
    *param_2 = DAT_00458438;
    if (DAT_0044eecc != 0) {
      FUN_004014e0(param_1);
      (**(code **)(*(int *)(&DAT_00452948)[DAT_00458438] + 0x3c))
                ((int *)(&DAT_00452948)[DAT_00458438],0xffffd8f0);
    }
    iVar5 = DAT_00458438 * 0x14 - (int)param_1;
    do {
      bVar1 = *param_1;
      param_1[(int)(&DAT_00455638 + iVar5)] = bVar1;
      param_1 = param_1 + 1;
    } while (bVar1 != 0);
    DAT_00458438 = DAT_00458438 + 1;
  }
  return;
}


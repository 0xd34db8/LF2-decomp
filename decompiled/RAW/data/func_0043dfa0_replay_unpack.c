/*
 * Procedure: FUN_0043dfa0
 * Address: 0x0043dfa0 - 0x0043e61a (Length: 1638 bytes)
 * Purpose: Replay Playback State Unpacker & Global State Initializer
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void FUN_0043dfa0(int *param_1, char *param_2, int *param_3, int param_4)
{
  char *pcVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 *puVar8;
  char *pcVar9;
  int *piVar10;
  int iVar11;
  int local_8;

  DAT_0045877c = DAT_00450c30;
  iVar11 = 0;
  DAT_00450b8c = 0;
  DAT_00450b84 = 1;
  DAT_00450b88 = 1;
  _DAT_00450c30 = *DAT_004588ac;
  DAT_004588ac[0x18c2ee] = DAT_00458428;
  DAT_004588ac[0x18c2ef] = DAT_0045842c;
  DAT_00458428 = DAT_004588ac[2];
  DAT_0045842c = DAT_004588ac[3];
  DAT_00450b94 = DAT_004588ac[1];
  *param_1 = DAT_004588ac[0x52];
  pcVar9 = (char *)(DAT_004588ac + 0x53);
  do
  {
    pcVar1 = &DAT_0044fcc0 + iVar11;
    pcVar5 = pcVar1;
    do
    {
      cVar2 = *pcVar5;
      pcVar5[(int)(&DAT_00458850 + (iVar11 - (int)pcVar1))] = cVar2;
      pcVar5 = pcVar5 + 1;
    } while (cVar2 != '\0');
    pcVar5 = pcVar9;
    do
    {
      cVar2 = *pcVar5;
      pcVar5[(int)pcVar1 - (int)pcVar9] = cVar2;
      pcVar5 = pcVar5 + 1;
    } while (cVar2 != '\0');
    iVar11 = iVar11 + 0xb;
    pcVar9 = pcVar9 + 0xb;
  } while (iVar11 < 0x58);
  iVar11 = 0;
  do
  {
    pcVar9 = &DAT_0044fd18 + iVar11;
    (&DAT_004587e8)[iVar11] = *pcVar9;
    puVar6 = DAT_004588ac;
    iVar11 = iVar11 + 1;
  } while (*pcVar9 != '\0');
  pcVar9 = (char *)(DAT_004588ac + 0x18c2f0);
  iVar11 = (int)&DAT_0044fd18 - (int)pcVar9;
  do
  {
    cVar2 = *pcVar9;
    pcVar9[iVar11] = cVar2;
    pcVar9 = pcVar9 + 1;
  } while (cVar2 != '\0');
  iVar11 = 0;
  do
  {
    pcVar9 = &DAT_0044f900 + iVar11;
    (&DAT_00458588)[iVar11] = *pcVar9;
    iVar11 = iVar11 + 1;
  } while (*pcVar9 != '\0');
  pcVar9 = (char *)(puVar6 + 0x18c309);
  iVar11 = (int)&DAT_0044f900 - (int)pcVar9;
  do
  {
    cVar2 = *pcVar9;
    pcVar9[iVar11] = cVar2;
    pcVar9 = pcVar9 + 1;
  } while (cVar2 != '\0');
  *(undefined1 *)((int)puVar6 + 0x630e17) = 0;
  iVar11 = 0;
  do
  {
    pcVar9 = &DAT_0044f890 + iVar11;
    (&DAT_00458780)[iVar11] = *pcVar9;
    puVar6 = DAT_004588ac;
    iVar11 = iVar11 + 1;
  } while (*pcVar9 != '\0');
  pcVar9 = (char *)(DAT_004588ac + 0x18c36d);
  iVar11 = (int)&DAT_0044f890 - (int)pcVar9;
  do
  {
    cVar2 = *pcVar9;
    pcVar9[iVar11] = cVar2;
    pcVar9 = pcVar9 + 1;
  } while (cVar2 != '\0');
  DAT_0044d024 = puVar6[0x69];
  memset(param_2, 0, 400);
  local_8 = 0;
  puVar6 = DAT_004588ac;
  piVar10 = param_3;
  do
  {
    iVar11 = (0x238 - (int)param_3) + (int)piVar10;
    if (*(int *)(iVar11 + (int)puVar6) != 0)
    {
      iVar7 = 0;
      if (0 < *(int *)(param_4 + 0x4d82380))
      {
        do
        {
          if (*(int *)(*(int *)(param_4 + iVar7 * 4) + 0x6f4) ==
              *(int *)(iVar11 + -0x48 + (int)puVar6))
          {
            iVar7 = *(int *)(param_4 + iVar7 * 4);
            if (iVar7 != 0)
            {
              iVar3 = *piVar10;
              FUN_004061d0();
              *(int *)(iVar3 + 0x368) = iVar7;
              uVar4 = *(undefined4 *)(iVar7 + 0x90);
              *(undefined8 *)(iVar3 + 0x58) = 0x4075e00000000000;
              *(undefined4 *)(iVar3 + 0x31c) = uVar4;
              *(undefined8 *)(iVar3 + 0x60) = 0;
              *(undefined8 *)(iVar3 + 0x68) = 0x4072c00000000000;
              puVar6 = DAT_004588ac;
            }
            break;
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 < *(int *)(param_4 + 0x4d82380));
      }
      *(undefined4 *)(*piVar10 + 0x364) = *(undefined4 *)(iVar11 + -0x90 + (int)puVar6);
      param_2[local_8] = *(char *)(iVar11 + (int)DAT_004588ac);
      *(undefined4 *)(*piVar10 + 8) = *(undefined4 *)(iVar11 + 0x48 + (int)DAT_004588ac);
      *(undefined4 *)(*piVar10 + 0x10) = *(undefined4 *)(iVar11 + 0x90 + (int)DAT_004588ac);
      *(undefined4 *)(*piVar10 + 0x14) = *(undefined4 *)(iVar11 + 0xd8 + (int)DAT_004588ac);
      *(undefined4 *)(*piVar10 + 0x18) = *(undefined4 *)(iVar11 + 0x120 + (int)DAT_004588ac);
      *(double *)(*piVar10 + 0x58) = (double)*(int *)(*piVar10 + 0x10);
      *(double *)(*piVar10 + 0x68) = (double)*(int *)(*piVar10 + 0x18);
      *(undefined4 *)(*piVar10 + 0x308) = *(undefined4 *)(iVar11 + 0x168 + (int)DAT_004588ac);
      *(undefined4 *)(*piVar10 + 0x354) = *(undefined4 *)(iVar11 + 0x1b0 + (int)DAT_004588ac);
      *(undefined4 *)(*piVar10 + 0x304) = *(undefined4 *)(iVar11 + 0x1f8 + (int)DAT_004588ac);
      *(undefined4 *)(*piVar10 + 0x300) = *(undefined4 *)(*piVar10 + 0x304);
      *(undefined4 *)(*piVar10 + 0x2fc) = *(undefined4 *)(*piVar10 + 0x300);
      *(undefined4 *)(*piVar10 + 0x33c) = *(undefined4 *)(iVar11 + 0x240 + (int)DAT_004588ac);
      *(undefined4 *)(*piVar10 + 0x344) = *(undefined4 *)(iVar11 + 0x288 + (int)DAT_004588ac);
      *(undefined4 *)(*piVar10 + 0x340) = *(undefined4 *)(iVar11 + 0x2d0 + (int)DAT_004588ac);
      puVar6 = DAT_004588ac;
    }
    local_8 = local_8 + 1;
    piVar10 = piVar10 + 1;
    if (0x11 < local_8)
    {
      DAT_00450c24 = 0;
      DAT_00450c20 = 0;
      DAT_00450c1c = 0;
      DAT_00450c18 = 0;
      _DAT_00450c14 = 0;
      _DAT_00450c10 = 0;
      _DAT_00450c0c = 0;
      _DAT_00450c08 = 0;
      _DAT_00450c04 = 0;
      DAT_00450c28 = 0;
      iVar11 = 0;
      if (0 < *(int *)(param_4 + 0x4d82384))
      {
        do
        {
          FUN_0040c0e0(iVar11);
          iVar11 = iVar11 + 1;
        } while (iVar11 < *(int *)(param_4 + 0x4d82384));
        puVar6 = DAT_004588ac;
      }
      if (DAT_0044d024 != 99)
      {
        FUN_0040c030(DAT_0044d024);
        puVar6 = DAT_004588ac;
      }
      pcVar9 = (char *)(puVar6 + 0x154);
      iVar11 = (int)&DAT_0044eed0 - (int)pcVar9;
      do
      {
        cVar2 = *pcVar9;
        pcVar9[iVar11] = cVar2;
        pcVar9 = pcVar9 + 1;
      } while (cVar2 != '\0');
      puVar8 = puVar6 + 0x1e9;
      iVar11 = 0;
      do
      {
        *(undefined4 *)((int)&DAT_0044d5f8 + iVar11) = puVar8[-0x16];
        *(undefined4 *)((int)&DAT_0044d650 + iVar11) = *puVar8;
        *(undefined4 *)((int)&DAT_0044d6a8 + iVar11) = puVar8[0x16];
        *(undefined4 *)((int)&DAT_0044d700 + iVar11) = puVar8[0x2c];
        iVar11 = iVar11 + 4;
        puVar8 = puVar8 + 1;
      } while (iVar11 < 0x58);
      DAT_00450bcc = puVar6[0x231];
      iVar11 = 0;
      do
      {
        (&DAT_0044ff90)[iVar11] = *(undefined1 *)((int)puVar6 + iVar11 + 0x8c8);
        iVar11 = iVar11 + 1;
      } while (iVar11 < 0xbb9);
      DAT_0044d324 = puVar6[0x522];
      DAT_0044d328 = puVar6[0x523];
      DAT_0044d32c = puVar6[0x524];
      DAT_0044d330 = puVar6[0x525];
      DAT_0044d334 = puVar6[0x526];
      DAT_0044d338 = puVar6[0x527];
      DAT_0044d33c = puVar6[0x528];
      DAT_0044d340 = puVar6[0x529];
      DAT_0044d344 = puVar6[0x52a];
      DAT_0044d348 = puVar6[0x52b];
      DAT_0044d34c = puVar6[0x52c];
      DAT_00450b90 = puVar6[0x52d];
      DAT_0044d034 = 1;
      DAT_00450bbc = 0;
      if (*param_1 != 1)
      {
        FUN_004025b0();
      }
      DAT_00450bb0 = 0;
      DAT_00450bb4 = 0;
      if (*param_1 == 1)
      {
        DAT_00450b9c = 0x46;
        DAT_00450ba8 = 0;
        DAT_00450bac = 0;
        DAT_00450ba4 = 0;
        DAT_0044fb6c = 0xffffffff;
        DAT_0044f880 = 0xffffffff;
        DAT_00450bc8 = 0;
        DAT_00450bc4 = 0;
      }
      iVar11 = 0;
      do
      {
        if (param_2[iVar11] == '\0')
        {
          FUN_004061d0();
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < 400);
      if ((param_2[10] == '\0') && (*param_2 == '\0'))
      {
        *(undefined4 *)(*param_3 + 0x364) = *(undefined4 *)(param_3[10] + 0x364);
        \r
      }
      if ((param_2[0xb] == '\0') && (param_2[1] == '\0'))
      {
        *(undefined4 *)(param_3[1] + 0x364) = *(undefined4 *)(param_3[0xb] + 0x364);
        \r
      }
      if ((param_2[0xc] == '\0') && (param_2[2] == '\0'))
      {
        *(undefined4 *)(param_3[2] + 0x364) = *(undefined4 *)(param_3[0xc] + 0x364);
        \r
      }
      if ((param_2[0xd] == '\0') && (param_2[3] == '\0'))
      {
        *(undefined4 *)(param_3[3] + 0x364) = *(undefined4 *)(param_3[0xd] + 0x364);
        \r
      }
      if ((param_2[0xe] == '\0') && (param_2[4] == '\0'))
      {
        *(undefined4 *)(param_3[4] + 0x364) = *(undefined4 *)(param_3[0xe] + 0x364);
        \r
      }
      if ((param_2[0xf] == '\0') && (param_2[5] == '\0'))
      {
        *(undefined4 *)(param_3[5] + 0x364) = *(undefined4 *)(param_3[0xf] + 0x364);
        \r
      }
      if ((param_2[0x10] == '\0') && (param_2[6] == '\0'))
      {
        *(undefined4 *)(param_3[6] + 0x364) = *(undefined4 *)(param_3[0x10] + 0x364);
        \r
      }
      if ((param_2[0x11] == '\0') && (param_2[7] == '\0'))
      {
        *(undefined4 *)(param_3[7] + 0x364) = *(undefined4 *)(param_3[0x11] + 0x364);
        \r
      }
      DAT_00450c34 = 0;
      DAT_00450bd0 = 0;
      DAT_00450bd4 = 0;
      DAT_00450bd8 = 0;
      return;
    }
  } while (true);
}

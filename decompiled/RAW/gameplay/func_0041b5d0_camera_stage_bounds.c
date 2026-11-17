/* Function: FUN_0041b5d0 */
/* Address: 0x0041b5d0 */

void FUN_0041b5d0(undefined4 param_1,int param_2)

{
  double dVar1;
  undefined4 uVar2;
  int *piVar3;
  int in_ECX;
  int *piVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  int *piVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  float10 fVar15;
  float10 extraout_ST0;
  float10 extraout_ST1;
  float10 extraout_ST1_00;
  float10 fVar16;
  int local_14;
  
  iVar6 = DAT_0044d024;
  fVar15 = (float10)1;
  fVar12 = (float10)-100.0;
  fVar13 = (float10)100.0;
  fVar16 = (float10)0;
  local_14 = 0;
  pcVar7 = (char *)(in_ECX + 4);
  piVar4 = (int *)(in_ECX + 0x194);
  do {
    if (*pcVar7 != '\0') {
      iVar10 = *piVar4;
      iVar8 = iVar6 * 0x990;
      iVar5 = *(int *)(iVar8 + 0x4d45db4 + *(int *)(in_ECX + 0x7d4));
      fVar14 = (float10)iVar5;
      if (*(int *)(*(int *)(iVar10 + 0x368) + 0x6f8) == 0) {
        if ((float10)*(double *)(iVar10 + 0x68) < fVar14) {
          *(double *)(iVar10 + 0x68) = (double)iVar5;
        }
        fVar15 = (float10)*(int *)(iVar8 + 0x4d45db8 + *(int *)(in_ECX + 0x7d4));
      }
      else {
        fVar14 = fVar14 - fVar15;
        if (fVar14 <= (float10)*(double *)(iVar10 + 0x68)) {
          fVar15 = (float10)*(int *)(iVar8 + 0x4d45db8 + *(int *)(in_ECX + 0x7d4)) + fVar15;
        }
        else {
          *(double *)(iVar10 + 0x68) = (double)fVar14;
          fVar15 = (float10)*(int *)(iVar8 + 0x4d45db8 + *(int *)(in_ECX + 0x7d4)) + fVar15;
        }
      }
      if (fVar15 < (float10)*(double *)(*piVar4 + 0x68)) {
        *(double *)(*piVar4 + 0x68) = (double)fVar15;
      }
      iVar5 = *piVar4;
      uVar2 = FUN_004450d0();
      *(undefined4 *)(iVar5 + 0x18) = uVar2;
      iVar5 = *piVar4;
      iVar10 = *(int *)(*(int *)(iVar5 + 0x368) + 0x6f8);
      if (iVar10 == 3) {
        if ((float10)*(double *)(iVar5 + 0x58) < fVar12) {
          *pcVar7 = '\0';
        }
        if ((double)*(int *)(iVar8 + 0x4d45db0 + *(int *)(in_ECX + 0x7d4)) + 300.0 <
            *(double *)(*piVar4 + 0x58)) {
          *pcVar7 = '\0';
        }
      }
      else if (iVar10 == 0) {
        if ((int)(pcVar7 + (-4 - in_ECX)) < 0x14) {
          if (*(int *)(iVar5 + 0x364) == 5) {
            if ((float10)*(double *)(iVar5 + 0x58) < fVar12) {
              *(double *)(iVar5 + 0x58) = (double)fVar12;
            }
          }
          else if ((float10)*(double *)(iVar5 + 0x58) < extraout_ST1) {
            *(double *)(iVar5 + 0x58) = (double)extraout_ST1;
          }
          dVar1 = (double)*(int *)(iVar8 + 0x4d45db0 + *(int *)(in_ECX + 0x7d4));
          if (dVar1 < *(double *)(*piVar4 + 0x58)) {
            *(double *)(*piVar4 + 0x58) = dVar1;
          }
        }
        else {
          if ((float10)*(double *)(iVar5 + 0x58) < fVar13) {
            *(double *)(iVar5 + 0x58) = (double)fVar13;
          }
          fVar15 = (float10)*(int *)(iVar8 + 0x4d45db0 + *(int *)(in_ECX + 0x7d4)) + fVar16;
          if (fVar15 < (float10)*(double *)(*piVar4 + 0x58)) {
            *(double *)(*piVar4 + 0x58) = (double)fVar15;
          }
        }
        if (0 < DAT_00450bb4) {
          iVar5 = *piVar4;
          if ((((double)DAT_00450bb4 < *(double *)(iVar5 + 0x58)) && (*(int *)(iVar5 + 0x364) != 5))
             && (*(int *)(iVar5 + 8) == 0)) {
            *(double *)(iVar5 + 0x58) = (double)DAT_00450bb4;
          }
        }
      }
      else {
        iVar10 = *(int *)(*(int *)(iVar5 + 0x368) + 0x6f4);
        if (((iVar10 == 0x7a) || (iVar10 == 0x7b)) &&
           ((0 < *(int *)(iVar5 + 0x344) || ((param_2 == 1 && (DAT_00450b94 / 10 == 5)))))) {
          if ((float10)*(double *)(iVar5 + 0x58) < extraout_ST0) {
            *(double *)(iVar5 + 0x58) = (double)extraout_ST0;
          }
          fVar15 = (float10)*(int *)(iVar8 + 0x4d45db0 + *(int *)(in_ECX + 0x7d4)) - extraout_ST0;
          if (fVar15 < (float10)*(double *)(*piVar4 + 0x58)) {
            *(double *)(*piVar4 + 0x58) = (double)fVar15;
          }
        }
        else {
          if (((float10)*(double *)(iVar5 + 0x58) < extraout_ST1) && (*(int *)(iVar5 + 0x14) == 0))
          {
            *pcVar7 = '\0';
          }
          if (((double)*(int *)(iVar8 + 0x4d45db0 + *(int *)(in_ECX + 0x7d4)) <
               *(double *)(*piVar4 + 0x58)) && (*(int *)(*piVar4 + 0x14) == 0)) {
            *pcVar7 = '\0';
          }
        }
      }
      iVar5 = *piVar4;
      fVar13 = extraout_ST1;
      fVar12 = fVar16;
      fVar15 = extraout_ST0;
      uVar2 = FUN_004450d0();
      *(undefined4 *)(iVar5 + 0x10) = uVar2;
      fVar16 = extraout_ST1_00;
    }
    iVar5 = 0;
    pcVar7 = pcVar7 + 1;
    piVar4 = piVar4 + 1;
  } while ((int)(pcVar7 + (-4 - in_ECX)) < 400);
  pcVar7 = (char *)(in_ECX + 5);
  piVar4 = (int *)(in_ECX + 0x198);
  piVar11 = &DAT_00450b50;
  param_2 = 2;
  piVar3 = piVar4;
  pcVar9 = pcVar7;
  do {
    if (((pcVar9[-1] != '\0') && (0 < piVar11[-1])) &&
       (iVar10 = piVar3[-1], 0 < *(int *)(iVar10 + 0x2fc))) {
      if (*(int *)(*(int *)(iVar10 + 0x368) + 0x7ac + *(int *)(iVar10 + 0x70) * 0x178) == 0xe) {
        iVar5 = iVar5 + *(int *)(iVar10 + 0x10);
      }
      else {
        iVar5 = iVar5 + 0x82 + *(int *)(iVar10 + 0x10) + *(char *)(iVar10 + 0x80) * -0x104;
      }
      local_14 = local_14 + 1;
    }
    if (((*pcVar9 != '\0') && (0 < *piVar11)) && (iVar10 = *piVar3, 0 < *(int *)(iVar10 + 0x2fc))) {
      if (*(int *)(*(int *)(iVar10 + 0x368) + 0x7ac + *(int *)(iVar10 + 0x70) * 0x178) == 0xe) {
        iVar5 = iVar5 + *(int *)(iVar10 + 0x10);
      }
      else {
        iVar5 = iVar5 + 0x82 + *(int *)(iVar10 + 0x10) + *(char *)(iVar10 + 0x80) * -0x104;
      }
      local_14 = local_14 + 1;
    }
    if (((pcVar9[1] != '\0') && (0 < piVar11[1])) &&
       (iVar10 = piVar3[1], 0 < *(int *)(iVar10 + 0x2fc))) {
      if (*(int *)(*(int *)(iVar10 + 0x368) + 0x7ac + *(int *)(iVar10 + 0x70) * 0x178) == 0xe) {
        iVar5 = iVar5 + *(int *)(iVar10 + 0x10);
      }
      else {
        iVar5 = iVar5 + 0x82 + *(int *)(iVar10 + 0x10) + *(char *)(iVar10 + 0x80) * -0x104;
      }
      local_14 = local_14 + 1;
    }
    if (((pcVar9[2] != '\0') && (0 < piVar11[2])) &&
       (iVar10 = piVar3[2], 0 < *(int *)(iVar10 + 0x2fc))) {
      if (*(int *)(*(int *)(iVar10 + 0x368) + 0x7ac + *(int *)(iVar10 + 0x70) * 0x178) == 0xe) {
        iVar5 = iVar5 + *(int *)(iVar10 + 0x10);
      }
      else {
        iVar5 = iVar5 + 0x82 + *(int *)(iVar10 + 0x10) + *(char *)(iVar10 + 0x80) * -0x104;
      }
      local_14 = local_14 + 1;
    }
    pcVar9 = pcVar9 + 4;
    piVar11 = piVar11 + 4;
    piVar3 = piVar3 + 4;
    param_2 = param_2 + -1;
  } while (param_2 != 0);
  if (local_14 == 0) {
    iVar10 = 0x50;
    do {
      if (((pcVar7[-1] != '\0') &&
          (iVar8 = piVar4[-1], *(int *)(*(int *)(iVar8 + 0x368) + 0x6f8) == 0)) &&
         (0 < *(int *)(iVar8 + 0x2fc))) {
        iVar5 = iVar5 + *(int *)(iVar8 + 0x10);
        local_14 = local_14 + 1;
      }
      if (((*pcVar7 != '\0') && (iVar8 = *piVar4, *(int *)(*(int *)(iVar8 + 0x368) + 0x6f8) == 0))
         && (0 < *(int *)(iVar8 + 0x2fc))) {
        iVar5 = iVar5 + *(int *)(iVar8 + 0x10);
        local_14 = local_14 + 1;
      }
      if (((pcVar7[1] != '\0') &&
          (iVar8 = piVar4[1], *(int *)(*(int *)(iVar8 + 0x368) + 0x6f8) == 0)) &&
         (0 < *(int *)(iVar8 + 0x2fc))) {
        iVar5 = iVar5 + *(int *)(iVar8 + 0x10);
        local_14 = local_14 + 1;
      }
      if (((pcVar7[2] != '\0') &&
          (iVar8 = piVar4[2], *(int *)(*(int *)(iVar8 + 0x368) + 0x6f8) == 0)) &&
         (0 < *(int *)(iVar8 + 0x2fc))) {
        iVar5 = iVar5 + *(int *)(iVar8 + 0x10);
        local_14 = local_14 + 1;
      }
      if (((pcVar7[3] != '\0') &&
          (iVar8 = piVar4[3], *(int *)(*(int *)(iVar8 + 0x368) + 0x6f8) == 0)) &&
         (0 < *(int *)(iVar8 + 0x2fc))) {
        iVar5 = iVar5 + *(int *)(iVar8 + 0x10);
        local_14 = local_14 + 1;
      }
      piVar4 = piVar4 + 5;
      pcVar7 = pcVar7 + 5;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    if (local_14 == 0) {
      iVar5 = 800;
      local_14 = 1;
    }
  }
  iVar5 = iVar5 / local_14 + -0x18d;
  if (iVar5 < 0) {
    iVar5 = 0;
  }
  iVar6 = iVar6 * 0x990;
  iVar10 = *(int *)(iVar6 + 0x4d45db0 + *(int *)(in_ECX + 0x7d4)) + -0x31a;
  if (iVar10 < iVar5) {
    iVar5 = iVar10;
  }
  if ((DAT_00450bb0 != 0) && (DAT_00450bb0 < iVar5)) {
    iVar5 = DAT_00450bb0;
  }
  DAT_00450bc8 = ((iVar5 - DAT_00450bc4) / 0xe + DAT_00450bc8 * 6) / 7;
  if (DAT_00450bc8 == 0) {
    if (DAT_00450bc4 < iVar5) {
      DAT_00450bc8 = 1;
    }
    else if (iVar5 < DAT_00450bc4) {
      DAT_00450bc8 = -1;
    }
  }
  DAT_00450bc4 = DAT_00450bc4 + DAT_00450bc8;
  if ((DAT_00450b74 != 0) && (DAT_00450b84 != 0)) {
    DAT_00450bc4 = DAT_00450b7c;
  }
  if (DAT_00450bc4 < 0) {
    DAT_00450bc4 = 0;
  }
  iVar6 = *(int *)(iVar6 + 0x4d45db0 + *(int *)(in_ECX + 0x7d4)) + -0x31a;
  if (iVar6 < DAT_00450bc4) {
    DAT_00450bc4 = iVar6;
  }
  if ((DAT_00450b74 != 0) && (DAT_00450b84 != 0)) {
    DAT_00450b7c = DAT_00450bc4;
  }
  FUN_0041a250(param_1);
  return;
}

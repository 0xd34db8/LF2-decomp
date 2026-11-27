/* Function: FUN_0040c160 */
/* Address: 0x0040c160 */

void FUN_0040c160(int param_1,undefined4 param_2,char *param_3)

{
  uint *puVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  undefined4 uVar6;
  FILE *pFVar7;
  int in_ECX;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  bool bVar12;
  undefined4 local_e8;
  int local_e4;
  int local_e0;
  void *local_dc;
  char local_d8 [100];
  char local_74 [29];
  undefined1 local_57;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00445c8e;
  local_c = ExceptionList;
  local_10 = DAT_0044eea4 ^ (uint)&local_e8;
  ExceptionList = &local_c;
  pcVar5 = param_3 + 1;
  pcVar3 = param_3;
  do {
    cVar2 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar2 != '\0');
  local_e4 = in_ECX;
  if ((((param_3[(int)(pcVar3 + (-3 - (int)pcVar5))] == 'd') ||
       (param_3[(int)(pcVar3 + (-3 - (int)pcVar5))] == 'D')) &&
      ((param_3[(int)(pcVar3 + (-2 - (int)pcVar5))] == 'a' ||
       (param_3[(int)(pcVar3 + (-2 - (int)pcVar5))] == 'A')))) &&
     ((param_3[(int)(pcVar3 + (-1 - (int)pcVar5))] == 't' ||
      (param_3[(int)(pcVar3 + (-1 - (int)pcVar5))] == 'T')))) {
    FUN_004148a0(param_3,DAT_0044eea4 ^ (uint)(local_d8 + -0x20));
    local_e8 = fopen("data\\temporary.txt","r");
  }
  else {
    local_e8 = fopen(param_3,"r");
  }
  pFVar7 = local_e8;
  local_e0 = param_1 * 0x990;
  iVar9 = local_e0 + in_ECX;
  *(undefined4 *)(iVar9 + 0x4d45dcc) = 0;
  *(undefined4 *)(iVar9 + 0x4d45dbc) = 0;
  *(undefined4 *)(iVar9 + 0x4d45dc0) = 0;
  iVar4 = feof(local_e8);
  do {
    if (iVar4 != 0) {
      fclose(pFVar7);
      pFVar7 = fopen("data\\temporary.txt","w");
      fprintf(pFVar7,"Do not erase this file.");
      fclose(pFVar7);
      ExceptionList = local_c;
      __security_check_cookie(local_10 ^ (uint)&local_e8);
      return;
    }
    fscanf(pFVar7,"%s",local_d8);
    pcVar5 = local_d8;
    uVar11 = 0;
    do {
      cVar2 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar2 != '\0');
    if (pcVar5 != local_d8 + 1) {
      do {
        pcVar5 = local_d8;
        DAT_0044f620 = DAT_0044f620 + (int)local_d8[uVar11] * uVar11;
        uVar11 = uVar11 + 1;
        do {
          cVar2 = *pcVar5;
          pcVar5 = pcVar5 + 1;
        } while (cVar2 != '\0');
      } while (uVar11 < (uint)((int)pcVar5 - (int)(local_d8 + 1)));
    }
    iVar4 = 6;
    bVar12 = true;
    pcVar5 = local_d8;
    pcVar3 = "name:";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar12 = *pcVar5 == *pcVar3;
      pcVar5 = pcVar5 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar12);
    if (bVar12) {
      fscanf(pFVar7,"%s",local_74);
      pcVar5 = local_74;
      local_57 = 0;
      iVar4 = 0;
      do {
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
      if (0 < (int)pcVar5 - (int)(local_74 + 1)) {
        do {
          if (local_74[iVar4] == '_') {
            local_74[iVar4] = ' ';
          }
          pcVar5 = local_74;
          iVar4 = iVar4 + 1;
          do {
            cVar2 = *pcVar5;
            pcVar5 = pcVar5 + 1;
          } while (cVar2 != '\0');
        } while (iVar4 < (int)pcVar5 - (int)(local_74 + 1));
      }
      pcVar5 = local_74;
      iVar4 = iVar9 - (int)pcVar5;
      do {
        cVar2 = *pcVar5;
        pcVar5[iVar4 + 0x4d4617c] = cVar2;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
    }
    iVar4 = 7;
    bVar12 = true;
    pcVar5 = local_d8;
    pcVar3 = "width:";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar12 = *pcVar5 == *pcVar3;
      pcVar5 = pcVar5 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar12);
    if (bVar12) {
      fscanf(pFVar7,"%d",iVar9 + 0x4d45db0);
    }
    iVar4 = 0xb;
    bVar12 = true;
    pcVar5 = local_d8;
    pcVar3 = "zboundary:";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar12 = *pcVar5 == *pcVar3;
      pcVar5 = pcVar5 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar12);
    if (bVar12) {
      fscanf(pFVar7,"%d %d",iVar9 + 0x4d45db4,iVar9 + 0x4d45db8);
    }
    iVar4 = 0xd;
    bVar12 = true;
    pcVar5 = local_d8;
    pcVar3 = "perspective:";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar12 = *pcVar5 == *pcVar3;
      pcVar5 = pcVar5 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar12);
    if (bVar12) {
      fscanf(pFVar7,"%d %d",iVar9 + 0x4d45dbc,iVar9 + 0x4d45dc0);
    }
    iVar4 = 8;
    bVar12 = true;
    pcVar5 = local_d8;
    pcVar3 = "shadow:";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar12 = *pcVar5 == *pcVar3;
      pcVar5 = pcVar5 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar12);
    if (bVar12) {
      fscanf(pFVar7,"%s %s %d %d",iVar9 + 0x4d46154,local_74,iVar9 + 0x4d45dc4,iVar9 + 0x4d45dc8);
      local_dc = operator_new(0x1f50);
      local_4 = 0;
      if (local_dc == (void *)0x0) {
        uVar6 = 0;
      }
      else {
        uVar6 = FUN_0043ee50(0x40,iVar9 + 0x4d46154,0);
      }
      local_4 = 0xffffffff;
      *(undefined4 *)(iVar9 + 0x4d4673c) = uVar6;
    }
    iVar4 = 7;
    bVar12 = true;
    pcVar5 = local_d8;
    pcVar3 = "layer:";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar12 = *pcVar5 == *pcVar3;
      pcVar5 = pcVar5 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar12);
    if (bVar12) {
      fscanf(pFVar7,"%s",local_e0 + *(int *)(iVar9 + 0x4d45dcc) * 0x1e + 0x4d45dd0 + local_e4);
      iVar10 = param_1 * 0x264;
      *(undefined4 *)(local_e4 + 0x4d4664c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      *(undefined4 *)(local_e4 + 0x4d4628c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      *(undefined4 *)(local_e4 + 0x4d46304 + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      *(undefined4 *)(local_e4 + 0x4d46214 + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      *(undefined4 *)(local_e4 + 0x4d4637c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      *(undefined4 *)(local_e4 + 0x4d463f4 + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      *(undefined4 *)(local_e4 + 0x4d4619c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      *(undefined4 *)(local_e4 + 0x4d4655c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      *(undefined4 *)(local_e4 + 0x4d4646c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      *(undefined4 *)(local_e4 + 0x4d464e4 + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      *(undefined4 *)(local_e4 + 0x4d465d4 + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      *(undefined4 *)(local_e4 + 0x4d466c4 + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4) = 0;
      fscanf(local_e8,"%s",local_d8);
      iVar4 = 10;
      bVar12 = true;
      pcVar5 = local_d8;
      pcVar3 = "layer_end";
      do {
        pFVar7 = local_e8;
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar12 = *pcVar5 == *pcVar3;
        pcVar5 = pcVar5 + 1;
        pcVar3 = pcVar3 + 1;
      } while (bVar12);
joined_r0x0040c58d:
      local_e8 = pFVar7;
      if (!bVar12) {
        iVar4 = 0xe;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "transparency:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        if (bVar12) {
          fscanf(pFVar7,"%d",local_e4 + 0x4d4619c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
        }
        iVar4 = 7;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "width:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        if (bVar12) {
          fscanf(local_e8,"%d",local_e4 + 0x4d46214 + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
        }
        iVar4 = 3;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "x:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        if (bVar12) {
          fscanf(local_e8,"%d",local_e4 + 0x4d4628c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
        }
        iVar4 = 3;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "y:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        if (bVar12) {
          fscanf(local_e8,"%d",local_e4 + 0x4d46304 + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
        }
        iVar4 = 8;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "height:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        if (bVar12) {
          fscanf(local_e8,"%d",local_e4 + 0x4d4637c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
        }
        iVar4 = local_e4;
        iVar8 = 6;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "rect:";
        do {
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        if (bVar12) {
          fscanf(local_e8,"%ld",local_e4 + 0x4d4664c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
          puVar1 = (uint *)(iVar4 + 0x4d4664c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
          uVar11 = *puVar1;
          *puVar1 = ((((int)uVar11 >> 0xb & 0x1fU) * 0x200 + ((int)uVar11 >> 5 & 0x3fU)) * 0x80 +
                    (uVar11 & 0x1f)) * 8 + 0x70707;
        }
        iVar4 = 8;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "rect32:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        if (bVar12) {
          fscanf(local_e8,"%ld",local_e4 + 0x4d4664c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
        }
        iVar4 = 6;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "loop:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        if (bVar12) {
          fscanf(local_e8,"%d",local_e4 + 0x4d463f4 + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
        }
        iVar4 = 4;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "cc:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        if (bVar12) {
          fscanf(local_e8,"%d",local_e4 + 0x4d4655c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
        }
        iVar4 = 4;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "c1:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        if (bVar12) {
          fscanf(local_e8,"%d",local_e4 + 0x4d4646c + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
        }
        iVar4 = 4;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "c2:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        if (bVar12) {
          fscanf(local_e8,"%d",local_e4 + 0x4d464e4 + (*(int *)(iVar9 + 0x4d45dcc) + iVar10) * 4);
        }
        fscanf(local_e8,"%s",local_d8);
        iVar4 = 10;
        bVar12 = true;
        pcVar5 = local_d8;
        pcVar3 = "layer_end";
        do {
          pFVar7 = local_e8;
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar12 = *pcVar5 == *pcVar3;
          pcVar5 = pcVar5 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar12);
        goto joined_r0x0040c58d;
      }
      *(int *)(iVar9 + 0x4d45dcc) = *(int *)(iVar9 + 0x4d45dcc) + 1;
    }
    iVar4 = feof(pFVar7);
  } while( true );
}


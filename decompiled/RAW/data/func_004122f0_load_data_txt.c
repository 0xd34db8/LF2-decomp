/* Function: FUN_004122f0 */
/* Address: 0x004122f0 */

void FUN_004122f0(char *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  FILE *_File;
  int iVar4;
  int in_ECX;
  uint uVar5;
  char *pcVar6;
  bool bVar7;
  void *local_27c;
  char *local_278;
  void *local_274;
  undefined4 local_270;
  undefined4 local_26c;
  char local_268 [200];
  undefined1 local_1a0 [200];
  undefined1 auStack_d8 [200];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00445da6;
  local_c = ExceptionList;
  local_10 = DAT_0044eea4 ^ (uint)&local_27c;
  ExceptionList = &local_c;
  *(undefined4 *)(in_ECX + 0x4d81060) = 0x960;
  *(undefined4 *)(in_ECX + 0x4d81064) = 0x15e;
  *(undefined4 *)(in_ECX + 0x4d81068) = 0x1d6;
  *(undefined4 *)(in_ECX + 0x4d81074) = 0x25;
  *(undefined4 *)(in_ECX + 0x4d81078) = 9;
  builtin_strncpy((char *)(in_ECX + 0x4d8142c),"Lee ",4);
  local_278 = param_1;
  builtin_strncpy((char *)(in_ECX + 0x4d81430),"On R",4);
  local_26c = param_2;
  builtin_strncpy((char *)(in_ECX + 0x4d81434),"oad",4);
  *(undefined4 *)(in_ECX + 0x4d81404) = 0x64616873;
  *(undefined4 *)(in_ECX + 0x4d81408) = 0x31776f;
  local_27c = operator_new(0x1f50);
  local_4 = 0;
  if (local_27c == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0043ee50(0x40,(undefined4 *)(in_ECX + 0x4d81404),0);
  }
  *(undefined4 *)(in_ECX + 0x4d819ec) = uVar2;
  *(undefined4 *)(in_ECX + 0x4d81080) = 0x6b636162;
  *(undefined4 *)(in_ECX + 0x4d81084) = 0x315f3939;
  local_4 = 0xffffffff;
  *(undefined1 *)(in_ECX + 0x4d81088) = 0;
  local_27c = operator_new(0x1f50);
  local_4 = 1;
  if (local_27c == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0043ee50(0x40,(undefined4 *)(in_ECX + 0x4d81080),0);
  }
  *(undefined4 *)(in_ECX + 0x4d81974) = uVar2;
  *(undefined4 *)(in_ECX + 0x4d8109e) = 0x6b636162;
  *(undefined4 *)(in_ECX + 0x4d810a2) = 0x325f3939;
  local_4 = 0xffffffff;
  *(undefined1 *)(in_ECX + 0x4d810a6) = 0;
  local_27c = operator_new(0x1f50);
  local_4 = 2;
  if (local_27c == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0043ee50(0x40,(undefined4 *)(in_ECX + 0x4d8109e),0);
  }
  *(undefined4 *)(in_ECX + 0x4d81978) = uVar2;
  *(undefined4 *)(in_ECX + 0x4d810bc) = 0x6b636162;
  *(undefined4 *)(in_ECX + 0x4d810c0) = 0x335f3939;
  local_4 = 0xffffffff;
  *(undefined1 *)(in_ECX + 0x4d810c4) = 0;
  local_27c = operator_new(0x1f50);
  local_4 = 3;
  if (local_27c == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0043ee50(0x40,(undefined4 *)(in_ECX + 0x4d810bc),0);
  }
  pcVar6 = local_278;
  *(undefined4 *)(in_ECX + 0x4d8197c) = uVar2;
  builtin_strncpy((char *)(in_ECX + 0x4d81dbc),"Rand",4);
  *(undefined2 *)(in_ECX + 0x4d81dc0) = 0x6d6f;
  *(undefined1 *)(in_ECX + 0x4d81dc2) = 0;
  local_4 = 0xffffffff;
  pcVar3 = local_278;
  do {
    cVar1 = *pcVar3;
    pcVar3[(in_ECX - (int)local_278) + 0x4d82388] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(in_ECX + 0x4d82384) = 0;
  *(undefined4 *)(in_ECX + 0x4d82380) = 0;
  timeGetTime();
  _File = fopen(pcVar6,"r");
  iVar4 = feof(_File);
  do {
    if (iVar4 != 0) {
      fclose(_File);
      FUN_0040c910();
      ExceptionList = local_c;
      __security_check_cookie(local_10 ^ (uint)&local_27c);
      return;
    }
    fscanf(_File,"%s",local_268);
    pcVar6 = local_268;
    uVar5 = 0;
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    if (pcVar6 != local_268 + 1) {
      do {
        DAT_0044f620 = DAT_0044f620 + (int)local_268[uVar5] * uVar5;
        pcVar6 = local_268;
        uVar5 = uVar5 + 1;
        do {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
      } while (uVar5 < (uint)((int)pcVar6 - (int)(local_268 + 1)));
    }
    iVar4 = 9;
    bVar7 = true;
    pcVar6 = local_268;
    pcVar3 = "<object>";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar7 = *pcVar6 == *pcVar3;
      pcVar6 = pcVar6 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar7);
    if (bVar7) {
      fscanf(_File,"%s",local_268);
      iVar4 = 0xd;
      bVar7 = true;
      pcVar6 = local_268;
      pcVar3 = "<object_end>";
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar7 = *pcVar6 == *pcVar3;
        pcVar6 = pcVar6 + 1;
        pcVar3 = pcVar3 + 1;
      } while (bVar7);
joined_r0x0041260a:
      if (!bVar7) {
        iVar4 = 4;
        bVar7 = true;
        pcVar6 = local_268;
        pcVar3 = "id:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar7 = *pcVar6 == *pcVar3;
          pcVar6 = pcVar6 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar7);
        if (bVar7) {
          fscanf(_File,"%d %s %d %s %s",&local_270,local_268,&local_278,local_268,local_1a0);
          uVar2 = local_26c;
          FUN_004242e0(local_1a0,local_26c);
          local_274 = operator_new(0x25360);
          local_4 = 4;
          if (local_274 == (void *)0x0) {
            uVar2 = 0;
          }
          else {
            uVar2 = FUN_0040ef70(local_270,local_278,local_1a0,uVar2);
          }
          *(undefined4 *)(in_ECX + *(int *)(in_ECX + 0x4d82380) * 4) = uVar2;
          *(int *)(in_ECX + 0x4d82380) = *(int *)(in_ECX + 0x4d82380) + 1;
          local_4 = 0xffffffff;
        }
        fscanf(_File,"%s",local_268);
        iVar4 = 0xd;
        bVar7 = true;
        pcVar6 = local_268;
        pcVar3 = "<object_end>";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar7 = *pcVar6 == *pcVar3;
          pcVar6 = pcVar6 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar7);
        goto joined_r0x0041260a;
      }
    }
    iVar4 = 0xd;
    bVar7 = true;
    pcVar6 = local_268;
    pcVar3 = "<background>";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar7 = *pcVar6 == *pcVar3;
      pcVar6 = pcVar6 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar7);
    if (bVar7) {
      fscanf(_File,"%s",local_268);
      iVar4 = 0x11;
      bVar7 = true;
      pcVar6 = local_268;
      pcVar3 = "<background_end>";
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar7 = *pcVar6 == *pcVar3;
        pcVar6 = pcVar6 + 1;
        pcVar3 = pcVar3 + 1;
      } while (bVar7);
joined_r0x00412724:
      if (!bVar7) {
        iVar4 = 4;
        bVar7 = true;
        pcVar6 = local_268;
        pcVar3 = "id:";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar7 = *pcVar6 == *pcVar3;
          pcVar6 = pcVar6 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar7);
        if (bVar7) {
          fscanf(_File,"%d %s %s",&local_27c,local_268,auStack_d8);
          FUN_0040c160(*(undefined4 *)(in_ECX + 0x4d82384),local_27c,auStack_d8);
          *(int *)(in_ECX + 0x4d82384) = *(int *)(in_ECX + 0x4d82384) + 1;
        }
        fscanf(_File,"%s",local_268);
        iVar4 = 0x11;
        bVar7 = true;
        pcVar6 = local_268;
        pcVar3 = "<background_end>";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar7 = *pcVar6 == *pcVar3;
          pcVar6 = pcVar6 + 1;
          pcVar3 = pcVar3 + 1;
        } while (bVar7);
        goto joined_r0x00412724;
      }
    }
    iVar4 = feof(_File);
  } while( true );
}


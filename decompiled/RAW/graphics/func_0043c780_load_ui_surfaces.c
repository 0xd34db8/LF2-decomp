/* Function: FUN_0043c780 */
/* Address: 0x0043c780 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043c780(void)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  char *local_460;
  undefined4 local_45c;
  FILE *local_458;
  char local_454 [52];
  char local_420 [52];
  char local_3ec [500];
  char local_1f8 [500];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_460;
  sprintf(&DAT_00453c68,"data\\ad%d.txt",DAT_0044d784);
  sprintf(&DAT_00453d40,"sprite\\sys\\ad%d.bmp",DAT_0044d784);
  iVar4 = 0;
  local_45c = 0;
  local_458 = fopen(&DAT_00453c68,"r");
  if (local_458 == (FILE *)0x0) {
    local_45c = 1;
    goto LAB_0043cc34;
  }
  fgets(local_1f8,500,local_458);
  DAT_0044d778 = -99;
  sscanf(local_1f8,"%d ",&DAT_0044d778);
  if (DAT_0044d778 == -99) {
    local_45c = 1;
    fclose(local_458);
    goto LAB_0043cc34;
  }
  local_460 = (char *)&DAT_00454a18;
  do {
    piVar1 = &DAT_004583b8 + iVar4;
    (&DAT_00453ce0)[iVar4] = 0xffffff9d;
    (&DAT_00453f70)[iVar4] = 0xffffff9d;
    (&DAT_00453c08)[iVar4] = 0xffffff9d;
    *piVar1 = -99;
    local_460[0] = '-';
    local_460[1] = '\0';
    fgets(local_3ec,500,local_458);
    sscanf(local_3ec,"%s %d %d %d %d %s %s",local_420,piVar1,&DAT_00453c08 + iVar4,
           &DAT_00453f70 + iVar4,&DAT_00453ce0 + iVar4,local_460,local_454);
    iVar3 = 3;
    bVar7 = true;
    pcVar5 = local_420;
    pcVar6 = "ba";
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (!bVar7) {
LAB_0043cb9e:
      (&DAT_004583b8)[iVar4] = 0xffffff9d;
      goto LAB_0043cc12;
    }
    iVar3 = 4;
    bVar7 = true;
    pcVar5 = local_454;
    pcVar6 = "bae";
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if ((((!bVar7) ||
         ((((cVar2 = *local_460, cVar2 != '?' && (cVar2 != 'h')) && (cVar2 != 'H')) ||
          ((*piVar1 == -99 || ((&DAT_00453c08)[iVar4] == -99)))))) ||
        ((&DAT_00453f70)[iVar4] == -99)) || ((&DAT_00453ce0)[iVar4] == -99)) goto LAB_0043cb9e;
    local_460 = local_460 + 100;
    iVar4 = iVar4 + 1;
  } while ((int)local_460 < 0x455378);
  iVar4 = 0;
  local_460 = (char *)&DAT_004546f8;
  do {
    piVar1 = &DAT_00452928 + iVar4;
    (&DAT_00453f50)[iVar4] = 0xffffff9d;
    (&DAT_004546d0)[iVar4] = 0xffffff9d;
    *piVar1 = -99;
    local_460[0] = '-';
    local_460[1] = '\0';
    fgets(local_3ec,500,local_458);
    sscanf(local_3ec,"%s %d %d %d %s %s",local_454,piVar1,&DAT_004546d0 + iVar4,
           &DAT_00453f50 + iVar4,local_460,local_420);
    iVar3 = 3;
    bVar7 = true;
    pcVar5 = local_454;
    pcVar6 = "ta";
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (!bVar7) {
LAB_0043cbab:
      (&DAT_00452928)[iVar4] = 0xffffff9d;
      (&DAT_004546d0)[iVar4] = 0xffffff9d;
      (&DAT_00453f50)[iVar4] = 0xffffff9d;
      goto LAB_0043cc12;
    }
    iVar3 = 4;
    bVar7 = true;
    pcVar5 = local_420;
    pcVar6 = "tae";
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (((!bVar7) || (((cVar2 = *local_460, cVar2 != '?' && (cVar2 != 'h')) && (cVar2 != 'H')))) ||
       (((*piVar1 == -99 || ((&DAT_004546d0)[iVar4] == -99)) || ((&DAT_00453f50)[iVar4] == -99))))
    goto LAB_0043cbab;
    local_460 = local_460 + 100;
    iVar4 = iVar4 + 1;
  } while ((int)local_460 < 0x454a18);
  DAT_004554bc = -99;
  _DAT_00453da8 = 0x2d;
  fgets(local_3ec,500,local_458);
  sscanf(local_3ec,"%s %d %s %s",local_454,&DAT_004554bc,&DAT_00453da8,local_420);
  iVar4 = 3;
  bVar7 = true;
  pcVar5 = local_454;
  pcVar6 = "un";
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar7 = *pcVar5 == *pcVar6;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  } while (bVar7);
  if (bVar7) {
    iVar4 = 4;
    bVar7 = true;
    pcVar5 = local_420;
    pcVar6 = "une";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (((!bVar7) || (((DAT_00453da8 != '?' && (DAT_00453da8 != 'h')) && (DAT_00453da8 != 'H')))) ||
       (DAT_004554bc == -99)) goto LAB_0043cbcc;
    DAT_0045757c = -99;
    DAT_00453da4 = -99;
    fgets(local_3ec,500,local_458);
    sscanf(local_3ec,"%s %d %d %s",local_454,&DAT_00453da4,&DAT_0045757c,local_420);
    iVar4 = 2;
    bVar7 = true;
    pcVar5 = local_454;
    pcVar6 = "y";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (!bVar7) {
LAB_0043cb90:
      DAT_0045757c = 0;
      DAT_00453da4 = 0;
      goto LAB_0043cc12;
    }
    iVar4 = 3;
    bVar7 = true;
    pcVar5 = local_420;
    pcVar6 = "ye";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (((!bVar7) || (DAT_00453da4 == -99)) || (DAT_0045757c == -99)) goto LAB_0043cb90;
    fgets(local_3ec,500,local_458);
    sscanf(local_3ec,"%s",local_454);
    iVar4 = 6;
    bVar7 = true;
    pcVar5 = local_454;
    pcVar6 = "<end>";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (!bVar7) goto LAB_0043cc12;
  }
  else {
LAB_0043cbcc:
    DAT_004554bc = -99;
LAB_0043cc12:
    local_45c = 1;
  }
  fclose(local_458);
LAB_0043cc34:
  __security_check_cookie(local_4 ^ (uint)&local_460);
  return;
}

/* Function: FUN_0043c4a0 */
/* Address: 0x0043c4a0 */

void FUN_0043c4a0(void)

{
  FILE *_File;
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  bool bVar4;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  char local_a0 [52];
  char local_6c [52];
  char local_38 [52];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_bc;
  local_bc = 0;
  _File = fopen("data\\adinfo.txt","r");
  if (_File == (FILE *)0x0) {
    local_bc = 1;
  }
  else {
    local_a0[0] = '\0';
    local_38[0] = '\0';
    local_6c[0] = '\0';
    DAT_004527b0 = 0;
    fscanf(_File,"%s %s %s %s",&DAT_004527b0,local_6c,local_38,local_a0);
    fclose(_File);
  }
  iVar1 = 6;
  bVar4 = true;
  pcVar2 = local_a0;
  pcVar3 = "<end>";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar4 = *pcVar2 == *pcVar3;
    pcVar2 = pcVar2 + 1;
    pcVar3 = pcVar3 + 1;
  } while (bVar4);
  if (!bVar4) {
    local_bc = 1;
    goto LAB_0043c666;
  }
  if (local_bc != 0) goto LAB_0043c666;
  bVar4 = true;
  iVar1 = 4;
  pcVar2 = &DAT_004527b0;
  pcVar3 = "now";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar4 = *pcVar2 == *pcVar3;
    pcVar2 = pcVar2 + 1;
    pcVar3 = pcVar3 + 1;
  } while (bVar4);
  if (bVar4) {
LAB_0043c5f9:
    sscanf(local_6c,"%d",&DAT_0044d784);
    sscanf(local_38,"%d",&DAT_0044d788);
    sprintf(&DAT_00453c68,"data\\ad%d.txt",DAT_0044d784);
    sprintf(&DAT_00453d40,"sprite\\sys\\ad%d.bmp",DAT_0044d784);
    if ((DAT_0044d784 != -99) && (DAT_0044d788 != -99)) goto LAB_0043c666;
  }
  else {
    iVar1 = 0xc;
    bVar4 = true;
    pcVar2 = &DAT_004527b0;
    pcVar3 = "dont_update";
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar4 = *pcVar2 == *pcVar3;
      pcVar2 = pcVar2 + 1;
      pcVar3 = pcVar3 + 1;
    } while (bVar4);
    if (bVar4) goto LAB_0043c5f9;
    local_a4 = -99;
    local_a8 = -99;
    local_ac = -99;
    local_b8 = -99;
    local_b4 = -99;
    local_b0 = -99;
    sscanf(&DAT_004527b0,"%04d/%02d/%02d/%02d/%02d/%02d",&local_a4,&local_a8,&local_ac,&local_b8,
           &local_b4,&local_b0);
    if (((((local_a4 != -99) && (local_a8 != -99)) && (local_ac != -99)) &&
        ((local_b8 != -99 && (local_b4 != -99)))) && (local_b0 != -99)) goto LAB_0043c5f9;
  }
  local_bc = 1;
LAB_0043c666:
  __security_check_cookie(local_4 ^ (uint)&local_bc);
  return;
}


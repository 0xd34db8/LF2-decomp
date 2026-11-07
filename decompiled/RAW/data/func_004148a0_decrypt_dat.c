/* Function: FUN_004148a0 */
/* Address: 0x004148a0 */

void FUN_004148a0(char *param_1)

{
  char cVar1;
  FILE *_File;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  int local_164;
  FILE *local_160;
  undefined1 local_15c [4];
  char local_158 [40];
  char local_130 [16];
  undefined2 local_120;
  undefined1 local_11e;
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_164;
  pcVar2 = "SiuHungIsAGoodBearBecauseHeIsVeryGood";
  pcVar5 = local_158;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar5 = pcVar5 + 4;
  }
  builtin_strncpy(local_130,"data\\temporary.t",0x10);
  *(undefined2 *)pcVar5 = *(undefined2 *)pcVar2;
  uVar4 = 0;
  local_120 = 0x7478;
  local_11e = 0;
  _File = fopen(param_1,"r");
  local_160 = fopen(local_130,"w");
  local_164 = 0x7b;
  do {
    pcVar2 = local_158;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    uVar4 = (uVar4 + 1) % (uint)((int)pcVar2 - (int)(local_158 + 1));
    fscanf(_File,"%c",local_15c);
    local_164 = local_164 + -1;
  } while (local_164 != 0);
  fscanf(_File,"%c",&local_164);
  iVar3 = feof(_File);
  while (iVar3 == 0) {
    local_164 = local_164 - local_158[uVar4];
    if (local_164 < 0) {
      local_164 = local_164 + 0x100;
    }
    pcVar2 = local_158;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    uVar4 = (uVar4 + 1) % (uint)((int)pcVar2 - (int)(local_158 + 1));
    fprintf(local_160,"%c",local_164);
    local_164 = 0;
    fscanf(_File,"%c",&local_164);
    iVar3 = feof(_File);
  }
  fclose(_File);
  fclose(local_160);
  __security_check_cookie(local_4 ^ (uint)&local_164);
  return;
}

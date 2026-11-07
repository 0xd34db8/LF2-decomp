/* Function: FUN_004146b0 */
/* Address: 0x004146b0 */

void FUN_004146b0(char *param_1)

{
  char cVar1;
  char *pcVar2;
  FILE *_File;
  FILE *_File_00;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  uint local_164;
  FILE *local_160;
  int local_15c;
  char local_158 [37];
  char acStack_133 [303];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_164;
  pcVar2 = "SiuHungIsAGoodBearBecauseHeIsVeryGood";
  pcVar3 = local_158;
  for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar3 = pcVar3 + 4;
  }
  *(undefined2 *)pcVar3 = *(undefined2 *)pcVar2;
  uVar5 = 0;
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2[(int)(acStack_133 + (3 - (int)param_1))] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  pcVar2 = acStack_133 + 3;
  do {
    pcVar3 = pcVar2;
    pcVar2 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  pcVar3[-3] = 'd';
  pcVar2 = acStack_133 + 3;
  do {
    pcVar3 = pcVar2;
    pcVar2 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  pcVar3[-2] = 'a';
  pcVar2 = acStack_133 + 3;
  do {
    pcVar3 = pcVar2;
    pcVar2 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  pcVar3[-1] = 't';
  _File = fopen(param_1,"r");
  _File_00 = fopen(acStack_133 + 3,"w");
  local_15c = 0x7b;
  local_160 = _File_00;
  do {
    iVar4 = rand();
    pcVar2 = local_158 + uVar5;
    pcVar3 = local_158;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    uVar5 = (uVar5 + 1) % (uint)((int)pcVar3 - (int)(local_158 + 1));
    fprintf(_File_00,"%c",(int)(char)((char)(iVar4 % 0x19) + 'A' + *pcVar2));
    local_15c = local_15c + -1;
  } while (local_15c != 0);
  fscanf(_File,"%c",&local_164);
  iVar4 = feof(_File);
  if (iVar4 == 0) {
    do {
      local_164 = (int)local_158[uVar5] + local_164 & 0x800000ff;
      if ((int)local_164 < 0) {
        local_164 = (local_164 - 1 | 0xffffff00) + 1;
      }
      pcVar2 = local_158;
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      uVar5 = (uVar5 + 1) % (uint)((int)pcVar2 - (int)(local_158 + 1));
      fprintf(local_160,"%c",(int)(char)local_164);
      fscanf(_File,"%c",&local_164);
      iVar4 = feof(_File);
    } while (iVar4 == 0);
    _File_00 = local_160;
  }
  fclose(_File);
  fclose(_File_00);
  __security_check_cookie(local_4 ^ (uint)&local_164);
  return;
}

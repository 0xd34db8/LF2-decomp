/* Function: FUN_00414a30 */
/* Address: 0x00414a30 */

void FUN_00414a30(char *param_1,char *param_2)

{
  char cVar1;
  FILE *_File;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  int local_38;
  FILE *local_34;
  undefined1 local_30 [4];
  char local_2c [40];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_38;
  pcVar2 = "SiuHungIsAGoodBearBecauseHeIsVeryGood";
  pcVar5 = local_2c;
  for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined4 *)pcVar5 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar5 = pcVar5 + 4;
  }
  *(undefined2 *)pcVar5 = *(undefined2 *)pcVar2;
  uVar4 = 0;
  _File = fopen(param_1,"r");
  local_34 = fopen(param_2,"w");
  local_38 = 0x7b;
  do {
    pcVar2 = local_2c;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    uVar4 = (uVar4 + 1) % (uint)((int)pcVar2 - (int)(local_2c + 1));
    fscanf(_File,"%c",local_30);
    local_38 = local_38 + -1;
  } while (local_38 != 0);
  fscanf(_File,"%c",&local_38);
  iVar3 = feof(_File);
  if (iVar3 == 0) {
    do {
      local_38 = local_38 - local_2c[uVar4];
      if (local_38 < 0) {
        local_38 = local_38 + 0x100;
      }
      pcVar2 = local_2c;
      do {
        cVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
      } while (cVar1 != '\0');
      uVar4 = (uVar4 + 1) % (uint)((int)pcVar2 - (int)(local_2c + 1));
      fprintf(local_34,"%c",local_38);
      local_38 = 0;
      fscanf(_File,"%c",&local_38);
      iVar3 = feof(_File);
    } while (iVar3 == 0);
  }
  fclose(_File);
  fclose(local_34);
  __security_check_cookie(local_4 ^ (uint)&local_38);
  return;
}

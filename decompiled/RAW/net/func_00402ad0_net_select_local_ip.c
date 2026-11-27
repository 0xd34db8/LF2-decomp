/* Function: FUN_00402ad0 */
/* Address: 0x00402ad0 */

void FUN_00402ad0(int *param_1)

{
  _struct_1227 in;
  int *piVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  char local_404 [1024];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)local_404;
  iVar4 = 0;
  if (*param_1 != 0) {
    piVar1 = param_1;
    do {
      in = ((_union_1226 *)*piVar1)->S_un_b;
      htons(0);
      pcVar2 = inet_ntoa((in_addr)in);
      sprintf(local_404,"%s",pcVar2);
      iVar3 = FUN_00402a60(local_404);
      if (iVar3 != 0) break;
      iVar4 = iVar4 + 1;
      piVar1 = param_1 + iVar4;
    } while (param_1[iVar4] != 0);
  }
  __security_check_cookie(local_4 ^ (uint)local_404);
  return;
}


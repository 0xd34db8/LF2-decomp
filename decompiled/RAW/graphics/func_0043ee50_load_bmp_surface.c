/* Function: FUN_0043ee50 */
/* Address: 0x0043ee50 */

void FUN_0043ee50(undefined4 param_1,char *param_2,int param_3)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined4 *in_ECX;
  undefined4 local_d4;
  undefined4 local_d0;
  CHAR local_cc [200];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_d4;
  local_d4 = 0;
  local_d0 = 0;
  iVar3 = -(int)param_2;
  do {
    cVar1 = *param_2;
    param_2[(int)(local_cc + iVar3)] = cVar1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  piVar2 = (int *)FUN_0043ed10(DAT_00457578,param_1,0,in_ECX + 1,in_ECX + 2);
  *in_ECX = piVar2;
  if (piVar2 == (int *)0x0) {
    if (param_3 == 0) {
      MessageBoxA((HWND)0x0,"Couldn\'t create art surface.",local_cc,0);
      OutputDebugStringA("Couldn\'t create art surface.\n");
    }
  }
  else {
    iVar3 = (**(code **)(*piVar2 + 0x74))(piVar2,8,&local_d4);
    if (iVar3 < 0) {
      MessageBoxA((HWND)0x0,"Couldn\'t set the color key.","Error",0);
      OutputDebugStringA("Couldn\'t set the color key.\n");
      (**(code **)(*(int *)*in_ECX + 8))((int *)*in_ECX);
      *in_ECX = 0;
    }
  }
  __security_check_cookie(local_4 ^ (uint)&local_d4);
  return;
}


/* Function: FUN_0043ed10 */
/* Address: 0x0043ed10 */

undefined4
FUN_0043ed10(int *param_1,undefined4 param_2,int param_3,undefined4 *param_4,undefined4 *param_5)

{
  int in_EAX;
  HMODULE pHVar1;
  HANDLE h;
  int iVar2;
  LPCSTR unaff_EDI;
  LPCSTR name;
  UINT UVar3;
  int cx;
  HANDLE cx_00;
  HANDLE cy;
  UINT fuLoad;
  undefined4 uVar4;
  undefined1 local_88 [4];
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  
  fuLoad = 0x2010;
  UVar3 = 0;
  name = unaff_EDI;
  pHVar1 = GetModuleHandleA((LPCSTR)0x0);
  h = LoadImageA(pHVar1,name,UVar3,cx,in_EAX,fuLoad);
  if (h == (HANDLE)0x0) {
    UVar3 = 0x2000;
    cx_00 = h;
    cy = h;
    pHVar1 = GetModuleHandleA((LPCSTR)0x0);
    h = LoadImageA(pHVar1,unaff_EDI,(UINT)h,(int)cx_00,(int)cy,UVar3);
    if (h == (HANDLE)0x0) {
      return 0;
    }
  }
  GetObjectA(h,0x18,local_18);
  memset(&local_84,0,0x6c);
  *param_4 = local_14;
  local_78 = local_14;
  local_1c = param_2;
  local_7c = local_10;
  *param_5 = local_10;
  local_84 = 0x6c;
  local_80 = 7;
  if (param_3 != 0) {
    local_38 = *(undefined4 *)(param_3 + 4);
    local_34 = *(undefined4 *)(param_3 + 8);
    local_30 = *(undefined4 *)(param_3 + 0xc);
    local_2c = *(undefined4 *)(param_3 + 0x10);
    local_28 = *(undefined4 *)(param_3 + 0x14);
    local_24 = *(undefined4 *)(param_3 + 0x18);
    local_20 = *(undefined4 *)(param_3 + 0x1c);
    local_80 = 0x1007;
  }
  uVar4 = 0;
  iVar2 = (**(code **)(*param_1 + 0x18))(param_1,&local_84,local_88);
  if (iVar2 == 0) {
    FUN_004013d0(uVar4,h,0,0,0,0);
    DeleteObject(h);
    return uVar4;
  }
  return 0;
}


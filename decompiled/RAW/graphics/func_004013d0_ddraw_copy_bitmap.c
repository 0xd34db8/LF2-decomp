/* Function: FUN_004013d0 */
/* Address: 0x004013d0 */

int FUN_004013d0(HDC param_1,HGDIOBJ param_2,undefined4 param_3,int param_4,int param_5)

{
  HDC hdc;
  int iVar1;
  undefined1 auStack_a0 [4];
  undefined1 auStack_88 [4];
  int iStack_84;
  int iStack_80;
  int iStack_78;
  int iStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  int iStack_8;
  int iStack_4;
  
  if ((param_2 == (HGDIOBJ)0x0) || (param_1 == (HDC)0x0)) {
    return -0x7fffbffb;
  }
  (**(code **)(param_1->unused + 0x6c))();
  hdc = CreateCompatibleDC((HDC)0x0);
  SelectObject(hdc,param_2);
  GetObjectA(param_2,0x18,auStack_88);
  if (param_4 == 0) {
    param_4 = iStack_84;
  }
  if (param_5 == 0) {
    param_5 = iStack_80;
  }
  uStack_70 = 0x6c;
  uStack_6c = 6;
  (**(code **)(param_1->unused + 0x58))(param_1,&uStack_70);
  iVar1 = (**(code **)(param_1->unused + 0x44))(param_1,auStack_a0 + 8);
  if (iVar1 == 0) {
    StretchBlt(param_1,0,0,iStack_74,iStack_78,hdc,iStack_8,iStack_4,param_4,param_5,0xcc0020);
    (**(code **)(param_1->unused + 0x68))(param_1,param_1);
  }
  DeleteDC(hdc);
  return iVar1;
}


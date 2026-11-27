/* Function: FUN_00401290 */
/* Address: 0x00401290 */

int FUN_00401290(int *param_1,COLORREF param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int c;
  HDC unaff_ESI;
  LPCSTR unaff_retaddr;
  
  piVar1 = param_1;
  iVar2 = (**(code **)(*param_1 + 0x44))(param_1,&param_1);
  if (-1 < iVar2) {
    SetBkColor(unaff_ESI,(COLORREF)param_1);
    SetTextColor(unaff_ESI,param_2);
    c = lstrlenA(unaff_retaddr);
    TextOutA(unaff_ESI,param_3,param_4,unaff_retaddr,c);
    (**(code **)(*piVar1 + 0x68))(piVar1,unaff_ESI);
  }
  return iVar2;
}


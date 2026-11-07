/* Function: FUN_0043ef70 */
/* Address: 0x0043ef70 */

undefined4
FUN_0043ef70(int *param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  int iVar1;
  int *in_ECX;
  int unaff_EBX;
  int unaff_ESI;
  int *unaff_EDI;
  
  iVar1 = *in_ECX;
  if (((((iVar1 < 0) && (*param_5 < 0)) || ((unaff_ESI < iVar1 && (unaff_ESI < *param_5)))) ||
      ((*unaff_EDI < 0 && (*param_6 < 0)))) || ((unaff_EBX < *unaff_EDI && (unaff_EBX < *param_6))))
  {
    return 0;
  }
  if (iVar1 < 0) {
    *param_1 = *param_1 - iVar1;
    *in_ECX = 0;
  }
  if (*unaff_EDI < 0) {
    *param_2 = *param_2 - *unaff_EDI;
    *unaff_EDI = 0;
  }
  if (unaff_ESI < *param_5) {
    *param_3 = *param_3 + (unaff_ESI - *param_5);
    *param_5 = unaff_ESI;
  }
  if (unaff_EBX < *param_6) {
    *param_4 = *param_4 + (unaff_EBX - *param_6);
    *param_6 = unaff_EBX;
  }
  return 1;
}

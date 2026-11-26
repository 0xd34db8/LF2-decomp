/* Function: FUN_00416cd0 */
/* Address: 0x00416cd0 */

void FUN_00416cd0(int *param_1,int *param_2)

{
  if (*param_1 == 0) {
    DAT_00450bfc = 0;
    DAT_0044fb60 = 0;
    DAT_0044fcb0 = 0;
    DAT_00450c2c = 0;
    DAT_0044d02c = 1;
    if ((((*param_2 != 5) && (DAT_00450be4 != 0)) && (DAT_00450b80 != 0)) &&
       (DAT_00450b80 = 0, DAT_00450bdc < 0x65)) {
      DAT_00450b70 = 3;
      DAT_00450b6c = 0;
    }
    if (DAT_00450b88 != 0) {
      *param_2 = 6;
      if ((DAT_004588ac != 0) && (DAT_00450b88 != 0)) {
        FUN_0043df00();
        DAT_00458428 = *(undefined4 *)(&Rsrc_Bitmap_MENU_CLIP3_404.field_0xe3f8 + DAT_004588ac);
        DAT_0045842c = *(undefined4 *)(&Rsrc_Bitmap_MENU_CLIP3_404.field_0xe3fc + DAT_004588ac);
      }
      DAT_00450b88 = 0;
      DAT_00450b84 = 0;
      *param_1 = 10;
      DAT_00450bdc = 0;
      return;
    }
    if ((*param_2 != 2) && (*param_2 != 3)) {
      DAT_00450bdc = 0x15e;
      return;
    }
    DAT_00450bdc = 0;
    *param_1 = 10;
    DAT_00457580 = 0;
  }
  return;
}

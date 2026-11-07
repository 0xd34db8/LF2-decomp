/* Function: FUN_0043cc60 */
/* Address: 0x0043cc60 */

bool FUN_0043cc60(void)

{
  bool bVar1;
  void *pvVar2;
  undefined1 auStack_12 [6];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004461db;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  bVar1 = false;
  if (DAT_00458420 != (int *)0x0) {
    FUN_0043ef50(DAT_0044eea4 ^ (uint)(auStack_12 + -0x12));
    free(DAT_00458420);
    DAT_00458420 = (int *)0x0;
  }
  pvVar2 = operator_new(0x1f50);
  local_4 = 0;
  if (pvVar2 == (void *)0x0) {
    DAT_00458420 = (int *)0x0;
  }
  else {
    DAT_00458420 = (int *)FUN_0043ee50(0x40,&DAT_00453d40,0);
  }
  if ((DAT_00458420 == (int *)0x0) || (*DAT_00458420 == 0)) {
    bVar1 = true;
  }
  else {
    DAT_00458420[4] = 0;
    DAT_00458420[0x1f8] = 0;
    DAT_00458420[0x3ec] = 0x18d;
    DAT_00458420[0x5e0] = 0x22;
    DAT_00458420[5] = 0x18d;
    DAT_00458420[0x1f9] = 0;
    DAT_00458420[0x3ed] = 0x18d;
    DAT_00458420[0x5e1] = 0x22;
    DAT_00458420[6] = 0;
    DAT_00458420[0x1fa] = 0x22;
    DAT_00458420[0x3ee] = 0xc6;
    DAT_00458420[0x5e2] = 0xc2;
    DAT_00458420[7] = 0xc6;
    DAT_00458420[0x1fb] = 0x22;
    DAT_00458420[0x3ef] = 0xc6;
    DAT_00458420[0x5e3] = 0xc2;
    DAT_00458420[8] = 0x18c;
    DAT_00458420[0x1fc] = 0x22;
    DAT_00458420[0x3f0] = 0xc6;
    DAT_00458420[0x5e4] = 0xc2;
    DAT_00458420[9] = 0x252;
    DAT_00458420[0x1fd] = 0x22;
    DAT_00458420[0x3f1] = 0xc6;
    DAT_00458420[0x5e5] = 0xc2;
    DAT_00458420[10] = 0;
    DAT_00458420[0x1fe] = 0xe4;
    DAT_00458420[0x3f2] = 0xc6;
    DAT_00458420[0x5e6] = 0xc2;
    DAT_00458420[0xb] = 0xc6;
    DAT_00458420[0x1ff] = 0xe4;
    DAT_00458420[0x3f3] = 0xc6;
    DAT_00458420[0x5e7] = 0xc2;
    DAT_00458420[0xc] = 0x18c;
    DAT_00458420[0x200] = 0xe4;
    DAT_00458420[0x3f4] = 0xc6;
    DAT_00458420[0x5e8] = 0xc2;
    DAT_00458420[0xd] = 0x252;
    DAT_00458420[0x201] = 0xe4;
    DAT_00458420[0x3f5] = 0xc6;
    DAT_00458420[0x5e9] = 0xc2;
    DAT_00458420[0xe] = 0;
    DAT_00458420[0x202] = 0x1a6;
    DAT_00458420[0x3f6] = 0x31a;
    DAT_00458420[0x5ea] = 0x80;
    DAT_00458420[3] = 0xb;
  }
  ExceptionList = local_c;
  return !bVar1;
}

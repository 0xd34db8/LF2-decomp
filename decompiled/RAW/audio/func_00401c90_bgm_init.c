/* Function: FUN_00401c90 */
/* Address: 0x00401c90 */

undefined4 FUN_00401c90(void)

{
  HRESULT HVar1;
  
  HVar1 = CoCreateInstance((IID *)&DAT_0044a2a4,(LPUNKNOWN)0x0,1,(IID *)&DAT_0044a254,&DAT_0044f040)
  ;
  if (HVar1 < 0) {
    return 0xffffffff;
  }
  (**(code **)*DAT_0044f040)(DAT_0044f040,&DAT_0044a294,&DAT_0044f044);
  (**(code **)*DAT_0044f040)(DAT_0044f040,&DAT_0044a284,&DAT_0044f048);
  (**(code **)*DAT_0044f040)(DAT_0044f040,&DAT_0044a274,&DAT_0044f04c);
  (**(code **)(*DAT_0044f048 + 0x34))(DAT_0044f048,DAT_004546f4,0x400,0);
  (**(code **)(*DAT_0044f048 + 0x38))(DAT_0044f048,0);
  DAT_0044ef04 = 0;
  return 0;
}

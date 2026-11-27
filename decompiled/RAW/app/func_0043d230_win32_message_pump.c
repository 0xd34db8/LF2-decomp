/* Function: FUN_0043d230 */
/* Address: 0x0043d230 */

void FUN_0043d230(void)

{
  BOOL BVar1;
  tagMSG local_1c;
  
  BVar1 = PeekMessageA(&local_1c,(HWND)0x0,0,0,0);
  if (BVar1 != 0) {
    BVar1 = GetMessageA(&local_1c,(HWND)0x0,0,0);
    if (BVar1 != 0) {
      TranslateMessage(&local_1c);
      DispatchMessageA(&local_1c);
    }
  }
  return;
}


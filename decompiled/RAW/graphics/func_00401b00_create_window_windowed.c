/* Function: FUN_00401b00 */
/* Address: 0x00401b00 */

HWND FUN_00401b00(HINSTANCE param_1,WNDPROC param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  HWND hWnd;
  WNDCLASSA local_28;
  
  iVar1 = GetSystemMetrics(7);
  iVar2 = GetSystemMetrics(8);
  iVar3 = GetSystemMetrics(8);
  iVar4 = GetSystemMetrics(4);
  DAT_0044d014 = DAT_0044d78c + iVar1 * 2;
  DAT_0044d018 = DAT_0044d790 + iVar4 + iVar2 + iVar3;
  local_28.style = 3;
  local_28.lpfnWndProc = param_2;
  local_28.cbClsExtra = 0;
  local_28.cbWndExtra = 0;
  local_28.hInstance = param_1;
  local_28.hIcon = LoadIconA(param_1,(LPCSTR)0x7f00);
  local_28.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  local_28.hbrBackground = (HBRUSH)0x0;
  local_28.lpszMenuName = "Marti";
  local_28.lpszClassName = "Marti";
  RegisterClassA(&local_28);
  hWnd = CreateWindowExA(0,"Marti","Little Fighter 2",0x10cb0000,-0x80000000,5,DAT_0044d014,
                         DAT_0044d018,(HWND)0x0,(HMENU)0x0,param_1,(LPVOID)0x0);
  if (hWnd == (HWND)0x0) {
    return (HWND)0x0;
  }
  UpdateWindow(hWnd);
  return hWnd;
}

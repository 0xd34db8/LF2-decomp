/* Function: FUN_00401bf0 */
/* Address: 0x00401bf0 */

void FUN_00401bf0(HINSTANCE param_1,WNDPROC param_2)

{
  int nHeight;
  int nWidth;
  HWND hWndParent;
  HMENU hMenu;
  LPVOID lpParam;
  WNDCLASSA local_28;
  
  local_28.style = 3;
  local_28.lpfnWndProc = param_2;
  local_28.cbClsExtra = 0;
  local_28.cbWndExtra = 0;
  local_28.hInstance = param_1;
  local_28.hIcon = LoadIconA(param_1,(LPCSTR)0x7f00);
  local_28.hbrBackground = (HBRUSH)0x0;
  local_28.lpszMenuName = "Marti";
  local_28.lpszClassName = "Marti";
  RegisterClassA(&local_28);
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hWndParent = (HWND)0x0;
  nHeight = GetSystemMetrics(1);
  nWidth = GetSystemMetrics(0);
  CreateWindowExA(8,"Marti","Little Fighter 2",0x80000000,0,0,nWidth,nHeight,hWndParent,hMenu,
                  param_1,lpParam);
  return;
}

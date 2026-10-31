/* 
 * Virtual Address: 0x0043cf40
 * Description: Main game loop and initialization.
 *              Handles window messages, game state updates, and rendering.
 * Calling Convention: __stdcall (parameters on stack)
 */
undefined4 FUN_0043cf40(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)



{

  DWORD DVar1;

  int iVar2;

  tm *ptVar3;

  HCURSOR hCursor;

  BOOL BVar4;

  DWORD DVar5;

  __time64_t local_2c;

  longlong local_24;

  tagMSG local_1c;

  

  DAT_00458420 = 0;

  DVar1 = timeGetTime();

  srand(DVar1);

  InitializeCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);

  CoInitialize((LPVOID)0x0);

  iVar2 = FUN_0043bec0(param_1,param_4);

  if (iVar2 == 0) {

    return 0;

  }

  iVar2 = FUN_0043c4a0();

  if (((iVar2 == 0) || (iVar2 = FUN_0043c780(), iVar2 == 0)) || (iVar2 = FUN_0043cc60(), iVar2 == 0)

     ) {

    FUN_0043c690();

  }

  local_2c = _time64((__time64_t *)0x0);

  ptVar3 = _localtime64(&local_2c);

  sprintf(&DAT_00451d48,"%04d/%02d/%02d/%02d/%02d/%02d",ptVar3->tm_year + 0x76c,ptVar3->tm_mon + 1,

          ptVar3->tm_mday,ptVar3->tm_hour,ptVar3->tm_min,ptVar3->tm_sec);

  local_24 = local_2c + DAT_0044d788 * 0x15180;

  ptVar3 = _localtime64(&local_24);

  sprintf(&DAT_00458350,"%04d/%02d/%02d/%02d/%02d/%02d",ptVar3->tm_year + 0x76c,ptVar3->tm_mon + 1,

          ptVar3->tm_mday,ptVar3->tm_hour,ptVar3->tm_min,ptVar3->tm_sec);

  FUN_00402020(&DAT_00447744);

  hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);

  SetCursor(hCursor);

  memset(&DAT_00455378,0x75,0x100);

  FUN_0043bf10();

  iVar2 = FUN_00401970(DAT_004546f4);

  if (iVar2 == 0) {

    MessageBoxA(DAT_004546f4,"Could not initialize Direct Sound",(LPCSTR)0x0,0x30);

  }

  FUN_004014e0("data\\m_join.wav");

  FUN_004014e0("data\\m_ok.wav");

  FUN_004014e0("data\\m_cancel.wav");

  FUN_004014e0("data\\m_pass.wav");

  FUN_004014e0("data\\m_end.wav");

  do {

    BVar4 = PeekMessageA(&local_1c,(HWND)0x0,0,0,0);

    if (BVar4 == 0) {

      if (DAT_0044d02c == 0) {

        DVar5 = timeGetTime();

        if (3 < DVar5 - DVar1) {

          DVar5 = timeGetTime();

          if (100 < DVar5 - DVar1) {

            DVar1 = timeGetTime();

            DVar1 = DVar1 - 100;

          }

          DVar1 = DVar1 + 3;

          iVar2 = FUN_0043e9a0(DAT_00451dac);

          if (iVar2 < 0) {

            FUN_0043e890();

          }

        }

        DVar5 = timeGetTime();

        DVar5 = (DVar1 - DVar5) + 3;

      }

      else {

        DVar5 = timeGetTime();

        if (0x21 < DVar5 - DVar1) {

          DVar5 = timeGetTime();

          if (100 < DVar5 - DVar1) {

            DVar1 = timeGetTime();

            DVar1 = DVar1 - 100;

          }

          DVar1 = DVar1 + 0x21;

          iVar2 = FUN_0043e9a0(DAT_00451dac);

          if (iVar2 < 0) {

            FUN_0043e890();

          }

        }

        DVar5 = timeGetTime();

        DVar5 = (DVar1 - DVar5) + 0x21;

      }

      if (0 < (int)DVar5) {

        if (5 < (int)DVar5) {

          DVar5 = 5;

        }

        Sleep(DVar5);

      }

    }

    else {

      BVar4 = GetMessageA(&local_1c,(HWND)0x0,0,0);

      if (BVar4 == 0) {

        return local_1c.wParam;

      }

      TranslateMessage(&local_1c);

      DispatchMessageA(&local_1c);

    }

    DAT_00458580 = DAT_00458580 + 1;

    if (0x3c < DAT_00458580) {

      DAT_00458580 = 0;

    }

  } while( true );

}




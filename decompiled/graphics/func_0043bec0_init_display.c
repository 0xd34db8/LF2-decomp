/* 
 * Virtual Address: 0x0043bec0
 * Description: Initializes DirectDraw and shows the game window.
 *              Calls FUN_0043bdd0() to set up graphics.
 *              Shows the game window (HWND) if initialization succeeds.
 * Calling Convention: __cdecl (parameters on stack)
 */

undefined4 FUN_0043bec0(undefined4 param_1)



{

  int iVar1;

  

  DAT_004554c0 = param_1;

  iVar1 = FUN_0043bdd0();

  if (iVar1 < 0) {

    MessageBoxA((HWND)0x0,"DirectDraw Init FAILED","ERROR",0);

    FUN_00401ae0();

    return 0;

  }

  ShowWindow(DAT_004546f4,5);

  return 1;

}




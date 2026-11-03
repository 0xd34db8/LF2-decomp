/*
 * Function: Drop-Shadow Outlined Text Renderer
 * Virtual Address: 0x00423A70
 * Calling Convention: __cdecl
 *
 * Parameters:
 *   param_1: Text string (char*)
 *   param_2: X screen coordinate (int)
 *   param_3: Y screen coordinate (int)
 *   param_4: Max characters per line (int)
 *   param_5: Max lines (int)
 *   param_6: Rendering mode (int)
 *   param_7: Blinking cursor flag (int)
 *
 * Description:
 *   Executes 4 rendering passes over FUN_00423940 at coordinate offsets
 *   (-1, +1), (-1, 0), (0, +1), and (0, 0) to produce a 1-pixel shadow outline effect.
 */

extern void FUN_00423940(char *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);

void FUN_00423a70(char *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
  FUN_00423940(param_1, param_2 - 1, param_3 + 1, param_4, param_5, param_6, param_7);
  FUN_00423940(param_1, param_2 - 1, param_3,     param_4, param_5, param_6, param_7);
  FUN_00423940(param_1, param_2,     param_3 + 1, param_4, param_5, param_6, param_7);
  FUN_00423940(param_1, param_2,     param_3,     param_4, param_5, param_6, param_7);
}


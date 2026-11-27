/* Function: FUN_0043d280 */
/* Address: 0x0043d280 */

void FUN_0043d280(undefined4 *param_1)

{
  if ((void *)*param_1 != (void *)0x0) {
    free((void *)*param_1);
    *param_1 = 0;
  }
  return;
}


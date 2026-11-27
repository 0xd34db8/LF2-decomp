/* Function: FUN_00402a60 */
/* Address: 0x00402a60 */

undefined4 FUN_00402a60(char *param_1)

{
  char cVar1;
  
  if ((*param_1 == '1') &&
     (((((cVar1 = param_1[1], cVar1 == '0' && (param_1[2] == '.')) ||
        ((cVar1 == '9' &&
         ((((param_1[2] == '2' && (param_1[3] == '.')) && (param_1[4] == '1')) &&
          ((param_1[5] == '6' && (param_1[6] == '8')))))))) ||
       (((cVar1 == '6' && ((param_1[2] == '9' && (param_1[3] == '.')))) &&
        ((param_1[4] == '2' && ((param_1[5] == '5' && (param_1[6] == '4')))))))) ||
      ((cVar1 == '2' && (param_1[2] == '7')))))) {
    return 0;
  }
  return 1;
}


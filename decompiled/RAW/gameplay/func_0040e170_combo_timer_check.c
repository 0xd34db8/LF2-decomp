/* Function: FUN_0040e170 */
/* Address: 0x0040e170 */

undefined4 FUN_0040e170(char param_1,int param_2)

{
  char cVar1;
  int in_ECX;
  
  if (param_2 == 0) {
    if (*(char *)(in_ECX + 0xbe) == '\x05') {
      return 1;
    }
LAB_0040e182:
    cVar1 = *(char *)(in_ECX + 0xbf);
LAB_0040e188:
    if (cVar1 == '\x05') {
      return 1;
    }
    cVar1 = *(char *)(in_ECX + 0xc0);
LAB_0040e190:
    if (cVar1 == '\x05') {
      return 1;
    }
    cVar1 = *(char *)(in_ECX + 0xc3);
LAB_0040e198:
    if (cVar1 == '\x05') {
      return 1;
    }
    cVar1 = *(char *)(in_ECX + 0xc4);
LAB_0040e1a0:
    if (cVar1 == '\x05') {
      return 1;
    }
    cVar1 = *(char *)(in_ECX + 0xc5);
  }
  else {
    if (param_2 != 1) {
      return 0;
    }
    if (param_1 == 'U') {
      if (*(char *)(in_ECX + 0xbe) == '\x05') {
        return 1;
      }
      if (*(char *)(in_ECX + 0xbf) == '\x05') {
        return 1;
      }
      if (*(char *)(in_ECX + 0xc0) == '\x05') {
        return 1;
      }
      cVar1 = *(char *)(in_ECX + 0xc3);
      goto LAB_0040e1a0;
    }
    if (param_1 != 'D') {
      if (param_1 != 'L') {
        if (param_1 == 'R') {
          if (*(char *)(in_ECX + 0xbe) == '\x05') {
            return 1;
          }
          if (*(char *)(in_ECX + 0xbf) == '\x05') {
            return 1;
          }
          if (*(char *)(in_ECX + 0xc0) == '\x05') {
            return 1;
          }
          if (*(char *)(in_ECX + 0xc3) == '\x05') {
            return 1;
          }
          if (*(char *)(in_ECX + 0xc4) == '\x05') {
            return 1;
          }
          cVar1 = *(char *)(in_ECX + 0xc5);
          goto LAB_0040e1b0;
        }
        if (param_1 != 'd') {
          if (param_1 != 'j') {
            if (param_1 != 'a') {
              return 0;
            }
            goto LAB_0040e182;
          }
          cVar1 = *(char *)(in_ECX + 0xbe);
          goto LAB_0040e188;
        }
        if (*(char *)(in_ECX + 0xbe) == '\x05') {
          return 1;
        }
        cVar1 = *(char *)(in_ECX + 0xbf);
        goto LAB_0040e190;
      }
      if (*(char *)(in_ECX + 0xbe) == '\x05') {
        return 1;
      }
      if (*(char *)(in_ECX + 0xbf) == '\x05') {
        return 1;
      }
      cVar1 = *(char *)(in_ECX + 0xc0);
      goto LAB_0040e198;
    }
    if (*(char *)(in_ECX + 0xbe) == '\x05') {
      return 1;
    }
    if (*(char *)(in_ECX + 0xbf) == '\x05') {
      return 1;
    }
    if (*(char *)(in_ECX + 0xc0) == '\x05') {
      return 1;
    }
    if (*(char *)(in_ECX + 0xc3) == '\x05') {
      return 1;
    }
    cVar1 = *(char *)(in_ECX + 0xc4);
  }
  if (cVar1 == '\x05') {
    return 1;
  }
  cVar1 = *(char *)(in_ECX + 0xc2);
LAB_0040e1b0:
  if (cVar1 == '\x05') {
    return 1;
  }
  return 0;
}

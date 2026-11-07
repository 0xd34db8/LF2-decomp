/* Function: FUN_00422f60 */
/* Address: 0x00422f60 */

char FUN_00422f60(int param_1)

{
  char cVar1;
  SHORT SVar2;
  short sVar3;
  char cVar4;
  
  cVar1 = '\0';
  cVar4 = (char)param_1;
  if (param_1 == 0x20) {
    return ' ';
  }
  if (param_1 - 0x41U < 0x1a) {
    if ((DAT_00455388 != 'd') || (SVar2 = GetKeyState(0x14), SVar2 != 0)) {
      sVar3 = GetKeyState(0x14);
joined_r0x00423015:
      if ((sVar3 < 1) || (DAT_00455388 == 'd')) {
        cVar1 = cVar4 + ' ';
        goto LAB_00422fa9;
      }
    }
  }
  else {
    if (param_1 - 0x60U < 10) {
      cVar1 = cVar4 + -0x30;
      goto LAB_00422fa9;
    }
    if (param_1 == 0x6b) {
      return '+';
    }
    if (param_1 == 0x6d) {
      return '-';
    }
    if (param_1 == 0x6a) {
      return '*';
    }
    if (param_1 == 0x6f) {
      return '/';
    }
    if (param_1 == 0x6e) {
      return '.';
    }
    if (param_1 - 0x41U < 0x1a) {
      if ((DAT_00455388 != 'd') || (SVar2 = GetKeyState(0x14), SVar2 != 0)) {
        sVar3 = GetKeyState(0x14);
        goto joined_r0x00423015;
      }
    }
    else {
      if (DAT_00455388 == 'd') {
        if (param_1 == 0xbd) {
          return '_';
        }
        if (param_1 == 0xbb) {
          return '+';
        }
        if (param_1 == 0xdb) {
          return '{';
        }
        if (param_1 == 0xdd) {
          return '}';
        }
        if (param_1 == 0xba) {
          return ':';
        }
        if (param_1 == 0xde) {
          return '\"';
        }
        if (param_1 == 0xdc) {
          return '|';
        }
        if (param_1 == 0xbc) {
          return '<';
        }
        if (param_1 == 0xbe) {
          return '>';
        }
        if (param_1 == 0xbf) {
          return '?';
        }
        if (param_1 == 0xc0) {
          return '~';
        }
        if (param_1 == 0x31) {
          return '!';
        }
        if (param_1 == 0x32) {
          return '@';
        }
        if (param_1 == 0x33) {
          return '#';
        }
        if (param_1 == 0x34) {
          return '$';
        }
        if (param_1 == 0x35) {
          return '%';
        }
        if (param_1 == 0x36) {
          return '^';
        }
        if (param_1 == 0x37) {
          return '&';
        }
        if (param_1 == 0x38) {
          return '*';
        }
        if (param_1 == 0x39) {
          return '(';
        }
        if (param_1 == 0x30) {
          return ')';
        }
        goto LAB_00422fa9;
      }
      if (9 < param_1 - 0x30U) {
        if (param_1 == 0xbd) {
          return '-';
        }
        if (param_1 == 0xbb) {
          return '=';
        }
        if (param_1 == 0xdb) {
          return '[';
        }
        if (param_1 == 0xdd) {
          return ']';
        }
        if (param_1 == 0xba) {
          return ';';
        }
        if (param_1 == 0xde) {
          return '\'';
        }
        if (param_1 == 0xdc) {
          return '\\';
        }
        if (param_1 == 0xbc) {
          return ',';
        }
        if (param_1 == 0xbe) {
          return '.';
        }
        if (param_1 == 0xbf) {
          return '/';
        }
        if (param_1 == 0xc0) {
          return '`';
        }
        goto LAB_00422fa9;
      }
    }
  }
  cVar1 = cVar4;
LAB_00422fa9:
  if (param_1 == 0x21) {
    return '9';
  }
  if (param_1 == 0x22) {
    return '3';
  }
  if (param_1 == 0x23) {
    return '1';
  }
  if (param_1 == 0x24) {
    return '7';
  }
  if (param_1 == 0x25) {
    return '4';
  }
  if (param_1 == 0x26) {
    return '8';
  }
  if (param_1 == 0x27) {
    return '6';
  }
  if (param_1 == 0x28) {
    return '2';
  }
  if (param_1 == 0xc) {
    return '5';
  }
  if (param_1 == 0x2d) {
    cVar1 = '0';
  }
  return cVar1;
}

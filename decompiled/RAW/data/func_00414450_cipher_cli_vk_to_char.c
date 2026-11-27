/* Function: FUN_00414450 */
/* Address: 0x00414450 */

char FUN_00414450(uint param_1)

{
  char cVar1;
  SHORT SVar2;
  char cVar3;
  
  cVar1 = '\0';
  cVar3 = (char)param_1;
  if (param_1 == 0x20) {
    return ' ';
  }
  if (param_1 - 0x41 < 0x1a) {
    if ((DAT_00455388 == 'd') && (SVar2 = GetKeyState(0x14), SVar2 == 0)) {
      return cVar3;
    }
    SVar2 = GetKeyState(0x14);
    if ((0 < SVar2) && (DAT_00455388 != 'd')) {
      return cVar3;
    }
  }
  else {
    if (param_1 - 0x60 < 10) {
      return cVar3 + -0x30;
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
    if (0x19 < param_1 - 0x41) {
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
      }
      else {
        if (param_1 - 0x30 < 10) goto LAB_0041450a;
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
          cVar1 = '`';
        }
      }
      return cVar1;
    }
    if (((DAT_00455388 == 'd') && (SVar2 = GetKeyState(0x14), SVar2 == 0)) ||
       ((SVar2 = GetKeyState(0x14), 0 < SVar2 && (DAT_00455388 != 'd')))) goto LAB_0041450a;
  }
  param_1 = (uint)(byte)(cVar3 + 0x20);
LAB_0041450a:
  return (char)param_1;
}


/* Function: FUN_00414b70 */
/* Address: 0x00414b70 */

void FUN_00414b70(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  code *pcVar5;
  char *pcVar6;
  bool bVar7;
  undefined4 uVar8;
  char local_130 [300];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)local_130;
  if (DAT_0044f820 == 0) {
    DAT_0044f81c = 0;
    DAT_0044f628 = 0;
    sprintf(local_130,"Doing what (\'E\'=encrp, \'D\'=decrp)? ");
    FUN_00401290(DAT_00455608,local_130,0,0xffffff,0x46,0x46);
    if (DAT_004553bd == 'd') {
      DAT_004553bd = 'u';
      DAT_0044f820 = 1;
    }
    else if (DAT_004553bc == 'd') {
      DAT_004553bc = 'u';
      DAT_0044f820 = 2;
    }
    goto LAB_00415116;
  }
  if (DAT_0044f820 == 1) {
    iVar3 = 0;
    iVar2 = DAT_0044f81c;
    do {
      if ((&DAT_00455378)[iVar3] == 'd') {
        cVar1 = FUN_00414450(iVar3);
        iVar2 = DAT_0044f81c;
        if (cVar1 == '\0') {
LAB_00414c5e:
          if (iVar3 == 8) {
LAB_00414c63:
            if (0 < DAT_0044f81c) {
              (&DAT_0044f627)[DAT_0044f81c] = 0;
              iVar2 = DAT_0044f81c + -1;
              goto LAB_00414c70;
            }
          }
        }
        else {
          if (iVar3 == 8) goto LAB_00414c63;
          if ((0x31 < DAT_0044f81c) || (iVar3 == 0xd)) goto LAB_00414c5e;
          (&DAT_0044f628)[DAT_0044f81c] = cVar1;
          (&DAT_0044f629)[DAT_0044f81c] = 0;
          iVar2 = DAT_0044f81c + 1;
LAB_00414c70:
          DAT_0044f81c = iVar2;
          (&DAT_00455378)[iVar3] = 0x75;
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 300);
    if (DAT_00455385 == 'd') {
      if (iVar2 == 0) {
        DAT_00455385 = 'u';
      }
      else {
        if (iVar2 < 1) goto LAB_00414ff2;
        iVar2 = 7;
        bVar7 = true;
        pcVar4 = &DAT_0044f628;
        pcVar6 = "helpme";
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          bVar7 = *pcVar4 == *pcVar6;
          pcVar4 = pcVar4 + 1;
          pcVar6 = pcVar6 + 1;
        } while (bVar7);
        DAT_00455385 = 'u';
        if (bVar7) {
          FUN_004146b0("data\\template.txt");
          FUN_004146b0("data\\julian.txt");
          FUN_004146b0("data\\firzen.txt");
          FUN_004146b0("data\\louisEX.txt");
          FUN_004146b0("data\\bat.txt");
          FUN_004146b0("data\\justin.txt");
          FUN_004146b0("data\\knight.txt");
          FUN_004146b0("data\\jan.txt");
          FUN_004146b0("data\\monk.txt");
          FUN_004146b0("data\\sorcerer.txt");
          FUN_004146b0("data\\jack.txt");
          FUN_004146b0("data\\mark.txt");
          FUN_004146b0("data\\hunter.txt");
          FUN_004146b0("data\\bandit.txt");
          FUN_004146b0("data\\deep.txt");
          FUN_004146b0("data\\john.txt");
          FUN_004146b0("data\\henry.txt");
          FUN_004146b0("data\\rudolf.txt");
          FUN_004146b0("data\\louis.txt");
          FUN_004146b0("data\\firen.txt");
          FUN_004146b0("data\\freeze.txt");
          FUN_004146b0("data\\dennis.txt");
          FUN_004146b0("data\\woody.txt");
          FUN_004146b0("data\\davis.txt");
          FUN_004146b0("data\\weapon0.txt");
          FUN_004146b0("data\\weapon2.txt");
          FUN_004146b0("data\\weapon4.txt");
          FUN_004146b0("data\\weapon5.txt");
          FUN_004146b0("data\\weapon6.txt");
          FUN_004146b0("data\\weapon1.txt");
          FUN_004146b0("data\\weapon3.txt");
          FUN_004146b0("data\\weapon8.txt");
          FUN_004146b0("data\\weapon9.txt");
          FUN_004146b0("data\\weapon10.txt");
          FUN_004146b0("data\\weapon11.txt");
          FUN_004146b0("data\\criminal.txt");
          FUN_004146b0("data\\john_ball.txt");
          FUN_004146b0("data\\henry_arrow1.txt");
          FUN_004146b0("data\\rudolf_weapon.txt");
          FUN_004146b0("data\\deep_ball.txt");
          FUN_004146b0("data\\henry_wind.txt");
          FUN_004146b0("data\\dennis_ball.txt");
          FUN_004146b0("data\\woody_ball.txt");
          FUN_004146b0("data\\davis_ball.txt");
          FUN_004146b0("data\\henry_arrow2.txt");
          FUN_004146b0("data\\freeze_ball.txt");
          FUN_004146b0("data\\firen_ball.txt");
          FUN_004146b0("data\\firen_flame.txt");
          FUN_004146b0("data\\freeze_column.txt");
          FUN_004146b0("data\\weapon7.txt");
          FUN_004146b0("data\\john_biscuit.txt");
          FUN_004146b0("data\\dennis_chase.txt");
          FUN_004146b0("data\\jack_ball.txt");
          FUN_004146b0("data\\jan_chaseh.txt");
          FUN_004146b0("data\\jan_chase.txt");
          FUN_004146b0("data\\firzen_chasef.txt");
          FUN_004146b0("data\\firzen_chasei.txt");
          FUN_004146b0("data\\firzen_ball.txt");
          FUN_004146b0("data\\bat_ball.txt");
          FUN_004146b0("data\\bat_chase.txt");
          FUN_004146b0("data\\justin_ball.txt");
          FUN_004146b0("data\\julian_ball.txt");
          FUN_004146b0("data\\julian_ball2.txt");
          FUN_004146b0("data\\etc.txt");
          FUN_004146b0("data\\broken_weapon.txt");
          FUN_004146b0("bg\\sys\\hkc\\bg.txt");
          FUN_004146b0("bg\\sys\\sp\\bg.txt");
          FUN_004146b0("bg\\sys\\lf\\bg.txt");
          FUN_004146b0("bg\\sys\\gw\\bg.txt");
          FUN_004146b0("bg\\sys\\qi\\bg.txt");
          FUN_004146b0("bg\\sys\\ft\\bg.txt");
          FUN_004146b0("bg\\sys\\cuhk\\bg.txt");
          FUN_004146b0("bg\\sys\\thv\\bg.txt");
          FUN_004146b0("bg\\template\\1\\bg.txt");
          FUN_004146b0("bg\\template\\2\\bg.txt");
          FUN_004146b0("bg\\template\\3\\bg.txt");
          FUN_004146b0("data\\data.txt");
        }
        else {
          FUN_004146b0(&DAT_0044f628);
        }
      }
      DAT_0044f820 = 0;
    }
LAB_00414ff2:
    pcVar5 = sprintf_exref;
    sprintf(local_130,"Encrp what file? ");
    uVar8 = 0x6464ff;
  }
  else {
    if (DAT_0044f820 != 2) goto LAB_00415116;
    iVar3 = 0;
    iVar2 = DAT_0044f81c;
    do {
      if ((&DAT_00455378)[iVar3] == 'd') {
        cVar1 = FUN_00414450(iVar3);
        iVar2 = DAT_0044f81c;
        if (cVar1 == '\0') {
LAB_00415060:
          if (iVar3 == 8) {
LAB_00415065:
            if (0 < DAT_0044f81c) {
              (&DAT_0044f627)[DAT_0044f81c] = 0;
              iVar2 = DAT_0044f81c + -1;
              goto LAB_00415072;
            }
          }
        }
        else {
          if (iVar3 == 8) goto LAB_00415065;
          if ((0x31 < DAT_0044f81c) || (iVar3 == 0xd)) goto LAB_00415060;
          (&DAT_0044f628)[DAT_0044f81c] = cVar1;
          (&DAT_0044f629)[DAT_0044f81c] = 0;
          iVar2 = DAT_0044f81c + 1;
LAB_00415072:
          DAT_0044f81c = iVar2;
          (&DAT_00455378)[iVar3] = 0x75;
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 300);
    if (DAT_00455385 == 'd') {
      if (iVar2 == 0) {
        DAT_00455385 = 'u';
      }
      else {
        if (iVar2 < 1) goto LAB_004150bb;
        DAT_00455385 = 'u';
        FUN_004148a0(&DAT_0044f628);
      }
      DAT_0044f820 = 0;
    }
LAB_004150bb:
    pcVar5 = sprintf_exref;
    sprintf(local_130,"Decrp what file? ");
    uVar8 = 0xaaff00;
  }
  FUN_00401290(DAT_00455608,local_130,0,uVar8,0x46,0x46);
  (*pcVar5)(local_130,&DAT_00448954,&DAT_0044f628);
  FUN_00401290(DAT_00455608,local_130,0,0xffbe96,0x50,0x5a);
LAB_00415116:
  FUN_0043e940(DAT_00458348);
  __security_check_cookie(local_4 ^ (uint)local_130);
  return;
}

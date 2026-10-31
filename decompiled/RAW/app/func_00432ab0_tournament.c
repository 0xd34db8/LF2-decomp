/*
 * Virtual Address: 0x00432AB0
 * Function: tournament_championship_process
 * Class / Subsystem: Application / Championship Tournament Mode
 *
 * Description:
 *   Authentic state machine and knockout bracket manager for LF2 Championship Mode:
 *   - State 0x14: Tournament entry initialization (resets 8 contestant slots with randoms/computers)
 *   - State 0x15: Character & human/computer selection for all 8 bracket slots
 *   - State 0x16: Bracket confirmation and setup screen
 *   - State 0x17: 50-step random swap shuffle of contestant seeds
 *   - State 0x18: Auto-fills unassigned bracket slots with random CPU characters
 *   - State 0x19: Bracket overview ladder and difficulty selection (Easy, Normal, Difficult)
 *   - State 0x1A: Match selector across rounds (Prelminar round 0, SemiFinal round 2, Final round 4).
 *                 Simulates CPU vs CPU matches with difficulty degradation formula;
 *                 dispatches human matches to live battle setup.
 *   - State 0x1B: Controller assignment screen for human matches
 *   - State 0x1C: Match completion handler: records survivor HP, advances winner to next round
 *   - State 0x1D: Tournament champion celebration and victory podium screen
 */

void FUN_00432ab0(undefined4 param_1,int *param_2,undefined4 *param_3)
{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  uint uVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  undefined4 uVar13;
  char *pcVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int *local_9f4;
  int local_9f0;
  undefined4 local_9ec;
  uint local_9e8;
  int *local_9e4;
  int local_9e0;
  undefined4 *local_9dc;
  _SYSTEMTIME local_9d8;
  int aiStack_9c8 [499];
  char cStack_1f9;
  char local_1f8 [6];
  char acStack_1f2 [494];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_9f4;
  local_9ec = param_1;
  local_9f4 = param_2;
  local_9dc = param_3;
  FUN_00431b70();
  if (*param_2 == 0x14) {
    *param_2 = 0x15;
    DAT_004513e8 = 0;
    DAT_004513e4 = 0;
    DAT_00451344 = 1;
    DAT_0044d0c0 = -1;
    DAT_00451364 = 0;
    DAT_0044d0e0 = 0;
    DAT_00451348 = 1;
    DAT_0044d0c4 = -1;
    DAT_00451368 = 0;
    DAT_0044d0e4 = 1;
    DAT_0045134c = 1;
    DAT_0044d0c8 = -1;
    DAT_0045136c = 0;
    DAT_0044d0e8 = 2;
    DAT_00451350 = 1;
    DAT_0044d0cc = -1;
    DAT_00451370 = 0;
    DAT_0044d0ec = 3;
    DAT_00451354 = 1;
    DAT_0044d0d0 = -1;
    _DAT_00451374 = 0;
    _DAT_0044d0f0 = 4;
    DAT_00451358 = 1;
    DAT_0044d0d4 = -1;
    _DAT_00451378 = 0;
    _DAT_0044d0f4 = 5;
    DAT_0045135c = 1;
    DAT_0044d0d8 = -1;
    _DAT_0045137c = 0;
    _DAT_0044d0f8 = 6;
    DAT_00451360 = 1;
    DAT_0044d0dc = -1;
    _DAT_00451380 = 0;
    _DAT_0044d0fc = 7;
  }
  if (0x14 < *param_2) {
    DAT_004513e0 = (DAT_004513e0 + 1) % 0x1e;
    if (*param_2 < 0x18) {
      local_9e4 = (int *)0x1b;
      local_9e0 = 0x6a;
      FUN_0043f010(0x1b,0x6a,0,0,0,local_9ec);
      FUN_00415160(0x2f,0x180,0x83,0x29,0x324d9a);
    }
    else {
      local_9e4 = (int *)0xffffffcd;
      local_9e0 = 0x7e;
      FUN_0043f010(0x77,0x7e,9,0,0,local_9ec);
    }
    iVar1 = local_9f0;
    iVar10 = DAT_004513e8;
    if (DAT_004513e8 < 8) {
      if (DAT_004513e4 == 0) {
        if (DAT_004513a4 != 0) {
          (&DAT_0044d0c0)[DAT_004513e8] = -1;
          (&DAT_00451344)[iVar10] = 1;
        }
        iVar6 = DAT_00458428;
        if (DAT_004513b0 != 0) {
          (&DAT_0044d0c0)[iVar10] = (&DAT_0044d0c0)[iVar10] + 1;
          iVar5 = (&DAT_0044d0c0)[iVar10];
          (&DAT_00451344)[iVar10] = 0;
          iVar12 = *(int *)(local_9f0 + 0x7d4);
          if (iVar5 < *(int *)(iVar12 + 0x4d82380)) {
            do {
              iVar12 = *(int *)(iVar12 + iVar5 * 4);
              if ((*(int *)(iVar12 + 0x6f8) == 0) &&
                 (((iVar12 = *(int *)(iVar12 + 0x6f4) / 10, iVar12 != 5 && (iVar12 != 3)) ||
                  (iVar6 == 1)))) goto LAB_00432d56;
              iVar5 = iVar5 + 1;
              (&DAT_0044d0c0)[iVar10] = iVar5;
              (&DAT_00451344)[iVar10] = 0;
              iVar12 = *(int *)(local_9f0 + 0x7d4);
            } while (iVar5 < *(int *)(iVar12 + 0x4d82380));
          }
          (&DAT_0044d0c0)[iVar10] = -1;
          (&DAT_00451344)[iVar10] = 1;
        }
LAB_00432d56:
        if (DAT_004513ac != 0) {
          (&DAT_0044d0c0)[iVar10] = (&DAT_0044d0c0)[iVar10] + -1;
          iVar6 = (&DAT_0044d0c0)[iVar10];
          iVar5 = iVar6 + 1;
          (&DAT_00451344)[iVar10] = 0;
          if (iVar6 != -1) {
            do {
              if (SBORROW4(iVar6,-1) != iVar5 < 0) {
                (&DAT_0044d0c0)[iVar10] = *(int *)(*(int *)(local_9f0 + 0x7d4) + 0x4d82380) + -1;
              }
              iVar5 = (&DAT_0044d0c0)[iVar10];
              iVar6 = *(int *)(*(int *)(local_9f0 + 0x7d4) + iVar5 * 4);
              if ((*(int *)(iVar6 + 0x6f8) == 0) &&
                 (((iVar6 = *(int *)(iVar6 + 0x6f4) / 10, iVar6 != 5 && (iVar6 != 3)) ||
                  (DAT_00458428 == 1)))) goto LAB_00432df8;
              iVar6 = iVar5 + -1;
              (&DAT_0044d0c0)[iVar10] = iVar6;
              (&DAT_00451344)[iVar10] = 0;
            } while (iVar5 != 0);
          }
          (&DAT_00451344)[iVar10] = 1;
        }
LAB_00432df8:
        if (DAT_004513b4 == 0) {
          if (DAT_004513b8 != 0) {
            DAT_004513b8 = 0;
            FUN_00401a30(0);
            iVar10 = DAT_004513e8;
            if (DAT_004513e8 < 1) {
              *local_9f4 = 10;
              FUN_00431c70();
              DAT_00457580 = 0;
            }
            else {
              iVar10 = DAT_004513e8 + -1;
              DAT_004513e4 = 1;
              DAT_004513e8 = iVar10;
            }
          }
        }
        else {
          DAT_004513b4 = 0;
          FUN_00401a30(0);
          DAT_004513e4 = 1;
          iVar10 = DAT_004513e8;
        }
      }
      iVar6 = local_9e0;
      piVar11 = local_9e4;
      uVar9 = 0xff;
      local_9e8 = 0xff;
      if (DAT_004513e4 == 0) {
        iVar5 = (DAT_004513e0 % 6) * 0x1e;
        uVar9 = iVar5 + 0x19;
        local_9e8 = iVar5 + 0x46;
      }
      if ((&DAT_0044d0c0)[iVar10] < 0) {
        FUN_0043f010((int)local_9e4 + 0x19,local_9e0 + 0x35,0xffffffff,0,0,local_9ec);
        iVar10 = (int)piVar11 + 0x3b;
        FUN_00401290(DAT_00455608," Random",0,(local_9e8 & 0xff | 0xff00) << 8 | uVar9 & 0xff,iVar10
                     ,iVar6 + 0xce);
      }
      else {
        FUN_0043f010((int)local_9e4 + 0x19,local_9e0 + 0x35,0xffffffff,0,0,local_9ec);
        iVar10 = (int)local_9e4 + 0x3b;
        FUN_00401290(DAT_00455608,
                     *(int *)(*(int *)(iVar1 + 0x7d4) + (&DAT_0044d0c0)[DAT_004513e8] * 4) + 0x25324
                     ,0,(local_9e8 & 0xff | 0xff00) << 8 | uVar9 & 0xff,iVar10,iVar6 + 0xce);
      }
      iVar5 = DAT_004513e8;
      iVar1 = DAT_004513e4;
      if (DAT_004513e4 == 1) {
        if ((DAT_004513b0 != 0) || (DAT_004513ac != 0)) {
          (&DAT_00451364)[DAT_004513e8] = (uint)((int)(&DAT_00451364)[DAT_004513e8] < 1);
        }
        if (DAT_004513b4 == 0) {
          if (DAT_004513b8 != 0) {
            DAT_004513b8 = 0;
            FUN_00401a30(0);
            DAT_004513e4 = DAT_004513e4 + -1;
            goto LAB_00433050;
          }
          goto LAB_00433058;
        }
        DAT_004513b4 = 0;
        FUN_00401a30(0);
        iVar10 = DAT_004513e8 + 1;
        DAT_004513e4 = 0;
        DAT_004513e8 = iVar10;
        if (iVar10 == 8) {
          *local_9f4 = 0x16;
          DAT_004513dc = 0;
        }
      }
      else {
LAB_00433050:
        if (0 < DAT_004513e4) {
          iVar1 = DAT_004513e4;
          iVar5 = DAT_004513e8;
LAB_00433058:
          uVar7 = 0xff;
          uVar9 = 0xff;
          if (iVar1 == 1) {
            iVar1 = (DAT_004513e0 % 6) * 0x1e;
            uVar9 = iVar1 + 0x19;
            uVar7 = iVar1 + 0x46;
          }
          if ((&DAT_00451364)[iVar5] == 0) {
            pcVar14 = "Computer";
          }
          else {
            pcVar14 = " Human";
          }
          FUN_00401290(DAT_00455608,pcVar14,0,(uVar7 & 0xff | 0xff00) << 8 | uVar9 & 0xff,iVar10,
                       iVar6 + 0xfd);
        }
        iVar10 = DAT_004513e8;
      }
    }
    iVar6 = 0;
    iVar1 = 0;
    _DAT_00451340 = 0;
    if (0 < iVar10) {
      do {
        if (0 < (int)(&DAT_00451364)[iVar1]) {
          iVar6 = iVar6 + 1;
          (&DAT_00451364)[iVar1] = iVar6;
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < iVar10);
      _DAT_00451340 = iVar6;
    }
    iVar1 = 0;
    if (0 < iVar10) {
      piVar11 = local_9e4 + 0x36;
      do {
        iVar10 = (&DAT_0044d0e0)[iVar1];
        uVar9 = 0x4d;
        local_9e8 = 0xe6;
        if ((&DAT_0044d0c0)[iVar10] < 0) {
          uVar16 = 1;
        }
        else {
          uVar16 = 0xffffffff;
        }
        FUN_0043f010(piVar11,local_9e0 + 0x104,uVar16,0,0,DAT_00455608);
        if ((&DAT_00451364)[iVar10] == 0) {
          uVar9 = 200;
          DAT_0044d31c = 'C';
          bVar4 = 0x96;
        }
        else {
          DAT_0044d31c = *(char *)(&DAT_00451364 + iVar10) + '0';
          bVar4 = (byte)local_9e8;
        }
        FUN_00401290(DAT_00455608,&DAT_0044d31c,0x8f472f,(uint)bVar4 << 0x10 | uVar9 | 0x7900,
                     (int)piVar11 + 0xd,local_9e0 + 0x133);
        iVar1 = iVar1 + 1;
        piVar11 = piVar11 + 0xf;
        iVar10 = DAT_004513e8;
      } while (iVar1 < DAT_004513e8);
    }
    iVar1 = local_9e0;
    piVar11 = local_9e4;
    if (iVar10 < 8) {
      iVar6 = (&DAT_0044d0e0)[iVar10];
      uVar9 = 0x4d;
      local_9e8 = 0xe6;
      if ((&DAT_0044d0c0)[iVar10] < 0) {
        uVar16 = 1;
      }
      else {
        uVar16 = 0xffffffff;
      }
      FUN_0043f010(local_9e4 + iVar10 * 0xf + 0x36,local_9e0 + 0x104,uVar16,0,0,DAT_00455608);
      if (0 < DAT_004513e4) {
        if ((&DAT_00451364)[iVar6] == 0) {
          uVar9 = 200;
          DAT_0044d31c = 'C';
          bVar4 = 0x96;
        }
        else {
          DAT_0044d31c = DAT_00451340 + '1';
          bVar4 = (byte)local_9e8;
        }
        FUN_00401290(DAT_00455608,&DAT_0044d31c,0x8f472f,(uint)bVar4 << 0x10 | uVar9 | 0x7900,
                     (int)piVar11 + DAT_004513e8 * 0x3c + 0xe5,iVar1 + 0x133);
      }
    }
  }
  uVar16 = local_9ec;
  piVar11 = local_9f4;
  if (*local_9f4 == 0x16) {
    FUN_0043f010(0x116,0xa2,2,0,0,local_9ec);
    FUN_0043f010(0x13a,0xb3,3,0,0,uVar16);
    FUN_0043f010(0x142,0xe8,5,0,0,uVar16);
    FUN_0043f010(0x1aa,0xe8,6,0,0,uVar16);
    if (DAT_004513dc == 0) {
      uVar17 = 7;
      uVar15 = 0xe5;
      uVar13 = 0x13f;
    }
    else {
      uVar17 = 8;
      uVar15 = 0xe6;
      uVar13 = 0x1a4;
    }
    FUN_0043f010(uVar13,uVar15,uVar17,0,0,uVar16);
    if ((DAT_004513ac != 0) || (DAT_004513b0 != 0)) {
      DAT_004513dc = 1 - DAT_004513dc;
    }
    if (DAT_004513b4 == 0) {
      if (DAT_004513b8 != 0) {
        FUN_00401a30(0);
        DAT_004513b8 = 0;
        *piVar11 = 0x15;
        DAT_004513e4 = 1;
        DAT_004513e8 = 7;
        DAT_0044d0e0 = 0;
        DAT_0044d0e4 = 1;
        DAT_0044d0e8 = 2;
        DAT_0044d0ec = 3;
        _DAT_0044d0f0 = 4;
        _DAT_0044d0f4 = 5;
        _DAT_0044d0f8 = 6;
        _DAT_0044d0fc = 7;
      }
      goto LAB_00433497;
    }
    DAT_004513b4 = 0;
    FUN_00401a30(0);
    if (DAT_004513dc == 0) {
      *piVar11 = 0x17;
      DAT_004513d8 = 0;
      goto LAB_004334a0;
    }
    DAT_004513dc = 0;
    *piVar11 = 0x18;
LAB_00433550:
    iVar10 = 0;
    do {
      iVar1 = 1;
      if (*(int *)((int)&DAT_00451344 + iVar10) == 1) {
        piVar11 = *(int **)(local_9f0 + 0x7d4);
        iVar6 = piVar11[0x13608e0];
        iVar5 = 0;
        if (1 < iVar6) {
          do {
            piVar11 = piVar11 + 1;
            if (((*(int *)(*piVar11 + 0x6f8) == 0) &&
                (DAT_0044d0dc != iVar1 &&
                 (DAT_0044d0d8 != iVar1 &&
                 (DAT_0044d0d4 != iVar1 &&
                 (DAT_0044d0d0 != iVar1 &&
                 (DAT_0044d0cc != iVar1 &&
                 (DAT_0044d0c8 != iVar1 && (DAT_0044d0c4 != iVar1 && DAT_0044d0c0 != iVar1))))))))
               && (*(int *)(*piVar11 + 0x6f4) < 0x1e)) {
              aiStack_9c8[iVar5] = iVar1;
              iVar5 = iVar5 + 1;
            }
            iVar1 = iVar1 + 1;
          } while (iVar1 < iVar6);
          uVar16 = local_9ec;
        }
        iVar1 = FUN_00417170(0xf9,iVar5);
        *(int *)((int)&DAT_0044d0c0 + iVar10) = aiStack_9c8[iVar1];
      }
      iVar10 = iVar10 + 4;
    } while (iVar10 < 0x20);
    *local_9f4 = 0x19;
    DAT_004513dc = 2;
LAB_00433660:
    FUN_00402130(2,DAT_004513ac,DAT_004513b0,uVar16);
    FUN_0043f010(3,3,8,0,0,uVar16);
    FUN_0043f010(3,0x9f,0xf,1,0,uVar16);
    if (DAT_004513dc == 0) {
      FUN_0043f010(0x5c,0x10,9,0,0,uVar16);
    }
    if (DAT_004513dc == 1) {
      FUN_0043f010(0x40,0x27,10,0,0,uVar16);
    }
    if (DAT_004513dc == 2) {
      FUN_0043f010(0x28,0x40,0xb,0,0,uVar16);
    }
    if (DAT_004513dc == 3) {
      FUN_0043f010(0xf,0x57,0xc,0,0,uVar16);
    }
    if (DAT_004513dc == 4) {
      FUN_0043f010(0x25,0x6f,0xd,0,0,uVar16);
    }
    if (DAT_004513dc == 5) {
      FUN_0043f010(0x65,0x89,0xe,0,0,uVar16);
    }
    if (DAT_0044d028 == 1) {
      DAT_0044d024 = 100;
    }
    FUN_00401290(DAT_00455608,DAT_0044d024 * 0x990 + 0x4d4617c + *(int *)(local_9f0 + 0x7d4),0,
                 0xff9b9b,0xae,0x5b);
    if (_DAT_00450c30 == 2) {
      FUN_00401290(DAT_00455608,&DAT_00449a30,0,0xff9b9b,0xae,0x73);
    }
    else if (_DAT_00450c30 == 1) {
      FUN_00401290(DAT_00455608,"Normal",0,0xff9b9b,0xae,0x73);
    }
    else if (_DAT_00450c30 == 0) {
      FUN_00401290(DAT_00455608,"Difficult",0,0xff9b9b,0xae,0x73);
    }
    else if (_DAT_00450c30 == -1) {
      FUN_00401290(DAT_00455608,"Difficult",0,0xff9b9b,0xae,0x73);
    }
    if ((DAT_004513a4 != 0) && (DAT_004513dc = DAT_004513dc + -1, DAT_004513dc == -1)) {
      DAT_004513dc = 5;
    }
    if (DAT_004513a8 != 0) {
      DAT_004513dc = (DAT_004513dc + 1) % 6;
    }
    if (DAT_004513b4 == 0) {
      if (DAT_004513b8 != 0) {
        DAT_004513b8 = 0;
        FUN_00401a30(0);
        *local_9f4 = 0x16;
        DAT_004513dc = 0;
        if (DAT_00451344 == 1) {
          DAT_0044d0c0 = -1;
        }
        if (DAT_00451348 == 1) {
          DAT_0044d0c4 = -1;
        }
        if (DAT_0045134c == 1) {
          DAT_0044d0c8 = -1;
        }
        if (DAT_00451350 == 1) {
          DAT_0044d0cc = -1;
        }
        if (DAT_00451354 == 1) {
          DAT_0044d0d0 = -1;
        }
        if (DAT_00451358 == 1) {
          DAT_0044d0d4 = -1;
        }
        if (DAT_0045135c == 1) {
          DAT_0044d0d8 = -1;
        }
        if (DAT_00451360 == 1) {
          DAT_0044d0dc = -1;
        }
      }
    }
    else {
      DAT_004513b4 = 0;
      FUN_00401a30(0);
      piVar11 = local_9f4;
      if (DAT_004513dc == 0) {
        *local_9f4 = 0x1a;
        _DAT_0044d080 = 500;
        _DAT_0044d0a0 = 0xffffffff;
        DAT_00451384 = 0;
        _DAT_0044d084 = 500;
        _DAT_0044d0a4 = 0xffffffff;
        DAT_00451388 = 0;
        _DAT_0044d088 = 500;
        _DAT_0044d0a8 = 0xffffffff;
        DAT_0045138c = 0;
        _DAT_0044d08c = 500;
        _DAT_0044d0ac = 0xffffffff;
        DAT_00451390 = 0;
        _DAT_0044d090 = 500;
        _DAT_0044d0b0 = 0xffffffff;
        _DAT_00451394 = 0;
        _DAT_0044d094 = 500;
        _DAT_0044d0b4 = 0xffffffff;
        _DAT_00451398 = 0;
        _DAT_0044d098 = 500;
        _DAT_0044d0b8 = 0xffffffff;
        _DAT_0045139c = 0;
        _DAT_0044d09c = 500;
        _DAT_0044d0bc = 0xffffffff;
        _DAT_004513a0 = 0;
        DAT_004513d8 = 0x19;
        DAT_0044d318 = 0;
        FUN_004025b0();
      }
      if (DAT_004513dc == 1) {
        *piVar11 = 0x14;
        goto LAB_00434a92;
      }
      if (DAT_004513dc == 2) {
        *piVar11 = 0x18;
        goto LAB_00434a92;
      }
      if (DAT_004513dc == 3) {
        FUN_00401a30(0);
        DAT_0044d028 = 0;
        if (DAT_0044d024 == 100) {
          DAT_0044d024 = 99;
        }
        else if (DAT_0044d024 == 99) {
          DAT_0044d024 = 0;
        }
        else {
          DAT_0044d024 = DAT_0044d024 + 1;
          if (DAT_0044d024 == *(uint *)(*(int *)(local_9f0 + 0x7d4) + 0x4d82384)) {
            DAT_0044d024 = 100;
            DAT_0044d028 = 1;
          }
        }
      }
      else if (DAT_004513dc == 4) {
        _DAT_00450c30 = _DAT_00450c30 + -1;
        if (_DAT_00450c30 < 0) {
          _DAT_00450c30 = 2;
        }
        FUN_00401a30(0);
      }
      else if (DAT_004513dc == 5) {
        *piVar11 = 10;
        FUN_00431c70();
        DAT_00457580 = 0;
      }
    }
  }
  else {
LAB_00433497:
    if (*piVar11 == 0x17) {
LAB_004334a0:
      iVar10 = 0x32;
      do {
        iVar1 = FUN_00417170(0xf7,8);
        iVar6 = FUN_00417170(0xf8,8);
        uVar13 = (&DAT_0044d0e0)[iVar1];
        iVar10 = iVar10 + -1;
        (&DAT_0044d0e0)[iVar1] = (&DAT_0044d0e0)[iVar6];
        (&DAT_0044d0e0)[iVar6] = uVar13;
      } while (iVar10 != 0);
      DAT_004513d8 = DAT_004513d8 + 1;
      if (DAT_004513d8 == (DAT_004513d8 / 5) * 5) {
        FUN_00401a30(0);
      }
      if (10 < DAT_004513d8) {
        *local_9f4 = 0x16;
        DAT_004513dc = 0;
        goto LAB_00434a92;
      }
      piVar11 = local_9f4;
    }
    if (*piVar11 == 0x18) goto LAB_00433550;
    if (*piVar11 == 0x19) goto LAB_00433660;
  }
  if (0x19 < *local_9f4) {
    local_9e8 = 0;
    local_9e4 = &DAT_0044d158;
    do {
      uVar9 = (&DAT_00451384)[local_9e8];
      if ((int)uVar9 < 8) {
        if (uVar9 == 7) goto LAB_00433b29;
      }
      else {
        uVar9 = 7;
LAB_00433b29:
        if (*local_9f4 < 0x1d) {
          *local_9f4 = 0x1d;
          DAT_004513d4 = local_9e8;
          DAT_004513d8 = 0;
        }
      }
      uVar16 = 0xffffff;
      if ((int)uVar9 < 7) {
        uVar7 = uVar9 & 0x80000001;
        if ((int)uVar7 < 0) {
          uVar7 = (uVar7 - 1 | 0xfffffffe) + 1;
        }
        if (uVar7 == 1) {
          uVar16 = 0x102860;
        }
      }
      iVar10 = 0;
      if (0 < (int)uVar9) {
        piVar11 = local_9e4;
        do {
          FUN_00415160(*piVar11 + -0x33,piVar11[1] + 0x7e,(&DAT_0044d120)[iVar10 * 2],
                       (&DAT_0044d124)[iVar10 * 2],uVar16);
          iVar10 = iVar10 + 1;
          piVar11 = piVar11 + 2;
        } while (iVar10 < (int)uVar9);
      }
      local_9e4 = local_9e4 + 0xe;
      local_9e8 = local_9e8 + 1;
    } while ((int)local_9e8 < 8);
  }
  iVar10 = DAT_0044d318;
  if (*local_9f4 == 0x1a) {
    _DAT_004513d0 = 0;
    iVar1 = 0;
    do {
      if ((&DAT_00451384)[iVar1] == iVar10) {
        (&DAT_004513c8)[_DAT_004513d0] = iVar1;
        _DAT_004513d0 = _DAT_004513d0 + 1;
        if (_DAT_004513d0 == 2) break;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 8);
    if (_DAT_004513d0 == 0) {
      if (iVar10 < 6) {
        DAT_0044d318 = iVar10 + 2;
      }
      goto LAB_00433c1e;
    }
    if (_DAT_004513d0 != 2) goto LAB_00433c1e;
    if (0x1e < DAT_004513d8) {
      iVar10 = DAT_004513c8;
      if (4 < DAT_004513e0 % 10) {
        iVar10 = DAT_004513cc;
      }
      iVar1 = (&DAT_00451384)[iVar10] + 2;
      if (7 < iVar1) {
        iVar1 = 7;
      }
      iVar6 = 0;
      if (0 < iVar1) {
        piVar11 = &DAT_0044d158 + iVar10 * 0xe;
        do {
          FUN_00415160(*piVar11 + -0x33,piVar11[1] + 0x7e,(&DAT_0044d120)[iVar6 * 2],
                       (&DAT_0044d124)[iVar6 * 2],0xffa0a0);
          iVar6 = iVar6 + 1;
          piVar11 = piVar11 + 2;
        } while (iVar6 < iVar1);
      }
    }
    iVar10 = local_9f0;
    piVar11 = local_9f4;
    DAT_004513d8 = DAT_004513d8 + 1;
    if (DAT_004513b8 == 0) {
      if (DAT_004513d8 != 0x50) goto LAB_00433c1e;
    }
    else {
      DAT_004513d8 = 0x50;
    }
    if (((&DAT_00451364)[(&DAT_0044d0e0)[DAT_004513c8]] == 0) &&
       ((&DAT_00451364)[(&DAT_0044d0e0)[DAT_004513cc]] == 0)) {
      FUN_00401a30(0);
      iVar10 = local_9f0;
      iVar1 = *(int *)(local_9f0 + 0x7d4);
      iVar6 = *(int *)(*(int *)(iVar1 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513c8]] * 4) + 0x6f4)
              / 10;
      DAT_004513d8 = 0;
      if (iVar6 == 5) {
LAB_00433ffa:
        if (*(int *)(*(int *)(iVar1 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513cc]] * 4) + 0x6f4) /
            10 == 5) {
          if (iVar6 != 5) goto LAB_00434030;
LAB_00434062:
          uVar16 = 0xfb;
LAB_00434069:
          iVar1 = FUN_00417170(uVar16,2);
        }
        else {
          iVar1 = 0;
        }
      }
      else {
        if (*(int *)(*(int *)(iVar1 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513cc]] * 4) + 0x6f4) /
            10 != 5) {
          uVar16 = 0xfa;
          goto LAB_00434069;
        }
        if (iVar6 == 5) goto LAB_00433ffa;
LAB_00434030:
        if (*(int *)(*(int *)(iVar1 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513cc]] * 4) + 0x6f4) /
            10 != 5) goto LAB_00434062;
        iVar1 = 1;
      }
      iVar6 = (&DAT_004513c8)[iVar1];
      (&DAT_00451384)[iVar6] = (&DAT_00451384)[iVar6] + 2;
      (&DAT_00451384)[(&DAT_004513cc)[-iVar1]] = (&DAT_00451384)[(&DAT_004513cc)[-iVar1]] + 1;
      if ((&DAT_00451384)[iVar6] == 6) {
        (&DAT_00451384)[iVar6] = 7;
      }
      iVar6 = _DAT_00450c30;
      if (_DAT_00450c30 < -1) {
        iVar6 = 0;
      }
      iVar1 = (&DAT_004513c8)[iVar1];
      iVar6 = FUN_00417170(0xfc,iVar6 * 0xc + 0xf);
      *(int *)(&DAT_0044d080 + iVar1 * 4) =
           ((iVar6 + _DAT_00450c30 * -0xc + 0x55) * *(int *)(&DAT_0044d080 + iVar1 * 4)) / 100;
    }
    else {
      *local_9f4 = 0x1b;
      DAT_004513d8 = 0;
      memset((void *)(local_9f0 + 4),0,400);
      DAT_004512d0 = 0xffffffff;
      DAT_004512d4 = 0xffffffff;
      DAT_004512d8 = 0xffffffff;
      DAT_004512dc = 0xffffffff;
      DAT_004512e0 = 0xffffffff;
      DAT_004512e4 = 0xffffffff;
      DAT_004512e8 = 0xffffffff;
      DAT_004512ec = 0xffffffff;
      DAT_004512f0 = 0xffffffff;
      DAT_004512f4 = 0xffffffff;
      DAT_004512f8 = 0xffffffff;
      _DAT_004512fc = 0xffffffff;
      _DAT_00451300 = 0xffffffff;
      _DAT_00451304 = 0xffffffff;
      _DAT_00451308 = 0xffffffff;
      _DAT_0045130c = 0xffffffff;
      _DAT_00451310 = 0xffffffff;
      _DAT_00451314 = 0xffffffff;
      _DAT_00451318 = 0xffffffff;
      _DAT_0045131c = 0xffffffff;
      (&DAT_00451384)[DAT_004513c8] = (&DAT_00451384)[DAT_004513c8] + 1;
      (&DAT_00451384)[DAT_004513cc] = (&DAT_00451384)[DAT_004513cc] + 1;
    }
  }
  else {
LAB_00433c1e:
    iVar10 = local_9f0;
    piVar11 = local_9f4;
  }
  if (*piVar11 == 0x1b) {
    if (DAT_004513d8 < 2) {
      if (DAT_004513e0 % 10 < 5) {
        iVar1 = (&DAT_00451384)[(&DAT_004513c8)[DAT_004513d8]] + 1;
        if (7 < iVar1) {
          iVar1 = 7;
        }
        iVar6 = 0;
        if (0 < iVar1) {
          piVar11 = &DAT_0044d158 + (&DAT_004513c8)[DAT_004513d8] * 0xe;
          do {
            FUN_00415160(*piVar11 + -0x33,piVar11[1] + 0x7e,(&DAT_0044d120)[iVar6 * 2],
                         (&DAT_0044d124)[iVar6 * 2],0xffa0a0);
            iVar6 = iVar6 + 1;
            piVar11 = piVar11 + 2;
          } while (iVar6 < iVar1);
        }
      }
      uVar16 = local_9ec;
      if (0 < (int)(&DAT_00451364)[(&DAT_0044d0e0)[(&DAT_004513c8)[DAT_004513d8]]]) {
        FUN_0043f010(10,10,10,0,0,local_9ec);
        FUN_0043f010(0xa9,0x18,(&DAT_00451364)[(&DAT_0044d0e0)[(&DAT_004513c8)[DAT_004513d8]]] + 10,
                     0,0,uVar16);
        FUN_0043f010(0x5a,0x31,0xffffffff,0,0,uVar16);
        iVar1 = 0;
        piVar11 = (int *)(iVar10 + 0x194);
        do {
          if ((*(char *)(*piVar11 + 0xd1) != '\0') && (*(char *)(*piVar11 + 0xca) == '\0')) {
            if (*(char *)(iVar10 + 4 + iVar1) != '\x01') {
              DAT_004513b4 = 0;
              *(undefined1 *)(*(int *)(iVar10 + 0x194 + iVar1 * 4) + 0xca) = 1;
              FUN_00401a30(0);
              (&DAT_004512d0)[iVar1] = (&DAT_004513c8)[DAT_004513d8];
              *(undefined1 *)(iVar10 + 4 + iVar1) = 1;
              piVar11 = &DAT_004513c8 + DAT_004513d8;
              DAT_004513d8 = DAT_004513d8 + 1;
              *(undefined4 *)(*(int *)(iVar10 + 0x194 + iVar1 * 4) + 0x368) =
                   *(undefined4 *)
                    (*(int *)(iVar10 + 0x7d4) + (&DAT_0044d0c0)[(&DAT_0044d0e0)[*piVar11]] * 4);
              break;
            }
            FUN_00401a30(0);
          }
          iVar1 = iVar1 + 1;
          piVar11 = piVar11 + 1;
        } while (iVar1 < 8);
        piVar11 = local_9f4;
        goto LAB_00433dba;
      }
      DAT_004513d8 = DAT_004513d8 + 1;
      DAT_004513dc = 1;
      piVar11 = local_9f4;
    }
    else {
LAB_00433dba:
    }
    uVar16 = local_9ec;
    if (DAT_004513d8 == 2) {
      FUN_0043f010(0x116,0xa2,2,0,0,local_9ec);
      FUN_0043f010(0x13a,0xb3,4,0,0,uVar16);
      FUN_0043f010(0x142,0xe8,5,0,0,uVar16);
      FUN_0043f010(0x1aa,0xe8,6,0,0,uVar16);
      if (DAT_004513dc == 0) {
        uVar17 = 7;
        uVar15 = 0xe5;
        uVar13 = 0x13f;
      }
      else {
        uVar17 = 8;
        uVar15 = 0xe6;
        uVar13 = 0x1a4;
      }
      FUN_0043f010(uVar13,uVar15,uVar17,0,0,uVar16);
      if ((DAT_004513ac != 0) || (DAT_004513b0 != 0)) {
        DAT_004513dc = 1 - DAT_004513dc;
      }
      if (DAT_004513b4 == 0) goto LAB_0043433c;
      DAT_004513b4 = 0;
      FUN_00401a30(0);
      DAT_004513b4 = 0;
      if (DAT_004513dc == 0) {
        DAT_004513d8 = 3;
        goto LAB_00434349;
      }
      DAT_004513d8 = 0;
      memset((void *)(iVar10 + 4),0,400);
      DAT_004512d0 = 0xffffffff;
      DAT_004512d4 = 0xffffffff;
      DAT_004512d8 = 0xffffffff;
      DAT_004512dc = 0xffffffff;
      DAT_004512e0 = 0xffffffff;
      DAT_004512e4 = 0xffffffff;
      DAT_004512e8 = 0xffffffff;
      DAT_004512ec = 0xffffffff;
      DAT_004512f0 = 0xffffffff;
      DAT_004512f4 = 0xffffffff;
      DAT_004512f8 = 0xffffffff;
      _DAT_004512fc = 0xffffffff;
      _DAT_00451300 = 0xffffffff;
      _DAT_00451304 = 0xffffffff;
      _DAT_00451308 = 0xffffffff;
      _DAT_0045130c = 0xffffffff;
      _DAT_00451310 = 0xffffffff;
      _DAT_00451314 = 0xffffffff;
      _DAT_00451318 = 0xffffffff;
      _DAT_0045131c = 0xffffffff;
    }
    else {
LAB_0043433c:
      if (DAT_004513d8 == 3) {
LAB_00434349:
        piVar11 = &DAT_004513c8;
        do {
          if ((&DAT_00451364)[(&DAT_0044d0e0)[*piVar11]] == 0) {
            iVar1 = 0;
            do {
              if (*(char *)(iVar1 + 4 + iVar10) == '\0') {
                FUN_00401a30(0);
                (&DAT_004512f8)[iVar1] = *piVar11;
                *(undefined1 *)(iVar10 + 0xe + iVar1) = 1;
                *(undefined4 *)(*(int *)(iVar10 + 0x1bc + iVar1 * 4) + 0x368) =
                     *(undefined4 *)
                      (*(int *)(iVar10 + 0x7d4) + (&DAT_0044d0c0)[(&DAT_0044d0e0)[*piVar11]] * 4);
                break;
              }
              iVar1 = iVar1 + 1;
            } while (iVar1 < 8);
          }
          piVar11 = piVar11 + 1;
        } while ((int)piVar11 < 0x4513d0);
        *local_9f4 = 0;
        GetLocalTime(&local_9d8);
        sprintf(local_1f8,"%4d%02d%02d_%02d%02d%02d",(uint)local_9d8.wYear,(uint)local_9d8.wMonth,
                (uint)local_9d8.wDay,(uint)local_9d8.wHour,(uint)local_9d8.wMinute,
                (uint)local_9d8.wSecond);
        pcVar14 = &cStack_1f9;
        do {
          pcVar2 = pcVar14;
          pcVar14 = pcVar2 + 1;
        } while (pcVar2[1] != '\0');
        builtin_strncpy(pcVar2 + 1,"_1on1_",7);
        if (DAT_0044d318 == 0) {
          pcVar14 = &cStack_1f9;
          do {
            pcVar2 = pcVar14;
            pcVar14 = pcVar2 + 1;
          } while (pcVar2[1] != '\0');
          builtin_strncpy(pcVar2 + 1,"Prelminar",10);
        }
        else if (DAT_0044d318 == 2) {
          pcVar14 = &cStack_1f9;
          do {
            pcVar2 = pcVar14;
            pcVar14 = pcVar2 + 1;
          } while (pcVar2[1] != '\0');
          builtin_strncpy(pcVar2 + 1,"SemiFinal",10);
        }
        else if (DAT_0044d318 == 4) {
          pcVar14 = &cStack_1f9;
          do {
            pcVar2 = pcVar14;
            pcVar14 = pcVar2 + 1;
          } while (pcVar2[1] != '\0');
          builtin_strncpy(pcVar2 + 1,"Final",6);
        }
        sprintf(&DAT_0044fd98,"%s.lfr",local_1f8);
        DAT_00450b6c = 0;
        if (DAT_00450be4 != 0) {
          DAT_00450b70 = 1;
        }
        if ((DAT_0044d028 == 1) &&
           (DAT_0044d024 = FUN_00417170(0xfd,*(int *)(*(int *)(iVar10 + 0x7d4) + 0x4d82384) + -2),
           DAT_0044d024 == *(int *)(*(int *)(iVar10 + 0x7d4) + 0x4d82384) - 3U)) {
          DAT_0044d024 = 99;
        }
        iVar1 = 0;
        piVar11 = (int *)(iVar10 + 0x194);
        local_9e8 = DAT_0044d024;
        do {
          if (*(char *)(iVar10 + 4 + iVar1) != '\0') {
            iVar6 = *piVar11;
            iVar5 = *(int *)(iVar6 + 0x368);
            FUN_004061d0();
            iVar10 = local_9f0;
            *(int *)(iVar6 + 0x368) = iVar5;
            uVar16 = *(undefined4 *)(iVar5 + 0x90);
            *(undefined8 *)(iVar6 + 0x58) = 0x4075e00000000000;
            *(undefined4 *)(iVar6 + 0x31c) = uVar16;
            *(undefined8 *)(iVar6 + 0x60) = 0;
            *(undefined8 *)(iVar6 + 0x68) = 0x4072c00000000000;
            *(undefined4 *)(*piVar11 + 0x308) = 500;
            *(undefined4 *)(*piVar11 + 0x2fc) =
                 *(undefined4 *)(&DAT_0044d080 + (&DAT_004512d0)[iVar1] * 4);
            *(undefined4 *)(*piVar11 + 0x300) = *(undefined4 *)(*piVar11 + 0x2fc);
            iVar12 = local_9e8 * 0x990;
            *(undefined4 *)(*piVar11 + 0x304) = *(undefined4 *)(*piVar11 + 0x300);
            *(undefined4 *)(*piVar11 + 0x33c) =
                 *(undefined4 *)(&DAT_0044d0a0 + (&DAT_004512d0)[iVar1] * 4);
            *(int *)(*piVar11 + 0x364) = (&DAT_004512d0)[iVar1] + 10;
            *(undefined4 *)(*piVar11 + 8) = 0x4b;
            iVar5 = FUN_00417170(0xfe,*(int *)(*(int *)(local_9f0 + 0x7d4) + 0x4d45db0 + iVar12) / 2
                                );
            iVar6 = *(int *)(*(int *)(iVar10 + 0x7d4) + 0x4d45db0 + iVar12);
            *(int *)(*piVar11 + 0x10) = iVar5 + ((int)(iVar6 + (iVar6 >> 0x1f & 3U)) >> 2);
            iVar6 = FUN_00417170(0xff,*(int *)(*(int *)(iVar10 + 0x7d4) + 0x4d45db8 + iVar12) -
                                      *(int *)(*(int *)(iVar10 + 0x7d4) + 0x4d45db4 + iVar12));
            *(int *)(*piVar11 + 0x18) =
                 iVar6 + *(int *)(*(int *)(iVar10 + 0x7d4) + 0x4d45db4 + iVar12);
            *(undefined4 *)(*piVar11 + 0x14) = 0;
            *(double *)(*piVar11 + 0x58) = (double)*(int *)(*piVar11 + 0x10);
            *(double *)(*piVar11 + 0x68) = (double)*(int *)(*piVar11 + 0x18);
            *(undefined8 *)(*piVar11 + 0x60) = 0;
            *(int *)(*piVar11 + 0x354) = iVar1;
          }
          iVar1 = iVar1 + 1;
          piVar11 = piVar11 + 1;
        } while (iVar1 < 0x14);
        DAT_00450c24 = 0;
        DAT_00450c20 = 0;
        DAT_00450c1c = 0;
        DAT_00450c18 = 0;
        _DAT_00450c14 = 0;
        _DAT_00450c10 = 0;
        _DAT_00450c0c = 0;
        _DAT_00450c08 = 0;
        _DAT_00450c04 = 0;
        DAT_00450c28 = 0;
        iVar1 = 0;
        if (0 < *(int *)(*(int *)(iVar10 + 0x7d4) + 0x4d82384)) {
          do {
            FUN_0040c0e0(iVar1);
            iVar1 = iVar1 + 1;
          } while (iVar1 < *(int *)(*(int *)(iVar10 + 0x7d4) + 0x4d82384));
        }
        if (DAT_0044d024 != 99) {
          FUN_0040c030(DAT_0044d024);
        }
        DAT_00450bbc = 0;
        DAT_0044d034 = 1;
        iVar1 = 0x14;
        do {
          if (*(char *)(iVar1 + 4 + iVar10) == '\0') {
            FUN_004061d0();
          }
          iVar1 = iVar1 + 1;
        } while (iVar1 < 400);
        FUN_00431c70();
        FUN_0043d2c0(*local_9dc,iVar10 + 4,iVar10 + 0x194);
        piVar11 = local_9f4;
        goto LAB_004347c1;
      }
    }
  }
  else {
LAB_004347c1:
    uVar16 = local_9ec;
  }
  if (*piVar11 == 0x1c) {
    piVar3 = &DAT_004512d4;
    piVar8 = (int *)(iVar10 + 0x198);
    do {
      iVar1 = piVar3[-1];
      if (-1 < iVar1) {
        *(undefined4 *)(&DAT_0044d080 + iVar1 * 4) = *(undefined4 *)(piVar8[-1] + 0x300);
        *(undefined4 *)(&DAT_0044d0a0 + iVar1 * 4) = *(undefined4 *)(piVar8[-1] + 0x33c);
      }
      iVar1 = *piVar3;
      if (-1 < iVar1) {
        *(undefined4 *)(&DAT_0044d080 + iVar1 * 4) = *(undefined4 *)(*piVar8 + 0x300);
        *(undefined4 *)(&DAT_0044d0a0 + iVar1 * 4) = *(undefined4 *)(*piVar8 + 0x33c);
      }
      iVar1 = piVar3[1];
      if (-1 < iVar1) {
        *(undefined4 *)(&DAT_0044d080 + iVar1 * 4) = *(undefined4 *)(piVar8[1] + 0x300);
        *(undefined4 *)(&DAT_0044d0a0 + iVar1 * 4) = *(undefined4 *)(piVar8[1] + 0x33c);
      }
      iVar1 = piVar3[2];
      if (-1 < iVar1) {
        *(undefined4 *)(&DAT_0044d080 + iVar1 * 4) = *(undefined4 *)(piVar8[2] + 0x300);
        *(undefined4 *)(&DAT_0044d0a0 + iVar1 * 4) = *(undefined4 *)(piVar8[2] + 0x33c);
      }
      iVar1 = piVar3[3];
      if (-1 < iVar1) {
        *(undefined4 *)(&DAT_0044d080 + iVar1 * 4) = *(undefined4 *)(piVar8[3] + 0x300);
        *(undefined4 *)(&DAT_0044d0a0 + iVar1 * 4) = *(undefined4 *)(piVar8[3] + 0x33c);
      }
      iVar1 = DAT_00450bf8;
      piVar3 = piVar3 + 5;
      piVar8 = piVar8 + 5;
    } while ((int)piVar3 < 0x451324);
    if (DAT_00450bf8 < 10) {
      iVar1 = FUN_00417170(0x100,2);
      iVar1 = (&DAT_004513c8)[iVar1];
      (&DAT_00451384)[iVar1] = (&DAT_00451384)[iVar1] + 1;
      if ((&DAT_00451384)[iVar1] == 6) {
        (&DAT_00451384)[iVar1] = 7;
      }
    }
    else {
      (&DAT_0045135c)[DAT_00450bf8] = (&DAT_0045135c)[DAT_00450bf8] + 1;
      if ((&DAT_0045135c)[iVar1] == 6) {
        (&DAT_0045135c)[iVar1] = 7;
      }
    }
    *piVar11 = 0x1a;
    memset((void *)(iVar10 + 4),0,400);
    DAT_004512d0 = 0xffffffff;
    DAT_004512d4 = 0xffffffff;
    DAT_004512d8 = 0xffffffff;
    DAT_004512dc = 0xffffffff;
    DAT_004512e0 = 0xffffffff;
    DAT_004512e4 = 0xffffffff;
    DAT_004512e8 = 0xffffffff;
    DAT_004512ec = 0xffffffff;
    DAT_004512f0 = 0xffffffff;
    DAT_004512f4 = 0xffffffff;
    DAT_004512f8 = 0xffffffff;
    _DAT_004512fc = 0xffffffff;
    _DAT_00451300 = 0xffffffff;
    _DAT_00451304 = 0xffffffff;
    _DAT_00451308 = 0xffffffff;
    _DAT_0045130c = 0xffffffff;
    _DAT_00451310 = 0xffffffff;
    _DAT_00451314 = 0xffffffff;
    _DAT_00451318 = 0xffffffff;
    _DAT_0045131c = 0xffffffff;
  }
  if (*piVar11 == 0x1d) {
    if (DAT_004513d8 < 0x32) {
      DAT_004513d8 = DAT_004513d8 + 1;
    }
    if (0x14 < DAT_004513d8) {
      if (DAT_004513d8 == 0x15) {
        FUN_00402100();
        FUN_00401a30(0);
      }
      FUN_0043f010(10,10,10,0,0,uVar16);
      if ((&DAT_00451364)[(&DAT_0044d0e0)[DAT_004513d4]] == 0) {
        iVar10 = 0x14;
        uVar15 = 0x16;
        uVar13 = 0x5d;
      }
      else {
        iVar10 = (&DAT_00451364)[(&DAT_0044d0e0)[DAT_004513d4]] + 10;
        uVar15 = 0x18;
        uVar13 = 0xa9;
      }
      FUN_0043f010(uVar13,uVar15,iVar10,0,0,uVar16);
      FUN_0043f010(0x5a,0x31,0xffffffff,0,0,uVar16);
      FUN_0043f010(0x17,0xaf,0x13,0,0,uVar16);
      if ((DAT_004513b4 != 0) && (DAT_004513d8 == 0x32)) {
        *piVar11 = 10;
        FUN_00431c70();
        DAT_00457580 = 0;
      }
    }
  }
LAB_00434a92:
  __security_check_cookie(local_4 ^ (uint)&local_9f4);
  return;
}


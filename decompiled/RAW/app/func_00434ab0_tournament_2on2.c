
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00434ab0(undefined4 param_1,int *param_2,undefined4 *param_3)

{
  char *pcVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  undefined4 uVar13;
  char *pcVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int *local_9f8;
  int local_9f4;
  undefined4 local_9f0;
  int *local_9ec;
  int local_9e8;
  int local_9e4;
  int local_9e0;
  undefined4 *local_9dc;
  _SYSTEMTIME local_9d8;
  int aiStack_9c8 [499];
  char cStack_1f9;
  char local_1f8 [6];
  char acStack_1f2 [494];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_9f8;
  local_9f0 = param_1;
  local_9f8 = param_2;
  local_9dc = param_3;
  FUN_00431b70();
  if (*param_2 == 0x78) {
    *param_2 = 0x79;
    _DAT_0044d108 = 2;
    DAT_0044d0e8 = 2;
    _DAT_0044d10c = 2;
    DAT_00451414 = 0;
    DAT_00451410 = 0;
    DAT_00451344 = 1;
    DAT_0044d0c0 = -1;
    DAT_00451364 = 0;
    DAT_0044d100 = 1;
    DAT_0044d0e0 = 0;
    DAT_00451348 = 1;
    DAT_0044d0c4 = -1;
    DAT_00451368 = 0;
    _DAT_0044d104 = 1;
    DAT_0044d0e4 = 1;
    DAT_0045134c = 1;
    DAT_0044d0c8 = -1;
    DAT_0045136c = 0;
    DAT_00451350 = 1;
    DAT_0044d0cc = -1;
    DAT_00451370 = 0;
    DAT_0044d0ec = 3;
    DAT_00451354 = 1;
    DAT_0044d0d0 = -1;
    _DAT_00451374 = 0;
    _DAT_0044d110 = 3;
    _DAT_0044d0f0 = 4;
    DAT_00451358 = 1;
    DAT_0044d0d4 = -1;
    _DAT_00451378 = 0;
    _DAT_0044d114 = 3;
    _DAT_0044d0f4 = 5;
    DAT_0045135c = 1;
    DAT_0044d0d8 = -1;
    _DAT_0045137c = 0;
    _DAT_0044d118 = 4;
    _DAT_0044d0f8 = 6;
    DAT_00451360 = 1;
    DAT_0044d0dc = -1;
    _DAT_00451380 = 0;
    _DAT_0044d11c = 4;
    _DAT_0044d0fc = 7;
  }
  if (0x78 < *param_2) {
    DAT_0045140c = (DAT_0045140c + 1) % 0x1e;
    if (*param_2 < 0x7c) {
      local_9e0 = 0x1b;
      local_9e8 = 0x6a;
      FUN_0043f010(0x1b,0x6a,0,0,0,local_9f0);
      FUN_00415160(0x2f,0x180,0x83,0x29,0x324d9a);
    }
    else {
      local_9e0 = -0x33;
      local_9e8 = 0x7e;
      FUN_0043f010(0x77,0x7e,9,0,0,local_9f0);
    }
    iVar11 = local_9e0;
    iVar7 = local_9e8;
    uVar16 = local_9f0;
    FUN_0043f010(local_9e0 + 0x135,local_9e8 + 0x17,0x15,0,0,local_9f0);
    FUN_0043f010(iVar11 + 0xe8,iVar7 + 0xd7,0x10,0,0,uVar16);
    piVar6 = &DAT_0044d100;
    iVar11 = iVar11 + 0xed;
    do {
      FUN_00415160(iVar11 + -5,iVar7 + 0xdd,0x49,0x24,0x324d9a);
      FUN_0043f010(iVar11,iVar7 + 0xdf,*piVar6 + 0x10,0,0,local_9f0);
      iVar8 = local_9f4;
      uVar3 = DAT_00451414;
      piVar6 = piVar6 + 2;
      iVar11 = iVar11 + 0x78;
    } while ((int)piVar6 < 0x44d120);
    if ((int)DAT_00451414 < 8) {
      if (DAT_00451410 == 0) {
        if (DAT_004513a4 != 0) {
          (&DAT_0044d0c0)[DAT_00451414] = -1;
          (&DAT_00451344)[uVar3] = 1;
        }
        if (DAT_004513b0 != 0) {
          (&DAT_0044d0c0)[uVar3] = (&DAT_0044d0c0)[uVar3] + 1;
          iVar7 = (&DAT_0044d0c0)[uVar3];
          (&DAT_00451344)[uVar3] = 0;
          iVar11 = *(int *)(local_9f4 + 0x7d4);
          if (iVar7 < *(int *)(iVar11 + 0x4d82380)) {
            do {
              iVar11 = *(int *)(iVar11 + iVar7 * 4);
              if ((*(int *)(iVar11 + 0x6f8) == 0) &&
                 (((iVar11 = *(int *)(iVar11 + 0x6f4) / 10, iVar11 != 5 && (iVar11 != 3)) ||
                  (DAT_00458428 == 1)))) goto LAB_00434e27;
              iVar7 = iVar7 + 1;
              (&DAT_0044d0c0)[uVar3] = iVar7;
              (&DAT_00451344)[uVar3] = 0;
              iVar11 = *(int *)(local_9f4 + 0x7d4);
            } while (iVar7 < *(int *)(iVar11 + 0x4d82380));
          }
          (&DAT_0044d0c0)[uVar3] = -1;
          (&DAT_00451344)[uVar3] = 1;
        }
LAB_00434e27:
        if (DAT_004513ac != 0) {
          (&DAT_0044d0c0)[uVar3] = (&DAT_0044d0c0)[uVar3] + -1;
          iVar7 = (&DAT_0044d0c0)[uVar3];
          iVar11 = iVar7 + 1;
          (&DAT_00451344)[uVar3] = 0;
          if (iVar7 != -1) {
            do {
              if (SBORROW4(iVar7,-1) != iVar11 < 0) {
                (&DAT_0044d0c0)[uVar3] = *(int *)(*(int *)(local_9f4 + 0x7d4) + 0x4d82380) + -1;
              }
              iVar11 = (&DAT_0044d0c0)[uVar3];
              iVar7 = *(int *)(*(int *)(local_9f4 + 0x7d4) + iVar11 * 4);
              if ((*(int *)(iVar7 + 0x6f8) == 0) &&
                 (((iVar7 = *(int *)(iVar7 + 0x6f4) / 10, iVar7 != 5 && (iVar7 != 3)) ||
                  (DAT_00458428 == 1)))) goto LAB_00434ec3;
              iVar7 = iVar11 + -1;
              (&DAT_0044d0c0)[uVar3] = iVar7;
              (&DAT_00451344)[uVar3] = 0;
            } while (iVar11 != 0);
          }
          (&DAT_00451344)[uVar3] = 1;
        }
LAB_00434ec3:
        if (DAT_004513b4 == 0) {
          if (DAT_004513b8 != 0) {
            DAT_004513b8 = 0;
            FUN_00401a30(0);
            if ((int)DAT_00451414 < 1) {
              *local_9f8 = 10;
              FUN_00431c70();
              DAT_00457580 = 0;
              uVar3 = DAT_00451414;
            }
            else {
              DAT_00451414 = DAT_00451414 - 1;
              DAT_00451410 = 1;
              uVar3 = DAT_00451414;
            }
          }
        }
        else {
          DAT_004513b4 = 0;
          FUN_00401a30(0);
          DAT_00451410 = 1;
          uVar3 = DAT_00451414;
        }
      }
      iVar11 = local_9e0;
      iVar7 = local_9e8;
      uVar4 = 0xff;
      local_9ec = (int *)0xff;
      if (DAT_00451410 == 0) {
        iVar9 = (DAT_0045140c % 6) * 0x1e;
        uVar4 = iVar9 + 0x19;
        local_9ec = (int *)(iVar9 + 0x46);
      }
      if ((&DAT_0044d0c0)[uVar3] < 0) {
        FUN_0043f010(local_9e0 + 0x19,local_9e8 + 0x35,0xffffffff,0,0,local_9f0);
        FUN_00401290(DAT_00455608," Random",0,((uint)local_9ec & 0xff | 0xff00) << 8 | uVar4 & 0xff,
                     iVar11 + 0x3b,iVar7 + 0xce);
      }
      else {
        FUN_0043f010(local_9e0 + 0x19,local_9e8 + 0x35,0xffffffff,0,0,local_9f0);
        FUN_00401290(DAT_00455608,
                     *(int *)(*(int *)(iVar8 + 0x7d4) + (&DAT_0044d0c0)[DAT_00451414] * 4) + 0x25324
                     ,0,((uint)local_9ec & 0xff | 0xff00) << 8 | uVar4 & 0xff,iVar11 + 0x3b,
                     iVar7 + 0xce);
      }
      uVar3 = DAT_00451414;
      iVar8 = DAT_00451410;
      if (DAT_00451410 == 1) {
        if ((DAT_004513b0 != 0) || (DAT_004513ac != 0)) {
          (&DAT_00451364)[DAT_00451414] = (uint)((int)(&DAT_00451364)[DAT_00451414] < 1);
        }
        if (DAT_004513b4 == 0) {
          if (DAT_004513b8 != 0) {
            DAT_004513b8 = 0;
            FUN_00401a30(0);
            DAT_00451410 = DAT_00451410 + -1;
            goto LAB_0043510c;
          }
          goto LAB_00435114;
        }
        DAT_004513b4 = 0;
        FUN_00401a30(0);
        uVar3 = DAT_00451414 + 1;
        DAT_00451410 = 0;
        DAT_00451414 = uVar3;
        if (uVar3 == 8) {
          *local_9f8 = 0x7a;
          DAT_00451408 = 0;
        }
      }
      else {
LAB_0043510c:
        if (0 < DAT_00451410) {
          iVar8 = DAT_00451410;
          uVar3 = DAT_00451414;
LAB_00435114:
          uVar5 = 0xff;
          uVar4 = 0xff;
          if (iVar8 == 1) {
            iVar8 = (DAT_0045140c % 6) * 0x1e;
            uVar4 = iVar8 + 0x19;
            uVar5 = iVar8 + 0x46;
          }
          if ((&DAT_00451364)[uVar3] == 0) {
            pcVar14 = "Computer";
          }
          else {
            pcVar14 = " Human";
          }
          FUN_00401290(DAT_00455608,pcVar14,0,(uVar5 & 0xff | 0xff00) << 8 | uVar4 & 0xff,
                       iVar11 + 0x3b,iVar7 + 0xfd);
        }
        uVar3 = DAT_00451414;
      }
    }
    iVar11 = 0;
    iVar7 = 0;
    _DAT_00451340 = 0;
    if (0 < (int)uVar3) {
      do {
        if (0 < (int)(&DAT_00451364)[iVar7]) {
          iVar11 = iVar11 + 1;
          (&DAT_00451364)[iVar7] = iVar11;
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 < (int)uVar3);
      _DAT_00451340 = iVar11;
    }
    uVar4 = 0;
    if (0 < (int)uVar3) {
      iVar7 = 0;
      do {
        uVar3 = uVar4 & 0x80000001;
        uVar5 = 0x4d;
        local_9e4 = 0xe6;
        if ((int)uVar3 < 0) {
          uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
        }
        local_9ec = (int *)(&DAT_0044d0e0)[uVar4];
        iVar11 = (-(uint)(uVar3 != 0) & 0xffffffec) + 10 + iVar7 + local_9e0;
        if ((&DAT_0044d0c0)[(int)local_9ec] < 0) {
          uVar16 = 1;
        }
        else {
          uVar16 = 0xffffffff;
        }
        FUN_0043f010(iVar11 + 0xd8,local_9e8 + 0xfc,uVar16,0,0,DAT_00455608);
        if ((&DAT_00451364)[(int)local_9ec] == 0) {
          uVar5 = 200;
          DAT_0044d320._0_1_ = 'C';
          bVar2 = 0x96;
        }
        else {
          DAT_0044d320._0_1_ = *(char *)(&DAT_00451364 + (int)local_9ec) + '0';
          bVar2 = (byte)local_9e4;
        }
        FUN_00401290(DAT_00455608,&DAT_0044d320,0x8f472f,(uint)bVar2 << 0x10 | uVar5 | 0x7900,
                     iVar11 + 0xe5,local_9e8 + 299);
        uVar4 = uVar4 + 1;
        iVar7 = iVar7 + 0x3c;
        uVar3 = DAT_00451414;
      } while ((int)uVar4 < (int)DAT_00451414);
    }
    iVar11 = local_9e0;
    iVar7 = local_9e8;
    if ((int)uVar3 < 8) {
      uVar5 = uVar3 & 0x80000001;
      uVar4 = 0x4d;
      local_9e4 = 0xe6;
      if ((int)uVar5 < 0) {
        uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
      }
      local_9ec = (int *)(&DAT_0044d0e0)[uVar3];
      iVar8 = (-(uint)(uVar5 != 0) & 0xffffffec) + 10;
      if ((&DAT_0044d0c0)[uVar3] < 0) {
        uVar16 = 1;
      }
      else {
        uVar16 = 0xffffffff;
      }
      FUN_0043f010(iVar8 + uVar3 * 0x3c + 0xd8 + local_9e0,local_9e8 + 0xfc,uVar16,0,0,DAT_00455608)
      ;
      if (0 < DAT_00451410) {
        if ((&DAT_00451364)[(int)local_9ec] == 0) {
          uVar4 = 200;
          DAT_0044d320._0_1_ = 'C';
          bVar2 = 0x96;
        }
        else {
          DAT_0044d320._0_1_ = DAT_00451340 + '1';
          bVar2 = (byte)local_9e4;
        }
        FUN_00401290(DAT_00455608,&DAT_0044d320,0x8f472f,(uint)bVar2 << 0x10 | uVar4 | 0x7900,
                     iVar8 + DAT_00451414 * 0x3c + 0xe5 + iVar11,iVar7 + 299);
      }
    }
  }
  uVar16 = local_9f0;
  piVar6 = local_9f8;
  if (*local_9f8 == 0x7a) {
    FUN_0043f010(0x116,0xa2,2,0,0,local_9f0);
    FUN_0043f010(0x13a,0xb3,3,0,0,uVar16);
    FUN_0043f010(0x142,0xe8,5,0,0,uVar16);
    FUN_0043f010(0x1aa,0xe8,6,0,0,uVar16);
    if (DAT_00451408 == 0) {
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
      DAT_00451408 = 1 - DAT_00451408;
    }
    if (DAT_004513b4 == 0) {
      if (DAT_004513b8 != 0) {
        FUN_00401a30(0);
        DAT_004513b8 = 0;
        *piVar6 = 0x79;
        DAT_00451410 = 1;
        DAT_0044d100 = 1;
        DAT_0044d0e4 = 1;
        _DAT_0044d104 = 1;
        DAT_0044d0e8 = 2;
        _DAT_0044d108 = 2;
        _DAT_0044d10c = 2;
        DAT_00451414 = 7;
        DAT_0044d0e0 = 0;
        DAT_0044d0ec = 3;
        _DAT_0044d0f0 = 4;
        _DAT_0044d110 = 3;
        _DAT_0044d0f4 = 5;
        _DAT_0044d114 = 3;
        _DAT_0044d0f8 = 6;
        _DAT_0044d118 = 4;
        _DAT_0044d0fc = 7;
        _DAT_0044d11c = 4;
      }
      goto LAB_004355cb;
    }
    DAT_004513b4 = 0;
    FUN_00401a30(0);
    if (DAT_00451408 == 0) {
      *piVar6 = 0x7b;
      DAT_00451404 = 0;
      goto LAB_004355d4;
    }
    DAT_00451408 = 0;
    *piVar6 = 0x7c;
LAB_004356d8:
    iVar7 = 0;
    do {
      iVar11 = 1;
      if (*(int *)((int)&DAT_00451344 + iVar7) == 1) {
        piVar6 = *(int **)(local_9f4 + 0x7d4);
        iVar8 = piVar6[0x13608e0];
        iVar9 = 0;
        if (1 < iVar8) {
          do {
            piVar6 = piVar6 + 1;
            if (((*(int *)(*piVar6 + 0x6f8) == 0) &&
                (DAT_0044d0dc != iVar11 &&
                 (DAT_0044d0d8 != iVar11 &&
                 (DAT_0044d0d4 != iVar11 &&
                 (DAT_0044d0d0 != iVar11 &&
                 (DAT_0044d0cc != iVar11 &&
                 (DAT_0044d0c8 != iVar11 && (DAT_0044d0c4 != iVar11 && DAT_0044d0c0 != iVar11)))))))
                ) && (*(int *)(*piVar6 + 0x6f4) < 0x1e)) {
              aiStack_9c8[iVar9] = iVar11;
              iVar9 = iVar9 + 1;
            }
            iVar11 = iVar11 + 1;
          } while (iVar11 < iVar8);
          uVar16 = local_9f0;
        }
        iVar11 = FUN_00417170(0x103,iVar9);
        *(int *)((int)&DAT_0044d0c0 + iVar7) = aiStack_9c8[iVar11];
      }
      iVar7 = iVar7 + 4;
    } while (iVar7 < 0x20);
    *local_9f8 = 0x7d;
    DAT_00451408 = 2;
LAB_004357f0:
    FUN_00402130(3,DAT_004513ac,DAT_004513b0,uVar16);
    FUN_0043f010(3,3,8,0,0,uVar16);
    FUN_0043f010(3,0x9f,0xf,1,0,uVar16);
    if (DAT_00451408 == 0) {
      FUN_0043f010(0x5c,0x10,9,0,0,uVar16);
    }
    if (DAT_00451408 == 1) {
      FUN_0043f010(0x40,0x27,10,0,0,uVar16);
    }
    if (DAT_00451408 == 2) {
      FUN_0043f010(0x28,0x40,0xb,0,0,uVar16);
    }
    if (DAT_00451408 == 3) {
      FUN_0043f010(0xf,0x57,0xc,0,0,uVar16);
    }
    if (DAT_00451408 == 4) {
      FUN_0043f010(0x25,0x6f,0xd,0,0,uVar16);
    }
    if (DAT_00451408 == 5) {
      FUN_0043f010(0x65,0x89,0xe,0,0,uVar16);
    }
    if (DAT_0044d028 == 1) {
      DAT_0044d024 = 100;
    }
    FUN_00401290(DAT_00455608,DAT_0044d024 * 0x990 + 0x4d4617c + *(int *)(local_9f4 + 0x7d4),0,
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
    if ((DAT_004513a4 != 0) && (DAT_00451408 = DAT_00451408 + -1, DAT_00451408 == -1)) {
      DAT_00451408 = 5;
    }
    if (DAT_004513a8 != 0) {
      DAT_00451408 = (DAT_00451408 + 1) % 6;
    }
    if (DAT_004513b4 == 0) {
      if (DAT_004513b8 != 0) {
        DAT_004513b8 = 0;
        FUN_00401a30(0);
        *local_9f8 = 0x7a;
        DAT_00451408 = 0;
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
      piVar6 = local_9f8;
      if (DAT_00451408 == 0) {
        *local_9f8 = 0x7e;
        _DAT_0044d080 = 500;
        _DAT_0044d0a0 = 0xffffffff;
        DAT_00451384 = 2;
        _DAT_0044d084 = 500;
        _DAT_0044d0a4 = 0xffffffff;
        DAT_00451388 = 2;
        _DAT_0044d088 = 500;
        _DAT_0044d0a8 = 0xffffffff;
        DAT_0045138c = 2;
        _DAT_0044d08c = 500;
        _DAT_0044d0ac = 0xffffffff;
        DAT_00451390 = 2;
        _DAT_0044d090 = 500;
        _DAT_0044d0b0 = 0xffffffff;
        _DAT_00451394 = 2;
        _DAT_0044d094 = 500;
        _DAT_0044d0b4 = 0xffffffff;
        _DAT_00451398 = 2;
        _DAT_0044d098 = 500;
        _DAT_0044d0b8 = 0xffffffff;
        _DAT_0045139c = 2;
        _DAT_0044d09c = 500;
        _DAT_0044d0bc = 0xffffffff;
        _DAT_004513a0 = 2;
        DAT_00451404 = 0x19;
        DAT_0044d318 = 0;
        FUN_004025b0();
      }
      if (DAT_00451408 == 1) {
        *piVar6 = 0x78;
        goto LAB_00436f9d;
      }
      if (DAT_00451408 == 2) {
        *piVar6 = 0x7c;
        goto LAB_00436f9d;
      }
      if (DAT_00451408 == 3) {
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
          if (DAT_0044d024 == *(int *)(*(int *)(local_9f4 + 0x7d4) + 0x4d82384)) {
            DAT_0044d024 = 100;
            DAT_0044d028 = 1;
          }
        }
      }
      else if (DAT_00451408 == 4) {
        _DAT_00450c30 = _DAT_00450c30 + -1;
        if (_DAT_00450c30 < 0) {
          _DAT_00450c30 = 2;
        }
        FUN_00401a30(0);
      }
      else if (DAT_00451408 == 5) {
        *piVar6 = 10;
        FUN_00431c70();
        DAT_00457580 = 0;
      }
    }
  }
  else {
LAB_004355cb:
    if (*piVar6 == 0x7b) {
LAB_004355d4:
      iVar7 = 0x32;
      do {
        iVar11 = FUN_00417170(0x101,4);
        iVar8 = FUN_00417170(0x102,4);
        uVar13 = (&DAT_0044d0e0)[iVar11 * 2];
        (&DAT_0044d0e0)[iVar11 * 2] = (&DAT_0044d0e0)[iVar8 * 2];
        (&DAT_0044d0e0)[iVar8 * 2] = uVar13;
        uVar13 = (&DAT_0044d0e4)[iVar11 * 2];
        (&DAT_0044d0e4)[iVar11 * 2] = (&DAT_0044d0e4)[iVar8 * 2];
        (&DAT_0044d0e4)[iVar8 * 2] = uVar13;
        uVar13 = (&DAT_0044d100)[iVar11 * 2];
        (&DAT_0044d100)[iVar11 * 2] = (&DAT_0044d100)[iVar8 * 2];
        (&DAT_0044d100)[iVar8 * 2] = uVar13;
        uVar13 = *(undefined4 *)(&DAT_0044d104 + iVar11 * 8);
        iVar7 = iVar7 + -1;
        *(undefined4 *)(&DAT_0044d104 + iVar11 * 8) = *(undefined4 *)(&DAT_0044d104 + iVar8 * 8);
        *(undefined4 *)(&DAT_0044d104 + iVar8 * 8) = uVar13;
      } while (iVar7 != 0);
      DAT_00451404 = DAT_00451404 + 1;
      if (DAT_00451404 % 5 == 0) {
        FUN_00401a30(0);
      }
      if (10 < DAT_00451404) {
        *local_9f8 = 0x7a;
        DAT_00451408 = 0;
        goto LAB_00436f9d;
      }
    }
    if (*local_9f8 == 0x7c) goto LAB_004356d8;
    if (*local_9f8 == 0x7d) goto LAB_004357f0;
  }
  if (0x7d < *local_9f8) {
    local_9e4 = 0;
    local_9ec = &DAT_0044d168;
    do {
      uVar3 = (&DAT_00451384)[local_9e4];
      if ((int)uVar3 < 8) {
        if (uVar3 == 7) goto LAB_00435cb9;
      }
      else {
        uVar3 = 7;
LAB_00435cb9:
        if (*local_9f8 < 0x81) {
          *local_9f8 = 0x81;
          DAT_00451400 = local_9e4;
          DAT_00451404 = 0;
        }
      }
      uVar16 = 0xffffff;
      if ((int)uVar3 < 7) {
        uVar4 = uVar3 & 0x80000001;
        if ((int)uVar4 < 0) {
          uVar4 = (uVar4 - 1 | 0xfffffffe) + 1;
        }
        if (uVar4 == 1) {
          uVar16 = 0x192f67;
        }
      }
      iVar7 = 2;
      if (2 < (int)uVar3) {
        piVar6 = local_9ec;
        do {
          FUN_00415160(*piVar6 + -0x33,piVar6[1] + 0x7e,(&DAT_0044d120)[iVar7 * 2],
                       (&DAT_0044d124)[iVar7 * 2],uVar16);
          iVar7 = iVar7 + 1;
          piVar6 = piVar6 + 2;
        } while (iVar7 < (int)uVar3);
      }
      local_9ec = local_9ec + 0x1c;
      local_9e4 = local_9e4 + 2;
    } while (local_9e4 < 8);
  }
  iVar7 = DAT_0044d318;
  if (*local_9f8 == 0x7e) {
    _DAT_004513fc = 0;
    iVar11 = 0;
    do {
      if ((&DAT_00451384)[iVar11] == iVar7) {
        (&DAT_004513ec)[_DAT_004513fc] = iVar11;
        (&DAT_004513f0)[_DAT_004513fc] = iVar11 + 1;
        _DAT_004513fc = _DAT_004513fc + 2;
        if (_DAT_004513fc == 4) break;
      }
      iVar11 = iVar11 + 2;
    } while (iVar11 < 8);
    if (_DAT_004513fc == 0) {
      if (iVar7 < 6) {
        DAT_0044d318 = iVar7 + 2;
      }
      goto LAB_00435db8;
    }
    if (_DAT_004513fc != 4) goto LAB_00435db8;
    if (0x1e < DAT_00451404) {
      iVar7 = DAT_004513ec;
      if (4 < DAT_0045140c % 10) {
        iVar7 = DAT_004513f4;
      }
      iVar11 = (&DAT_00451384)[iVar7] + 2;
      if (7 < iVar11) {
        iVar11 = 7;
      }
      iVar8 = 2;
      if (2 < iVar11) {
        piVar6 = &DAT_0044d168 + iVar7 * 0xe;
        do {
          FUN_00415160(*piVar6 + -0x33,piVar6[1] + 0x7e,(&DAT_0044d120)[iVar8 * 2],
                       (&DAT_0044d124)[iVar8 * 2],0xffa7a7);
          iVar8 = iVar8 + 1;
          piVar6 = piVar6 + 2;
        } while (iVar8 < iVar11);
      }
    }
    iVar7 = local_9f4;
    DAT_00451404 = DAT_00451404 + 1;
    if (DAT_004513b8 == 0) {
      if (DAT_00451404 != 0x50) goto LAB_00435db8;
    }
    else {
      DAT_00451404 = 0x50;
    }
    if ((((&DAT_00451364)[(&DAT_0044d0e0)[DAT_004513ec]] == 0) &&
        ((&DAT_00451364)[(&DAT_0044d0e0)[DAT_004513f0]] == 0)) &&
       (((&DAT_00451364)[(&DAT_0044d0e0)[DAT_004513f4]] == 0 &&
        ((&DAT_00451364)[(&DAT_0044d0e0)[DAT_004513f8]] == 0)))) {
      FUN_00401a30(0);
      iVar7 = *(int *)(local_9f4 + 0x7d4);
      iVar11 = *(int *)(*(int *)(iVar7 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513ec]] * 4) + 0x6f4
                       ) / 10;
      DAT_00451404 = 0;
      if (iVar11 == 5) {
LAB_004361ca:
        if ((*(int *)(*(int *)(iVar7 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513f4]] * 4) + 0x6f4)
             / 10 == 5) ||
           (*(int *)(*(int *)(iVar7 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513f8]] * 4) + 0x6f4) /
            10 == 5)) {
LAB_0043622b:
          if (((iVar11 == 5) ||
              (*(int *)(*(int *)(iVar7 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513f0]] * 4) + 0x6f4
                       ) / 10 == 5)) ||
             ((*(int *)(*(int *)(iVar7 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513f4]] * 4) + 0x6f4
                       ) / 10 != 5 &&
              (*(int *)(*(int *)(iVar7 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513f8]] * 4) + 0x6f4
                       ) / 10 != 5)))) {
            uVar16 = 0x106;
            goto LAB_004362c9;
          }
          iVar7 = 2;
        }
        else {
          iVar7 = 0;
        }
      }
      else {
        if (((*(int *)(*(int *)(iVar7 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513f0]] * 4) + 0x6f4)
              / 10 == 5) ||
            (*(int *)(*(int *)(iVar7 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513f4]] * 4) + 0x6f4)
             / 10 == 5)) ||
           (*(int *)(*(int *)(iVar7 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513f8]] * 4) + 0x6f4) /
            10 == 5)) {
          if ((iVar11 == 5) ||
             (*(int *)(*(int *)(iVar7 + (&DAT_0044d0c0)[(&DAT_0044d0e0)[DAT_004513f0]] * 4) + 0x6f4)
              / 10 == 5)) goto LAB_004361ca;
          goto LAB_0043622b;
        }
        uVar16 = 0x105;
LAB_004362c9:
        iVar7 = FUN_00417170(uVar16,2);
        iVar7 = iVar7 * 2;
      }
      iVar11 = (&DAT_004513ec)[iVar7];
      iVar8 = (&DAT_004513f0)[iVar7];
      (&DAT_00451384)[iVar11] = (&DAT_00451384)[iVar11] + 2;
      (&DAT_00451384)[iVar8] = (&DAT_00451384)[iVar8] + 2;
      (&DAT_00451384)[(&DAT_004513f4)[-iVar7]] = (&DAT_00451384)[(&DAT_004513f4)[-iVar7]] + 1;
      (&DAT_00451384)[(&DAT_004513f8)[-iVar7]] = (&DAT_00451384)[(&DAT_004513f8)[-iVar7]] + 1;
      if ((&DAT_00451384)[iVar11] == 6) {
        (&DAT_00451384)[iVar11] = 7;
      }
      if ((&DAT_00451384)[iVar8] == 6) {
        (&DAT_00451384)[iVar8] = 7;
      }
      iVar9 = _DAT_00450c30;
      iVar11 = (&DAT_004513ec)[iVar7];
      iVar8 = _DAT_00450c30 * 0x12;
      iVar12 = FUN_00417170(0x107,_DAT_00450c30 * 0x12 + 0xf);
      iVar7 = (&DAT_004513f0)[iVar7];
      *(int *)(&DAT_0044d080 + iVar11 * 4) =
           ((iVar12 + iVar9 * -0x12 + 0x55) * *(int *)(&DAT_0044d080 + iVar11 * 4)) / 100;
      iVar11 = FUN_00417170(0x108,iVar8 + 0xf);
      *(int *)(&DAT_0044d080 + iVar7 * 4) =
           ((iVar11 + _DAT_00450c30 * -0x12 + 0x55) * *(int *)(&DAT_0044d080 + iVar7 * 4)) / 100;
      goto LAB_00435db8;
    }
    *local_9f8 = 0x7f;
    DAT_00451404 = 0;
    memset((void *)(local_9f4 + 4),0,400);
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
    (&DAT_00451384)[DAT_004513ec] = (&DAT_00451384)[DAT_004513ec] + 1;
    (&DAT_00451384)[DAT_004513f0] = (&DAT_00451384)[DAT_004513f0] + 1;
    (&DAT_00451384)[DAT_004513f4] = (&DAT_00451384)[DAT_004513f4] + 1;
    (&DAT_00451384)[DAT_004513f8] = (&DAT_00451384)[DAT_004513f8] + 1;
  }
  else {
LAB_00435db8:
    iVar7 = local_9f4;
  }
  if (*local_9f8 == 0x7f) {
    if (DAT_00451404 < 4) {
      if (DAT_0045140c % 10 < 5) {
        iVar11 = (&DAT_00451384)[(&DAT_004513ec)[DAT_00451404]] + 1;
        if (7 < iVar11) {
          iVar11 = 7;
        }
        iVar8 = 2;
        if (2 < iVar11) {
          piVar6 = &DAT_0044d168 + (&DAT_004513ec)[DAT_00451404] * 0xe;
          do {
            FUN_00415160(*piVar6 + -0x33,piVar6[1] + 0x7e,(&DAT_0044d120)[iVar8 * 2],
                         (&DAT_0044d124)[iVar8 * 2],0xffa7a7);
            iVar8 = iVar8 + 1;
            piVar6 = piVar6 + 2;
          } while (iVar8 < iVar11);
        }
      }
      uVar16 = local_9f0;
      if ((int)(&DAT_00451364)[(&DAT_0044d0e0)[(&DAT_004513ec)[DAT_00451404]]] < 1) {
        DAT_00451404 = DAT_00451404 + 1;
        DAT_00451408 = 1;
      }
      else {
        FUN_0043f010(10,10,10,0,0,local_9f0);
        FUN_0043f010(0xa9,0x18,(&DAT_00451364)[(&DAT_0044d0e0)[(&DAT_004513ec)[DAT_00451404]]] + 10,
                     0,0,uVar16);
        FUN_0043f010(0x5a,0x31,0xffffffff,0,0,uVar16);
        iVar11 = 0;
        piVar6 = (int *)(iVar7 + 0x194);
        do {
          if ((*(char *)(*piVar6 + 0xd1) != '\0') && (*(char *)(*piVar6 + 0xca) == '\0')) {
            if (*(char *)(iVar7 + 4 + iVar11) != '\x01') {
              DAT_004513b4 = 0;
              *(undefined1 *)(*(int *)(iVar7 + 0x194 + iVar11 * 4) + 0xca) = 1;
              FUN_00401a30(0);
              (&DAT_004512d0)[iVar11] = (&DAT_004513ec)[DAT_00451404];
              *(undefined1 *)(iVar7 + 4 + iVar11) = 1;
              piVar6 = &DAT_004513ec + DAT_00451404;
              DAT_00451404 = DAT_00451404 + 1;
              *(undefined4 *)(*(int *)(iVar7 + 0x194 + iVar11 * 4) + 0x368) =
                   *(undefined4 *)
                    (*(int *)(iVar7 + 0x7d4) + (&DAT_0044d0c0)[(&DAT_0044d0e0)[*piVar6]] * 4);
              break;
            }
            FUN_00401a30(0);
          }
          iVar11 = iVar11 + 1;
          piVar6 = piVar6 + 1;
        } while (iVar11 < 8);
      }
    }
    uVar16 = local_9f0;
    if (DAT_00451404 == 4) {
      FUN_0043f010(0x116,0xa2,2,0,0,local_9f0);
      FUN_0043f010(0x13a,0xb3,4,0,0,uVar16);
      FUN_0043f010(0x142,0xe8,5,0,0,uVar16);
      FUN_0043f010(0x1aa,0xe8,6,0,0,uVar16);
      if (DAT_00451408 == 0) {
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
        DAT_00451408 = 1 - DAT_00451408;
      }
      if (DAT_004513b4 == 0) goto LAB_004366b8;
      DAT_004513b4 = 0;
      FUN_00401a30(0);
      DAT_004513b4 = 0;
      if (DAT_00451408 != 0) {
        DAT_00451404 = 0;
        memset((void *)(iVar7 + 4),0,400);
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
        goto LAB_00436afd;
      }
      DAT_00451404 = 5;
    }
    else {
LAB_004366b8:
      if (DAT_00451404 != 5) goto LAB_00436afd;
    }
    piVar6 = &DAT_004513ec;
    do {
      if ((&DAT_00451364)[(&DAT_0044d0e0)[*piVar6]] == 0) {
        iVar11 = 0;
        do {
          if ((*(char *)(iVar7 + 4 + iVar11) == '\0') && (*(char *)(iVar7 + 0xe + iVar11) == '\0'))
          {
            FUN_00401a30(0);
            (&DAT_004512f8)[iVar11] = *piVar6;
            *(undefined1 *)(iVar7 + 0xe + iVar11) = 1;
            *(undefined4 *)(*(int *)(iVar7 + 0x1bc + iVar11 * 4) + 0x368) =
                 *(undefined4 *)
                  (*(int *)(iVar7 + 0x7d4) + (&DAT_0044d0c0)[(&DAT_0044d0e0)[*piVar6]] * 4);
            break;
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < 8);
      }
      piVar6 = piVar6 + 1;
    } while ((int)piVar6 < 0x4513fc);
    *local_9f8 = 0;
    GetLocalTime(&local_9d8);
    sprintf(local_1f8,"%4d%02d%02d_%02d%02d%02d",(uint)local_9d8.wYear,(uint)local_9d8.wMonth,
            (uint)local_9d8.wDay,(uint)local_9d8.wHour,(uint)local_9d8.wMinute,
            (uint)local_9d8.wSecond);
    pcVar14 = &cStack_1f9;
    do {
      pcVar1 = pcVar14;
      pcVar14 = pcVar1 + 1;
    } while (pcVar1[1] != '\0');
    builtin_strncpy(pcVar1 + 1,"_2on2_",7);
    if (DAT_0044d318 == 2) {
      pcVar14 = &cStack_1f9;
      do {
        pcVar1 = pcVar14;
        pcVar14 = pcVar1 + 1;
      } while (pcVar1[1] != '\0');
      builtin_strncpy(pcVar1 + 1,"SemiFinal",10);
    }
    else if (DAT_0044d318 == 4) {
      pcVar14 = &cStack_1f9;
      do {
        pcVar1 = pcVar14;
        pcVar14 = pcVar1 + 1;
      } while (pcVar1[1] != '\0');
      builtin_strncpy(pcVar1 + 1,"Final",6);
    }
    sprintf(&DAT_0044fd98,"%s.lfr",local_1f8);
    DAT_00450b6c = 0;
    if (DAT_00450be4 != 0) {
      DAT_00450b70 = 1;
    }
    if ((DAT_0044d028 == 1) &&
       (DAT_0044d024 = FUN_00417170(0x109,*(int *)(*(int *)(iVar7 + 0x7d4) + 0x4d82384) + -2),
       DAT_0044d024 == *(int *)(*(int *)(iVar7 + 0x7d4) + 0x4d82384) + -3)) {
      DAT_0044d024 = 99;
    }
    iVar11 = 0;
    piVar6 = (int *)(iVar7 + 0x194);
    local_9e4 = DAT_0044d024;
    do {
      if (*(char *)(iVar7 + 4 + iVar11) != '\0') {
        iVar8 = *piVar6;
        iVar9 = *(int *)(iVar8 + 0x368);
        FUN_004061d0();
        iVar7 = local_9f4;
        *(int *)(iVar8 + 0x368) = iVar9;
        uVar16 = *(undefined4 *)(iVar9 + 0x90);
        *(undefined8 *)(iVar8 + 0x58) = 0x4075e00000000000;
        *(undefined4 *)(iVar8 + 0x31c) = uVar16;
        *(undefined8 *)(iVar8 + 0x60) = 0;
        *(undefined8 *)(iVar8 + 0x68) = 0x4072c00000000000;
        *(undefined4 *)(*piVar6 + 0x308) = 500;
        *(undefined4 *)(*piVar6 + 0x2fc) =
             *(undefined4 *)(&DAT_0044d080 + (&DAT_004512d0)[iVar11] * 4);
        *(undefined4 *)(*piVar6 + 0x300) = *(undefined4 *)(*piVar6 + 0x2fc);
        iVar12 = local_9e4 * 0x990;
        *(undefined4 *)(*piVar6 + 0x304) = *(undefined4 *)(*piVar6 + 0x300);
        *(undefined4 *)(*piVar6 + 0x33c) =
             *(undefined4 *)(&DAT_0044d0a0 + (&DAT_004512d0)[iVar11] * 4);
        *(undefined4 *)(*piVar6 + 0x364) = (&DAT_0044d100)[(&DAT_004512d0)[iVar11]];
        *(undefined4 *)(*piVar6 + 8) = 0x4b;
        iVar9 = FUN_00417170(0x10a,*(int *)(iVar12 + 0x4d45db0 + *(int *)(local_9f4 + 0x7d4)) / 2);
        iVar8 = *(int *)(iVar12 + 0x4d45db0 + *(int *)(iVar7 + 0x7d4));
        *(int *)(*piVar6 + 0x10) = iVar9 + ((int)(iVar8 + (iVar8 >> 0x1f & 3U)) >> 2);
        iVar8 = FUN_00417170(0x10b,*(int *)(iVar12 + 0x4d45db8 + *(int *)(iVar7 + 0x7d4)) -
                                   *(int *)(iVar12 + 0x4d45db4 + *(int *)(iVar7 + 0x7d4)));
        *(int *)(*piVar6 + 0x18) = iVar8 + *(int *)(iVar12 + 0x4d45db4 + *(int *)(iVar7 + 0x7d4));
        *(undefined4 *)(*piVar6 + 0x14) = 0;
        *(double *)(*piVar6 + 0x58) = (double)*(int *)(*piVar6 + 0x10);
        *(double *)(*piVar6 + 0x68) = (double)*(int *)(*piVar6 + 0x18);
        *(undefined8 *)(*piVar6 + 0x60) = 0;
        *(int *)(*piVar6 + 0x354) = iVar11;
      }
      iVar11 = iVar11 + 1;
      piVar6 = piVar6 + 1;
    } while (iVar11 < 0x14);
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
    iVar11 = 0;
    if (0 < *(int *)(*(int *)(iVar7 + 0x7d4) + 0x4d82384)) {
      do {
        FUN_0040c0e0(iVar11);
        iVar11 = iVar11 + 1;
      } while (iVar11 < *(int *)(*(int *)(iVar7 + 0x7d4) + 0x4d82384));
    }
    if (DAT_0044d024 != 99) {
      FUN_0040c030(DAT_0044d024);
    }
    DAT_0044d034 = 1;
    DAT_00450bbc = 0;
    iVar11 = 0x14;
    do {
      if (*(char *)(iVar11 + 4 + iVar7) == '\0') {
        FUN_004061d0();
      }
      iVar11 = iVar11 + 1;
    } while (iVar11 < 400);
    FUN_00431c70();
    FUN_0043d2c0(*local_9dc,iVar7 + 4,iVar7 + 0x194);
  }
LAB_00436afd:
  piVar6 = local_9f8;
  if (*local_9f8 == 0x80) {
    piVar10 = &DAT_004512d4;
    piVar6 = (int *)(iVar7 + 0x198);
    do {
      if (-1 < piVar10[-1]) {
        iVar11 = piVar6[-1];
        if (*(int *)(iVar11 + 0x2fc) < 1) {
          *(int *)(iVar11 + 0x300) = *(int *)(iVar11 + 0x300) / 2;
        }
        iVar11 = piVar10[-1];
        *(undefined4 *)(&DAT_0044d080 + iVar11 * 4) = *(undefined4 *)(piVar6[-1] + 0x300);
        *(undefined4 *)(&DAT_0044d0a0 + iVar11 * 4) = *(undefined4 *)(piVar6[-1] + 0x33c);
        if ((*(int *)(piVar6[-1] + 0x364) == DAT_00450bf8) &&
           ((&DAT_00451384)[iVar11] = (&DAT_00451384)[iVar11] + 1, (&DAT_00451384)[iVar11] == 6)) {
          (&DAT_00451384)[iVar11] = 7;
        }
      }
      if (-1 < *piVar10) {
        iVar11 = *piVar6;
        if (*(int *)(iVar11 + 0x2fc) < 1) {
          *(int *)(iVar11 + 0x300) = *(int *)(iVar11 + 0x300) / 2;
        }
        iVar11 = *piVar10;
        *(undefined4 *)(&DAT_0044d080 + iVar11 * 4) = *(undefined4 *)(*piVar6 + 0x300);
        *(undefined4 *)(&DAT_0044d0a0 + iVar11 * 4) = *(undefined4 *)(*piVar6 + 0x33c);
        if ((*(int *)(*piVar6 + 0x364) == DAT_00450bf8) &&
           ((&DAT_00451384)[iVar11] = (&DAT_00451384)[iVar11] + 1, (&DAT_00451384)[iVar11] == 6)) {
          (&DAT_00451384)[iVar11] = 7;
        }
      }
      if (-1 < piVar10[1]) {
        iVar11 = piVar6[1];
        if (*(int *)(iVar11 + 0x2fc) < 1) {
          *(int *)(iVar11 + 0x300) = *(int *)(iVar11 + 0x300) / 2;
        }
        iVar11 = piVar10[1];
        *(undefined4 *)(&DAT_0044d080 + iVar11 * 4) = *(undefined4 *)(piVar6[1] + 0x300);
        *(undefined4 *)(&DAT_0044d0a0 + iVar11 * 4) = *(undefined4 *)(piVar6[1] + 0x33c);
        if ((*(int *)(piVar6[1] + 0x364) == DAT_00450bf8) &&
           ((&DAT_00451384)[iVar11] = (&DAT_00451384)[iVar11] + 1, (&DAT_00451384)[iVar11] == 6)) {
          (&DAT_00451384)[iVar11] = 7;
        }
      }
      if (-1 < piVar10[2]) {
        iVar11 = piVar6[2];
        if (*(int *)(iVar11 + 0x2fc) < 1) {
          *(int *)(iVar11 + 0x300) = *(int *)(iVar11 + 0x300) / 2;
        }
        iVar11 = piVar10[2];
        *(undefined4 *)(&DAT_0044d080 + iVar11 * 4) = *(undefined4 *)(piVar6[2] + 0x300);
        *(undefined4 *)(&DAT_0044d0a0 + iVar11 * 4) = *(undefined4 *)(piVar6[2] + 0x33c);
        if ((*(int *)(piVar6[2] + 0x364) == DAT_00450bf8) &&
           ((&DAT_00451384)[iVar11] = (&DAT_00451384)[iVar11] + 1, (&DAT_00451384)[iVar11] == 6)) {
          (&DAT_00451384)[iVar11] = 7;
        }
      }
      if (-1 < piVar10[3]) {
        iVar11 = piVar6[3];
        if (*(int *)(iVar11 + 0x2fc) < 1) {
          *(int *)(iVar11 + 0x300) = *(int *)(iVar11 + 0x300) / 2;
        }
        iVar11 = piVar10[3];
        *(undefined4 *)(&DAT_0044d080 + iVar11 * 4) = *(undefined4 *)(piVar6[3] + 0x300);
        *(undefined4 *)(&DAT_0044d0a0 + iVar11 * 4) = *(undefined4 *)(piVar6[3] + 0x33c);
        if ((*(int *)(piVar6[3] + 0x364) == DAT_00450bf8) &&
           ((&DAT_00451384)[iVar11] = (&DAT_00451384)[iVar11] + 1, (&DAT_00451384)[iVar11] == 6)) {
          (&DAT_00451384)[iVar11] = 7;
        }
      }
      piVar10 = piVar10 + 5;
      piVar6 = piVar6 + 5;
    } while ((int)piVar10 < 0x451324);
    if (DAT_00450bf8 == -1) {
      iVar8 = FUN_00417170(0x10c,2);
      iVar11 = (&DAT_004513ec)[iVar8 * 2];
      iVar8 = (&DAT_004513f0)[iVar8 * 2];
      (&DAT_00451384)[iVar11] = (&DAT_00451384)[iVar11] + 1;
      (&DAT_00451384)[iVar8] = (&DAT_00451384)[iVar8] + 1;
      if ((&DAT_00451384)[iVar11] == 6) {
        (&DAT_00451384)[iVar11] = 7;
      }
      if ((&DAT_00451384)[iVar8] == 6) {
        (&DAT_00451384)[iVar8] = 7;
      }
    }
    piVar6 = local_9f8;
    *local_9f8 = 0x7e;
    memset((void *)(iVar7 + 4),0,400);
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
  if (*piVar6 == 0x81) {
    if (DAT_00451404 < 0x32) {
      DAT_00451404 = DAT_00451404 + 1;
    }
    if (0x14 < DAT_00451404) {
      if (DAT_00451404 == 0x15) {
        FUN_00402100();
        FUN_00401a30(0);
      }
      uVar16 = local_9f0;
      FUN_0043f010(10,10,10,0,0,local_9f0);
      FUN_0043f010(0x6d,0x16,0x15,0,0,uVar16);
      FUN_0043f010(0xa9,0x18,(&DAT_0044d100)[DAT_00451400] + 10,0,0,uVar16);
      FUN_0043f010(0x1e,0x31,0xffffffff,0,0,uVar16);
      FUN_0043f010(0x96,0x31,0xffffffff,0,0,uVar16);
      FUN_0043f010(0x17,0xaf,0x13,0,0,uVar16);
      if ((DAT_004513b4 != 0) && (DAT_00451404 == 0x32)) {
        *piVar6 = 10;
        FUN_00431c70();
        DAT_00457580 = 0;
      }
    }
  }
LAB_00436f9d:
  __security_check_cookie(local_4 ^ (uint)&local_9f8);
  return;
}


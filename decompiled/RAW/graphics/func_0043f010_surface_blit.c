/* Function: FUN_0043f010 */
/* Address: 0x0043f010 */

void FUN_0043f010(int param_1,int param_2,int param_3,int param_4,int param_5,int *param_6)

{
  int iVar1;
  undefined4 *in_ECX;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 *puVar5;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_98;
  int local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  int iStack_68;
  undefined4 local_64;
  undefined4 local_60;
  
  if (param_5 != 0) {
    memset(&local_64,0,100);
    local_64 = 100;
    local_60 = 2;
  }
  if ((in_ECX[3] == 0) || (param_3 < 0)) {
    local_a0 = in_ECX[1];
    local_a8 = in_ECX[2];
    local_a4 = local_a8 + param_2;
    local_b4 = param_2;
    local_98 = local_a0 + param_1;
    local_b0 = param_1;
    local_9c = 0;
    local_ac = 0;
    iVar1 = FUN_0043ef70(&local_9c,&local_ac,&local_a0,&local_a8,&local_98,&local_a4);
    if (iVar1 != 0) {
      local_94 = local_b0;
      local_90 = local_b4;
      local_8c = local_98;
      local_88 = local_a4;
      local_84 = local_9c;
      local_80 = local_ac;
      local_7c = local_a0;
      local_78 = local_a8;
      if (param_5 == 0) {
        puVar5 = (undefined4 *)0x0;
        uVar2 = -(uint)(param_4 != 0) & 0x8000 | 0x1000000;
      }
      else {
        puVar5 = &local_64;
        uVar2 = -(uint)(param_4 != 0) & 0x8000 | 0x1000800;
      }
      (**(code **)(*param_6 + 0x14))(param_6,&local_94,*in_ECX,&local_84,uVar2,puVar5);
    }
  }
  if (param_3 < (int)in_ECX[3]) {
    local_a4 = in_ECX[param_3 + 4];
    local_98 = in_ECX[param_3 + 0x1f8];
    local_b4 = local_a4 + in_ECX[param_3 + 0x3ec];
    local_b0 = local_98 + in_ECX[param_3 + 0x5e0];
    local_9c = in_ECX[param_3 + 0x5e0] + param_2;
    local_a0 = param_2;
    local_ac = in_ECX[param_3 + 0x3ec] + param_1;
    local_a8 = param_1;
    iVar1 = FUN_0043ef70(&local_a4,&local_98,&local_b4,&local_b0,&local_ac,&local_9c);
    if (iVar1 != 0) {
      local_94 = local_a8;
      local_90 = local_a0;
      local_8c = local_ac;
      local_88 = local_9c;
      iStack_74 = local_a4;
      iStack_70 = local_98;
      iStack_6c = local_b4;
      iStack_68 = local_b0;
      if (param_5 == 0) {
        puVar5 = (undefined4 *)0x0;
        uVar2 = -(uint)(param_4 != 0) & 0x8000 | 0x1000000;
        piVar4 = &iStack_74;
        uVar3 = *in_ECX;
      }
      else {
        local_7c = in_ECX[param_3 + 4];
        local_80 = local_98;
        local_84 = (local_7c * 2 - local_b4) + in_ECX[param_3 + 0x3ec];
        local_7c = (in_ECX[param_3 + 0x3ec] - (local_a4 - local_7c)) + local_7c;
        puVar5 = &local_64;
        uVar2 = -(uint)(param_4 != 0) & 0x8000 | 0x1000800;
        piVar4 = &local_84;
        uVar3 = *in_ECX;
        local_78 = local_b0;
      }
      (**(code **)(*param_6 + 0x14))(param_6,&local_94,uVar3,piVar4,uVar2,puVar5);
    }
  }
  return;
}

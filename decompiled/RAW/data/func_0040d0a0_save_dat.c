/* 
 * Function: FUN_0040d0a0
 * Description: Saves stage data to a DAT file in human-readable format.
 *              This is the inverse of FUN_0040ef70 (load_dat).
 * Virtual Address: 0x0040d0a0
 * Calling Convention: __thiscall (ECX = stage_data_t*)
 */

void FUN_0040d0a0(char *param_1)

{
  int iVar1;
  FILE *_File;
  int in_ECX;
  int *piVar2;
  undefined4 *puVar3;
  int local_10;
  int local_c;
  
  _File = fopen(param_1,"w");
  fprintf(_File,"<bmp_begin>\n");
  if (*(int *)(in_ECX + 0x6f8) == 0) {
    fprintf(_File,"name: %s\n");
    fprintf(_File,"head: %s\n",in_ECX + 0x700);
    fprintf(_File,"small: %s\n",in_ECX + 0x72c);
  }
  param_1 = (char *)0x0;
  if (0 < *(int *)(in_ECX + 0x498)) {
    local_10 = in_ECX + 0x49c;
    piVar2 = (int *)(in_ECX + 0x6cc);
    do {
      fprintf(_File,"file(%d-%d): %s  w: %d  h: %d  row: %d  col: %d\n",piVar2[-0x28],
              piVar2[-10] * *piVar2 + -1 + piVar2[-0x28],local_10,piVar2[-0x1e],piVar2[-0x14],
              piVar2[-10]);
      local_10 = local_10 + 0x28;
      param_1 = (char *)((int)param_1 + 1);
      piVar2 = piVar2 + 1;
    } while ((int)param_1 < *(int *)(in_ECX + 0x498));
  }
  fprintf(_File,"walking_frame_rate %d\n");
  fprintf(_File,"walking_speed %lf\n",*(undefined8 *)(in_ECX + 8));
  fprintf(_File,"walking_speedz %lf\n",*(undefined8 *)(in_ECX + 0x10));
  fprintf(_File,"running_frame_rate %d\n",*(undefined4 *)(in_ECX + 0x18));
  fprintf(_File,"running_speed %lf\n",*(undefined8 *)(in_ECX + 0x20));
  fprintf(_File,"running_speedz %lf\n",*(undefined8 *)(in_ECX + 0x28));
  fprintf(_File,"heavy_walking_speed %lf\n",*(undefined8 *)(in_ECX + 0x30));
  fprintf(_File,"heavy_walking_speedz %lf\n",*(undefined8 *)(in_ECX + 0x38));
  fprintf(_File,"heavy_running_speed %lf\n",*(undefined8 *)(in_ECX + 0x40));
  fprintf(_File,"heavy_running_speedz %lf\n",*(undefined8 *)(in_ECX + 0x48));
  fprintf(_File,"jump_height %lf\n",*(undefined8 *)(in_ECX + 0x50));
  fprintf(_File,"jump_distance %lf\n",*(undefined8 *)(in_ECX + 0x58));
  fprintf(_File,"jump_distancez %lf\n",*(undefined8 *)(in_ECX + 0x60));
  fprintf(_File,"dash_height %lf\n",*(undefined8 *)(in_ECX + 0x68));
  fprintf(_File,"dash_distance %lf\n",*(undefined8 *)(in_ECX + 0x70));
  fprintf(_File,"dash_distancez %lf\n",*(undefined8 *)(in_ECX + 0x78));
  fprintf(_File,"rowing_height %lf\n",*(undefined8 *)(in_ECX + 0x80));
  fprintf(_File,"rowing_distance %lf\n",*(undefined8 *)(in_ECX + 0x88));
  fprintf(_File,"<bmp_end>\n\n");
  param_1 = (char *)0x0;
  do {
    iVar1 = (int)param_1 * 0x178 + in_ECX;
    if (*(char *)((int)param_1 * 0x178 + 0x7a4 + in_ECX) == '\x01') {
      fprintf(_File,"<frame> %d %s\n",param_1);
      fprintf(_File,
              "   pic: %d  state: %d  wait: %d  next: %d  dvx: %d  dvy: %d  dvz: %d  centerx: %d  centery: %d  hit_a: %d  hit_d: %d  hit_j: %d"
              ,*(undefined4 *)(iVar1 + 0x7a8),*(undefined4 *)(iVar1 + 0x7ac),
              *(undefined4 *)(iVar1 + 0x7b0),*(undefined4 *)(iVar1 + 0x7b4),
              *(undefined4 *)(iVar1 + 0x7b8),*(undefined4 *)(iVar1 + 0x7bc),
              *(undefined4 *)(iVar1 + 0x7c0),*(undefined4 *)(iVar1 + 0x7f4),
              *(undefined4 *)(iVar1 + 0x7f8),*(undefined4 *)(iVar1 + 0x7c8),
              *(undefined4 *)(iVar1 + 0x7cc),*(undefined4 *)(iVar1 + 2000));
      if (*(int *)(iVar1 + 0x7d4) != 0) {
        fprintf(_File," hit_Fa: %d");
      }
      if (*(int *)(iVar1 + 0x7d8) != 0) {
        fprintf(_File," hit_Ua: %d");
      }
      if (*(int *)(iVar1 + 0x7dc) != 0) {
        fprintf(_File," hit_Da: %d");
      }
      if (*(int *)(iVar1 + 0x7e0) != 0) {
        fprintf(_File," hit_Fj: %d");
      }
      if (*(int *)(iVar1 + 0x7e4) != 0) {
        fprintf(_File," hit_Uj: %d");
      }
      if (*(int *)(iVar1 + 0x7e8) != 0) {
        fprintf(_File," hit_Dj: %d");
      }
      if (*(int *)(iVar1 + 0x7ec) != 0) {
        fprintf(_File," hit_ja: %d");
      }
      if (*(int *)(iVar1 + 0x7f0) != 0) {
        fprintf(_File," mp: %d");
      }
      fprintf(_File,"\n");
      if (*(int *)(iVar1 + 0x914) != 0) {
        fprintf(_File,"  sound: %s \n");
      }
      if (*(int *)(iVar1 + 0x7fc) != 0) {
        fprintf(_File,"   opoint:\n");
        fprintf(_File,
                "      kind: %d  x: %d  y: %d  action: %d  dvx: %d  dvy: %d  oid: %d  facing: %d\n",
                *(undefined4 *)(iVar1 + 0x7fc),*(undefined4 *)(iVar1 + 0x800),
                *(undefined4 *)(iVar1 + 0x804),*(undefined4 *)(iVar1 + 0x808),
                *(undefined4 *)(iVar1 + 0x80c),*(undefined4 *)(iVar1 + 0x810),
                *(undefined4 *)(iVar1 + 0x814),*(undefined4 *)(iVar1 + 0x818));
        fprintf(_File,"   opoint_end:\n");
      }
      if (*(int *)(iVar1 + 0x824) != 0) {
        fprintf(_File,"   bpoint:\n");
        fprintf(_File,"      x: %d  y: %d\n",*(undefined4 *)(iVar1 + 0x824),
                *(undefined4 *)(iVar1 + 0x828));
        fprintf(_File,"   bpoint_end:\n");
      }
      if (*(int *)(iVar1 + 0x82c) != 0) {
        fprintf(_File,"   cpoint:\n");
        fprintf(_File,"      kind: %d  x: %d  y: %d\n",*(undefined4 *)(iVar1 + 0x82c),
                *(undefined4 *)(iVar1 + 0x830),*(undefined4 *)(iVar1 + 0x834));
        fprintf(_File,"      ");
        if (*(int *)(iVar1 + 0x82c) == 1) {
          if (*(int *)(iVar1 + 0x838) != 0) {
            fprintf(_File,"injury: %d  ");
          }
          if (*(int *)(iVar1 + 0x83c) != 0) {
            fprintf(_File,"cover: %d  ");
          }
          if (*(int *)(iVar1 + 0x840) != 0) {
            fprintf(_File,"vaction: %d  ");
          }
          if (*(int *)(iVar1 + 0x844) != 0) {
            fprintf(_File,"aaction: %d  ");
          }
          if (*(int *)(iVar1 + 0x848) != 0) {
            fprintf(_File,"jaction: %d  ");
          }
          if (*(int *)(iVar1 + 0x864) != 0) {
            fprintf(_File,"taction: %d  ");
          }
          if (*(int *)(iVar1 + 0x84c) != 0) {
            fprintf(_File,"daction: %d  ");
          }
          if (*(int *)(iVar1 + 0x850) != 0) {
            fprintf(_File,"throwvx: %d  ");
          }
          if (*(int *)(iVar1 + 0x854) != 0) {
            fprintf(_File,"throwvy: %d  ");
          }
          if (*(int *)(iVar1 + 0x86c) != 0) {
            fprintf(_File,"throwvz: %d  ");
          }
          if (*(int *)(iVar1 + 0x858) != 0) {
            fprintf(_File,"hurtable: %d ");
          }
          if (*(int *)(iVar1 + 0x868) != 0) {
            fprintf(_File,"throwinjury: %d ");
          }
        }
        if (*(int *)(iVar1 + 0x82c) == 2) {
          if (*(int *)(iVar1 + 0x838) != 0) {
            fprintf(_File,"fronthurtact: %d ");
          }
          if (*(int *)(iVar1 + 0x83c) != 0) {
            fprintf(_File,"backhurtact: %d ");
          }
        }
        if (*(int *)(iVar1 + 0x85c) != 0) {
          fprintf(_File,"decrease: %d ");
        }
        if (*(int *)(iVar1 + 0x860) != 0) {
          fprintf(_File,"dircontrol: %d ");
        }
        fprintf(_File,"\n   cpoint_end:\n");
      }
      if (*(int *)(iVar1 + 0x87c) != 0) {
        fprintf(_File,"   wpoint:\n");
        fprintf(_File,
                "      kind: %d  x: %d  y: %d  weaponact: %d  attacking: %d  cover: %d  dvx: %d  dvy: %d  dvz: %d \n"
                ,*(undefined4 *)(iVar1 + 0x87c),*(undefined4 *)(iVar1 + 0x880),
                *(undefined4 *)(iVar1 + 0x884),*(undefined4 *)(iVar1 + 0x888),
                *(undefined4 *)(iVar1 + 0x88c),*(undefined4 *)(iVar1 + 0x890),
                *(undefined4 *)(iVar1 + 0x894),*(undefined4 *)(iVar1 + 0x898),
                *(undefined4 *)(iVar1 + 0x89c));
        fprintf(_File,"   wpoint_end:\n");
      }
      local_10 = 0;
      if (0 < *(int *)(iVar1 + 0x8cc)) {
        local_c = 0;
        do {
          piVar2 = (int *)(*(int *)(iVar1 + 0x8d4) + local_c);
          fprintf(_File,"   itr:\n");
          fprintf(_File,"      kind: %d  x: %d  y: %d  w: %d  h: %d  ",*piVar2,piVar2[1],piVar2[2],
                  piVar2[3],piVar2[4]);
          if (piVar2[5] != 0) {
            fprintf(_File,"dvx: %d  ");
          }
          if (piVar2[6] != 0) {
            fprintf(_File,"dvy: %d  ");
          }
          if (piVar2[7] != 0) {
            fprintf(_File,"fall: %d  ");
          }
          if (piVar2[8] != 0) {
            fprintf(_File,"arest: %d  ");
          }
          if (piVar2[9] != 0) {
            fprintf(_File,"vrest: %d  ");
          }
          if (piVar2[10] != 0) {
            fprintf(_File,"respond: %d  ");
          }
          if (piVar2[0x10] != 0) {
            fprintf(_File,"bdefend: %d  ");
          }
          if (piVar2[0x11] != 0) {
            fprintf(_File,"injury: %d  ");
          }
          if (piVar2[0x12] != 0) {
            fprintf(_File,"zwidth: %d  ");
          }
          if (piVar2[0xb] != 0) {
            fprintf(_File,"\n      effect: %d  ");
          }
          if ((*piVar2 == 1) || (*piVar2 == 3)) {
            fprintf(_File,"\n      ");
            if (piVar2[0xc] != 0) {
              fprintf(_File,"catchingact: %d %d  ",piVar2[0xc]);
            }
            if (piVar2[0xe] != 0) {
              fprintf(_File,"caughtact: %d %d  ",piVar2[0xe]);
            }
          }
          if (*piVar2 == 2) {
            fprintf(_File,"\n      ");
            if (piVar2[0xc] != 0) {
              fprintf(_File,"pickingact: %d  ");
            }
            if (piVar2[0xd] != 0) {
              fprintf(_File,"pickedact: %d  ");
            }
          }
          fprintf(_File,"\n   itr_end:\n");
          local_c = local_c + 0x50;
          local_10 = local_10 + 1;
        } while (local_10 < *(int *)(iVar1 + 0x8cc));
      }
      piVar2 = (int *)(((int)param_1 + 6) * 0x178 + in_ECX);
      local_10 = 0;
      if (0 < *piVar2) {
        local_c = 0;
        do {
          puVar3 = (undefined4 *)(*(int *)(iVar1 + 0x8d8) + local_c);
          fprintf(_File,"   bdy:\n");
          fprintf(_File,"      kind: %d  x: %d  y: %d  w: %d  h: %d\n",*puVar3,puVar3[1],puVar3[2],
                  puVar3[3],puVar3[4]);
          fprintf(_File,"   bdy_end:\n");
          local_c = local_c + 0x28;
          local_10 = local_10 + 1;
        } while (local_10 < *piVar2);
      }
      fprintf(_File,"<frame_end>\n\n");
    }
    param_1 = (char *)((int)param_1 + 1);
  } while ((int)param_1 < 400);
  fclose(_File);
  return;
}



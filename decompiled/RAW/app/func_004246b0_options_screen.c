/*
 * Function: Interactive Options, Key Reconfiguration & Profile Setup UI
 * Virtual Address: 0x004246B0
 * Calling Convention: __thiscall (ECX = application context pointer)
 *
 * Parameters:
 *   param_1: Target surface handle (DAT_00455608)
 *
 * Description:
 *   Handles rendering and state machine dispatch for the Options screens:
 *   - Substate 0: Options / Network lobby root menu
 *   - Substate 1: Host game / network IP setup
 *   - Substate 2: Waiting for network client connection
 *   - Substate 3: Client connecting to server IP / IP text input
 *   - Substate 4: Network connected state
 *   - Substate 6: Control reconfiguration (4 players x 11 keys, keyboard/gamepad, player names)
 *   - Substate 7: Recording options & system profile (<No name>, <No email>, <No info>, auto-recording)
 *   - Substate 8: Challenge info
 *   - Substate -1: Credits / About screen animation
 *   - Substate -3: Display mode toggle / resolution switch dialog
 */

#include <windows.h>
#include <stdio.h>
#include <string.h>

extern int DAT_0044d064;           // Sub-state ID (0 = root, 6 = control, 7 = profile, -3 = display)
extern int DAT_0044d068;           // Initial allocation flag (1 = initialize UI sprites)
extern int DAT_0044d060;           // Mouse button previous state
extern int DAT_00457580;           // Mouse button current state (1 = clicked)
extern int DAT_004546f0;           // Mouse X position
extern int DAT_00453cdc;           // Mouse Y position
extern int DAT_004511e0;           // Rebinding key slot index (player*20 + key_idx)
extern int DAT_004511c8;           // Active player name editing index (player_idx + 1)
extern char* DAT_004511c4;         // Active profile string editing pointer
extern int DAT_00450be4;           // Replay auto-record toggle (0 = off, 1 = on)
extern int DAT_00450be8;           // Demo mode flag
extern int DAT_0044d780;           // Banner ad rotation timer
extern int DAT_004511f4;           // Resolution switch animation counter
extern int DAT_0044d784;           // Fullscreen display mode (0 = windowed, 1 = fullscreen)
extern void* DAT_004511ac;         // Background texture surface
extern void* DAT_00455608;         // Primary surface

// Player control and profile globals
extern int  DAT_0044fb70[80];      // 4 players x 20 ints (11 keys used)
extern char DAT_0044fcc0[44];      // 4 players x 11 chars
extern char DAT_0044fd18[100];     // Profile name
extern char DAT_0044f890[100];     // Profile email
extern char DAT_0044f900[100];     // Profile info
extern char DAT_00455378[300];     // Win32 Virtual Key buffer ('d' = pressed)

// Forward declarations of helper procedures
extern void FUN_00422b00(int key, char *out_name, int *out_width);
extern char FUN_00422f60(int key);
extern void FUN_00423230(void);    // save_control_txt
extern void FUN_00423480(void);    // load_control_txt
extern void FUN_004236d0(void);    // toggle_display_mode
extern void FUN_004237e0(void);    // validate_display
extern void FUN_00423840(void);    // load_menu_bg
extern void FUN_00423910(void);    // free_menu_bg
extern void FUN_00423940(char*, int, int, int, int, int, int);
extern void FUN_00423a70(char*, int, int, int, int, int, int);
extern void FUN_00401a30(int sound_id);
extern void FUN_00401290(void *surf, const char *txt, int color, int bg, int x, int y);
extern void FUN_0043f010(int x, int y, int glyph, int mode, int extra, void* target);

void FUN_004246b0(void *param_1)
{
  int iVar4;
  int iVar7;
  int iVar9;
  char *pcVar10;
  char *pcVar12;
  char cVar3;
  char cVar1;

  // Background initialization
  if (DAT_004511ac == NULL) {
    FUN_00423840();
  }

  // Substate 6: Interactive Control Reconfiguration
  if (DAT_0044d064 == 6) {
    // Check if waiting for key input to rebind
    if (DAT_004511e0 > 0) {
      for (iVar4 = 0; iVar4 < 0xFA; ++iVar4) {
        if (DAT_00455378[iVar4] == 'd') {
          DAT_0044fb70[DAT_004511e0] = iVar4;
          DAT_004511e0 = 0;
          break;
        }
      }
    }

    // Check if typing player name
    if (DAT_004511c8 > 0) {
      int p_idx = DAT_004511c8 - 1;
      char *p_name = &DAT_0044fcc0[p_idx * 11];
      for (iVar4 = 0; iVar4 < 300; ++iVar4) {
        if (DAT_00455378[iVar4] == 'd') {
          cVar3 = FUN_00422f60(iVar4);
          int name_len = strlen(p_name);
          if (iVar4 == 8) { // Backspace
            if (name_len > 0) {
              p_name[name_len - 1] = '\0';
            }
            DAT_00455378[iVar4] = 'u';
          }
          else if (cVar3 != '\0' && name_len < 10 && iVar4 != 0xD) {
            p_name[name_len] = cVar3;
            p_name[name_len + 1] = '\0';
            DAT_00455378[iVar4] = 'u';
          }
        }
      }
    }

    // Process player slot layout: 4 players
    for (int p = 0; p < 4; ++p) {
      int slot_x = 0xC2 + p * 0x8B;
      int *p_device = &DAT_0044fb70[p * 20];
      char *p_name = &DAT_0044fcc0[p * 11];

      // Click on input device toggle button (Keyboard vs Joystick 1..4)
      if (DAT_004546f0 >= slot_x && DAT_004546f0 <= slot_x + 0x69 &&
          DAT_00457580 == 1 && DAT_0044d060 == 0 &&
          (DAT_00453cdc - 0xB6U < 0x5B)) {
        DAT_004511e0 = 0;
        *p_device = (*p_device + 1) % 3;
      }

      // Click on name input box
      if (DAT_004546f0 >= slot_x && DAT_004546f0 <= slot_x + 0x69 &&
          (DAT_00453cdc - 0x9CU < 0x12) &&
          DAT_0044d060 == 0 && DAT_00457580 == 1) {
        DAT_004511c8 = p + 1;
        DAT_004511e0 = 0;
      }

      // Check click on action keys: 11 keys per player
      int key_y = 0x11B;
      for (int k = 0; k < 7; ++k) {
        if (DAT_004546f0 >= slot_x && DAT_004546f0 <= slot_x + 0x69 &&
            DAT_0044d060 == 0 && DAT_00457580 == 1 &&
            DAT_00453cdc >= key_y - 3 && DAT_00453cdc <= key_y + 0xF) {
          if (*p_device == 0 || k >= 4) {
            DAT_004511e0 = p * 20 + (k + 1);
          }
          DAT_004511c8 = 0;
        }

        // Render key label or Friendly Name
        if (*p_device == 0) {
          char key_name[32];
          int width_adj = 0;
          FUN_00422b00(DAT_0044fb70[p * 20 + k + 1], key_name, &width_adj);
          FUN_00401290(DAT_00455608, key_name, 0xFFFFFF, 0, slot_x + 10, key_y);
        }

        key_y += 0x16;
      }
    }

    // Save and Cancel buttons at bottom
    if (DAT_00453cdc > 0x1B8) {
      // Cancel / Discard button (reloads control.txt)
      if (DAT_00453cdc < 0x1D2 && (DAT_004546f0 - 0x246U < 0x9C) &&
          DAT_0044d060 == 0 && DAT_00457580 == 1) {
        FUN_00401a30(0);
        FUN_00423480();
        DAT_0044d064 = 0;
        DAT_0044d780 = 0xFFFFFFFF;
        FUN_00423910();
      }
      // Save button (writes control.txt)
      if ((DAT_00453cdc - 0x1B9U < 0x19) && (DAT_004546f0 - 0x195U < 0x9C) &&
          DAT_0044d060 == 0 && DAT_00457580 == 1) {
        FUN_00401a30(0);
        FUN_00423230();
        DAT_0044d064 = 0;
        DAT_0044d780 = 0xFFFFFFFF;
        FUN_00423910();
      }
    }
  }

  // Substate 7: Profile and Recording Settings
  else if (DAT_0044d064 == 7) {
    if (DAT_0044d060 == 0 && DAT_00457580 == 1) {
      if (DAT_004546f0 >= 0xD2 && DAT_004546f0 <= 0x2DA) {
        if (DAT_00453cdc >= 0xCF && DAT_00453cdc <= 0xE1) {
          DAT_004511c4 = DAT_0044fd18; // Profile Name
        } else if (DAT_00453cdc >= 0xE8 && DAT_00453cdc <= 0x12E) {
          DAT_004511c4 = DAT_0044f900; // Profile Info
        } else if (DAT_00453cdc >= 0x135 && DAT_00453cdc <= 0x147) {
          DAT_004511c4 = DAT_0044f890; // Profile Email
        }
      }
    }

    // Auto-record replay checkbox toggle
    if (DAT_004546f0 > 0x11E && DAT_004546f0 < 0x133 &&
        DAT_00453cdc > 0x185 && DAT_00453cdc < 0x19A &&
        DAT_0044d060 == 0 && DAT_00457580 == 1) {
      DAT_00450be4 = 1 - DAT_00450be4;
    }

    // Save and Cancel buttons
    if (DAT_00453cdc > 0x19F && DAT_00453cdc < 0x1B9) {
      // Cancel
      if (DAT_004546f0 > 0x192 && DAT_004546f0 < 0x22F &&
          DAT_0044d060 == 0 && DAT_00457580 == 1) {
        FUN_00423480();
        FUN_00401a30(0);
        DAT_0044d064 = 0;
        FUN_00423910();
      }
      // Save
      if (DAT_004546f0 > 0xE6 && DAT_004546f0 < 0x183 &&
          DAT_0044d060 == 0 && DAT_00457580 == 1) {
        FUN_00423230();
        FUN_00401a30(0);
        DAT_0044d064 = 0;
      }
    }
  }

  // Substate -3: Display Mode / Fullscreen Switch
  else if (DAT_0044d064 == -3) {
    if (DAT_004546f0 - 0xD1U < 0xEA &&
        DAT_00453cdc > 0x11C && DAT_00453cdc < 0x139 &&
        DAT_0044d060 == 0 && DAT_00457580 == 1) {
      DAT_00457580 = 0;
      DAT_00450be8 = 1;
      FUN_00423230();
      DAT_0044d064 = 0;
      FUN_00401a30(0);
      FUN_004237e0();
    }
  }

  DAT_0044d060 = DAT_00457580;
}


#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/* Decompiled WindowProc from (0x0043b3d0 - 0x0043bc50)
 * Handles window messages, keyboard state array, mouse events, and secret cheat codes.
 */

#include <windows.h>
#include <stdint.h>
#include <stdbool.h>

// Global pointers and state variables mapped from lf2.exe addresses
extern uint8_t g_key_states[256];      // 0x00455378: keyboard state array ('u' = up, 'd' = down)
extern uint8_t g_cheat_lf2net;         // 0x00455471: 'd' when "lf2.net" typed
extern uint8_t g_cheat_herofighter;    // 0x00455470: 'd' when "herofighter.com" typed
extern int32_t g_cheat_lf2net_idx;     // 0x0045857c: progression index in "lf2.net"
extern int32_t g_cheat_herofighter_idx;// 0x00458578: progression index in "herofighter.com"
extern int32_t g_fullscreen;           // 0x00458430: 0 = windowed, 1 = fullscreen
extern int32_t g_mouse_x;              // 0x004546f0: mouse X coordinate
extern int32_t g_mouse_y;              // 0x00453cdc: mouse Y coordinate
extern int32_t g_mouse_lbutton;        // 0x00457580: mouse left button state
extern int32_t g_mouse_rbutton;        // 0x004527e4: mouse right button state
extern int32_t g_active_state;         // 0x00451dac: active state flag

LRESULT CALLBACK LF2_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_ACTIVATE:
        if (LOWORD(wParam) == WA_INACTIVE) {
            g_active_state = 0;
        } else {
            g_active_state = 1;
        }
        return 0;

    case WM_KEYDOWN:
        // Update keyboard state array to 'd' (0x64 = down)
        if (wParam < 256) {
            g_key_states[wParam] = 'd';
        }

        // Secret Cheat Code 1: "lf2.net" (unlocks Julian, Firzen, LouisEX)
        // Sequence: 'L' (0x4c), 'F' (0x46), '2' (0x32), '.' (0xbe), 'N' (0x4e), 'E' (0x45), 'T' (0x54)
        switch (g_cheat_lf2net_idx) {
        case 0:
            if (wParam == 'L') g_cheat_lf2net_idx = 1;
            break;
        case 1:
            if (wParam == 'F') g_cheat_lf2net_idx = 2;
            else if (wParam != 'L') g_cheat_lf2net_idx = 0;
            break;
        case 2:
            if (wParam == '2') g_cheat_lf2net_idx = 3;
            else if (wParam == 'L') g_cheat_lf2net_idx = 1;
            else g_cheat_lf2net_idx = 0;
            break;
        case 3:
            if (wParam == VK_OEM_PERIOD || wParam == 0xBE || wParam == '.') g_cheat_lf2net_idx = 4;
            else if (wParam == 'L') g_cheat_lf2net_idx = 1;
            else g_cheat_lf2net_idx = 0;
            break;
        case 4:
            if (wParam == 'N') g_cheat_lf2net_idx = 5;
            else if (wParam == 'L') g_cheat_lf2net_idx = 1;
            else g_cheat_lf2net_idx = 0;
            break;
        case 5:
            if (wParam == 'E') g_cheat_lf2net_idx = 6;
            else if (wParam == 'L') g_cheat_lf2net_idx = 1;
            else g_cheat_lf2net_idx = 0;
            break;
        case 6:
            if (wParam == 'T') {
                g_cheat_lf2net = 'd'; // Unlock full character roster
            }
            if (wParam != 'L') g_cheat_lf2net_idx = 0;
            else g_cheat_lf2net_idx = 1;
            break;
        default:
            g_cheat_lf2net_idx = 0;
            break;
        }

        // Secret Cheat Code 2: "herofighter.com" (alternative Marti Wong cheat)
        // Sequence: 'H', 'E', 'R', 'O', 'F', 'I', 'G', 'H', 'T', 'E', 'R', '.', 'C', 'O', 'M'
        switch (g_cheat_herofighter_idx) {
        case 0:
            if (wParam == 'H') g_cheat_herofighter_idx = 1;
            break;
        case 1:
            if (wParam == 'E') g_cheat_herofighter_idx = 2;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 2:
            if (wParam == 'R') g_cheat_herofighter_idx = 3;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 3:
            if (wParam == 'O') g_cheat_herofighter_idx = 4;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 4:
            if (wParam == 'F') g_cheat_herofighter_idx = 5;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 5:
            if (wParam == 'I') g_cheat_herofighter_idx = 6;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 6:
            if (wParam == 'G') g_cheat_herofighter_idx = 7;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 7:
            if (wParam == 'H') g_cheat_herofighter_idx = 8;
            else g_cheat_herofighter_idx = 0;
            break;
        case 8:
            if (wParam == 'T') g_cheat_herofighter_idx = 9;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 9:
            if (wParam == 'E') g_cheat_herofighter_idx = 10;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 10:
            if (wParam == 'R') g_cheat_herofighter_idx = 11;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 11:
            if (wParam == VK_OEM_PERIOD || wParam == 0xBE || wParam == '.') g_cheat_herofighter_idx = 12;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 12:
            if (wParam == 'C') g_cheat_herofighter_idx = 13;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 13:
            if (wParam == 'O') g_cheat_herofighter_idx = 14;
            else if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        case 14:
            if (wParam == 'M') {
                g_cheat_herofighter = 'd';
            }
            if (wParam == 'H') g_cheat_herofighter_idx = 1;
            else g_cheat_herofighter_idx = 0;
            break;
        default:
            g_cheat_herofighter_idx = 0;
            break;
        }

        // Check for Alt+Enter (toggle fullscreen)
        if (wParam == VK_RETURN && (GetKeyState(VK_MENU) & 0x8000)) {
            // Fullscreen toggle logic
        }
        return 0;

    case WM_KEYUP:
        // Update keyboard state array to 'u' (0x75 = up)
        if (wParam < 256) {
            g_key_states[wParam] = 'u';
        }
        return 0;

    case WM_MOUSEMOVE:
        g_mouse_x = (int16_t)LOWORD(lParam);
        g_mouse_y = (int16_t)HIWORD(lParam);
        return 0;

    case WM_LBUTTONDOWN:
        g_mouse_lbutton = 1;
        return 0;

    case WM_LBUTTONUP:
        g_mouse_lbutton = 0;
        return 0;

    case WM_RBUTTONDOWN:
        g_mouse_rbutton = 1;
        return 0;

    case WM_RBUTTONUP:
        g_mouse_rbutton = 0;
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProcA(hWnd, uMsg, wParam, lParam);
    }
}


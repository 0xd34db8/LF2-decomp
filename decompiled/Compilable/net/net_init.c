#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>

/*
 * Function: InitWinSock & Host Socket Initialization
 * Original Virtual Address: 0x00402B60 (FUN_00402b60) & 0x00402AD0 (FUN_00402ad0)
 *
 * Description: Initializes WinSock 1.1, resolves local hostname and IP addresses,
 * formats local IP strings via FUN_00402ad0, initializes local address structure
 * (0x0044f260, port 5000) and default connect/host structure (0x0044f58c, port 12345),
 * creates the TCP stream socket (0x0044f1b4), and registers WSAAsyncSelect with
 * WM_USER + 1 (0x401) for FD_ACCEPT | FD_CONNECT | FD_CLOSE (0x38).
 */

#define LF2_WM_NET_EVENT (WM_USER + 1) /* 0x401 */
#define LF2_ASYNC_EVENTS 0x38          /* FD_ACCEPT (0x08) | FD_CONNECT (0x10) | FD_CLOSE (0x20) */
#define LF2_LOCAL_PORT   5000
#define LF2_DEFAULT_PORT 12345         /* 0x3039 */

SOCKET g_listen_socket = INVALID_SOCKET;
struct sockaddr_in g_local_addr = {0};
struct sockaddr_in g_remote_addr = {0};
char g_local_ip[64] = {0};

int FUN_00402ad0(char **addr_list)
{
    if (!addr_list || !addr_list[0]) return 0;

    int best_idx = 0;
    for (int i = 0; addr_list[i] != NULL && i < 5; ++i) {
        struct in_addr addr;
        memcpy(&addr, addr_list[i], sizeof(struct in_addr));
        const char *ip_str = inet_ntoa(addr);
        if (ip_str) {
            if (i == 0) {
                strncpy(g_local_ip, ip_str, sizeof(g_local_ip) - 1);
                g_local_ip[sizeof(g_local_ip) - 1] = '\0';
            }
            if (strcmp(ip_str, "127.0.0.1") != 0) {
                best_idx = i;
                strncpy(g_local_ip, ip_str, sizeof(g_local_ip) - 1);
                g_local_ip[sizeof(g_local_ip) - 1] = '\0';
            }
        }
    }
    return best_idx;
}

int func_00402b60_net_init(HWND hwnd)
{
    WSADATA wsa_data;
    char hostname[256];
    struct hostent *host_entry;

    /* 0x00402B7A: WSAStartup(0x0101, &wsa_data) */
    WSAStartup(0x0101, &wsa_data);
    if (wsa_data.wVersion != 0x0101) {
        MessageBoxA((HWND)0, "WSAStartup()", "Error", 0);
        return 0;
    }

    /* 0x00402BAE: gethostname(hostname, 0x100) */
    if (gethostname(hostname, 0x100) == -1) {
        MessageBoxA((HWND)0, "gethostname()", "Error", 0);
        return 0;
    }

    /* 0x00402BE1: gethostbyname(hostname) */
    host_entry = gethostbyname(hostname);
    if (!host_entry) {
        MessageBoxA((HWND)0, "gethostbyname()", "Error", 0);
        return 0;
    }

    /* 0x00402C18: Select local IP address */
    int ip_idx = FUN_00402ad0(host_entry->h_addr_list);

    /* 0x00402C29: Populate 0x0044f260 (AF_INET, port 5000) */
    memset(&g_local_addr, 0, sizeof(g_local_addr));
    g_local_addr.sin_family = AF_INET;
    g_local_addr.sin_addr.s_addr = *(u_long *)host_entry->h_addr_list[ip_idx];
    g_local_addr.sin_port = htons(LF2_LOCAL_PORT);

    /* 0x00402C5D: socket(AF_INET=2, SOCK_STREAM=1, IPPROTO_TCP=6) */
    g_listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (g_listen_socket == INVALID_SOCKET) {
        MessageBoxA((HWND)0, "socket()", "Error", 0);
        return 0;
    }

    /* 0x00402C8F: WSAAsyncSelect(DAT_0044f1b4, param_1, 0x401, 0x38) */
    if (WSAAsyncSelect(g_listen_socket, hwnd, LF2_WM_NET_EVENT, LF2_ASYNC_EVENTS) != 0) {
        MessageBoxA((HWND)0, "WSAAsyncSelect()", "Error", 0);
        return 0;
    }

    /* 0x00402CA9: Populate 0x0044f58c (AF_INET, port 12345 = 0x3039) */
    memset(&g_remote_addr, 0, sizeof(g_remote_addr));
    g_remote_addr.sin_family = AF_INET;
    g_remote_addr.sin_addr.s_addr = *(u_long *)host_entry->h_addr_list[ip_idx];
    g_remote_addr.sin_port = htons(LF2_DEFAULT_PORT);
    DAT_0044f1af = 0;

    return 1;
}

int func_00402b80_net_init(HWND hwnd)
{
    return func_00402b60_net_init(hwnd);
}

void FUN_00402b60(HWND hwnd)
{
    func_00402b60_net_init(hwnd);
}

int FUN_00402b80(void)
{
    return func_00402b60_net_init(DAT_004546f4);
}




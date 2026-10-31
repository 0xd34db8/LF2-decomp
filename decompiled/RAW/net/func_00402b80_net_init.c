/*
 * Function: InitWinSock & Host Socket Initialization
 * Original Virtual Address: 0x00402B80
 *
 * Description: Initializes WinSock, resolves local hostname and IP address,
 * creates the TCP listening stream socket, configures asynchronous window message
 * notification (WM_USER + 1 = 0x401 for FD_READ | FD_WRITE | FD_CLOSE),
 * and sets default port 12345 / 5000 / 12328.
 */

#include <windows.h>
#include <winsock.h>

#define LF2_WM_NET_EVENT (WM_USER + 1) // 0x401
#define LF2_DEFAULT_PORT 12345

extern HWND g_hWnd;
extern SOCKET g_listen_socket;
extern struct sockaddr_in g_local_addr;
extern struct sockaddr_in g_remote_addr;
extern char g_local_ip[64];

int func_00402b80_net_init(HWND hwnd) {
    WSADATA wsa_data;
    char hostname[256];
    struct hostent* host_entry;

    // 0x00402B81: WSAStartup(0x0101, &wsa_data)
    if (WSAStartup(MAKEWORD(1, 1), &wsa_data) != 0) {
        MessageBoxA(hwnd, "WSAStartup()", "Error", MB_OK);
        return 0;
    }

    // 0x00402BC0: gethostname(hostname, sizeof(hostname))
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        MessageBoxA(hwnd, "gethostname()", "Error", MB_OK);
        return 0;
    }

    // 0x00402C0B: gethostbyname(hostname)
    host_entry = gethostbyname(hostname);
    if (!host_entry) {
        MessageBoxA(hwnd, "gethostbyname()", "Error", MB_OK);
        return 0;
    }

    // 0x00402C53: Bind address setup
    memset(&g_local_addr, 0, sizeof(g_local_addr));
    g_local_addr.sin_family = AF_INET; // 0x2
    g_local_addr.sin_port = htons(5000); // 0x1388
    memcpy(&g_local_addr.sin_addr, host_entry->h_addr_list[0], host_entry->h_length);

    // 0x00402C79: socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
    g_listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (g_listen_socket == INVALID_SOCKET) {
        MessageBoxA(hwnd, "socket()", "Error", MB_OK);
        return 0;
    }

    // 0x00402CD5: WSAAsyncSelect(socket, hwnd, 0x401, FD_READ | FD_WRITE | FD_CLOSE)
    if (WSAAsyncSelect(g_listen_socket, hwnd, LF2_WM_NET_EVENT, FD_READ | FD_WRITE | FD_CLOSE) != 0) {
        MessageBoxA(hwnd, "WSAAsyncSelect()", "Error", MB_OK);
        closesocket(g_listen_socket);
        g_listen_socket = INVALID_SOCKET;
        return 0;
    }

    return 1;
}


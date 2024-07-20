#include "pch.h"
#include "TrackLand.h"

#include "framework_directx.h"

extern "C" extern const uint32_t D3D12SDKVersion = D3D12_SDK_VERSION;
extern "C" extern LPCSTR D3D12SDKPath = ".\\D3D12\\";

extern void ExitGame(int code);

#define MAX_LOADSTRING 32

static TCHAR
g_zTitle[MAX_LOADSTRING],   // Main Window Display Name
g_zMainWndClass[MAX_LOADSTRING];// Main Window Class Name

static LONGLONG
g_qpcFrequency,
g_qpcStart,
g_qpcCurrent;

static ATOM RegisterMainClass(HINSTANCE);
static LRESULT WINAPI WndProc(HWND, UINT uMsg, WPARAM, LPARAM);

extern int APIENTRY
_tWinMain(_In_      HINSTANCE   hInstance,
          _In_opt_  HINSTANCE   hPrevInstance,
          _In_      LPTSTR      lpCmdLine,
          _In_      int         nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!QueryPerformanceFrequency((PLARGE_INTEGER)&g_qpcFrequency) ||
        !(QueryPerformanceCounter((PLARGE_INTEGER)&g_qpcStart)))
    {
        return FALSE;
    }
    else g_qpcCurrent = g_qpcStart;

    LoadString(hInstance, IDS_TITLE, g_zTitle, _countof(g_zTitle));
    LoadString(hInstance, IDS_MAIN_WND_CLASS, g_zMainWndClass, _countof(g_zMainWndClass));

    ATOM aMainCls = RegisterMainClass(hInstance);
    if (!aMainCls)
        return FALSE;

    HWND hWnd = CreateWindowEx(0L, (LPCTSTR)aMainCls, g_zTitle, WS_OVERLAPPEDWINDOW,
        // X * Y
        CW_USEDEFAULT, 0,
        // Width x Height
        CW_USEDEFAULT, 0,
        NULL, NULL, hInstance, NULL);
    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }
        // Game Loop


    }

    return (int)msg.wParam;
}

static ATOM RegisterMainClass(HINSTANCE hInstance)
{
    const WNDCLASSEX wcex = {
        .cbSize = sizeof wcex,
        .style = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc = WndProc,
        .cbWndExtra = sizeof (void*),
        .hInstance = hInstance,
        .hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRACKLAND)),
        .hCursor = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground = (HBRUSH)COLOR_WINDOWFRAME,
        .lpszClassName = g_zMainWndClass,
        .hIconSm = wcex.hIcon,
    };
    return RegisterClassEx(&wcex);
}

static LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {

    case WM_DESTROY:
        ExitGame(0);
        break;
    default:
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}







extern void ExitGame(int code)
{
    PostQuitMessage(code);
}
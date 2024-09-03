/* MIT License

Copyright (c) 2024 Stefan-Mihai MOGA

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

// DemoApp.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "DemoApp.h"
#include "Commctrl.h"

#define GENUP4WIN_EXPORTS
#include "../genUp4win.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    AboutCallback(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    UpdateCallback(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    const DWORD nLength = _MAX_PATH;
    TCHAR lpszFilePath[nLength] = { 0, };
    GetModuleFileName(nullptr, lpszFilePath, nLength);
    WriteConfigFile(lpszFilePath, _T("https://www.moga.doctor/freeware/IntelliEditSetup.msi"));

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEMOAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMOAPP));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMOAPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DEMOAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
                case ID_FILE_CHECK_FOR_UPDATES:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_CHECK_FOR_UPDATES), hWnd, UpdateCallback);
                    break;
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutCallback);
                    break;
                case IDM_EXIT:
                        DestroyWindow(hWnd);
                        break;
                    default:
                        return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;
       }
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            UNREFERENCED_PARAMETER(hdc);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

BOOL CenterWindow(HWND hwndWindow)
{
    HWND hwndParent;
    RECT rectWindow, rectParent;

    // make the window relative to its parent
    if ((hwndParent = GetParent(hwndWindow)) != NULL)
    {
        GetWindowRect(hwndWindow, &rectWindow);
        GetWindowRect(hwndParent, &rectParent);

        int nWidth = rectWindow.right - rectWindow.left;
        int nHeight = rectWindow.bottom - rectWindow.top;

        int nX = ((rectParent.right - rectParent.left) - nWidth) / 2 + rectParent.left;
        int nY = ((rectParent.bottom - rectParent.top) - nHeight) / 2 + rectParent.top;

        int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
        int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

        // make sure that the dialog box never moves outside of the screen
        if (nX < 0) nX = 0;
        if (nY < 0) nY = 0;
        if (nX + nWidth > nScreenWidth) nX = nScreenWidth - nWidth;
        if (nY + nHeight > nScreenHeight) nY = nScreenHeight - nHeight;

        MoveWindow(hwndWindow, nX, nY, nWidth, nHeight, FALSE);

        return TRUE;
    }

    return FALSE;
}

// Message handler for about box.
INT_PTR CALLBACK AboutCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_INITDIALOG:
            CenterWindow(hDlg);
            return (INT_PTR)TRUE;
        case WM_COMMAND:
        {
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

HWND hwndDialog = nullptr;
void UI_Callback(int, const std::wstring& strMessage)
{
    SetWindowText(GetDlgItem(hwndDialog, IDC_STATUS), strMessage.c_str());
    UpdateWindow(GetDlgItem(hwndDialog, IDC_STATUS));
}

bool g_bThreadRunning = false;
bool g_bNewUpdateFound = false;
DWORD WINAPI UpdateThreadProc(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);

    g_bThreadRunning = true;
    const DWORD nLength = _MAX_PATH;
    TCHAR lpszFilePath[nLength] = { 0, };
    GetModuleFileName(nullptr, lpszFilePath, nLength);
    g_bNewUpdateFound = CheckForUpdates(lpszFilePath, _T("https://www.moga.doctor/freeware/genUp4win.xml"), UI_Callback);
    g_bThreadRunning = false;

    ::ExitThread(0);
    return 0;
}

DWORD m_nUpdateThreadID = 0;
HANDLE m_hUpdateThread = 0;
UINT_PTR m_nTimerID = 0;
// Message handler for Check for updates box.
INT_PTR CALLBACK UpdateCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
        case WM_INITDIALOG:
            hwndDialog = hDlg; // used in UI_Callback
            CenterWindow(hDlg);
            // SendMessage(GetDlgItem(hDlg, IDC_PROGRESS), (UINT)PBM_SETMARQUEE, (WPARAM)TRUE, (LPARAM)30);
            m_hUpdateThread = ::CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)UpdateThreadProc, hDlg, 0, &m_nUpdateThreadID);
            m_nTimerID = SetTimer(hDlg, 0x1234, 100, nullptr);
            return (INT_PTR)TRUE;
        case WM_TIMER:
            if (!g_bThreadRunning)
            {
                EndDialog(hDlg, IDCANCEL);
                if (g_bNewUpdateFound)
                {
                    PostQuitMessage(0);
                }
            }
            return 0;
        case WM_COMMAND:
        {
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
        }
    }
    return (INT_PTR)FALSE;
}

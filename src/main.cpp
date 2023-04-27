#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <commctrl.h>
#include "memhacking.hpp"

#define ID_TRACKBAR 100
#define ID_LABEL    101
#define ID_BUTTON   102

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = {0};
    HWND hwnd;
    MSG msg;

    // Register the window class.
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "Tbc243NameplateMaxDistance";
    RegisterClass(&wc);

    // Create the window.
    hwnd = CreateWindow(
        "Tbc243NameplateMaxDistance", 
        "Tbc 2.4.3 Tweaks", 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        286, 160, 
        NULL, NULL, hInstance, NULL);

    // Create the trackbar.
    InitCommonControls();
    HWND hTrackbar = CreateWindowEx(0, TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE | TBS_HORZ, 15, 20, 250, 30, hwnd, (HMENU)ID_TRACKBAR, hInstance, NULL);
    SendMessage(hTrackbar, TBM_SETRANGE, TRUE, MAKELPARAM(5, 100));
    SendMessage(hTrackbar, TBM_SETPOS, TRUE, 35);

    // Create the label text component.
    HWND hLabel = CreateWindowEx(0, "STATIC", "35 yards", WS_CHILD | WS_VISIBLE | SS_CENTER, 15, 50, 250, 30, hwnd, (HMENU)ID_LABEL, hInstance, NULL);

    // Create the button.
    HWND hButton = CreateWindow("BUTTON", "Set Distance", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 160, 90, 100, 25, hwnd, (HMENU)ID_BUTTON, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_BUTTON) {
                // Handle button click event.
                int yards = SendMessage((HWND)lParam, TBM_GETPOS, 0, 0);
                SetNameplateMaxDistance(yards);
            }
            break;

        case WM_HSCROLL:
            if (GetDlgCtrlID((HWND)lParam) == ID_TRACKBAR) {
                int pos = SendMessage((HWND)lParam, TBM_GETPOS, 0, 0);
                char buf[16];
                sprintf(buf, "%d yards", pos);
                SetWindowText(GetDlgItem(hwnd, ID_LABEL), buf);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int main()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int nCmdShow = SW_SHOWDEFAULT;

    WinMain(hInstance, NULL, NULL, nCmdShow);

    return 0;
}
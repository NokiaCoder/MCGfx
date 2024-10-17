#pragma once
#include <windows.h>
#include <string>
#include <thread>
#include "GameManager.h"
#include "MCGraphics.cpp"
#include "TBGlobals.h"

using namespace std;


static MCGraphics graphics; 
static GameManager game;

bool lMouseButtonDown = false;
bool rMouseButtonDown = false;
POINT lastMouseDown;
POINT lastMousePos;
int windowWidth = 800;
int windowHeight = 600;
wstring windowTitle = L"";


// Forward declaration of the Window Procedure
LRESULT CALLBACK WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);




int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    const wchar_t CLASS_NAME[] = L"SimpleWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(GetStockObject(BLACK_BRUSH));
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClass(&wc);

    //Center the window on the screen
    RECT rect = { 0, 0, windowWidth, windowHeight };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;

    // Get screen dimensions
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Calculate centered position
    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;

    HWND hwnd = CreateWindowEx(
        0,                          // Optional window styles
        CLASS_NAME,                 // Window class
        windowTitle.c_str(),         // Window text
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,  // Non-resizable window style
        x, y,                       // Position (centered)
        windowWidth,                // Width
        windowHeight,               // Height
        nullptr,                    // Parent window
        nullptr,                    // Menu
        hInstance,                  // Instance handle
        nullptr                     // Additional application data
    );

    if (hwnd == nullptr) 
    {
        return 0;
    }

    ShowWindow(hwnd, nShowCmd);


    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        game.Process();
        game.Render(hwnd);
        //double t = GetElapsedMilliseconds();
        //while (t < 1000.0)
        //{
        //    int i = 5;
        //}
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}




LRESULT CALLBACK WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    switch (uMsg) 
    {
    case WM_CREATE:
        graphics.Initialize(g_pixelWidth,g_pixelHeight);
        graphics.Clear();
        game.SetPointer(&graphics);
        game.Restart();
        
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT: 
        graphics.Present(hwnd);
        return 0;

        case WM_KEYUP:
            game.HandleKey((int)wParam, false);
        return 0;

        case WM_KEYDOWN:
            game.HandleKey((int)wParam, true);
            return 0;
        
    case WM_LBUTTONDOWN:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            lastMouseDown.x = x;
            lastMouseDown.y = y;
            lMouseButtonDown = true;
            game.Update(lMouseButtonDown, rMouseButtonDown, x, y);
        }
		return 0;

    case WM_RBUTTONDOWN:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            lastMouseDown.x = x;
            lastMouseDown.y = y;
            rMouseButtonDown = true;
            game.Update(lMouseButtonDown, rMouseButtonDown, x, y);
        }
        return 0;

    case WM_LBUTTONUP:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            lMouseButtonDown = false;
            game.Update(lMouseButtonDown, rMouseButtonDown, x, y);
        }
        return 0;
   
    case WM_RBUTTONUP:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            rMouseButtonDown = false;
            game.Update(lMouseButtonDown, rMouseButtonDown, x, y);
        }
        return 0;

    case WM_MOUSEMOVE:
        {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            lastMousePos.x = x;
            lastMousePos.y = y;
            game.Update(lMouseButtonDown, rMouseButtonDown, x, y);
            wstring txt = g_GameTitle + L"      mouse: " + to_wstring(x) + L", " + to_wstring(y);
            SetWindowTextW(hwnd, txt.c_str());
        }
		return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

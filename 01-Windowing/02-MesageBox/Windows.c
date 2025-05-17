#include <windows.h>


// Global function declarations or prototype or signature
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // Varibale declaration
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("RTR6");

    // Window class initialization
    // code
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszClassName = szAppName;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // register window class
    RegisterClassEx(&wndclass);

    // Create window class
    hwnd = CreateWindow(
        szAppName,
        TEXT("Rajashree Adikane"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    // show window
    ShowWindow(hwnd, iCmdShow);

    // paint window 
    UpdateWindow(hwnd);

    // Main message loop
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Window message handler
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
    case WM_CREATE:
        MessageBox(hwnd, TEXT("Window created"), TEXT("WM_CREATE"), MB_OK);
        break;

    case WM_SIZE:
        MessageBox(hwnd, TEXT("Window resized"), TEXT("WM_SIZE"), MB_OK);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            MessageBox(hwnd, TEXT("Escape pressed"), TEXT("WM_KEYDOWN"), MB_OK);
        break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, iMsg, wParam, lParam);
    }
    return 0;
}
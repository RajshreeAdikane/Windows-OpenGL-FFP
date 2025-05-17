// Win32 Headers
#include<windows.h> 

// Global function declarations or prototype or signature
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // wnd proc window procedure this handler msg end to the window

// HWND: hndle to the window
// UNIT: Msg identifier (WM_CREATE, WM_SIZE...)
// WPARAM & LPARAM is additional msg specific info 

// Entry Point Function 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) // main entry point function replace to the int main
// HINSTANCE hInstance: handle to the current instance 
// HINSTANCE hPrevInstance: handle to the previous instane which is deprecated
// LPSTR lpszCmdLine: command line argument as a single string
// int iCmdShow: how window should be shown minizedd or maximized
{

    // Varibale Declarations
    WNDCLASSEX wndclass; // WNDCLASSEX is a structure in OS struct decl
    HWND hwnd; // internally pointer but cannot use as a ponter its opague because 
    MSG msg;
    TCHAR szAppName[] = TEXT("RTR6"); //TEXT is macro characterbtype its a multibyte string that converts unicode to ASCII code

    // Window class initialization
    // code
    wndclass.cbSize = sizeof(WNDCLASSEX); //size of sturcture 
    wndclass.style = CS_HREDRAW | CS_VREDRAW; // cs-class style horizontally and vertically resize the window
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc; //pointer to the message handling callback function WndProc callback fun
    wndclass.hInstance = hInstance; // handle to current instance
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Background white
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // icon of the system 
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); //handle to the cursor
    wndclass.lpszClassName = szAppName; // name of the windlow class
    wndclass.lpszMenuName = NULL; // we dont  have menu of our window
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    //Registration of window class
    RegisterClassEx(&wndclass); // its a structure WNDCLASSEX RegisterClassEx value is atom, atom is a internslly string its a unique string and its immutable

    //Create Window using registered class 
    // that is we are telling to the os that i want my cutom class window or i want to create a window
    hwnd = CreateWindow(  //memory handle will get in HWND 
        szAppName, // szAppName string or class name associated with the window, lpsz-custom class name asking, null terminated string type 
        TEXT("Rajashree Adikane"), //window caption or title unicode string that why TEXT macro
        WS_OVERLAPPEDWINDOW, //  type-DWORD-double word 32 bit DWORD internally long or unsigned long, ws-window style create window like that is top over other overlapped other windows ,
        //internally is a combination of 6 windows style( WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | S_THICKFRAME-border) think menu 
        CW_USEDEFAULT, //CW-create window, used for function paramter macro, create window used default,  for x-cordinate
        CW_USEDEFAULT,//y-cordinate
        CW_USEDEFAULT,//w-width
        CW_USEDEFAULT,//h-height
        NULL,
        NULL,
        hInstance,
        NULL
    );

    //The window is created in memory (RAM), and hwnd is the handle to that window. Everything related to the window is mapped to this handle, similar to how a database table maps to a unique identifier, like an Aadhaar number. Although hwnd may seem like a pointer, the OS treats it as an index or reference rather than a direct memory address, similar to how an array or table lookup works. 

    //Show Window to show the window that is crated in the memory
    ShowWindow(hwnd, iCmdShow); // iCmdShow is os winmain 4th parameter by deafault how window should be look that is that parameter 

    //Paint Window
    UpdateWindow(hwnd);

    // Message Loop
    // The user generates events such as key presses, mouse clicks, or window movements.
    // These events are captured by the OS, which then creates corresponding messages 
    // (e.g., WM_KEYDOWN, WM_LBUTTONDOWN). Each message is a unique 32-bit number 
    // defined as a macro (WM_*) by the OS. 
    // 
    // The OS places these messages in a message queue, and `GetMessage` retrieves 
    // them from this queue one by one. The retrieved message is then passed to 
    // `TranslateMessage`, which processes keyboard input (e.g., converts raw key 
    // presses into character messages). After that, `DispatchMessage` forwards 
    // the message to `WndProc`, where it is handled accordingly. 
    //
    // `GetMessage(&msg, NULL, 0, 0)` retrieves all messages for the window. 
    // The first `NULL` parameter means messages are fetched for the main window 
    // (not a child window). The range `(0, 0)` means all messages are processed. 
    //
    // `GetMessage` returns a BOOL value: 
    // - It returns `TRUE` for all messages except `WM_QUIT`. 
    // - It returns `FALSE` only when `WM_QUIT` is encountered, which exits the loop.

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); // Converts virtual key(events) messages to character messages if needed
        DispatchMessage(&msg);  // Sends the message to the WndProc function for handling
    }

    // The program exits when `WM_QUIT` is received, returning the exit code (`msg.wParam`).
    return ((int)msg.wParam);
}


//CallBack Function
// Callback Function (Window Procedure)
// This function processes messages sent to the window. It is automatically called 
// by the system whenever an event occurs (e.g., window creation, resizing, 
// key press, mouse click). The function receives the following parameters:
//
// - `hwnd`: Handle to the window receiving the message.
// - `iMsg`: The message identifier (e.g., WM_CREATE, WM_KEYDOWN).
// - `wParam`: Additional information (e.g., which key was pressed).
// - `lParam`: Additional information depending on the message type.

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
    case WM_CREATE:

    case WM_LBUTTONDOWN:  // Left mouse button click
        MessageBox(hwnd, TEXT("WM_LBUTTONDOWN message received!"), TEXT("Mouse Click"), MB_OK);
        break;

    case WM_RBUTTONDOWN:  // Right mouse button click
        MessageBox(hwnd, TEXT("WM_RBUTTONDOWN message received!"), TEXT("Right Click"), MB_OK);
        break;

    case WM_KEYDOWN:  // Key press event
        MessageBox(hwnd, TEXT("WM_KEYDOWN message received!"), TEXT("Key Press"), MB_OK);
        break;

    case WM_DESTROY:  // Window close event
        MessageBox(hwnd, TEXT("WM_DESTROY message received!"), TEXT("Exiting"), MB_OK);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, iMsg, wParam, lParam);
    }

    return 0;
}





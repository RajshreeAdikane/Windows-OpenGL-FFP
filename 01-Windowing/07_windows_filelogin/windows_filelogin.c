#include <windows.h>
#include <stdio.h> // this file is included called file io is also std io file open write read and file close
#include<stdlib.h> // if file want to clode then exit function or library is in std lib header file
#include "Window.h"

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// global variable declarations for full screen
BOOL gbFullScreen = FALSE;    
HWND ghwnd = NULL;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;

//global declarations for file io
char gszlogFileName[] = "log.txt";// mix programing simple libabry its not win 32, its a std c libabry thats why we use char Not TCHAR
FILE *gpFile; // File pointer, FILE is a datatype in stdio.h 

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // variable declarations
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("RTR6");

    // Coming in winmain we have to create file
    // create log file
    gpFile = fopen("gszlogFileName", "w"); // fopen it is a std c library function use for opening and creating file for "r" : read, "w" : write , edit: "append"
    if (gpFile == NULL) {
        MessageBox(NULL, TEXT("Log File Creation Faild!"), TEXT("Error"), MB_OK);
        exit(0); // this is system error thats why exit 0 if it was my error then i would be write return -1;
    }
    else {
        fprintf(gpFile, "Program started successfully!\n");// fprintf means f means file in that print
    }
    //fflush(gpFile); 

    // window class initialization
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.lpszClassName = szAppName;
    wndclass.lpszMenuName = NULL;
    wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));

    // Register window class
    RegisterClassEx(&wndclass);

    // Create window
    hwnd = CreateWindowEx(WS_EX_APPWINDOW,
                          szAppName,
                          TEXT("RAJASHREE ADIKANE"),
                          WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
    ghwnd = hwnd;

    // Show window
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    // Message loop
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //close the files
    if (gpFile) {
        fprintf(gpFile,"Program Terminated Successfully!\n");
        fclose(gpFile);
        gpFile = NULL;
    }

    return((int)msg.wParam);
}



// Callback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    void toggleFullScreen(void);

    switch (iMsg)
    {
    case WM_CREATE:
        ZeroMemory((void*)&wpPrev, sizeof(WINDOWPLACEMENT));
        wpPrev.length = sizeof(WINDOWPLACEMENT);
        break;

    case WM_CHAR:
        switch (wParam)
        {
        case 'F':
        case 'f':
            if (gbFullScreen == FALSE)
            {
                toggleFullScreen();
                gbFullScreen = TRUE;
            }
            else
            {
                toggleFullScreen();
                gbFullScreen = FALSE;
            }
            break;

        default:
            break;
        }
        break;

    case WM_DESTROY:
        // Write termination message and close log file
   /*     if (logFile != NULL)
        {
            fprintf(logFile, "Program terminated successfully!\n");
            fclose(logFile);
        }*/
        PostQuitMessage(0);
        break;

    default:
        break;
    }

    return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

// User-defined function
void toggleFullScreen(void)
{
    MONITORINFO mi;

    if (gbFullScreen == FALSE)
    {
        dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
        if (dwStyle & WS_OVERLAPPEDWINDOW)
        {
            ZeroMemory((void*)&mi, sizeof(MONITORINFO));
            mi.cbSize = sizeof(MONITORINFO);
            if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
            {
                SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(ghwnd,
                             HWND_TOP,
                             mi.rcMonitor.left,
                             mi.rcMonitor.top,
                             mi.rcMonitor.right - mi.rcMonitor.left,
                             mi.rcMonitor.bottom - mi.rcMonitor.top,
                             SWP_NOZORDER | SWP_FRAMECHANGED);
            }
        }
        ShowCursor(FALSE);
    }
    else
    {
        SetWindowPlacement(ghwnd, &wpPrev);
        SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
        SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
    ShowCursor(TRUE);
}

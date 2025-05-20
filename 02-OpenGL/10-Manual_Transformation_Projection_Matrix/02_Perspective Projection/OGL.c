// Win32 headers 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES 1 
#include <math.h>

// OpenGL Related Header Files
#include <gl/GL.h>

// Custom header files
#include "OGL.h"

// OpenGL related libraries
#pragma comment(lib, "opengl32.lib")

//Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations
BOOL gbFullScreen = FALSE;
HWND ghwnd = NULL;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;

// Variable related with File I/O
char gszLogFileName[] = "Log.txt";
FILE* gpFile = NULL;

// Active window related variables
BOOL gbActiveWindow = FALSE;

// Exit key press related 
BOOL gbEscapeKeyIsPressed = FALSE;

// OpenGL related global variables
HDC ghdc = NULL;
HGLRC ghrc = NULL;

// Matrix variables
GLfloat identityMatrix[16];
GLfloat perspectiveMatrix[16];

// Function prototypes
void loadIdentityMatrix(GLfloat* matrix);
void createPerspectiveMatrix(GLfloat* matrix, GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);
void multiplyMatrix(GLfloat* result, GLfloat* matA, GLfloat* matB);

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
    // function declarations
    int initialize(void);
    void display(void);
    void update(void);
    void uninitialize(void);

    //variable declarations
    WNDCLASSEX wndclass;
    HWND hwnd;
    MSG msg;
    TCHAR szAppName[] = TEXT("RTR6 : My Window");
    BOOL bDone = FALSE;

    // Create Log File
    gpFile = fopen(gszLogFileName, "w");

    if (gpFile == NULL)
    {
        MessageBox(NULL, TEXT("Log file creation failed!"), TEXT("File I/O Error"), MB_OK);
        exit(0);
    }
    else
    {
        fprintf(gpFile, "File successfully created\n");
    }

    // window class initialization
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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

    // Registration of window class
    RegisterClassEx(&wndclass);

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int xPos = (screenWidth - WIN_WIDTH) / 2;
    int yPos = (screenHeight - WIN_HEIGHT) / 2;

    // Create Window     
    hwnd = CreateWindowEx(WS_EX_APPWINDOW,
        szAppName,
        TEXT("Rajashree Adikane"),
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
        xPos,
        yPos,
        WIN_WIDTH,
        WIN_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL);

    ghwnd = hwnd;
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    // initialize
    int result = initialize();
    if (result != 0)
    {
        fprintf(gpFile, "Initialize() : Failed!!!\n");
        DestroyWindow(hwnd);
        hwnd = NULL;
    }
    else
    {
        fprintf(gpFile, "initialize() : Completed successfully...\n");
    }

    SetForegroundWindow(hwnd);
    SetFocus(hwnd);

    // Game Loop
    while (bDone == FALSE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bDone = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if (gbActiveWindow == TRUE)
            {
                if (gbEscapeKeyIsPressed == TRUE)
                {
                    bDone = TRUE;
                }
                display();
                update();
            }
        }
    }

    uninitialize();
    return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
    void toggleFullScreen(void);
    void resize(int, int);
    void uninitialize(void);

    switch (imsg)
    {
    case WM_CREATE:
        ZeroMemory((void*)&wpPrev, sizeof(WINDOWPLACEMENT));
        wpPrev.length = sizeof(WINDOWPLACEMENT);
        break;
    case WM_SETFOCUS:
        gbActiveWindow = TRUE;
        break;
    case WM_KILLFOCUS:
        gbActiveWindow = FALSE;
        break;
    case WM_ERASEBKGND:
        return(0);
    case WM_SIZE:
        resize(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            gbEscapeKeyIsPressed = TRUE;
            break;
        default:
            break;
        }
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
    case WM_CLOSE:
        uninitialize();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        break;
    }
    return (DefWindowProc(hwnd, imsg, wParam, lParam));
}

void toggleFullScreen(void)
{
    MONITORINFO mi;
    ZeroMemory((void*)&mi, sizeof(MONITORINFO));
    mi.cbSize = sizeof(MONITORINFO);

    if (gbFullScreen == FALSE)
    {
        dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

        if (dwStyle & WS_OVERLAPPEDWINDOW)
        {
            if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
            {
                SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
                SetWindowPos(ghwnd, HWND_TOP,
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
        ShowCursor(TRUE);
    }
}

int initialize(void)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iPixelFormatIndex = 0;

    ZeroMemory((void*)&pfd, sizeof(PIXELFORMATDESCRIPTOR));
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cRedBits = 8;
    pfd.cGreenBits = 8;
    pfd.cBlueBits = 8;
    pfd.cAlphaBits = 8;

    ghdc = GetDC(ghwnd);
    if (ghdc == NULL)
    {
        fprintf(gpFile, "GetDC() : function failed!\n");
        return (-1);
    }

    iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
    if (iPixelFormatIndex == 0)
    {
        fprintf(gpFile, "ChoosePixelFormat() : Failed!\n");
        return (-2);
    }

    if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
    {
        fprintf(gpFile, "SetPixelFormat() : Failed!\n");
        return (-3);
    }

    ghrc = wglCreateContext(ghdc);
    if (ghrc == NULL)
    {
        fprintf(gpFile, "wglCreateContext() : Failed!\n");
        return (-4);
    }

    if (wglMakeCurrent(ghdc, ghrc) == FALSE)
    {
        fprintf(gpFile, "wglMakeCurrent() : Failed!\n");
        return (-5);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0f);

    // Initialize identity matrix
    loadIdentityMatrix(identityMatrix);

    // Initialize perspective matrix with default values
    createPerspectiveMatrix(perspectiveMatrix, 45.0f, (GLfloat)WIN_WIDTH / (GLfloat)WIN_HEIGHT, 0.1f, 100.0f);


    return (0);
}

void resize(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);


    createPerspectiveMatrix(perspectiveMatrix, 45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

    // Set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(perspectiveMatrix);

    // Switch back to modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void loadIdentityMatrix(GLfloat* matrix)
{
    for (int i = 0; i < 16; i++)
        matrix[i] = 0.0f;

    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;
    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;
    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}

void createPerspectiveMatrix(GLfloat* matrix, GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
    GLfloat f = 1.0f / tan(fovy * M_PI / 360.0f);
    GLfloat range = zNear - zFar;

    loadIdentityMatrix(matrix);

    matrix[0] = f / aspect;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;
    matrix[4] = 0.0f;
    matrix[5] = f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;
    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = (zFar + zNear) / range;
    matrix[11] = -1.0f;
    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = (2.0f * zFar * zNear) / range;
    matrix[15] = 0.0f;
}

void multiplyMatrix(GLfloat* result, GLfloat* matA, GLfloat* matB)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result[i * 4 + j] = 0.0f;
            for (int k = 0; k < 4; k++)
            {
                result[i * 4 + j] += matA[i * 4 + k] * matB[k * 4 + j];
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw a triangle that fits within our orthographic projection (-1 to 1)
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);   // White
    glVertex3f(0.0f, 0.5f, 0.0f);  // Top vertex

    glColor3f(1.0f, 1.0f, 1.0f);   // White
    glVertex3f(-0.5f, -0.5f, 0.0f); // Bottom left vertex

    glColor3f(1.0f, 1.0f, 1.0f);   // White
    glVertex3f(0.5f, -0.5f, 0.0f);  // Bottom right vertex
    glEnd();

    SwapBuffers(ghdc);
}

void update(void)
{
    // No updates needed for static triangle
}

void uninitialize(void)
{
    if (gbFullScreen == TRUE)
    {
        toggleFullScreen();
        gbFullScreen = FALSE;
    }

    if (wglGetCurrentContext() == ghrc)
    {
        wglMakeCurrent(NULL, NULL);
    }

    if (ghrc)
    {
        wglDeleteContext(ghrc);
        ghrc = NULL;
    }

    if (ghdc)
    {
        ReleaseDC(ghwnd, ghdc);
        ghdc = NULL;
    }

    if (ghwnd)
    {
        DestroyWindow(ghwnd);
        ghwnd = NULL;
    }

    if (gpFile != NULL)
    {
        fprintf(gpFile, "Program terminated successfully\n");
        fclose(gpFile);
        gpFile = NULL;
    }
}
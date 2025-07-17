// Win32 headers 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES 1 
#include <math.h>

// OpenGL Related Header Files
#include <gl/GL.h> // visual studio 

#include <gl/GLU.h>

// Custom header files
#include "Triangle.h"

// OpenGL related libraries
#pragma comment(lib, "opengl32.lib") //give linker the link file for import
#pragma comment(lib, "GLU32.lib")
#pragma comment(lib, "winmm.lib") //realted sound

//Macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations
//variable related to Full Screen
BOOL gbFullScreen = FALSE;
HWND ghwnd = NULL;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;

// Variable related with File I/O
char gszLogFuileName[] = "Log.txt";
FILE* gpFile = NULL;

// Active window related variables
BOOL gbActiveWindow = FALSE;

// Exit key press related 
BOOL gbEscapeKeyIsPressed = FALSE;

// OpenGL related global variables
HDC ghdc = NULL;
HGLRC ghrc = NULL;

// variables for BHARAT Movement
GLfloat translateX = -1.8f;
GLfloat posbX = 1.0f;

GLfloat poshX = -3.0f;
GLfloat poshY = 3.0f;

GLfloat posaX = -3.0f;
GLfloat posaY = -3.0f;

GLfloat posrX = -3.0f;
GLfloat posrY = 3.0f;

GLfloat posa1X = 3.0f;
GLfloat posa1Y = -3.0f;

GLfloat postX = 4.0f;

//speed
GLfloat speed = 0.00025f/2.0f;

//realted movement
BOOL isMovingB = TRUE;
BOOL isMovingH = FALSE;
BOOL isMovingA = FALSE;
BOOL isMovingR = FALSE;
BOOL isMovingA1 = FALSE;
BOOL isMovingT = FALSE;
GLfloat angle = 0.0f;

// Variables for rotate Deathly Hallows
GLfloat planeTopAngle = 30.0f;

BOOL moveMiddle = FALSE;
BOOL moveMiddleStaright = FALSE;
BOOL isMovingTop = FALSE;
//BOOL isTopStraight = FALSE;
BOOL isTopMiddle = FALSE;
BOOL isMovingExit = FALSE;
BOOL moveBottom = FALSE;
BOOL isBottomMiddle = FALSE;
BOOL isBottomExit = FALSE;

GLfloat planeMiddleX = 10.0f;
GLfloat planeTopX = -10.0f, planeTopY = 10.0f;
GLfloat planeBottomX = -10.0f, planeBottomY = -10.0f;

GLfloat T_position_x = 0.6f;

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{

	// function declaration
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
	gpFile = fopen(gszLogFuileName, "w");

	if (gpFile == NULL)
	{
		MessageBox(NULL, TEXT("Log file creation failed!"), TEXT("File I/O Error"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "File succesfully created\n");
	}
	// code
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

	// Regestration of window class
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
	// Show window
	ShowWindow(hwnd, iCmdShow);

	//Paint background of the window
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

	// Set this window as foreground and active window
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	//playdound
	PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC);

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
				// Render
				display();
				// update
				update();
			}
		}
	}

	// uninitialize
	uninitialize();
	return ((int)msg.wParam);
}

// Callback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
	// local function declarations
	void toggleFullScreen(void);
	void resize(int, int);
	void uninitialize(void);
	// code
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
	//variable declarations
	MONITORINFO mi;
	ZeroMemory((void*)&mi, sizeof(MONITORINFO));
	mi.cbSize = sizeof(MONITORINFO);
	//code
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
	//code
	// function declration
	void printGLInfo(void);
	void resize(int, int);

	// variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex = 0;

	// code
	// PIXELFORMATDESCRIPTOR initialization
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

	// Get DC
	ghdc = GetDC(ghwnd);
	if (ghdc == NULL)
	{
		fprintf(gpFile, "GetDC() : function failed!\n");
		return (-1);
	}

	// Get matching pixel format index using HDC and pfd
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		fprintf(gpFile, "ChoosePixelFormat() : Failed!\n");
		return (-2);
	}

	// Select the pixel format of found index
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gpFile, "SetPixelFormat() : Failed!\n");
		return (-3);
	}

	// Create Rendering context using HDC , PFD and Pixel Format Index and choosen pixel format index
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		fprintf(gpFile, "wglCreateContext() : Failed!\n");
		return (-4);
	}

	// Make this rendering context as current context
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpFile, "wglMakeCurrent() : Failed!\n");
		return (-5);
	}

	//printGLInfo
	printGLInfo();

	// From here Onwords OpenGL code starts
	// Tell OpenGL to choose the color to clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//warm up resize
	resize(WIN_WIDTH, WIN_HEIGHT);
	return (0);
}

void printGLInfo(void)
{
	//print OpenGL info
	fprintf(gpFile, "*********************\n");
	fprintf(gpFile, "OpenGL Vendor  : %s\n", glGetString(GL_VENDOR));
	fprintf(gpFile, "OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(gpFile, "OpenGL Version : %s\n", glGetString(GL_VERSION));
	fprintf(gpFile, "*********************\n");
	const GLubyte* version = glGetString(GL_VERSION);

}

void resize(int width, int height)
{
	// code
	// if height by accident is less than 0 make it 1
	if (height < 0)
	{
		height = 1;
	}
	// set the view port
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//set matrix projection mode
	glMatrixMode(GL_PROJECTION);

	//set identity to matrix
	glLoadIdentity();

	//Do perspective projection
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

}

void movingFunc(void) {
	if (isMovingB) {
		posbX -= speed;
		if (posbX <= 0.0f) {
			posbX = 0.0f;
			isMovingB = FALSE;
			isMovingH = TRUE; 
		}
	}
	else if (isMovingH) {
		poshX += speed;
		poshY -= speed; 

		if (poshX >= 0.0f && poshY <= 0.0f) {
			poshX = 0.0f;
			poshY = 0.0f;
			isMovingH = FALSE;
			isMovingA = TRUE;
		}
	}
	else if (isMovingA) {
		posaX += speed;
		posaY += speed;

		if (posaX >= 0.0f && posaY >= 0.0f) {
			posaX = 0.0f;
			posaX = 0.0f;
			isMovingA = FALSE;
			isMovingR = TRUE;
		}
	}
	else if (isMovingR) {
		posrX += speed;
		posrY -= speed; 

		if (posrX >= 0.0f && posrY <= 0.0f) {
			posrX = 0.0f;
			posrY = 0.0f;
			isMovingR = FALSE;
			isMovingA1 = TRUE;
		}
	}
	else if (isMovingA1) {
		posa1X -= speed; 
		posa1Y += speed; 

		if (posa1X <= 0.0f && posa1Y >= 0.0f) {
			posa1X = 0.0f;
			posa1Y = 0.0f;
			isMovingA1 = FALSE;
			isMovingT = TRUE;
		}
	}
	else if (isMovingT) {
		postX -= speed;
		if (postX <= 0.0f) {
			postX = 0.0f;
			isMovingT = FALSE;
			moveMiddle = TRUE;
			isMovingTop = TRUE;
			moveBottom = TRUE;
		}
	}
	if (moveMiddle) {
		planeMiddleX -= speed * 3.0;
		if (planeMiddleX <= 0.0f) {
			planeMiddleX = 0.0f;
			moveMiddle = FALSE;
			moveMiddleStaright = TRUE;
		}
	}

	if (moveMiddleStaright) {
		planeMiddleX -= speed * 3.0;
		if (planeMiddleX >= 0.0f) {
			planeMiddleX = 0.0f;
			//isMovingB = FALSE;
		}
	}

	if (isMovingTop) {
		planeTopX += speed * 3.0f;

		if (planeTopX <= planeMiddleX) {
			planeTopY = 1.0f + (planeTopX * planeTopX) * 0.2f;
			planeTopAngle = 40.0f * (planeMiddleX - planeTopX) / (planeMiddleX - (-10.0f));
		}

		if (planeTopX >= planeMiddleX) {
			planeTopX = planeMiddleX;
			planeTopY = 1.0f;
			planeTopAngle = 0.0f; // Reset rotation
			isMovingTop = FALSE;
			isTopMiddle = TRUE;
		}
	}



	if (isTopMiddle) {
		planeTopX += speed * 3.0f;
		if (planeTopX >= 20.0f) {
			planeTopX = 20.0f;
			planeTopY = 1.0f;
			isTopMiddle = FALSE;
			isMovingExit = TRUE;
		}
	}

	if (isMovingExit)
	{
		planeTopX += speed * 3.0f;
		fprintf(gpFile, "speed1: %.2f\n", planeBottomX);
		if (planeTopX <= 30.0f)
		{
			float t = (planeTopX - 7.0f) / (20.0f - 7.0f);
			planeTopY = 1.0f + (1.0f - t) * (1.0f - t) * 9.0f;
			planeTopAngle = 30.0f * (1.0f - t);

		}
	}

	if (moveBottom)
	{
		planeBottomX += speed * 3.0f;
		if (planeBottomX <= planeMiddleX)
		{
			planeBottomY = 1.0f + (planeBottomX * planeBottomX) * 0.2f;
			planeTopAngle = 40.0f * (planeMiddleX - planeTopX) / (planeMiddleX - (-10.0f));
		}
		if (planeBottomX >= planeMiddleX) {
			planeBottomX = planeMiddleX;
			planeBottomY = 1.0f;
			moveBottom = FALSE;
			isBottomMiddle = TRUE;
		}
	}

	if (isBottomMiddle) {
		planeBottomX += speed * 3.0f;
		if (planeBottomX >= 20.0f) {
			planeBottomX = 20.0f;
			planeBottomY = 1.0f;
			isBottomMiddle = FALSE;
			isBottomExit = TRUE;
		}
	}
	if (isBottomExit)
	{
		planeBottomX += speed * 3.0f;

		fprintf(gpFile, "speed2: %.2f\n", planeBottomX);
		if (planeBottomX <= 30.0f)
		{
			float t = (planeBottomX - 7.0f) / (20.0f - 7.0f);
			planeBottomY = 1.0f + (1.0f - t) * (1.0f - t) * 9.0f;
		}
	}

}

void LetterB(void)
{
	movingFunc();
	glPushMatrix();
	glTranslatef(translateX-posbX, 0.0f, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f); 

	
	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;

	if (planeMiddleX <= -2.0f) {
		// Use original colors when planeMiddleX > 2
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}
	/*fprintf(gpFile, "x = %f", planeMiddleX);*/
	// Left vertical bar 
	glBegin(GL_QUADS);
	 glColor3fv(saffron);
	glVertex3f(-0.98f, 1.0f, 0.0f);   
	glVertex3f(-0.3f, 0.557f, 0.0f); 
	 glColor3fv(white);
	glVertex3f(-0.3f, 0.22f, 0.0f);   
	glVertex3f(-0.98f, 0.22f, 0.0f);  
	glEnd();

	// Middle connecting part
	glBegin(GL_QUADS);
	 glColor3fv(white);
	glVertex3f(-0.98f, 0.22f, 0.0f);
	glVertex3f(-0.3f, 0.22f, 0.0f);
	 glColor3fv(white);
	glVertex3f(-0.3f, -0.175f, 0.0f);
	glVertex3f(-0.98f, -0.175f, 0.0f);
	glEnd();

	// Lower vertical bar
	glBegin(GL_QUADS);
	 glColor3fv(white);
	glVertex3f(-0.98f, -0.175f, 0.0f);
	glVertex3f(-0.3f, -0.175f, 0.0f);

	 glColor3fv(green);
	glVertex3f(-0.3f, -0.595f, 0.0f);
	glVertex3f(-0.98f, -1.0f, 0.0f);

	glEnd();

	// Upper curved section
	glBegin(GL_QUADS);

	 glColor3fv(saffron);
	glVertex3f(0.54f, 1.0f, 0.0f);
	glVertex3f(-0.98f, 1.0f, 0.0f);

	 glColor3fv(saffron);
	glVertex3f(-0.3f, 0.557f, 0.0f);
	glVertex3f(0.17f, 0.557f, 0.0f);
	glEnd();

	// Lower curved section
	glBegin(GL_QUADS);
	 glColor3fv(green);
	glVertex3f(0.17f, -0.594f, 0.0f);
	glVertex3f(-0.3f, -0.594f, 0.0f);
	 glColor3fv(green);
	glVertex3f(-0.98f, -0.99f, 0.0f);
	glVertex3f(0.54f, -0.99f, 0.0f);
	glEnd();

	// Top-right corner
	glBegin(GL_QUADS);

	 glColor3fv(saffron);
	glVertex3f(0.17f, 0.567f, 0.0f);
	glVertex3f(0.54f, 1.0f, 0.0f);
	 glColor3fv(saffron);
	glVertex3f(0.98f, 0.7f, 0.0f);
	glVertex3f(0.3f, 0.49f, 0.0f);
	glEnd();

	 //Top middle curve
	glBegin(GL_QUADS);
	 glColor3fv(white);
	glVertex3f(0.98f, 0.7f, 0.0f);
	glVertex3f(0.98f, 0.49f, 0.0f);
	glVertex3f(0.3f, 0.3f, 0.0f);
	glVertex3f(0.98f, 0.2f, 0.0f);
	glEnd();

	 //Middle connecting part
	glBegin(GL_QUADS);
	 glColor3fv(saffron);
	glVertex3f(0.98f, 0.7f, 0.0f);
	glVertex3f(0.3f, 0.5f, 0.0f);
	 glColor3fv(white);
	glVertex3f(0.3f, 0.26f, 0.0f);
	glVertex3f(0.98f, 0.22f, 0.0f);
	glEnd();

	// Middle lower curve
	glBegin(GL_QUADS);
	glVertex3f(0.98f, 0.2f, 0.0f);
	glVertex3f(0.7f, 0.02f, 0.0f);
	glVertex3f(-0.1f, 0.02f, 0.0f);
	glVertex3f(0.3f, 0.3f, 0.0f);
	glEnd();

	// Lower rectangle inside B
	glBegin(GL_QUADS);
	glVertex3f(0.7f, 0.02f, 0.0f);
	glVertex3f(0.19f, 0.02f, 0.0f);
	glVertex3f(0.19f, -0.17f, 0.0f);
	glVertex3f(0.7f, -0.17f, 0.0f);
	glEnd();

	// Bottom left diagonal connection
	glBegin(GL_QUADS);
	glVertex3f(0.7f, 0.02f, 0.0f);
	glVertex3f(0.19f, -0.17f, 0.0f);
	glVertex3f(0.3f, -0.26f, 0.0f);
	glVertex3f(0.98f, -0.16f, 0.0f);
	glEnd();

	// Middle-bottom curve
	glBegin(GL_QUADS);
	 glColor3fv(white);
	glVertex3f(0.98f, -0.16f, 0.0f);
	glVertex3f(0.3f, -0.26f, 0.0f);

	 glColor3fv(green);
	glVertex3f(0.3f, -0.5f, 0.0f);
	glVertex3f(0.98f, -0.72f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	 glColor3fv(green);
	glVertex3f(0.98f, -0.72f, 0.0f);
	glVertex3f(0.3f, -0.5f, 0.0f);
	 glColor3fv(green);
	glVertex3f(0.17f, -0.595f, 0.0f);
	glVertex3f(0.54f, -0.99f, 0.0f);
	glEnd();

	// Middle bar 
	glBegin(GL_QUADS);
	 glColor3fv(white);
	glVertex3f(0.19f, 0.22f, 0.0f);
	glVertex3f(-0.3f, 0.22f, 0.0f);
	 glColor3fv(white);
	glVertex3f(-0.3f, -0.175f, 0.0f);
	glVertex3f(0.19f, -0.175f, 0.0f);
	glEnd();

	glPopMatrix(); 
}

void LetterH(void)
{
	movingFunc();
	glPushMatrix();
	glTranslatef(translateX+poshX, poshY, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;

	if (planeMiddleX <= -5.0f) {
		// Use original colors when planeMiddleX > 2
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}
	/*fprintf(gpFile, "x = %f", planeMiddleX);*/


	// Left vertical bar - First half
	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(1.5f, 1.0f, 0.0f);
	glVertex3f(2.18f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(2.18f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glEnd();

	// Left vertical bar - Second half
	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glVertex3f(2.18f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(2.18f, -1.0f, 0.0f);
	glVertex3f(1.5f, -1.0f, 0.0f);
	glEnd();

	// Right vertical bar - First half
	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(2.97f, 1.0f, 0.0f);
	glVertex3f(3.65f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(3.65f, 0.0f, 0.0f);
	glVertex3f(2.97f, 0.0f, 0.0f);
	glEnd();

	// Right vertical bar - Second half
	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(2.97f, 0.0f, 0.0f);
	glVertex3f(3.65f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(3.65f, -1.0f, 0.0f);
	glVertex3f(2.97f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(2.18f, 0.3f, 0.0f); 
	glVertex3f(2.58f, 0.3f, 0.0f);
	glColor3fv(white);
	glVertex3f(2.58f, -0.3f, 0.0f); 
	glVertex3f(2.18f, -0.3f, 0.0f);
	glEnd();

	// Middle bar - Second half
	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(2.58f, 0.3f, 0.0f);
	glVertex3f(2.97f, 0.3f, 0.0f);
	glColor3fv(white);
	glVertex3f(2.97f, -0.3f, 0.0f);
	glVertex3f(2.58f, -0.3f, 0.0f);
	glEnd();

	glPopMatrix();
}

void LetterA(void) {
	movingFunc();
	glPushMatrix();
	glTranslatef(translateX+posaX, posaY, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;

	if (planeMiddleX <= -9.0f) {
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}
	/*fprintf(gpFile, "x = %f", planeMiddleX);*/

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(4.625f, 0.0f, 0.0f);	
	glVertex3f(5.351f, 0.0f, 0.0f);


	glColor3fv(green);
	glVertex3f(5.0f, -1.0f, 0.0f);
	glVertex3f(4.254f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	
	glColor3fv(saffron);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glColor3fv(white);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glVertex3f(5.351f, 0.0f, 0.0f);
	glVertex3f(4.625f, 0.0f, 0.0f);

	glColor3fv(white);

	glEnd();



	glBegin(GL_TRIANGLES);
	glColor3fv(saffron);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glVertex3f(5.71f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(5.39f, 1.0f, 0.0f);
	glVertex3f(6.25f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(6.7f, 0.0f, 0.0f);
	glVertex3f(6.0f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(6.0f, 0.0f, 0.0f);
	glVertex3f(6.7f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(7.15f, -1.0f, 0.0f);
	glVertex3f(6.4f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(5.43f, 0.22f, 0.0f);
	glVertex3f(5.28f, -0.19f, 0.0f);
	glColor3fv(white);
	glVertex3f(6.07f, -0.19f, 0.0f);
	glVertex3f(5.90f, 0.22f, 0.0f);
	glEnd();


	glPopMatrix();
}

void LetterR(void) {
	movingFunc();
	glPushMatrix();
	glTranslatef((translateX- 0.03)-posrX, posrY, -3.0f);
	//glTranslatef(translateX - poshX - 0.03, poshY, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;

	if (planeMiddleX <= -13.0f) {
		// Use original colors when planeMiddleX > 2
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}

	fprintf(gpFile, "x = %f", planeMiddleX);

	// Top Horizontal Part
	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(7.8f, 1.0f, 0.0f);   
	glVertex3f(8.37f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(8.37f, 0.33f, 0.0f);
	glVertex3f(7.8f, 0.33f, 0.0f); 

	glEnd();

	 //Middle Horizontal Part
	glBegin(GL_QUADS);
	glVertex3f(7.8f, 0.33f, 0.0f);  
	glVertex3f(7.8f, -0.33f, 0.0f); 
	glVertex3f(8.37f, -0.33f, 0.0f);
	glVertex3f(8.37f, 0.33f, 0.0f); 
	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(7.8f, -0.33f, 0.0f);
	glVertex3f(8.37f, -0.33f, 0.0f);

	glColor3fv(green);
	glVertex3f(8.37f, -1.0f, 0.0f);
	glVertex3f(7.8f, -1.0f, 0.0f);
	glEnd();


	glBegin(GL_QUADS);

	glColor3fv(saffron);
	glVertex3f(8.37f, 1.0f, 0.0f);
	glVertex3f(9.5f, 1.0f, 0.0f);
	glColor3fv(white);
	glVertex3f(9.3f, 0.5f, 0.0f);
	glVertex3f(8.36f, 0.5f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(9.5f, 1.0f, 0.0f);
	glVertex3f(9.92f, 0.63f, 0.0f);
	glColor3fv(white);
	glVertex3f(9.5f, 0.25f, 0.0f);
	glVertex3f(9.3f, 0.5f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(9.92f, 0.63f, 0.0f);
	glVertex3f(9.92f, 0.19f, 0.0f);
	glColor3fv(white);
	glVertex3f(9.5f, 0.1f, 0.0f);
	glVertex3f(9.5f, 0.25f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glVertex3f(9.92f, 0.19f, 0.0f);
	glVertex3f(9.6f, -0.35f, 0.0f);
	glVertex3f(9.2f, -0.19f, 0.0f);
	glVertex3f(9.5f, 0.2f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(9.4f, -0.01f, 0.0f);
	glVertex3f(9.55f, -0.37f, 0.0f);
	glVertex3f(8.37f, -0.37f, 0.0f);
	glVertex3f(8.37f, -0.01f, 0.0f);

	glEnd();


	glBegin(GL_QUADS);
	glVertex3f(9.3f, -0.22f, 0.0f);
	glVertex3f(9.6f, 0.03f, 0.0f);
	glVertex3f(9.93f, -0.40f, 0.0f);
	glVertex3f(9.45f, -0.5f, 0.0f);

	glEnd();


	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(9.93f, -0.40f, 0.0f);
	glVertex3f(9.45f, -0.5f, 0.0f);
	glColor3fv(green);
	glVertex3f(9.45f, -1.0f, 0.0f);
	glVertex3f(9.93f, -1.0f, 0.0f);
	glEnd();	

	glPopMatrix();
}

void LetterA1(GLfloat x) {
	movingFunc();
	glPushMatrix();
	glTranslatef(x + posa1X, posa1Y, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;

	if (planeMiddleX <= -15.55f) {
		// Use original colors when planeMiddleX > 2
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}
	//fprintf(gpFile, "x = %f", planeMiddleX);

	glBegin(GL_QUADS);

	//glBegin(GL_QUADS);

	glColor3fv(white);
	glVertex3f(4.625f, 0.0f, 0.0f);
	glVertex3f(5.351f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(5.0f, -1.0f, 0.0f);
	glVertex3f(4.254f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3fv(saffron);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glColor3fv(white);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glVertex3f(5.351f, 0.0f, 0.0f);
	glVertex3f(4.625f, 0.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnd();



	glBegin(GL_TRIANGLES);
	glColor3fv(saffron);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glVertex3f(5.71f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(5.39f, 1.0f, 0.0f);
	glVertex3f(6.25f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(6.7f, 0.0f, 0.0f);
	glVertex3f(6.0f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(6.0f, 0.0f, 0.0f);
	glVertex3f(6.7f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(7.15f, -1.0f, 0.0f);
	glVertex3f(6.4f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(5.43f, 0.22f, 0.0f);
	glVertex3f(5.28f, -0.19f, 0.0f);
	glColor3fv(white);
	glVertex3f(6.07f, -0.19f, 0.0f);
	glVertex3f(5.90f, 0.22f, 0.0f);
	glEnd();


	glPopMatrix();
}

void LetterT(GLfloat x) {
	glPushMatrix();
	glTranslatef(x + postX, 0.0f, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;
	if (planeMiddleX <= -17.88f) {
		// Use original colors when planeMiddleX > 2
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}

	fprintf(gpFile, "x = %f", planeMiddleX);

	// Top bar - Left half
	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(7.0f, 1.0f, 0.0f);
	glVertex3f(8.25f, 1.0f, 0.0f);
	glColor3fv(saffron);
	glVertex3f(8.25f, 0.5f, 0.0f);
	glVertex3f(7.0f, 0.5f, 0.0f);
	glEnd();

	// Top bar - Right half
	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(8.25f, 1.0f, 0.0f);
	glVertex3f(9.5f, 1.0f, 0.0f);
	glColor3fv(saffron);
	glVertex3f(9.5f, 0.5f, 0.0f);
	glVertex3f(8.25f, 0.5f, 0.0f);
	glEnd();

	// Vertical bar - Upper half
	glBegin(GL_QUADS);

	glColor3fv(saffron);
	glVertex3f(8.0f, 0.68f, 0.0f);
	glVertex3f(8.6f, 0.68f, 0.0f);

	glColor3fv(white);
	glVertex3f(8.6f, 0.0f, 0.0f);
	glVertex3f(8.0f, 0.0f, 0.0f);
	glEnd();

	// Vertical bar - Lower half
	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(8.0f, 0.0f, 0.0f);
	glVertex3f(8.6f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(8.6f, -1.0f, 0.0f);
	glVertex3f(8.0f, -1.0f, 0.0f);
	glEnd();

	glPopMatrix();
}

void DrawIAFInsignia() {
	int segments = 100;
	float radius[] = { 0.12f, 0.08f, 0.04f };

	float colors[3][3] = {
		{1.0f, 0.5f, 0.0f},   // Orange
		{1.0f, 1.0f, 1.0f},   // White
		{0.0f, 0.6f, 0.0f}    // Green
	};

	for (int i = 0; i < 3; i++) {
		glColor3f(colors[i][0], colors[i][1], colors[i][2]);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0f, 0.0f);
		for (int j = 0; j <= segments; j++) {
			float angle = 2.0f * M_PI * j / segments;
			glVertex2f(cos(angle) * radius[i], sin(angle) * radius[i]);
		}
		glEnd();
	}
}


void DrawPlane() {
		movingFunc();
		glPushMatrix();
		glScalef(0.025f/2, 0.025f/2, 0.0f);

		// Translate by x and y passed in from animation logic
		glTranslatef(-(planeMiddleX + 10.0f) * 10, 0.0f, 0.0f);
		//glTranslatef(translateX - posbX, 0.0f, -3.0f);


		glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
		glBegin(GL_POLYGON);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-2.75f, -4.8f, 0.0f);
		glVertex3f(-4.77f, -4.8f, 0.0f);
		glVertex3f(-4.77f, 4.8f, 0.0f);
		glVertex3f(-2.75f, 4.8f, 0.0f);

		glEnd();


		glColor3f(70.0f / 256.0f, 130.0f / 256.0f, 180.0f / 256.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-5.5f, 1.0f, 0.0f);
		glVertex3f(2.0f, 1.0f, 0.0f);
		glVertex3f(5.0f, 0.0f, 0.0f);
		glVertex3f(2.0f, -1.0f, 0.0f);
		glVertex3f(-5.5f, -1.0f, 0.0f);
		glEnd();

		glColor3f(0.6f, 0.6f, 0.7f);
		glBegin(GL_QUADS);
		glVertex3f(-2.75f, -4.5f, 0.0f);
		glVertex3f(-0.75f, -5.3f, 0.0f);
		glVertex3f(-4.77f, -5.0f, 0.0f);
		glVertex3f(-4.77f, -4.5f, 0.0f);

		glEnd();

		glColor3f(0.6f, 0.6f, 0.7f);
		glBegin(GL_QUADS);
		glVertex3f(-4.77f, 4.5f, 0.0f);
		glVertex3f(-2.75f, 4.5f, 0.0f);
		glVertex3f(-0.8f, 5.3f, 0.0f);
		glVertex3f(-4.77f, 5.0f, 0.0f);
		glEnd();

		glColor3f(0.6f, 0.6f, 0.7f);
		glBegin(GL_POLYGON);
		glVertex3f(-5.5f, 0.71f, 0.0f);
		glVertex3f(-5.5f, -0.71f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glVertex3f(-9.0f, -0.71f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-12.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-9.0f, 0.71f, 0.0f);
		glEnd();

		glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-9.0f, 0.71f, 0.0f);
		glVertex3f(-9.5f, 1.0f, 0.0f);
		glVertex3f(-9.5f, 3.2f, 0.0f);
		glVertex3f(-8.0f, 3.1f, 0.0f);
		//glVertex3f(-10.0f, 0.0f, 0.0f);
		glVertex3f(-5.6f, 0.71f, 0.0f);
		glEnd();

		glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-9.0f, -0.71f, 0.0f);
		glVertex3f(-9.5f, -1.0f, 0.0f);
		glVertex3f(-9.5f, -3.2f, 0.0f);
		glVertex3f(-8.0f, -3.1f, 0.0f);
		//glVertex3f(-10.0f, 0.0f, 0.0f);
		glVertex3f(-5.6f, -0.71f, 0.0f);
		glEnd();
		glTranslatef(-4.2f, 0.0f, 0.01f);  // adjust position
		glScalef(8.0f, 8.0f, 1.0f);     // upscale only the insignia
		DrawIAFInsignia();

		glPopMatrix();
	}
void DrawPlane1() {
	movingFunc();
	glPushMatrix();
	glScalef(0.025f / 2, 0.025f / 2, 0.0f);

	// Translate by x and y passed in from animation logic
	//glTranslatef((planeTopX + 10.0f) * 10, planeTopY*10, 0.0f);
	glTranslatef((planeTopX - 10.0f) * 10.0f, planeTopY * 10.0f, -3.0f);
	glRotatef(-planeTopAngle, 0.0f, 0.0f, 1.0f);

	//glTranslatef(-(planeMiddleX + 10.0f) * 10, 0.0f, 0.0f);
	//glTranslatef(translateX - posbX, 0.0f, -3.0f);


	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-2.75f, -4.8f, 0.0f);
	glVertex3f(-4.77f, -4.8f, 0.0f);
	glVertex3f(-4.77f, 4.8f, 0.0f);
	glVertex3f(-2.75f, 4.8f, 0.0f);

	glEnd();


	glColor3f(70.0f / 256.0f, 130.0f / 256.0f, 180.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-5.5f, 1.0f, 0.0f);
	glVertex3f(2.0f, 1.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, -1.0f, 0.0f);
	glVertex3f(-5.5f, -1.0f, 0.0f);
	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-2.75f, -4.5f, 0.0f);
	glVertex3f(-0.75f, -5.3f, 0.0f);
	glVertex3f(-4.77f, -5.0f, 0.0f);
	glVertex3f(-4.77f, -4.5f, 0.0f);

	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-4.77f, 4.5f, 0.0f);
	glVertex3f(-2.75f, 4.5f, 0.0f);
	glVertex3f(-0.8f, 5.3f, 0.0f);
	glVertex3f(-4.77f, 5.0f, 0.0f);
	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_POLYGON);
	glVertex3f(-5.5f, 0.71f, 0.0f);
	glVertex3f(-5.5f, -0.71f, 0.0f);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(-9.0f, -0.71f, 0.0f);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(-12.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(-9.0f, 0.71f, 0.0f);
	glEnd();

	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-9.0f, 0.71f, 0.0f);
	glVertex3f(-9.5f, 1.0f, 0.0f);
	glVertex3f(-9.5f, 3.2f, 0.0f);
	glVertex3f(-8.0f, 3.1f, 0.0f);
	//glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-5.6f, 0.71f, 0.0f);
	glEnd();

	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-9.0f, -0.71f, 0.0f);
	glVertex3f(-9.5f, -1.0f, 0.0f);
	glVertex3f(-9.5f, -3.2f, 0.0f);
	glVertex3f(-8.0f, -3.1f, 0.0f);
	//glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-5.6f, -0.71f, 0.0f);
	glEnd();
	glTranslatef(-4.2f, 0.0f, 0.01f);  // adjust position
	glScalef(8.0f, 8.0f, 1.0f);     // upscale only the insignia
	DrawIAFInsignia();

	glPopMatrix();
}
void DrawPlane2() {
	movingFunc();
	glPushMatrix();
	glScalef(0.025f / 2, 0.025f / 2, 0.0f);
	//glTranslatef(planeBottomX, planeBottomY, 0.0f);
	glTranslatef((planeBottomX - 10.0f) * 10.0f, -planeBottomY * 10.0f, -3.0f);
	glRotatef(planeTopAngle, 0.0f, 0.0f, 1.0f);

	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-2.75f, -4.8f, 0.0f);
	glVertex3f(-4.77f, -4.8f, 0.0f);
	glVertex3f(-4.77f, 4.8f, 0.0f);
	glVertex3f(-2.75f, 4.8f, 0.0f);

	glEnd();

	glColor3f(70.0f / 256.0f, 130.0f / 256.0f, 180.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-5.5f, 1.0f, 0.0f);
	glVertex3f(2.0f, 1.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, -1.0f, 0.0f);
	glVertex3f(-5.5f, -1.0f, 0.0f);
	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-2.75f, -4.5f, 0.0f);
	glVertex3f(-0.75f, -5.3f, 0.0f);
	glVertex3f(-4.77f, -5.0f, 0.0f);
	glVertex3f(-4.77f, -4.5f, 0.0f);

	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-4.77f, 4.5f, 0.0f);
	glVertex3f(-2.75f, 4.5f, 0.0f);
	glVertex3f(-0.8f, 5.3f, 0.0f);
	glVertex3f(-4.77f, 5.0f, 0.0f);
	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_POLYGON);
	glVertex3f(-5.5f, 0.71f, 0.0f);
	glVertex3f(-5.5f, -0.71f, 0.0f);
	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(-9.0f, -0.71f, 0.0f);
	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(-12.0f, 0.0f, 0.0f);
	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(-9.0f, 0.71f, 0.0f);
	glEnd();

	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-9.0f, 0.71f, 0.0f);
	glVertex3f(-9.5f, 1.0f, 0.0f);
	glVertex3f(-9.5f, 3.2f, 0.0f);
	glVertex3f(-8.0f, 3.1f, 0.0f);
	//glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-5.6f, 0.71f, 0.0f);
	glEnd();

	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-9.0f, -0.71f, 0.0f);
	glVertex3f(-9.5f, -1.0f, 0.0f);
	glVertex3f(-9.5f, -3.2f, 0.0f);
	glVertex3f(-8.0f, -3.1f, 0.0f);
	//glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-5.6f, -0.71f, 0.0f);
	glEnd();
	glTranslatef(-4.2f, 0.0f, 0.01f);  
	glScalef(8.0f, 8.0f, 1.0f);     
	DrawIAFInsignia();

	glPopMatrix();
}


void display() {
	// Clear the color buffer.
	glClear(GL_COLOR_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);

	glColor3f(0.5f, 0.5f, 0.5f); // Grey color
	// translate triangle backwords by z
	glTranslatef(0.0f, 0.0f, -3.0f);

	glPushMatrix();

	//set matrix to model view mode
	glMatrixMode(GL_MODELVIEW);

	//set it to identity matrix
	glLoadIdentity();

	LetterB();
	LetterH();
	LetterA();
	LetterR();
	LetterA1(-2.1f - translateX);
	LetterT(-2.0f - translateX);

	DrawPlane();
	DrawPlane1();
	DrawPlane2();

	glPopMatrix();

	SwapBuffers(ghdc);
}



void update(void)
{
	// code
	angle = angle + 2.0f;

	if (angle >= 360.0f)
	{
		angle = angle - 360.0f;
	}
}

void uninitialize(void)
{
	// function declaration
	void toggleFullsSreen(void);
	// code
	// user is exiting in full screen then restore full screen in normal
	if (gbFullScreen == TRUE)
	{
		toggleFullScreen();
		gbFullScreen = FALSE;
	}

	// Make hdc as current context by releasing rending context as current contex
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	// delete the rendering context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	// release the DC
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
	//close the file
	if (gpFile != NULL)
	{
		fprintf(gpFile, "Program terminated successfully\n");
		fclose(gpFile);
		gpFile = NULL;
	}
}
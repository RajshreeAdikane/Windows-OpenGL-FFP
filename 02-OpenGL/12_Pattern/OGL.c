// Win32 headers 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// OpenGL Related Header Files
#include <gl/GL.h> // visual studio 

#include <gl/GLU.h>

// Custom header files
#include "OGL.h"

// OpenGL related libraries
#pragma comment(lib, "opengl32.lib") //give linker the link file for import
#pragma comment(lib, "GLU32.lib")

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
	glClearColor(0.01f, 0.01f, 0.01f, 1.0f); // state fuc

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
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.01f);

}

void drawPattern_One(void) {
	glPointSize(5.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	for (float y = 0.6f; y >= -0.6f; y -= 0.4f) {
		for (float x = -0.6f; x <= 0.6f; x += 0.4f) {
			glVertex2f(x, y);
		}
	}
	glEnd();
}

void drawPattern_Two(void) {
	float startX = -0.6f;
	float startY = 0.6f;
	float step = 0.4f;

	glColor3f(1.0f, 1.0f, 1.0f); 
	glBegin(GL_LINES);
	for (float y = startY; y > -0.6f; y -= step) {
		for (float x = startX; x < 0.6f; x += step) {
			// Vertical line 
			glVertex2f(x, y);
			glVertex2f(x, y - step);

			// Diagonal line 
			glVertex2f(x, y - step);
			glVertex2f(x + step, y);

			// Horizontal line 
			glVertex2f(x, y);
			glVertex2f(x + step, y);
		}
	}
	glEnd();
}

void drawPattern_Three(void) {
	float startX = -0.6f;
	float startY = 0.6f;
	float step = 0.4f;

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);

	// Vertical lines
	for (int i = 0; i <= 3; ++i) {
		float x = startX + i * step;
		glVertex2f(x, startY);     
		glVertex2f(x, startY - 3 * step);
	}

	// Horizontal lines 
	for (int i = 0; i <= 3; ++i) {
		float y = startY - i * step;
		glVertex2f(startX, y);        
		glVertex2f(startX + 3 * step, y); 
	}

	glEnd();
}

void drawPattern_Four(void) {
	float startX = -0.6f;
	float startY = 0.6f;
	float step = 0.4f;

	glColor3f(1.0f, 1.0f, 1.0f); 
	glBegin(GL_LINES);

	glBegin(GL_LINES);

	// Vertical lines 
	for (int i = 0; i <= 3; ++i) {
		float x = startX + i * step;
		glVertex2f(x, startY);         
		glVertex2f(x, startY - 3 * step); 
	}

	// Horizontal lines
	for (int i = 0; i <= 3; ++i) {
		float y = startY - i * step;
		glVertex2f(startX, y);         
		glVertex2f(startX + 3 * step, y); 
	}
	for (float y = startY; y > -0.6f; y -= step) {
		for (float x = startX; x < 0.6f; x += step) {
			
			glVertex2f(x, y - step);
			glVertex2f(x + step, y);
		}
	}

	glEnd();

}

void drawPattern_Five() {
	float startX = -0.6f;
	float startY = 0.6f;
	float width = 1.2f; 
	float step = 0.2f;

	glColor3f(1.0f, 1.0f, 1.0f); 

	glBegin(GL_LINES);

	// Draw square boundary
	glVertex2f(startX, startY);      
	glVertex2f(startX + width, startY);          
	glVertex2f(startX + width, startY);     
	glVertex2f(startX + width, startY - width);
	glVertex2f(startX + width, startY - width); 
	glVertex2f(startX, startY - width);         
	glVertex2f(startX, startY - width);      
	glVertex2f(startX, startY);              

	// Diagonal rays from top-left to bottom edge 
	for (float x = startX + 0.4f; x <= startX + width; x += 0.4f) {
		glVertex2f(startX, startY);  
		glVertex2f(x, startY - width); 
	}

	// Diagonal rays from top-left to right edge 
	for (float y = startY - 0.4f; y >= startY - width; y -= 0.4f) {
		glVertex2f(startX, startY);    
		glVertex2f(startX + width, y); 
	}

	glEnd();

}

void drawPattern_Six(void) {
	float startX = -0.6f;
	float startY = 0.6f;
	float step = 0.4f;

	// Drawing the grid lines
	glColor3f(1.0f, 1.0f, 1.0f); 
	glBegin(GL_LINES);

	// Vertical lines
	for (int i = 0; i <= 3; ++i) {
		float x = startX + i * step;
		glVertex2f(x, startY);          
		glVertex2f(x, startY - 3 * step); 
	}

	// Horizontal lines 
	for (int i = 0; i <= 3; ++i) {
		float y = startY - i * step;
		glVertex2f(startX, y);         
		glVertex2f(startX + 3 * step, y); 
	}

	glEnd();

	// Fill left vertical blocks (Red)
	glColor3f(1.0f, 0.01f, 0.01f); // Red
	glBegin(GL_QUADS);
	glVertex2f(startX + 0.01f, startY - 0.01f);                // Top-left
	glVertex2f(startX + step - 0.01f, startY - 0.01f);          // Top-right
	glVertex2f(startX + step - 0.01f, startY - step + 0.01f);    // Bottom-right
	glVertex2f(startX + 0.01f, startY - step + 0.01f);           // Bottom-left

	glVertex2f(startX + 0.01f, startY - step - 0.01f);          // Second row top-left
	glVertex2f(startX + step - 0.01f, startY - step - 0.01f);    // Second row top-right
	glVertex2f(startX + step - 0.01f, startY - 2 * step + 0.01f); // Second row bottom-right
	glVertex2f(startX + 0.01f, startY - 2 * step + 0.01f);       // Second row bottom-left

	glVertex2f(startX + 0.01f, startY - 2 * step - 0.01f);      // Third row top-left
	glVertex2f(startX + step - 0.01f, startY - 2 * step - 0.01f); // Third row top-right
	glVertex2f(startX + step - 0.01f, startY - 3 * step + 0.01f); // Third row bottom-right
	glVertex2f(startX + 0.01f, startY - 3 * step + 0.01f);       // Third row bottom-left
	glEnd();

	// Fill middle vertical blocks (Green)
	glColor3f(0.01f, 1.0f, 0.01f); // Green
	glBegin(GL_QUADS);
	glVertex2f(startX + step + 0.01f, startY - 0.01f);                // Top-left
	glVertex2f(startX + 2 * step - 0.01f, startY - 0.01f);             // Top-right
	glVertex2f(startX + 2 * step - 0.01f, startY - step + 0.01f);       // Bottom-right
	glVertex2f(startX + step + 0.01f, startY - step + 0.01f);           // Bottom-left

	glVertex2f(startX + step + 0.01f, startY - step - 0.01f);          // Second row top-left
	glVertex2f(startX + 2 * step - 0.01f, startY - step - 0.01f);       // Second row top-right
	glVertex2f(startX + 2 * step - 0.01f, startY - 2 * step + 0.01f);    // Second row bottom-right
	glVertex2f(startX + step + 0.01f, startY - 2 * step + 0.01f);       // Second row bottom-left

	glVertex2f(startX + step + 0.01f, startY - 2 * step - 0.01f);      // Third row top-left
	glVertex2f(startX + 2 * step - 0.01f, startY - 2 * step - 0.01f);   // Third row top-right
	glVertex2f(startX + 2 * step - 0.01f, startY - 3 * step + 0.01f);   // Third row bottom-right
	glVertex2f(startX + step + 0.01f, startY - 3 * step + 0.01f);      // Third row bottom-left
	glEnd();

	// Fill right vertical blocks (Blue)
	glColor3f(0.01f, 0.01f, 1.0f); // Blue
	glBegin(GL_QUADS);
	glVertex2f(startX + 2 * step + 0.01f, startY - 0.01f);                // Top-left
	glVertex2f(startX + 3 * step - 0.01f, startY - 0.01f);                 // Top-right
	glVertex2f(startX + 3 * step - 0.01f, startY - step + 0.01f);           // Bottom-right
	glVertex2f(startX + 2 * step + 0.01f, startY - step + 0.01f);           // Bottom-left

	glVertex2f(startX + 2 * step + 0.01f, startY - step - 0.01f);          // Second row top-left
	glVertex2f(startX + 3 * step - 0.01f, startY - step - 0.01f);           // Second row top-right
	glVertex2f(startX + 3 * step - 0.01f, startY - 2 * step + 0.01f);       // Second row bottom-right
	glVertex2f(startX + 2 * step + 0.01f, startY - 2 * step + 0.01f);       // Second row bottom-left

	glVertex2f(startX + 2 * step + 0.01f, startY - 2 * step - 0.01f);      // Third row top-left
	glVertex2f(startX + 3 * step - 0.01f, startY - 2 * step - 0.01f);       // Third row top-right
	glVertex2f(startX + 3 * step - 0.01f, startY - 3 * step + 0.01f);       // Third row bottom-right
	glVertex2f(startX + 2 * step + 0.01f, startY - 3 * step + 0.01f);       // Third row bottom-left
	glEnd();
}

void display(void)
{
	// Clear the screen with the current clear color (black)
	glClear(GL_COLOR_BUFFER_BIT);

	/* VIEWPORT SETUP */
	// Get the actual client area dimensions of our window
	// This works correctly in both windowed and fullscreen modes
	RECT windowRect;
	GetClientRect(ghwnd, &windowRect);
	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;

	// We want to divide our window into a 3x2 grid (6 cells total)
	const int columns = 3;
	const int rows = 2;

	// Calculate the width and height of each individual cell
	int cellWidth = windowWidth / columns;
	int cellHeight = windowHeight / rows;

	/* DRAW EACH PATTERN IN ITS OWN CELL */
	for (int patternIndex = 0; patternIndex < 6; patternIndex++)
	{
		// Calculate which column and row this pattern goes in
		int col = patternIndex % columns;  // 0,1,2,0,1,2
		int row = patternIndex / columns;  // 0,0,0,1,1,1

		// OpenGL uses bottom-left origin, so we need to flip the Y coordinate
		int viewportX = col * cellWidth;
		int viewportY = (rows - 1 - row) * cellHeight; // Flip Y axis

		// Set the drawing area for this specific pattern
		glViewport(viewportX, viewportY, cellWidth, cellHeight);

		/* SETUP COORDINATE SYSTEM FOR THIS CELL */
		// 1. Switch to projection matrix mode
		glMatrixMode(GL_PROJECTION);
		// 2. Reset to identity matrix (clear any previous transformations)
		glLoadIdentity();
		// 3. Set up a 2D orthographic projection (-1 to 1 in both axes)
		gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

		// Switch back to modelview matrix for actual drawing
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/* DRAW THE APPROPRIATE PATTERN */
		switch (patternIndex)
		{
		case 0:
			drawPattern_One();   
			break;
		case 1:
			drawPattern_Two();    
			break;
		case 2:
			drawPattern_Three();
			break;
		case 3:
			drawPattern_Four();   
			break;
		case 4:
			drawPattern_Five(); 
			break;
		case 5:
			drawPattern_Six();  
			break;
		}
	}

	//using double buffering 
	SwapBuffers(ghdc);
}

void update(void)
{
	// code
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

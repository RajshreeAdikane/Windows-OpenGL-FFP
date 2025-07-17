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

//Solar System related Variables
int year = 0;
int date = 0;
int moonAngle = 0;
float skyboxAngle = 0.0f;
GLUquadric* quadric = NULL;
GLfloat size = 50.0f;

//Texture related variables
GLuint background;
GLuint sun_texture;
GLuint earth_texture;
GLuint moon_texture;
GLuint mars_texture;
GLuint saturn_ring;
GLuint jupiter_texture;
GLuint saturn_texture;

//rotation varibales
GLfloat marsYear = 0.0f; // Mars revolution around Sun
GLfloat marsDay = 0.0f;  // Mars rotation on axis

GLfloat jupiterYear = 0.0f;
GLfloat saturnYear = 0.0f;
GLfloat jupiterDay = 0.0f;
GLfloat saturnDay = 0.0f;

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
	pfd.cDepthBits = 32;

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

	if (loadGLTexture(&background, MAKEINTRESOURCE(IDBITMAP_BACKGROUND)) == FALSE)
	{
		fprintf(gpFile, "load texture unsuccessful: SMILEY\n");
		return(-6);
	}
	if (loadGLTexture(&sun_texture, MAKEINTRESOURCE(IDBITMAP_SUN_TEXTURE)) == FALSE)
	
	{
		fprintf(gpFile, "load texture unsuccessful: SMILEY\n");
		return(-7);
	}
	if (loadGLTexture(&earth_texture, MAKEINTRESOURCE(IDBITMAP_EARTH_TEXTURE)) == FALSE)
	
	{
		fprintf(gpFile, "load texture unsuccessful: SMILEY\n");
		return(-8);
	}
	if (loadGLTexture(&moon_texture, MAKEINTRESOURCE(IDBITMAP_MOON_TEXTURE)) == FALSE)
	
	{
		fprintf(gpFile, "load texture unsuccessful: SMILEY\n");
		return(-9);
	}
	if (loadGLTexture(&mars_texture, MAKEINTRESOURCE(IDBITMAP_MARS_TEXTURE)) == FALSE)
	
	{
		fprintf(gpFile, "load texture unsuccessful: SMILEY\n");
		return(-10);
	}
	if (loadGLTexture(&saturn_ring, MAKEINTRESOURCE(IDBITMAP_SATURN_RINGS_TEXTURE)) == FALSE)
	
	{
		fprintf(gpFile, "load texture unsuccessful: SMILEY\n");
		return(-11);
	}
	if (loadGLTexture(&jupiter_texture, MAKEINTRESOURCE(IDBITMAP_JUPITER_TEXTURE)) == FALSE)
	
	{
		fprintf(gpFile, "load texture unsuccessful: SMILEY\n");
		return(-12);
	}
	if (loadGLTexture(&saturn_texture, MAKEINTRESOURCE(IDBITMAP_SATURN_TEXTURE)) == FALSE)
	
	{
		fprintf(gpFile, "load texture unsuccessful: SMILEY\n");
		return(-13);
	}
	
	//printGLInfo
	printGLInfo();

	// From here Onwords OpenGL code starts
	// Tell OpenGL to choose the color to clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // state fuc

	// Depth related code
	glShadeModel(GL_SMOOTH); // for smoothness
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); // glcleardepth madhlya 1.0 fragment value <=
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Initialize Quadric
	quadric = gluNewQuadric(); 
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricOrientation(quadric, GLU_INSIDE);

	//enable texture
	glEnable(GL_TEXTURE_2D); //cause our texture is 2D

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

BOOL loadGLTexture(GLuint* texture, TCHAR imageResourceID[])
{
	// variable declarations
	HBITMAP hBitmap = NULL;
	BITMAP bmp;
	BOOL bResult = FALSE;

	// Load the bitmap as an image
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (hBitmap)
	{
		bResult = TRUE;  // Set to TRUE initially, assuming successful loading

		// Get bitmap structure from the loaded bitmap image
		GetObject(hBitmap, sizeof(BITMAP), &bmp);

		// Generate OpenGL texture object
		glGenTextures(1, texture);

		// Bind the new texture to the texture object
		glBindTexture(GL_TEXTURE_2D, *texture);

		// Unpack the image into memory for faster loading
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  // Assuming RGBA format (4 bytes per pixel)

		// Set texture wrapping and filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  // Adding wrapping in T direction as well
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // When zooming in on the texture magnificaion
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  // For quality mipmaps minification

		// Load the image into OpenGL texture
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, bmp.bmWidth, bmp.bmHeight, GL_BGRA_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
		// for create texture give me informationx`

		// Generate mipmaps for better texture quality at varying distances
		//glGenerateMipmap(GL_TEXTURE_2D);

		// Unbind the texture after loading
		glBindTexture(GL_TEXTURE_2D, 0); // 0 means we telling OpenGl to do mipmap s 

		// Clean up the bitmap object
		DeleteObject(hBitmap);
		hBitmap = NULL;
	}

	return bResult;  // Return TRUE if the texture was successfully loaded, otherwise FALSE
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

void drawSaturnRings(float innerRadius, float outerRadius) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, saturn_ring);

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= 360; i += 10) {
		float angle = i * M_PI / 180.0f;
		float x = cos(angle);
		float y = sin(angle);

		glTexCoord2f((float)i / 360.0f, 0.0f);
		glVertex3f(x * innerRadius/4, y * innerRadius/4, 0.0f);

		glTexCoord2f((float)i / 360.0f, 1.0f);
		glVertex3f(x * outerRadius/12, y * outerRadius/12, 0.0f);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawOrbit(float radius)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float angle = i * 3.14159f / 180.0f;

		glVertex3f(radius * cos(angle), 0.0f, radius * sin(angle));
	}
	glEnd();
}

void display(void)
{
	// Clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set matrix mode before anything
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Setup camera
	gluLookAt(0.0, 4.0, 8.0,   // Eye
		0.0, 0.0, 0.0,   // Center
		0.0, 5.0, 0.0);  // Up

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, background);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef((GLfloat)skyboxAngle, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Correct pole 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	gluSphere(quadric, 8.0f,50, 50);   
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	//Sun
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sun_texture);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluSphere(quadric, 0.5f, 30, 30);

	glPopMatrix();

	// Earth
	glPushMatrix();
	// Earth orbit around Sun

	//orbit
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(0.7f);
	drawOrbit(1.5f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earth_texture);
	// around the sun
	glRotatef((GLfloat)year, 0.0f, 1.0f, 0.0f);
	glTranslatef(1.5f, 0.0f, 0.0f);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, moon_texture);
	glRotatef((GLfloat)moonAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.4f, 0.1f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluSphere(quadric, 0.1f, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//adjust polls of the earth
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earth_texture);
	// earth spin / rotatate around its own axis 
	glRotatef((GLfloat)date, 0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluSphere(quadric, 0.2f, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();
	

	// Mars
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(0.7f);
	drawOrbit(2.5f);
	// Mars revolves around Sun
	glRotatef((GLfloat)marsYear, 0.0f, 1.0f, 0.0f);
	glTranslatef(2.5f, 0.0f, 0.0f); 
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); 
	glRotatef((GLfloat)marsDay, 0.0f, 0.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mars_texture); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluSphere(quadric, 0.17f, 20, 20);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// jupiter
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(0.7f);
	drawOrbit(3.2f);
	glRotatef((GLfloat)jupiterYear, 0.0f, 1.0f, 0.0f);
	glTranslatef(3.2f, 0.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 1.0f); 
	glRotatef(3.1f, 0.0f, 0.0f, 1.0f);
	glRotatef((GLfloat)jupiterDay, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jupiter_texture);
	gluSphere(quadric, 0.12f, 50, 50);  
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// saturn
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(0.7f);
	drawOrbit(4.2f);
	glRotatef((GLfloat)saturnYear, 0.0f, 1.0f, 0.0f);
	glTranslatef(4.2f, 0.0f, 0.0f);
	glRotatef(-80.7f, 1.0f, 0.0f, 1.0f); 
	glRotatef((GLfloat)saturnDay, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, saturn_texture);
	gluQuadricTexture(quadric, GL_TRUE);
	gluSphere(quadric, 0.15f, 50, 50);  
	glDisable(GL_TEXTURE_2D);

	// Saturn rings
	glPushMatrix();
	drawSaturnRings(1.2f, 2.2f); 
	glPopMatrix();

	glPopMatrix();

	SwapBuffers(ghdc);
}



void update(void)
{
	// code
	// earth rotate around its oen axis
	if (date < 360) {
		date += 0.1; 
		if (date >= 360) date = 0; 
	}

	// Earth revolution around sun
	if (year < 360) {
		year += 1.0; 
		if (year >= 360) year = 0; 
	}

	// Moon's revolution 
	if (moonAngle < 360) {
		moonAngle += 2; 
		if (moonAngle >= 360) moonAngle = 0; 
	}

	//mars revolution around sun
	marsYear += 1.0f;
	if (marsYear >= 360.0f) marsYear = 0.0f;

	//mars rotate around its oen axis
	marsDay += 0.5f;
	if (marsDay >= 360.0f) marsDay = 0.0f;

	//jupiter revolution around sun
	jupiterYear += 1.2f;
	if (jupiterYear >= 360.0f) jupiterYear = 0.0f;

	//jupiter rotate around its oen axis
	jupiterDay  += 0.5f;
	if (jupiterDay >= 360.0f) jupiterDay = 0.0f;

	//saturn revolution around sun
	saturnYear += 0.8f;
	if (saturnYear >= 360.0f) saturnYear = 0.0f;

	// saturn rotate around its oen axis
	saturnDay += 1.0f;
	if (saturnDay >= 360.0f) saturnDay = 0.0f;

	//galexy starts rotating
	skyboxAngle += 0.05f;
	if (skyboxAngle >= 360.0f) skyboxAngle -= 360.0f;

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

if (quadric ) {
    gluDeleteQuadric(quadric);
    quadric = NULL;
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

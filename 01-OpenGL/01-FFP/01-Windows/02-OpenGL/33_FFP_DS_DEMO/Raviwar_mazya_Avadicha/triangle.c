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
#pragma comment(lib, "winmm.lib")

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// older GL headers
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif


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


BOOL isDelayStarted = FALSE;
BOOL hasSoundPlayed = FALSE;
DWORD startTime = 0;

//Texture related variables
GLuint textureID;
GLuint textureID2;
GLuint textureID3;
GLuint textureID4;
GLuint textureID5;
GLuint textureID6;
GLuint textureID7;
GLuint textureID8;
GLuint textureID9;
GLuint textureID10;
GLuint textureID11;
GLuint textureID12;
GLuint textureID13;
GLuint textureID14;
GLuint textureID15;
GLuint textureID16;
GLuint textureID17;
GLuint textureID18;
GLuint textureID19;
GLuint textureID20;
GLuint textureID21;
GLuint textureID22;
GLuint textureID23;
GLuint textureID24;
GLuint textureID25;
GLuint textureID26;
GLuint textureID27;
GLuint textureID28;
GLuint textureID29;
GLuint textureID30;
GLuint textureID31;
GLuint textureID32;
GLuint textureID33;
GLuint textureID34;
GLuint textureID35;
GLuint textureID36;
GLuint textureID37;
GLuint textureID38;
GLuint textureID39;
GLuint textureID40;
GLuint textureID41;
GLuint textureID42;
GLuint textureID43;

GLfloat pos1X = 0.0f;
GLfloat pos2X = 0.0f;
GLfloat pos3X = 0.0f;
GLfloat pos4X = 0.0f;
GLfloat pos5X = 0.0f;
GLfloat pos6X = -70.0f;

GLfloat speed = 0.043f;

BOOL isMoving1 = FALSE;
BOOL isMoving2 = FALSE;
BOOL isMoving3 = FALSE;
BOOL isMoving4 = FALSE;
BOOL isMoving5 = FALSE;
BOOL isMoving6 = FALSE;

BOOL showSceneOne = FALSE;
BOOL showHouse = FALSE;
BOOL sceneOneDone = FALSE;
BOOL showScene3 = FALSE;
BOOL showScene4 = FALSE;
BOOL showScene5 = FALSE;

GLfloat handAngle = 0.0f;
GLfloat legAngle = 0.0f;
BOOL handDirection = TRUE;
BOOL legDirection = TRUE;

GLfloat angleHead = 0.0f;
BOOL headDirection = TRUE;

// Rotation angles
GLfloat anglePyramid = 0.0f;
GLfloat angle= 0.0f;
GLfloat angleCube= 0.0f;
GLUquadric* quadric = NULL;

float tx = 0.0f, ty = 0.0f, tz = 0.0f;
float step1 = 0.2f;
float step = 0.5f;


float ez = 0.0f;
float cz = 0.0f;
float ex, ey, ez;
float cx, cy, cz;
float ux, uy, uz;

float rx = 0.0f, ry = 0.0f, rz = 0.0f;
float sx = 0.5, sy = 0.5, sz = 0.5;
float cameraStep = 0.8f;

DWORD startTimeObject1 = 0;
DWORD startTimeObject2 = 0;
DWORD startTimeObject3 = 0;
DWORD startTimeObject4 = 0;
DWORD startTimeObject5 = 0;
DWORD startTimeObject6 = 0;
BOOL ravivarobjStop = FALSE;


BOOL showObject1 = FALSE;
BOOL showObject2 = FALSE;
BOOL showObject3 = FALSE;
BOOL showObject4 = FALSE;
BOOL showObject5 = FALSE;
BOOL showObject6 = FALSE;
BOOL ravivarobj = FALSE;

float alpha = 0.5f;

BOOL showLogo = TRUE;
GLfloat logoAlpha = 1.0f;
BOOL isFadingOut = FALSE;
BOOL showNextImage = FALSE;
BOOL showThirdFourthImages = FALSE; 
DWORD nextImageStartTime = 0;
DWORD thirdFourthStartTime = 0; 
GLfloat nextImageZ = -40.0f;
GLfloat thirdImageX = -7.0f;
GLfloat fourthImageX = 7.0f; 

GLfloat allAlpha = 1.0f;  
BOOL fadeOutAll = FALSE;  
DWORD fadeStartTime = 0;


//camera zoomout

GLfloat cameraZoomZ = 0.0f;
GLfloat cameraRotationAngle = 0.0f;
GLfloat cameraRotateStep = 1.0f;
BOOL startZoomOut = FALSE;
BOOL startCameraRotate = FALSE;

BOOL isZoomOutDelayStarted = FALSE;
DWORD zoomOutDelayStartTime = 0;
const DWORD ZOOM_OUT_DELAY_MS = 3000;

//===============CURVE

#define SEGMENTS 100

typedef struct {
	GLfloat x, y, z;
	char name;
} Point;

Point controlPoints[] = {
	{ -6.0f,  -20.20, -70.0f, 'A'},  
	{ -7.0f,  6.5f,  10.99f, 'B' },   
	{ -5.29f, 19.0f,  61.0f, 'C' },   
	{ -4.6f,  80.8f,  54.7f, 'D' },
	{ -4.6f,  80.8f,  54.7f, 'D' }, 
	{ -4.6f,  83.0f,  58.0f, 'E' }, 
	{ -4.6f,  88.0f,  35.0f, 'F' }, 
	{ -4.6f,  92.0f,  20.0f, 'G' }  

};

Point controlPoints1[] = {
	{ -4.6f,  92.0f,  20.0f, 'A' },  
	{ -4.6f,  85.0f,  -10.0f, 'B' }
};




GLuint activeIndex = 0;
GLuint  controlPointsSize = 0;
GLfloat time = 0.0f;

float walkAngle = 0.0f;   // walking cycle
float walkSpeed = 2.0f;
float walkZ = 20.50f;
float walkStep = -0.05f;
BOOL walking = TRUE;
float stopZ = 40.0f;
float stopZScene4 = 40.0f;

BOOL scene5Initialized = FALSE;
GLfloat stopZScene5 = 35.0f;

int headFrames = 0;         
int maxHeadFrames = 1100;     

BOOL headShaking = TRUE;    
BOOL dancing = FALSE;      

static int pauseFrames = 0;

BOOL showScene6 = FALSE;
BOOL scene6Initialized = FALSE;
GLuint scene6Textures[6];
int currentImageIndex = 0;
float imageAlpha = 0.0f;
DWORD imageStartTime = 0;

DWORD fadeInDuration = 1000;  
DWORD holdDuration = 2000;   
DWORD fadeOutDuration = 1000; 


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

	//PlaySound(TEXT("sound.wav"), NULL, SND_FILENAME | SND_ASYNC);

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
		case VK_LEFT:
			ex += cameraStep;
			cx += cameraStep;
			break;
		case VK_RIGHT:
			ex -= cameraStep;
			cx -= cameraStep;
			break;
		case VK_UP:
			ey -= cameraStep;
			cy -= cameraStep;
			break;
		case VK_DOWN:
			ey += cameraStep;
			cy += cameraStep;
			break;
		case VK_TAB:
			activeIndex++;
			if (controlPointsSize == activeIndex)
			{
				activeIndex =0;
			}
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
		case 'a':
			tx -= step;
			break;
		case 'A':
			tx += step;
			break;
		case 's':
			ty -= step;
			break;
		case 'S':
			ty += step;
			break;
		case 'w':
			tz -= step;
			break;
		case 'W':
			tz += step;
			break;

		case 'z':
			ez -= cameraStep;
			cz -= cameraStep;
			break;
		case 'Z':
			ez += cameraStep;
			cz += cameraStep;
			break;

		case 'd':
			sx -= step;
			break;
		case 'D':
			sx += step;
			break;
		case 'b':
			sy -= step;
			break;
		case 'B':
			sy += step;
			break;
		case 'c':
			sz -= step;
			break;
		case 'C':
			sz += step;
			break;

		case 'i':
			angleCube += step;
			break;
		case 'I':
			angleCube -= step;
			break;
		case 'm':
			angle += step;
			break;
		case 'M':
			angle -= step;
			break;
		case 'r':  
			cameraRotationAngle -= cameraRotateStep;
			break;
		case 'R':  
			cameraRotationAngle += cameraRotateStep;
		case 'q':
			controlPoints[activeIndex].x += cameraStep;
			break;
		case 'Q':
			controlPoints[activeIndex].x -= cameraStep;
			break;
		case 't':
			controlPoints[activeIndex].y += cameraStep;
			break;
		case 'T':
			controlPoints[activeIndex].y -= cameraStep;
			break;
		case 'p':
			controlPoints[activeIndex].z += cameraStep;
			break;
		case 'P':
			controlPoints[activeIndex].z -= cameraStep;
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

	GLuint loadTexture(GLuint * texture, const char* filename);

	Point evaluate_points(GLfloat t);
	Point evaluate_points1(GLfloat t);

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);


	if (loadTexture(&textureID2, "tie1.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-7);
	}

	//if (loadTexture(&textureID, "wood.png") == 0) {
	//	fprintf(gpFile, "load texture unsuccessful for textureID2\n");
	//	return (-8);
	//}

	if (loadTexture(&textureID3, "office1.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-9);
	}

	if (loadTexture(&textureID4, "1.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-10);
	}
	if (loadTexture(&textureID5, "2.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-11);
	}

	if (loadTexture(&textureID6, "3.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-12);
	}

	if (loadTexture(&textureID7, "4.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-13);
	}

	if (loadTexture(&textureID8, "5.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-14);
	}

	if (loadTexture(&textureID9, "B5.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-15);
	}

	if (loadTexture(&textureID10, "B6.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-16);
	}

	if (loadTexture(&textureID11, "B7.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-17);
	}

	if (loadTexture(&textureID12, "B8.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-18);
	}

	if (loadTexture(&textureID13, "B9.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-19);
	}

	if (loadTexture(&textureID14, "road.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-20);
	}

	if (loadTexture(&textureID15, "road1.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-21);
	}

	if (loadTexture(&textureID16, "eve.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-22);
	}

	if (loadTexture(&textureID17, "sealing.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-23);
	}

	if (loadTexture(&textureID18, "window.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-24);
	}

	if (loadTexture(&textureID19, "window1.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-25);
	}

	if (loadTexture(&textureID20, "dore.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-26);
	}

	if (loadTexture(&textureID21, "compund.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-27);
	}

	if (loadTexture(&textureID22, "name.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-28);
	}

	if (loadTexture(&textureID23, "6.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-29);
	}

	if (loadTexture(&textureID24, "clouds.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-29);
	}
	if (loadTexture(&textureID25, "grass.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-30);
	}
	if (loadTexture(&textureID26, "thought.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-31);
	}
	if (loadTexture(&textureID27, "bedroom.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-32);
	}

	if (loadTexture(&textureID28, "day.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-33);
	}

	if (loadTexture(&textureID29, "night.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-34);
	}

	if (loadTexture(&textureID30, "bhar.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-35);
	}

	if (loadTexture(&textureID31, "logo.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-36);
	}

	if (loadTexture(&textureID32, "text.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-37);
	}
	if (loadTexture(&textureID33, "text1.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-38);
	}
	if (loadTexture(&textureID34, "text2.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-39);
	}
	if (loadTexture(&textureID35, "10.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-39);
	}
	if (loadTexture(&textureID36, "11.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-39);
	}
	if (loadTexture(&textureID37, "12.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-39);
	}
	if (loadTexture(&textureID38, "13.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-39);
	}
	if (loadTexture(&textureID39, "14.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-39);
	}
	if (loadTexture(&textureID40, "15.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-39);
	}
	if (loadTexture(&textureID41, "leaves1.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-39);
	}
	if (loadTexture(&textureID42, "trunk.png") == 0) {
		fprintf(gpFile, "load texture unsuccessful for textureID2\n");
		return (-39);
	}

	scene6Textures[0] = textureID35;
	scene6Textures[1] = textureID36;
	scene6Textures[2] = textureID37;
	scene6Textures[3] = textureID38;
	scene6Textures[4] = textureID39;
	scene6Textures[5] = textureID40;
	//if (loadTexture(&textureID39, "14.png") == 0) {
	//	fprintf(gpFile, "load texture unsuccessful for textureID2\n");
	//	return (-39);
	//}
	//if (loadTexture(&textureID40, "1.png") == 0) {
	//	fprintf(gpFile, "load texture unsuccessful for textureID2\n");
	//	return (-39);
	//}
	//if (loadTexture(&textureID34, "text2.png") == 0) {
	//	fprintf(gpFile, "load texture unsuccessful for textureID2\n");
	//	return (-39);
	//}
	//enable texture
	glEnable(GL_TEXTURE_2D); //cause our texture is 2D
	//quadric = gluNewQuadric();

	//warm up resize
	resize(WIN_WIDTH, WIN_HEIGHT);

	if (showHouse) {
		Point obj = evaluate_points(time);
		ex = obj.x;
		ey = obj.y;
		ez = obj.z;
	}

	//static float t = 0.0f;
	if (showScene3) {
		Point obj = evaluate_points1(time);
		ex = obj.x;
		ey = obj.y;
		ez = obj.z;

	}

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

GLuint loadTexture(GLuint* texture, const char* filename) {
	int width, height, channels;
	//stbi_set_flip_vertically_on_load(1); // <--- Add this line
	unsigned char* imageData = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

	if (!imageData) {
		fprintf(gpFile, "Failed to load texture: %s\n", filename);
		return 0;
	}

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // repeat in X
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // repeat in Y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
	return *texture;
}

void resize(int width, int height)
{
	// code
	// if height by accident is less than 0 make it 1
	if (height <= 0)
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
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);


}

void cube(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz, GLfloat r, GLfloat g, GLfloat b)
{

	//glLoadIdentity();
	glTranslatef(tx, ty, tz);
	glRotatef(angle, rx, 0.0f, 0.0f);
	glScalef(sx, sy, sz);
	glColor3f(r, g, b);

	// Rotate the cube around x-axis
	/*glRotatef(angle, rx, 0.0f, 0.0f);*/
	/*glRotatef(angle, 0.0f, ry, 0.0f);
	glRotatef(angle, 1.0f, 0.0f, rz);*/

	//glRotatef(angleCube, 1.0f, 0.0f, 0.0f);


	//glBindTexture(GL_TEXTURE_2D, textureID);
	//glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	// Front face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);   // Top-right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top-left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom-left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom-right

	// Back face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);   // Top-right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top-left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom-left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom-right

	// Right face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);   // Top-front
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top-back
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // Bottom-back
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom-front

	// Left face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);   // Top-front
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top-back
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom-back
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom-front

	// Top face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);   // Front-right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Front-left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Back-left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Back-right

	// Bottom face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);   // Front-right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Front-left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Back-left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Back-right

	glEnd();

	//glBindTexture(GL_TEXTURE_2D, 0);
}

void pyramid(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz)
{
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glRotatef(angle, rx, ry, rz);
	glScalef(sx, sy, sz);

	glBegin(GL_TRIANGLES);

	// Apex is now at the bottom because Y is inverted in your view
	// Swap 1.0f ↔ -1.0f from the usual coordinates

	// Front face
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, -1.0f, 0.0f); // Apex
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // Base-left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // Base-right

	// Right face
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	// Back face
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	// Left face
	glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	glEnd();

	glPopMatrix();
}

void sphere(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat sx, GLfloat sy, GLfloat sz, GLfloat r, GLfloat g, GLfloat b)
{
	glPushMatrix();

	glTranslatef(tx, ty, tz);
	glScalef(sx, sy, sz);

	// Disable texturing to ensure solid color
	glDisable(GL_TEXTURE_2D);

	// Set skin color
	glColor3f(r,g,b);

	gluQuadricTexture(quadric, GL_FALSE); // Also disable texture on quadric
	gluSphere(quadric, 1.0f, 30, 30);

	glPopMatrix();
}

void sphere1(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat sx, GLfloat sy, GLfloat sz, GLuint texture)
{
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glScalef(sx, sy, sz);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Make sure quadric is initialized
	// quadric = gluNewQuadric(); // initialize once in setup
	gluQuadricTexture(quadric, GL_TRUE); // enable texture on quadric

	gluSphere(quadric, 1.0f, 30, 30); // radius 1, 30 slices, 30 stacks

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void drawPlane(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz, GLuint texture)
{
	glPushMatrix();

	glTranslatef(tx, ty, tz);
	glRotatef(angle, rx, ry, rz);
	glScalef(sx, sy, sz);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.0f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.0f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.0f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.0f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void drawPlane1(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz, GLuint texture, float alpha)
{
	glPushMatrix();

	glTranslatef(tx, ty, tz);
	glRotatef(angle, rx, ry, rz);
	glScalef(sx, sy, sz);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	// use incoming alpha instead of forcing 1.0
	glColor4f(1.0f, 1.0f, 1.0f, alpha);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.0f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.0f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.0f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.0f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void cubeBuilding(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz, GLuint texture)
{

	glPushMatrix();

	glTranslatef(tx, ty, tz);
	glRotatef(angle, rx, ry, rz);
	glScalef(sx, sy, sz);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1.0f, 1.0f, 1.0f);

	//glLoadIdentity();
	//glTranslatef(tx, ty, tz);
	//glRotatef(angle, rx, 0.0f, 0.0f);
	//glScalef(sx, sy, sz);
	//glColor3f(r, g, b);

	// Rotate the cube around x-axis
	/*glRotatef(angle, rx, 0.0f, 0.0f);*/
	/*glRotatef(angle, 0.0f, ry, 0.0f);
	glRotatef(angle, 1.0f, 0.0f, rz);*/

	//glRotatef(angleCube, 1.0f, 0.0f, 0.0f);


	//glBindTexture(GL_TEXTURE_2D, textureID);
	//glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	// Front face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);   // Top-right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top-left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom-left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom-right

	// Back face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);   // Top-right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top-left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom-left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom-right

	// Right face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);   // Top-front
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top-back
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // Bottom-back
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom-front

	// Left face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);   // Top-front
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top-back
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom-back
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom-front

	// Top face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);   // Front-right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Front-left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // Back-left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Back-right

	// Bottom face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);   // Front-right
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Front-left
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // Back-left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Back-right

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void blenderLikeView()
{
	GLfloat gridSide = 40.0f;
	GLfloat gridStep = 1.0f;

	glPushMatrix();
	glTranslatef(0.0, 13.0f, -13.0f); // 13
	glScalef(2.0f, 2.0f, 2.0f);

	glBegin(GL_LINES);
	glColor3f(0.3f, 0.3f, 0.3f);
	for (float i = -gridSide; i <= gridSide; i += gridStep)
	{
		glVertex3f(i, 0.0f, -gridSide);
		glVertex3f(i, 0.0f, gridSide);

		glVertex3f(-gridSide, 0.0f, i);
		glVertex3f(gridSide, 0.0f, i);
	}
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.42f, 0.42f, 0.42f);
	for (float i = -gridSide; i <= gridSide; i += 5.0f)
	{
		glVertex3f(i, 0.0f, -gridSide);
		glVertex3f(i, 0.0f, gridSide);

		glVertex3f(-gridSide, 0.0f, i);
		glVertex3f(gridSide, 0.0f, i);
	}
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-gridSide, 0.0f, 0.0f);
	glVertex3f(gridSide, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -gridSide, 0.0f);
	glVertex3f(0.0f, gridSide, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -gridSide);
	glVertex3f(0.0f, 0.0f, gridSide);

	glEnd();
	glPopMatrix();

}

void drawSphereSkybox(float radius, GLuint textureID) {
	glPushMatrix();

	glDisable(GL_DEPTH_TEST);     // Always in background
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textureID);

	// Lighting enabled so texture responds to light
	glEnable(GL_LIGHTING);

	GLUquadric* quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);
	gluQuadricOrientation(quad, GLU_INSIDE);
	gluSphere(quad, radius, 60, 60);

	gluDeleteQuadric(quad);

	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
}

void setupNightLighting() {
	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Soft ambient light (dark blue tint for night)
	GLfloat ambientLight[] = { 0.05f, 0.05f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	// Moonlight (directional white-blue light)
	GLfloat lightColor[] = { 0.6f, 0.6f, 0.9f, 1.0f };
	GLfloat lightDir[] = { -0.2f, -1.0f, -0.3f, 0.0f }; // Directional (like moon)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightDir);

	// Slight material shine for reflective objects (glass/windows/stars)
	GLfloat mat_specular[] = { 0.8f, 0.8f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 50.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void buildings(void)
{

	//glPushMatrix();
	//drawSphereSkybox(200.0f, textureID16); // big enough to cover scene
	//glPopMatrix();


	glPushMatrix();
	//void tree(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz);
	//glPushMatrix();

	// Buildings
	glPushMatrix();
	cubeBuilding(0.0f, -1.50f, 1.00f, angle, rx, ry, rz, -11.0f, 12.0f, 11.0f, textureID9);
	glPopMatrix();

	glPushMatrix();
	cubeBuilding(21.0f, -6.0f, 4.0f, angle, rx, ry, rz, 9.0f, 16.0f, 10.0f, textureID10);
	glPopMatrix();

	glPushMatrix();
	cubeBuilding(-24.0f, -4.0f, -9.50f, angle, rx, ry, rz, 9.50f, 15.50f, 17.0f, textureID11);
	glPopMatrix();

	glPushMatrix();
	cubeBuilding(44.0f, -11.0f, -11.0f, angle, rx, ry, rz, 12.0f, 22.0f, 15.50f, textureID12);
	glPopMatrix();

	glPushMatrix();
	cubeBuilding(-48.0f, -8.0f, 0.0f, angle, rx, ry, rz, 13.50f, 21.0f, 0.50f, textureID13);
	glPopMatrix();

	// Planes/ground
	glPushMatrix();
	drawPlane(1.0f, 12.50f, 42.50f, 0, 0, 0, 0, 142.0f, 4.50f, 71.50f, textureID14);
	glPopMatrix();


	glPushMatrix();
	drawPlane(0.0f, 12.50f, -43.0f, 0, 0, 0, 0, 237.0f, 4.50f, 101.50f, textureID15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	drawPlane(1.0f, -19.0f, -38.50f, 0, 0, 0, 0, 237.0f, 2.0f, 101.50f, textureID16);
	glPopMatrix();

	// Tree - FIXED: Corrected parameters based on the declaration
	//glPushMatrix();
	//tree(-16.50f, 56.00f, 17.00f, 0.0f, 0.0f, 0.0f, 0.0f, 11.00f, 7.50f, -1.50f);
	//glPopMatrix();

	glPopMatrix(); // This matches the first glPushMatrix()
	//glPopMatrix();
}

void human(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz) 
{
	// Rotate the cube around x-axis
	/*glRotatef(angle, rx, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, ry, 0.0f);
	glRotatef(angle, 1.0f, 0.0f, rz);*/

	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glScalef(sx, sy, sz);
	glRotatef(angleCube, rx, ry, rz);
	// head
	glPushMatrix();
	glTranslatef(0.0f, -2.80f, 0.0f); // Base head position

	// Dancing effect
	//glTranslatef(0.0f, -sinf(angleHead) * 0.1f, 0.0f);   // Up-down motion
	//glRotatef(sinf(angleHead) * 15.0f, 0.0f, 0.0f, 1.0f); // Side tilt
	if (headShaking) {
		glRotatef(angleHead, 0.0f, 1.0f, 0.0f);  // Y axis → NO
	}
	if (dancing) {
		glTranslatef(0.0f, sinf(angleHead) * 0.2f, 0.0f);   // bounce
		glRotatef(sinf(angleHead * 2.0f) * 10.0f, 0.0f, 0.0f, 1.0f); // tilt side
	}
	// Face
	sphere(0.0f, 0.0f, 0.0f, 0.50f, 0.50f, 0.50f, 1.0f, 0.8f, 0.6f);

	// Right Ear
	sphere(0.50f, 0.0f, 0.0f, 0.10f, 0.10f, -0.10f, 1.0f, 0.8f, 0.6f);

	sphere(0.20f, 0.05f, 0.5f, 0.07f, 0.08f, 0.0f, 0.0f, 0.0f, 0.0f);

	// Left Ear
	sphere(-0.50f, 0.0f, 0.0f, 0.10f, 0.10f, -0.10f, 1.0f, 0.8f, 0.6f);

	sphere(-0.20f, 0.05f, 0.5f, 0.07f, 0.08f, 0.0f, 0.0f, 0.0f, 0.0f);

	// Hair
	sphere(0.0f, -0.20f, -0.20f, 0.50f, 0.50f, 0.70f, 0.0f, 0.0f, 0.0f);

	glPopMatrix();


	// BODY
	glPushMatrix();
	glTranslatef(0.0f, -1.4f, 0.0f);
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.90f, -0.90f, -0.30f, 0.1f, 0.1f, 0.1f); // body

	// RIGHT HAND (connected at shoulder)
	glPushMatrix();
	glTranslatef(0.85f, 0.2f, 0.0f);             // Move to right shoulder
	glRotatef(-60.0f, 0.0f, 0.0f, 1.0f);         // base rotation from shoulder
	glRotatef(-handAngle, 0.0f, 1.0f, 0.0f);     // waving animation
	glTranslatef(0.39590f, 0.26f, 0.0f);            // move arm pivot to center
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.30f, 0.30f, 0.1f, 0.1f, 0.1f);
	glPushMatrix();
	sphere(1.3f, 0.0f, 0.2f, 0.38f, 1.0f, -1.0f, 1.0f, 0.8f, 0.6f); //palm
	//glPopMatrix();


	// LEFT HAND (connected at shoulder)
	glPushMatrix();
	glTranslatef(-0.85f, 0.2f, 0.0f);            // Move to left shoulder
	glRotatef(60.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(-handAngle, 0.0f, 1.0f, 0.0f);    // opposite wave
	glTranslatef(-0.39590f, 0.26f, 0.0f);           // move arm pivot to center
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.30f, 0.30f, 0.1f, 0.1f, 0.1f);
	glPushMatrix();
	sphere(-1.3f, 0.0f, 0.2f, 0.38f, 1.0f, -1.0f, 1.0f, 0.8f, 0.6f); //palm
	glPopMatrix(); // END BODY


	// SHIRT-TIE
	glPushMatrix();
	drawPlane(0.0f, -1.53f, 0.35f, -90.0f, 1.0f, 0.0f, 0.0f, 0.90f, 0.90f, 1.50f, textureID2);
	glPopMatrix();


	//glPopMatrix();

	glPushMatrix();
	glTranslatef(0.40f, 0.40f, 0.0f);
	glRotatef(legAngle, 1.0f, 0.0f, 0.0f);
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.30f, 1.05f, 0.30f, 0.1f, 0.1f, 0.1f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.40f, 0.40f, 0.0f);
	glRotatef(-legAngle, 1.0f, 0.0f, 0.0f);
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.30f, 1.05f, 0.30f, 0.1f, 0.1f, 0.1f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(legAngle, 1.0f, 0.0f, 0.0f);
	sphere(0.40f, 1.60f, 0.20f, 0.30f, -0.30f, 0.70f, 0.545f, 0.271f, 0.074f); //shoe left

	glPushMatrix();
	glRotatef(-legAngle, 1.0f, 0.0f, 0.0f);
	sphere(-0.40f, 1.60f, 0.20f, 0.30f, -0.30f, 0.70f, 0.545f, 0.271f, 0.074f);  //shoe right
	glPopMatrix();

	glPopMatrix();
}

void human1(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz)
{
	// Rotate the cube around x-axis
	/*glRotatef(angle, rx, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, ry, 0.0f);
	glRotatef(angle, 1.0f, 0.0f, rz);*/
	glPushMatrix();
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	glScalef(sx, sy, sz);
	glRotatef(angleCube, rx, ry, rz);
	// head
	glPushMatrix();
	glTranslatef(0.0f, -3.0f, 0.0f); // Base head position

	// Dancing effect
	//glTranslatef(0.0f, -sinf(angleHead) * 0.1f, 0.0f);   // Up-down motion
	//glRotatef(sinf(angleHead) * 15.0f, 0.0f, 0.0f, 1.0f); // Side tilt
	if (headShaking) {
		glRotatef(angleHead, 0.0f, 1.0f, 0.0f);  // Y axis → NO
	}
	if (dancing) {
		glTranslatef(0.0f, sinf(angleHead) * 0.2f, 0.0f);   // bounce
		glRotatef(sinf(angleHead * 2.0f) * 10.0f, 0.0f, 0.0f, 1.0f); // tilt side
	}
	// Face
	sphere(0.0f, 0.0f, 0.0f, 0.50f, 0.50f, 0.50f, 1.0f, 0.8f, 0.6f);

	// Right Ear
	sphere(0.50f, 0.0f, 0.0f, 0.10f, 0.10f, -0.10f, 1.0f, 0.8f, 0.6f);

	sphere(0.20f, 0.05f, 0.5f, 0.07f, 0.08f, 0.0f, 0.0f, 0.0f, 0.0f);

	// Left Ear
	sphere(-0.50f, 0.0f, 0.0f, 0.10f, 0.10f, -0.10f, 1.0f, 0.8f, 0.6f);

	sphere(-0.20f, 0.05f, 0.5f, 0.07f, 0.08f, 0.0f, 0.0f, 0.0f, 0.0f);

	// Hair
	sphere(0.0f, -0.20f, -0.20f, 0.50f, 0.50f, 0.70f, 0.0f, 0.0f, 0.0f);
	sphere(0.0f, -0.20f, -0.20f, 0.50f, 0.50f, 0.70f, 0.0f, 0.0f, 0.0f);

	glPopMatrix();


	// BODY
	glPushMatrix();
	glTranslatef(0.0f, -1.4f, 0.0f); 0.75f, -1.0f, -0.25f,
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.90f, -1.10f, -0.32f, 0.2745f, 0.5098f, 0.758823f); // body

	// RIGHT HAND (connected at shoulder)
	glPushMatrix();
	glTranslatef(0.85f, 0.2f, 0.0f);             // Move to right shoulder
	glRotatef(-60.0f, 0.0f, 0.0f, 1.0f);         // base rotation from shoulder
	glRotatef(-handAngle, 0.0f, 1.0f, 0.0f);     // waving animation
	glTranslatef(0.39590f, 0.26f, 0.0f);            // move arm pivot to center
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.30f, 0.30f, 0.2745f, 0.5098f, 0.758823f);
	glPushMatrix();
	sphere(1.3f, 0.0f, 0.2f, 0.38f, 1.0f, -1.0f, 1.0f, 0.8f, 0.6f); //palm
	//glPopMatrix();


	// LEFT HAND (connected at shoulder)
	glPushMatrix();
	glTranslatef(-0.85f, 0.2f, 0.0f);            // Move to left shoulder
	glRotatef(60.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(-handAngle, 0.0f, 1.0f, 0.0f);    // opposite wave
	glTranslatef(-0.39590f, 0.26f, 0.0f);           // move arm pivot to center
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.30f, 0.30f, 0.2745f, 0.5098f, 0.758823f);
	glPushMatrix();
	sphere(-1.3f, 0.0f, 0.2f, 0.38f, 1.0f, -1.0f, 1.0f, 0.8f, 0.6f); //palm
	glPopMatrix(); // END BODY


	//// SHIRT-TIE
	//glPushMatrix();
	//drawPlane(0.0f, -1.53f, 0.35f, -90.0f, 1.0f, 0.0f, 0.0f, 0.90f, 0.90f, 1.50f, textureID2);
	//glPopMatrix();


	//glPopMatrix();

	glPushMatrix();
	glTranslatef(0.40f, 0.40f, 0.0f);
	glRotatef(legAngle, 1.0f, 0.0f, 0.0f);
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.30f, 1.05f, 0.30f, 0.1f, 0.1f, 0.1f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.40f, 0.40f, 0.0f);
	glRotatef(-legAngle, 1.0f, 0.0f, 0.0f);
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.30f, 1.05f, 0.30f, 0.1f, 0.1f, 0.1f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(legAngle, 1.0f, 0.0f, 0.0f);
	sphere(0.40f, 1.60f, 0.20f, 0.30f, -0.30f, 0.70f, 0.545f, 0.271f, 0.074f); //shoe left

	glPushMatrix();
	glRotatef(-legAngle, 1.0f, 0.0f, 0.0f);
	sphere(-0.40f, 1.60f, 0.20f, 0.30f, -0.30f, 0.70f, 0.545f, 0.271f, 0.074f);  //shoe right
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}

void human2(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz)
{
	glPushMatrix();
	glTranslatef(tx	, ty, tz);
	glScalef(sx, sy, sz);
	glRotatef(angleCube, rx, ry, rz);

	// HEAD
	glPushMatrix();
	glTranslatef(0.0f, -2.80f, 0.0f); // Base head position

	// Dancing effect
	if (headShaking) {
		glRotatef(angleHead, 0.0f, 1.0f, 0.0f);  // Y axis → NO
	}
	if (dancing) {
		glTranslatef(0.0f, sinf(angleHead) * 0.2f, 0.0f);   // bounce
		glRotatef(sinf(angleHead * 2.0f) * 10.0f, 0.0f, 0.0f, 1.0f); // tilt side
	}

	// Face - lighter skin tone
	sphere(0.0f, 0.0f, 0.0f, 0.50f, 0.50f, 0.50f, 1.0f, 0.9f, 0.8f);

	// Ears - smaller and more delicate
	sphere(0.45f, 0.0f, 0.0f, 0.08f, 0.08f, -0.08f, 1.0f, 0.9f, 0.8f); // Right Ear
	sphere(-0.45f, 0.0f, 0.0f, 0.08f, 0.08f, -0.08f, 1.0f, 0.9f, 0.8f); // Left Ear

	// Eyes
	sphere(0.20f, 0.05f, 0.5f, 0.07f, 0.05f, 0.0f, 0.3f, 0.2f, 0.1f); // Left Eye White
	sphere(-0.20f, 0.05f, 0.5f, 0.07f, 0.05f, 0.0f, 0.3f, 0.2f, 0.1f); // Left Eye White
	//sphere(-0.18f, 0.08f, 0.41f, 0.02f, 0.02f, 0.02f, 0.0f, 0.0f, 0.0f);

	// Lips - pink color
	//sphere(0.0f, -0.15f, 0.45f, 0.15f, 0.05f, 0.05f, 1.0f, 0.4f, 0.4f);

	// Hair - long hair style
	sphere(0.0f, 0.20f, -0.20f, 0.50f, 0.60f, 0.40f, 0.3f, 0.2f, 0.1f); // Main hair
	sphere(0.0f, -0.40f, -0.15f, 0.50f, 0.40f, 0.60f, 0.3f, 0.2f, 0.1f); // Back hair
	sphere(0.47f, 0.07f, -0.05f, 0.25f, 0.90f, 0.40f, 0.3f, 0.2f, 0.1f); // Right side hair
	sphere(-0.47f, 0.07f, -0.05f, 0.25f, 0.90f, 0.40f, 0.3f, 0.2f, 0.1f); // Left side hair

	glPopMatrix();

	// BODY - more feminine shape
	glPushMatrix();
	glTranslatef(0.0f, -1.4f, 0.0f);

	// Torso - hourglass shape
	cube(0.0f, 0.15f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.75f, -1.0f, -0.25f, 0.8f, 0.4f, 0.7f); // Pink dress

	// RIGHT ARM
	glPushMatrix();
	glTranslatef(0.75f, 0.15f, 0.0f);             // Move to right shoulder
	glRotatef(-55.0f, 0.0f, 0.0f, 1.0f);         // base rotation
	glRotatef(-handAngle, 0.0f, 1.0f, 0.0f);     // waving animation
	glTranslatef(0.35f, 0.22f, 0.0f);            // move arm pivot to center
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.90f, 0.25f, 0.25f, 1.0f, 0.9f, 0.8f); // Slimmer arm
	sphere(1.2f, 0.0f, 0.15f, 0.32f, 0.90f, -0.90f, 1.0f, 0.9f, 0.8f); // Hand
	glPopMatrix();

	// LEFT ARM
	glPushMatrix();
	glTranslatef(-0.75f, 0.15f, 0.0f);            // Move to left shoulder
	glRotatef(55.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(-handAngle, 0.0f, 1.0f, 0.0f);    // opposite wave
	glTranslatef(-0.35f, 0.22f, 0.0f);           // move arm pivot to center
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.90f, 0.25f, 0.25f, 1.0f, 0.9f, 0.8f); // Slimmer arm
	sphere(-1.2f, 0.0f, 0.15f, 0.32f, 0.90f, -0.90f, 1.0f, 0.9f, 0.8f); // Hand
	glPopMatrix();

	// DRESS DETAILS - Waist line
	//cube(0.0f, -0.30f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.80f, 0.10f, 0.30f, 0.9f, 0.6f, 0.9f);

	//// Skirt part
	//glPushMatrix();
	//glTranslatef(0.0f, 1.0f, 0.0f);
	//cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.85f, 0.40f, 0.35f, 0.8f, 0.4f, 0.7f);
	//glPopMatrix(); // END SKIRT

	glPopMatrix(); // END BODY

	// LEGS - Separate from body to avoid transformation issues
	glPushMatrix();
	glTranslatef(0.0f + 0.30f, 0.58f, 0.0f); // Position relative to body
	glRotatef(legAngle, 1.0f, 0.0f, 0.0f);
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 0.95f, 0.25f, 0.6f, 0.4f, 0.8f); // Right leg
	sphere(0.0f, 0.95f, 0.15f, 0.25f, 0.25f, 0.25f, 0.8f, 0.6f, 0.9f); // Right shoe
	glPopMatrix(); // END RIGHT LEG

	glPushMatrix();
	glTranslatef(- 0.30f, 0.58f, 0.0f); // Position relative to body
	glRotatef(-legAngle, 1.0f, 0.0f, 0.0f);
	cube(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.25f, 0.95f, 0.25f, 0.6f, 0.4f, 0.8f); // Left leg
	sphere(0.0f, 0.95f, 0.15f, 0.25f, 0.25f, 0.25f, 0.8f, 0.6f, 0.9f); // Left shoe
	glPopMatrix(); // END LEFT LEG

	glPopMatrix(); // END HUMAN
}

void house(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz)
{
	glPushMatrix();
	glTranslatef(tx, ty, tz);
	//glRotatef(angleCube, rx, ry, rz);

	void tree(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz);

	glPushMatrix();


	glPushMatrix();
	glPushMatrix();
	glRotatef(-70.0f, 0.0f, 0.0f, 1.0f);
	cubeBuilding(-32.3f, 16.50f, 0.0f, 0, 0, 0, 0, 0.30f, 5.00f, 11.0f, textureID17);
	glPopMatrix();


	glPushMatrix();
	glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
	cubeBuilding(32.3f, 16.50f, 0.0f, 0, 0, 0, 0, 0.30f, 5.00f, 11.0f, textureID17);
	glPopMatrix();

	glPushMatrix();
	glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
	cube(34.0f, 16.3f, 0.0f, 0, 0, 0, 0, 1.50f, 5.0f, 10.50f, 1.000000f, 0.9921569f, 0.8156863f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-70.0f, 0.0f, 0.0f, 1.0f);
	cube(-34.0f, 16.3f, 0.0f, 0, 0, 0, 0, 1.50f, 5.0f, 10.50f, 1.000000f, 0.9921569f, 0.8156863f);
	glPopMatrix();

	//glPushMatrix();
	glPushMatrix();
	cube(0.0f, 41.50f, 0.0f, 0, 0, 0, 0, 9.0f, 3.8f, 9.0f, 1.000000f, 0.9921569f, 0.8156863f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-40.0f, 1.0f, 0.0f, 0.0f);
	cubeBuilding(0.3f, 21.50f, 32.5f, 0, 0, 0, 0, -5.50f, 0.0f, -0.8f, textureID17);//window upside shelter
	glPopMatrix();

	glPushMatrix();
	cubeBuilding(-1.5f, 39.50f, 10.0f, 0, 0, 0, 0, 3.50f, 1.50f + 0.50f, 0.3f + 0.50f, textureID18);// window
	glPopMatrix();

	glPushMatrix();
	cubeBuilding(-1.5f + 5.50f, 39.50f, 10.0f, 0, 0, 0, 0, 3.50f - 1.50f, 1.50f + 0.50f, 0.3f + 0.50f, textureID19); //window1
	glPopMatrix();
	//glPopMatrix();

	glPopMatrix();


	// Group transformation for all objects
	glPushMatrix();
	glTranslatef(-2.50f + 5.0f, -10.0f + 1.50f, -4.0f);
	glScalef(1.5f - 0.20f, 1.5f, 1.5f);

	// First object
	glPushMatrix();
	glRotatef(-40.0f, 1.0f, 0.0f, 0.0f);
	cubeBuilding(0.3f, 21.50f, 32.5f, 0, 0, 0, 0, -5.50f, 0.0f, -0.8f, textureID17); // window upside shelter
	glPopMatrix();

	// Second object
	glPushMatrix();
	cubeBuilding(-1.5f, 39.50f, 10.0f, 0, 0, 0, 0, 3.50f, 2.0f, 0.8f, textureID18); // window
	glPopMatrix();

	// Third object
	glPushMatrix();
	cubeBuilding(4.0f, 39.50f, 10.0f, 0, 0, 0, 0, 2.0f, 2.0f, 0.8f, textureID19); // window1
	glPopMatrix();


	glPopMatrix(); // End group transform



	glPushMatrix();

	glTranslatef(-2.50f, -10.0f, -4.0f);
	// Apply scaling to the entire structure
	glScalef(1.5f, 1.5f, 1.5f); // increase size by 50%

	// Your original drawing code
	glPushMatrix();
	glRotatef(-70.0f, 0.0f, 0.0f, 1.0f);
	cubeBuilding(-32.3f, 16.50f, 0.0f, 0, 0, 0, 0, 0.30f, 5.00f, 11.0f, textureID17);
	glPopMatrix();

	glPushMatrix();
	glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
	cubeBuilding(32.3f, 16.50f, 0.0f, 0, 0, 0, 0, 0.30f, 5.00f, 11.0f, textureID17);
	glPopMatrix();

	glPushMatrix();
	glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
	cube(34.0f, 16.3f, 0.0f, 0, 0, 0, 0, 1.50f, 5.0f, 10.50f, 1.000000f, 0.9921569f, 0.8156863f);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-70.0f, 0.0f, 0.0f, 1.0f);
	cube(-34.0f, 16.3f, 0.0f, 0, 0, 0, 0, 1.50f, 5.0f, 10.50f, 1.000000f, 0.9921569f, 0.8156863f);
	glPopMatrix();

	glPushMatrix();
	cube(0.0f, 41.50f, 0.0f, 0, 0, 0, 0, 9.0f, 3.8f, 9.0f, 1.000000f, 0.9921569f, 0.8156863f);
	glPopMatrix();

	glPopMatrix(); // end outer scale


	glPushMatrix();
	cubeBuilding(-11.0f + 1.50f, 52.00f, 12.0f, 0, 0, 0, 0, 4.0f + 1.50f, 5.0f, 0.0f, textureID20); // window1
	glPopMatrix();

	glPushMatrix();
	glRotatef(-40.0f, 1.0f, 0.0f, 0.0f);
	cubeBuilding(0.3f - 11.0f, 21.50f + 6.50f, 32.5f + 7.0f, 0, 0, 0, 0, -5.50f + 1.0, 0.0f, -0.8f - 0.50f, textureID17); // window upside shelter
	glPopMatrix();


	glPushMatrix();
	cubeBuilding(3.3f + 5.0f, 53.0f, 27.5f + 0.0f, 0, 0, 0, 0, -11.0f - 2.0f, 3.0f + 0.50f, 1.2f + 0.50f, textureID21); // compund
	glPopMatrix();


	// ---------- First cube ----------
	glPushMatrix();

	// Switch to texture matrix
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();  // <--- Reset texture matrix first

	// Scale texture horizontally (0.5 = stretch, >1 = repeat)
	glScalef(0.5f, 1.0f, 1.0f);

	// Back to modelview
	glMatrixMode(GL_MODELVIEW);

	// Draw cube
	cubeBuilding(-17.2f + 0.0f, 53.0f + 0.0f, 27.5f + 0.50f,
		0, 0, 0, 0,
		-9.50f + 4.50f + 0.50f, 3.0f + 0.50f, 1.2f + 0.50f,
		textureID21);

	// Restore texture matrix
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glPopMatrix();


	// ---------- Second cube ----------
	glPushMatrix();

	// Switch to texture matrix
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glScalef(2.0f, 1.0f, 1.0f); // repeat texture 2 times horizontally
	glMatrixMode(GL_MODELVIEW);

	//Draw cube
	cubeBuilding(3.3f - 20.50f + 12.0f + 1.0f + 3.50f, 53.0f + 0.0f, 27.5f - 61.50f + 7.0f + 4.0f,
		0, 0, 0, 0,
		-9.50f + 4.50f - 20.00f + 6.50f - 7.0f + 4.0f, 3.0f + 0.50f + 0.50f, 1.2f + 0.50f + 0.50f,
		textureID21);

	// Restore texture matrix
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glPopMatrix();


	// ---------- Second cube ----------
	glPushMatrix();

	// Switch to texture matrix
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glScalef(2.0f, 1.0f, 1.0f); // repeat texture 2 times horizontally
	glMatrixMode(GL_MODELVIEW);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	// Draw cube
	cubeBuilding(3.3f - 20.50f + 12.0f + 7.0f - 2.50f, 53.0f, 27.5f - 61.50f + 13.0f,
		0, 0, 0, 0,
		-9.50f + 4.50f - 22.50f + 0.50f, 3.0f + 0.50f, 1.2f + 0.50f,
		textureID21);

	// Restore texture matrix
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glPopMatrix();

	// ---------- Second cube ----------
	glPushMatrix();

	// Switch to texture matrix
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glScalef(2.0f, 1.0f, 1.0f); // repeat texture 2 times horizontally
	glMatrixMode(GL_MODELVIEW);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	// Draw cube
	cubeBuilding(3.3f - 20.50f + 12.0f + 7.0f - 2.0f + 2.50f, 53.0f + 13.0f - 13.0f, 27.5f - 61.50f + 13.0f + 8.0f - 6.50f,
		0, 0, 0, 0,
		-9.50f + 4.50f - 22.50f + 0.50f + 0.50f, 3.0f + 0.50f, 1.2f + 0.50f,
		textureID21);

	// Restore texture matrix
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glPopMatrix();

	glPushMatrix();
	tree(-9.00f + 10.0f - 1.50f + 0.50f + 6.50f, 55.50f + 1.00f - 0.50f, 30.00f - 7.0f + 3.50f, 0.0f, 0.0f, 0.0f, 0.0f, 9.50f + 3.0f - 7.0f, 7.0f - 3.0f + 0.50f + 0.50f, -2.50f + 0.50f + 0.50f + 0.50f);
	glPopMatrix();

	glPushMatrix();
	tree(-9.00f + 17.50f + 8.50f - 2.50f, 55.50f + 1.50f - 1.0f, 25.50f + 0.50f - 3.0f - 0.50f, 0.0f, 0.0f, 0.0f, 0.0f, 9.50f - 2.50f - 2.0f, 7.0f + 0.50f + 2.0f + 0.0f, -2.50f + 1.0f + 3.0f);
	glPopMatrix();

	glPushMatrix();
	tree(-9.00f + 10.0f - 17.50f+0.50f, 55.50f - 3.0f, 25.50f - 8.50f + 8.0f, 0.0f, 0.0f, 0.0f, 0.0f, 9.50f + 1.50f - 7.0f, 7.0f + 0.50f - 1.50f, -2.50f + 1.0f + 1.0f);
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();
}

void letters(void)
{
	if (isMoving1 || (showObject1 && pos1X < 4.0f)) {
		// Moving textureID4 (first object)
		glPushMatrix();
		glTranslatef(pos1X, -6.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(rz, 0.0f, 0.0f, 1.0f);
		glScalef(3.50f, 0.50f, 5.50f);
		drawPlane(0, 0, 0, 0, 0, 0, 0, 1, 1, 1, textureID4);
		glPopMatrix();
	}

	if (isMoving2 || (showObject2 && pos2X > -4.0f)) {
		// Moving textureID5
		glPushMatrix();
		glTranslatef(pos2X, -7.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(rz, 0.0f, 0.0f, 1.0f);
		glScalef(3.50f, 0.50f, 5.50f);
		drawPlane(0, 0, 0, 0, 0, 0, 0, 1, 1, 1, textureID5);
		glPopMatrix();
	}

	if (isMoving3 || (showObject3 && pos3X < 4.0f)) {
		glPushMatrix();
		glTranslatef(pos3X, -6.0f, 0.0f);  // Same pos2X, same time
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(rz, 0.0f, 0.0f, 1.0f);
		glScalef(3.50f, 0.50f, 5.50f);
		drawPlane(0, 0, 0, 0, 0, 0, 0, 1, 1, 1, textureID6);
		glPopMatrix();
	}

	if (isMoving4 || (showObject4 && pos4X > -4.0f)) {
		glPushMatrix();
		glTranslatef(pos4X, -6.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(rz, 0.0f, 0.0f, 1.0f);
		glScalef(3.50f, 0.50f, 5.50f);
		drawPlane(0, 0, 0, 0, 0, 0, 0, 1, 1, 1, textureID7);
		glPopMatrix();
	}

	if (isMoving5 || (showObject5 && pos5X < 4.0f)) {
		glPushMatrix();
		glTranslatef(pos5X, -5.0f, 0.0f);  // use pos5X instead of pos4X
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(rz, 0.0f, 0.0f, 1.0f);
		glScalef(3.50f, 0.50f, 5.50f);
		drawPlane(0, 0, 0, 0, 0, 0, 0, 1, 1, 1, textureID23);
		glPopMatrix();
	}

	if (ravivarobj || startZoomOut) {
		glPushMatrix();
		glTranslatef(pos6X+tx, 0+ty, 5.0f+30);
		glRotatef(85.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(rz, 0.0f, 0.0f, 1.0f);
		glScalef(36.0f+0.50f, 4.0f+0.50f, 34.0f+5.50f);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		drawPlane(0, 0, 0, 0, 0, 0, 0, 1, 1, 1, textureID22);
		glPopMatrix();
	}


}

void updateDance() {
	// Animate hand
	handAngle += handDirection ? 1.0f : -1.0f;
	if (handAngle >= 30.0f) {
		handAngle = 30.0f;
		handDirection = FALSE;
	}
	else if (handAngle <= -30.0f) {
		handAngle = -30.0f;
		handDirection = TRUE;
	}

	// Animate leg
	legAngle += legDirection ? 0.5f : -0.5f;
	if (legAngle >= 15.0f) {
		legAngle = 15.0f;
		legDirection = FALSE;
	}
	else if (legAngle <= -15.0f) {
		legAngle = -15.0f;
		legDirection = TRUE;
	}
	//if (headDirection)
	//{
	//	angleHead += 1.0f;
	//	if (angleHead >= 15.0f) headDirection = FALSE;
	//}
	//else
	//{
	//	angleHead -= 1.0f;
	//	if (angleHead <= -15.0f) headDirection = TRUE;
	//}

	angleHead += 0.05f;
	if (angleHead > 2 * 3.14159f) angleHead = 0.0f;
}

void movingFunc(void) {
	static BOOL logoPhaseCompleted = FALSE;
	static DWORD logoStartTime = 0;
	static const DWORD logoDuration = 4000; // Show logo for 4 sec
	static const DWORD fadeDuration = 2000; // Fade-out duration = 2 sec

	DWORD currentTime = GetTickCount();

	// 1. LOGO FADE
	if (!logoPhaseCompleted) {
		showLogo = TRUE;
		showSceneOne = FALSE;

		if (logoStartTime == 0) {
			logoStartTime = currentTime;
		}

		DWORD elapsed = currentTime - logoStartTime;

		if (elapsed <= logoDuration) {
			logoAlpha = 1.0f; // fully visible
		}
		else if (elapsed <= logoDuration + fadeDuration) {
			float progress = (float)(elapsed - logoDuration) / fadeDuration;
			logoAlpha = 1.0f - progress; // 1 → 0 over 2 sec
		}
		else {
			logoAlpha = 0.0f;
			logoPhaseCompleted = TRUE;
			showLogo = FALSE;
			showNextImage = TRUE;
			nextImageStartTime = currentTime;
			//fprintf(gpFile, "Logo fade-out completed → next image starting\n");
		}
	}

	// 2. NEXT IMAGE
	if (showNextImage) {
		DWORD elapsedImageTime = currentTime - nextImageStartTime;
		DWORD moveDuration = 3000;

		if (elapsedImageTime <= moveDuration) {
			float progress = (float)elapsedImageTime / moveDuration;
			nextImageZ = -40.0f + progress * 33.0f;  // -40 → -7
		}
		else {
			nextImageZ = -7.0f;

			// Start third/fourth once next image is fixed
			if (!showThirdFourthImages) {
				showThirdFourthImages = TRUE;
				thirdFourthStartTime = currentTime;
				fprintf(gpFile, "3rd/4th started\n");
			}
		}
	}

	// 3. THIRD & FOURTH SLIDE
	if (showThirdFourthImages) {
		DWORD elapsedThirdFourthTime = currentTime - thirdFourthStartTime;
		DWORD moveDuration = 2000;

		if (elapsedThirdFourthTime <= moveDuration) {
			float progress = (float)elapsedThirdFourthTime / moveDuration;
			thirdImageX = -7.0f + progress * 7.0f;   // -7 → 0
			fourthImageX = 7.0f - progress * 7.0f;   //  7 → 0
		}
		else {
			thirdImageX = 0.0f;
			fourthImageX = 0.0f;

			// Start fading out all three images
			fadeOutAll = TRUE;
			fadeStartTime = currentTime;

			// Lock flags
			showNextImage = FALSE;
			showThirdFourthImages = FALSE;
		}
	}

	if (fadeOutAll) {
		DWORD elapsedFadeTime = currentTime - fadeStartTime;
		DWORD fadeDuration = 2000;

		if (elapsedFadeTime <= fadeDuration) {
			float progress = (float)elapsedFadeTime / fadeDuration;
			allAlpha = 1.0f - progress;  // 1 → 0
		}
		else {
			allAlpha = 0.0f;
			fadeOutAll = FALSE;
			showSceneOne = TRUE;
			startTime = currentTime;
			//fprintf(gpFile, "All images faded → Scene One start\n");
		}
	}




		// PHASE 2: SCENE ONE ANIMATION
		if (showSceneOne) {
			DWORD currentSceneTime = GetTickCount() - startTime;

			if (currentSceneTime >= 2050 && !hasSoundPlayed) {
				PlaySound(TEXT("ravivar3.wav"), NULL, SND_FILENAME | SND_ASYNC);
				hasSoundPlayed = TRUE;
				fprintf(gpFile, "Sound played at: %lu ms\n", currentSceneTime);
			}

			if (currentSceneTime >= 3000 && !isMoving1) {
				isMoving1 = TRUE;
				fprintf(gpFile, "Moving1 started at: %lu ms\n", currentSceneTime);
			}

			if (isMoving1) {
				showObject1 = TRUE;
				pos1X += speed;
				if (pos1X >= 4.0f) {
					pos1X = 4.0f;
					isMoving1 = FALSE;
					isMoving2 = TRUE;
					fprintf(gpFile, "Moving1 completed\n");
				}
			}

			if (isMoving2) {
				showObject2 = TRUE;
				pos2X -= speed;
				if (pos2X <= -4.0f) {
					pos2X = -4.0f;
					isMoving2 = FALSE;
					isMoving3 = TRUE;
					fprintf(gpFile, "Moving2 completed\n");
				}
			}

			if (isMoving3) {
				showObject3 = TRUE;
				pos3X += speed;
				if (pos3X >= 4.0f) {
					pos3X = 4.0f;
					isMoving3 = FALSE;
					isMoving4 = TRUE;
					fprintf(gpFile, "Moving3 completed\n");
				}
			}

			if (isMoving4) {
				showObject4 = TRUE;
				pos4X -= speed;
				if (pos4X <= -4.0f) {
					pos4X = -4.0f;
					isMoving4 = FALSE;
					isMoving5 = TRUE;
					fprintf(gpFile, "Moving4 completed\n");
				}
			}

			if (isMoving5) {
				showObject5 = TRUE;
				pos5X += speed;
				if (pos5X >= 4.0f) {
					pos5X = 4.0f;
					isMoving5 = FALSE;
					startZoomOut = TRUE;
					fprintf(gpFile, "Moving5 completed\n");
				}
			}

			if (startZoomOut) {
				cameraZoomZ += speed * 4;
				if (cameraZoomZ > 85.50f) {
					cameraZoomZ = 85.50f;
					startZoomOut = FALSE;
					ravivarobj = TRUE;
					fprintf(gpFile, "ZoomOut completed\n");
				}
			}

			if (ravivarobj) {
				showObject6 = TRUE;
				pos6X += speed * 4.5;
				if (pos6X >= 35.0f) {
					pos6X = 35.0f;
					ravivarobj = FALSE;
					showSceneOne = FALSE;
					showHouse = TRUE;
					fprintf(gpFile, "Scene One completed. Switching to House scene\n");
				}
			}
		}
}

void sceneOne()
{
	glPushMatrix();

	// --- Draw Skybox (stars) ---
	//glDisable(GL_LIGHTING);  // Stars shouldn’t be affected by light
	//drawSphereSkybox(150.0f, textureID16);
	//glEnable(GL_LIGHTING);

	// --- Setup Night Lighting ---
	//setupNightLighting();

	// --- Draw human ---
	glPushMatrix();
	human(0.0f, -5.0f, 0.0f, angleCube, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	glPopMatrix();

	// --- Draw plane/office ---
	glPushMatrix();
	drawPlane(0.0f, -6.0f, -3.0f, -90.0f, 1, ry, rz, 19.50f, 2.50f, 12.50f, textureID3);
	glPopMatrix();

	// --- Animated functions ---
	movingFunc();
	letters();

	// --- Buildings ---
	glPushMatrix();
	buildings();
	glPopMatrix();


	glPopMatrix();  // End of scene
}

void drawCylinder(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat sx, GLfloat sy, GLfloat sz, float radius, float height, int segments, GLfloat r, GLfloat g, GLfloat b) {
	float angle, x, z;

	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, textureID);

	// Set trunk color
	glColor3f(r, g, b);
	// Draw the side of the cylinder
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= segments; i++) {
		angle = 2.0f * 3.14159f * i / segments;
		x = radius * cos(angle);
		z = radius * sin(angle);

		float u = (float)i / segments; // texture wrap horizontally

		glNormal3f(cos(angle), 0.0f, sin(angle));
		glTexCoord2f(u, 1.0f); glVertex3f(x, height / 2, z);
		glTexCoord2f(u, 0.0f); glVertex3f(x, -height / 2, z);
	}
	glEnd();

	// Draw top cap
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, height / 2, 0.0f);
	for (int i = 0; i <= segments; i++) {
		angle = 2.0f * 3.14159f * i / segments;
		x = radius * cos(angle);
		z = radius * sin(angle);
		glTexCoord2f(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));
		glVertex3f(x, height / 2, z);
	}
	glEnd();

	// Draw bottom cap
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, -height / 2, 0.0f);
	for (int i = segments; i >= 0; i--) {
		angle = 2.0f * 3.14159f * i / segments;
		x = radius * cos(angle);
		z = radius * sin(angle);
		glTexCoord2f(0.5f + 0.5f * cos(angle), 0.5f + 0.5f * sin(angle));
		glVertex3f(x, -height / 2, z);
	}
	glEnd();

	//glBindTexture(GL_TEXTURE_2D, 0);
	//glDisable(GL_TEXTURE_2D);
}

void tree(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat angle, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat sx, GLfloat sy, GLfloat sz) {
	glPushMatrix();

	// Apply transformations in correct order
	glTranslatef(tx, ty - 0.3f, tz);   // ⬅ lowered tree slightly (ty - 0.3)
	//glRotatef(angle, rx, ry, rz);
	glRotatef(180, 1.0f, ry, rz);
	glScalef(sx, sy - 0.3f, sz);

	// Set material properties for better lighting
	GLfloat trunk_ambient[] = { 0.55f, 0.27f, 0.07f, 1.0f };
	GLfloat trunk_diffuse[] = { 0.35f, 0.17f, 0.02f, 1.0f };
	GLfloat leaves_ambient[] = { 0.0f, 0.4f, 0.0f, 1.0f };
	GLfloat leaves_diffuse[] = { 0.0f, 0.7f, 0.0f, 1.0f };

	// --- TRUNK (brown) ---
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);   // slightly lower
	glMaterialfv(GL_FRONT, GL_AMBIENT, trunk_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, trunk_diffuse);
	drawCylinder(0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.24f, 1.3f, 24,          // ⬅ wider trunk (radius 0.24, taller 1.3)
		0.55f, 0.27f, 0.07f);     // brown trunk
	glPopMatrix();

	// --- LEAVES (GREEN spheres) ---
	glMaterialfv(GL_FRONT, GL_AMBIENT, leaves_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, leaves_diffuse);

	// Main canopy structure - more natural arrangement
	sphere(0.0f, 1.6f, 0.0f, 0.65f, 0.65f, 0.65f, 0.0f, 0.6f, 0.0f);  // Top center

	// Middle layer
	sphere(0.4f, 1.3f, 0.3f, 0.55f, 0.55f, 0.55f, 0.0f, 0.7f, 0.0f);
	sphere(-0.4f, 1.3f, -0.2f, 0.55f, 0.55f, 0.55f, 0.0f, 0.65f, 0.0f);
	sphere(0.3f, 1.3f, -0.4f, 0.50f, 0.50f, 0.50f, 0.0f, 0.7f, 0.0f);
	sphere(-0.3f, 1.3f, 0.4f, 0.50f, 0.50f, 0.50f, 0.0f, 0.75f, 0.0f);

	// Lower layer
	sphere(0.6f, 1.0f, 0.1f, 0.45f, 0.45f, 0.45f, 0.0f, 0.8f, 0.0f);
	sphere(-0.6f, 1.0f, -0.1f, 0.45f, 0.45f, 0.45f, 0.0f, 0.75f, 0.0f);
	sphere(0.2f, 1.0f, 0.6f, 0.40f, 0.40f, 0.40f, 0.0f, 0.7f, 0.0f);
	sphere(-0.2f, 1.0f, -0.6f, 0.40f, 0.40f, 0.40f, 0.0f, 0.8f, 0.0f);

	// Fill spheres
	sphere(0.0f, 1.1f, 0.0f, 0.45f, 0.45f, 0.45f, 0.0f, 0.65f, 0.0f);
	sphere(0.5f, 1.2f, 0.0f, 0.35f, 0.35f, 0.35f, 0.0f, 0.7f, 0.0f);
	sphere(-0.5f, 1.2f, 0.0f, 0.35f, 0.35f, 0.35f, 0.0f, 0.75f, 0.0f);

	glPopMatrix();
}

int factorial(int val)  // formula = n *(n-1)*(n-2)*(n-
{
	int fact = 1;
	for (int i = 1; i <= val; ++i)
	{
		fact = fact * i;

	}
	return fact;
}

int binomialCoeff(int n, int i)
{
	int temp = factorial(n) / (factorial(i) * factorial(n - i));
	return temp;
}

Point evaluate_points(GLfloat t)
{
	Point obj = { 0.0f, 0.0f, 0.0f };
	int size = sizeof(controlPoints) / sizeof(Point);

	for (int i = 0; i < size; ++i) {
		int binoCoeff = binomialCoeff(size - 1, i);
		GLfloat basis = binoCoeff * pow(1 - t, size - 1 - i) * pow(t, i);

		obj.x += basis * controlPoints[i].x;
		obj.y += basis * controlPoints[i].y;
		obj.z += basis * controlPoints[i].z;
	}
	return obj;
}

Point evaluate_points1(GLfloat t)
{
	Point obj = { 0.0f, 0.0f, 0.0f };
	int size = sizeof(controlPoints1) / sizeof(Point);

	for (int i = 0; i < size; ++i) {
		int binoCoeff = binomialCoeff(size - 1, i);
		GLfloat basis = binoCoeff * pow(1 - t, size - 1 - i) * pow(t, i);

		obj.x += basis * controlPoints1[i].x;
		obj.y += basis * controlPoints1[i].y;
		obj.z += basis * controlPoints1[i].z;
	}
	return obj;
}

void drawCurve() {
	 //--- REMOVE CURVE LINE ---
	 glColor3f(1.0, 0.0, 0.0);
	 glBegin(GL_LINE_STRIP);
	 for (int i = 0; i <= SEGMENTS; ++i) {
	     GLfloat t = (GLfloat)i / SEGMENTS;
	     Point p = evaluate_points(t);
	     glVertex3f(p.x, p.y, p.z);
	 }
	 glEnd();

	// Draw control points
	int controlPointsSize = sizeof(controlPoints) / sizeof(Point);
	glPointSize(5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < controlPointsSize; ++i) {
		if (i != activeIndex)
			glVertex3f(controlPoints[i].x, controlPoints[i].y, controlPoints[i].z);
	}
	glEnd();

	// Highlight active control point
	glPointSize(7.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex3f(controlPoints[activeIndex].x,
		controlPoints[activeIndex].y,
		controlPoints[activeIndex].z);
	glEnd();
}

float getTimeSeconds() {
	static DWORD start = 0;
	if (start == 0) start = GetTickCount();
	return (GetTickCount() - start) / 1000.0f;
}

void drawTexturedQuad()
{
	//glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	//glPopMatrix();
}

void drawDayNightWindow(float tx, float ty, float tz, float sx, float sy, float sz, GLuint textureID28, GLuint textureID29)
{
	// Enable states
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Optional: avoid depth fighting between day/night quads
	//glDisable(GL_DEPTH_TEST);

	float duration = 16.0f; // slower fade (increase for even slower)
	float time = getTimeSeconds();
	float t = fmod(time / duration, 1.0f); // keeps looping 0→1
	if (t > 1.0f) t = 1.0f; // stop after transition

	// Sine fade (smooth, slower)
	float alpha = sinf(t * (M_PI / 2.0f));
	glPushMatrix();
	
	//glTranslatef(598.0f, -673.0f, 0.0f);
	//glTranslatef(tx, ty, tz);

		// Apply scale relative to its origin
		//glScalef(15.0f, 3.50f, 148.0f);
		//glScalef(sx, sy, sz);
	// --- Day quad ---
	glBindTexture(GL_TEXTURE_2D, textureID28);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f - alpha); // fades out
	drawTexturedQuad();

	// --- Night quad ---
	glBindTexture(GL_TEXTURE_2D, textureID29);
	glColor4f(1.0f, 1.0f, 1.0f, alpha); // fades in
	drawTexturedQuad();

	glPopMatrix();

	// Restore states
	//glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void display(void)
{
	char str[128] = { 0 };
	sprintf(str, "tx:%.2f, ty:%.2f,  tz:%.2f, sx:%.2f, sy:%.2f, sz:%.2f, angle:%.2f, rx:%.2f, ry:%.2f,rz:%.2f", tx, ty, tz, sx, sy, sz, angle, rx, ry, rz);
	//char str[1024] = { 0 };
	//sprintf(str, "%c[%f, %f, %f]",
	//	controlPoints[activeIndex].name,   // assuming name is a char in Point
	//	controlPoints[activeIndex].x,
	//	controlPoints[activeIndex].y,
	//	controlPoints[activeIndex].z);
	//printf("%s\n", str);

	//sprintf(str, "ex:%.2f, ey:%.2f, ez:%.2f, cx:%.2f, cy:%.2f, cz:%.2f, ux:%.2f, uy:%.2f, uz:%.2f",ex, ey, ez, cx, cy, cz, ux, uy, uz);

	//sprintf(str, "ez:%.2f, cz:%.2f", ez, cz);
	SetWindowText(ghwnd, str);
	// code
	// clear OpenGL buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Translate triangle backword by z
	// Set matrix to model view mode
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(0.0f + ex, -6.80f + ey, 8.50f + ez, 0.0f + cx, -6.80f + cy, -10.0f + cz, 0.0f + ux, -1.0f + uy, 0.0f + uz);
	/* gluLookAt(0.0f + ex, -6.80f + ey, 8.50f + ez + cameraZoomZ,
	0.0f + cx, -6.80f + cy, -10.0f + cz,
		0.0f + ux, -1.0f + uy, 0.0f + uz);*/

	float radians = cameraRotationAngle * M_PI / 180.0f;

	// Fixed camera position
	float eyeX = 0.0f + ex;
	float eyeY = -6.80f + ey;
	float eyeZ = 8.50f + ez + cameraZoomZ;

	// Initial target is looking down negative Z (standard OpenGL)
	float targetX = 0.0f + cx;
	float targetY = -6.80f + cy;
	float targetZ = -10.0f + cz;

	// Calculate initial direction vector from eye to target
	float dx = targetX - eyeX;
	float dy = targetY - eyeY;
	float dz = targetZ - eyeZ;

	// Rotate the direction vector around Y axis
	float rotatedX = dx * cosf(radians) - dz * sinf(radians);
	float rotatedZ = dx * sinf(radians) + dz * cosf(radians);

	// Calculate new target position based on rotated direction
	targetX = eyeX + rotatedX;
	targetZ = eyeZ + rotatedZ;

	// After rotation is complete, we want to look at positive Z
	if (!startCameraRotate && cameraRotationAngle <= -180.0f) {
		targetX = eyeX;
		targetZ = eyeZ + 1.0f;  // Look directly along positive Z axis
	}

	gluLookAt(
		eyeX, eyeY, eyeZ,
		targetX, targetY, targetZ,
		0.0f + ux, -1.0f + uy, 0.0f + uz
	);

	//gluLookAt(0.0f + ex, -6.80f, -1.20f, 0.0f + cx, -6.80f, -1.20f, 0.0f + ux, -1.0f + uy, 0.0f + uz);
	//glTranslatef(0.0f+tx, -1.0f+ty, -6.0f+tz);
	//blenderLikeView();

	if (showLogo) {
		movingFunc();
		// Logo drawing code (with fade)
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glColor4f(1.0f, 1.0f, 1.0f, logoAlpha);
		drawPlane1(0.0f, 2.5f, -7.0f, 0, 0, 0, 0, 11.0f, 9.5f, 14.5f, textureID31, logoAlpha);
		glPopMatrix();

		glDisable(GL_BLEND);
	}
	if (showNextImage || showThirdFourthImages || fadeOutAll) {
		movingFunc();
		// NEW: Draw the second image with Z translation
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

	//	// Use nextImageZ for the Z position (translates over time)
		drawPlane1(0.0f, 2.5f + nextImageZ, -9.50f, 0, 0, 0, 0, 11.0f, 9.5f, 14.5f, textureID32, allAlpha);

		glPopMatrix();

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glColor4f(1.0f, 1.0f, 1.0f, allAlpha);
		drawPlane1(thirdImageX, 2.5f, -5.0f - 1.70f, 0, 0, 0, 0, 11.0f - 2.50f, 9.5f, 14.5f - 5.0f, textureID33, allAlpha);
		glPopMatrix();

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glColor4f(1.0f, 1.0f, 1.0f, allAlpha);
		drawPlane1(fourthImageX, 2.5f, -5.0f - 0.70f, 0, 0, 0, 0, 11.0f - 2.50f, 9.5f, 14.5f - 5.0f, textureID34, allAlpha);
		glPopMatrix();

		glDisable(GL_BLEND);
	}

	else if (showSceneOne) {
		glPushMatrix();
		sceneOne();
		glPopMatrix();
	}

	else if (showHouse) {
		//drawCurve();

		glPushMatrix();                // Save world state
		glScalef(2.0f, 2.0f, 2.0f);          // Apply scale to the whole scene

		// House
		house(0.0f, -6.0f, -7.50f, angleCube, 0.0f, 1.0f, 0.0f,
			-0.50f, 0.50f, 0.50f);

		// First plane
		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		drawPlane(
			1.0f - 0.50f,
			-19.0f - 90.50f,
			-38.50f + 60.50f,
			0, 0, 0, 0,
			237.0f + 102.0f,
			2.0f + 0.50f,
			101.50f + 68.50f,
			textureID24
		);
		glPopMatrix();

		// Second plane
		glPushMatrix();
		drawPlane(
			1.0f - 0.50f + 0.50f + 10.0f,
			-19.0f - 114.50f + 134.0f + 43.0f + 8.50f,
			-38.50f + 60.50f + 23.0f - 67.50f,
			0, 0, 0, 0,
			237.0f + 102.0f - 292.0f + 24.0f + 104.50f,
			2.0f + 0.50f + 0.50f + 0.50f,
			101.50f + 68.50f - 139.5f + 100.50f,
			textureID25
		);
		glPopMatrix();

		glPushMatrix();
		glPushMatrix();
		glTranslatef(
			-10.50f + 9.50f,
			-5.0f + 56.50f + 0.1 * sinf(2 * walkAngle * M_PI / 180.0f) + 1.50f, // bounce
			walkZ + 1.15f                                                   // forward movement
		);

		human(0.0f, -5.0f, 0.0f, angleCube,
			0.0f, 1.0f, 0.0f,
			1.5f, 1.5f, 1.5f); // scaled a bit bigger
		glPopMatrix();

		glPopMatrix();

		glPushMatrix();
		glScalef(0.5f, 0.5, 0.5f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		drawPlane(-10.50f + 9.50f, walkZ + 2.0f + 40.0f, -5.0f + 56.50f + 0.1f + 1.50f + 33.0f, 0, 0, 0, 0, 1.0f + 4.0f - 0.50f - 1.50f + 1.0f + 1.0f + 3.50f, 1.0f + 0.50f + 0.50f + 0.50f + 1.0f + 1.50f, 1.0f + 14.0f - 1.50f - 8.0f + 1.0f + 3.0f, textureID26);
		glPopMatrix();

		glPopMatrix();                 // Restore world state
	}

	else if (showScene3)
	{
		//time = 0.0f;
		glPushMatrix();
		glTranslatef(0.0f - 15.50f, 100.0f + 14.0f, 0.0f - 60.0f);
		glScalef(1.50f, 1.50f, 0.50f);

		//Floor / environment
		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		drawPlane(
			-10.50f + 9.50f + 6.0f - 6.0f,
			1.0f - 3.50f - 190.0f + 20.0f,
			-5.0f + 56.50f + 0.1f + 1.50f - 11.50 + 44.50f - 211.0f + 120.0f - 8.0f,
			0, 0, 0, 0,
			1.0f + 4.0f - 0.50f - 1.50f + 1.0f + 169.00f + 130.0f - 17.0f,
			1.0f + 0.50f + 0.50f + 0.50f + 1.0f + 0.50f + 19.50f,
			1.0f + 14.0f - 1.50f - 8.0f + 96.50f - 53.0f + 118.00f - 9.0f,
			textureID27);
		glPopMatrix();

		// --- Cubes (walls, structure) ---
		glPushMatrix();
		//glTranslatef(tx, ty, tz);
		// ❌ removed glScalef(sx, sy, sz);   // <-- this was distorting bed

		// ---- Wall 1 ----
		glPushMatrix();
		cube(43.0f, 52.0f, -171.50f,
			0, 0, 0, 0,
			2.30f, 10.05f, 2.80f,
			0.1f, 0.1f, 0.1f);
		glPopMatrix();

		// ---- Wall 2 ----
		glPushMatrix();
		cube(43.0f, 52.0f, -171.50f + 62.50f,
			0, 0, 0, 0,
			2.30f, 10.05f, 2.80f,
			0.1f, 0.1f, 0.1f);
		glPopMatrix();

		// ---- Wall 3 ----
		glPushMatrix();
		cube(43.0f - 107.0f, 52.0f, -171.50f,
			0, 0, 0, 0,
			2.30f, 10.05f, 2.80f,
			0.1f, 0.1f, 0.1f);
		glPopMatrix();

		// ---- Wall 4 ----
		glPushMatrix();
		cube(43.0f - 107.0f, 52.0f, -171.50f + 62.50f,
			0, 0, 0, 0,
			2.30f, 10.05f, 2.80f,
			0.1f, 0.1f, 0.1f);
		glPopMatrix();

		// ---- Wall Panel ----
		glPushMatrix();
		cube(43.0f - 107.0f + 56.0f, 52.0f - 6.0f, -171.50f + 62.50f - 18.50f,
			0, 0, 0, 0,
			53.3f, 3.05f, 40.5f,
			0.1f, 0.1f, 0.1f);
		glPopMatrix();

		// ---- Darker Wall Panel ----
		glPushMatrix();
		cube(43.0f - 107.0f + 56.0f, 52.0f - 12.0f, -171.50f + 62.50f - 18.50f,
			0, 0, 0, 0,
			53.3f, 3.05f, 40.5f,
			0.3f, 0.3f, 0.3f);
		glPopMatrix();

		// ---- Back Wall ----
		glPushMatrix();
		cube(43.0f - 107.0f + 55.50f, 52.0f - 26.0f, -171.50f + 62.50f - 63.50f,
			0, 0, 0, 0,
			53.8f, 11.05f, 3.5f,
			0.1f, 0.1f, 0.1f);
		glPopMatrix();

		// ---- Human ----
		glPushMatrix();
		glRotatef(70.0f, 1.0f, 0.0f, 0.0f);
		human(-7.0f, -90.0f, -72.0f, angleCube,
			0.0f, 1.0f, 0.0f, 1.0f + 11.50f, 1.0f + 14.0f, 1.0f + 3.0f); glPopMatrix();
		// ---- Bed ----
		glPushMatrix();
		cube(43.0f - 107.0f + 55.50f,
			52.0f - 26.0f + 2.0f,
			-171.50f + 62.50f - 63.50f + 70.0f,
			0, 0, 0, 0,
			34.0f,   // sx
			6.0f,    // sy (bed height)
			29.0f,   // sz
			0.034747f, 0.595162f, 0.546279f);
		glPopMatrix();

		// ---- Pillow ----
		glPushMatrix();
		cube(43.0f - 107.0f + 55.50f,
			52.0f - 26.0f + 2.0f,
			-171.50f + 62.50f - 63.50f + 10.50f,
			0, 0, 0, 0,
			30.0f,   // sx
			11.0f,   // sy (thicker pillow)
			5.0f,    // sz
			0.9f, 0.9f, 0.8f);
		glPopMatrix();

		glPopMatrix(); // end root walls group


		//Window with day-night transition
		glPushMatrix();

		// Move to object position (center of window)
		glTranslatef(19.50f, -33.55f, 0.0f);

		// Apply scale relative to its origin
		glScalef(34.50f, 30.50f, -168.00f);

		// Now draw window at *its local coordinates* (e.g. starting at 0,0,0 or centered properly)
		drawDayNightWindow(0.0f, 0.0f, 0.0f,
			34.5f, 329.0f, 36.5f,   // local coordinates (example)
			textureID28, textureID29);

		glPopMatrix();


		glPopMatrix(); // end Scene3 root
	}


	else if (showScene4)
	{
		glPushMatrix();
		glTranslatef(tx, 90.50f + 7.50f - 19.50f + ty, 10.0f + tz);
		buildings();
		glPopMatrix();

		glPushMatrix();
		glPushMatrix();
		glTranslatef(
			-10.50f + 9.50f - 2.50f + 0.0f + 0.0f,
			-5.0f + 56.50f + 0.1f * sinf(2 * walkAngle * M_PI / 180.0f) + 1.50f + 44.50f + 0.50f - 7.50f, // bounce
			walkZ + 1.0f + 9.0f + 35.0f - 15.0f - 3                                      // forward movement
		);

		human(0.0f, -5.0f, 0.0f, angleCube,
			0.0f, 1.0f, 0.0f,
			1.5f, 1.5f, 1.5f); // scaled a bit bigger
		glPopMatrix();

		glPushMatrix();
		glTranslatef(
			-10.50f + 9.50f - 2.50f + 0.0f + 0.0f + tx,  // Simplified: -10.50f + 9.50f - 2.50f + 0.0f + 0.0f = -3.50f
			-5.0f + 56.50f + 0.1f + 1.50f + 44.50f + 0.50f - 7.50f - 13.0f,  // Simplified: -5.0f + 56.50f = 51.50f
			walkZ + 30.0f - 3 + tz  // Simplified: 1.0f + 9.0f + 35.0f - 15.0f = 30.0f
		);
		glScalef(0.5f + sx, 0.5f + sy, 0.5f + sz);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		drawPlane(0.0f, -5.0f, 0.0f, 0, 0, 0, 0, 1.0f + 4.0f - 0.50f - 1.50f + 1.0f + 1.0f, 1.0f + 0.50f + 0.50f + 0.50f + 1.0f, 1.0f + 14.0f - 1.50f - 8.0f + 1.0f, textureID30);
		glPopMatrix();

		glPopMatrix();
	}


	else if (showScene5)
	{
		glPushMatrix();
		glTranslatef(0.0f, -10.0f, -27.0f);// Save world state
		glScalef(2.0f, 2.0f, 2.0f);
		// Second plane - simplified calculations

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		drawPlane(
			1.0f - 0.50f,
			-19.0f - 90.50f,
			-38.50f + 60.50f,
			0, 0, 0, 0,
			237.0f + 102.0f,
			2.0f + 0.50f,
			101.50f + 68.50f,
			textureID24
		);
		glPopMatrix();

		glPushMatrix();
		drawPlane(
			11.0f,       // 1.0f - 0.50f + 0.50f + 10.0f = 11.0f
			52.0f,       // -19.0f - 114.50f + 134.0f + 43.0f + 8.50f = 52.0f
			-22.0f,      // -38.50f + 60.50f + 23.0f - 67.50f = -22.0f
			0, 0, 0, 0,
			176.0f,      // 237.0f + 102.0f - 292.0f + 24.0f + 104.50f = 176.0f
			3.5f,        // 2.0f + 0.50f + 0.50f + 0.50f = 3.5f
			131.0f,      // 101.50f + 68.50f - 139.5f + 100.50f = 131.0f
			textureID25
		);
		glPopMatrix();

		float bounce = 0.1f * sinf(2.0f * walkAngle * M_PI / 180.0f);

		// Human 1
		glPushMatrix();
		glTranslatef(-1.0f, 53.0f + bounce - 4.0f, -3.0f+ walkZ);   // world position
		glScalef(1.5f, 1.5f, 1.5f);                          // scale if needed
		human1(0.0f, 0.0f, 0.0f, angleCube, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f);
		glPopMatrix();

		// Human 2
		glPushMatrix();
		glTranslatef(-5.0f, 53.0f + bounce - 3.50f, -3.0f + walkZ);   // different X and tiny Z offset
		glScalef(1.5f, 1.5f, 1.5f);
		human2(0.0f, 0.0f, 0.0f, angleCube, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f);
		glPopMatrix();

		// ---- Forest / Garden Trees ----

	// ---- Forest / Garden Trees ----

// Big trees (much bigger now)
		glPushMatrix(); tree(12.0f, 50.0f, -30.0f, 0, 0, 0, 0, 8.0f, 5.7f, 2.0f); glPopMatrix();
		glPushMatrix(); tree(-20.0f, 51.0f, -25.0f, 0, 0, 0, 0, 8.5f, 6.0f, 2.1f); glPopMatrix();
		glPushMatrix(); tree(15.0f, 52.0f, 15.0f, 0, 0, 0, 0, 7.8f, 5.5f, 1.9f); glPopMatrix();
		glPushMatrix(); tree(-22.0f, 52.0f, 20.0f, 0, 0, 0, 0, 8.2f, 5.7f, 2.0f); glPopMatrix();
		glPushMatrix(); tree(18.0f, 52.0f, 30.0f, 0, 0, 0, 0, 8.7f, 6.1f, 2.2f); glPopMatrix();

		// Medium trees
		glPushMatrix(); tree(5.0f, 50.0f, -40.0f, 0, 0, 0, 0, 5.5f, 4.5f, 1.5f); glPopMatrix();
		glPushMatrix(); tree(-25.0f, 53.0f, -35.0f, 0, 0, 0, 0, 5.8f, 4.5f, 1.6f); glPopMatrix();
		glPushMatrix(); tree(20.0f, 50.5f, -20.0f, 0, 0, 0, 0, 5.2f, 4.0f, 1.4f); glPopMatrix();
		glPushMatrix(); tree(-15.0f, 50.5f, -15.0f, 0, 0, 0, 0, 5.0f, 3.9f, 1.3f); glPopMatrix();

		// Small trees
		glPushMatrix(); tree(10.0f, 51.5f, -15.0f, 0, 0, 0, 0, 4.5f, 3.1f, 1.3f); glPopMatrix();
		glPushMatrix(); tree(-18.0f, 51.5f, 5.0f, 0, 0, 0, 0, 4.8f, 3.5f, 1.3f); glPopMatrix();
		glPushMatrix(); tree(8.0f, 51.0f, 30.0f, 0, 0, 0, 0, 4.5f, 3.4f, 1.2f); glPopMatrix();
		glPushMatrix(); tree(8.0f, 51.0f, 10.0f, 0, 0, 0, 0, 4.8f, 3.4f, 1.3f); glPopMatrix();



		glPopMatrix();                 // Restore world state
	}

	else if (showScene6) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		// Draw current image
		drawPlane1(
			11.0f - 8.50f ,       // 1.0f - 0.50f + 0.50f + 10.0f = 11.0f
			52.0f - 146.50f-0.50f,       // -19.0f - 114.50f + 134.0f + 43.0f + 8.50f = 52.0f
			-22.0f + 125.0f-22.50f,       // -38.50f + 60.50f + 23.0f - 67.50f = -22.0f
			0, 0, 0, 0,
			176.0f+sx,      // 237.0f + 102.0f - 292.0f + 24.0f + 104.50f = 176.0f
			3.5f+sy,        // 2.0f + 0.50f + 0.50f + 0.50f = 3.5f
			131.0f+sz,
			scene6Textures[currentImageIndex], imageAlpha
		);

		glPopMatrix();
		glDisable(GL_BLEND);
	}




	

	// swap the buffers
	SwapBuffers(ghdc);

}

void update(void)
{
	if (showHouse)
	{
		time += step1;
		if (time < SEGMENTS) {
			GLfloat t = (GLfloat)time / (GLfloat)SEGMENTS;

			Point obj = evaluate_points(t);
			ex = obj.x;
			ey = obj.y;
			ez = obj.z;

			// Look-ahead point
			Point ahead = evaluate_points(min(t + 0.01f, 1.0f));
			cx = ahead.x;
			cy = ahead.y;
			cz = ahead.z;
		}
		else if (walking) {
			walkAngle += walkSpeed;
			if (walkAngle > 360.0f) walkAngle -= 360.0f;

			legAngle = 30.0f * sinf(walkAngle * M_PI / 180.0f);
			handAngle = 20.0f * sinf((walkAngle + 90.0f) * M_PI / 180.0f);

			walkZ += fabs(walkStep);

			if (walkZ >= stopZ) {
				walking = FALSE;
				legAngle = 0.0f;
				handAngle = 0.0f;
				headShaking = TRUE; // Start head shaking after walking
			}
		}
		else if (headShaking) {
			if (headDirection) {
				angleHead += 1.0f;
				if (angleHead >= 15.0f) headDirection = FALSE;
			}
			else {
				angleHead -= 1.0f;
				if (angleHead <= -15.0f) headDirection = TRUE;
			}

			headFrames++;
			if (headFrames > maxHeadFrames) {
				headShaking = FALSE;
				dancing = TRUE;
				angleHead = 0.0f;
				headFrames = 0;
			}
		}
		else if (dancing) {
			angleHead += 0.1f;

			// store in global vars, not apply GL here
			float bounce = sinf(angleHead) * 0.05f;
			float tilt = sinf(angleHead * 2.0f) * 5.0f;

			headFrames++;
			if (headFrames >= 400) {
				dancing = FALSE;
				angleHead = 0.0f;
				bounce = 0.0f;
				tilt = 0.0f;
				time = 0.0f;

				showHouse = FALSE;
				showScene3 = TRUE;
			}
		}
	}
	else if (showScene3)
	{
		if (time < SEGMENTS) {
			time += step1 * 5.0f;
			GLfloat t = (GLfloat)time / (GLfloat)SEGMENTS;

			Point obj = evaluate_points1(t);
			ex = obj.x;
			ey = obj.y;
			ez = obj.z;

			Point ahead = evaluate_points1(min(t + 0.01f, 1.0f));
			cx = ahead.x;
			cy = ahead.y;
			cz = ahead.z;
		}
		else {
			if (pauseFrames < 500) {   // stop ~200 frames (~3 seconds at 60fps)
				pauseFrames++;
			}
			else {
				// continue to next scene or reset
				showScene3 = FALSE;
				showScene4 = TRUE;
				walking = TRUE;
				walkZ = 0.0f;
				walkAngle = 0.0f;
				pauseFrames = 0; // Reset for next use

				// Reset head shaking and dancing flags for Scene 4
				headShaking = FALSE;
				dancing = FALSE;
				headFrames = 0;
			}
		}
	}
	else if (showScene4)
	{
		if (walking) {
			walkAngle += walkSpeed;
			if (walkAngle > 360.0f) walkAngle -= 360.0f;

			legAngle = 30.0f * sinf(walkAngle * M_PI / 180.0f);
			handAngle = 20.0f * sinf((walkAngle + 90.0f) * M_PI / 180.0f);

			walkZ += fabs(walkStep);

			// Stop walking after reaching a certain distance in scene 4
			if (walkZ >= stopZScene4) {
				walking = FALSE;
				legAngle = 0.0f;
				handAngle = 0.0f;
				headShaking = TRUE; // Start head shaking after walking in Scene 4
			}
		}
		else if (headShaking) {
			if (headDirection) {
				angleHead += 1.0f;
				if (angleHead >= 15.0f) headDirection = FALSE;
			}
			else {
				angleHead -= 1.0f;
				if (angleHead <= -15.0f) headDirection = TRUE;
			}

			headFrames++;
			if (headFrames > maxHeadFrames/1.5) {
				headShaking = FALSE;
				dancing = TRUE;
				angleHead = 0.0f;
				headFrames = 0;
			}
		}
		else if (dancing) {
			angleHead += 0.1f;

			// store in global vars, not apply GL here
			float bounce = sinf(angleHead) * 0.05f;
			float tilt = sinf(angleHead * 2.0f) * 5.0f;

			headFrames++;
			if (headFrames >= 350) {
				dancing = FALSE;
				angleHead = 0.0f;
				bounce = 0.0f;
				tilt = 0.0f;
				time = 0.0f;

				// Scene 4 completes - you can add transition to another scene or end here
				showScene4 = FALSE;
				 showScene5 = TRUE; // Uncomment if you want to transition to another scene

				 walking = TRUE;
				 walkZ = 0.0f;
				 walkAngle = 0.0f;
				 headShaking = FALSE;
				 dancing = FALSE;
				 headFrames = 0;
			}
		}
	}
	else if (showScene5)
	{
		// Reset walking variables when Scene 5 starts
		if (!scene5Initialized) {
			walking = TRUE;
			walkZ = 0.0f;
			walkAngle = 0.0f;
			legAngle = 0.0f;
			handAngle = 0.0f;
			scene5Initialized = TRUE;
		}

		if (walking) {
			walkAngle += walkSpeed;
			if (walkAngle > 360.0f) walkAngle -= 360.0f;

			legAngle = 30.0f * sinf(walkAngle * M_PI / 180.0f);
			handAngle = 20.0f * sinf((walkAngle + 90.0f) * M_PI / 180.0f);

			walkZ += fabs(walkStep);

			if (walkZ >= stopZScene5) {  // Walking complete
				walking = FALSE;
				legAngle = 0.0f;
				handAngle = 0.0f;

				// Immediately go to Scene 6
				showScene5 = FALSE;
				scene5Initialized = FALSE;
				showScene6 = TRUE;
			}
		}

		// Remove dancing / headShaking entirely
		}

	else if (showScene6) {
			DWORD currentTime = GetTickCount();

			// Initialize Scene6 on first entry
			if (!scene6Initialized) {
				currentImageIndex = 0;   // start with first image
				imageAlpha = 0.0f;       // fade starts from 0
				imageStartTime = currentTime;
				scene6Initialized = TRUE;
			}

			DWORD elapsed = currentTime - imageStartTime;
			DWORD totalDuration = fadeInDuration + holdDuration + fadeOutDuration;

			if (elapsed <= fadeInDuration) {
				float progress = (float)elapsed / fadeInDuration;
				imageAlpha = progress;  // fade in
			}
			else if (elapsed <= fadeInDuration + holdDuration) {
				imageAlpha = 1.0f;     // hold
			}
			else if (elapsed <= totalDuration) {
				float progress = (float)(elapsed - (fadeInDuration + holdDuration)) / fadeOutDuration;
				imageAlpha = 1.0f - progress; // fade out
			}
			else {
				currentImageIndex++;
				if (currentImageIndex >= 6) {
				}
				else {
					imageStartTime = currentTime; // next image
					imageAlpha = 0.0f;
				}
			}
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
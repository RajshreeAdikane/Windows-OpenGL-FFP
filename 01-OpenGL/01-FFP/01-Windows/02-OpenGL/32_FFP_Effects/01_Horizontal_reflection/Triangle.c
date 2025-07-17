// Win32 headers 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

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

#define MAX_LIMITS_CUBE_TRANSLATE_X 8.0f
#define MIN_LIMITS_CUBE_TRANSLATE_X -8.0f

#define MAX_LIMITS_CUBE_TRANSLATE_Y 4.0f
#define MIN_LIMITS_CUBE_TRANSLATE_Y 0.45f

#define CLOSEST_LIMIT_CUBE_TRANSLATE_Z 5.0f 
#define FARTHEST_LIMIT_CUBE_TRANSLATE_Z -20.0f 

#define INCREMENT 0.1f
#define DECREMENT 0.1f

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

GLfloat angleCube = 0.0f;

// Lights Variable
GLfloat lightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat lightDefuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPositon[] = { 0.0f, 5.0f, 10.0f, 2.0f }; //x ,y, z, w

GLfloat materialAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat materialDeffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialShininess = 128.0f;

//Texture related variables
GLuint texture_marble;

GLfloat translateCubeX = 0.0f;
GLfloat translateCubeY = 1.0f;
GLfloat translateCubeZ = 0.0f;

GLfloat CubeScale = 0.25f;

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
		case VK_RIGHT:  // +x axis
			if (translateCubeX < MAX_LIMITS_CUBE_TRANSLATE_X)
			{
				translateCubeX += INCREMENT;
			}
			break;
		case VK_LEFT: //-x
			if (translateCubeX > MIN_LIMITS_CUBE_TRANSLATE_X)
			{
				translateCubeX -= DECREMENT;
			}
			break;
		case VK_UP: //+y
			if (translateCubeY < MAX_LIMITS_CUBE_TRANSLATE_Y)
			{
				translateCubeY += INCREMENT;
			}
			break;
		case VK_DOWN: // -y
			if (translateCubeY > MIN_LIMITS_CUBE_TRANSLATE_Y)
			{
				translateCubeY -= DECREMENT;
			}
			break;
		case VK_ADD: // cube away from viewver
			if (translateCubeZ < CLOSEST_LIMIT_CUBE_TRANSLATE_Z)
			{
				translateCubeZ += INCREMENT;
			}
			break;
		case VK_SUBTRACT: // cube towards viewver
			if (translateCubeZ > FARTHEST_LIMIT_CUBE_TRANSLATE_Z)
			{
				translateCubeZ -= DECREMENT;
			}
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
	pfd.cStencilBits = 24;    // without this line we can not have stencil 

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
	if (loadGLTexture(&texture_marble, MAKEINTRESOURCE(IDBITMAP_MARBLE)) == FALSE)
	{
		fprintf(gpFile, "load texture unsuccessful: MARBLE\n");
		return(-6);
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

	//Load Textures
	

	//enable texture
	glEnable(GL_TEXTURE_2D); //cause our texture is 2D

	// Light Configuration
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient); // light type, light property, Value 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDefuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositon);
	glLightfv(GL_LIGHT0, GL_SPECULAR , lightSpecular);

	glEnable(GL_LIGHT0); //Enable Light
	glEnable(GL_NORMALIZE); // normal scalling enable with norbale when scle up and scale down we are doing
	glEnable(GL_AUTO_NORMAL);

	//matrial confi
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDeffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

	//if we want to add light then Normal  Line is very imp it shows the orientation of the light its the perpendicular 


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
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);
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
	
void display()
{
	// function prototypes
	void DrawLitCube(void);
	void DrawFloor(void);

	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Set the matrix mode to model-view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set up camera
	gluLookAt(0.0f, 5.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	//render actual cube
	glPushMatrix(); // set camera matrix cody we need to push for the cube camera push 
	// Translate the scene backward
	glTranslatef(translateCubeX, translateCubeY, translateCubeZ);

	glScalef(CubeScale, CubeScale, CubeScale);
	// Apply rotation
	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);

	DrawLitCube();
	glPopMatrix();


	//define your floor as a stencil Stencil means chapa rangolicha chap
	//we are defining floor as a stencil so that we dont need a depth testing to improve performance
	glDisable(GL_DEPTH_TEST);
	//as now we not rendering anything for sometime so mask out all the colour component 
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	//now enable stencil test
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1); // always pass the stencil test where where its 1 pass 1 

	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // what should be done when stencil operation firt para keep all the values same 2 if depth test fails keep sme if both values pass replace glstencilfunc cha 2nd bharun trak replace ker 

	DrawFloor(); // this call will not render the floor this is only for stencil so that stencil is for the floor only define the floor as the stencil, its define the stencil limits

	glEnable(GL_DEPTH_TEST); //reanable the depth test

	//now we want start rendering so unmask the colour let the colours comes
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	//draw only when there is only 1 stored in stencil buffer
	glStencilFunc(GL_EQUAL, 1, 1);

	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	//render the reflected cube
	glPushMatrix(); // set camera matrix cody we need to push for the cube camera push 

	glScalef(1.0f, -1.0f, 1.0f);
	// Translate the scene backward
	glTranslatef(translateCubeX, translateCubeY, translateCubeZ);

	glScalef(CubeScale, CubeScale, CubeScale);
	// Apply rotation
	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);

	DrawLitCube();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);

	//render the floor
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	DrawFloor();
	glDisable(GL_BLEND);

	SwapBuffers(ghdc);
}

void DrawLitCube(void) 
{
	// code 
	glEnable(GL_LIGHTING);

	// Draw the cube
	// Front face
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 0.0f, 0.0f); // Red
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	// Back face
	glBegin(GL_QUADS);
	//glColor3f(0.0f, 1.0f, 0.0f); // Green
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	// Right face
	glBegin(GL_QUADS);
	//glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	// Left face
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	// Top face
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 0.0f, 1.0f); // Magenta
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	// Bottom face
	glBegin(GL_QUADS);
	//glColor3f(0.0f, 1.0f, 1.0f); // Cyan
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glDisable(GL_LIGHTING);
}

void DrawFloor(void)
{
	//code
	// translate triangle backwords by z
	glPushMatrix(); // pushing the camera matrix set in display
	glTranslatef(0.0f, -1.0f, -2.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // angle, x, y, z

	glScalef(10.0f, 10.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_marble);
	glBegin(GL_QUADS);

	// Top-right
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);

	// Top-left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);

	// Bottom-left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);

	// Bottom-right
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();

}

void update(void)
{
	// code

	angleCube = angleCube + 2.0f;

	if (angleCube >= 360.0f)
	{
		angleCube = angleCube - 360.0f;
	}

	//angleRectangle = angleRectangle - 2.0f;
	//if (angleRectangle <= 0)
	//{
	//	angleRectangle = angleRectangle + 360.0f;
	//}
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

	//if (texture_marble)
	//{
	//	glDeleteTextures(1, &texture_marble);
	//	texture_marble = 0;
	//}

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

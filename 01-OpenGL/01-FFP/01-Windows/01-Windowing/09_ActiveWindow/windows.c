#include<windows.h>
#include "Window.h"

#define win_width 800  // this std window height and width
#define win_height 600

//Active window varible
BOOL gbActiveWindow = FALSE;

// gloabal function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// global variable declarations
BOOL gbFullScreen = FALSE;    // g for global, b for BOOL
HWND ghwnd = NULL; // Handle window g is global hwndd is handle to the window initialize to NULL
DWORD dwStyle; // across the msg it will be use current windows style
WINDOWPLACEMENT wpPrev;// struct window

RECT rect;


// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//Function declarations
	int initialize(void);
	//void resize(int, int);
	void display(void);
	void update(void);
	void uninitialize(void);

	// variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("RTR6");

	BOOL bDone = FALSE;

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

	// Registration of window class
	RegisterClassEx(&wndclass);

	//cntering the window win32 Api to fo calculate window size
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	int x = (screenWidth - win_width) / 2;
	int y = (screenHeight - win_height) / 2;

	SetWindowPos(hwnd, NULL, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// create window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,//show window that will over task bar
		szAppName,
		TEXT("RAJASHREE ADIKANE"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 
		x,
		y,
		win_width,
		win_height,
		NULL,
		NULL,
		hInstance,
		NULL);
	ghwnd = hwnd; 
	// Show window
	ShowWindow(hwnd, iCmdShow);

	// Paint background of window
	//UpdateWindow(hwnd);

	//initialize
	int result = initialize();
	if (result != 0)
	{
		MessageBox(hwnd, TEXT("Initialization Failed!"), TEXT("Error"), MB_OK);
		DestroyWindow(hwnd);
		hwnd = NULL;
		return -1;
	}
	//else {
	//	printf("initalized function completed sucessfully");
	//}

	// Paint background of window
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//set this window as SetForegroundWindow and active window
	SetForegroundWindow(hwnd); 
	SetFocus(hwnd);


	//Game Loop
	while (bDone == FALSE) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE )) 
		{
			if (msg.message == WM_QUIT) {
				bDone = TRUE;      
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			if (gbActiveWindow == TRUE) { 
				//render
				display();

				//update
				update();
			}
		}
	}

	//unitialize
	initialize();
	return((int)msg.wParam);
}

// callback function
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// function declarations
	void toggleFullScreen(void);
	void resize(int, int);
	void uninitialize(void);

	// code
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
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam)); 

}


void toggleFullScreen(void) {

	//Variable declarations
	MONITORINFO mi;  

	//code
	if (gbFullScreen == FALSE) {
		// Get current window style
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE); 
		if (dwStyle & WS_OVERLAPPEDWINDOW) {
			ZeroMemory((void*)&mi, sizeof(MONITORINFO));
			mi.cbSize = sizeof(MONITORINFO);
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi)) 
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW); 
				SetWindowPos(ghwnd, HWND_TOP,  
					mi.rcMonitor.left, mi.rcMonitor.top, 
					mi.rcMonitor.right - mi.rcMonitor.left, 
					mi.rcMonitor.bottom - mi.rcMonitor.top, 
					SWP_NOZORDER | SWP_FRAMECHANGED); 
			}
		}
		ShowCursor(FALSE);  // our cursor
		gbFullScreen = TRUE;
	}
	else {
		// Restore previous window style and placement
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev); 
		SetWindowPos(ghwnd, HWND_TOP,        
			0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
		gbFullScreen = FALSE;
	}
}


int initialize(void) {
	//code

	return 0;
}

void resize(int width, int Height)
{
	//code

}

void display(void)
{
	//code
}

void update(void)
{
	//code
}

void uninitialize(void)
{
	//code
}









// Win32 Headers
#include<windows.h> 

// Global function declarations or prototype or signature
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Entry Point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{

// Varibale Declarations
WNDCLASSEX wndclass;
HWND hwnd;
MSG msg;
TCHAR szAppName[] = TEXT("RTR6"); //TEXT is macro

// Window class initialization
// code
wndclass.cbSize = sizeof(WNDCLASSEX);
wndclass.style = CS_HREDRAW | CS_VREDRAW;
wndclass.cbClsExtra = 0;
wndclass.cbWndExtra = 0;
wndclass.lpfnWndProc = WndProc;
wndclass.hInstance = hInstance;
wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
wndclass.lpszClassName = szAppName;
wndclass.lpszMenuName = NULL;
wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

//Registration of window class
RegisterClassEx(&wndclass);

//Create Window
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

//Show Window
ShowWindow(hwnd, iCmdShow);

//Paint Window
UpdateWindow(hwnd);

//Message loop
while (GetMessage(&msg, NULL, 0, 0))
{
	TranslateMessage(&msg);
	DispatchMessage(&msg);

}

return((int)msg.wParam);

}

//CallBack Function
LRESULT CALLBACK WndProc(HWND hwnd, UINT imsg, WPARAM wParam, LPARAM lParam)
{
//code
	switch (imsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, imsg, wParam, lParam));

}


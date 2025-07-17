// Win32 Headers
#include<windows.h> 

#include<window.h>


// Global function declarations or prototype or signature
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Entry Point Function 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{

	// Varibale Declarations
	WNDCLASSEX wndclass;
	HWND hwnd; // internally pointer but cannot use as a ponter its opague because 
	MSG msg;
	TCHAR szAppName[] = TEXT("RTR6"); //TEXT is macro characterbtype

	// Window class initialization
	// code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW; // cs-clss style
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON)); // icon of the system 
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));

	//Registration of window class
	RegisterClassEx(&wndclass);

	//Create Window
	hwnd = CreateWindow(  //memory handle will get in HWND 
		szAppName, // szAppName string, lpsz-custom class name asking, null terminated string type
		TEXT("Rajashree Adikane"), //window caption or title unicode string that why TEXT macro
		WS_OVERLAPPEDWINDOW, //  type-DWORD-double word 32 bit DWORD internally long or unsigned long, ws-window style create window like that that is top over other overlapped other windows ,
		//internally is a combination of 6 windows style WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | S_THICKFRAME-border think menu  
		CW_USEDEFAULT, //CW-create window, used for function paramter macro, create window used default,  for x-cordinate
		CW_USEDEFAULT,//y-cordinate
		CW_USEDEFAULT,//w-width
		CW_USEDEFAULT,//h-height
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
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Variable declarations
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	TCHAR str[] = TEXT("Hello World !!");
	static int iPaintFlag = -1;


	// code
	switch (iMsg)
	{

		//case WM_LBUTTONDOWN:
		//	GetClientRect(hwnd, &rc); // Get the dimensions of the client area
		//	hdc = GetDC(hwnd);        // Get the device context for the window
		//	// Set the background color
		//	SetBkColor(hdc, RGB(0, 0, 0)); // RGB(0, 0, 0) is black 
		//	SetTextColor(hdc, RGB(0, 255, 0));
		//	//TCHAR str[] = TEXT("Mouse Clicked!");
		//	DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		//	ReleaseDC(hwnd, hdc);

	case WM_CHAR:
		switch (wParam)
		{
		case 'R':
		case 'r':
			iPaintFlag = 1;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'G':
		case 'g':
			iPaintFlag = 2;
			InvalidateRect(hwnd, NULL, TRUE);
			break;


		case 'B':
		case 'b':
			iPaintFlag = 3;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'Y':
		case 'y':
			iPaintFlag = 4;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'C':
		case 'c':
			iPaintFlag = 5;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'M':
		case 'm':
			iPaintFlag = 6;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'W':
		case 'w':
			iPaintFlag = 7;
			InvalidateRect(hwnd, NULL, TRUE);
			break;



		default:
			break;
		}
		break;

	case WM_PAINT: //post 
		GetClientRect(hwnd, &rc); // Get the dimensions of the client area
		hdc = BeginPaint(hwnd, &ps);

		// Set the background color
		SetBkColor(hdc, RGB(0, 0, 0)); // RGB(0, 0, 0) is black 
		SetTextColor(hdc, RGB(0, 255, 0)); // Green text color

		if (iPaintFlag == 1)
			SetTextColor(hdc, RGB(255, 0, 0));
		else if (iPaintFlag == 2)
			SetTextColor(hdc, RGB(0, 255, 0));
		else if (iPaintFlag == 3)
			SetTextColor(hdc, RGB(0, 0, 255));
		else if (iPaintFlag == 4)
			SetTextColor(hdc, RGB(255, 255, 0));
		else if (iPaintFlag == 5)
			SetTextColor(hdc, RGB(255, 255, 255));
		else if (iPaintFlag == 6)
			SetTextColor(hdc, RGB(0, 255, 255));
		else if (iPaintFlag == 7)
			SetTextColor(hdc, RGB(255, 0, 255));


		// Text to display
		//TCHAR str[] = TEXT("Mouse Clicked!");

		// Draw the text in the center of the client area
		DrawText(hdc, str, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		break; // Added break to avoid falling through to WM_DESTROY

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}



// Headers
#include <windows.h>

// IDs
#define ID_SUBMIT_BUTTON 1001
#define ID_TEXTBOX 1002

// Dimensions
#define WIND_X 500
#define WIND_Y 400
#define TEXTBOX_X 230
#define TEXTBOX_Y 25
#define BUTTON_X 100
#define BUTTON_Y 30

// Others
#define TITLE "Network Scanner"
#define IP_TITLE "Enter Local IPv4 Address"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND hSubmitButton;
HWND hTextInput;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Reg the Windows Class First
	
	const char CLASS_NAME[] = "Network Scanner GUI"; // Main class name
	
	WNDCLASS wc = { }; 
	
	wc.lpfnWndProc = WindowProc;
	wc.hInstance  = hInstance;
	wc.lpszClassName = CLASS_NAME;
	
	RegisterClass(&wc);
	
	
	const char CHILD_CLASS_NAME[] = "ChildWindowClass";
	
	WNDCLASS childWc = { };
	
	childWc.lpfnWndProc = ChildWindowProc;
	childWc.hInstance = hInstance;
	childWc.lpszClassName = CHILD_CLASS_NAME;
	
	RegisterClass(&childWc);
	
	// Create the Main Window
	
	HWND hwnd = CreateWindowEx(
		0,                       		// Opt. Window Styles ----
		CLASS_NAME,              		// Window Class ----------
		"Network Scanner",       		// Name of Window --------
		WS_BORDER | WS_VISIBLE,         // Window Style ----------
		CW_USEDEFAULT, CW_USEDEFAULT, 	// x, y Pos --------------
		WIND_X, WIND_Y, 				// x, y Dim --------------
		NULL,							// Parent Window ---------
		NULL,							// Menu ------------------
		hInstance,						// Instance Handle -------
		NULL                            // Other Stuff -----------
		);
		
	if (hwnd == NULL) {
		return 0;
	}
	
	// Create Child Handle
	
	HWND hwndChild = CreateWindowEx(
		0,
		CHILD_CLASS_NAME,
		"Child Class",
		WS_CHILD | WS_VISIBLE,
		0, 0,
		WIND_X/2, WIND_Y,
		hwnd,
		NULL,
		hInstance,
		NULL
		);
	
		if (hwndChild == NULL) {
			return 0;
	}
	
	hTextInput = CreateWindow(
		"EDIT",
		"",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		10,
		60,
		TEXTBOX_X, TEXTBOX_Y,
		hwndChild,
		(HMENU)ID_TEXTBOX,
		hInstance,
		NULL
		);
	
	
	hSubmitButton = CreateWindow(
		"BUTTON",
		"Submit",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		(WIND_X/2) - BUTTON_X - 10,
		WIND_Y - BUTTON_Y - 40,
		BUTTON_X, BUTTON_Y,
		hwndChild,
		(HMENU)ID_SUBMIT_BUTTON,
		hInstance,
		NULL
		);
		
		if (!hSubmitButton) {
			return 0;
		}
	
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	// Run the message loop
	
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		
		case WM_PAINT:
		{	
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
			FillRect(hdc, &ps.rcPaint, hBrush);
			DeleteObject(hBrush);
			
			// text stuff
			SetTextColor(hdc, RGB(0,0,0));
			SetBkMode(hdc, TRANSPARENT);
			HFONT hFont = CreateFont(
				28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
			HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
			
			TextOut(hdc, (WIND_X/2)+5, 0, "Output Details", 14);
			DeleteObject(hFont);
			
			HFONT hFont2 = CreateFont(
				16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
			HFONT hOldFont2 = (HFONT)SelectObject(hdc, hFont2);
			
			TextOut(hdc, WIND_X-200,WIND_Y-55, "Press ESC to exit", 17);
			DeleteObject(hFont2);
			
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_KEYDOWN: {
			if (wParam == VK_ESCAPE) {
				DestroyWindow(hwnd);
			}
			break;

		}

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


LRESULT CALLBACK ChildWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			
			// painting
			HBRUSH hBrush = CreateSolidBrush(RGB(224, 224, 224));
			FillRect(hdc, &ps.rcPaint, hBrush);
			DeleteObject(hBrush);
			
			// text stuff
			SetTextColor(hdc, RGB(0,0,0));
			SetBkMode(hdc, TRANSPARENT);
			HFONT hFont = CreateFont(
				28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
			HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
			
			TextOut(hdc, 0, 0, TITLE, sizeof(TITLE));
			
			// Clean
			SelectObject(hdc, hOldFont);
			DeleteObject(hFont);
			
			HFONT hFont2 = CreateFont(
				16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
			HFONT hOldFont2 = (HFONT)SelectObject(hdc, hFont);
			
			TextOut(hdc, 10, 40, IP_TITLE, sizeof(IP_TITLE)); 
			
			SelectObject(hdc, hOldFont);
			DeleteObject(hFont);
			EndPaint(hwnd, &ps);
			
			return 0;
		}
		
		case WM_COMMAND: {
			if (LOWORD(wParam) == ID_SUBMIT_BUTTON) {
				char buffer[256];
				GetWindowText(hTextInput, buffer, sizeof(buffer));
				
				MessageBox(hwnd, buffer, "You entered:", MB_OK);
			}
			break;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
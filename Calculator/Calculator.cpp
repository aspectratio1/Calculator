// Calculator.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Calculator.h"
#include <cstring>
#include <iostream>
#include <sstream>

#define MAX_LOADSTRING 100
#define IDC_MAIN_EDIT 101
#define BUTTON_1 102
#define BUTTON_2 103
#define BUTTON_3 104
#define BUTTON_4 105
#define BUTTON_5 106
#define BUTTON_6 107
#define BUTTON_7 108
#define BUTTON_8 109
#define BUTTON_9 110
#define BUTTON_0 111
#define BUTTON_CLR 112
#define BUTTON_ADD 113
#define BUTTON_MINUS 114
#define BUTTON_MULTI 115
#define BUTTON_DIV 116
#define BUTTON_EQ 117
std::string EditText;


void AddEditText(HWND control, const char* text)
{
	EditText = EditText + text;
}

void Calculate(HWND control)
{
	//Create our Buffer to work on answer later.
#ifdef _UNICODE
	wostringstream oss;
#else
	std::ostringstream oss;
#endif
	double operationIndex, number1, number2, answer;
	TCHAR buff[MAX_PATH];
	GetDlgItemText(control, IDC_MAIN_EDIT, buff, 260);
	std::string box = buff;
	int length = box.length();
	for (int i = 0; i < length; i++)
	{
		if ((box.at(i) == '+') | (box.at(i) == '-') | (box.at(i) == '*') | (box.at(i) == '/'))
		{
			oss << i;

			std::string number1s, number2s;
			number1s = (box.substr(0, i));
			number2s = (box.substr(i + 1, box.length()));
			std::stringstream geek(number1s);
			std::stringstream geek2(number2s);
			geek >> number1;
			geek2 >> number2;
			switch (box.at(i))
			{
			case '+':
				answer = number1 + number2;
				break;
			case '-':
				answer = number1 - number2;
				break;
			case '*':
				answer = number1 * number2;
				break;
			case '/':
				answer = number1 / number2;
				break;

			default:
				answer = 0;
				break;
			}
			EditText = std::to_string(answer);
			SetDlgItemTextA(control, IDC_MAIN_EDIT, EditText.c_str());
		}
	}
	 
}


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CALCULATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CALCULATOR));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEXA);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CALCULATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = MAKEINTRESOURCEA(IDC_CALCULATOR);
    wcex.lpszClassName  = "Calculator";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExA(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowA("Calculator", "Calculator", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
      CW_USEDEFAULT, CW_USEDEFAULT, 270, 370, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		HWND hEdit;
		HFONT hfDefault;
		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED, 10, 10, 230, 50, hWnd, (HMENU)IDC_MAIN_EDIT, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow( "BUTTON", "1", WS_CHILD | WS_VISIBLE | WS_GROUP, 10, 70, 50, 50, hWnd, (HMENU)BUTTON_1, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "2", WS_CHILD | WS_VISIBLE, 70, 70, 50, 50, hWnd, (HMENU)BUTTON_2, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "3", WS_CHILD | WS_VISIBLE, 130, 70, 50, 50, hWnd, (HMENU)BUTTON_3, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "4", WS_CHILD | WS_VISIBLE, 10, 130, 50, 50, hWnd, (HMENU)BUTTON_4, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "5", WS_CHILD | WS_VISIBLE, 70, 130, 50, 50, hWnd, (HMENU)BUTTON_5, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "6", WS_CHILD | WS_VISIBLE, 130, 130, 50, 50, hWnd, (HMENU)BUTTON_6, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "7", WS_CHILD | WS_VISIBLE, 10, 190, 50, 50, hWnd, (HMENU)BUTTON_7, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "8", WS_CHILD | WS_VISIBLE, 70, 190, 50, 50, hWnd, (HMENU)BUTTON_8, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "9", WS_CHILD | WS_VISIBLE, 130, 190, 50, 50, hWnd, (HMENU)BUTTON_9, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "0", WS_CHILD | WS_VISIBLE, 70, 250, 50, 50, hWnd, (HMENU)BUTTON_0, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "CLR", WS_CHILD | WS_VISIBLE, 10, 250, 50, 50, hWnd, (HMENU)BUTTON_CLR, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 70, 50, 50, hWnd, (HMENU)BUTTON_ADD, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 130, 50, 50, hWnd, (HMENU)BUTTON_MINUS, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 190, 50, 50, hWnd, (HMENU)BUTTON_MULTI, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE | WS_BORDER, 190, 250, 50, 50, hWnd, (HMENU)BUTTON_DIV, GetModuleHandle(NULL), NULL);
		hEdit = CreateWindow("BUTTON", "=", WS_CHILD | WS_VISIBLE | WS_BORDER, 130, 250, 50, 50, hWnd, (HMENU)BUTTON_EQ, GetModuleHandle(NULL), NULL);

	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			HWND hEdit;
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case BUTTON_1:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "1");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_2:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "2");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_3:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "3");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_4:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "4");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_5:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "5");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_6:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "6");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_7:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "7");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_8:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "8");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_9:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "9");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_0:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "0");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_ADD:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				if ((EditText.find("+") != std::string::npos) || (EditText.find("-") != std::string::npos) || (EditText.find("*") != std::string::npos) || (EditText.find("/") != std::string::npos))
					break;
				AddEditText(hEdit, "+");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_MINUS:
				if ((EditText.find("+") != std::string::npos) || (EditText.find("-") != std::string::npos) || (EditText.find("*") != std::string::npos) || (EditText.find("/") != std::string::npos))
					break;
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "-");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_MULTI:
				if ((EditText.find("+") != std::string::npos) || (EditText.find("-") != std::string::npos) || (EditText.find("*") != std::string::npos) || (EditText.find("/") != std::string::npos))
					break;
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "*");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_DIV:
				if ((EditText.find("+") != std::string::npos) || (EditText.find("-") != std::string::npos) || (EditText.find("*") != std::string::npos) || (EditText.find("/") != std::string::npos))
					break;
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				AddEditText(hEdit, "/");
				SetWindowTextA(hEdit, EditText.c_str());
				break;
			case BUTTON_CLR:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				SetWindowText(hEdit, "");
				EditText = "";
				break;
			case BUTTON_EQ:
				hEdit = GetDlgItem(hWnd, IDC_MAIN_EDIT);
				Calculate(hWnd);
				break;
            default:
                return DefWindowProcA(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcA(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

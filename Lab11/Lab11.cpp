// Lab11.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Lab11.h"
#include "commctrl.h"
#include "strsafe.h"
#include <string>
#include <cmath>

#define MAX_LOADSTRING 100
#define TIMER1 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szText[MAX_LOADSTRING];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Test(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LAB11, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB11));

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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB11));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB11);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_TEST:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_TEST), hWnd,Test);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // black border
            SelectObject(hdc, hPen);

            POINT pp[6];
            pp[0].x = 100; pp[0].y = 50;
            pp[1].x = 143; pp[1].y = 75;
            pp[2].x = 143; pp[2].y = 125;
            pp[3].x = 100; pp[3].y = 150;
            pp[4].x = 57; pp[4].y = 125;
            pp[5].x = 57; pp[5].y = 75;
            Polygon(hdc, pp, 6);
            POINT tr1[3] = { pp[1],pp[2],{186,250} };
            Polygon(hdc, tr1, 3);
            POINT tr2[3] = { pp[2],pp[3],{186,250} };
            Polygon(hdc, tr2, 3);
            POINT tr3[3] = { pp[3],pp[4],{186,250} };
            Polygon(hdc, tr3, 3);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
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

INT_PTR CALLBACK Test(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int iProgress = 0, range = 0;
    int index = 0;
    double dVal;
    std::string::size_type sz;

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_TIMER:
        if (IsDlgButtonChecked(hDlg, IDC_CH_PR2) == IsDlgButtonChecked(hDlg, IDC_CH_PR1) == BST_CHECKED) {
            if (SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_GETPOS, 0, 0) + iProgress >= range) {
                SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETPOS, range, 0);
                SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_STEPIT, NULL, NULL);
            } else SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_STEPIT, NULL, NULL);
        }
        else {
            if (IsDlgButtonChecked(hDlg, IDC_CH_PR1) == BST_CHECKED)
                SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_STEPIT, NULL, NULL);
            if (IsDlgButtonChecked(hDlg, IDC_CH_PR2) == BST_CHECKED)
                SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_STEPIT, NULL, NULL);
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        bool toLB = false;
        switch (wmId)
        {
        case IDC_BTN_MTLB:
            toLB = true;
        case IDC_BTN_MTCB:
            try {
                if (!GetDlgItemText(hDlg, IDC_EDIT, szText, MAX_LOADSTRING))
                    *szText = 0;
                dVal = std::stod(szText, &sz);
                if (toLB) {
                    SendDlgItemMessage(hDlg, IDC_LB, LB_ADDSTRING, NULL, (LPARAM)szText);
                }
                else {
                    index = SendDlgItemMessage(hDlg, IDC_LB, LB_GETCURSEL, (WPARAM)NULL, (LPARAM)NULL);
                    if (index != CB_ERR)
                    {
                        index = SendDlgItemMessage(hDlg, IDC_LB, LB_GETTEXT, (WPARAM)index, (LPARAM)szText);
                        if (index != CB_ERR)
                            SendDlgItemMessage(hDlg, IDC_CB, CB_ADDSTRING, NULL, (LPARAM)szText);
                        else
                            MessageBox(hDlg, L"Error getting the selected item", L"ERROR!", MB_OK | MB_ICONERROR);
                    }
                    else MessageBox(hDlg, L"Error getting the selected item", L"ERROR!", MB_OK | MB_ICONERROR);
                }
            }
            catch (...) {
                MessageBox(hDlg, L"Error to extract double value", L"Error!", MB_ICONERROR | MB_OK);
                dVal = 0.0;
            }
            return (INT_PTR)TRUE;
            
        case IDC_BTN_START:
            if (!(IsDlgButtonChecked(hDlg, IDC_CH_PR1) == BST_CHECKED ||
                IsDlgButtonChecked(hDlg, IDC_CH_PR2) == BST_CHECKED))
                goto label;
            index = SendDlgItemMessage(hDlg, IDC_LB, LB_GETCURSEL, (WPARAM)NULL, (LPARAM)NULL);
            if (index != CB_ERR)
            {
                index = SendDlgItemMessage(hDlg, IDC_LB, LB_GETTEXT, (WPARAM)index, (LPARAM)szText);
                if (index != CB_ERR) {
                    try {
                        dVal = std::stod(szText, &sz);
                        range = (int)round(dVal);
                        /*
                        StringCbPrintf(szText, ARRAYSIZE(szText), L"The range is \"%i\"", range);
                        MessageBox(hDlg, szText, L"Done!", MB_OK);*/
                        SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETRANGE, NULL, MAKELPARAM(0, range));
                        SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETRANGE, NULL, MAKELPARAM(0, range));
                    }
                    catch (...) {
                        goto label;
                    }
                }
                else goto label;
            }
            else goto label;
            index = SendDlgItemMessage(hDlg, IDC_CB, CB_GETCURSEL, (WPARAM)NULL, (LPARAM)NULL);
            if (index != CB_ERR)
            {
                index = SendDlgItemMessage(hDlg, IDC_CB, CB_GETLBTEXT, (WPARAM)index, (LPARAM)szText);
                if (index != CB_ERR) {
                    try {
                        dVal = std::stod(szText, &sz);
                        iProgress = (int)round(dVal);
                        /*
                        StringCbPrintf(szText, ARRAYSIZE(szText), L"The step is \"%i\"", iProgress);
                        MessageBox(hDlg, szText, L"Done!", MB_OK);*/
                        SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETSTEP, (WPARAM)iProgress, NULL);
                        SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETSTEP, (WPARAM)iProgress, NULL);
                    }
                    catch (...) {
                        goto label;
                    }
                }
                else goto label;
            }
            else goto label;
            SetTimer(hDlg, TIMER1, 1000, NULL);
            //MessageBox(hDlg, L"Timer set", L"Done!", MB_OK);
            return (INT_PTR)TRUE;
            label:
            MessageBox(hDlg, L"Error extracting values", L"ERROR!", MB_OK | MB_ICONERROR);
            return (INT_PTR)TRUE;
            
        case IDC_BTN_STOP:
            KillTimer(hDlg, TIMER1);
            return (INT_PTR)TRUE;
              
        case IDOK:
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
    }
    return (INT_PTR)FALSE;
}
// FN21621397LAB07.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "FN21621397LAB07.h"
#include "strsafe.h"
#include <string>

#define MAX_LOADSTRING 100

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
INT_PTR CALLBACK    DegConverter(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    LenConverter(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_FN21621397LAB07, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FN21621397LAB07));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FN21621397LAB07));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FN21621397LAB07);
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
    HMENU hMenu, hSubMenu;
    DWORD dwRes;
    BOOL bRes;
    UINT uRes;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_DEG_CONVERTER:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DEG_CONVERTER), hWnd, DegConverter);
                break;
            case IDM_LEN_CONVERTER:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_LEN_CONVERTER), hWnd, LenConverter);
                break;
            case IDM_CHECK_ME:
                hMenu = GetMenu(hWnd);
                dwRes = GetMenuState(hMenu, IDM_CHECK_ME, MF_BYCOMMAND);
                ModifyMenu(hMenu, IDM_CHECK_ME, MF_BYCOMMAND,
                    IDM_CHECK_ME, dwRes & MF_CHECKED ? L"Check me" : L"Uncheck me");
                dwRes = CheckMenuItem(hMenu, IDM_CHECK_ME, dwRes & MF_CHECKED ? MF_UNCHECKED : MF_CHECKED);
                break;
            case IDM_DISABLE_ME:
                hMenu = GetMenu(hWnd);
                bRes = EnableMenuItem(hMenu, IDM_DISABLE_ME, MF_DISABLED);
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
    case WM_RBUTTONDOWN: {
        hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_POPUP));
        hSubMenu = GetSubMenu(hMenu, 0);
        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        ClientToScreen(hWnd, &pt);
        TrackPopupMenu(hSubMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
        DestroyMenu(hMenu);
        break;
    }
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
INT_PTR CALLBACK DegConverter(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:

        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDC_BTN_DEG:
            if (IsDlgButtonChecked(hDlg, IDC_RD_C_1) == BST_CHECKED &&
                IsDlgButtonChecked(hDlg, IDC_RD_C_2) == BST_CHECKED) {
                CheckRadioButton(hDlg, IDC_RD_C_1, IDC_RD_C_2, IDC_RD_C_2);
            }
            if (IsDlgButtonChecked(hDlg, IDC_RD_F_1) == BST_CHECKED &&
                IsDlgButtonChecked(hDlg, IDC_RD_F_2) == BST_CHECKED) {
                CheckRadioButton(hDlg, IDC_RD_F_1, IDC_RD_F_2, IDC_RD_F_2);
            }
            if (IsDlgButtonChecked(hDlg, IDC_RD_K_1) == BST_CHECKED &&
                IsDlgButtonChecked(hDlg, IDC_RD_K_2) == BST_CHECKED) {
                CheckRadioButton(hDlg, IDC_RD_K_1, IDC_RD_K_2, IDC_RD_K_2);
            }
            if (!((IsDlgButtonChecked(hDlg, IDC_RD_C_1) == BST_CHECKED ||
                IsDlgButtonChecked(hDlg, IDC_RD_F_1) == BST_CHECKED ||
                IsDlgButtonChecked(hDlg, IDC_RD_K_1) == BST_CHECKED) &&
                (IsDlgButtonChecked(hDlg, IDC_RD_C_2) == BST_CHECKED ||
                IsDlgButtonChecked(hDlg, IDC_RD_F_2) == BST_CHECKED ||
                IsDlgButtonChecked(hDlg, IDC_RD_K_2) == BST_CHECKED)))
                MessageBox(hDlg, L"Choose parameters", L"Error!", MB_OK);
            else {
                double dVal;
                std::string::size_type sz;
                try {
                    if (!GetDlgItemText(hDlg, IDC_DEG_IN, szText, MAX_LOADSTRING))
                        *szText = 0;
                    dVal = std::stod(szText, &sz);

                }
                catch (std::exception& e) {
                    MessageBox(hDlg, L"Error to extract double value", L"Error!",
                        MB_ICONERROR | MB_OK);
                    dVal = 0.0;
                }
                if (IsDlgButtonChecked(hDlg, IDC_RD_C_1) == BST_CHECKED) {
                    if (IsDlgButtonChecked(hDlg, IDC_RD_F_2) == BST_CHECKED) {
                        dVal = dVal * 1.8 + 32;
                    }
                    if (IsDlgButtonChecked(hDlg, IDC_RD_K_2) == BST_CHECKED) {
                        dVal += 273.15;
                    }
                }
                if (IsDlgButtonChecked(hDlg, IDC_RD_F_1) == BST_CHECKED) {
                    if (IsDlgButtonChecked(hDlg, IDC_RD_C_2) == BST_CHECKED) {
                        dVal = (dVal - 32) * 5 / 9;
                    }
                    if (IsDlgButtonChecked(hDlg, IDC_RD_K_2) == BST_CHECKED) {
                        dVal = (dVal - 32) * 5 / 9;
                        dVal += 273.15;
                    }
                }
                if (IsDlgButtonChecked(hDlg, IDC_RD_K_1) == BST_CHECKED) {
                    if (IsDlgButtonChecked(hDlg, IDC_RD_C_2) == BST_CHECKED) {
                        dVal -= 273.15;
                    }
                    if (IsDlgButtonChecked(hDlg, IDC_RD_F_2) == BST_CHECKED) {
                        dVal = (dVal - 273.15) * 1.8 + 32;
                    }
                }
                StringCbPrintf(szText, ARRAYSIZE(szText), L"%f", dVal);
                SetDlgItemText(hDlg, IDC_DEG_OUT, szText);
            }
            break;
        case IDOK:
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
    }
    return (INT_PTR)FALSE;
}
INT_PTR CALLBACK LenConverter(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDC_BTN_LEN:
            if (IsDlgButtonChecked(hDlg, IDC_RD_MI_1) == BST_CHECKED &&
                IsDlgButtonChecked(hDlg, IDC_RD_MI_2) == BST_CHECKED) {
                CheckRadioButton(hDlg, IDC_RD_MI_1, IDC_RD_MI_2, IDC_RD_MI_2);
            }
            if (IsDlgButtonChecked(hDlg, IDC_RD_KM_1) == BST_CHECKED &&
                IsDlgButtonChecked(hDlg, IDC_RD_KM_2) == BST_CHECKED) {
                CheckRadioButton(hDlg, IDC_RD_KM_1, IDC_RD_KM_2, IDC_RD_KM_2);
            }
            if (!((IsDlgButtonChecked(hDlg, IDC_RD_KM_1) == BST_CHECKED ||
                IsDlgButtonChecked(hDlg, IDC_RD_MI_1) == BST_CHECKED) &&
                (IsDlgButtonChecked(hDlg, IDC_RD_KM_2) == BST_CHECKED ||
                IsDlgButtonChecked(hDlg, IDC_RD_MI_2) == BST_CHECKED)))
                MessageBox(hDlg, L"Choose parameters", L"Error!", MB_OK);
            else {
                double dVal;
                std::string::size_type sz;
                try {
                    if (!GetDlgItemText(hDlg, IDC_LEN_IN, szText, MAX_LOADSTRING))
                        *szText = 0;
                    dVal = std::stod(szText, &sz);

                }
                catch (std::exception& e) {
                    MessageBox(hDlg, L"Error to extract double value", L"Error!",
                        MB_ICONERROR | MB_OK);
                    dVal = 0.0;
                }
                if (IsDlgButtonChecked(hDlg, IDC_RD_KM_1) == BST_CHECKED) {
                    if (IsDlgButtonChecked(hDlg, IDC_RD_MI_2) == BST_CHECKED) {
                        dVal *= 1.609344;
                    }
                }
                if (IsDlgButtonChecked(hDlg, IDC_RD_MI_1) == BST_CHECKED) {
                    if (IsDlgButtonChecked(hDlg, IDC_RD_KM_2) == BST_CHECKED) {
                        dVal /= 1.609344;
                    }
                }
                StringCbPrintf(szText, ARRAYSIZE(szText), L"%f", dVal);
                SetDlgItemText(hDlg, IDC_LEN_OUT, szText);
            }
            break;
        case IDOK:
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
    }
    return (INT_PTR)FALSE;
}
#include <windows.h>
#include <random>
#include <iostream>
#include <string>
#include <vector>
#include "Substitution_Cipher.hpp"
#include "Affine_Cipher.hpp"
#include "Recurrent_Affine_Cipher.hpp"
#define W_X 200
#define W_Y 350
#define W_W 850
#define W_H 500
LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM); // ������� ��������� ��������� ����
LONG WINAPI WndFirstProc(HWND, UINT, WPARAM, LPARAM); // ������� ��������� ��������� ����
LONG WINAPI WndSecondProc(HWND, UINT, WPARAM, LPARAM); // ������� ��������� ��������� ����
LONG WINAPI WndThirdProc(HWND, UINT, WPARAM, LPARAM); // ������� ��������� ��������� ����
//#define ID_1BUTT 1;
//#define ID_2BUTT 2;
int random(int a, int b) {
    std::random_device radm;
    std::mt19937_64 rng(radm());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(a, b);
    return distribution(rng);
}
// ������� �������������� ������ � �����
int StrToInt(wchar_t* s)
{
    int temp = 0; // �����
    int i = 0;
    int sign = 0; // ���� ����� 0- �������������, 1 - �������������
    if (s[i] == '-')
    {
        sign = 1;
        i++;
    }
    while (s[i] >= 0x30 && s[i] <= 0x39)
    {
        temp = temp + (s[i] & 0x0F);
        temp = temp * 10;
        i++;
    }
    temp = temp / 10;
    if (sign == 1)
        temp = -temp;
    return(temp);
}
// ������� �������������� ����� � ������
wchar_t* IntToStr(int n)
{
    wchar_t s[40], t, * temp;
    int i, k;
    int sign = 0;
    i = 0;
    k = n;
    if (k < 0)
    {
        sign = 1;
        k = -k;
    }
    do {
        t = k % 10;
        k = k / 10;
        s[i] = t | 0x30;
        i++;
    } while (k > 0);
    if (sign == 1)
    {
        s[i] = '-';
        i++;
    }
    temp = new wchar_t[i];
    k = 0;
    i--;
    while (i >= 0) {
        temp[k] = s[i];
        i--; k++;
    }
    temp[k] = '\0';
    return(temp);
}
// ��������� �������
int  WINAPI  WinMain(HINSTANCE  hInstance,
    HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd; // ���������� ����
    MSG msg;   // ��������� ���������
    WNDCLASS w; // ��������� ������ ����
    memset(&w, 0, sizeof(WNDCLASS)); // ������� ������ ��� ���������
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = (WNDPROC)WndProc;
    w.hInstance = hInstance;
    w.hbrBackground = CreateSolidBrush(0x00F0F0F0); // ���� ����
    w.lpszClassName = L"MyClass";
    RegisterClass(&w); // ����������� ������ ����

    WNDCLASS ww1; // ��������� ������ ����
    memset(&ww1, 0, sizeof(WNDCLASS)); // ������� ������ ��� ���������
    ww1.style = CS_HREDRAW | CS_VREDRAW;
    ww1.lpfnWndProc = (WNDPROC)WndFirstProc;
    ww1.hInstance = hInstance;
    ww1.hbrBackground = CreateSolidBrush(0x00F0F0F0); // ���� ����
    ww1.lpszClassName = L"first";
    RegisterClass(&ww1); // ����������� ������ ����

    WNDCLASS ww2; // ��������� ������ ����
    memset(&ww2, 0, sizeof(WNDCLASS)); // ������� ������ ��� ���������
    ww2.style = CS_HREDRAW | CS_VREDRAW;
    ww2.lpfnWndProc = (WNDPROC)WndSecondProc;
    ww2.hInstance = hInstance;
    ww2.hbrBackground = CreateSolidBrush(0x00F0F0F0); // ���� ����
    ww2.lpszClassName = L"second";
    RegisterClass(&ww2); // ����������� ������ ����

    WNDCLASS ww3; // ��������� ������ ����
    memset(&ww3, 0, sizeof(WNDCLASS)); // ������� ������ ��� ���������
    ww3.style = CS_HREDRAW | CS_VREDRAW;
    ww3.lpfnWndProc = (WNDPROC)WndThirdProc;
    ww3.hInstance = hInstance;
    ww3.hbrBackground = CreateSolidBrush(0x00F0F0F0); // ���� ����
    ww3.lpszClassName = L"third";
    RegisterClass(&ww3); // ����������� ������ ����

    // �������� ����
    hwnd = CreateWindow(L"MyClass", L"������������ ������ �1",
        WS_OVERLAPPEDWINDOW,
        W_X, W_Y, W_W-400, W_H-150,
        NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow); // ����������� ����
    UpdateWindow(hwnd);         // ����������� ����
    // ���� ��������� ���������
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return int(msg.wParam);
}
// ������� ��������� ���������
LONG WINAPI WndProc(HWND hwnd, UINT Message,
    WPARAM wparam, LPARAM lparam) {
    HDC hdc;
    HINSTANCE hInst;
    PAINTSTRUCT ps;
    HMENU IDC_GRPBUTTONS;
    static HWND hBtn0, hBtn1, hBtn, first, second, third; // ���������� ������
    static HWND hEdt1, hEdt2; // ����������� ����� ��������������
    //static HWND hEdt01;
    static std::vector<HWND> hEdt01(26);
    static std::vector<HWND> hEdt02(26);
    static HWND hStat; // ���������� ������������ ������
    TCHAR StrA[21474];
    int a, b, sum, Len;
    std::string str;
    std::string strEng = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //std::string strRus = "�����Ũ��������������������������";
    switch (Message) {
    case WM_CREATE: // ��������� �������� ����
        hInst = ((LPCREATESTRUCT)lparam)->hInstance; // ���������� ����������
        // ������� � ���������� �������
        /*hBtn0 = CreateWindow(L"button", L"�����������",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            350, 30, 60, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hBtn0, SW_SHOWNORMAL);*/
        

        //CreateWindow(TEXT("button"), TEXT("Choose colour"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 50, 25, 300, 70, hwnd, (HMENU)0, hInst, NULL);
        //CreateWindow(TEXT("button"), TEXT("Blue"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 70, 50, 75, 30, hwnd, (HMENU)ID_1BUTT, hInst, NULL);

        //DialogBox(hInst,
         //   MAKEINTRESOURCE(HYDRA),
         //   0, DialogProc);


        hBtn0 = CreateWindow(L"button", L"",
            WS_CHILD | WS_VISIBLE | WS_GROUP,
            20, 100, 120, 30, hwnd, (HMENU)0, hInst, NULL);

        CreateWindow(L"button", L"�������������� ����",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            200, 100, 250, 30, hwnd, ((HMENU)1), hInst, NULL);

        //CreateWindow(TEXT("button"), TEXT("Red"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 40, 80, 100, 30, hwnd, (HMENU)ID_1BUTT, hInst, NULL);

        CreateWindow(L"button", L"������� ����",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            200, 150, 250, 30, hwnd, (HMENU)2, hInst, NULL);

        CreateWindow(L"button", L"������� ������������ ����",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            200, 200, 250, 30, hwnd, (HMENU)3, hInst, NULL);


        //hBtn1 = CreateWindow(L"button", L"����",
        //    WS_CHILD | WS_VISIBLE | WS_GROUP,
        //    20, 150, 120, 30, hwnd, (HMENU)4, hInst, NULL);

        //CreateWindow(L"button", L"�������",
        //    WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        //    200, 150, 150, 30, hwnd, ((HMENU)5), hInst, NULL);

        ////CreateWindow(TEXT("button"), TEXT("Red"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 40, 80, 100, 30, hwnd, (HMENU)ID_1BUTT, hInst, NULL);

        //CreateWindow(L"button", L"����������",
        //    WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        //    400, 150, 150, 30, hwnd, (HMENU)6, hInst, NULL);
        
        ShowWindow(hBtn0, SW_HIDE);
        //ShowWindow(hBtn1, SW_HIDE);
        //// ������� � ���������� ������ ���� ��������������
        //hEdt1 = CreateWindow(L"edit", L"",
        //    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 50, 40, 600, 20,
        //    hwnd, 0, hInst, NULL);
        //ShowWindow(hEdt1, SW_SHOWNORMAL);
        //// ������� � ���������� ���� �����
        //hEdt2 = CreateWindow(L"edit", L"",
        //    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 50, 240, 600, 20,
        //    hwnd, 0, hInst, NULL);
        //ShowWindow(hEdt2, SW_SHOWNORMAL);


        //CreateMDIWindow(L"edit", L"",
        //    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 50, 240, 600, 20,
        //    hwnd,hInst, NULL);
        // ������� ����
        /*for (int i = 0; i < 26; i++) {
            hEdt01[i] = CreateWindow(L"static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
                50 + i * 50, 240, 40, 20, hwnd, 0, hInst, NULL);
            str = strEng[i];
            SetWindowText(hEdt01[i], (LPCWSTR)str.c_str());
            hEdt02[i] = CreateWindow(L"combobox", L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL, 50+i*50, 270, 40, 40,
                hwnd, (HMENU)(3+i), hInst, NULL);
        }*/
        //LB_ADDSTRING(hEdt22, 'asd');
        //SendMessage(hEdt01, WM_SETREDRAW, FALSE, 0L);
        //SendMessage(hEdt22, CB_ADDSTRING, 0, (LPARAM)(LPSTR)"A");
        //SendMessage(hEdt22, CB_ADDSTRING, 0, (LPARAM)str.c_str());

        /*for (int i = 0; i < streng.length(); i++) {
            str = streng[i];
            sendmessage(hedt02[i], cb_addstring, 0, (lparam)str.c_str());
        }*/

        //SendMessage(hEdt01, WM_SETREDRAW, TRUE, 0L);
        //InvalidateRect(hEdt01, NULL, TRUE);
        //ComboBox_AddItemData();
        //ShowWindow(hEdt22, SW_SHOWNORMAL);
        //if (HIWORD(lparam) == LBN_DBLCLK)
        //{
            //int uSelectedItem;
           // char Buffer[256];

            // ���������� ����� ���������� ������
            //uSelectedItem = (int)SendMessage(hEdt22,
             //   LB_GETCURSEL, 0, 0L);

            // ���� � ������ ���� ���������� ������,
            // ������� �� �� ����� 
           // if (uSelectedItem != LB_ERR)
           // {
                // �������� ���������� ������
            //    SendMessage(hEdt22, LB_GETTEXT,
                //    uSelectedItem, (LPARAM)Buffer);

                // ������� �� �� �����  
              //  MessageBox(hwnd, (LPCWSTR)(LPSTR)Buffer, L"szWindowTitle",
            //        MB_OK);
          //  }
        //}
        // ������� � ���������� ������
        hBtn = CreateWindow(L"button", L"�����",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            200, 250, 120, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hBtn, SW_SHOWNORMAL);
        // ������� � ���������� ���� ������ ��� ����������
        /*hStat = CreateWindow(L"static", L"", WS_CHILD | WS_VISIBLE,
            50, 400, 600, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hStat, SW_SHOWNORMAL);*/
        break;
    case WM_COMMAND:  // ��������� � �������
        if (HIWORD(wparam) == BN_CLICKED) {
            //flag = BM_GETSTATE(hBtn0, 0);
            //BS_RADIOBUTTON
            //flag = IsDlgButtonChecked(hwnd, 0);
           // if (IsDlgButtonChecked(hwnd, 1) == BST_CHECKED)
           //     MessageBox(hwnd, L"������� ������", L"������ ����11", MB_OK | MB_ICONERROR);
           // if (IsDlgButtonChecked(hwnd, 2) == BST_CHECKED)
            //    MessageBox(hwnd, L"������� ������", L"������ ����22", MB_OK | MB_ICONERROR);
            //switch (flag) {
            //case 1: // ���� ������������ ��
             //   MessageBox(hwnd, L"������� ������", L"������ ����11", MB_OK | MB_ICONERROR);
               // break;
           // case 2: // ���� ������������� ��
           //     MessageBox(hwnd, L"������� ������", L"������ ����22", MB_OK | MB_ICONERROR);
           //     break;
           // }
            if (lparam == (LPARAM)hBtn)    // ���� ������ �� ������
            {
              //  if (IsDlgButtonChecked(hwnd, 1) == BST_CHECKED)
               //     MessageBox(hwnd, L"������� ������", L"������ ����1", MB_OK | MB_ICONERROR);
              //  if (IsDlgButtonChecked(hwnd, 2) == BST_CHECKED)
             //       MessageBox(hwnd, L"������� ������", L"������ ����2", MB_OK | MB_ICONERROR);



                /*if (IsDlgButtonChecked(hwnd, 1) == BST_UNCHECKED && IsDlgButtonChecked(hwnd, 2) == BST_UNCHECKED)
                    MessageBox(hwnd, L"�������� �����", L"������", MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt1, StrA, 20) == 0)
                    MessageBox(hwnd, L"������� �������� �����", L"������", MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt2, StrA, 20) == 0) {
                    MessageBox(hwnd, L"������� ����", L"������", MB_OK | MB_ICONERROR);*/
                if (IsDlgButtonChecked(hwnd, 1) == BST_UNCHECKED && IsDlgButtonChecked(hwnd, 2) == BST_UNCHECKED && IsDlgButtonChecked(hwnd, 3) == BST_UNCHECKED)
                    MessageBox(hwnd, L"�������� ����", L"������", MB_OK | MB_ICONERROR);
                /*if (IsDlgButtonChecked(hwnd, 5) == BST_UNCHECKED && IsDlgButtonChecked(hwnd, 6) == BST_UNCHECKED)
                    MessageBox(hwnd, L"�������� ����", L"������", MB_OK | MB_ICONERROR);*/

                if (IsDlgButtonChecked(hwnd, 1) == BST_CHECKED) { // ��������������
                    first = CreateWindow(L"first", L"�������������� ����",
                        WS_VISIBLE | WS_POPUP | WS_OVERLAPPEDWINDOW,
                        W_X, W_Y, W_W, W_H, hwnd, 0, NULL, NULL);
                    ShowWindow(first, SW_SHOWNORMAL);
                }
                if (IsDlgButtonChecked(hwnd, 2) == BST_CHECKED) { // �������
                    second = CreateWindow(L"second", L"������� ����",
                        WS_VISIBLE | WS_POPUP | WS_OVERLAPPEDWINDOW,
                        W_X, W_Y, W_W, W_H, hwnd, 0, NULL, NULL);
                    ShowWindow(second, SW_SHOWNORMAL);
                }
                if (IsDlgButtonChecked(hwnd, 3) == BST_CHECKED) { // ������������
                    third = CreateWindow(L"third", L"������� ������������ ����",
                        WS_VISIBLE | WS_POPUP | WS_OVERLAPPEDWINDOW,
                        W_X, W_Y, W_W, W_H, hwnd, 0, NULL, NULL);
                    ShowWindow(third, SW_SHOWNORMAL);
                }
                    /*hInst = ((LPCREATESTRUCT)lparam)->hInstance;
                    CreateWindow(L"static", L"������ 1",
                        WS_OVERLAPPEDWINDOW | WS_CHILD,
                        200, 350, 850, 500,
                        NULL, NULL, hInst, NULL);*/



                    /*sec = CreateWindow(l"second", l"������ 1", WS_VISIBLE | WS_OVERLAPPEDWINDOW, W_X, W_Y, W_W, W_H, hwnd, 0, NULL, NULL);
                    ShowWindow(sec, SW_SHOWNORMAL);*/


                }
               // switch (flag) {
               // case 1: // ���� ������������ ��
                 //   MessageBox(hwnd, L"������� ������", L"������ ����1", MB_OK | MB_ICONERROR);
                //    break;
               // case 2: // ���� ������������� ��
               //     MessageBox(hwnd, L"������� ������", L"������ ����2", MB_OK | MB_ICONERROR);
               //     break;
              //  default: // ���� ������� �������
              //       MessageBox(hwnd, L"������� ������", L"������ ����3", MB_OK | MB_ICONERROR);
              //    break;
               // } 

                //Len = GetWindowText(hEdt1, StrA, 20);
                //a = StrToInt(StrA); // ��������� ����� �� ������� ����
                //Len = GetWindowText(hEdt2, StrA, 20);
                //b = StrToInt(StrA); // ��������� ����� �� ������� ����
                //sum = a + b;  // ������� ����� ���� �����
                //SetWindowText(hStat, IntToStr(sum)); // ������� ��������� � ����������� ����
            //}
        }
        break;
    case WM_PAINT: // ����������� ����
        hdc = BeginPaint(hwnd, &ps); // ������ �����������
        //TextOut(hdc, 50, 20, L"�������� �����:", ARRAYSIZE(L"�������� �����:")); // ���� ��������� ���������
        SetBkColor(hdc, 0x00F0F0F0);
        TextOut(hdc, 50, 110, L"�������� ����:", ARRAYSIZE(L"�������� ����:")); // ����� ��������� ���������
        //TextOut(hdc, 50, 220, L"����:", ARRAYSIZE(L"����:")); // ����� ��������� ���������
        //TextOut(hdc, 50, 380, L"����������:", ARRAYSIZE(L"����������:"));
        EndPaint(hwnd, &ps); // ����� �����������
        break;
    case WM_DESTROY: // �������� ����
        PostQuitMessage(0);
        break;
    default: // ��������� ��������� �� ���������
        return LONG(DefWindowProc(hwnd, Message, wparam, lparam));
    }
    return 0;
}


// ������� ��������� ���������
LONG WINAPI WndFirstProc(HWND hwnd, UINT Message,
    WPARAM wparam, LPARAM lparam) {
    HDC hdc;
    HINSTANCE hInst;
    PAINTSTRUCT ps;
    HMENU IDC_GRPBUTTONS;
    static HWND hBtn0, hBtn, hGenBtn, hStartBtn, first; // ���������� ������
    static HWND hEdt1, hEdt2; // ����������� ����� ��������������
    //static HWND hEdt01;
    static std::vector<HWND> hEdt01(26);
    static std::vector<HWND> hEdt02(26);
    static HWND hStat; // ���������� ������������ ������
    TCHAR StrA[21474];
    int Len;
    std::string a, b, sum;
    std::string str;
    std::string strEng = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //std::string strRus = "�����Ũ��������������������������";
    switch (Message) {
    case EN_MAXTEXT:
        SendMessage(hEdt1, EM_SETLIMITTEXT, 2000, 0);
        break;
    case WM_CREATE: // ��������� �������� ����
        hInst = ((LPCREATESTRUCT)lparam)->hInstance; // ���������� ����������
        // ������� � ���������� �������
        /*hBtn0 = CreateWindow(L"button", L"�����������",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            350, 30, 60, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hBtn0, SW_SHOWNORMAL);*/


        //CreateWindow(TEXT("button"), TEXT("Choose colour"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 50, 25, 300, 70, hwnd, (HMENU)0, hInst, NULL);
        //CreateWindow(TEXT("button"), TEXT("Blue"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 70, 50, 75, 30, hwnd, (HMENU)ID_1BUTT, hInst, NULL);

        //DialogBox(hInst,
         //   MAKEINTRESOURCE(HYDRA),
         //   0, DialogProc);


        hBtn0 = CreateWindow(L"button", L"",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            20, 100, 120, 30, hwnd, (HMENU)0, hInst, NULL);

        CreateWindow(L"button", L"������������",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            200, 100, 150, 30, hwnd, ((HMENU)1), hInst, NULL);

        //CreateWindow(TEXT("button"), TEXT("Red"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 40, 80, 100, 30, hwnd, (HMENU)ID_1BUTT, hInst, NULL);

        CreateWindow(L"button", L"�������������",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            400, 100, 150, 30, hwnd, (HMENU)2, hInst, NULL);

        ShowWindow(hBtn0, SW_HIDE);
        // ������� � ���������� ������ ���� ��������������
        hEdt1 = CreateWindow(L"edit", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT, 50, 40, 600, 20,
            hwnd, 0, hInst, NULL);
        ShowWindow(hEdt1, SW_SHOWNORMAL);
        // ������� � ���������� ���� �����
        hEdt2 = CreateWindow(L"edit", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 50, 240, 600, 20,
            hwnd, 0, hInst, NULL);
        ShowWindow(hEdt2, SW_SHOWNORMAL);


        /*CreateMDIWindow(L"edit", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 50, 240, 600, 20,
            hwnd, hInst, NULL);*/
        // ������� ����
        /*for (int i = 0; i < 26; i++) {
            hEdt01[i] = CreateWindow(L"static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
                50 + i * 50, 240, 40, 20, hwnd, 0, hInst, NULL);
            str = strEng[i];
            SetWindowText(hEdt01[i], (LPCWSTR)str.c_str());
            hEdt02[i] = CreateWindow(L"combobox", L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL, 50+i*50, 270, 40, 40,
                hwnd, (HMENU)(3+i), hInst, NULL);
        }*/
        //LB_ADDSTRING(hEdt22, 'asd');
        //SendMessage(hEdt01, WM_SETREDRAW, FALSE, 0L);
        //SendMessage(hEdt22, CB_ADDSTRING, 0, (LPARAM)(LPSTR)"A");
        //SendMessage(hEdt22, CB_ADDSTRING, 0, (LPARAM)str.c_str());

        /*for (int i = 0; i < streng.length(); i++) {
            str = streng[i];
            sendmessage(hedt02[i], cb_addstring, 0, (lparam)str.c_str());
        }*/

        //SendMessage(hEdt01, WM_SETREDRAW, TRUE, 0L);
        //InvalidateRect(hEdt01, NULL, TRUE);
        //ComboBox_AddItemData();
        //ShowWindow(hEdt22, SW_SHOWNORMAL);
        //if (HIWORD(lparam) == LBN_DBLCLK)
        //{
            //int uSelectedItem;
           // char Buffer[256];

            // ���������� ����� ���������� ������
            //uSelectedItem = (int)SendMessage(hEdt22,
             //   LB_GETCURSEL, 0, 0L);

            // ���� � ������ ���� ���������� ������,
            // ������� �� �� ����� 
           // if (uSelectedItem != LB_ERR)
           // {
                // �������� ���������� ������
            //    SendMessage(hEdt22, LB_GETTEXT,
                //    uSelectedItem, (LPARAM)Buffer);

                // ������� �� �� �����  
              //  MessageBox(hwnd, (LPCWSTR)(LPSTR)Buffer, L"szWindowTitle",
            //        MB_OK);
          //  }
        //}
        hGenBtn = CreateWindow(L"button", L"Random key",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            700, 195-20, 120, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hGenBtn, SW_SHOWNORMAL);
        hStartBtn = CreateWindow(L"button", L"AB..Z key",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            700, 295-50, 120, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hStartBtn, SW_SHOWNORMAL);
        // ������� � ���������� ������
        hBtn = CreateWindow(L"button", L"Run",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            700, 395, 120, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hBtn, SW_SHOWNORMAL);
        // ������� � ���������� ���� ������ ��� ����������
        hStat = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER | ES_READONLY,
            50, 400, 600, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hStat, SW_SHOWNORMAL);
        break;
    case WM_COMMAND:  // ��������� � �������
        if (HIWORD(wparam) == BN_CLICKED) {
            //flag = BM_GETSTATE(hBtn0, 0);
            //BS_RADIOBUTTON
            //flag = IsDlgButtonChecked(hwnd, 0);
           // if (IsDlgButtonChecked(hwnd, 1) == BST_CHECKED)
           //     MessageBox(hwnd, L"������� ������", L"������ ����11", MB_OK | MB_ICONERROR);
           // if (IsDlgButtonChecked(hwnd, 2) == BST_CHECKED)
            //    MessageBox(hwnd, L"������� ������", L"������ ����22", MB_OK | MB_ICONERROR);
            //switch (flag) {
            //case 1: // ���� ������������ ��
             //   MessageBox(hwnd, L"������� ������", L"������ ����11", MB_OK | MB_ICONERROR);
               // break;
           // case 2: // ���� ������������� ��
           //     MessageBox(hwnd, L"������� ������", L"������ ����22", MB_OK | MB_ICONERROR);
           //     break;
           // }
            if (lparam == (LPARAM)hGenBtn) {
                std::string tempStr = strEng;
                std::string randStr;
                int i = 0;
                while (tempStr.size()) {
                    i = random(0, tempStr.size() - 1);
                    randStr.push_back(tempStr.at(i));
                    tempStr.erase(i, 1);
                }
                std::wstring temp;
                temp = std::wstring(randStr.begin(), randStr.end());
                LPCWSTR wideString = temp.c_str();
                SetWindowText(hEdt2, wideString);
            }
            if (lparam == (LPARAM)hStartBtn) {
                std::wstring temp;
                temp = std::wstring(strEng.begin(), strEng.end());
                LPCWSTR wideString = temp.c_str();
                SetWindowText(hEdt2, wideString);
            }
            if (lparam == (LPARAM)hBtn)    // ���� ������ �� ������
            {
                SetWindowText(hStat, (LPCWSTR)(L""));
                Len = GetWindowText(hEdt2, StrA, 21474);
                bool collision = FALSE;
                std::wstring wStr = StrA;
                std::string s = std::string(wStr.begin(), wStr.end());
                if (IsDlgButtonChecked(hwnd, 1) == BST_UNCHECKED && IsDlgButtonChecked(hwnd, 2) == BST_UNCHECKED)
                    MessageBox(hwnd, L"�������� �����", L"������", MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt1, StrA, 21474) == 0)
                    MessageBox(hwnd, L"������� �������� �����", L"������", MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt2, StrA, 21474) == 0) {
                    MessageBox(hwnd, L"������� ����", L"������", MB_OK | MB_ICONERROR);
                } else {
                    if (s.size() == 26) {
                        for (int i = 0; i<s.size()-1; i++) {
                            for (int j = i+1; j < s.size(); j++) {
                                if (s.at(i) == s.at(j)) {
                                    MessageBox(hwnd, L"�������� �����", L"������", MB_OK | MB_ICONERROR);
                                    collision = TRUE;
                                }
                            }
                        }
                    }
                }
                if (IsDlgButtonChecked(hwnd, 1) == BST_CHECKED) { // encode
                    /*Len = GetWindowText(hEdt2, StrA, 21474);*/
                    /*std::wstring wStr = StrA;
                    std::string s = std::string(wStr.begin(), wStr.end());*/
                    if (s.size() != 26 && s.size() != 0) {
                        MessageBox(hwnd, L"���� ������ ����� ������ � 26 ��������", L"������", MB_OK | MB_ICONERROR);
                    }
                    if (s.size() == 26 && !collision) {
                        Substitution_Cipher d{s};
                        Len = GetWindowText(hEdt1, StrA, 21474);
                        wStr = StrA;
                        s = std::string(wStr.begin(), wStr.end());
                        d.setOpText(s);
                        auto qqq = d.Encrypt();
                        std::wstring temp;
                        temp = std::wstring(qqq.begin(), qqq.end());
                        LPCWSTR wideString = temp.c_str();
                        SetWindowText(hStat, wideString);
                    }
                }
                if (IsDlgButtonChecked(hwnd, 2) == BST_CHECKED) { // decode
                    /*Len = GetWindowText(hEdt2, StrA, 21474);*/
                    /*std::wstring wStr = StrA;
                    std::string s = std::string(wStr.begin(), wStr.end());*/
                    if (s.size() != 26 && s.size() != 0) {
                        MessageBox(hwnd, L"���� ������ ����� ������ � 26 ��������", L"������", MB_OK | MB_ICONERROR);
                    }
                    if (s.size() == 26 && !collision) {
                        Substitution_Cipher d{s};
                        Len = GetWindowText(hEdt1, StrA, 21474);
                        wStr = StrA;
                        s = std::string(wStr.begin(), wStr.end());
                        d.setClText(s);
                        auto qqq = d.Decrypt();
                        std::wstring temp;
                        temp = std::wstring(qqq.begin(), qqq.end());
                        LPCWSTR wideString = temp.c_str();
                        SetWindowText(hStat, wideString);
                    }
                }
            }
        }
        break;
    case WM_PAINT: // ����������� ����
        hdc = BeginPaint(hwnd, &ps); // ������ �����������
        SetBkColor(hdc, 0x00F0F0F0);
        TextOut(hdc, 50, 20, L"�������� �����:", ARRAYSIZE(L"�������� �����:")); // ���� ��������� ���������
        TextOut(hdc, 50, 110, L"�������� �����:", ARRAYSIZE(L"�������� �����:")); // ����� ��������� ���������
        TextOut(hdc, 50, 220, L"����:", ARRAYSIZE(L"����:")); // ����� ��������� ���������
        TextOut(hdc, 50, 380, L"����������:", ARRAYSIZE(L"����������:"));
        EndPaint(hwnd, &ps); // ����� �����������
        break;
    case WM_DESTROY: // �������� ����
        //PostQuitMessage(0);
        break;
    default: // ��������� ��������� �� ���������
        return LONG(DefWindowProc(hwnd, Message, wparam, lparam));
    }
    return 0;
}

// ������� ��������� ���������
LONG WINAPI WndSecondProc(HWND hwnd, UINT Message,
    WPARAM wparam, LPARAM lparam) {
    HDC hdc;
    HINSTANCE hInst;
    PAINTSTRUCT ps;
    HMENU IDC_GRPBUTTONS;
    static HWND hBtn0, hBtn, first; // ���������� ������
    static HWND hEdt1, hEdt2, hEdt3; // ����������� ����� ��������������
    //static HWND hEdt01;
    static std::vector<HWND> hEdt01(26);
    static std::vector<HWND> hEdt02(26);
    static HWND hStat; // ���������� ������������ ������
    TCHAR StrA[21474];
    int a, b, sum, Len;
    std::string str;
    std::string strEng = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //std::string strRus = "�����Ũ��������������������������";
    switch (Message) {
    case EN_MAXTEXT:
        SendMessage(hEdt1, EM_SETLIMITTEXT, 2000, 0);
        break;
    case WM_CREATE: // ��������� �������� ����
        hInst = ((LPCREATESTRUCT)lparam)->hInstance; // ���������� ����������
        // ������� � ���������� �������
        /*hBtn0 = CreateWindow(L"button", L"�����������",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            350, 30, 60, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hBtn0, SW_SHOWNORMAL);*/


        //CreateWindow(TEXT("button"), TEXT("Choose colour"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 50, 25, 300, 70, hwnd, (HMENU)0, hInst, NULL);
        //CreateWindow(TEXT("button"), TEXT("Blue"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 70, 50, 75, 30, hwnd, (HMENU)ID_1BUTT, hInst, NULL);

        //DialogBox(hInst,
         //   MAKEINTRESOURCE(HYDRA),
         //   0, DialogProc);


        hBtn0 = CreateWindow(L"button", L"",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            20, 100, 120, 30, hwnd, (HMENU)0, hInst, NULL);

        CreateWindow(L"button", L"������������",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            200, 100, 150, 30, hwnd, ((HMENU)1), hInst, NULL);

        //CreateWindow(TEXT("button"), TEXT("Red"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 40, 80, 100, 30, hwnd, (HMENU)ID_1BUTT, hInst, NULL);

        CreateWindow(L"button", L"�������������",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            400, 100, 150, 30, hwnd, (HMENU)2, hInst, NULL);

        ShowWindow(hBtn0, SW_HIDE);
        // ������� � ���������� ������ ���� ��������������
        hEdt1 = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER | ES_LEFT, 50, 40, 600, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hEdt1, SW_SHOWNORMAL);
        // ������� � ���������� ���� �����
        hEdt2 = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER | ES_LEFT, 100+50, 240, 60, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hEdt2, SW_SHOWNORMAL);
        hEdt3 = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER | ES_LEFT, 100+130, 240, 60, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hEdt3, SW_SHOWNORMAL);
        // ������� ����
        /*for (int i = 0; i < 26; i++) {
            hEdt01[i] = CreateWindow(L"static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
                50 + i * 50, 240, 40, 20, hwnd, 0, hInst, NULL);
            str = strEng[i];
            SetWindowText(hEdt01[i], (LPCWSTR)str.c_str());
            hEdt02[i] = CreateWindow(L"combobox", L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL, 50+i*50, 270, 40, 40,
                hwnd, (HMENU)(3+i), hInst, NULL);
        }*/
        //LB_ADDSTRING(hEdt22, 'asd');
        //SendMessage(hEdt01, WM_SETREDRAW, FALSE, 0L);
        //SendMessage(hEdt22, CB_ADDSTRING, 0, (LPARAM)(LPSTR)"A");
        //SendMessage(hEdt22, CB_ADDSTRING, 0, (LPARAM)str.c_str());

        /*for (int i = 0; i < streng.length(); i++) {
            str = streng[i];
            sendmessage(hedt02[i], cb_addstring, 0, (lparam)str.c_str());
        }*/

        //SendMessage(hEdt01, WM_SETREDRAW, TRUE, 0L);
        //InvalidateRect(hEdt01, NULL, TRUE);
        //ComboBox_AddItemData();
        //ShowWindow(hEdt22, SW_SHOWNORMAL);
        //if (HIWORD(lparam) == LBN_DBLCLK)
        //{
            //int uSelectedItem;
           // char Buffer[256];

            // ���������� ����� ���������� ������
            //uSelectedItem = (int)SendMessage(hEdt22,
             //   LB_GETCURSEL, 0, 0L);

            // ���� � ������ ���� ���������� ������,
            // ������� �� �� ����� 
           // if (uSelectedItem != LB_ERR)
           // {
                // �������� ���������� ������
            //    SendMessage(hEdt22, LB_GETTEXT,
                //    uSelectedItem, (LPARAM)Buffer);

                // ������� �� �� �����  
              //  MessageBox(hwnd, (LPCWSTR)(LPSTR)Buffer, L"szWindowTitle",
            //        MB_OK);
          //  }
        //}
        // ������� � ���������� ������
        hBtn = CreateWindow(L"button", L"Run",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            700, 395, 120, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hBtn, SW_SHOWNORMAL);
        // ������� � ���������� ���� ������ ��� ����������
        hStat = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER | ES_READONLY,
            50, 400, 600, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hStat, SW_SHOWNORMAL);
        break;
    case WM_COMMAND:  // ��������� � �������
        if (HIWORD(wparam) == BN_CLICKED) {
            // flag = BM_GETSTATE(hBtn0, 0);
            // BS_RADIOBUTTON
            // flag = IsDlgButtonChecked(hwnd, 0);
            // if (IsDlgButtonChecked(hwnd, 1) == BST_CHECKED)
            //     MessageBox(hwnd, L"������� ������", L"������ ����11", MB_OK |
            //     MB_ICONERROR);
            // if (IsDlgButtonChecked(hwnd, 2) == BST_CHECKED)
            //    MessageBox(hwnd, L"������� ������", L"������ ����22", MB_OK |
            //    MB_ICONERROR);
            // switch (flag) {
            // case 1: // ���� ������������ ��
            //   MessageBox(hwnd, L"������� ������", L"������ ����11", MB_OK |
            //   MB_ICONERROR);
            // break;
            // case 2: // ���� ������������� ��
            //     MessageBox(hwnd, L"������� ������", L"������ ����22", MB_OK |
            //     MB_ICONERROR); break;
            // }
            if (lparam == (LPARAM)hBtn) // ���� ������ �� ������
            {
                SetWindowText(hStat, (LPCWSTR)(L""));
                //  if (IsDlgButtonChecked(hwnd, 1) == BST_CHECKED)
                //     MessageBox(hwnd, L"������� ������", L"������ ����1",
                //     MB_OK | MB_ICONERROR);
                //  if (IsDlgButtonChecked(hwnd, 2) == BST_CHECKED)
                //       MessageBox(hwnd, L"������� ������", L"������ ����2",
                //       MB_OK | MB_ICONERROR);
                if (IsDlgButtonChecked(hwnd, 1) == BST_UNCHECKED &&
                    IsDlgButtonChecked(hwnd, 2) == BST_UNCHECKED)
                    MessageBox(hwnd, L"�������� �����", L"������",
                               MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt1, StrA, 21474) == 0)
                    MessageBox(hwnd, L"������� �������� �����", L"������",
                               MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt2, StrA, 21474) == 0)
                    MessageBox(hwnd, L"������� ���� �����", L"������",
                               MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt3, StrA, 21474) == 0)
                    MessageBox(hwnd, L"������� ���� �����", L"������",
                               MB_OK | MB_ICONERROR);
                // Len = GetWindowText(hEdt1, StrA, 21474);
                // a = StrToInt(StrA); // ��������� ����� �� ������� ����
                // Len = GetWindowText(hEdt2, StrA, 21474);
                // b = StrToInt(StrA); // ��������� ����� �� ������� ����
                // sum = a + b;  // ������� ����� ���� �����
                // SetWindowText(hStat, IntToStr(sum)); // ������� ��������� �
                // ����������� ����
                if (IsDlgButtonChecked(hwnd, 1) == BST_CHECKED &&
                    GetWindowText(hEdt2, StrA, 21474) != 0 &&
                    GetWindowText(hEdt3, StrA, 21474) != 0) { // encode
                    // Len = GetWindowText(hEdt2, StrA, 21474);
                    // std::wstring wStr = StrA;
                    std::wstring wStr;
                    std::string s;
                    // std::string s = std::string(wStr.begin(), wStr.end());
                    // Len = GetWindowText(hEdt3, StrA, 21474);
                    // std::wstring wStr = StrA;
                    // std::string s = std::string(wStr.begin(), wStr.end());

                    Len = GetWindowText(hEdt2, StrA, 21474);
                    a = StrToInt(StrA); // ��������� ����� �� ������� ����
                    Len = GetWindowText(hEdt3, StrA, 21474);
                    b = StrToInt(StrA); // ��������� ����� �� ������� ����
                    /*if (s.size() != 26 && s.size() != 0) {
                        MessageBox(hwnd,
                                   L"���� ������ ����� ������ � 26 ��������",
                                   L"������", MB_OK | MB_ICONERROR);
                    }*/
                    /*if (s.size() == 26) {*/
                    // Affine_Cipher d{s};
                    Len = GetWindowText(hEdt1, StrA, 21474);
                    wStr = StrA;
                    s = std::string(wStr.begin(), wStr.end());
                    auto qqq = Affine_Cipher::Encrypt(s, a, b, "eng");
                    std::wstring temp;
                    temp = std::wstring(qqq.begin(), qqq.end());
                    LPCWSTR wideString = temp.c_str();
                    SetWindowText(hStat, wideString);
                    //}
                }
                if (IsDlgButtonChecked(hwnd, 2) == BST_CHECKED &&
                    GetWindowText(hEdt2, StrA, 21474) != 0 &&
                    GetWindowText(hEdt3, StrA, 21474) != 0) { // decode
                    /*Len = GetWindowText(hEdt2, StrA, 21474);
                    std::wstring wStr = StrA;
                    std::string s = std::string(wStr.begin(), wStr.end());
                    Substitution_Cipher d{s};
                    Len = GetWindowText(hEdt1, StrA, 21474);
                    wStr = StrA;
                    s = std::string(wStr.begin(), wStr.end());
                    d.setClText(s);
                    auto qqq = d.Decrypt();
                    std::wstring temp;
                    temp = std::wstring(qqq.begin(), qqq.end());
                    LPCWSTR wideString = temp.c_str();
                    SetWindowText(hStat, wideString);*/
                    // Len = GetWindowText(hEdt2, StrA, 21474);
                    // std::wstring wStr = StrA;
                    std::wstring wStr;
                    std::string s;
                    // std::string s = std::string(wStr.begin(), wStr.end());
                    // Len = GetWindowText(hEdt3, StrA, 21474);
                    // std::wstring wStr = StrA;
                    // std::string s = std::string(wStr.begin(), wStr.end());

                    Len = GetWindowText(hEdt2, StrA, 21474);
                    a = StrToInt(StrA); // ��������� ����� �� ������� ����
                    Len = GetWindowText(hEdt3, StrA, 21474);
                    b = StrToInt(StrA); // ��������� ����� �� ������� ����
                    /*if (s.size() != 26 && s.size() != 0) {
                        MessageBox(hwnd,
                                   L"���� ������ ����� ������ � 26 ��������",
                                   L"������", MB_OK | MB_ICONERROR);
                    }*/
                    /*if (s.size() == 26) {*/
                    // Affine_Cipher d{s};
                    Len = GetWindowText(hEdt1, StrA, 21474);
                    wStr = StrA;
                    s = std::string(wStr.begin(), wStr.end());
                    auto qqq = Affine_Cipher::Decrypt(s, a, b, "eng");
                    std::wstring temp;
                    temp = std::wstring(qqq.begin(), qqq.end());
                    LPCWSTR wideString = temp.c_str();
                    SetWindowText(hStat, wideString);
                }
            }
        }
        break;
    case WM_PAINT: // ����������� ����
        hdc = BeginPaint(hwnd, &ps); // ������ �����������
        SetBkColor(hdc, 0x00F0F0F0);
        TextOut(hdc, 50, 20, L"�������� �����:", ARRAYSIZE(L"�������� �����:")); // ���� ��������� ���������
        TextOut(hdc, 50, 110, L"�������� �����:", ARRAYSIZE(L"�������� �����:")); // ����� ��������� ���������
        TextOut(hdc, 50, 220, L"�����:", ARRAYSIZE(L"�����:")); // ����� ��������� ���������
        TextOut(hdc, 30+100+50, 220, L"a", ARRAYSIZE(L"a")); // ����� ��������� ���������
        TextOut(hdc, 30+100+130, 220, L"b", ARRAYSIZE(L"b")); // ����� ��������� ���������
        TextOut(hdc, 50, 380, L"����������:", ARRAYSIZE(L"����������:"));
        EndPaint(hwnd, &ps); // ����� �����������
        break;
    case WM_DESTROY: // �������� ����
        //PostQuitMessage(0);
        break;
    default: // ��������� ��������� �� ���������
        return LONG(DefWindowProc(hwnd, Message, wparam, lparam));
    }
    return 0;
}

// ������� ��������� ���������
LONG WINAPI WndThirdProc(HWND hwnd, UINT Message,
    WPARAM wparam, LPARAM lparam) {
    HDC hdc;
    HINSTANCE hInst;
    PAINTSTRUCT ps;
    HMENU IDC_GRPBUTTONS;
    static HWND hBtn0, hBtn, first; // ���������� ������
    static HWND hEdt1, hEdt2, hEdt3, hEdt4, hEdt5; // ����������� ����� ��������������
    //static HWND hEdt01;
    static std::vector<HWND> hEdt01(26);
    static std::vector<HWND> hEdt02(26);
    static HWND hStat; // ���������� ������������ ������
    TCHAR StrA[21474];
    int a1, a2, b1, b2, sum, Len;
    std::string str;
    std::string strEng = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //std::string strRus = "�����Ũ��������������������������";
    switch (Message) {
    case EN_MAXTEXT:
        SendMessage(hEdt1, EM_SETLIMITTEXT, 2000, 0);
        break;
    case WM_CREATE: // ��������� �������� ����
        hInst = ((LPCREATESTRUCT)lparam)->hInstance; // ���������� ����������
        // ������� � ���������� �������
        /*hBtn0 = CreateWindow(L"button", L"�����������",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            350, 30, 60, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hBtn0, SW_SHOWNORMAL);*/


        //CreateWindow(TEXT("button"), TEXT("Choose colour"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 50, 25, 300, 70, hwnd, (HMENU)0, hInst, NULL);
        //CreateWindow(TEXT("button"), TEXT("Blue"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 70, 50, 75, 30, hwnd, (HMENU)ID_1BUTT, hInst, NULL);

        //DialogBox(hInst,
         //   MAKEINTRESOURCE(HYDRA),
         //   0, DialogProc);


        hBtn0 = CreateWindow(L"button", L"",
            WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
            20, 100, 120, 30, hwnd, (HMENU)0, hInst, NULL);

        CreateWindow(L"button", L"������������",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            200, 100, 150, 30, hwnd, ((HMENU)1), hInst, NULL);

        //CreateWindow(TEXT("button"), TEXT("Red"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 40, 80, 100, 30, hwnd, (HMENU)ID_1BUTT, hInst, NULL);

        CreateWindow(L"button", L"�������������",
            WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
            400, 100, 150, 30, hwnd, (HMENU)2, hInst, NULL);

        ShowWindow(hBtn0, SW_HIDE);
        // ������� � ���������� ������ ���� ��������������
        hEdt1 = CreateWindow(L"edit", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT, 50, 40, 600, 20,
            hwnd, 0, hInst, NULL);
        ShowWindow(hEdt1, SW_SHOWNORMAL);
        // ������� � ���������� ���� �����
        /*hEdt2 = CreateWindow(L"edit", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 50, 240, 600, 20,
            hwnd, 0, hInst, NULL);
        ShowWindow(hEdt2, SW_SHOWNORMAL);*/
        hEdt2 = CreateWindow(L"edit", L"",
                             WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER | ES_LEFT, 100+50,
                             240, 60, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hEdt2, SW_SHOWNORMAL);
        hEdt3 = CreateWindow(L"edit", L"",
                             WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER | ES_LEFT, 100+130,
                             240, 60, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hEdt3, SW_SHOWNORMAL);
        hEdt4 = CreateWindow(L"edit", L"",
                             WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER | ES_LEFT, 100+210,
                             240, 60, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hEdt2, SW_SHOWNORMAL);
        hEdt5 = CreateWindow(L"edit", L"",
                             WS_CHILD | WS_VISIBLE | ES_NUMBER | WS_BORDER | ES_LEFT, 100+290,
                             240, 60, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hEdt3, SW_SHOWNORMAL);

        /*CreateMDIWindow(L"edit", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, 50, 240, 600, 20,
            hwnd, hInst, NULL);*/
        // ������� ����
        /*for (int i = 0; i < 26; i++) {
            hEdt01[i] = CreateWindow(L"static", L"", WS_CHILD | WS_VISIBLE | SS_CENTER,
                50 + i * 50, 240, 40, 20, hwnd, 0, hInst, NULL);
            str = strEng[i];
            SetWindowText(hEdt01[i], (LPCWSTR)str.c_str());
            hEdt02[i] = CreateWindow(L"combobox", L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | WS_VSCROLL, 50+i*50, 270, 40, 40,
                hwnd, (HMENU)(3+i), hInst, NULL);
        }*/
        //LB_ADDSTRING(hEdt22, 'asd');
        //SendMessage(hEdt01, WM_SETREDRAW, FALSE, 0L);
        //SendMessage(hEdt22, CB_ADDSTRING, 0, (LPARAM)(LPSTR)"A");
        //SendMessage(hEdt22, CB_ADDSTRING, 0, (LPARAM)str.c_str());

        /*for (int i = 0; i < streng.length(); i++) {
            str = streng[i];
            sendmessage(hedt02[i], cb_addstring, 0, (lparam)str.c_str());
        }*/

        //SendMessage(hEdt01, WM_SETREDRAW, TRUE, 0L);
        //InvalidateRect(hEdt01, NULL, TRUE);
        //ComboBox_AddItemData();
        //ShowWindow(hEdt22, SW_SHOWNORMAL);
        //if (HIWORD(lparam) == LBN_DBLCLK)
        //{
            //int uSelectedItem;
           // char Buffer[256];

            // ���������� ����� ���������� ������
            //uSelectedItem = (int)SendMessage(hEdt22,
             //   LB_GETCURSEL, 0, 0L);

            // ���� � ������ ���� ���������� ������,
            // ������� �� �� ����� 
           // if (uSelectedItem != LB_ERR)
           // {
                // �������� ���������� ������
            //    SendMessage(hEdt22, LB_GETTEXT,
                //    uSelectedItem, (LPARAM)Buffer);

                // ������� �� �� �����  
              //  MessageBox(hwnd, (LPCWSTR)(LPSTR)Buffer, L"szWindowTitle",
            //        MB_OK);
          //  }
        //}
        // ������� � ���������� ������
        hBtn = CreateWindow(L"button", L"Run",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            700, 395, 120, 30, hwnd, 0, hInst, NULL);
        ShowWindow(hBtn, SW_SHOWNORMAL);
        // ������� � ���������� ���� ������ ��� ����������
        hStat = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER | ES_READONLY,
            50, 400, 600, 20, hwnd, 0, hInst, NULL);
        ShowWindow(hStat, SW_SHOWNORMAL);
        break;
    case WM_COMMAND:  // ��������� � �������
        if (HIWORD(wparam) == BN_CLICKED) {
            //flag = BM_GETSTATE(hBtn0, 0);
            //BS_RADIOBUTTON
            //flag = IsDlgButtonChecked(hwnd, 0);
           // if (IsDlgButtonChecked(hwnd, 1) == BST_CHECKED)
           //     MessageBox(hwnd, L"������� ������", L"������ ����11", MB_OK | MB_ICONERROR);
           // if (IsDlgButtonChecked(hwnd, 2) == BST_CHECKED)
            //    MessageBox(hwnd, L"������� ������", L"������ ����22", MB_OK | MB_ICONERROR);
            //switch (flag) {
            //case 1: // ���� ������������ ��
             //   MessageBox(hwnd, L"������� ������", L"������ ����11", MB_OK | MB_ICONERROR);
               // break;
           // case 2: // ���� ������������� ��
           //     MessageBox(hwnd, L"������� ������", L"������ ����22", MB_OK | MB_ICONERROR);
           //     break;
           // }
            if (lparam == (LPARAM)hBtn) // ���� ������ �� ������
            {
                SetWindowText(hStat, (LPCWSTR)(L""));
                //  if (IsDlgButtonChecked(hwnd, 1) == BST_CHECKED)
                //     MessageBox(hwnd, L"������� ������", L"������ ����1",
                //     MB_OK | MB_ICONERROR);
                //  if (IsDlgButtonChecked(hwnd, 2) == BST_CHECKED)
                //       MessageBox(hwnd, L"������� ������", L"������ ����2",
                //       MB_OK | MB_ICONERROR);
                if (IsDlgButtonChecked(hwnd, 1) == BST_UNCHECKED &&
                    IsDlgButtonChecked(hwnd, 2) == BST_UNCHECKED)
                    MessageBox(hwnd, L"�������� �����", L"������",
                               MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt1, StrA, 21474) == 0)
                    MessageBox(hwnd, L"������� �������� �����", L"������",
                               MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt2, StrA, 21474) == 0)
                    MessageBox(hwnd, L"������� ���� ����� 1", L"������",
                               MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt3, StrA, 21474) == 0)
                    MessageBox(hwnd, L"������� ���� ����� 2", L"������",
                               MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt4, StrA, 21474) == 0)
                    MessageBox(hwnd, L"������� ���� ����� 1", L"������",
                               MB_OK | MB_ICONERROR);
                if (GetWindowText(hEdt5, StrA, 21474) == 0)
                    MessageBox(hwnd, L"������� ���� ����� 2", L"������",
                               MB_OK | MB_ICONERROR);
                // Len = GetWindowText(hEdt1, StrA, 21474);
                // a = StrToInt(StrA); // ��������� ����� �� ������� ����
                // Len = GetWindowText(hEdt2, StrA, 21474);
                // b = StrToInt(StrA); // ��������� ����� �� ������� ����
                // sum = a + b;  // ������� ����� ���� �����
                // SetWindowText(hStat, IntToStr(sum)); // ������� ��������� �
                // ����������� ����
                if (IsDlgButtonChecked(hwnd, 1) == BST_CHECKED &&
                    GetWindowText(hEdt2, StrA, 21474) != 0 &&
                    GetWindowText(hEdt3, StrA, 21474) != 0) { // encode
                    // Len = GetWindowText(hEdt2, StrA, 21474);
                    // std::wstring wStr = StrA;
                    std::wstring wStr;
                    std::string s;
                    // std::string s = std::string(wStr.begin(), wStr.end());
                    // Len = GetWindowText(hEdt3, StrA, 21474);
                    // std::wstring wStr = StrA;
                    // std::string s = std::string(wStr.begin(), wStr.end());

                    Len = GetWindowText(hEdt2, StrA, 21474);
                    a1 = StrToInt(StrA); // ��������� ����� �� ������� ����
                    Len = GetWindowText(hEdt3, StrA, 21474);
                    a2 = StrToInt(StrA); // ��������� ����� �� ������� ����
                    Len = GetWindowText(hEdt4, StrA, 21474);
                    b1 = StrToInt(StrA); // ��������� ����� �� ������� ����
                    Len = GetWindowText(hEdt5, StrA, 21474);
                    b2 = StrToInt(StrA); // ��������� ����� �� ������� ����
                    /*if (s.size() != 26 && s.size() != 0) {
                        MessageBox(hwnd,
                                   L"���� ������ ����� ������ � 26 ��������",
                                   L"������", MB_OK | MB_ICONERROR);
                    }*/
                    /*if (s.size() == 26) {*/
                    // Affine_Cipher d{s};
                    Len = GetWindowText(hEdt1, StrA, 21474);
                    wStr = StrA;
                    s = std::string(wStr.begin(), wStr.end());
                    auto qqq = Recurrent_Affine_Cipher::Encrypt(s, a1, a2, b1, b2, "eng");
                    std::wstring temp;
                    temp = std::wstring(qqq.begin(), qqq.end());
                    LPCWSTR wideString = temp.c_str();
                    SetWindowText(hStat, wideString);
                    //}
                }
                if (IsDlgButtonChecked(hwnd, 2) == BST_CHECKED &&
                    GetWindowText(hEdt2, StrA, 21474) != 0 &&
                    GetWindowText(hEdt3, StrA, 21474) != 0) { // decode
                    /*Len = GetWindowText(hEdt2, StrA, 21474);
                    std::wstring wStr = StrA;
                    std::string s = std::string(wStr.begin(), wStr.end());
                    Substitution_Cipher d{s};
                    Len = GetWindowText(hEdt1, StrA, 21474);
                    wStr = StrA;
                    s = std::string(wStr.begin(), wStr.end());
                    d.setClText(s);
                    auto qqq = d.Decrypt();
                    std::wstring temp;
                    temp = std::wstring(qqq.begin(), qqq.end());
                    LPCWSTR wideString = temp.c_str();
                    SetWindowText(hStat, wideString);*/
                    // Len = GetWindowText(hEdt2, StrA, 21474);
                    // std::wstring wStr = StrA;
                    std::wstring wStr;
                    std::string s;
                    // std::string s = std::string(wStr.begin(), wStr.end());
                    // Len = GetWindowText(hEdt3, StrA, 21474);
                    // std::wstring wStr = StrA;
                    // std::string s = std::string(wStr.begin(), wStr.end());

                    Len = GetWindowText(hEdt2, StrA, 21474);
                    a1 = StrToInt(StrA); // ��������� ����� �� ������� ����
                    Len = GetWindowText(hEdt3, StrA, 21474);
                    a2 = StrToInt(StrA); // ��������� ����� �� ������� ����
                    Len = GetWindowText(hEdt4, StrA, 21474);
                    b1 = StrToInt(StrA); // ��������� ����� �� ������� ����
                    Len = GetWindowText(hEdt5, StrA, 21474);
                    b2 = StrToInt(StrA); // ��������� ����� �� ������� ����
                    /*if (s.size() != 26 && s.size() != 0) {
                        MessageBox(hwnd,
                                   L"���� ������ ����� ������ � 26 ��������",
                                   L"������", MB_OK | MB_ICONERROR);
                    }*/
                    /*if (s.size() == 26) {*/
                    // Affine_Cipher d{s};
                    Len = GetWindowText(hEdt1, StrA, 21474);
                    wStr = StrA;
                    s = std::string(wStr.begin(), wStr.end());
                    auto qqq = Recurrent_Affine_Cipher::Decrypt(s, a1, a2, b1, b2, "eng");
                    std::wstring temp;
                    temp = std::wstring(qqq.begin(), qqq.end());
                    LPCWSTR wideString = temp.c_str();
                    SetWindowText(hStat, wideString);
                }
            }
        }
        break;
    case WM_PAINT: // ����������� ����
        hdc = BeginPaint(hwnd, &ps); // ������ �����������
        SetBkColor(hdc, 0x00F0F0F0);
        TextOut(hdc, 50, 20, L"�������� �����:", ARRAYSIZE(L"�������� �����:")); // ���� ��������� ���������
        TextOut(hdc, 50, 110, L"�������� �����:", ARRAYSIZE(L"�������� �����:")); // ����� ��������� ���������
        TextOut(hdc, 50, 220, L"�����:", ARRAYSIZE(L"�����:")); // ����� ��������� ���������
        TextOut(hdc, 30+100+50, 220, L"a1", ARRAYSIZE(L"a1")); // ����� ��������� ���������
        TextOut(hdc, 30+100+130, 220, L"a2", ARRAYSIZE(L"a2")); // ����� ��������� ���������
        TextOut(hdc, 30+100+210, 220, L"b1", ARRAYSIZE(L"b1")); // ����� ��������� ���������
        TextOut(hdc, 30+100+290, 220, L"b2", ARRAYSIZE(L"b2")); // ����� ��������� ���������
        TextOut(hdc, 50, 380, L"����������:", ARRAYSIZE(L"����������:"));
        EndPaint(hwnd, &ps); // ����� �����������
        break;
    case WM_DESTROY: // �������� ����
        //PostQuitMessage(0);
        break;
    default: // ��������� ��������� �� ���������
        return LONG(DefWindowProc(hwnd, Message, wparam, lparam));
    }
    return 0;
}
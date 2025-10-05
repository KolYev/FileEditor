#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE 4
#define FILE_MENU_SAVE 5
#define FILE_MENU_LOAD 6


LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);

HMENU hMenu;
HWND hEdit;

void LoadFileContent(HWND hEdit) {
    ifstream file("mynote.txt");
    if (file.is_open()) {
        string content;
        string line;
        while (getline(file, line)) {
            content += line + "\n";
        }
        file.close();
        
        int size = MultiByteToWideChar(CP_UTF8, 0, content.c_str(), -1, NULL, 0);
        if (size > 0) {
            wstring wideText(size - 1, L'\0');
            MultiByteToWideChar(CP_UTF8, 0, content.c_str(), -1, &wideText[0], size);
            SetWindowTextW(hEdit, wideText.c_str());
        }
    } else {
        SetWindowTextW(hEdit, L"...");
    }
}


LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (wp)
        {
            case FILE_MENU_EXIT:
                DestroyWindow(hWnd);
                return 0;
            case FILE_MENU_NEW:
                MessageBeep(MB_ICONINFORMATION);
                return 0;
            case CHANGE_TITLE:
                wchar_t text[100];
                GetWindowTextW(hEdit, text, 100);
                SetWindowTextW(hWnd, text);
                return 0;
            case FILE_MENU_SAVE:
            {
                wchar_t text[1000];
                GetWindowTextW(hEdit, text, 1000);


                ofstream file("mynote.txt");
                char narrowText[1000];
                WideCharToMultiByte(CP_UTF8, 0, text, -1, narrowText, 1000, NULL, NULL);
                file << narrowText;
                file.close();

                MessageBoxW(hWnd, L"File Saved!", L"Success", MB_OK);
                return 0;
            }
            case FILE_MENU_LOAD:
            {
                ifstream file("mynote.txt");
                if (file.is_open()) {
                    string content;
                    string line;
                    while (getline(file, line)) {
                        content += line + "\n";
                    }
                    file.close();
                    
                    wchar_t wideText[1000];
                    MultiByteToWideChar(CP_UTF8, 0, content.c_str(), -1, wideText, 1000);
                    SetWindowTextW(hEdit, wideText);
                    
                    MessageBoxW(hWnd, L"File is uploaded!", L"Успех", MB_OK);
                } else {
                    MessageBoxW(hWnd, L"File not found!", L"Ошибка", MB_OK);
                }
                return 0;
            }
        }
        return 0;
    case WM_CREATE:
        AddMenus(hWnd);
        AddControls(hWnd);
        LoadFileContent(hEdit);
        return 0;
    case WM_DESTROY:
       PostQuitMessage(0);
       return 0;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING, CHANGE_TITLE, TEXT("Change Title"));


    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, TEXT("New"));
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, TEXT("Open SubMenu"));
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_SAVE, TEXT("Save to File"));
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_LOAD, TEXT("Load from File"));
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, TEXT("Exit"));

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, TEXT("File"));
    AppendMenu(hMenu, MF_STRING, 1002, TEXT("Help"));

    SetMenu(hWnd, hMenu);

}

void AddControls(HWND hWnd)
{
    CreateWindowW(L"static", L"Enter Text Here: ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 200, 100, 1000, 50, hWnd,
                NULL, NULL, NULL);

    hEdit = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 200, 152, 1000, 500, hWnd,
    NULL, NULL, NULL);
}

int CreateAndShowWindow(HINSTANCE hInst, int nCmdShow)
{
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass", L"My Window with File Operations", 
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 1500, 1000,
                  NULL, NULL, NULL, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}
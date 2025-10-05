#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>


#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE 4
#define FILE_MENU_SAVE 5
#define FILE_MENU_LOAD 6

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);
void AddControls(HWND);
void LoadFileContent(HWND hEdit);
int CreateAndShowWindow(HINSTANCE hInstance, int nCmdShow);

extern HMENU hMenu;
extern HWND hEdit;

#endif
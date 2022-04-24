#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <tchar.h>
#include <wtypes.h>
#include <string.h>
using namespace std;

// Notepad-Clone by Toni Valverde | tovape.github.io

// Menu and Submenu

// File
#define FILE_MENU_NEW 1
#define FILE_MENU_NEWINDOW 2
#define FILE_MENU_OPEN 3
#define FILE_MENU_SAVE 4
#define FILE_MENU_SAVEAS 5
#define FILE_MENU_CONFIGPAGE 6
#define FILE_MENU_PRINT 7
#define FILE_MENU_EXIT 8

// Edition
#define EDITION_UNDO 9
#define EDITION_CUT 10
#define EDITION_COPY 11
#define EDITION_PASTE 12
#define EDITION_DELETE 13
#define EDITION_SEARCHBING 14
#define EDITION_SEARCH 15
#define EDITION_SEARCHNEXT 16
#define EDITION_SEARCHPREV 17
#define EDITION_REPLACE 18
#define EDITION_GOTO 19
#define EDITION_SELECTALL 20
#define EDITION_TIMEDATE 21

// Format
#define FORMAT_LINESETTING 22
#define FORMAT_FONT 23
#define FORMAT_FONT_LIST 31
#define FORMAT_FONT_STYLE 32
#define FORMAT_FONT_SIZE 33
#define FORMAT_FONT_CANCEL 34
#define FORMAT_FONT_APPLY 35

// View
#define VIEW_ZOOMIN 24
#define VIEW_ZOOMOUT 25
#define VIEW_ZOOMDEF 26
#define VIEW_STATUS 27

// Help
#define HELP_VIEW 28
#define HELP_SUGGESTION 29
#define HELP_ABOUT 30

// Including Files

#include "functions.cpp"

// Prototypes
LRESULT CALLBACK windowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddMenu(HWND, HWND);
void AddContent(HWND, HWND);
void ClassDialogFont(HINSTANCE);
void CreateDialogFont(HWND, int, int, HFONT, HWND, HWND, HWND);

// Global Variables
HANDLE hLogo;
RECT rWindow;
HMENU hMenu;
HWND hMainwindow,hEditor;
HFONT hDefaultFont = CreateFont(0,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,FALSE,CLEARTYPE_QUALITY,FALSE,TEXT("Consolas"));
HFONT hSecundaryFont = CreateFont(0,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,FALSE,CLEARTYPE_QUALITY,FALSE,TEXT("Segoe UI"));
HWND hApplyFont;
HWND hFontList, hFontStyle, hFontSize;
HBITMAP notepadImage, windowsImage;
int screenWidth = 0;
int screenHeight = 0;

// Main Windows
int WINAPI WinMain(HINSTANCE mainWindow, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
  SetConsoleTitleA("Debugger");

  WNDCLASSW windowClass = {0};
  windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
  windowClass.hCursor = LoadCursor(NULL, IDC_IBEAM);
  windowClass.hInstance = mainWindow;
  windowClass.lpszClassName = L"mainWindow";
  windowClass.lpfnWndProc = windowProcedure;
  windowClass.hIcon = NULL;
  if (!RegisterClassW(&windowClass)) {
    cout << "Error Registing Class\n";
    return 1;
  }

  // Loading Child Dialogs
  ClassDialogFont(mainWindow);

  screenWidth = GetSystemMetrics(SM_CXSCREEN);
  screenHeight = GetSystemMetrics(SM_CYSCREEN);
  cout << "Screen resolution: " << screenWidth << "x" << screenHeight << "\n";

  //Create Main Window
  hMainwindow = CreateWindowW(L"mainWindow", L"Null", WS_OVERLAPPEDWINDOW | WS_VISIBLE,(screenWidth-500)/2,(screenHeight-500)/2,700,500,NULL,NULL,NULL,NULL);

  MSG msg = {0};

  while(GetMessage(&msg,NULL,NULL,NULL)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

// Main Windows Handling

LRESULT CALLBACK windowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

  switch (msg) {
    default:
      return DefWindowProcW(hWnd,msg,wp,lp);
    case WM_NCCREATE:
      // Load Menu
      AddMenu(hWnd,hMenu);
      //AddContent(hWnd,hEditor);
      // Add Content
      hEditor = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 0, 0, hWnd, NULL, NULL, NULL);
      // Set Window Title
      SetWindowTextW(hWnd, L"Notepad");
      // Load Icon
      hLogo = LoadImage(0, _T("notepad.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
      if (hLogo) {
        SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM) hLogo);
      }
      // Set Editor Default Font
      cout << "Setting Default Font\n";
      SendMessage(hEditor, WM_SETFONT, (WPARAM)hDefaultFont, TRUE);

      cout << "Window Created\n";
      break;
    case WM_SIZE:
      // Resize Editor Window
      if (GetWindowRect(hWnd, &rWindow)) {
        int width = rWindow.right - rWindow.left;
        int height = rWindow.bottom - rWindow.top;
        cout << "Width: " << width << " | Height: " << height << "\n";
        MoveWindow(hEditor,0,0,width-17,height-60,1);
      }
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      cout << "Window Closed\n";
      break;
    // Menu Items Behaviour
    case WM_COMMAND:
      switch(wp) {
        case FILE_MENU_NEW:
          cout << "File Menu New\n";
          break;
        case FILE_MENU_EXIT:
          cout << "File Menu Exit\n";
          DestroyWindow(hWnd);
          break;
        case FORMAT_FONT:
          cout << "Format Font\n";
          CreateDialogFont(hWnd, screenWidth, screenHeight, hSecundaryFont, hFontList, hFontStyle, hFontSize);
          break;
      }
  }
}

// Font Windows Handling

LRESULT CALLBACK DialogFontProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
  int indexFont, indexStyle, indexSize, indexScript;
  char bufferFontList[64], bufferFontStyle[64], bufferFontSize[64], bufferFontScript[64];
  switch(msg) {
    case WM_COMMAND:
      switch(LOWORD(wp)) {
          case FORMAT_FONT_LIST:
            switch(HIWORD(wp)) {
              case LBN_SELCHANGE:
                indexFont = SendMessage((HWND)lp, LB_GETCARETINDEX, 0, 0);
                SendMessage((HWND)lp, LB_GETTEXT, (LPARAM)indexFont, (WPARAM)bufferFontList);
                cout << bufferFontList << " font selected" << " | Font ID: " << indexFont << "\n";
                break;
            }
            break;
          case FORMAT_FONT_STYLE:
            switch(HIWORD(wp)) {
              case LBN_SELCHANGE:
                indexStyle = SendMessage((HWND)lp, LB_GETCARETINDEX, 0, 0);
                SendMessage((HWND)lp, LB_GETTEXT, (LPARAM)indexStyle, (WPARAM)bufferFontStyle);
                cout << bufferFontStyle << " style selected" << " | Style ID: " << indexStyle << "\n";
                break;
            }
            break;
          case FORMAT_FONT_SIZE:
            switch(HIWORD(wp)) {
              indexSize = SendMessage((HWND)lp, LB_GETCARETINDEX, 0, 0);
              SendMessage((HWND)lp, LB_GETITEMDATA, (LPARAM)indexSize, (WPARAM)bufferFontStyle);
              cout << bufferFontStyle << " size selected" << " | Size ID: " << indexSize << "\n";
              break;
            }
            break;
          case FORMAT_FONT_CANCEL:
            EnableWindow(hMainwindow, true);
            DestroyWindow(hWnd);
            break;
          case FORMAT_FONT_APPLY:
            break;
      }
      break;
    case WM_CREATE:
      cout << "Font Dialog Created\n";
      // Set Window Title
      SetWindowTextW(hWnd, L"Font");
      break;
    case WM_DESTROY:
      EnableWindow(hMainwindow, true);
      DestroyWindow(hWnd);
      break;
    default:
      return DefWindowProcW(hWnd, msg, wp, lp);
  }
}

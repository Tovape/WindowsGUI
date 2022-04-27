#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <tchar.h>
#include <wtypes.h>
#include <string.h>

// Prototypes
LRESULT CALLBACK DialogFontProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK DialogAboutProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

// Variables
string globalPathWindow = "";
string globalPath = "";

// Creating Menu Bars
void AddMenu(HWND hWnd, HMENU hMenu) {

  // Menus
  hMenu = CreateMenu();
  HMENU hFileMenu = CreateMenu();
  HMENU hEditionMenu = CreateMenu();
  HMENU hFormatMenu = CreateMenu();
  HMENU hViewMenu = CreateMenu();
  HMENU hHelpMenu = CreateMenu();

  // Appending Menu Content

  // File
  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_NEW, "&New\tCtrl+N");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_NEWINDOW, "&New Window\tCtrl+S");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_OPEN, "&Open\tCtrl+May+N");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_SAVE, "&Save\tCtrl+G");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_SAVEAS, "&Save As\tCtrl+May+S");
  AppendMenu(hFileMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hFileMenu, MF_STRING, FILE_MENU_CONFIGPAGE, "Configure Page");
  AppendMenu(hFileMenu, MF_STRING | MF_ENABLED, FILE_MENU_PRINT, "&Print\tCtrl+P");
  AppendMenu(hFileMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

  // Edition
  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditionMenu, "Edition");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_UNDO, "&Undo\tCtrl+Z");
  AppendMenu(hEditionMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_CUT, "&Cut\tCtrl+X");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_COPY, "&Copy\tCtrl+C");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_PASTE, "&Paste\tCtrl+P");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_DELETE, "&Delete\tSupr");
  AppendMenu(hEditionMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_SEARCHBING, "&Search with Bing\tCtrl+F");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_SEARCH, "&Search\tCtrl+B");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_SEARCHNEXT, "&Search Next\tF3");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_SEARCHPREV, "&Search Previous\tMay+F3");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_REPLACE, "&Replace\tCtrl+R");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_GOTO, "&Go To\tCtrl+T");
  AppendMenu(hEditionMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_SELECTALL, "&Select All\tCtrl+E");
  AppendMenu(hEditionMenu, MF_STRING | MF_ENABLED, EDITION_TIMEDATE, "&Time & Date\tF5");

  // Format
  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFormatMenu, "Format");
  AppendMenu(hFormatMenu, MF_STRING, FORMAT_LINESETTING, "Line Settings");
  AppendMenu(hFormatMenu, MF_STRING, FORMAT_FONT, "Font");

  // View

  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hViewMenu, "View");

  HMENU hViewSubmenu = CreateMenu();
  AppendMenu(hViewSubmenu, MF_STRING | MF_ENABLED, VIEW_ZOOMIN, "&Zoom In\tCtrl++");
  AppendMenu(hViewSubmenu, MF_STRING | MF_ENABLED, VIEW_ZOOMOUT, "&Zoom Out\tCtrl+-");
  AppendMenu(hViewSubmenu, MF_STRING | MF_ENABLED, VIEW_ZOOMDEF, "&Restore Zoom\tCtrl+0");
  AppendMenu(hViewMenu, MF_STRING, (UINT_PTR)hViewSubmenu, "Zoom");
  AppendMenu(hViewMenu, MF_STRING, VIEW_STATUS, "Status Bar");

  // Help
  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");
  AppendMenu(hHelpMenu, MF_STRING, HELP_VIEW, "View Help");
  AppendMenu(hHelpMenu, MF_STRING, HELP_SUGGESTION, "Send Suggestion");
  AppendMenu(hHelpMenu, MF_SEPARATOR,NULL,NULL);
  AppendMenu(hHelpMenu, MF_STRING, HELP_ABOUT, "About Notepad-Clone");

  SetMenu(hWnd,hMenu);
}

// Adding Items - Inoperative
/*
void AddContent(HWND hWnd, HWND hEditor) {
  // Scroll Bar width is 17
  //hEditor = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 683, 440, hWnd, NULL, NULL, NULL);
}
*/

// Font Dialog Box
void ClassDialogFont(HINSTANCE mainWindow) {

  WNDCLASSW fontClass = {0};
  fontClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
  fontClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  fontClass.hInstance = mainWindow;
  fontClass.lpszClassName = L"fontDialog";
  fontClass.lpfnWndProc = DialogFontProcedure;

  RegisterClassW(&fontClass);

}

void ClassDialogAbout(HINSTANCE mainWindow) {

  WNDCLASSW aboutClass = {0};
  aboutClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
  aboutClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  aboutClass.hInstance = mainWindow;
  aboutClass.lpszClassName = L"aboutDialog";
  aboutClass.lpfnWndProc = DialogAboutProcedure;

  RegisterClassW(&aboutClass);

}

struct FontsStruct {
    TCHAR fontName[64];
};

FontsStruct fontList[] =
{
    {TEXT("Consolas")},
    {TEXT("Courier")},
    {TEXT("Verdana")}
};

struct StyleStruct {
    TCHAR fontStyle[64];
};

StyleStruct styleList[] =
{
    {TEXT("Normal")},
    {TEXT("Cursive")},
    {TEXT("Bold")},
    {TEXT("Italic")}
};

struct SizesStruct {
    TCHAR fontSize[64];
};

SizesStruct sizesList[] =
{
    {TEXT("8")},
    {TEXT("10")},
    {TEXT("12")}
};

void CreateDialogAbout(HWND hWnd, int screenWidth, int screenHeight, HBITMAP bWindowsImage, HBITMAP bNotepadImage, HWND hWindowsImage, HWND hNotepadImage) {
  bWindowsImage = (HBITMAP)LoadImageW(NULL, L"windows.bmp", IMAGE_BITMAP, 200, 60, LR_LOADFROMFILE);
  bNotepadImage = (HBITMAP)LoadImageW(NULL, L"notepad.bmp", IMAGE_BITMAP, 40, 40, LR_LOADFROMFILE);

  HWND haboutDialog = CreateWindowW(L"aboutDialog", L"", WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU, (screenWidth-500)/2, (screenHeight-500)/2, 500, 300, hWnd, NULL, NULL, NULL);

  hWindowsImage = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 150, 10, 200, 60, haboutDialog, NULL, NULL, NULL);
  SendMessageW(hWindowsImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bWindowsImage);
  hNotepadImage = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 20, 80, 50, 50, haboutDialog, NULL, NULL, NULL);
  SendMessageW(hNotepadImage, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) bNotepadImage);
  CreateWindowW(L"static", L"Microsoft Windows 2022 (R)\nNotepad Clone by Toni Valverde\ntovape.github.io", WS_VISIBLE | WS_CHILD, 100, 80, 380, 100, haboutDialog, NULL, NULL, NULL);

  CreateWindowW(L"Button", L"Accept", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_DEFPUSHBUTTON | BS_FLAT, 410, 236, 80, 30, haboutDialog, (HMENU)HELP_ABOUT_ACCEPT, NULL, NULL);

  EnableWindow(hWnd, false);
}

void CreateDialogFont(HWND hWnd, int screenWidth, int screenHeight, HFONT hSecundaryFont, HWND hFontList, HWND hFontStyle, HWND hFontSize) {

  HWND hfontDialog = CreateWindowW(L"fontDialog", L"", WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU, (screenWidth-500)/2, (screenHeight-500)/2, 400, 500, hWnd, NULL, NULL, NULL);
  SetWindowLong(hfontDialog, GWL_STYLE,GetWindowLong(hfontDialog, GWL_STYLE) & ~WS_MINIMIZEBOX & ~WS_MAXIMIZEBOX);

  // Adding Content
  CreateWindowW(L"static", L"Font:", WS_VISIBLE | WS_CHILD, 10, 10, 160, 20, hfontDialog, NULL, NULL, NULL);
  CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 34, 160, 20, hfontDialog, NULL, NULL, NULL);
  hFontList = CreateWindowW(L"listbox", NULL, WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | LBS_STANDARD | LBS_NOTIFY, 10, 64, 160, 100, hfontDialog, (HMENU)FORMAT_FONT_LIST, NULL, NULL);

  CreateWindowW(L"static", L"Style:", WS_VISIBLE | WS_CHILD, 180, 10, 120, 20, hfontDialog, NULL, NULL, NULL);
  CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 180, 34, 120, 20, hfontDialog, NULL, NULL, NULL);
  hFontStyle = CreateWindowW(L"listbox", NULL, WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | LBS_STANDARD | LBS_NOTIFY, 180, 64, 120, 100, hfontDialog, (HMENU)FORMAT_FONT_STYLE, NULL, NULL);

  CreateWindowW(L"static", L"Size:", WS_VISIBLE | WS_CHILD, 310, 10, 70, 20, hfontDialog, NULL, NULL, NULL);
  CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 310, 34, 70, 20, hfontDialog, NULL, NULL, NULL);
  hFontSize = CreateWindowW(L"listbox", NULL, WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | LBS_STANDARD | LBS_NOTIFY, 310, 64, 70, 100, hfontDialog, (HMENU)FORMAT_FONT_SIZE, NULL, NULL);

  CreateWindowW(L"Button", L"Accept", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_DEFPUSHBUTTON | BS_FLAT, 210, 430, 80, 30, hfontDialog, (HMENU)FORMAT_FONT_APPLY, NULL, NULL);
  CreateWindowW(L"Button", L"Cancel", WS_VISIBLE | WS_CHILD | SS_CENTER | BS_FLAT, 300, 430, 80, 30, hfontDialog, (HMENU)FORMAT_FONT_CANCEL, NULL, NULL);

  // Adding Items in the Font List
  int fontListArray = sizeof(fontList)/sizeof(fontList[0]);
  cout << fontListArray << " Fonts Added\n";
  for (int i = 0; i < fontListArray; i++) {
    int pos = (int)SendMessage(hFontList, LB_ADDSTRING, 0, (LPARAM) fontList[i].fontName);
    SendMessage(hFontList, LB_SETITEMDATA, pos, (LPARAM) i);
  }

  // Adding Items in the Style List
  int fontStyleArray = sizeof(fontList)/sizeof(styleList[0]);
  cout << fontStyleArray << " Styles Added\n";
  for (int i = 0; i < fontStyleArray; i++) {
    int pos = (int)SendMessage(hFontStyle, LB_ADDSTRING, 0, (LPARAM) styleList[i].fontStyle);
    SendMessage(hFontStyle, LB_SETITEMDATA, pos, (LPARAM) i);
  }

  // Adding Items in the Size List
  int fontSizeArray = sizeof(fontList)/sizeof(sizesList[0]);
  cout << fontSizeArray << " Sizes Added\n";
  for (int i = 0; i < fontSizeArray; i++) {
    int pos = (int)SendMessage(hFontSize, LB_ADDSTRING, 0, (LPARAM) sizesList[i].fontSize);
    SendMessage(hFontSize, LB_SETITEMDATA, pos, (LPARAM) i);
  }

  SetFocus(hFontList);
  SetFocus(hFontStyle);
  SetFocus(hFontSize);

  //CreateWindowW(L"combobox", L"Dropdown?", WS_VISIBLE | WS_CHILD, 20, 20, 198, 20, hfontDialog, NULL, NULL, NULL);

  // Setting Font
  //SendMessage(hApplyFont, WM_SETFONT, (WPARAM)hSecundaryFont, TRUE);

  EnableWindow(hWnd, false);
}

// Display File

void DisplayFile(char* path, HWND hEditor) {
  FILE *file;
  file = fopen(path,"r");
  fseek(file,0,SEEK_END);
  int filesize = ftell(file);
  rewind(file);
  char *data = new char[filesize+1];
  fread(data,filesize,1,file);
  data[filesize] = '\0';

  SetWindowText(hEditor,data);

  fclose(file);
}

// Open File

void OpenFile(HWND hWnd, HWND hEditor) {
  cout << "Open File\n";

  char filename[100];

  OPENFILENAME ofn;
  ZeroMemory(&ofn,sizeof(OPENFILENAME));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = hWnd;
  ofn.lpstrFile = filename;
  ofn.lpstrFile[0] = '\0';
  ofn.nMaxFile = 100;
  // This will filter the files in the explorer (Open extensions)
  ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.txt\0";
  ofn.nFilterIndex = 1;

  GetOpenFileName(&ofn);

  // Path of the file
  cout << ofn.lpstrFile << "\n";
  globalPath = ofn.lpstrFile;
  globalPathWindow = ofn.lpstrFile;

  // Setting New Window Name
  globalPathWindow = "Notepad - " + globalPathWindow;

  wstring globalPathWide = wstring(globalPathWindow.begin(), globalPathWindow.end());
  const wchar_t* globalPathTide = globalPathWide.c_str();

  SetWindowTextW(hWnd, TEXT(globalPathTide));

  DisplayFile(ofn.lpstrFile, hEditor);
}

// Write File

void WriteFile(char* path, HWND hEditor) {
  FILE *file;
  file = fopen(path,"w");

  int filesize = GetWindowTextLength(hEditor);
  char *data = new char[filesize+1];
  GetWindowText(hEditor,data,filesize+1);

  fwrite(data,filesize+1,1,file);
  fclose(file);
}

// Save As File

void SaveAsFile(HWND hWnd, HWND hEditor) {
  cout << "Saving File\n";

  char filename[100];

  OPENFILENAME ofn;
  ZeroMemory(&ofn,sizeof(OPENFILENAME));

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = hWnd;
  ofn.lpstrFile = filename;
  ofn.lpstrFile[0] = '\0';
  ofn.nMaxFile = 100;
  // This will filter the files in the explorer (Open extensions)
  ofn.lpstrFilter = "All Files\0*.*\0Text Files\0*.txt\0";
  ofn.nFilterIndex = 1;

  GetSaveFileName(&ofn);

  // Path of the file
  cout << ofn.lpstrFile << "\n";

  WriteFile(ofn.lpstrFile, hEditor);
}

// Save File

void SaveFile(HWND hWnd, HWND hEditor) {
  OPENFILENAME ofn;

  int globalPathSize = globalPath.length();
  char filename[globalPathSize + 1];
  strcpy(filename, globalPath.c_str());
  ofn.lpstrFile = filename;
  ofn.hwndOwner = hWnd;
  cout << ofn.lpstrFile << "\n";

  WriteFile(ofn.lpstrFile, hEditor);
}

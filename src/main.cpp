#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iterator>
#include <windows.h>
#include <shobjidl.h>
#include <objbase.h>
#include "FRONTEND_P20241023_TEXTEDIT.h"
#include "FRONTEND_P20241023_TEXTEDIT_EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT_Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT_Slider.h"
#include "FRONTEND_P20241023_TEXTEDIT_Text.h"
#include "FRONTEND_P20241023_TEXTEDIT_MarkedText.h"
#include "Editor.h"


//#define _WIN32_WINNT 0x0600 

#ifndef UNICODE
#define UNICODE
#endif 

#define NTDDI_VERSION 0x0A000006 //NTDDI_WIN10_RS5
#define _WIN32_WINNT 0x0A00

/*
TODO:
	Umlaute
	...
*/

//Set ld flags in mingw in order to compile this. See Stackoverflow
//CPP-Reference:
std::string print_wide(const wchar_t* wstr) {
    std::mbstate_t state = std::mbstate_t();
    std::size_t len = 1 + std::wcsrtombs(nullptr, &wstr, 0, &state);
    std::vector<char> mbstr(len);
    std::wcsrtombs(&mbstr[0], &wstr, mbstr.size(), &state);
    //std::cout << &mbstr[0] << std::endl;
    return std::string(mbstr.begin(), mbstr.end());
}

//Win32 API - Stackoverflow:

std::string fileDialogWinApi() {
	std::string s1;
	s1 = "C:\\Users\\marku\\OneDrive\\Dokumente\\privat\\Projects\\SovieditorV2.0\\prevver\\mainTest.cpp";
/*
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr)) {
        IFileOpenDialog* pFileOpen;

        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
        // if object created ( that's com object )
        if (SUCCEEDED(hr)) {
            hr = pFileOpen->Show(NULL);

            if (SUCCEEDED(hr)) {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr)){
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    if (SUCCEEDED(hr)) {
                        //MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        s1 = print_wide(pszFilePath);
                        CoTaskMemFree(pszFilePath);

                        std::string stringtoconvert;

                        std::wstring temp = std::wstring(stringtoconvert.begin(), stringtoconvert.end());
                        LPCWSTR lpcwstr = temp.c_str();
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }    */
    return s1;
}

int main(int argc, char *argv[]) {
	std::string path1 = "";

	if(argc == 2) {
		path1 = std::string(argv[1]);
	}

	FRONTEND_P20241023_TEXTEDIT::EditorMouse m_t;
	FRONTEND_P20241023_TEXTEDIT::Text s_t;
	FRONTEND_P20241023_TEXTEDIT::MarkedText cursor_MT;
	FRONTEND_P20241023_TEXTEDIT::Cursor s_c(cursor_MT);
	FRONTEND_P20241023_TEXTEDIT::Slider slider_t(1200 - 10, 0);

	Editor editor(s_t, s_c, slider_t, m_t);
	
	s_t.loadText();
	s_c.loadCursor(editor, s_t);

	//editor.setTextObj(s_t);
	//editor.setCursorObj(s_c);
	//editor.setSliderObj(slider_t);
	//editor.loadMouse(m_t);
	editor.loadEditor(path1);
}

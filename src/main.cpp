#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iterator>/*
#include "FRONTEND_P20241023_TEXTEDIT.h"
#include "FRONTEND_P20241023_TEXTEDIT_EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT_Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT_Slider.h"
#include "FRONTEND_P20241023_TEXTEDIT_Text.h"
#include "FRONTEND_P20241023_TEXTEDIT_MarkedText.h"*/
#include "Editor.h"

/*
TODO:
	Umlaute
	...
*/

//Set ld flags in mingw in order to compile this. See Stackoverflow
//CPP-Reference:

//Win32 API - Stackoverflow:

int main(int argc, char *argv[]) {
	std::string path1 = "";

	if(argc == 2) {
		path1 = std::string(argv[1]);
	}

	Editor editor;
	FRONTEND_P20241023_TEXTEDIT::EditorMouse m_t;
	FRONTEND_P20241023_TEXTEDIT::Text s_t;
	FRONTEND_P20241023_TEXTEDIT::MarkedText cursor_MT;
	FRONTEND_P20241023_TEXTEDIT::Cursor s_c(cursor_MT);
	FRONTEND_P20241023_TEXTEDIT::Slider slider_t(editor.wGetSize().x - 10, 0);

	//Editor editor(s_t, s_c, slider_t, m_t);
	
	s_t.loadText();
	s_c.loadCursor(editor, s_t);

	editor.setTextObj(s_t);
	editor.setCursorObj(s_c);
	editor.setSliderObj(slider_t);
	editor.loadMouse(m_t);
	editor.loadEditor(path1);
}

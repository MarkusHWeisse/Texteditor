#pragma once
#ifndef FRONTEND_P20241023_TEXTEDIT_H
#define FRONTEND_P20241023_TEXTEDIT_H

namespace FRONTEND_P20241023_TEXTEDIT {
	
	struct string_to_display {
		std::string str;
		bool highlight;
		int stdLength;
	};

	struct TextWidths {
		int charWidth;
		int tabWidth;
		int textWidth;
	};

	struct cursorPosition {
		int lineNr;
		int posX;
		int posY;

		cursorPosition() {

		}

		cursorPosition(int lineNr, int posX, int posY) {
			this->lineNr = lineNr;
			this->posX = posX;
			this->posY = posY;
		}
	};
		
	/*
	class EditorMouse;
		
	class MarkedText;
		
	class Slider;
		
	class Cursor;
		
	class Text;
	*/
}
	
#endif
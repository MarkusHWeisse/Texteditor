#ifndef FRONTEND_P20241023_TEXTEDIT_MarkedText
#define FRONTEND_P20241023_TEXTEDIT_MarkedText

#include "FRONTEND_P20241023_TEXTEDIT.h"
//#include "Editor.h"

class Editor;
namespace FRONTEND_P20241023_TEXTEDIT {
	class Cursor;
	class Slider;
	class Text;
	
	class MarkedText {
	FRONTEND_P20241023_TEXTEDIT::cursorPosition cp1;
	FRONTEND_P20241023_TEXTEDIT::cursorPosition cp2;
	bool isActive;
	sf::RectangleShape rs;

public:
	MarkedText() {
		
	}	

	MarkedText(FRONTEND_P20241023_TEXTEDIT::cursorPosition &cp1, FRONTEND_P20241023_TEXTEDIT::cursorPosition &cp2) {
		this->cp1 = cp1;
		this->cp2 = cp2;
		isActive = true;
	}

	std::string getString(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	cursorPosition setString(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, std::string stringToInsert);
	cursorPosition deleteString(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	void drawMarkedText(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::RenderWindow &window);
	void drawRectangle(sf::RenderWindow &window, int posX, int posY, int width, int height);
	void checkOrientation();

	void setCursorPositionOne(FRONTEND_P20241023_TEXTEDIT::cursorPosition &cp1) {
		this->cp1 = cp1;
	}

	void setCursorPositionTwo(FRONTEND_P20241023_TEXTEDIT::cursorPosition &cp2) {
		this->cp2 = cp2;
	}

	void setActive() {
		isActive = true;
	}

	void unsetActive() {
		isActive = false;
	}

	bool getActive() {
		return isActive;
	}
};}

#endif
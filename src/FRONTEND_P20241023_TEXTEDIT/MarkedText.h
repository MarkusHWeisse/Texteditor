#pragma once
#ifndef FRONTEND_P20241023_TEXTEDIT_MarkedText
#define FRONTEND_P20241023_TEXTEDIT_MarkedText

#include <SFML/Graphics.hpp>
#include "FRONTEND_P20241023_TEXTEDIT.h"

class Editor;
 namespace FRONTEND_P20241023_TEXTEDIT {
	class Cursor;
	class Slider;
	class Text;
	
	struct cursorPosition;
	
	class MarkedText {
	cursorPosition cp1;
	cursorPosition cp2;
	bool isActive;
	sf::RectangleShape rs;

public:
	MarkedText() {
		
	}	

	MarkedText(cursorPosition cp1, cursorPosition cp2);

	std::string getString(Editor &editor, Cursor &cursor, Text &text);
	//cursorPosition setString(Editor &editor, Cursor &cursor, Text &text, std::string stringToInsert);
	cursorPosition deleteString(Editor &editor, Cursor &cursor, Text &text);
	void drawMarkedText(Editor &editor, Text &text, sf::RenderWindow &window);
	void drawRectangle(sf::RenderWindow &window, int posX, int posY, int width, int height);
	void checkOrientation();

	void setCursorPositionOne(cursorPosition &cp1);

	void setCursorPositionTwo(cursorPosition &cp2);

	void setActive();

	void unsetActive();

	bool getActive();
	
};}

#endif
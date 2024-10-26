#pragma once
#ifndef FRONTEND_P20241023_TEXTEDIT_Cursor
#define FRONTEND_P20241023_TEXTEDIT_Cursor

#include <SFML/Graphics.hpp>
#include "MarkedText.h"

class Editor;
namespace FRONTEND_P20241023_TEXTEDIT {
	class Text;
	class MarkedText;
	class Slider;
	class EditorMouse;

	class Cursor {
private:	
	int textMovingWhileMarkingSet;
	int posY;
	int posX;
	int cursorLineNr;
	int cursorBlink;
	int cursorShow;
	int posXAtClick;
	int lineNrAtClick;
	int posYAtClick;
	int textMovingWhileMarkingSpeed;
	sf::RectangleShape cursorDraw;
	sf::RectangleShape cursorBackground;
	MarkedText MT;

public:

	Cursor() {
		
	}	
	
	Cursor(MarkedText MT);

	void loadEvents(Editor &editor, sf::Event &event, Text &text);

	void loadDraw(Editor &editor, Text &text, sf::RenderWindow &window);

	void loadCursor(Editor &editor, Text &text);

	void loadVars(Editor &editor);

	void setCursorRects(Editor &editor, Text &text);

	bool cursorLeft(Editor &editor, Text &text);

	bool cursorRight(Editor &editor, Text &text);

	bool cursorUp(Editor &editor, Text &text);

	bool cursorDown(Editor &editor, Text &text);

	bool cursorSimpleBackspace(Editor &editor, Text &text);

	bool cursorMTBackspace(Editor &editor, Text &text);

	bool cursorBackspace(Editor &editor, Text &text);

	bool cursorEnter(Editor &editor, Text &text);

	bool cursorU(Editor &editor, Text &text);

	bool cursorD(Editor &editor, Text &text);

	void cursorMouseEvent(Editor &editor, Text &text, sf::Event &event, sf::Vector2i &mcords);

	void cursorMouseMarking(Editor &editor, Text &text, sf::Vector2i &mcords);

	void cursorMouseEventRecognition(Editor &editor, Text &text, sf::Vector2i &mcords);

	bool checkMouseInWindowBounds(sf::Vector2i &mcords, int screenPosX, int screenPosY, int screenWidth, int screenHeight);

	void setMousePosToCursorPos(Editor &editor, Text &text, sf::Vector2i &mcords);

	void setMousePosYToLine(Text &text, sf::Vector2i &mcords);

	int getMousePosYToLineNr(int mousePosY, int fontSize, int topSpace);

	int setMousePosXToCursorX(Editor &editor, Text &text, sf::Vector2i &mcords, int lineNr);

	int setMousePosXToCursorPosXValues(Editor &editor, Text &text, int charSize, int charSizeBef, sf::Vector2i &mcords);

	int getTabsForNewLine(Text &text, int tillPos);

	void setPosYBottomLine(Editor &editor, Text &text);

	void createNewLineSetNewLineParameters(Editor &editor, Text &text, int &lineNr, int tillPos, int tabNr);

	void setNormalBackspace(Editor &editor, Text &text, int cursorCharNr);

	void setDeleteLineBackspace(Editor &editor, Text &text);

	cursorPosition cursorInsertText(Editor &editor, Text &text, std::string textToInsert, int lineNr, int linePosX, int linePosY);

	int getPosXToCharNr(Editor &editor, Text &text, int linePosX, int lineNr);

	void cursorInsertTextMakeNewLine(Editor &editor, Text &text, std::string &textToInsert, int &lineNr, int &linePosX);

	void ctrlV(Editor &editor, Text &text);

	void simpleCtrlV(Editor &editor, Text &text);

	void cursorTextMovingWhileMarking(Editor &editor, Text &text, sf::Vector2i &mcords);

	bool defaultMTIsActive();

	std::string getStringFromMarkedText(Editor &editor, Cursor &cursor, Text &text);

	cursorPosition deleteDefaultMTString(Editor &editor, Cursor &cursor, Text &text);

	cursorPosition defaultMTSetString(Editor &editor, Cursor &cursor, Text &text, std::string stringToInsert);

	void drawDefaultMarkedText(Editor &editor, Text &text, sf::RenderWindow &window);

	//When posXAtClick is set at -1 all the conditions know that posXAtClick does not have a meaningful value.

	void enableSetPosXAtClick();

	void setPosXAtClick();

	int getPosY();

	void setPosY(int x);

	int getPosX();

	void setPosX(int x);

	int getCursorLineNr();

	void setCursorLineNr(int x);

	void showCursor();

	void blankCursor();

};}

#endif
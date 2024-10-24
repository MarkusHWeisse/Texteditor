#ifndef FRONTEND_P20241023_TEXTEDIT_Cursor
#define FRONTEND_P20241023_TEXTEDIT_Cursor

#include "FRONTEND_P20241023_TEXTEDIT.h"
#include "FRONTEND_P20241023_TEXTEDIT_MarkedText.h"
//#include "Editor.h"

class Editor;
namespace FRONTEND_P20241023_TEXTEDIT {
	class Slider;
	class Text;
	class MarkedText;
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
	FRONTEND_P20241023_TEXTEDIT::MarkedText MT;

public:
	Cursor() {
		
	}	

	Cursor(FRONTEND_P20241023_TEXTEDIT::MarkedText &MT) {
		this->posXAtClick = -1;
		this->lineNrAtClick = -1;
		this->posYAtClick = -1;
		this->textMovingWhileMarkingSpeed = 10;
		this->textMovingWhileMarkingSet = 0;
		this->MT = MT;
		MT.unsetActive();
	}

	void loadEvents(Editor &editor, sf::Event &event, FRONTEND_P20241023_TEXTEDIT::Text &text);
	void loadDraw(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::RenderWindow &window);
	void loadCursor(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	void loadVars(Editor &editor);
	void setCursorRects(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	bool cursorLeft(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	bool cursorRight(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	bool cursorUp(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	bool cursorDown(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	bool cursorSimpleBackspace(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	bool cursorMTBackspace(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	bool cursorBackspace(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	bool cursorEnter(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	bool cursorU(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	bool cursorD(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	void cursorMouseEvent(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::Vector2i &mcords);
	void cursorMouseMarking(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords);
	void cursorMouseEventRecognition(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords);
	bool checkMouseInWindowBounds(sf::Vector2i &mcords, int screenPosX, int screenPosY, int screenWidth, int screenHeight);
	void setMousePosToCursorPos(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords);
	void setMousePosYToLine(FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords);
	int getMousePosYToLineNr(int mousePosY, int fontSize, int topSpace);
	int setMousePosXToCursorX(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords, int lineNr);
	int setMousePosXToCursorPosXValues(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, int charSize, int charSizeBef, sf::Vector2i &mcords);
	int getTabsForNewLine(FRONTEND_P20241023_TEXTEDIT::Text &text, int tillPos);
	void setPosYBottomLine(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	void createNewLineSetNewLineParameters(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, int &lineNr, int tillPos, int tabNr);
	void setNormalBackspace(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, int cursorCharNr);
	void setDeleteLineBackspace(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	cursorPosition cursorInsertText(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, std::string textToInsert, int lineNr, int linePosX, int linePosY);
	int getPosXToCharNr(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, int linePosX, int lineNr);
	void cursorInsertTextMakeNewLine(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, std::string &textToInsert, int &lineNr, int &linePosX);
	void ctrlV(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	void simpleCtrlV(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	void cursorTextMovingWhileMarking(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords);

	bool defaultMTIsActive() {
		return MT.getActive();
	}

	std::string getStringFromMarkedText(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
		return MT.getString(editor, cursor, text);
	}

	cursorPosition deleteDefaultMTString(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
		return MT.deleteString(editor, cursor, text);
	}

	cursorPosition defaultMTSetString(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, std::string stringToInsert) {
		return MT.setString(editor, cursor, text, stringToInsert);
	}

	void drawDefaultMarkedText(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::RenderWindow &window) {
		MT.drawMarkedText(editor, text, window);
	}

	//When posXAtClick is set at -1 all the conditions know that posXAtClick does not have a meaningful value.
	void enableSetPosXAtClick() {
		this->posXAtClick = -1;
		this->lineNrAtClick = -1;
		this->posYAtClick = -1;
	}

	void setPosXAtClick() {
		posXAtClick = posX;
		lineNrAtClick = cursorLineNr;
		posYAtClick = posY;
	}

	int getPosY() {
		return posY;
	}

	void setPosY(int x) {
		posY = x;
	}

	int getPosX() {
		return posX;
	}

	void setPosX(int x) {
		posX = x;
	}

	int getCursorLineNr() {
		return cursorLineNr;
	}

	void setCursorLineNr(int x) {
		cursorLineNr = x;
	}

	void showCursor() {
		cursorShow = 20;
	}

	void blankCursor() {
		cursorShow = 0;
	}
};}

#endif
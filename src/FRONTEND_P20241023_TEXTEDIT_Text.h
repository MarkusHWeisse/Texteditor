#ifndef FRONTEND_P20241023_TEXTEDIT_Text
#define FRONTEND_P20241023_TEXTEDIT_Text

#include "FRONTEND_P20241023_TEXTEDIT.h"
//#include "Editor.h"

class Editor;
namespace FRONTEND_P20241023_TEXTEDIT {
	class Cursor;
	class Slider;
	class MarkedText;
	class EditorMouse;

 class Text {
private:
	std::vector<std::string> lines;
	sf::Text textDraw;
	float bottomLine;
	bool allowInput;
	FRONTEND_P20241023_TEXTEDIT::TextWidths textWidths;
	int fontSize;
	int fontSizeSpacing;
	sf::Font font;
	std::vector<std::string> keywords;
	std::vector<std::string> keywordsSpecial;
	std::vector<sf::Text> textDrawVector;

public:
	Text();

	void loadFile(std::string file);
	int loadFont(std::string sfont);
	void loadTextWidthsBounds(int lineNr);
	void loadVars();
	void loadText();
	void insertText(int cursorLineNr, int cursorCharNr, char insert, bool deleteB);
	void loadEvents(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, sf::Event &event);
	void loadDraw(sf::RenderWindow &window, Editor &editor);
	void countChars(void* outVal, Editor &editor, std::string s1, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, void func(int* outVal2, int* igive, int* sgive));
	int getSize(int lineNr, int charNr);
	void drawText(sf::RenderWindow &window);
	//void countCharsTab(int* i, int* size, int* i2);

	int getFontSize();

	int getFontSizeSpacing();

	void setFontSize(int real, int spacing);

	float getBottomLine();

	void setBottomLine(float x);

	std::string getLine(int x);

	int getCharWidth();

	int getTabWidth();

	int getTextWidth();

	int getLineSize();

	void insertLines(int cursorLineNr, std::string text);

	void deleteLine(int x);

	void addText(int x, std::string textAdd);

	void setText(int x, std::string textSet);

	void setAllowInput();

	void denieInput();

	bool allowInputSet();

	static void countCharsSize(int* outVal, int* i, int* size);
	
};}

#endif
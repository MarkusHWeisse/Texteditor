#ifndef Editor
#define Editor

#include "FRONTEND_P20241023_TEXTEDIT.h"

namespace FRONTEND_P20241023_TEXTEDIT {
	class Cursor;
	class Slider;
	class Text;
	class MarkedText;
	class EditorMouse;
}

class Editor {
private:
	sf::RenderWindow window;
	sf::RectangleShape background;
	sf::RectangleShape leftNumBlock;
	FRONTEND_P20241023_TEXTEDIT::Text &text;
	FRONTEND_P20241023_TEXTEDIT::Cursor &cursor;
	FRONTEND_P20241023_TEXTEDIT::Slider &slider;
	int GreyBlockSize;
	bool setCTRL;
	bool setAlt;
	int leftIndent;
	std::string path;
	std::string wTitle;
	bool mouseInRange;
	FRONTEND_P20241023_TEXTEDIT::EditorMouse &mouse;

public:
	void loadEvents(sf::Event &event);
	void loadDraw();
	void loadEditor(std::string path1);
	void loadAllEvents(sf::Event &event);
	void loadSwitchKeyPressedEvents(sf::Event &event);
	void loadSwitchKeyReleasedEvents(sf::Event &event);
	void loadAllDraws();
	void loadLoop();
	void loadVars();
	void openFile(FRONTEND_P20241023_TEXTEDIT::Text &text, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor);
	void writeFile(Text &text);
	void dynamicGBS(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	void checkMouse();
	void mScrolled(sf::Event &event);
	void loadTotalEvents();
	void setMouseInUse();
	void unsetMouseInUse();
	void loadMouse(FRONTEND_P20241023_TEXTEDIT::EditorMouse &m);
	bool getSliderInUse();
	int getLeftIndent();
	bool getMouseInRange();
	void setMouseInRange(bool s);
	void setFilePath(std::string p);
	void setTextObj(FRONTEND_P20241023_TEXTEDIT::Text &text);
	void setCursorObj(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor);
	void setSliderObj(FRONTEND_P20241023_TEXTEDIT::Slider &slider);
	int getGreyBlockSize();
	void setGreyBlockSize(int x);
	sf::Vector2u wGetSize();
	bool getCTRL();
	void onCTRL();
	void offCTRL();
	void onAlt();
	void offAlt();
	bool getAlt();
	void setTitleNotSaved();
	void setTitleSaved();
};

#endif
#pragma once
#ifndef Editor_h
#define Editor_h
//#include <SFML/Graphics.hpp>

//#include "FRONTEND_P20241023_TEXTEDIT.h"

#include "CONTROLLER_P20241027_TEXTEDIT/Controller.h"
#include "BACKEND_P20241027_TEXTEDIT/File.h"
#include "BACKEND_P20241027_TEXTEDIT/Text.h"
#include "FRONTEND_P20241023_TEXTEDIT/FRONTEND_P20241023_TEXTEDIT.h"
#include "FRONTEND_P20241023_TEXTEDIT/EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT/Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT/Slider.h"
#include "FRONTEND_P20241023_TEXTEDIT/Text.h"
#include "FRONTEND_P20241023_TEXTEDIT/MarkedText.h"

/*
namespace FRONTEND_P20241023_TEXTEDIT {
	class Cursor;
	class Slider;
	class Text;
	class MarkedText;
	class EditorMouse;
}
*/
class Editor {
private:
	sf::RenderWindow window;
	sf::RectangleShape background;
	sf::RectangleShape leftNumBlock;
	FRONTEND_P20241023_TEXTEDIT::Text text;
	FRONTEND_P20241023_TEXTEDIT::Cursor cursor;
	FRONTEND_P20241023_TEXTEDIT::Slider slider;
	BACKEND_P20241027_TEXTEDIT::File file;
	int GreyBlockSize;
	bool setCTRL;
	bool setAlt;
	int leftIndent;
	std::string path;
	std::string wTitle;
	bool mouseInRange;
	FRONTEND_P20241023_TEXTEDIT::EditorMouse mouse;

public:
	
	Editor();
	
	//Editor(FRONTEND_P20241023_TEXTEDIT::Text &text, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Slider &slider, FRONTEND_P20241023_TEXTEDIT::EditorMouse &mouse);

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

	void writeFile(FRONTEND_P20241023_TEXTEDIT::Text &text);

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

	void setTextObj(FRONTEND_P20241023_TEXTEDIT::Text text);

	void setCursorObj(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor);

	void setSliderObj(FRONTEND_P20241023_TEXTEDIT::Slider slider);

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
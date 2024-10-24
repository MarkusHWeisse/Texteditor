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

/*
#include "FRONTEND_P20241023_TEXTEDIT_EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT_Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT_Slider.h"
#include "FRONTEND_P20241023_TEXTEDIT_Text.h"*/
//#include "FRONTEND_P20241023_TEXTEDIT_MarkedText.h"
/*
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
	Editor() {
		window.create(sf::VideoMode(1200, 900), "Sovieditor");
		window.setFramerateLimit(60);

		HWND win = window.getSystemHandle();
		SetWindowLongPtr(win, GWL_EXSTYLE, GetWindowLongPtr(win, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(window.getSystemHandle(), 0x00FFFFFF, 228, LWA_ALPHA);

		GreyBlockSize = 30;
		background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
		background.setPosition(0, 0);
		background.setFillColor(sf::Color::White);
		leftNumBlock.setSize(sf::Vector2f(30, window.getSize().y));
		leftNumBlock.setFillColor(sf::Color(210, 210, 210));
		leftNumBlock.setPosition(0, 0);
		setCTRL = false;
		wTitle = "Sovieditor";
	}

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

	void setMouseInUse() {
		mouse.setInUse(true);
	}

	void unsetMouseInUse() {
		mouse.setInUse(false);
	}

	void loadMouse(FRONTEND_P20241023_TEXTEDIT::EditorMouse &m) {
		this->mouse = m;
	}

	bool getSliderInUse() {
		return slider.getInUse();
	}

	int getLeftIndent() {
		return slider.getSliderWidth();
	}

	bool getMouseInRange() {
		return mouseInRange;
	}

	void setMouseInRange(bool s) {
		mouseInRange = s;
	}

	void setFilePath(std::string p) {
		path = p;
	}

	void setTextObj(FRONTEND_P20241023_TEXTEDIT::Text &text) {
		this->text = text;
	}

	void setCursorObj(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor) {
		this->cursor = cursor;
		
		cursor.loadCursor(*this, text);
	}

	void setSliderObj(FRONTEND_P20241023_TEXTEDIT::Slider &slider) {
		this->slider = slider;
	}

	int getGreyBlockSize() {
		return GreyBlockSize;
	}

	void setGreyBlockSize(int x) {
		GreyBlockSize = x;
	}

	sf::Vector2u wGetSize() {
		return window.getSize();
	}

	bool getCTRL() {
		return setCTRL;
	}

	void onCTRL() {
		setCTRL = true;
	}

	void offCTRL() {
		setCTRL = false;
	}

	void onAlt() {
		setAlt = true;
	}

	void offAlt() {
		setAlt = false;
	}

	bool getAlt() {
		return setAlt;
	}

	void setTitleNotSaved() {
		window.setTitle(wTitle + "*");
	}

	void setTitleSaved() {
		window.setTitle(wTitle);
	}
};*/

#endif
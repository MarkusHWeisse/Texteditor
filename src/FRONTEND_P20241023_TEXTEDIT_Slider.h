#ifndef FRONTEND_P20241023_TEXTEDIT_Slider
#define FRONTEND_P20241023_TEXTEDIT_Slider

#include "FRONTEND_P20241023_TEXTEDIT.h"
//#include "Editor.h"

class Editor;
namespace FRONTEND_P20241023_TEXTEDIT {
	class Cursor;
	class Text;
	class MarkedText;
	class EditorMouse;

	class Slider {
private:
	bool inUse;
	bool allowUpdate;
	int posX;
	int posY;
	int changeY;
	int defaultSize;
	int sizeY;
	int mPosBef;
	int changeYClick;
	int sliderWidth;
	sf::RectangleShape sliderRect;
	sf::CircleShape circle;

public:
	Slider() {

	}

	Slider(int posX, int posY) {
		this->posX = posX;
		this->posY = posY;
		this->defaultSize = 20;
		this->sizeY = defaultSize;
		this->inUse = false;
		this->mPosBef = 0;
		this->changeY = 0;
		this->allowUpdate = true;
		this->sliderWidth = 7;
	}

	void loadEvents(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords);
	void loadDraw(Editor &editor, sf::RenderWindow &window);
	void updateSlider(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	void setChangeYToLine(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::RenderWindow &window);
	void sliderInUse(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords);
	void sliderClicked(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords);
	void setChangeYOutOfBounds(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords);
	void setChangeYInBounds(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords);

	void setInUse(bool t) {
		inUse = t;
	}

	bool getInUse() {
		return inUse;
	}

	void setSliderWidth(int x) {
		this->sliderWidth = x;
	}

	int getSliderWidth() {
		return this->sliderWidth + 10;
	}

	void setCPosY(int posY) {
		this->changeY = posY;
	}

	int getCPosY() {
		return changeY;
	}

	void setPosY(int posY) {
		this->posY = posY;
	}

	void setPosX(int posX) {
		this->posX = posX;
	} 

	int getPosX() {
		return posX;
	}

	void escapeEvent() {
		inUse = false;
		mPosBef = 0;
	}
};}

#endif
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

	Slider(int posX, int posY);

	void loadEvents(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords);
	void loadDraw(Editor &editor, sf::RenderWindow &window);
	void updateSlider(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	void setChangeYToLine(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::RenderWindow &window);
	void sliderInUse(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords);
	void sliderClicked(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords);
	void setChangeYOutOfBounds(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords);
	void setChangeYInBounds(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords);

	void setInUse(bool t);

	bool getInUse();

	void setSliderWidth(int x);

	int getSliderWidth();

	void setCPosY(int posY);

	int getCPosY();

	void setPosY(int posY);

	void setPosX(int posX);

	int getPosX();

	void escapeEvent();
	
};}

#endif
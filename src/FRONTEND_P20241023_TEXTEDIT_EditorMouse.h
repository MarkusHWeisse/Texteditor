#ifndef FRONTEND_P20241023_TEXTEDIT_EditorMouse
#define FRONTEND_P20241023_TEXTEDIT_EditorMouse

#include "FRONTEND_P20241023_TEXTEDIT.h"

namespace FRONTEND_P20241023_TEXTEDIT {
	class Cursor;
	class Slider;
	class Text;
	class MarkedText;

	class EditorMouse {	
	bool inUse;
	sf::Mouse m;
	sf::Vector2i mcords;

public:
	EditorMouse() {

	}

	//Bad Design: intention not obvious -> change!
	void loadMouseCoordinates(sf::RenderWindow &window);

	int getPosX();

	int getPosY();

	sf::Vector2i& getMouseCords();

	void setInUse(bool t);

	bool getInUse();
};}

#endif
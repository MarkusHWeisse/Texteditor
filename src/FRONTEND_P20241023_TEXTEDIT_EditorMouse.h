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
	void loadMouseCoordinates(sf::RenderWindow &window) {
		mcords = m.getPosition(window);
	}


	int getPosX() {
		return mcords.x;
	}

	int getPosY() {
		return mcords.y;
	}

	sf::Vector2i& getMouseCords() {
		return mcords;
	}

	void setInUse(bool t) {
		inUse = t;
	}

	bool getInUse() {
		return inUse;
	}
};}

#endif
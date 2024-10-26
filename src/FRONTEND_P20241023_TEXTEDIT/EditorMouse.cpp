#include <SFML/Graphics.hpp>

#include "FRONTEND_P20241023_TEXTEDIT.h"
#include "EditorMouse.h"
#include "Cursor.h"
#include "Slider.h"
#include "Text.h"
#include "MarkedText.h"
#include "../Editor.h"


namespace FRONTEND_P20241023_TEXTEDIT {

//Bad Design: intention not obvious -> change!
void EditorMouse::loadMouseCoordinates(sf::RenderWindow &window) {
	mcords = m.getPosition(window);
}


int EditorMouse::getPosX() {
	return mcords.x;
}

int EditorMouse::getPosY() {
	return mcords.y;
}

sf::Vector2i& EditorMouse::getMouseCords() {
	return mcords;
}

void EditorMouse::setInUse(bool t) {
	inUse = t;
}

bool EditorMouse::getInUse() {
	return inUse;
}

}
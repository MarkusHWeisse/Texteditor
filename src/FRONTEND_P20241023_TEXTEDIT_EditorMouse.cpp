#include <SFML/Graphics.hpp>

#include "FRONTEND_P20241023_TEXTEDIT.h"
#include "FRONTEND_P20241023_TEXTEDIT_EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT_Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT_Slider.h"
#include "FRONTEND_P20241023_TEXTEDIT_Text.h"*/
#include "FRONTEND_P20241023_TEXTEDIT_MarkedText.h"
#include "Editor.h"

//Bad Design: intention not obvious -> change!
void FRONTEND_P20241023_TEXTEDIT::EditorMouse::loadMouseCoordinates(sf::RenderWindow &window) {
	mcords = m.getPosition(window);
}


int FRONTEND_P20241023_TEXTEDIT::EditorMouse::getPosX() {
	return mcords.x;
}

int FRONTEND_P20241023_TEXTEDIT::EditorMouse::getPosY() {
	return mcords.y;
}

sf::Vector2i& FRONTEND_P20241023_TEXTEDIT::EditorMouse::getMouseCords() {
	return mcords;
}

void FRONTEND_P20241023_TEXTEDIT::EditorMouse::setInUse(bool t) {
	inUse = t;
}

bool FRONTEND_P20241023_TEXTEDIT::EditorMouse::getInUse() {
	return inUse;
}
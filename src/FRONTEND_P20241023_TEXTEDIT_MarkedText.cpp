#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

#include "FRONTEND_P20241023_TEXTEDIT.h"
#include "FRONTEND_P20241023_TEXTEDIT_EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT_Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT_Slider.h"
#include "FRONTEND_P20241023_TEXTEDIT_Text.h"*/
#include "FRONTEND_P20241023_TEXTEDIT_MarkedText.h"
#include "Editor.h"

FRONTEND_P20241023_TEXTEDIT::MarkedText::MarkedText(FRONTEND_P20241023_TEXTEDIT::cursorPosition &cp1, FRONTEND_P20241023_TEXTEDIT::cursorPosition &cp2) {
	this->cp1 = cp1;
	this->cp2 = cp2;
	isActive = true;
}

void FRONTEND_P20241023_TEXTEDIT::MarkedText::setCursorPositionOne(FRONTEND_P20241023_TEXTEDIT::cursorPosition &cp1) {
	this->cp1 = cp1;
}

void FRONTEND_P20241023_TEXTEDIT::MarkedText::setCursorPositionTwo(FRONTEND_P20241023_TEXTEDIT::cursorPosition &cp2) {
	this->cp2 = cp2;
}

void FRONTEND_P20241023_TEXTEDIT::MarkedText::setActive() {
	isActive = true;
}

void FRONTEND_P20241023_TEXTEDIT::MarkedText::unsetActive() {
	isActive = false;
}

bool FRONTEND_P20241023_TEXTEDIT::MarkedText::getActive() {
	return isActive;
}
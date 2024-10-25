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

FRONTEND_P20241023_TEXTEDIT::Slider::Slider(int posX, int posY) {
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

void FRONTEND_P20241023_TEXTEDIT::Slider::setInUse(bool t) {
	inUse = t;
}

bool FRONTEND_P20241023_TEXTEDIT::Slider::getInUse() {
	return inUse;
}

void FRONTEND_P20241023_TEXTEDIT::Slider::setSliderWidth(int x) {
	this->sliderWidth = x;
}

int FRONTEND_P20241023_TEXTEDIT::Slider::getSliderWidth() {
	return this->sliderWidth + 10;
}

void FRONTEND_P20241023_TEXTEDIT::Slider::setCPosY(int posY) {
	this->changeY = posY;
}

int FRONTEND_P20241023_TEXTEDIT::Slider::getCPosY() {
	return changeY;
}

void FRONTEND_P20241023_TEXTEDIT::Slider::setPosY(int posY) {
	this->posY = posY;
}

void FRONTEND_P20241023_TEXTEDIT::Slider::setPosX(int posX) {
	this->posX = posX;
} 

int FRONTEND_P20241023_TEXTEDIT::Slider::getPosX() {
	return posX;
}

void FRONTEND_P20241023_TEXTEDIT::Slider::escapeEvent() {
	inUse = false;
	mPosBef = 0;
}
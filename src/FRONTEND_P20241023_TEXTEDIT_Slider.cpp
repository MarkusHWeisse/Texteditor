#include <iostream>
#include <string>
#include <cmath>

#include "FRONTEND_P20241023_TEXTEDIT.h"
#include "FRONTEND_P20241023_TEXTEDIT_EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT_Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT_Text.h"
#include "FRONTEND_P20241023_TEXTEDIT_MarkedText.h"
#include "FRONTEND_P20241023_TEXTEDIT_Slider.h"
#include "Editor.h"


namespace FRONTEND_P20241023_TEXTEDIT {

Slider::Slider(int posX, int posY) {
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


void Slider::setChangeYToLine(Cursor &cursor, Text &text, sf::RenderWindow &window) {
	int maxLines = (int)((window.getSize().y - 3) / text.getFontSizeSpacing());
	int zeile = (int)((float)changeY * (float)((float)(text.getLineSize() - maxLines) / (float)(window.getSize().y - posY - sizeY)));
	//cursor.setCursorLineNr(cursor.getCursorLineNr() + zeile + 1 - text.getBottomLine());
	text.setBottomLine(zeile + 1);
	allowUpdate = false;
}

void Slider::setChangeYOutOfBounds(Editor &editor, Cursor &cursor, Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords) {
	if(mcords.x >= editor.getGreyBlockSize() && mcords.x <= window.getSize().x)	{
		if(mcords.y < posY) {
			changeY = 0;
		}else if(mcords.y > window.getSize().y) {
			changeY = window.getSize().y - sizeY; 
		}
		setChangeYToLine(cursor, text, window);
	}
}

void Slider::setChangeYInBounds(Editor &editor, Cursor &cursor, Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords) {
	if(mcords.x >= editor.getGreyBlockSize() && mcords.y >= 0 && mcords.x <= window.getSize().x && mcords.y <= window.getSize().y) {
		int difference = (float)mPosBef - mcords.y;
		int maxLines = (int)((window.getSize().y - 3) / text.getFontSizeSpacing());

		if((changeYClick - difference >= posY) && (changeYClick - difference + posY + sizeY <= window.getSize().y)) {
			changeY = changeYClick - difference;
			setChangeYToLine(cursor, text, window);
		}
	}
}

void Slider::sliderInUse(Editor &editor, Cursor &cursor, Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords) {
	setChangeYOutOfBounds(editor, cursor, text, event, window, mcords);

	setChangeYInBounds(editor, cursor, text, event, window, mcords);

	cursor.setPosY(cursor.getCursorLineNr()+1 - text.getBottomLine());
}

void Slider::sliderClicked(Editor &editor, Cursor &cursor, Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords) {
	sf::Cursor c;
	if(c.loadFromSystem(sf::Cursor::Arrow))
		window.setMouseCursor(c);	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !inUse) {
		inUse = true;
		editor.setMouseInUse();
		mPosBef = mcords.y;
		changeYClick = changeY;
	}
}

void Slider::loadEvents(Editor &editor, Cursor &cursor, Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords) {
	if(inUse) {
		sliderInUse(editor, cursor, text, event, window, mcords);	
		return;
	}
	
	if(mcords.x >= window.getSize().x-sliderWidth && mcords.y >= posY+changeY && mcords.x <= window.getSize().x-2 && mcords.y <= posY+changeY+sizeY) {
		sliderClicked(editor, cursor, text, event, window, mcords);
		return;
	}
}

void Slider::updateSlider(Editor &editor, Cursor &cursor, Text &text) {
	if(!allowUpdate) {
		allowUpdate = true;
		return;
	}

	int maxLines = (int)((editor.wGetSize().y - 3) / text.getFontSizeSpacing());

	if(text.getLineSize() - maxLines < (editor.wGetSize().y - posY - defaultSize)) {
		sizeY = (editor.wGetSize().y - posY - defaultSize) - text.getLineSize() - maxLines;
	}else {
		sizeY = defaultSize;
	}

	changeY = (int)((float)text.getBottomLine() * (float)((float)(editor.wGetSize().y - posY - sizeY) / (float)(text.getLineSize() - maxLines)));
}

void Slider::loadDraw(Editor &editor, sf::RenderWindow &window) {
	sf::Color c;

	c = sf::Color(200, 200, 200);

	if(inUse) {
		c = sf::Color(100, 100, 100);
	}

	circle.setRadius(2.5);
	circle.setPosition(sf::Vector2f(window.getSize().x - sliderWidth, posY+changeY));
	circle.setFillColor(c);

	window.draw(circle);

	circle.setRadius(2.5);
	circle.setPosition(sf::Vector2f(window.getSize().x - sliderWidth, posY+changeY+sizeY-5));
	circle.setFillColor(c);

	window.draw(circle);

	sliderRect.setFillColor(c);
	sliderRect.setPosition(sf::Vector2f(window.getSize().x - sliderWidth, posY+changeY+2.5));
	sliderRect.setSize(sf::Vector2f(5, sizeY-5));

	window.draw(sliderRect);
}

void Slider::setInUse(bool t) {
	inUse = t;
}

bool Slider::getInUse() {
	return inUse;
}

void Slider::setSliderWidth(int x) {
	this->sliderWidth = x;
}

int Slider::getSliderWidth() {
	return this->sliderWidth + 10;
}

void Slider::setCPosY(int posY) {
	this->changeY = posY;
}

int Slider::getCPosY() {
	return changeY;
}

void Slider::setPosY(int posY) {
	this->posY = posY;
}

void Slider::setPosX(int posX) {
	this->posX = posX;
} 

int Slider::getPosX() {
	return posX;
}

void Slider::escapeEvent() {
	inUse = false;
	mPosBef = 0;
}

}
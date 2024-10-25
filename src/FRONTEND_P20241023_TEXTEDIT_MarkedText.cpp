#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>

#include "FRONTEND_P20241023_TEXTEDIT.h"
#include "FRONTEND_P20241023_TEXTEDIT_EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT_Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT_Slider.h"
#include "FRONTEND_P20241023_TEXTEDIT_Text.h"
#include "FRONTEND_P20241023_TEXTEDIT_MarkedText.h"
#include "Editor.h"

namespace FRONTEND_P20241023_TEXTEDIT {

MarkedText::MarkedText(cursorPosition cp1, cursorPosition cp2) {
	this->cp1 = cp1;
	this->cp2 = cp2;
	isActive = true;
}

void MarkedText::drawRectangle(sf::RenderWindow &window, int posX, int posY, int width, int height) {
	rs.setFillColor(sf::Color(150, 150, 150));
	rs.setPosition(sf::Vector2f(posX, posY));
	rs.setSize(sf::Vector2f(abs(width), height));

	window.draw(rs);
}

void MarkedText::checkOrientation() {
	if(cp1.lineNr > cp2.lineNr || (cp1.posX > cp2.posX && cp1.lineNr == cp2.lineNr)) {
		cursorPosition ret = cp1;
		cp1 = cp2;
		cp2 = ret;	
	}
}

void MarkedText::drawMarkedText(Editor &editor, Text &text, sf::RenderWindow &window) {
	if(!isActive) {
		return;
	}

	if(cp2.lineNr < text.getBottomLine() - 1) {
		return;
	}
	
	if(cp1.lineNr == cp2.lineNr) {
		int MTPosY = ((cp1.lineNr - text.getBottomLine() + 1)) * text.getFontSizeSpacing() + 3;
		drawRectangle(window, cp1.posX, MTPosY, abs(cp1.posX - cp2.posX), text.getFontSizeSpacing());
		return;
	}

	int iLineNr = abs(cp2.lineNr - cp1.lineNr);

	int i = 0;
	int MTPosY = ((cp1.lineNr - text.getBottomLine() + 1)) * text.getFontSizeSpacing() + 3;
	drawRectangle(window, cp1.posX, MTPosY, abs((cp1.posX-editor.getGreyBlockSize()) - text.getSize(cp1.lineNr, -1)), text.getFontSizeSpacing());
	while(i<iLineNr-1) {
		i++;
		MTPosY += text.getFontSizeSpacing();
		drawRectangle(window, editor.getGreyBlockSize(), MTPosY, text.getSize(cp1.lineNr + i, -1), text.getFontSizeSpacing());
	}
	MTPosY += text.getFontSizeSpacing();
	drawRectangle(window, editor.getGreyBlockSize(), MTPosY, cp2.posX - editor.getGreyBlockSize(), text.getFontSizeSpacing());
}

std::string MarkedText::getString(Editor &editor, Cursor &cursor, Text &text) {
	if(!isActive) {
		return "";
	}

	std::string returnstr;

	if(cp1.lineNr == cp2.lineNr) {
		int cp1x = cursor.getPosXToCharNr(editor, text, cp1.posX, cp1.lineNr);
		int cp2x = cursor.getPosXToCharNr(editor, text, cp2.posX, cp1.lineNr);

		if(cp2x == -1) {
			cp2x = text.getLine(cp1.lineNr).size();
		}

		returnstr = text.getLine(cp1.lineNr).substr(cp1x, cp2x - cp1x);
		return returnstr;
	}

	int iLineNr = abs(cp2.lineNr - cp1.lineNr);
	int cp1x = cursor.getPosXToCharNr(editor, text, cp1.posX, cp1.lineNr);
	int cp2x = cursor.getPosXToCharNr(editor, text, cp2.posX, cp2.lineNr);
	cp1x = (cp1x == -1) ? (text.getLine(cp1.lineNr).size()) : (cp1x);
	cp2x = (cp2x == -1) ? (text.getLine(cp2.lineNr).size()) : (cp2x);
	returnstr += text.getLine(cp1.lineNr).substr(cp1x, text.getLine(cp1.lineNr).size() - cp1x);
	int i = 0;
	while(i<iLineNr-1) {
		i++;
		returnstr += "\n" + text.getLine(cp1.lineNr + i);
	}
	returnstr += "\n";
	returnstr += text.getLine(cp2.lineNr).substr(0, cp2x + 1);

	return returnstr;
}

cursorPosition MarkedText::deleteString(Editor &editor, Cursor &cursor, Text &text) {
	cursorPosition retcp;

	if(!isActive) {
		return retcp;
	}

	if(cp1.lineNr == cp2.lineNr) {
		int cp1x = cursor.getPosXToCharNr(editor, text, cp1.posX, cp1.lineNr);
		int cp2x = cursor.getPosXToCharNr(editor, text, cp2.posX, cp1.lineNr);
		std::string text1 = text.getLine(cp1.lineNr).substr(0, cp1x);
		std::string text2 = (cp2x != -2) ? text.getLine(cp1.lineNr).substr(cp2x, text.getLine(cp1.lineNr).size()-cp2x) : "";
		text.setText(cp1.lineNr, text1 + text2);

		retcp.lineNr = cp1.lineNr;
		retcp.posX = cp1.posX;
		retcp.posY = cp1.posY;
		return retcp;
	}

	int cp1x = cursor.getPosXToCharNr(editor, text, cp1.posX, cp1.lineNr);
	int cp2x = cursor.getPosXToCharNr(editor, text, cp2.posX, cp2.lineNr);
	std::string text1 = text.getLine(cp1.lineNr).substr(0, cp1x);
	std::string text2 = (cp2x != -2) ? text.getLine(cp2.lineNr).substr(cp2x, text.getLine(cp2.lineNr).size()-cp2x) : "";
	text.setText(cp1.lineNr, text1 + text2);

	retcp.lineNr = cp1.lineNr;
	retcp.posX = cp1.posX;
	retcp.posY = cp1.posY;

	for(int i = cp1.lineNr+1;i<=cp2.lineNr;++i) {
		text.deleteLine(cp1.lineNr+1);
	}

	return retcp;
}

void MarkedText::setCursorPositionOne(cursorPosition &cp1) {
	this->cp1 = cp1;
}

void MarkedText::setCursorPositionTwo(cursorPosition &cp2) {
	this->cp2 = cp2;
}

void MarkedText::setActive() {
	isActive = true;
}

void MarkedText::unsetActive() {
	isActive = false;
}

bool MarkedText::getActive() {
	return isActive;
}
}
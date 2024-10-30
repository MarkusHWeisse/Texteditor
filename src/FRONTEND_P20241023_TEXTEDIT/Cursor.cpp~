#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <iterator>

#include "FRONTEND_P20241023_TEXTEDIT.h"
#include "EditorMouse.h"
#include "Cursor.h"
#include "Slider.h"
#include "Text.h"
#include "MarkedText.h"
#include "../Editor.h"


namespace FRONTEND_P20241023_TEXTEDIT {

int Cursor::setMousePosXToCursorPosXValues(Editor &editor, Text &text, int charSize, int charSizeBef, sf::Vector2i &mcords) {
	
	int r;
	
	if(mcords.x <= editor.getGreyBlockSize()) {
	
		return editor.getGreyBlockSize();
	
	}

	if(charSize - mcords.x - editor.getGreyBlockSize() > mcords.x - editor.getGreyBlockSize() - charSizeBef) {
	
		r = charSizeBef + editor.getGreyBlockSize();
	
	}else {
	
		r = charSize + editor.getGreyBlockSize();
	
	} 

	return r;

}

int Cursor::setMousePosXToCursorX(Editor &editor, Text &text, sf::Vector2i &mcords, int lineNr) {
	
	int charSize = 0;
	
	int charSizeBef = 0;
	
	for(int i = 0;i<text.getLine(lineNr).size();++i) {
		
		charSizeBef = charSize;

		if(text.getLine(lineNr).at(i) == '	') {
			
			charSize += text.getTabWidth();
			
		}else {
			
			charSize += text.getCharWidth();
			
		}

		if(charSize >= mcords.x - editor.getGreyBlockSize()) {
			
			return setMousePosXToCursorPosXValues(editor, text, charSize, charSizeBef, mcords);
			
		}
		
	}

	return charSize + editor.getGreyBlockSize();
	
}

int Cursor::getMousePosYToLineNr(int mousePosY, int fontSize, int topSpace) {
	
	return (int)((mousePosY - topSpace) / fontSize);
	
}

void Cursor::setMousePosYToLine(Text &text, sf::Vector2i &mcords) {
	
	cursorLineNr = getMousePosYToLineNr(mcords.y, text.getFontSizeSpacing(), 3);
	
	posY = cursorLineNr;
	
	cursorLineNr += text.getBottomLine() - 1;
	
}

void Cursor::setMousePosToCursorPos(Editor &editor, Text &text, sf::Vector2i &mcords) {
	
	setMousePosYToLine(text, mcords);

	posX = setMousePosXToCursorX(editor, text, mcords, cursorLineNr);

	if(posXAtClick == -1) {
		
		MT.unsetActive();
		
		setPosXAtClick();
		
	}
	
}

bool Cursor::checkMouseInWindowBounds(sf::Vector2i &mcords, int screenPosX, int screenPosY, int screenWidth, int screenHeight) {
	
	return mcords.x >= screenPosX && mcords.x <= screenWidth && mcords.y >= screenPosY && mcords.y <= screenHeight;
}

void Cursor::cursorMouseMarking(Editor &editor, Text &text, sf::Vector2i &mcords) {
	
	if(lineNrAtClick - cursorLineNr != 0 || getPosXToCharNr(editor, text, posX, cursorLineNr) - getPosXToCharNr(editor, text, posXAtClick, lineNrAtClick) != 0) {
		
		std::cout << "You are marking Text" << std::endl;
		
		MarkedText newMT(cursorPosition(lineNrAtClick, posXAtClick, posYAtClick), cursorPosition(cursorLineNr, posX, posY));
		
		MT = newMT;
		
		MT.checkOrientation();
		
	}
	
}

void Cursor::cursorMouseEventRecognition(Editor &editor, Text &text, sf::Vector2i &mcords) {
	
	setMousePosToCursorPos(editor, text, mcords);
	
	showCursor();
	
	cursorMouseMarking(editor, text, mcords); 
	
}

void Cursor::cursorTextMovingWhileMarking(Editor &editor, Text &text, sf::Vector2i &mcords) {
	
	if(textMovingWhileMarkingSet == 0 || textMovingWhileMarkingSpeed > 0) {
		
		textMovingWhileMarkingSpeed--;
		
		return;
		
	}

	textMovingWhileMarkingSpeed = 10;

	if(textMovingWhileMarkingSet == 1) {
		
		if(cursorUp(editor, text))cursorMouseEventRecognition(editor, text, mcords);
		
	}else {
		
		if(cursorDown(editor, text))cursorMouseEventRecognition(editor, text, mcords);
		
	}
	
}

void Cursor::cursorMouseEvent(Editor &editor, Text &text, sf::Event &event, sf::Vector2i &mcords) {
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && checkMouseInWindowBounds(mcords, 0, -20, editor.wGetSize().x - editor.getLeftIndent(), editor.wGetSize().y+20)) {
		
		if(mcords.y <= 0 && mcords.y >= -20) {
			
			textMovingWhileMarkingSet = 1;
			
			return;
			
		}else if(mcords.y >= editor.wGetSize().y && mcords.y <= editor.wGetSize().y+20) {
			
			textMovingWhileMarkingSet = 2;
			
			return;
			
		}

		textMovingWhileMarkingSet = 0;
		
		textMovingWhileMarkingSpeed = 10;
		
		cursorMouseEventRecognition(editor, text, mcords);
		
		//std::cout << "recognizing" << std::endl;
	}
	
}

void Cursor::setCursorRects(Editor &editor, Text &text) {
	
	cursorBackground.setSize(sf::Vector2f(editor.wGetSize().x - editor.getGreyBlockSize(), text.getFontSizeSpacing()));
	
	cursorBackground.setPosition(editor.getGreyBlockSize(), (posY * text.getFontSizeSpacing()) + 3);
	
	cursorBackground.setFillColor(sf::Color(240, 240, 240));

	cursorDraw.setSize(sf::Vector2f(2, text.getFontSizeSpacing()));
	
	cursorDraw.setPosition(posX, (posY * text.getFontSizeSpacing()) + 3);
	
	cursorDraw.setFillColor(sf::Color(255, 0, 0));
	
}

void Cursor::loadCursor(Editor &editor, Text &text) {
	
	loadVars(editor);
	
	setCursorRects(editor, text);
	
}

void Cursor::loadVars(Editor &editor) {
	
	posY = 0;
	
	posX = 0;
	
	cursorLineNr = 0;
	
	cursorBlink = 0;
	
	cursorShow = 0;
	
}

bool Cursor::cursorLeft(Editor &editor, Text &text) {
	
	if(editor.getCTRL()) {
		
		return false;
		
	}

	if((posX-editor.getGreyBlockSize()) != 0) {
		
		int nextChar = 0;
		
		text.countChars(&nextChar, editor, text.getLine(cursorLineNr), *this);
		
		if(text.getLine(cursorLineNr).at(nextChar - 1) == '	') {
			
			posX-=text.getTabWidth();
			
		}else {
			
			posX-=text.getCharWidth();
			
		}
		
	}

	return true;
	
}

bool Cursor::cursorRight(Editor &editor, Text &text) {
	
	if(editor.getCTRL()) {
		
		return false;
		
	}

	int charPosSize = 0;
	
	text.countChars(&charPosSize, editor, text.getLine(cursorLineNr), *this);
	
	if(charPosSize < text.getLine(cursorLineNr).length()) {
		
		int nextChar = 0;
		
		text.countChars(&nextChar, editor, text.getLine(cursorLineNr), *this);
		
		if(text.getLine(cursorLineNr).at(nextChar) == '	') {
			
			posX+=text.getTabWidth();
			
		}else {
			
			posX += text.getCharWidth();
			
		}
		
	}
	
	return true;
	
}

bool Cursor::cursorU(Editor &editor, Text &text) {
	
	int maxLines = (int)((editor.wGetSize().y - 3) / text.getFontSizeSpacing());

	if(editor.getCTRL() && text.getBottomLine() - maxLines > 0) {
	
		text.setBottomLine(text.getBottomLine() - maxLines);
		
		cursorLineNr -= maxLines;
		
		return true;
	
	}else {
	
		cursorLineNr -= text.getBottomLine() - 1;
	
		text.setBottomLine(1);
	
	}
	
	return false;

}

bool Cursor::cursorUp(Editor &editor, Text &text) { 

	if(editor.getCTRL()) {
		
		return false;
		
	}

	cursorLineNr--;
	
	if((cursorLineNr) < 0) {
		
		cursorLineNr++;
		
		return false;
		
	}else if((posY-1) < 0) {
		
		text.setBottomLine(text.getBottomLine() - 1);
		
	}else {
		
		posY--;
		
	}
	
	return true;
	
}

bool Cursor::cursorD(Editor &editor, Text &text) {
	
	int maxLines = (int)((editor.wGetSize().y - 3) / text.getFontSizeSpacing());

	if(editor.getCTRL() && text.getBottomLine() + 2*maxLines - 1 <= text.getLineSize()) {
		
		text.setBottomLine(text.getBottomLine() + maxLines);
		
		cursorLineNr += maxLines;
		
		return true;
		
	}else {
		
		cursorLineNr += (text.getLineSize() - maxLines + 1) - text.getBottomLine();
		
		text.setBottomLine(text.getLineSize() - maxLines + 1);
		
	}
	
	return false;
	
}

bool Cursor::cursorDown(Editor &editor, Text &text) {
	
	if(editor.getCTRL()) {
		
		return false;
		
	}

	if(cursorLineNr + 1 < text.getLineSize()) {
		
		if((posY+1) > (int)((editor.wGetSize().y - 3) / text.getFontSizeSpacing()) - 1) {
			
			text.setBottomLine(text.getBottomLine() + 1);
			
		}else {
			
			posY++;
			
		}
		
		cursorLineNr++;
		
		return true;
		
	}
	
	return false;
	
}

void Cursor::setNormalBackspace(Editor &editor, Text &text, int cursorCharNr) {

	int nextChar = 0;

	text.countChars(&nextChar, editor, text.getLine(cursorLineNr), *this);

	if(text.getLine(cursorLineNr).at(nextChar - 1) == '	') {

		posX-=text.getTabWidth();

	}else {

		posX-=text.getCharWidth();

	}

	text.insertText(cursorLineNr, cursorCharNr, ' ', true);

	text.loadTextWidthsBounds(cursorLineNr);

}

void Cursor::setDeleteLineBackspace(Editor &editor, Text &text) {

	std::string deletedLine = text.getLine(cursorLineNr);

	text.deleteLine(cursorLineNr);

	cursorLineNr--;

	text.loadTextWidthsBounds(cursorLineNr);

	posX = editor.getGreyBlockSize() + text.getSize(cursorLineNr, -1);

	text.addText(cursorLineNr, deletedLine);

	text.loadTextWidthsBounds(cursorLineNr);

	posY--;

}

bool Cursor::cursorSimpleBackspace(Editor &editor, Text &text) {

	if(editor.getCTRL()) {

		return false;

	}

	int cursorCharNr = 0;

	text.countChars(&cursorCharNr, editor, text.getLine(cursorLineNr), *this);

	if((posX-editor.getGreyBlockSize()) != 0) {

		setNormalBackspace(editor, text, cursorCharNr);		

	}else if((posX - editor.getGreyBlockSize()) == 0 && cursorLineNr > 0) {

		setDeleteLineBackspace(editor, text);

	}

	return true;

}

bool Cursor::cursorMTBackspace(Editor &editor, Text &text) {

	cursorPosition cp = deleteDefaultMTString(editor, *this, text);

	setPosX(cp.posX);

	setPosY(cp.posY);

	if(text.getBottomLine() > cp.lineNr+1) {

		text.setBottomLine(cp.lineNr+1);

	}	

	setCursorLineNr(cp.lineNr);

	MT.unsetActive();

	return true;

}

bool Cursor::cursorBackspace(Editor &editor, Text &text) {

	if(defaultMTIsActive()) {

		cursorMTBackspace(editor, text);

		text.denieInput();

		return true;

	}else if(cursorSimpleBackspace(editor, text)) {

		text.denieInput();

		return true;

	}	

	return false;

} 

int Cursor::getTabsForNewLine(Text &text, int tillPos) {

	int tabNr = 0;

	for (int i = 0;i<text.getLine(cursorLineNr).length() && i<tillPos;i++) {

		if(text.getLine(cursorLineNr).at(i) == '	') {

			tabNr++;

		}else {

			break;

		}	

	}

	return tabNr;

}

void Cursor::setPosYBottomLine(Editor &editor, Text &text) {

	if((posY+1) > (int)((editor.wGetSize().y - 3) / text.getFontSizeSpacing()) - 1) {

		text.setBottomLine(text.getBottomLine() + 1);

	}else {

		posY++;

	}

}

void Cursor::createNewLineSetNewLineParameters(Editor &editor, Text &text, int &lineNr, int tillPos, int tabNr) {

	std::string insertStr = text.getLine(lineNr).substr(tillPos, text.getLine(lineNr).length());

	std::string remainingStr = text.getLine(lineNr).substr(0, tillPos);

	lineNr++;

	text.insertLines(lineNr, std::string(tabNr, '	') + insertStr);

	text.setText(lineNr-1, remainingStr);
	//text.loadTextWidthsBounds(lineNr);

}

bool Cursor::cursorEnter(Editor &editor, Text &text) {

	if(editor.getCTRL()) {

		return false;

	}

	int strPos = 0;
	text.countChars(&strPos, editor, text.getLine(cursorLineNr), *this);	

	setPosYBottomLine(editor, text);

	int tabNr = getTabsForNewLine(text, strPos);

	createNewLineSetNewLineParameters(editor, text, cursorLineNr, strPos, tabNr);

	posX = editor.getGreyBlockSize() + tabNr * text.getTabWidth();

	return true;

}

int Cursor::getPosXToCharNr(Editor &editor, Text &text, int linePosX, int lineNr) {

	int width = 0;

	for(int i = 0;i<text.getLine(lineNr).size();++i) {

		if(width == linePosX - editor.getGreyBlockSize()) {

			return i;

		}
		
		if(text.getLine(lineNr).at(i) == '	') {

			width += text.getTabWidth();

		}else {

			width += text.getCharWidth();

		}

	}

	if(linePosX - editor.getGreyBlockSize() == text.getSize(lineNr, text.getLine(lineNr).size())) {

		//return text.getLine(lineNr).size()-1;
		return -2;

	}

	return -1;

}

void Cursor::cursorInsertTextMakeNewLine(Editor &editor, Text &text, std::string &textToInsert, int &lineNr, int &linePosX) {

	int j = getPosXToCharNr(editor, text, linePosX, lineNr);

	if(j == -1 || j == -2) {

		textToInsert = text.getLine(lineNr) + textToInsert; 

	}else {

		std::string first = text.getLine(lineNr).substr(0, j);

		std::string second = text.getLine(lineNr).substr(j, text.getLine(lineNr).size() - j);

		textToInsert = first + textToInsert + second;

	}

	text.setText(lineNr, textToInsert);

	std::cout << textToInsert << std::endl;

	for(int i = 0;i<textToInsert.size();++i) {

		char c = textToInsert.at(i);

		if(c == '\r') {

			std::string first = textToInsert.substr(0, i);

			std::string second = textToInsert.substr(i+2, textToInsert.size() - i - 2);

			textToInsert = first + second;

			text.setText(lineNr, first);

			lineNr++;

			text.insertLines(lineNr+1, second);

			//createNewLineSetNewLineParameters(editor, text, lineNr, i, 0);
			textToInsert = text.getLine(lineNr);

		}

	}

	editor.setTitleNotSaved();

}

cursorPosition Cursor::cursorInsertText(Editor &editor, Text &text, std::string textToInsert, int lineNr, int linePosX, int linePosY) {

	FRONTEND_P20241023_TEXTEDIT::cursorPosition returnCP;

	returnCP.lineNr = lineNr;

	returnCP.posX = linePosX + textToInsert.size() * text.getCharWidth();

	returnCP.posY = linePosY;

	if(textToInsert.find('\n', 0) == std::string::npos) {

		text.setText(lineNr, text.getLine(lineNr) + textToInsert);

		return returnCP;

	}

	cursorInsertTextMakeNewLine(editor, text, textToInsert, lineNr, linePosX);

	return returnCP;

}

void Cursor::loadEvents(Editor &editor, sf::Event &event, Text &text) {
	
}

void Cursor::loadDraw(Editor &editor, Text &text, sf::RenderWindow &window) { //Constant Framerate important, no usage of time.

	cursorBackground.setPosition(editor.getGreyBlockSize(), (posY * text.getFontSizeSpacing()) + 3);

	cursorDraw.setPosition(posX, (posY * text.getFontSizeSpacing()) + 3);

	//window.draw(cursorBackground);	

	if(cursorBlink <= 40 && cursorShow == 0) {

		if(cursorBlink > 0) {

			cursorBlink--;

		}else if(cursorBlink == -40) {

			cursorBlink *= -1;

		}else {

			cursorBlink--;

			window.draw(cursorDraw);

		}	

	}else {

		window.draw(cursorDraw);

		cursorShow--;

		cursorBlink = 40;

	}

}

void Cursor::simpleCtrlV(Editor &editor, Text &text) {
	
	cursorPosition cp;
	
	cp = cursorInsertText(editor, text, sf::Clipboard::getString().toAnsiString(), getCursorLineNr(), getPosX(), getPosY());
	
	setCursorLineNr(cp.lineNr);
	
	setPosX(cp.posX);
	
	setPosY(cp.posY);
	
	editor.offCTRL();
	
	text.denieInput();

}

void Cursor::ctrlV(Editor &editor, Text &text) {
	
	if(!editor.getCTRL()) {
	
		return;
	
	}

	if(!MT.getActive()) {
	
		simpleCtrlV(editor, text);
	
		return;
	
	}

	cursorPosition cp = MT.deleteString(editor, *this, text);
	
	setPosX(cp.posX);
	
	setPosY(cp.posY);
	
	if(text.getBottomLine() > cp.lineNr+1) {
	
		text.setBottomLine(cp.lineNr+1);
	
	}	
	
	setCursorLineNr(cp.lineNr);
	
	MT.unsetActive();
	
	cursorInsertText(editor, text, sf::Clipboard::getString(), cursorLineNr, posX, posY);
	
	text.denieInput();

}

Cursor::Cursor(MarkedText MT) {
	
	this->posXAtClick = -1;
	
	this->lineNrAtClick = -1;
	
	this->posYAtClick = -1;
	
	this->textMovingWhileMarkingSpeed = 10;
	
	this->textMovingWhileMarkingSet = 0;
	
	this->MT = MT;
	
	MT.unsetActive();
	
}

bool Cursor::defaultMTIsActive() {
	return MT.getActive();
}

std::string Cursor::getStringFromMarkedText(Editor &editor, Cursor &cursor, Text &text) {
	return MT.getString(editor, cursor, text);
}

cursorPosition Cursor::deleteDefaultMTString(Editor &editor, Cursor &cursor, Text &text) {
	return MT.deleteString(editor, cursor, text);
}

cursorPosition Cursor::defaultMTSetString(Editor &editor, Cursor &cursor, Text &text, std::string stringToInsert) {
	//return MT.getString(editor, cursor, text);
}

void Cursor::drawDefaultMarkedText(Editor &editor, Text &text, sf::RenderWindow &window) {
	MT.drawMarkedText(editor, text, window);
}

//When posXAtClick is set at -1 all the conditions know that posXAtClick does not have a meaningful value.
void Cursor::enableSetPosXAtClick() {
	this->posXAtClick = -1;
	this->lineNrAtClick = -1;
	this->posYAtClick = -1;
}

void Cursor::setPosXAtClick() {
	posXAtClick = posX;
	lineNrAtClick = cursorLineNr;
	posYAtClick = posY;
}

int Cursor::getPosY() {
	return posY;
}

void Cursor::setPosY(int x) {
	posY = x;
}

int Cursor::getPosX() {
	return posX;
}

void Cursor::setPosX(int x) {
	posX = x;
}

int Cursor::getCursorLineNr() {
	return cursorLineNr;
}

void Cursor::setCursorLineNr(int x) {
	cursorLineNr = x;
}

void Cursor::showCursor() {
	cursorShow = 20;
}

void Cursor::blankCursor() {
	cursorShow = 0;
}

}
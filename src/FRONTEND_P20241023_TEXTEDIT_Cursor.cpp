class Editor;
namespace FRONTEND_P20241023_TEXTEDIT {
	class Cursor;
	class Slider;
	class Text;
	class MarkedText;
}

#include "FRONTEND_P20241023_TEXTEDIT_Cursor.h"

/*
int FRONTEND_P20241023_TEXTEDIT::Cursor::setMousePosXToCursorPosXValues(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, int charSize, int charSizeBef, sf::Vector2i &mcords) {
	
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

int FRONTEND_P20241023_TEXTEDIT::Cursor::setMousePosXToCursorX(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords, int lineNr) {
	
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

int FRONTEND_P20241023_TEXTEDIT::Cursor::getMousePosYToLineNr(int mousePosY, int fontSize, int topSpace) {
	
	return (int)((mousePosY - topSpace) / fontSize);
	
}

void FRONTEND_P20241023_TEXTEDIT::Cursor::setMousePosYToLine(FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords) {
	
	cursorLineNr = getMousePosYToLineNr(mcords.y, text.getFontSizeSpacing(), 3);
	
	posY = cursorLineNr;
	
	cursorLineNr += text.getBottomLine() - 1;
	
}

void FRONTEND_P20241023_TEXTEDIT::Cursor::setMousePosToCursorPos(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords) {
	
	setMousePosYToLine(text, mcords);

	posX = setMousePosXToCursorX(editor, text, mcords, cursorLineNr);

	if(posXAtClick == -1) {
		
		MT.unsetActive();
		
		setPosXAtClick();
		
	}
	
}

bool FRONTEND_P20241023_TEXTEDIT::Cursor::checkMouseInWindowBounds(sf::Vector2i &mcords, int screenPosX, int screenPosY, int screenWidth, int screenHeight) {
	
	return mcords.x >= screenPosX && mcords.x <= screenWidth && mcords.y >= screenPosY && mcords.y <= screenHeight;
}

void FRONTEND_P20241023_TEXTEDIT::Cursor::cursorMouseMarking(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords) {
	
	if(lineNrAtClick - cursorLineNr != 0 || getPosXToCharNr(editor, text, posX, cursorLineNr) - getPosXToCharNr(editor, text, posXAtClick, lineNrAtClick) != 0) {
		
		std::cout << "You are marking Text" << std::endl;
		
		MarkedText newMT(cursorPosition(lineNrAtClick, posXAtClick, posYAtClick), cursorPosition(cursorLineNr, posX, posY));
		
		MT = newMT;
		
		MT.checkOrientation();
		
	}
	
}

void FRONTEND_P20241023_TEXTEDIT::Cursor::cursorMouseEventRecognition(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords) {
	
	setMousePosToCursorPos(editor, text, mcords);
	
	showCursor();
	
	cursorMouseMarking(editor, text, mcords); 
	
}

void FRONTEND_P20241023_TEXTEDIT::Cursor::cursorTextMovingWhileMarking(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Vector2i &mcords) {
	
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

void FRONTEND_P20241023_TEXTEDIT::Cursor::cursorMouseEvent(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::Vector2i &mcords) {
	
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

void FRONTEND_P20241023_TEXTEDIT::Cursor::setCursorRects(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
	
	cursorBackground.setSize(sf::Vector2f(editor.wGetSize().x - editor.getGreyBlockSize(), text.getFontSizeSpacing()));
	
	cursorBackground.setPosition(editor.getGreyBlockSize(), (posY * text.getFontSizeSpacing()) + 3);
	
	cursorBackground.setFillColor(sf::Color(240, 240, 240));

	cursorDraw.setSize(sf::Vector2f(2, text.getFontSizeSpacing()));
	
	cursorDraw.setPosition(posX, (posY * text.getFontSizeSpacing()) + 3);
	
	cursorDraw.setFillColor(sf::Color(255, 0, 0));
	
}

void FRONTEND_P20241023_TEXTEDIT::Cursor::loadCursor(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
	
	loadVars(editor);
	
	setCursorRects(editor, text);
	
}

void FRONTEND_P20241023_TEXTEDIT::Cursor::loadVars(Editor &editor) {
	
	posY = 0;
	
	posX = 0;
	
	cursorLineNr = 0;
	
	cursorBlink = 0;
	
	cursorShow = 0;
	
}

bool FRONTEND_P20241023_TEXTEDIT::Cursor::cursorLeft(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
	
	if(editor.getCTRL()) {
		
		return false;
		
	}

	if((posX-editor.getGreyBlockSize()) != 0) {
		
		int nextChar = 0;
		
		text.countChars(&nextChar, editor, text.getLine(cursorLineNr), *this, text.countCharsSize);
		
		if(text.getLine(cursorLineNr).at(nextChar - 1) == '	') {
			
			posX-=text.getTabWidth();
			
		}else {
			
			posX-=text.getCharWidth();
			
		}
		
	}

	return true;
	
}

bool FRONTEND_P20241023_TEXTEDIT::Cursor::cursorRight(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
	
	if(editor.getCTRL()) {
		
		return false;
		
	}

	int charPosSize = 0;
	
	text.countChars(&charPosSize, editor, text.getLine(cursorLineNr), *this, text.countCharsSize);
	
	if(charPosSize < text.getLine(cursorLineNr).length()) {
		
		int nextChar = 0;
		
		text.countChars(&nextChar, editor, text.getLine(cursorLineNr), *this, text.countCharsSize);
		
		if(text.getLine(cursorLineNr).at(nextChar) == '	') {
			
			posX+=text.getTabWidth();
			
		}else {
			
			posX += text.getCharWidth();
			
		}
		
	}
	
	return true;
	
}

bool FRONTEND_P20241023_TEXTEDIT::Cursor::cursorU(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
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

bool FRONTEND_P20241023_TEXTEDIT::Cursor::cursorUp(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) { 
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

bool FRONTEND_P20241023_TEXTEDIT::Cursor::cursorD(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
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

bool FRONTEND_P20241023_TEXTEDIT::Cursor::cursorDown(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
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

void FRONTEND_P20241023_TEXTEDIT::Cursor::setNormalBackspace(Editor &editor, Text &text, int cursorCharNr) {
	int nextChar = 0;
	text.countChars(&nextChar, editor, text.getLine(cursorLineNr), *this, text.countCharsSize);
	if(text.getLine(cursorLineNr).at(nextChar - 1) == '	') {
		posX-=text.getTabWidth();
	}else {
		posX-=text.getCharWidth();
	}
	text.insertText(cursorLineNr, cursorCharNr, ' ', true);
	text.loadTextWidthsBounds(cursorLineNr);
}

void FRONTEND_P20241023_TEXTEDIT::Cursor::setDeleteLineBackspace(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
	std::string deletedLine = text.getLine(cursorLineNr);
	text.deleteLine(cursorLineNr);
	cursorLineNr--;
	text.loadTextWidthsBounds(cursorLineNr);
	posX = editor.getGreyBlockSize() + text.getSize(cursorLineNr, -1);
	text.addText(cursorLineNr, deletedLine);
	text.loadTextWidthsBounds(cursorLineNr);
	posY--;
}

bool FRONTEND_P20241023_TEXTEDIT::Cursor::cursorSimpleBackspace(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
	if(editor.getCTRL()) {
		return false;
	}

	int cursorCharNr = 0;
	text.countChars(&cursorCharNr, editor, text.getLine(cursorLineNr), *this, text.countCharsSize);
	if((posX-editor.getGreyBlockSize()) != 0) {
		setNormalBackspace(editor, text, cursorCharNr);		
	}else if((posX - editor.getGreyBlockSize()) == 0 && cursorLineNr > 0) {
		setDeleteLineBackspace(editor, text);
	}
	return true;
}

bool FRONTEND_P20241023_TEXTEDIT::Cursor::cursorMTBackspace(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
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

bool FRONTEND_P20241023_TEXTEDIT::Cursor::cursorBackspace(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
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

int FRONTEND_P20241023_TEXTEDIT::Cursor::getTabsForNewLine(FRONTEND_P20241023_TEXTEDIT::Text &text, int tillPos) {
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

void FRONTEND_P20241023_TEXTEDIT::Cursor::setPosYBottomLine(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
	if((posY+1) > (int)((editor.wGetSize().y - 3) / text.getFontSizeSpacing()) - 1) {
		text.setBottomLine(text.getBottomLine() + 1);
	}else {
		posY++;
	}
}

void FRONTEND_P20241023_TEXTEDIT::Cursor::createNewLineSetNewLineParameters(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, int &lineNr, int tillPos, int tabNr) {
	std::string insertStr = text.getLine(lineNr).substr(tillPos, text.getLine(lineNr).length());
	std::string remainingStr = text.getLine(lineNr).substr(0, tillPos);
	lineNr++;
	text.insertLines(lineNr, std::string(tabNr, '	') + insertStr);
	text.setText(lineNr-1, remainingStr);
	//text.loadTextWidthsBounds(lineNr);
}

bool FRONTEND_P20241023_TEXTEDIT::Cursor::cursorEnter(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
	if(editor.getCTRL()) {
		return false;
	}

	int strPos = 0;
	text.countChars(&strPos, editor, text.getLine(cursorLineNr), *this, text.countCharsSize);	

	setPosYBottomLine(editor, text);

	int tabNr = getTabsForNewLine(text, strPos);

	createNewLineSetNewLineParameters(editor, text, cursorLineNr, strPos, tabNr);

	posX = editor.getGreyBlockSize() + tabNr * text.getTabWidth();

	return true;
}

int FRONTEND_P20241023_TEXTEDIT::Cursor::getPosXToCharNr(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, int linePosX, int lineNr) {
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

void FRONTEND_P20241023_TEXTEDIT::Cursor::cursorInsertTextMakeNewLine(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, std::string &textToInsert, int &lineNr, int &linePosX) {
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

cursorPosition FRONTEND_P20241023_TEXTEDIT::Cursor::cursorInsertText(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, std::string textToInsert, int lineNr, int linePosX, int linePosY) {
	cursorPosition returnCP;
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

void FRONTEND_P20241023_TEXTEDIT::Cursor::loadEvents(Editor &editor, sf::Event &event, FRONTEND_P20241023_TEXTEDIT::Text &text) {
	
}

void FRONTEND_P20241023_TEXTEDIT::Cursor::loadDraw(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::RenderWindow &window) { //Constant Framerate important, no usage of time.
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

void FRONTEND_P20241023_TEXTEDIT::Cursor::simpleCtrlV(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
	cursorPosition cp;
	cp = cursorInsertText(editor, text, sf::Clipboard::getString().toAnsiString(), getCursorLineNr(), getPosX(), getPosY());
	setCursorLineNr(cp.lineNr);
	setPosX(cp.posX);
	setPosY(cp.posY);
	editor.offCTRL();
	text.denieInput();
}

void FRONTEND_P20241023_TEXTEDIT::Cursor::ctrlV(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
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
}*/

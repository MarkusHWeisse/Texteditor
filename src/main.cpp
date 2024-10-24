#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iterator>
#include <windows.h>
#include <shobjidl.h>
#include <objbase.h>
/*
namespace FRONTEND_P20241023_TEXTEDIT {
	class EditorMouse;
	class Cursor;
	class Slider;
	class Text;
	class MarkedText;
}*/

#include "FRONTEND_P20241023_TEXTEDIT_EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT_Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT_Slider.h"
#include "FRONTEND_P20241023_TEXTEDIT_Text.h"
#include "FRONTEND_P20241023_TEXTEDIT_MarkedText.h"

//#include "Editor.h"


class Editor {
private:
	sf::RenderWindow window;
	sf::RectangleShape background;
	sf::RectangleShape leftNumBlock;
	FRONTEND_P20241023_TEXTEDIT::Text text;
	FRONTEND_P20241023_TEXTEDIT::Cursor cursor;
	FRONTEND_P20241023_TEXTEDIT::Slider slider;
	int GreyBlockSize;
	bool setCTRL;
	bool setAlt;
	int leftIndent;
	std::string path;
	std::string wTitle;
	bool mouseInRange;
	FRONTEND_P20241023_TEXTEDIT::EditorMouse mouse;

public:
	Editor(FRONTEND_P20241023_TEXTEDIT::Text &text, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Slider &slider) {
		setTextObj(text);
		setCursorObj(cursor);
		setSliderObj(slider);

		window.create(sf::VideoMode(1200, 900), "Sovieditor");
		window.setFramerateLimit(60);

		HWND win = window.getSystemHandle();
		SetWindowLongPtr(win, GWL_EXSTYLE, GetWindowLongPtr(win, GWL_EXSTYLE) | WS_EX_LAYERED);
		SetLayeredWindowAttributes(window.getSystemHandle(), 0x00FFFFFF, 228, LWA_ALPHA);

		GreyBlockSize = 30;
		background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
		background.setPosition(0, 0);
		background.setFillColor(sf::Color::White);
		leftNumBlock.setSize(sf::Vector2f(30, window.getSize().y));
		leftNumBlock.setFillColor(sf::Color(210, 210, 210));
		leftNumBlock.setPosition(0, 0);
		setCTRL = false;
		wTitle = "Sovieditor";
	}

	void loadEvents(sf::Event &event);
	void loadDraw();
	void loadEditor(std::string path1);
	void loadAllEvents(sf::Event &event);
	void loadSwitchKeyPressedEvents(sf::Event &event);
	void loadSwitchKeyReleasedEvents(sf::Event &event);
	void loadAllDraws();
	void loadLoop();
	void loadVars();
	void openFile(FRONTEND_P20241023_TEXTEDIT::Text &text, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor);
	void writeFile(Text &text);
	void dynamicGBS(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text);
	void checkMouse();
	void mScrolled(sf::Event &event);
	void loadTotalEvents();

	void setMouseInUse() {
		mouse.setInUse(true);
	}

	void unsetMouseInUse() {
		mouse.setInUse(false);
	}

	void loadMouse(FRONTEND_P20241023_TEXTEDIT::EditorMouse &m) {
		this->mouse = m;
	}

	bool getSliderInUse() {
		return slider.getInUse();
	}

	int getLeftIndent() {
		return slider.getSliderWidth();
	}

	bool getMouseInRange() {
		return mouseInRange;
	}

	void setMouseInRange(bool s) {
		mouseInRange = s;
	}

	void setFilePath(std::string p) {
		path = p;
	}

	void setTextObj(FRONTEND_P20241023_TEXTEDIT::Text &text) {
		this->text = text;
	}

	void setCursorObj(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor) {
		this->cursor = cursor;
		
		cursor.loadCursor(*this, text);
	}

	void setSliderObj(FRONTEND_P20241023_TEXTEDIT::Slider &slider) {
		this->slider = slider;
	}

	int getGreyBlockSize() {
		return GreyBlockSize;
	}

	void setGreyBlockSize(int x) {
		GreyBlockSize = x;
	}

	sf::Vector2u wGetSize() {
		return window.getSize();
	}

	bool getCTRL() {
		return setCTRL;
	}

	void onCTRL() {
		setCTRL = true;
	}

	void offCTRL() {
		setCTRL = false;
	}

	void onAlt() {
		setAlt = true;
	}

	void offAlt() {
		setAlt = false;
	}

	bool getAlt() {
		return setAlt;
	}

	void setTitleNotSaved() {
		window.setTitle(wTitle + "*");
	}

	void setTitleSaved() {
		window.setTitle(wTitle);
	}
};


//#define _WIN32_WINNT 0x0600 

#ifndef UNICODE
#define UNICODE
#endif 

#define NTDDI_VERSION 0x0A000006 //NTDDI_WIN10_RS5
#define _WIN32_WINNT 0x0A00

/*
TODO:
	Umlaute
	...
*/

//Set ld flags in mingw in order to compile this. See Stackoverflow
//CPP-Reference:
std::string print_wide(const wchar_t* wstr) {
    std::mbstate_t state = std::mbstate_t();
    std::size_t len = 1 + std::wcsrtombs(nullptr, &wstr, 0, &state);
    std::vector<char> mbstr(len);
    std::wcsrtombs(&mbstr[0], &wstr, mbstr.size(), &state);
    //std::cout << &mbstr[0] << std::endl;
    return std::string(mbstr.begin(), mbstr.end());
}

//Win32 API - Stackoverflow:

std::string fileDialogWinApi() {
	std::string s1;
	s1 = "C:\\Users\\marku\\OneDrive\\Dokumente\\privat\\Projects\\SovieditorV2.0\\prevver\\mainTest.cpp";
/*
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr)) {
        IFileOpenDialog* pFileOpen;

        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
        // if object created ( that's com object )
        if (SUCCEEDED(hr)) {
            hr = pFileOpen->Show(NULL);

            if (SUCCEEDED(hr)) {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr)){
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    if (SUCCEEDED(hr)) {
                        //MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        s1 = print_wide(pszFilePath);
                        CoTaskMemFree(pszFilePath);

                        std::string stringtoconvert;

                        std::wstring temp = std::wstring(stringtoconvert.begin(), stringtoconvert.end());
                        LPCWSTR lpcwstr = temp.c_str();
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }    */
    return s1;
}

/*

void FRONTEND_P20241023_TEXTEDIT::MarkedText::drawRectangle(sf::RenderWindow &window, int posX, int posY, int width, int height) {
	rs.setFillColor(sf::Color(150, 150, 150));
	rs.setPosition(sf::Vector2f(posX, posY));
	rs.setSize(sf::Vector2f(abs(width), height));

	window.draw(rs);
}

void FRONTEND_P20241023_TEXTEDIT::MarkedText::checkOrientation() {
	if(cp1.lineNr > cp2.lineNr || (cp1.posX > cp2.posX && cp1.lineNr == cp2.lineNr)) {
		cursorPosition ret = cp1;
		cp1 = cp2;
		cp2 = ret;	
	}
}

void FRONTEND_P20241023_TEXTEDIT::MarkedText::drawMarkedText(Editor &editor, Text &text, sf::RenderWindow &window) {
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

std::string FRONTEND_P20241023_TEXTEDIT::MarkedText::getString(Editor &editor, Cursor &cursor, Text &text) {
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

cursorPosition FRONTEND_P20241023_TEXTEDIT::MarkedText::deleteString(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
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

void FRONTEND_P20241023_TEXTEDIT::Slider::setChangeYToLine(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::RenderWindow &window) {
	int maxLines = (int)((window.getSize().y - 3) / text.getFontSizeSpacing());
	int zeile = (int)((float)changeY * (float)((float)(text.getLineSize() - maxLines) / (float)(window.getSize().y - posY - sizeY)));
	//cursor.setCursorLineNr(cursor.getCursorLineNr() + zeile + 1 - text.getBottomLine());
	text.setBottomLine(zeile + 1);
	allowUpdate = false;
}

void FRONTEND_P20241023_TEXTEDIT::Slider::setChangeYOutOfBounds(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords) {
	if(mcords.x >= editor.getGreyBlockSize() && mcords.x <= window.getSize().x)	{
		if(mcords.y < posY) {
			changeY = 0;
		}else if(mcords.y > window.getSize().y) {
			changeY = window.getSize().y - sizeY; 
		}
		setChangeYToLine(cursor, text, window);
	}
}

void FRONTEND_P20241023_TEXTEDIT::Slider::setChangeYInBounds(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords) {
	if(mcords.x >= editor.getGreyBlockSize() && mcords.y >= 0 && mcords.x <= window.getSize().x && mcords.y <= window.getSize().y) {
		int difference = (float)mPosBef - mcords.y;
		int maxLines = (int)((window.getSize().y - 3) / text.getFontSizeSpacing());

		if((changeYClick - difference >= posY) && (changeYClick - difference + posY + sizeY <= window.getSize().y)) {
			changeY = changeYClick - difference;
			setChangeYToLine(cursor, text, window);
		}
	}
}

void FRONTEND_P20241023_TEXTEDIT::Slider::sliderInUse(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords) {
	setChangeYOutOfBounds(editor, cursor, text, event, window, mcords);

	setChangeYInBounds(editor, cursor, text, event, window, mcords);

	cursor.setPosY(cursor.getCursorLineNr()+1 - text.getBottomLine());
}

void FRONTEND_P20241023_TEXTEDIT::Slider::sliderClicked(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords) {
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

void FRONTEND_P20241023_TEXTEDIT::Slider::loadEvents(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text, sf::Event &event, sf::RenderWindow &window, sf::Vector2i &mcords) {
	if(inUse) {
		sliderInUse(editor, cursor, text, event, window, mcords);	
		return;
	}
	
	if(mcords.x >= window.getSize().x-sliderWidth && mcords.y >= posY+changeY && mcords.x <= window.getSize().x-2 && mcords.y <= posY+changeY+sizeY) {
		sliderClicked(editor, cursor, text, event, window, mcords);
		return;
	}
}

void FRONTEND_P20241023_TEXTEDIT::Slider::updateSlider(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
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

void FRONTEND_P20241023_TEXTEDIT::Slider::loadDraw(Editor &editor, sf::RenderWindow &window) {
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

void Editor::writeFile(FRONTEND_P20241023_TEXTEDIT::Text &text) {
	std::ofstream myfile;

	myfile.open(path, std::ofstream::out | std::ofstream::trunc);

	for(int i = 0;i<text.getLineSize() && myfile.is_open();i++) {
		myfile << text.getLine(i) + "\n";
	}

	myfile.close();

	setTitleSaved();
}

void Editor::openFile(FRONTEND_P20241023_TEXTEDIT::Text &text, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor) {
	std::string file_path = fileDialogWinApi();
	text.loadFile(file_path);
	text.loadText();
	cursor.loadVars(*this);
	path = file_path;
	std::ofstream wfile;
	wfile.open("se_data_current.sedatac", std::ofstream::out | std::ofstream::trunc);
	wfile << file_path;
	wfile.close();
	//cursor.loadCursor(*this, window, text);
}

//This function initializes cursor vars two times.
void Editor::loadEditor(std::string path1) {
	if(!path1.size() > 0) {
		std::ifstream file("se_data_current.sedatac");

		if(!file.is_open()) {
			std::ofstream nfile("se_data_current.sedatac");
			nfile.close();
		}

		std::string file_path;
		if(!getline(file, file_path)) {
			std::ofstream wfile("se_data_current.sedatac");
			file_path = fileDialogWinApi();
			wfile << file_path;
			wfile.close();
		}
		text.loadFile(file_path);
		setFilePath(file_path);

		file.close();
	}else {
		text.loadFile(path1);
		setFilePath(path1);
	}

	loadVars();

	loadLoop();
}

void Editor::loadVars() { //TODO: One String for Title

}

void Editor::checkMouse() {
	mouseInRange = false;
	mouse.loadMouseCoordinates(window);

	//std::cout << "Mouse X: " << mcords.x << "; Cursor X: " << cursor.getPosX() << "; Mouse Y: " << mcords.y << "; Cursor Y: " << cursor.getPosY() << std::endl;
	
	if(mouse.getPosX() >= GreyBlockSize && mouse.getPosY() >= 0 && mouse.getPosX() <= window.getSize().x - GreyBlockSize && mouse.getPosY() <= window.getSize().y) {
		sf::Cursor c;
		if(c.loadFromSystem(sf::Cursor::Text))
			window.setMouseCursor(c);
		mouseInRange = true;
	}else if(mouse.getPosX() >= 0 && mouse.getPosX() <= GreyBlockSize || mouse.getPosX() >= window.getSize().x - GreyBlockSize && mouse.getPosX() <= window.getSize().x) {
		/*sf::Cursor c;
		if(c.loadFromSystem(sf::Cursor::SizeAll))
			window.setMouseCursor(c);*//*
	}else {
		sf::Cursor c;
		if(c.loadFromSystem(sf::Cursor::Arrow))
			window.setMouseCursor(c);
	}
}

void Editor::loadLoop() {
	while (window.isOpen()) {
		checkMouse();

		cursor.cursorTextMovingWhileMarking(*this, text, mouse.getMouseCords());

		loadTotalEvents();

		window.clear();

		loadAllDraws();

		window.display();
    }
}

void Editor::loadDraw() {
	//window.draw(background);

	leftNumBlock.setSize(sf::Vector2f(getGreyBlockSize(), window.getSize().y));
	window.draw(leftNumBlock);
}

void Editor::mScrolled(sf::Event &event) {
	if(event.type == sf::Event::MouseWheelScrolled) {
		int maxLines = (int)((wGetSize().y - 3) / text.getFontSizeSpacing());
		int change = (event.mouseWheelScroll.delta > 0) ? (text.getBottomLine() - 1 > 0 ? -1 : 0) : (text.getBottomLine() - 1 >= (text.getLineSize() - maxLines) ? 0 : 1);
		text.setBottomLine(text.getBottomLine() + change);
		cursor.setCursorLineNr(cursor.getCursorLineNr() + change);
		cursor.setPosY(cursor.getPosY() - change);
	}
}

void Editor::loadEvents(sf::Event &event) {
	mScrolled(event);
}

void Editor::loadTotalEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::Resized) {
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			window.setView(sf::View(visibleArea));
		}

		loadAllEvents(event);
	}
}

void Editor::loadAllDraws() {
	loadDraw();
	cursor.loadDraw(*this, text, window);
	cursor.drawDefaultMarkedText(*this, text, window);
	text.loadDraw(window, *this);
	slider.loadDraw(*this, window);
}

void Editor::dynamicGBS(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Text &text) {
	double i = 1.0;
	bool setDo = true;
	while(setDo) {
		if((int)((double)(text.getLineSize()) / (double)(i)) >= 1) {
			i *= 10.0;
			//std::cout << "i: " << ((int)((float)(text.getLineSize()) / (float)(i)) >= 1) << std::endl; 
		}else {
			setDo = false;
		}
	}

	int changeBefore = getGreyBlockSize();
	int change = (int)(std::log(i) / std::log(10.0)) * 8;
	change += 14;
	setGreyBlockSize(change);
	text.loadTextWidthsBounds(cursor.getCursorLineNr());
	cursor.setPosX(cursor.getPosX() - changeBefore + change);

	int *nothing;
	text.countChars(&nothing, *this, text.getLine(cursor.getCursorLineNr()), cursor, text.countCharsSize);
	//std::cout << "das wird getan" << std::endl;
}

void Editor::loadAllEvents(sf::Event &event) {
	if(!window.hasFocus()) {
		return;
	}

	dynamicGBS(cursor, text);

	loadEvents(event);
	//cursor.loadEvents(*this, event, text);

	slider.loadEvents(*this, cursor, text, event, window, mouse.getMouseCords());	

	if(!getCTRL()) {
		text.loadEvents(*this, cursor, event);
	}

	if(!mouse.getInUse()) {
		cursor.cursorMouseEvent(*this, text, event, mouse.getMouseCords());
	}

	if(event.type == sf::Event::MouseButtonReleased) {
		slider.escapeEvent();
		cursor.enableSetPosXAtClick();
		mouse.setInUse(false);
	}

	if(event.type == sf::Event::KeyPressed) {
		loadSwitchKeyPressedEvents(event);
	}	

	if(event.type == sf::Event::KeyReleased) {
		loadSwitchKeyReleasedEvents(event);
	}

	int *nothing;
	text.countChars(&nothing, *this, text.getLine(cursor.getCursorLineNr()), cursor, text.countCharsSize);

	slider.updateSlider(*this, cursor, text);
}

void Editor::loadSwitchKeyPressedEvents(sf::Event &event) {
	switch(event.key.code) {
		case sf::Keyboard::Backspace:
			cursor.cursorBackspace(*this, text);
			break;
		case sf::Keyboard::Left:
			if(cursor.cursorLeft(*this, text)) {
			}	
			break;
		case sf::Keyboard::Right:
			if(cursor.cursorRight(*this, text)) {

			}	
			break;
		case sf::Keyboard::Up:
			if(cursor.cursorUp(*this, text)) {
			}
			break;
		case sf::Keyboard::Down:
			if(cursor.cursorDown(*this, text)) {
			}	
			break;
		case sf::Keyboard::Enter:
			if(cursor.cursorEnter(*this, text)) {
				text.denieInput();
			}	
			break;
		case sf::Keyboard::U:
			if(getCTRL()) {
				cursor.cursorU(*this, text);
				text.denieInput();
			}	
			break;
		case sf::Keyboard::D:
			if(getCTRL()) {
				cursor.cursorD(*this, text);
				text.denieInput();
			}	
			break;
		case sf::Keyboard::O:
			if(getCTRL()) {
				openFile(text, cursor);
				loadVars();
				loadLoop();
				offCTRL();
				text.denieInput();
			}	
			break;
		case sf::Keyboard::S:
			if(getCTRL()) {
				writeFile(text);
				offCTRL();
				text.denieInput();
			}
			break;	
		case sf::Keyboard::V:
			cursor.ctrlV(*this, text);
			break;
		case  sf::Keyboard::C:
			if(getCTRL()) {
				sf::Clipboard::setString(cursor.getStringFromMarkedText(*this, cursor, text));
			}	
			break;
		case sf::Keyboard::LControl:
			onCTRL();
			break;	
		case sf::Keyboard::RAlt: //In order to scheiß auf control
			offCTRL();
			onAlt();
			break;	
		default:
			break;
	}
	cursor.showCursor();
}

void Editor::loadSwitchKeyReleasedEvents(sf::Event &event) {
	switch(event.key.code) {
		case sf::Keyboard::Backspace:
			text.setAllowInput();
			break;
		case sf::Keyboard::Left:
			break;
		case sf::Keyboard::Right:
			break;
		case sf::Keyboard::Up:
			break;
		case sf::Keyboard::Down:
			break;	
		case sf::Keyboard::Enter:
			text.setAllowInput();
			break;
		case sf::Keyboard::LControl:
			offCTRL();
			text.setAllowInput();
			break;
		case sf::Keyboard::RAlt:
			offAlt();
			break;
		default:
			break;
	}
}

void FRONTEND_P20241023_TEXTEDIT::Text::drawText(sf::RenderWindow &window) {
	for(int i = 0;i<textDrawVector.size();++i) {
		window.draw(textDrawVector.at(i));
	}
}

/*
*	Either count the number of characters with respect to the tab or change the X-Position of the Cursor if it 
*	would otherwise be stuck inside a tab(when moving up and down it check if we would move inside a tab and then 
*	changes our psoition before the tab). 
*//*
void FRONTEND_P20241023_TEXTEDIT::Text::countChars(void* outVal, Editor &editor, std::string s1, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, void func(int* outVal2, int* igive, int* sgive)) {
	if(s1.length() == 0) {
		*(int *)outVal = 0;
		cursor.setPosX(editor.getGreyBlockSize());	
	}	

	int sizeChars = 0;
	int sizeCharsBefore = 0;
	for(int i = 0;i<s1.size();i++) {
		if(s1.at(i) == '	') {
			sizeCharsBefore = sizeChars;
			sizeChars += textWidths.tabWidth;
		}else {
			sizeChars += textWidths.charWidth;
		}
		if(sizeChars == (cursor.getPosX()) - editor.getGreyBlockSize()) {
			int return1 = 0;
			(func(&return1, &i, &sizeChars));
			(*(int*)(outVal)) = return1;
			return;
		}else if(sizeChars > (cursor.getPosX()) - editor.getGreyBlockSize()) {
			cursor.setPosX(sizeCharsBefore + editor.getGreyBlockSize());
			return;
		}
	}
		
	cursor.setPosX(sizeChars + editor.getGreyBlockSize());
		
}

int FRONTEND_P20241023_TEXTEDIT::Text::getSize(int lineNr, int charNr) {
	int j = 0;
	for(int i = 0;i < lines.at(lineNr).size() && (charNr != -1 ? i < charNr : true);++i) {
		if(lines.at(lineNr).at(i) == '	') {
			j += getTabWidth();
		}else {
			j += getCharWidth();
		}
	}
	return j;
}

void FRONTEND_P20241023_TEXTEDIT::Text::loadEvents(Editor &editor, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, sf::Event &event) {
	if(event.type == sf::Event::TextEntered && allowInputSet()) {
		int cursorCharNr = 0;
		countChars(&cursorCharNr, editor, getLine(cursor.getCursorLineNr()), cursor, countCharsSize);
		char c = (char)event.text.unicode;
		insertText(cursor.getCursorLineNr(), cursorCharNr, c, false);

		if(c == '	') {
			cursor.setPosX(cursor.getPosX() + getTabWidth());
		}else {
			cursor.setPosX(cursor.getPosX() + getCharWidth());
		}

		loadTextWidthsBounds(cursor.getCursorLineNr());

		editor.setTitleNotSaved();
	}
}

void FRONTEND_P20241023_TEXTEDIT::Text::loadText() {
	loadVars();
	loadTextWidthsBounds(bottomLine-1);
}

void FRONTEND_P20241023_TEXTEDIT::Text::loadVars() {
	bottomLine = 1;
	allowInput = true;
}

void FRONTEND_P20241023_TEXTEDIT::Text::loadFile(std::string file) {
	loadFont("C:/CONSOLA.TTF");

	lines.clear();

    std::ifstream myfile(file);
	int cline;
	std::string line;
	if (myfile.is_open())
	{
		while ( getline(myfile,line) )
		{
		  
		  lines.push_back(line);
		}
		myfile.close();
	}

	if(lines.size() == 0) {
		lines.push_back("");
	}

	textDraw.setFont(font);
	textDraw.setCharacterSize(fontSize);
	textDraw.setColor(sf::Color::Black);
}

int FRONTEND_P20241023_TEXTEDIT::Text::loadFont(std::string sfont) {
	if(!font.loadFromFile(sfont)) {
		std::cout << "no font";
		return 0;
	}
	return 1;
}

void FRONTEND_P20241023_TEXTEDIT::Text::loadTextWidthsBounds(int lineNr) {
	sf::Text text3;
	text3.setFont(font);
	text3.setCharacterSize(fontSize);
	text3.setString(" ");
	textWidths.charWidth = text3.getLocalBounds().width;
	
	text3.setString("	");
	textWidths.tabWidth = text3.getLocalBounds().width;
	
	if(lines.size() > 0) {
		text3.setString(lines.at(lineNr));
		textWidths.textWidth = text3.getLocalBounds().width;
	}	
}

void FRONTEND_P20241023_TEXTEDIT::Text::insertText(int cursorLineNr, int cursorCharNr, char insert, bool deleteB) {
	std::string sinsert;
	if(deleteB) {
		sinsert = "";
	}else {
		sinsert = insert;
	}

	lines.at(cursorLineNr) = lines.at(cursorLineNr).substr(0, cursorCharNr-(deleteB ? 1 : 0)) + sinsert + lines.at(cursorLineNr).substr(cursorCharNr, lines.at(cursorLineNr).size()-(cursorCharNr));
}

void FRONTEND_P20241023_TEXTEDIT::Text::loadDraw(sf::RenderWindow &window, Editor &editor) {
	textDrawVector.clear();
	int ilinec = ((int)bottomLine < 0) ? 0 : (int)bottomLine-1;
	for(int i = 0;ilinec+i<lines.size() && ((i+1)*fontSizeSpacing + 3) <= window.getSize().y;i++) {

		std::vector<string_to_display> strDisplay;

		int before;
		int last;
		for(int j = 0;j<1;j++) {
			int k = 0;
			before = 0;
			last = 0;
			while(k<lines.at(i+ilinec).length()) {
				std::vector<std::string> keywordsNow(keywords);

				for(int z = 0;z<keywordsSpecial.size();z++) {
					keywordsNow.push_back(keywordsSpecial.at(z));
				}

				std::size_t pos = lines.at(i+ilinec).find(keywordsNow.at(j), k);
				int newpos = 0;
				bool specialOnes = false;
				for(int x = 0;x<keywordsNow.size();x++) {
					std::size_t pos2 = lines.at(i+ilinec).find(keywordsNow.at(x), k);
					if(x > keywords.size()-1) {
						specialOnes = true;
					}else {
						specialOnes = false;
					}
					
					if(pos2 < pos) {
						pos = pos2;
						newpos = x;
					}
				}
				//std::cout << "fgjghj" << std::endl;
				if(pos != std::string::npos) {
					if(specialOnes) {
						string_to_display strtop;

						strtop.str = lines.at(i+ilinec).substr(last, pos - last);
						strtop.highlight = false;
						strtop.stdLength = strtop.str.length();
						strDisplay.push_back(strtop);

						strtop.str = lines.at(i+ilinec).substr(pos, keywordsNow.at(newpos).length());
						strtop.highlight = true;
						strtop.stdLength = strtop.str.length();
						strDisplay.push_back(strtop);
						before = pos + keywordsNow.at(newpos).length() ;
						k = pos + keywordsNow.at(newpos).length();
						last = pos + keywordsNow.at(newpos).length();
					}else if(pos > 0 && pos + keywords.at(newpos).length() < lines.at(i+ilinec).length()-1) {
						if(!iswalnum(lines.at(i+ilinec).at(pos-1)) && !iswalnum(lines.at(i+ilinec).at(pos + keywords.at(newpos).length()))) {
							string_to_display strtop;

							strtop.str = lines.at(i+ilinec).substr(last, pos - last);
							strtop.highlight = false;
							strtop.stdLength = strtop.str.length();
							strDisplay.push_back(strtop);

							strtop.str = lines.at(i+ilinec).substr(pos, keywords.at(newpos).length());
							strtop.highlight = true;
							strtop.stdLength = strtop.str.length();
							strDisplay.push_back(strtop);
							before = pos + keywords.at(newpos).length() ;
							k = pos + keywords.at(newpos).length();
							last = pos + keywords.at(newpos).length();
							//std::cout << "adfasdf" << std::endl;

							//string_to_display strtop;
							//k += lines.at(i+ilinec).length();
						}else {
							k++;
						}
					}else {
							string_to_display strtop;
							strtop.str = lines.at(i+ilinec).substr(before, pos + keywords.at(newpos).length());
							strtop.highlight = true;
							strtop.stdLength = strtop.str.length();
							strDisplay.push_back(strtop);
							before = pos + keywords.at(newpos).length() ;
							k = pos + keywords.at(newpos).length();
							last = pos + keywords.at(newpos).length();
							//std::cout << "adfasdf" << std::endl;
					}	
				}else {
						string_to_display strtop;
						strtop.str = lines.at(i+ilinec).substr(last, lines.at(i+ilinec).length());
						strtop.highlight = false;
						strtop.stdLength = strtop.str.length();
						strDisplay.push_back(strtop);
						k += lines.at(i+ilinec).length();
				}
			}
		}

		int abstand = 0;
		for(int j = 0;j<strDisplay.size();j++) {
			sf::Font f2 = font;
			if(strDisplay.at(j).highlight) {
				//textDraw.setStyle(sf::Text::Bold);
				textDraw.setColor(sf::Color(0, 119, 0));
			}else {
				textDraw.setColor(sf::Color::Blue);
			}
		
			textDraw.setString(strDisplay.at(j).str);
			textDraw.setPosition(editor.getGreyBlockSize() + abstand * getCharWidth(), i*fontSizeSpacing + 3);
			window.draw(textDraw);

			for(int k = 0;k<strDisplay.at(j).stdLength;k++) {
				if(strDisplay.at(j).str.at(k) == '	') {
					abstand += 4;
				}else {
					abstand++;
				}
			}

			textDraw.setColor(sf::Color::Black);
			//textDraw.setStyle(sf::Text::Regular);

			//std::cout << strDisplay.at(j).str << std::endl;
		}	
		
		
	
		textDraw.setString(std::to_string(i+ilinec+1));
		textDraw.setPosition(editor.getGreyBlockSize() - textDraw.getString().getSize() * getCharWidth() - 5, i*fontSizeSpacing+3);
		textDrawVector.push_back(textDraw);
	}
	drawText(window);
	//window.display();	
	drawText(window);
}*/

int main(int argc, char *argv[]) {
	std::string path1 = "";

	if(argc == 2) {
		path1 = std::string(argv[1]);
	}

	FRONTEND_P20241023_TEXTEDIT::EditorMouse m_t;
	FRONTEND_P20241023_TEXTEDIT::Text s_t;
	FRONTEND_P20241023_TEXTEDIT::MarkedText cursor_MT;
	FRONTEND_P20241023_TEXTEDIT::Cursor s_c(cursor_MT);
	FRONTEND_P20241023_TEXTEDIT::Slider slider_t(1200 - 10, 0);

	Editor editor(s_t, s_c, slider_t);
	
	s_t.loadText();
	s_c.loadCursor(editor, s_t);

	editor.setTextObj(s_t);
	editor.setCursorObj(s_c);
	editor.setSliderObj(slider_t);
	editor.loadMouse(m_t);
	editor.loadEditor(path1);
}

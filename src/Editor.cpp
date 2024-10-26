#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iterator>
#include <windows.h>
#include <shobjidl.h>
#include <objbase.h>

#include "FRONTEND_P20241023_TEXTEDIT/FRONTEND_P20241023_TEXTEDIT.h"
#include "FRONTEND_P20241023_TEXTEDIT/EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT/Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT/Slider.h"
#include "FRONTEND_P20241023_TEXTEDIT/Text.h"
#include "FRONTEND_P20241023_TEXTEDIT/MarkedText.h"
#include "Editor.h"

//Editor::Editor(FRONTEND_P20241023_TEXTEDIT::Text &text, FRONTEND_P20241023_TEXTEDIT::Cursor &cursor, FRONTEND_P20241023_TEXTEDIT::Slider &slider, FRONTEND_P20241023_TEXTEDIT::EditorMouse &mouse)  : text(text), cursor(cursor), slider(slider), mouse(mouse) {
Editor::Editor() {
	/*setTextObj(text);
	setCursorObj(cursor);
	setSliderObj(slider);*/
	//cursor.loadCursor(*this, text);
	
	window.create(sf::VideoMode(1200, 900), "Sovieditor");
	window.setFramerateLimit(60);

	/*HWND win = window.getSystemHandle();
	SetWindowLongPtr(win, GWL_EXSTYLE, GetWindowLongPtr(win, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(window.getSystemHandle(), 0x00FFFFFF, 228, LWA_ALPHA);
	*/

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
	std::string file_path = "../main_v_6.txt";//fileDialogWinApi();
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
			file_path = "../main_v_6.txt";
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
			window.setMouseCursor(c);*/
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
	window.draw(background);

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
	text.countChars(&nothing, *this, text.getLine(cursor.getCursorLineNr()), cursor);
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
	text.countChars(&nothing, *this, text.getLine(cursor.getCursorLineNr()), cursor);

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


void Editor::setMouseInUse() {
	mouse.setInUse(true);
}

void Editor::unsetMouseInUse() {
	mouse.setInUse(false);
}

void Editor::loadMouse(FRONTEND_P20241023_TEXTEDIT::EditorMouse &m) {
	this->mouse = m;
}

bool Editor::getSliderInUse() {
	return slider.getInUse();
}

int Editor::getLeftIndent() {
	return slider.getSliderWidth();
}

bool Editor::getMouseInRange() {
	return mouseInRange;
}

void Editor::setMouseInRange(bool s) {
	mouseInRange = s;
}

void Editor::setFilePath(std::string p) {
	path = p;
}

void Editor::setTextObj(FRONTEND_P20241023_TEXTEDIT::Text text) {
	this->text = text;
}

void Editor::setCursorObj(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor) {
	this->cursor = cursor;
	
	cursor.loadCursor(*this, text);
}

void Editor::setSliderObj(FRONTEND_P20241023_TEXTEDIT::Slider slider) {
	this->slider = slider;
}

int Editor::getGreyBlockSize() {
	return GreyBlockSize;
}

void Editor::setGreyBlockSize(int x) {
	GreyBlockSize = x;
}

sf::Vector2u Editor::wGetSize() {
	return window.getSize();
}

bool Editor::getCTRL() {
	return setCTRL;
}

void Editor::onCTRL() {
	setCTRL = true;
}

void Editor::offCTRL() {
	setCTRL = false;
}

void Editor::onAlt() {
	setAlt = true;
}

void Editor::offAlt() {
	setAlt = false;
}

bool Editor::getAlt() {
	return setAlt;
}

void Editor::setTitleNotSaved() {
	window.setTitle(wTitle + "*");
}

void Editor::setTitleSaved() {
	window.setTitle(wTitle);
}

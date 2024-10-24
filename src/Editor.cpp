#ifndef Editor
#define Editor

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iterator>
#include <windows.h>
#include <shobjidl.h>
#include <objbase.h>

#include "FRONTEND_P20241023_TEXTEDIT.h"
#include "FRONTEND_P20241023_TEXTEDIT_EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT_Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT_Slider.h"
#include "FRONTEND_P20241023_TEXTEDIT_Text.h"*/
#include "FRONTEND_P20241023_TEXTEDIT_MarkedText.h"
#include "Editor.h"

Editor::Editor() {
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

void Editor::setTextObj(FRONTEND_P20241023_TEXTEDIT::Text &text) {
	this->text = text;
}

void Editor::setCursorObj(FRONTEND_P20241023_TEXTEDIT::Cursor &cursor) {
	this->cursor = cursor;
	
	cursor.loadCursor(*this, text);
}

void Editor::setSliderObj(FRONTEND_P20241023_TEXTEDIT::Slider &slider) {
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


#endif
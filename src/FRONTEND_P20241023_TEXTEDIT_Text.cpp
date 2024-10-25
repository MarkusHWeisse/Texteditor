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

FRONTEND_P20241023_TEXTEDIT::Text::Text() {
	keywords = {"/*", "*/", "//", "void", "int", "double", "float", "bool", "return", "break", "switch", "case", "class", "struct", "if", "else", "while", "for", "#include", "#if",
	"#define", "#ifndef", "#endif", "public:", "private:", "string", "std", "sf"};
	keywordsSpecial = {"{", "}", "=", "!", "(", ")", ";", ":", "+", "-", "*", "/", "\"", ">", ",", "<"};

	setFontSize(14, 20);
}

int FRONTEND_P20241023_TEXTEDIT::Text::getFontSize() {
	return fontSize;
}

int FRONTEND_P20241023_TEXTEDIT::Text::getFontSizeSpacing() {
	return fontSizeSpacing;
}

void FRONTEND_P20241023_TEXTEDIT::Text::setFontSize(int real, int spacing) {
	fontSize = real;
	fontSizeSpacing = spacing;
}

float FRONTEND_P20241023_TEXTEDIT::Text::getBottomLine() {
	return bottomLine;
}

void FRONTEND_P20241023_TEXTEDIT::Text::setBottomLine(float x) {
	bottomLine = x;
}

std::string FRONTEND_P20241023_TEXTEDIT::Text::getLine(int x) {
	return lines.at(x);
} 

int FRONTEND_P20241023_TEXTEDIT::Text::getCharWidth() {
	return textWidths.charWidth;
}

int FRONTEND_P20241023_TEXTEDIT::Text::getTabWidth() {
	return textWidths.tabWidth;
}

int FRONTEND_P20241023_TEXTEDIT::Text::getTextWidth() {
	return textWidths.textWidth;
}

int FRONTEND_P20241023_TEXTEDIT::Text::getLineSize() {
	return lines.size();
}

void FRONTEND_P20241023_TEXTEDIT::Text::insertLines(int cursorLineNr, std::string text) {
	lines.insert(lines.begin() + cursorLineNr, text);
}

void FRONTEND_P20241023_TEXTEDIT::Text::deleteLine(int x) {
	lines.erase(lines.begin() + x);
}

void FRONTEND_P20241023_TEXTEDIT::Text::addText(int x, std::string textAdd) {
	lines.at(x) += textAdd;
}

void FRONTEND_P20241023_TEXTEDIT::Text::setText(int x, std::string textSet) {
	lines.at(x) = textSet;
}

void FRONTEND_P20241023_TEXTEDIT::Text::setAllowInput() {
	allowInput = true;
}

void FRONTEND_P20241023_TEXTEDIT::Text::denieInput() {
	allowInput = false;
}

bool FRONTEND_P20241023_TEXTEDIT::Text::allowInputSet() {
	return allowInput;
}

static void FRONTEND_P20241023_TEXTEDIT::Text::countCharsSize(int* outVal, int* i, int* size) {
	(*(int*)(outVal)) = (*i)+1;
}
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "FRONTEND_P20241023_TEXTEDIT.h"
#include "FRONTEND_P20241023_TEXTEDIT_EditorMouse.h"
#include "FRONTEND_P20241023_TEXTEDIT_Cursor.h"
#include "FRONTEND_P20241023_TEXTEDIT_Slider.h"
#include "FRONTEND_P20241023_TEXTEDIT_Text.h"
#include "FRONTEND_P20241023_TEXTEDIT_MarkedText.h"
#include "Editor.h"

namespace FRONTEND_P20241023_TEXTEDIT {

Text::Text() {
	keywords = {"/*", "*/", "//", "void", "int", "double", "float", "bool", "return", "break", "switch", "case", "class", "struct", "if", "else", "while", "for", "#include", "#if",
	"#define", "#ifndef", "#endif", "public:", "private:", "string", "std", "sf"};
	keywordsSpecial = {"{", "}", "=", "!", "(", ")", ";", ":", "+", "-", "*", "/", "\"", ">", ",", "<"};

	setFontSize(14, 20);
}


void Text::drawText(sf::RenderWindow &window) {
	for(int i = 0;i<textDrawVector.size();++i) {
		window.draw(textDrawVector.at(i));
	}
}

/*
*	Either count the number of characters with respect to the tab or change the X-Position of the Cursor if it 
*	would otherwise be stuck inside a tab(when moving up and down it check if we would move inside a tab and then 
*	changes our psoition before the tab). 
*/
void Text::countChars(void* outVal, Editor &editor, std::string s1, Cursor &cursor) { //, void func(int* outVal2, int* igive, int* sgive)
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
			//(*(int*)(outVal)) = (*i)+1;
			//(func(&return1, &i, &sizeChars));
			(*(int*)(outVal)) = return1;
			return;
		}else if(sizeChars > (cursor.getPosX()) - editor.getGreyBlockSize()) {
			cursor.setPosX(sizeCharsBefore + editor.getGreyBlockSize());
			return;
		}
	}
		
	cursor.setPosX(sizeChars + editor.getGreyBlockSize());
		
}

int Text::getSize(int lineNr, int charNr) {
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

void Text::loadEvents(Editor &editor, Cursor &cursor, sf::Event &event) {
	if(event.type == sf::Event::TextEntered && allowInputSet()) {
		int cursorCharNr = 0;
		countChars(&cursorCharNr, editor, getLine(cursor.getCursorLineNr()), cursor);
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

void Text::loadText() {
	loadVars();
	loadTextWidthsBounds(bottomLine-1);
}

void Text::loadVars() {
	bottomLine = 1;
	allowInput = true;
}

void Text::loadFile(std::string file) {
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

int Text::loadFont(std::string sfont) {
	if(!font.loadFromFile(sfont)) {
		std::cout << "no font";
		return 0;
	}
	return 1;
}

void Text::loadTextWidthsBounds(int lineNr) {
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

void Text::insertText(int cursorLineNr, int cursorCharNr, char insert, bool deleteB) {
	std::string sinsert;
	if(deleteB) {
		sinsert = "";
	}else {
		sinsert = insert;
	}

	lines.at(cursorLineNr) = lines.at(cursorLineNr).substr(0, cursorCharNr-(deleteB ? 1 : 0)) + sinsert + lines.at(cursorLineNr).substr(cursorCharNr, lines.at(cursorLineNr).size()-(cursorCharNr));
}

void Text::loadDraw(sf::RenderWindow &window, Editor &editor) {
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
}


int Text::getFontSize() {
	return fontSize;
}

int Text::getFontSizeSpacing() {
	return fontSizeSpacing;
}

void Text::setFontSize(int real, int spacing) {
	fontSize = real;
	fontSizeSpacing = spacing;
}

float Text::getBottomLine() {
	return bottomLine;
}

void Text::setBottomLine(float x) {
	bottomLine = x;
}

std::string Text::getLine(int x) {
	return lines.at(x);
} 

int Text::getCharWidth() {
	return textWidths.charWidth;
}

int Text::getTabWidth() {
	return textWidths.tabWidth;
}

int Text::getTextWidth() {
	return textWidths.textWidth;
}

int Text::getLineSize() {
	return lines.size();
}

void Text::insertLines(int cursorLineNr, std::string text) {
	lines.insert(lines.begin() + cursorLineNr, text);
}

void Text::deleteLine(int x) {
	lines.erase(lines.begin() + x);
}

void Text::addText(int x, std::string textAdd) {
	lines.at(x) += textAdd;
}

void Text::setText(int x, std::string textSet) {
	lines.at(x) = textSet;
}

void Text::setAllowInput() {
	allowInput = true;
}

void Text::denieInput() {
	allowInput = false;
}

bool Text::allowInputSet() {
	return allowInput;
}

}

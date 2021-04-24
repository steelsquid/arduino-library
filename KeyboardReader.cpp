#include "KeyboardReader.h"


//##########################################################################################
KeyboardReader::KeyboardReader(){
	KeyboardReader(64);
}


//##########################################################################################
KeyboardReader::KeyboardReader(int maxLength){
	_maxLength = maxLength;
	_text = new char[_maxLength];
}


//##########################################################################################
String KeyboardReader::getText(){
	if(_index < _maxLength){
		_text[_index] = '\0';
	}
	return String(_text);
}


//##########################################################################################
void KeyboardReader::clearText(){
	_index = 0;
}


//##########################################################################################
void KeyboardReader::addChar(char c){
	if(c >= 32 && c <= 126 && _index < _maxLength){
		_keyPressed = true;
		_text[_index] = c;
		_index++;
	}
	else if(c==8 && _index > 0){
		_keyPressed = true;
		_index--;
		_text[_index] = ' ';
	}
	else if(c==27){
		_keyPressed = true;
		clearText();
	}
	else if(c==13){
		_enterPressed = true;
	}
	else if(c==9){
		_tabPressed = true;
	}
	else if(c==181){
		_upPressed = true;
	}
	else if(c==180){
		_leftPressed = true;
	}
	else if(c==183){
		_rightPressed = true;
	}
	else if(c==182){
		_downPressed = true;
	}
}


//##########################################################################################
bool KeyboardReader::isKeyPressed(){
	if(_keyPressed == true){
		_keyPressed = false;
		return true;
	}
	else{
		return false;
	}
}


//##########################################################################################
bool KeyboardReader::isEnterPressed(){
	if(_enterPressed == true){
		_enterPressed = false;		
		return true;
	}
	else{
		return false;
	}
}


//##########################################################################################
bool KeyboardReader::isTabPressed(){
	if(_tabPressed == true){
		_tabPressed = false;		
		return true;
	}
	else{
		return false;
	}
}


//##########################################################################################
bool KeyboardReader::isUpPressed(){
	if(_upPressed == true){
		_upPressed = false;		
		return true;
	}
	else{
		return false;
	}
}


//##########################################################################################
bool KeyboardReader::isLeftPressed(){
	if(_leftPressed == true){
		_leftPressed = false;		
		return true;
	}
	else{
		return false;
	}
}


//##########################################################################################
bool KeyboardReader::isRightPressed(){
	if(_rightPressed == true){
		_rightPressed = false;		
		return true;
	}
	else{
		return false;
	}
}


//##########################################################################################
bool KeyboardReader::isDownPressed(){
	if(_downPressed == true){
		_downPressed = false;		
		return true;
	}
	else{
		return false;
	}
}



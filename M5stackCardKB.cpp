#include "M5stackCardKB.h"


//##########################################################################################
M5stackCardKB::M5stackCardKB(int maxLineLength){
	_keyboard = KeyboardReader(maxLineLength);
}


//##########################################################################################
void M5stackCardKB::check(){
	Wire.requestFrom(CARDKB_ADDR, 1);
	if(Wire.available()){
		_keyboard.addChar(Wire.read());
	}
}


//##########################################################################################
void M5stackCardKB::clearText(){
	_keyboard.clearText();
}


//##########################################################################################
String M5stackCardKB::getText(){
	return _keyboard.getText();
}


//##########################################################################################
bool M5stackCardKB::isKeyPressed(){
	return _keyboard.isKeyPressed();
}


//##########################################################################################
bool M5stackCardKB::isEnterPressed(){
	return _keyboard.isEnterPressed();
}


//##########################################################################################
bool M5stackCardKB::isTabPressed(){
	return _keyboard.isTabPressed();
}


//##########################################################################################
bool M5stackCardKB::isUpPressed(){
	return _keyboard.isUpPressed();
}


//##########################################################################################
bool M5stackCardKB::isLeftPressed(){
	return _keyboard.isLeftPressed();
}


//##########################################################################################
bool M5stackCardKB::isRightPressed(){
	return _keyboard.isRightPressed();
}


//##########################################################################################
bool M5stackCardKB::isDownPressed(){
	return _keyboard.isDownPressed();
}


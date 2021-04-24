#ifndef M5stackCardKB_h
#define M5stackCardKB_h


#include <Steelsquid.h>
#include <KeyboardReader.h>
#include <Wire.h>


#define CARDKB_ADDR 0x5F


class M5stackCardKB{
	public:
		M5stackCardKB(int maxLineLength);
		void check();
		String getText();
		void clearText();
		bool isKeyPressed();
		bool isEnterPressed();
		bool isTabPressed();
		bool isUpPressed();
		bool isLeftPressed();
		bool isRightPressed();
		bool isDownPressed();
		
	private:
		KeyboardReader _keyboard;
};


#endif


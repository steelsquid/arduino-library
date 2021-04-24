#ifndef KeyboardReader_h
#define KeyboardReader_h


#include <Steelsquid.h>


class KeyboardReader{
	public:
		KeyboardReader();
		KeyboardReader(int maxLength);
		String getText();
		void clearText();
		void addChar(char c);
		bool isKeyPressed();
		bool isEnterPressed();
		bool isTabPressed();
		bool isUpPressed();
		bool isLeftPressed();
		bool isRightPressed();
		bool isDownPressed();
		
	private:
		char* _text;
		int _maxLength;
		int _index = 0;
		bool _keyPressed = false;
		bool _enterPressed = false;
		bool _tabPressed = false;
		bool _upPressed = false;
		bool _leftPressed = false;
		bool _rightPressed = false;
		bool _downPressed = false;
};


#endif


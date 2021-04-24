#ifndef Ssd1306_h
#define Ssd1306_h


#include <Steelsquid.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>


class Ssd1306{
	public:
		Ssd1306();
		Ssd1306(int width, int height);
		void init();
		void printTextToScreen(String text);
		
	private:
		Adafruit_SSD1306 _display;
};


#endif


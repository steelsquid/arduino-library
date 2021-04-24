#include "Ssd1306.h"


//##########################################################################################
Ssd1306::Ssd1306(){
	 Ssd1306(128, 64);
}


//##########################################################################################
Ssd1306::Ssd1306(int width, int height){
	 _display = Adafruit_SSD1306(width, height, &Wire, -1);
}


//##########################################################################################
void Ssd1306::init(){
	if(!_display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
		Serial.println("SSD1306 allocation failed");
		exit(0);
    }
    else{
		_display.setTextSize(1);
		_display.setTextColor(WHITE);
		_display.clearDisplay();
		_display.display();	
	}
}


//##########################################################################################
void Ssd1306::printTextToScreen(String text){
	_display.clearDisplay();
	_display.setCursor(0, 0);
	_display.print(text);
	_display.display();	
}


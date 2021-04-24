#include "Feather.h"


#define VBATPIN A7


//##########################################################################################
Feather::Feather(){
}


//##########################################################################################
float Feather::batteryVoltage(){
	float v = analogRead(VBATPIN);
	v *= 2;
	v *= 3.3;
	v /= 1024;
	return v;
}


//##########################################################################################
byte Feather::batteryPercent(){
	float v = batteryVoltage();
	if(v >= 4.2){
		return 100;
	}
	else if(v < 4.2 && v >= 4.15){
		return 95;
	}
	else if(v < 4.15 && v >= 4.11){
		return 90;
	}
	else if(v < 4.11 && v >= 4.08){
		return 85;
	}
	else if(v < 4.08 && v >= 4.02){
		return 80;
	}
	else if(v < 4.02 && v >= 3.98){
		return 75;
	}
	else if(v < 3.98 && v >= 3.95){
		return 70;
	}
	else if(v < 3.95 && v >= 3.91){
		return 65;
	}
	else if(v < 3.91 && v >= 3.87){
		return 60;
	}
	else if(v < 3.87 && v >= 3.85){
		return 55;
	}
	else if(v < 3.85 && v >= 3.84){
		return 50;
	}
	else if(v < 3.84 && v >= 3.82){
		return 45;
	}
	else if(v < 3.82 && v >= 3.8){
		return 40;
	}
	else if(v < 3.8 && v >= 3.79){
		return 35;
	}
	else if(v < 3.79 && v >= 3.77){
		return 30;
	}
	else if(v < 3.77 && v >= 3.75){
		return 25;
	}
	else if(v < 3.75 && v >= 3.73){
		return 20;
	}
	else if(v < 3.73 && v >= 3.71){
		return 15;
	}
	else if(v < 3.71 && v >= 3.69){
		return 10;
	}
	else if(v < 3.69 && v >= 3.61){
		return 5;
	}
	else{
		return 0;
	}
}



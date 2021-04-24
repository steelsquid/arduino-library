#include "Steelsquid.h"


long Steelsquid::_executeEveryMs[4]; 

typedef union {
    double val;
    byte bytes[8];
} doubleval;


//##########################################################################################
void Steelsquid::init(){	
	Serial.begin(115200);
	#ifdef DEBUG
		while (!Serial) {
		}		
	#endif	
}


//##########################################################################################
bool Steelsquid::executeEvery(int nr, long ms){
	if(millis() - Steelsquid::_executeEveryMs[nr] > ms){
		Steelsquid::_executeEveryMs[nr] = millis();
		return true;
	}
	else{
		return false;
	}
}


//##########################################################################################
byte Steelsquid::crc(byte* intArray){
    byte c = 0;
    while(*intArray != '\0')
        c ^= *intArray++;
    return c;
}


//##########################################################################################
double Steelsquid::toDouble(byte* bytes, int startIndex = 0){
	doubleval v;
	v.bytes[0] = bytes[startIndex];
	v.bytes[1] = bytes[startIndex + 1];
	v.bytes[2] = bytes[startIndex + 2];
	v.bytes[3] = bytes[startIndex + 3];
	v.bytes[4] = bytes[startIndex + 4];
	v.bytes[5] = bytes[startIndex + 5];
	v.bytes[6] = bytes[startIndex + 6];
	v.bytes[7] = bytes[startIndex + 7];
	return v.val;
}

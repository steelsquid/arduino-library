#ifndef Steelsquid_h
#define Steelsquid_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

#include <avr/dtostrf.h>


class Steelsquid{
	public:
		static void init();
		static bool executeEvery(int nr, long ms);
		static byte crc(byte* intArray);
		static double toDouble(byte* bytes, int startIndex);
	private:
		static long _executeEveryMs[];
		
};


#endif


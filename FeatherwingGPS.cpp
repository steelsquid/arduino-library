#include "FeatherwingGPS.h"

int _latDegrees = 0;
double _latMinutes = 0;
int _longDegrees = 0;
double _longMinutes = 0;


//##########################################################################################
FeatherwingGPS::FeatherwingGPS(){
}


//##########################################################################################
void FeatherwingGPS::init(){
	while (!Serial1);
	Serial1.begin(9600);
	delay(10);
	Serial1.println(PMTK_SET_NMEA_UPDATE_5HZ);
	delay(10);
	Serial1.println(PMTK_API_SET_FIX_CTL_5HZ);
	delay(10);
	Serial1.println(PMTK_SET_NMEA_OUTPUT_RMCONLY);
	delay(10);
}


//##########################################################################################
void FeatherwingGPS::_check(){
	if (Serial1.available()) {
		char c = Serial1.read();
		if(c != -1){
			_buffer[_counter] = c;
			_counter++;
			if(_counter>127){
				_counter = 0;
			}
			else if(c == '\n'){
				if(_isBufferOk(_counter)){
					_lock = true;

					char tempLatDegrees[2] = {_buffer[20], _buffer[21]};
					_latDegrees = atoi(tempLatDegrees);
					char tempLatMinutes[7] = {_buffer[22], _buffer[23], _buffer[24], _buffer[25], _buffer[26], _buffer[27], _buffer[28]};
					_latMinutes = atof(tempLatMinutes);
					_latNS = _buffer[30];

					char tempLongDegrees[3] = {_buffer[32], _buffer[33], _buffer[34]};
					_longDegrees = atoi(tempLongDegrees);
					char tempLongMinutes[7] = {_buffer[35], _buffer[36], _buffer[37], _buffer[38], _buffer[39], _buffer[40], _buffer[41]};
					_longMinutes = atof(tempLongMinutes);
					_longEW = _buffer[43];
					
					char tempSpeed[4] = {_buffer[45], _buffer[46], _buffer[47], _buffer[48]};
					_speed = atof(tempSpeed);
					
					char tempAngle[6] = {_buffer[50], _buffer[51], _buffer[52], _buffer[53], _buffer[54], _buffer[55]};
					_angle = atof(tempAngle);
				}
				else{
					_lock = false;				
				}
				_counter = 0;
			}
		}
	}
}


//##########################################################################################
bool FeatherwingGPS::_isBufferOk(int count){
	if(count > 56){
		bool head = _buffer[0]=='$' && _buffer[1]=='G' && _buffer[2]=='P' && _buffer[3]=='R' && _buffer[4]=='M' && _buffer[5]=='C' && _buffer[18]=='A';

		bool latDegrees = isDigit(_buffer[20]) && isDigit(_buffer[21]);
		bool latMinutes = isDigit(_buffer[22]) && isDigit(_buffer[23]) && _buffer[24]=='.' && isDigit(_buffer[25]) && isDigit(_buffer[26]) && isDigit(_buffer[27]) && isDigit(_buffer[28]);
		bool latNS = _buffer[30]=='N' || _buffer[30]=='S';

		bool longDegrees = isDigit(_buffer[32]) && isDigit(_buffer[33]) && isDigit(_buffer[34]);
		bool longMinutes = isDigit(_buffer[35]) && isDigit(_buffer[36]) && _buffer[37]=='.' && isDigit(_buffer[38]) && isDigit(_buffer[39]) && isDigit(_buffer[40]) && isDigit(_buffer[41]);
		bool longEW = _buffer[43]=='E' || _buffer[43]=='W';

		bool speed = isDigit(_buffer[45]) && (isDigit(_buffer[46]) || _buffer[46]=='.') && (isDigit(_buffer[47]) || _buffer[47]=='.') && isDigit(_buffer[48]);
		bool angle = isDigit(_buffer[50]) && (isDigit(_buffer[51]) || _buffer[51]=='.') && (isDigit(_buffer[52]) || _buffer[52]=='.') && (isDigit(_buffer[53]) || _buffer[53]=='.') && (isDigit(_buffer[54]) || _buffer[54]=='.') && isDigit(_buffer[55]);
		
		return head && latDegrees && latMinutes && latNS && longDegrees && longMinutes && longEW && speed && angle;
	}
	else{
		return false;
	}
}


//##########################################################################################
bool FeatherwingGPS::hasLock(){
	_check();
	return _lock;
}


//##########################################################################################
int FeatherwingGPS::latDegrees(){
	return _latDegrees;
}


//##########################################################################################
double FeatherwingGPS::latMinutes(){
	return _latMinutes;
}


//##########################################################################################
char FeatherwingGPS::latNS(){
	return _latNS;
}


//##########################################################################################
int FeatherwingGPS::longDegrees(){
	return _longDegrees;
}


//##########################################################################################
double FeatherwingGPS::longMinutes(){
	return _longMinutes;
}


//##########################################################################################
char FeatherwingGPS::longEW(){
	return _longEW;
}


//##########################################################################################
double FeatherwingGPS::speed(){
	return _speed;
}


//##########################################################################################
double FeatherwingGPS::angle(){
	return _angle;
}


//##########################################################################################
double FeatherwingGPS::latitude(){
	double d = latDegrees() + (latMinutes()/(double)60);
	if(_latNS == 'S'){
		d = d * -1;
	}
	return d;
}


//##########################################################################################
double FeatherwingGPS::longitude(){
	double d = longDegrees() + (longMinutes()/(double)60);
	if(_longEW == 'W'){
		d = d * -1;
	}
	return d;
}

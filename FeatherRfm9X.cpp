#include "FeatherRfm9X.h"


RH_RF95 _rf95 = RH_RF95(RFM95_CS, RFM95_INT);	
byte _deviceAddress = 0;
byte _historyCounter = 255;
bool _isRepeter = false;
byte _lastRxLength = 0;
byte _txFrom = 0;
byte _txTo = 0;
byte _txCounter = 255;
byte _txType = 255;


//##########################################################################################
FeatherRfm9X::FeatherRfm9X(float frequency, int transmitterPower, long bandwidth, byte spreadingFactory, byte codingRate){
	randomSeed(analogRead(0));
	_frequency = frequency;
	_transmitterPower = transmitterPower;
	_bandwidth = bandwidth;
	_spreadingFactory = spreadingFactory;
	_codingRate = codingRate;
}


//##########################################################################################
void FeatherRfm9X::init(){
	init(random(255));
}


//##########################################################################################
void FeatherRfm9X::init(byte deviceAddress){
	_isRepeter = false;
	_deviceAddress = deviceAddress;
	_rf95.setThisAddress(deviceAddress);
	_rf95.setHeaderFrom(deviceAddress);
	_rf95.setHeaderTo(BROADCAST_ADDRESS);
	_rf95.setPromiscuous(false);
	_txFrom = deviceAddress;
	_txTo = BROADCAST_ADDRESS;

	_initRfm9X();
}


//##########################################################################################
void FeatherRfm9X::init(byte deviceAddress, byte _toAddress){
	init(deviceAddress);
	toAddress(_toAddress);
}


//##########################################################################################
void FeatherRfm9X::initRepeter(){
	initRepeter(random(255));
}


//##########################################################################################
void FeatherRfm9X::initRepeter(byte deviceAddress){
	_isRepeter = true;
	_deviceAddress = deviceAddress;
	_rf95.setThisAddress(deviceAddress);
	_rf95.setHeaderFrom(deviceAddress);
	_rf95.setPromiscuous(true);

	_initRfm9X();
}


//##########################################################################################
void FeatherRfm9X::_initRfm9X(){
	for(int i=0; i<15; i++){
		_historyFrom[i] = NULL;
		_historyTo[i] = NULL;
		_historyCount[i] = NULL;
		_historyType[i] = NULL;
		_historyTimestamp[i] = NULL;
	}		
				
	pinMode(RFM95_RST, OUTPUT);
	digitalWrite(RFM95_RST, HIGH);	
	
	delay(100);
	digitalWrite(RFM95_RST, LOW);
	delay(10);
	digitalWrite(RFM95_RST, HIGH);
	delay(10);
 
	
	while (!_rf95.init()) {
		Serial.println("LoRa radio init failed");
		exit(0);
	}

	if (!_rf95.setFrequency(_frequency)) {
		Serial.println("setFrequency failed");
		exit(0);
	}
	
	_rf95.setTxPower(_transmitterPower, false);
	_rf95.setPayloadCRC(true);
	_rf95.setSignalBandwidth(_bandwidth);
	_rf95.setSpreadingFactor(_spreadingFactory);
	_rf95.setCodingRate4(_codingRate);
	delay(100);
}


//##########################################################################################
void FeatherRfm9X::toAddress(byte _toAddress){
	_rf95.setHeaderTo(_toAddress);
	_txTo = _toAddress;
}


//##########################################################################################
void FeatherRfm9X::transmitRepeterPing(byte* data, byte length){
	_rf95.setHeaderId(_getTxCounter());
	_checkHistory();
	_setTxHeaderFlags(TYPE_REPETER_PING);
	_addTxToHistory();
	for(int i=0; i<length; i++){
		_buffer[i] = data[i];
	}
	delay(10);
	_rf95.send(_buffer, length);
	delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}


//##########################################################################################
void FeatherRfm9X::transmitRepeterPong(byte* data, byte length){
	_rf95.setHeaderFrom(_deviceAddress);
	_rf95.setHeaderId(_getTxCounter());
	_checkHistory();
	_setTxHeaderFlags(TYPE_REPETER_PONG);
	_addTxToHistory();
	for(int i=0; i<length; i++){
		_buffer[i] = data[i];
	}
	delay(10);
	_rf95.send(_buffer, length);
	delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}


//##########################################################################################
void FeatherRfm9X::transmitPing(byte* data, byte length){
	_rf95.setHeaderId(_getTxCounter());
	_checkHistory();
	_setTxHeaderFlags(TYPE_PING);
	_addTxToHistory();
	for(int i=0; i<length; i++){
		_buffer[i] = data[i];
	}
	delay(10);
	_rf95.send(_buffer, length);
	delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}


//##########################################################################################
void FeatherRfm9X::transmitPong(byte* data, byte length){
	_rf95.setHeaderId(_getTxCounter());
	_checkHistory();
	_setTxHeaderFlags(TYPE_PONG);
	_addTxToHistory();
	for(int i=0; i<length; i++){
		_buffer[i] = data[i];
	}
	delay(10);
	_rf95.send(_buffer, length);
	delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}


//##########################################################################################
void FeatherRfm9X::transmitEnq(byte* data, byte length){
	_rf95.setHeaderId(_getTxCounter());
	_checkHistory();
	_setTxHeaderFlags(TYPE_ENQ);
	_addTxToHistory();
	for(int i=0; i<length; i++){
		_buffer[i] = data[i];
	}
	delay(10);
	_rf95.send(_buffer, length);
	delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}



//##########################################################################################
void FeatherRfm9X::transmitAck(byte* data, byte length){
	_rf95.setHeaderId(_getTxCounter());
	_checkHistory();
	_setTxHeaderFlags(TYPE_ACK);
	_addTxToHistory();
	for(int i=0; i<length; i++){
		_buffer[i] = data[i];
	}
	delay(10);
	_rf95.send(_buffer, length);
	delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}


//##########################################################################################
void FeatherRfm9X::transmitNak(byte* data, byte length){
	_rf95.setHeaderId(_getTxCounter());
	_checkHistory();
	_setTxHeaderFlags(TYPE_NAK);
	_addTxToHistory();
	for(int i=0; i<length; i++){
		_buffer[i] = data[i];
	}
	delay(10);
	_rf95.send(_buffer, length);
	delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}


//##########################################################################################
void FeatherRfm9X::transmitBell(byte* data, byte length){
	_rf95.setHeaderId(_getTxCounter());
	_checkHistory();
	_setTxHeaderFlags(TYPE_BELL);
	_addTxToHistory();
	for(int i=0; i<length; i++){
		_buffer[i] = data[i];
	}
	delay(10);
	_rf95.send(_buffer, length);
	delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}


//##########################################################################################
void FeatherRfm9X::transmitByte(byte data){
	_rf95.setHeaderId(_getTxCounter());
	_checkHistory();
	_setTxHeaderFlags(TYPE_BYTE);
	_addTxToHistory();
	_buffer[0] = data;
	delay(10);
	_rf95.send(_buffer, 1);
	delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}


//##########################################################################################
void FeatherRfm9X::transmitBytes(byte* data, byte length){
	_rf95.setHeaderId(_getTxCounter());
	_checkHistory();
	_setTxHeaderFlags(TYPE_BYTES);
	_addTxToHistory();
	for(int i=0; i<length; i++){
		_buffer[i] = data[i];
	}
	delay(10);
	_rf95.send(_buffer, length);
    delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}


//##########################################################################################
void FeatherRfm9X::transmitString(String data){
	_rf95.setHeaderId(_getTxCounter());
	_checkHistory();
	_setTxHeaderFlags(TYPE_STRING);
	_addTxToHistory();
	int len = data.length();
	for(int i=0; i<len; i++){
		_buffer[i] = (byte)data.charAt(i);
	}
	delay(10);
	_rf95.send(_buffer, len);
	delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}


//##########################################################################################
bool FeatherRfm9X::available(){
	return _rf95.available();
}


//##########################################################################################
int FeatherRfm9X::receive(){
	if (_rf95.available()){
		byte maxLength = RH_RF95_MAX_MESSAGE_LEN;
		if (_rf95.recv(_buffer, &maxLength)){
			_lastRxLength = maxLength;
			if(_isPackageOk()){
				return _getRxHeaderFlags();
			}
			else{
				return TYPE_NONE;
			}
		}
		else{
			return TYPE_NONE;
		}
	}
	else{
		return TYPE_NONE;
	}
}


//##########################################################################################
bool FeatherRfm9X::_isPackageOk(){
	_checkHistory();
	
	byte from = _rf95.headerFrom();
	byte to = _rf95.headerTo();
	byte count = _rf95.headerId();
	byte type = _getRxHeaderFlags();
	long ts = millis();
	
	for(int i=0; i<15; i++){
		if(_historyTimestamp[i] != NULL){
			if(from == _historyFrom[i] && to == _historyTo[i] && count == _historyCount[i] && type == _historyType[i]){
				_historyTimestamp[i] = ts;
				return false;
			}
		}
	}
	
	_addRxToHistory();
	
	return true;
}


//##########################################################################################
byte FeatherRfm9X::receivedByte(){
	return _buffer[0];
}


//##########################################################################################
char FeatherRfm9X::receivedChar(){
	return (char)_buffer[0];
}


//##########################################################################################
byte* FeatherRfm9X::receivedBytes(){
	return _buffer;
}


//##########################################################################################
String FeatherRfm9X::receivedString(){
	return String((char*)_buffer);
}


//##########################################################################################
void FeatherRfm9X::repetePackage(){	
	_rf95.setHeaderFrom(_rf95.headerFrom());
	_rf95.setHeaderTo(_rf95.headerTo());
	_rf95.setHeaderId(_rf95.headerId());
	_rf95.setHeaderFlags(_getRxHeaderFlags());
	delay(10);
	_rf95.send(_buffer, _lastRxLength);
	delay(10);
	_rf95.waitPacketSent(WAIT_PACKAGE_SENT);
}


//##########################################################################################
int FeatherRfm9X::lastRssi(){
	return _rf95.lastRssi();
}


//##########################################################################################
int FeatherRfm9X::lastSnr(){
	return _rf95.lastSNR();
}


//##########################################################################################
byte FeatherRfm9X::lastRxLength(){
	return _lastRxLength;
}


//##########################################################################################
byte FeatherRfm9X::lastRxFrom(){
	return _rf95.headerFrom();
}


//##########################################################################################
byte FeatherRfm9X::lastRxTo(){
	return _rf95.headerTo();
}


//##########################################################################################
byte FeatherRfm9X::lastTxFrom(){
	return _txFrom;
}


//##########################################################################################
byte FeatherRfm9X::lastTxTo(){
	return _txTo;
}


//##########################################################################################
byte FeatherRfm9X::_getTxCounter(){
	if(_txCounter >= 255){
		_txCounter = 0;
	}
	else{
		_txCounter++;
	}
	return _txCounter;
}


//##########################################################################################
void FeatherRfm9X::_addRxToHistory(){
	if(_historyCounter >= 16){
		_historyCounter = 0;
	}
	else{
		_historyCounter++;
	}

	byte from = _rf95.headerFrom();
	byte to = _rf95.headerTo();
	byte count = _rf95.headerId();
	byte type = _getRxHeaderFlags();

	_historyFrom[_historyCounter] = from;
	_historyTo[_historyCounter] = to;
	_historyCount[_historyCounter] = count;
	_historyType[_historyCounter] = type;
	_historyTimestamp[_historyCounter] = millis();
}


//##########################################################################################
void FeatherRfm9X::_addTxToHistory(){
	if(_historyCounter >= 16){
		_historyCounter = 0;
	}
	else{
		_historyCounter++;
	}

	byte from = _txFrom;
	byte to = _txTo;
	byte count = _txCounter;
	byte type = _txType;

	_historyFrom[_historyCounter] = from;
	_historyTo[_historyCounter] = to;
	_historyCount[_historyCounter] = count;
	_historyType[_historyCounter] = type;
	_historyTimestamp[_historyCounter] = millis();
}


//##########################################################################################
void FeatherRfm9X::_checkHistory(){
	long ts = millis();
	for(int i=0; i<15; i++){
		if(_historyTimestamp[i] != NULL){
			if(ts > _historyTimestamp[i] + TIMEOUT){
				_historyFrom[i] = NULL;
				_historyTo[i] = NULL;
				_historyCount[i] = NULL;
				_historyType[i] = NULL;
				_historyTimestamp[i] = NULL;
			}
		}
	}
}


//##########################################################################################
byte FeatherRfm9X::_getRxHeaderFlags(){
	byte b = _rf95.headerFlags();
	bitWrite(b, 4, 0);
	bitWrite(b, 5, 0);
	bitWrite(b, 6, 0);
	bitWrite(b, 7, 0);
	return b;
}


//##########################################################################################
void FeatherRfm9X::_setTxHeaderFlags(byte flags){
	_rf95.setHeaderFlags(flags);
	_txType = flags;
}





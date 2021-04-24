#ifndef FeatherRfm9X_h
#define FeatherRfm9X_h


#include <Steelsquid.h>
#include <Feather.h>
#include <SPI.h>
#include <RH_RF95.h>

// Pins
#define RFM95_CS 	8
#define RFM95_RST 	4
#define RFM95_INT 	3

#define TIMEOUT 30000
#define BROADCAST_ADDRESS 255
#define WAIT_PACKAGE_SENT 30000

// Package types
#define TYPE_NONE   255
#define TYPE_REPETER_PING   0
#define TYPE_REPETER_PONG   1
#define TYPE_PING   2
#define TYPE_PONG   3
#define TYPE_ENQ    4
#define TYPE_ACK    5
#define TYPE_NAK    6
#define TYPE_BELL   7
#define TYPE_BYTE	8
#define TYPE_BYTES	9
#define TYPE_STRING	10

// Frequency [MHz]
#define F_915       915.0
#define F_434       434.0

// Transmitter Power [dBm] (Low power > Range)
#define TP_5        5
#define TP_6        6
#define TP_7        7
#define TP_8        8
#define TP_9        9
#define TP_10       10
#define TP_11       11
#define TP_12       12
#define TP_13       13
#define TP_14       14
#define TP_15       15
#define TP_16       16
#define TP_17       17
#define TP_18       18
#define TP_19       19
#define TP_20       20
#define TP_21       21
#define TP_22       22
#define TP_23       23

// Bandwidth [kHz] (Range > Speed)
#define BW_62_5     62500
#define BW_125_0    125000
#define BW_250_0    250000
#define BW_500_0    500000

// Spreading Factory [64CPS>4096CPS] (Speed > Range)
#define SF_6        6
#define SF_7        7
#define SF_8        8
#define SF_9        9
#define SF_10       10
#define SF_11       11
#define SF_12       12

// Coding Rate [] (Speed > Reliable)
#define CR_4_5      5
#define CR_4_6      6
#define CR_4_7      7
#define CR_4_8      8

class FeatherRfm9X : public Feather{
	public:
		FeatherRfm9X(float frequency=F_434, int transmitterPower=TP_23, long bandwidth=BW_62_5, byte spreadingFactory=SF_12, byte codingRate=CR_4_8);
		void init();
		void init(byte deviceAddress);
		void init(byte deviceAddress, byte toAddress);
		void initRepeter();
		void initRepeter(byte deviceAddress);
		void toAddress(byte toAddress);
		void transmitRepeterPing(byte* data=nullptr, byte length=0);
		void transmitRepeterPong(byte* data=nullptr, byte length=0);
		void transmitPing(byte* data=nullptr, byte length=0);
		void transmitPong(byte* data=nullptr, byte length=0);
		void transmitEnq(byte* data=nullptr, byte length=0);
		void transmitAck(byte* data=nullptr, byte length=0);
		void transmitNak(byte* data=nullptr, byte length=0);
		void transmitBell(byte* data=nullptr, byte length=0);
		void transmitByte(byte data);
		void transmitBytes(byte* data, byte length);
		void transmitString(String data);
		bool available();
		int receive();
		void repetePackage();
		byte receivedByte();
		char receivedChar();
		byte* receivedBytes();
		String receivedString();
		int lastRssi();		
		int lastSnr();
		byte lastRxLength();
		byte lastTxFrom();
		byte lastTxTo();
		byte lastRxFrom();
		byte lastRxTo();
		
	private:
		int _deviceAddress;
		float _frequency;
		int _transmitterPower;
		long _bandwidth;
		void _initRfm9X();
		bool _isPackageOk();
		byte _historyFrom[16];
		byte _historyTo[16];
		byte _historyCount[16];
		byte _historyType[16];
		unsigned long _historyTimestamp[16];
		byte _spreadingFactory;
		byte _codingRate;
		byte _buffer[RH_RF95_MAX_MESSAGE_LEN];
		void _addTxToHistory();
		void _addRxToHistory();
		void _checkHistory();
		byte _getTxCounter();
		byte _getRxHeaderFlags();
		void _setTxHeaderFlags(byte flags);

};


#endif


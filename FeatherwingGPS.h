#ifndef FeatherwingGPS_h
#define FeatherwingGPS_h


#include <Steelsquid.h>
#include <Feather.h>

#define PMTK_SET_NMEA_UPDATE_5HZ "$PMTK220,200*2C"
#define PMTK_API_SET_FIX_CTL_5HZ "$PMTK300,200,0,0,0,0*2F"
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"

class FeatherwingGPS : public Feather{
	public:
		FeatherwingGPS();
		void init();
		bool hasLock();
		int latDegrees();
		double latMinutes();
		char latNS();
		int longDegrees();
		double longMinutes();
		char longEW();
		double speed();
		double angle();
		double latitude();
		double longitude();
	private:
		void _check();
		bool _isBufferOk(int count);
		int _counter = 0;
		char _buffer[128];
		bool _lock = false;
		char _latNS;
		char _longEW;
		double _speed;
		double _angle;
};


#endif


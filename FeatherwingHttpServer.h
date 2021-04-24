#ifndef FeatherwingHttpServer_h
#define FeatherwingHttpServer_h


#include <Steelsquid.h>
#include <Feather.h>
#include <SPI.h>
#include <Ethernet.h>


class FeatherwingHttpServer : public Feather{
	public:
		FeatherwingHttpServer();
		FeatherwingHttpServer(int port);
		FeatherwingHttpServer(byte ip1, byte ip2, byte ip3, byte ip4);
		FeatherwingHttpServer(byte ip1, byte ip2, byte ip3, byte ip4, int port);
		void init();
		void init(byte* mac);
		bool hasRequest();
		String request();
		void responseHtml(String html);
		void responseText(String text);
		void responseNotFound();
	private:
		byte _ip1;
		byte _ip2;
		byte _ip3;
		byte _ip4;
		int _port;
};


#endif


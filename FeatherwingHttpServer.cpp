#include "FeatherwingHttpServer.h"


byte _mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetServer server = NULL;
EthernetClient client = NULL;
String requestString = "";


//##########################################################################################
FeatherwingHttpServer::FeatherwingHttpServer(){
	_ip1 = 192;
	_ip2 = 168;
	_ip3 = 0;
	_ip4 = 177;
	_port = 80;
}


//##########################################################################################
FeatherwingHttpServer::FeatherwingHttpServer(int port){
	_ip1 = 192;
	_ip2 = 168;
	_ip3 = 0;
	_ip4 = 177;
	_port = port;
}


//##########################################################################################
FeatherwingHttpServer::FeatherwingHttpServer(byte ip1, byte ip2, byte ip3, byte ip4){
	_ip1 = ip1;
	_ip2 = ip2;
	_ip3 = ip3;
	_ip4 = ip4;
	_port = 80;
}


//##########################################################################################
FeatherwingHttpServer::FeatherwingHttpServer(byte ip1, byte ip2, byte ip3, byte ip4, int port){
	_ip1 = ip1;
	_ip2 = ip2;
	_ip3 = ip3;
	_ip4 = ip4;
	_port = port;
}


//##########################################################################################
void FeatherwingHttpServer::init(byte* mac){
	_mac[0] = mac[0];
	_mac[1] = mac[1];
	_mac[2] = mac[2];
	_mac[3] = mac[3];
	_mac[4] = mac[4];
	_mac[5] = mac[5];
	init();
}


//##########################################################################################
void FeatherwingHttpServer::init(){
	IPAddress ip(_ip1, _ip2, _ip3, _ip4);
	server = EthernetServer(_port);
	Ethernet.init(10);
	Ethernet.begin(_mac, ip);

	if (Ethernet.hardwareStatus() == EthernetNoHardware) {
		Serial.println("Ethernet shield was not found");
		exit(0);
	}

	server.begin();
}


//##########################################################################################
bool FeatherwingHttpServer::hasRequest(){
	client = server.available();
	if (client) {
		bool currentLineIsBlank = true;
		byte step = 0;
		requestString = "";
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				if(step == 0 && c == ' '){
					step = 1;
				}
				else if(step == 1 && c == ' '){
					step = 2;
				}
				else if(step == 1){
					requestString.concat(c);
				}
				
				if (c == '\n' && currentLineIsBlank) {
					break;
				}
				if (c == '\n') {
					currentLineIsBlank = true;
				} 
				else if (c != '\r') {
					currentLineIsBlank = false;
				}
			}
		}
		return true;
    }
	else{
		return false;
	}
}


//##########################################################################################
String FeatherwingHttpServer::request(){
	return requestString;
}


//##########################################################################################
void FeatherwingHttpServer::responseHtml(String html){
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/html; charset=utf-8");
	client.println("Accept-Charset: utf-8"); 
	client.println("Connection: close"); 
	client.println();
	client.println(html);
	delay(1);
	client.stop();
}


//##########################################################################################
void FeatherwingHttpServer::responseText(String text){
	client.println("HTTP/1.1 200 OK");
	client.println("Content-Type: text/plain; charset=utf-8");
	client.println("Cache-Control: no-cache");
	client.println("Connection: close"); 
	client.println();
	client.println(text);
	delay(1);
	client.stop();
}


//##########################################################################################
void FeatherwingHttpServer::responseNotFound(){
	client.println("HTTP/1.1 402 Not found");
	client.println("Content-Type: text/plain; charset=utf-8");
	client.println("Cache-Control: no-cache");
	client.println("Connection: close"); 
	client.println();
	client.println("402 Not found");
	delay(1);
	client.stop();
}


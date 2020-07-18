#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

#ifndef STASSID
#define STASSID "ZTE_2.4G_ExQCMa"
#define STAPSK "NullReferenceException#123"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(80);

const String postForms = "<html>\
  <head>\
    <title>ESP8266 Web Server POST handling</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
  </body>\
</html>";

void handleRoot() {
	server.send(200, "text/html", postForms);
}

void handleForm() {
	Serial.println(server.arg("R"));
	Serial.println(server.arg("G"));
	Serial.println(server.arg("B"));
	Serial.println(server.arg("Brightness"));
	Serial.println(server.arg("color"));

	server.sendHeader("Access-Control-Allow-Origin", "*");
	server.send(200, "text/plain", "Value Updated");
}

void setRGB(int r = 255, int g = 255, int b = 255, int brightness = 50) {

}

void setup(void) {
	Serial.begin(115200);
	WiFi.begin(ssid, password);
	Serial.println("");

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	if (MDNS.begin("esp8266")) {
		Serial.println("MDNS responder started");
	}

	server.on("/", handleRoot);

	server.on("/postform/", handleForm);

	server.begin();
	Serial.println("HTTP server started");
}

void loop(void) {
	server.handleClient();
}

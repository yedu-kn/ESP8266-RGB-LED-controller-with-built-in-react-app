// install https://github.com/me-no-dev/ESPAsyncWebServer and https://github.com/me-no-dev/ESPAsyncTCP
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <WiFiClient.h>

#ifndef STASSID
#define STASSID "ZTE_2.4G_ExQCMa"
#define STAPSK "NullReferenceException#123"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

AsyncWebServer server(80);

void setRGB(int r = 255, int g = 255, int b = 255, int brightness = 50) {
}

void setup(void) {
	Serial.begin(115200);
	SPIFFS.begin();
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

	server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

	server.on("/postform", HTTP_POST, [](AsyncWebServerRequest *request) {
		Serial.print("R: ");
		Serial.print(request->getParam("R", true)->value());

		Serial.print(", G: ");
		Serial.print(request->getParam("G", true)->value());

		Serial.print(", B: ");
		Serial.print(request->getParam("B", true)->value());

		Serial.print(", Hex: ");
		Serial.print(request->getParam("color", true)->value());

		Serial.print(", Brightness: ");
		Serial.println(request->getParam("Brightness", true)->value());

		request->send(200, "application/json", "done");
	});

	server.begin();
	Serial.println("HTTP server started");
}

void loop(void) {
}

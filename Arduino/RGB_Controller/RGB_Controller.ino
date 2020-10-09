// install:
//		https://github.com/me-no-dev/ESPAsyncWebServer,
//		https://github.com/me-no-dev/ESPAsyncTCP
//		https://github.com/alanswx/ESPAsyncWiFiManager
// SPIFS Unloader Plugin for Arduino IDE: https://github.com/esp8266/arduino-esp8266fs-plugin

#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <FS.h>
#include <WiFiClient.h>

#define PIN D2
#define NUMPIXELS 64

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
AsyncWebServer server(80);
DNSServer dns;

void setColor(int r = 255, int g = 255, int b = 255, int brightness = 50) {
	for (int i = 0; i <= 19; i++) {
		pixels.setPixelColor(i, pixels.Color(r, g, b));
	}
	pixels.show();
}

void setup(void) {
	Serial.begin(115200);
	SPIFFS.begin();

	pixels.begin();

	AsyncWiFiManager wifiManager(&server, &dns);
	// wifiManager.resetSettings(); // Debug
	wifiManager.autoConnect("RGB Controller");
	Serial.println(WiFi.localIP());

	if (MDNS.begin("esp8266")) {
		Serial.println("MDNS responder started");
	}

	server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

	server.on("/postform", HTTP_POST, [](AsyncWebServerRequest *request) {
		int r = request->getParam("R", true)->value().toInt();
		int g = request->getParam("G", true)->value().toInt();
		int b = request->getParam("B", true)->value().toInt();
		int brightness = request->getParam("Brightness", true)->value().toInt();

		Serial.print("R: ");
		Serial.print(r);
		Serial.print(", G: ");
		Serial.print(g);
		Serial.print(", B: ");
		Serial.print(b);
		Serial.print(", Brightness: ");
		Serial.print(brightness);
		Serial.print(", Hex: ");
		Serial.println(request->getParam("color", true)->value());

		setColor(r, g, b, brightness);

		request->send(200, "application/json", "done");
	});

	server.begin();
	Serial.println("HTTP server started");
}

void loop(void) {
}

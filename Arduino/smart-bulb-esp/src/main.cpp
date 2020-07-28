#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <WiFiClient.h>

#ifndef STASSID
#define STASSID "D-Link"
#define STAPSK "9446882946"
#endif
const char *ssid = STASSID;
const char *password = STAPSK;

const byte redPin=D1;
const byte greenPin=D2;
const byte bluePin=D3;

#define UP 0
#define DOWN 1
const int minPWM = 5;
const int maxPWM = 1023;
byte fadeDirection = UP;
int fadeValue = 0;
byte fadeIncrement = 10;
unsigned long previousFadeMillis;
unsigned long fadeInterval = 50;

int power,
    effect,
    speed,
    brightness,
    r,
    g,
    b;

AsyncWebServer server(80);

void noEffects(int r = 0, int g = 0, int b = 0, int brightness = 50) {
	int brightMax=map(brightness, 0, 100, 0, 1023);
	analogWrite(redPin, map(r, 0, 255, 0, brightMax));
	analogWrite(greenPin, map(g, 0, 255, 0, brightMax));
	analogWrite(bluePin, map(b, 0, 255, 0, brightMax));
	Serial.println(brightMax);
}

void fade(int r= 0, int g= 0, int b= 0, int speed = 30, unsigned long thisMillis=0){
  
  int speedMax = map(speed, 0, 100, 50, 0);

  if (thisMillis - previousFadeMillis >= speedMax){
    if (fadeDirection == UP){
      fadeValue = fadeValue + fadeIncrement;
      if (fadeValue >= maxPWM){
        fadeValue = maxPWM;
        fadeDirection = DOWN;
      }
    }
    else{
      fadeValue = fadeValue - fadeIncrement;
      if (fadeValue <= minPWM){
        fadeValue = minPWM;
        fadeDirection = UP;
      }
    }

    analogWrite(redPin, map(r, 0, 255, 0, fadeValue));
    analogWrite(greenPin, map(g, 0, 255, 0, fadeValue));
    analogWrite(bluePin, map(b, 0, 255, 0, fadeValue));

    previousFadeMillis = thisMillis;
  }
  Serial.println("Fade");
  Serial.println(speedMax);
}

void colorChange(int speed=30){
  int speedMax = map(speed, 0, 100, 30, 1023);
  analogWrite(redPin, speedMax);
  analogWrite(greenPin, speedMax);
  analogWrite(bluePin, speedMax);
  Serial.println("Colour Change");
}

void off(){
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  Serial.println("Off");
}

void setup(void) {

  pinMode(redPin, OUTPUT);
  analogWrite(redPin, fadeValue);
	pinMode(greenPin, OUTPUT);
  analogWrite(greenPin, fadeValue);
	pinMode(bluePin, OUTPUT);
  analogWrite(bluePin, fadeValue);

	Serial.begin(115200);
	LittleFS.begin();
	WiFi.begin(ssid, password);
	WiFi.mode(WIFI_STA);
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

	server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

	server.on("/postform", HTTP_POST, [](AsyncWebServerRequest *request) {
		power = request->getParam("power", true)->value().toInt();
		effect = request->getParam("effect", true)->value().toInt();
		speed = request->getParam("speed", true)->value().toInt();
		brightness = request->getParam("Brightness", true)->value().toInt();
		r = request->getParam("R", true)->value().toInt();
		g = request->getParam("G", true)->value().toInt();
		b = request->getParam("B", true)->value().toInt();
		request->send(200, "application/json", "done");

	});

	server.begin();
	Serial.println("HTTP server started");
}

void loop(void) {
      if (power==1){
      switch (effect)
      {
      case 1:
        noEffects(r, g, b, brightness);
        break;
      case 2:
        {unsigned long currentMillis = millis();
          fade(r, g, b, speed, currentMillis);
        }
        break;
      case 3:
        colorChange(speed);
        break;
      default:
        off();
        break;
      }
    }
    else off();
}
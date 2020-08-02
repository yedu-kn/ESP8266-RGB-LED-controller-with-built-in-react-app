//Including Libraries

#include <ESP8266WiFi.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include <WiFiClient.h>
//___________________________________________________________________________________________________________________________

//Defining WiFi credentials

#ifndef STASSID
#define STASSID "D-Link"
#define STAPSK "9446882946"
#endif
const char *ssid = STASSID;
const char *password = STAPSK;
//___________________________________________________________________________________________________________________________

//Defining LED Pins

const byte redPin=D1;
const byte greenPin=D2;
const byte bluePin=D3;
//___________________________________________________________________________________________________________________________

//Defining variables for Fading effect without using delay.
//For more details, https://www.baldengineer.com/fading-led-analogwrite-millis-example.html

#define UP 0
#define DOWN 1
const int minPWM = 5;
const int maxPWM = 1023;
byte fadeDirection = UP;
int fadeValue = 0;
byte fadeIncrement = 10;
unsigned long previousFadeMillis;
unsigned long fadeInterval = 50;
//___________________________________________________________________________________________________________________________

//Defining variables to store data from POST request

int power,
    effect,
    speed,
    brightness,
    r,
    g,
    b;
//___________________________________________________________________________________________________________________________

//Defininge asynchronous web server at PORT 80
AsyncWebServer server(80);
//___________________________________________________________________________________________________________________________

//No-effect function

void noEffects(int r = 0, int g = 0, int b = 0, int brightness = 50) {
  int brightMax=map(brightness, 0, 100, 0, 1023);
//instead of mapping colour values to 1023 we're mapping to brightMax to get control over brightness.
  analogWrite(redPin, map(r, 0, 255, 0, brightMax));
  analogWrite(greenPin, map(g, 0, 255, 0, brightMax));
  analogWrite(bluePin, map(b, 0, 255, 0, brightMax));
}
//___________________________________________________________________________________________________________________________

//Fade function
//refer this tutorial for clarification https://www.baldengineer.com/fading-led-analogwrite-millis-example.html
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
}
//___________________________________________________________________________________________________________________________

//Colour change function
//Define your colour change function here
void colorChange(int speed=30){
  
}
//___________________________________________________________________________________________________________________________

//Off function
void off(){
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

void setup(void) {

//Defining pins and default states
  pinMode(redPin, OUTPUT);
  analogWrite(redPin, fadeValue);
  pinMode(greenPin, OUTPUT);
  analogWrite(greenPin, fadeValue);
  pinMode(bluePin, OUTPUT);
  analogWrite(bluePin, fadeValue);
//___________________________________________________________________________________________________________________________

//Begining Serial Communication and Flash file system
  Serial.begin(115200);
  LittleFS.begin();
//___________________________________________________________________________________________________________________________

//Connecting to the local network in STA mode
//change the code if you've to connect in Acess Point Mode
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
//___________________________________________________________________________________________________________________________

//Serving the index.html file from Flash

  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
//___________________________________________________________________________________________________________________________

//Retrieving the parameters sent by the browser POST request
//This will always listen for the request from browser

  server.on("/postform", HTTP_POST, [](AsyncWebServerRequest *request) {
    power = request->getParam("power", true)->value().toInt();
    effect = request->getParam("effect", true)->value().toInt();
    speed = request->getParam("speed", true)->value().toInt();
    brightness = request->getParam("Brightness", true)->value().toInt();
    r = request->getParam("R", true)->value().toInt();
    g = request->getParam("G", true)->value().toInt();
    b = request->getParam("B", true)->value().toInt();
    
//Send a 200 OK response to the browser
    request->send(200, "application/json", "done");
    
//print recieved data for debugging
    Serial.println();
    Serial.println();
    Serial.print("POWER: ");
    Serial.println(power);
    Serial.print("EFFECT: ");
    Serial.println(effect);
    Serial.print("SPEED: ");
    Serial.println(speed);
    Serial.print("BRIGHTNESS: ");
    Serial.println(brightness);
    Serial.print("RED: ");
    Serial.println(r);
    Serial.print("GREEN: ");
    Serial.println(g);
    Serial.print("BLUE: ");
    Serial.println(b);
  });
//___________________________________________________________________________________________________________________________

//Begin the server

  server.begin();
  Serial.println("HTTP server started");
}
//___________________________________________________________________________________________________________________________

//Calling each function in the main loop by matching the parameters obtained from the browser
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
//___________________________________________________________________________________________________________________________

# ESP8266 RGB LED controller with built-in web app

This project is an ESP8266 based smart bulb where we can control the colour and effect of an RGB LED bulb/strip using a web app.

# At a glance
* App demo link: http://yedu-kn.github.io/Smart-Bulb/ (Add to Home screen will install the web app (PWA))
* Module used: node-mcu 1.0
* Server: ESP async web server
* Protocol: HTTP
* File System: LittleFS
* Delay function not used.
* Driving: 3 N-channel MOSFETs for R, G and B
* Web App: Developed using react.js
* Data transfer: HTTP POST
* This project is an ESP8266 based smart bulb where we can control the colour and effect of an RGB LED bulb/strip using a web app.
* The web app is built using react.js. The source files can be found at React App folder.

# Prerequisites
* Basic arduino coding
* Basics of IoT like server, POST requests etc.
* Electronic circuit basics
* Basic knowledge in React app (if you wish to modify the web-app)

# How it works...
* The main hardware of this project is an ESP8266 NodeMCU.
* Both the arduino code and web page are uploaded to the flash of the controller.
* The web app is created using react.js and the build folder of the app is converted into single HTML page using the gulp.js package.
* Then, this HTML page and the favicon are uploaded to the flash of the nodemcu with LittleFS.
* ESP is configured in STA mode and you can either change it to Access Point mode or you can modify the program using WiFi manager library for efficient WiFi connection management.
* When the device is connected to the wifi, it serves the web page on the local IP. While we change the colour or change the effects or speed, corresponding data is sent to the esp server by means of POST request.
* On the server side, we retrieve these parameters sent by the browser and stores to different variables to use them further.
* The variable values are compared with conditional statements to select from different modes like ON, OFF, FADE etc. The values of the brightness and colours are mapped to the PWM duty cycle of the PWM pins and we get desired colour and outputs on the LED.
* The common anod LED is driven using 3 N-Channel MOSFETs for R, G and B and the VCC is supplied directly to the strip.
* The MOSFETs switches the 12V ground with respect to the PWM recieved on the gate pin and we get the set colour.

# Get it worked...

* Arduino code
  * Install the required libraries
      * ESPAsyncWebServer : https://github.com/me-no-dev/ESPAsyncWebServer
      * ESPAsyncTCP for AsyncWebServer : https://github.com/me-no-dev/ESPAsyncTCP
  * Install arduino LittleFS uploader plugin : https://github.com/earlephilhower/arduino-esp8266littlefs-plugin
  * Select flash size which is just above our data folder size using Tool bar --> Tools --> Flash Size
  * Upload files using Tool bar --> Tools --> ESP8266 LittleFS Data Upload
    (This will upload all the contents in the data folder which is in our sketch folder)
  * Replace the WiFi credentials in the code and upload the sketch.
  * Open Serial monitor, wait for the connection and check the IP address.
  * Enter the IP address from any browser in the local network.
  * Vary the colours, effects and observe changes in the serial monitor.
     
* Wiring up
      
  * Select any N-channel MOSFETs by considering the load. Remember our pins are 3.3V
  * I've used P55NF06
  * Connect the 3 ouput pins from the MCU to the gate of the MOSFET through a 1 Kilo Ohm resistor
  * Connect the source of the MOSFETs to the ground of the 12V power supply and drain to the corresponding LED pin.
  * Connect the ground of MCU with the 12V ground.
 
* Modifying the app (if you wish) 

  * Open the source folder in any text editor and edit your changes.
  * Run `npm start` to run the app in development mode.
  * Run `npm run build-esp` to build the react app and move to arduino data folder.
  * This script will run npm build, npx gulp and then move the file to your arduino data folder.
  * Now upload the data folder to the flash using the above mentioned method.

//Imports from linux
#include "/home/rashed/BattleField/Weapon/development/Arduino/GPS Tracker/cg-gt/TinyGPSPlus/src/TinyGPS++.h"
#include "/home/rashed/BattleField/Weapon/development/Arduino/GPS Tracker/cg-gt/ArduinoSIM800L/Http.h"
#include "/home/rashed/BattleField/Weapon/development/Arduino/GPS Tracker/cg-gt/ArduinoJson/ArduinoJson.h"
#include "SoftwareSerial.h"

//Imports from windows


//RX=pin 10, TX=pin 11
SoftwareSerial softwareSerial(11, 10);
//This is the GPS object that will pretty much do all the grunt work with the NMEA data
TinyGPSPlus tinyGpsPlus;

void setup() {
  // put your setup code here, to run once:

  //This opens up communications to the Serial monitor in the Arduino IDE
  Serial.begin(9600);
  //This opens up communications to the GPS
  softwareSerial.begin(9600);
  //Just show to the monitor that the sketch has started
  Serial.println("GPS Started...");
}

void loop() {
  // put your main code here, to run repeatedly:

  //While there are characters to come from the GPS
  while(softwareSerial.available()){
    //This feeds the serial NMEA data into the library one char at a time
    tinyGpsPlus.encode(softwareSerial.read());
  }

  //This will pretty much be fired all the time anyway but will at leaset reduce it to only after a packaeg of NMEA data comes in
  if(tinyGpsPlus.location.isUpdated()){
    //Baud rate of the GSM/GPRS module
    Serial.begin(9600);
    Serial.print("\r");
    delay(1000);
    Serial.print("AT+CMGF=1\r");
    delay(1000);
    //Number to which you want to send the sms with country code
    Serial.print("AT+CMGF=\"+8801794620787\"\r");
    delay(1000);
    //The message to be sent
    Serial.print("I'm lost! Please help me, I'm here ");
    //Link of Google Map
    Serial.print("www.google.com.ph/maps/place/");
    //To get the coordinate for Latitude
    Serial.print(tinyGpsPlus.location.lat(), 6);
    Serial.print(",");
    //To get the coordinate for Longitude
    Serial.print(tinyGpsPlus.location.lng(), 6);
    Serial.print("\r");
    delay(1000);
    //ASCII code to end the message
    Serial.println((char)26);
    delay(1000);
    Serial.write(0x1A);
    Serial.write(0x0D);
    Serial.write(0x0A);
    delay(1000);
  }
}

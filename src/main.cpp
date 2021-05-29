#include "Arduino.h"
#include "SoftwareSerial.h"
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "VxbjbMoTOewMeVG8WZystVaQVD2vUgJI";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "HarooN..";
char pass[] = "haroonmectec";

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000);
}
SoftwareSerial s(14,12);  //RX TX uses different type of pinout
String command,NO2,NH3,CO,PPM,PM25;

//functions 
void decode(String command)
{
  NO2= command.substring(command.indexOf('@')+1,command.indexOf(','));
  NH3 = command.substring(command.indexOf(',')+1,command.indexOf('!'));
  CO  = command.substring(command.indexOf("!")+1,command.indexOf("#"));
  PPM = command.substring(command.indexOf('#')+1,command.indexOf('&'));
  PM25 = command.substring(command.indexOf('&')+1,command.indexOf('$'));
}

//---------

void setup() {
  // put your setup code here, to run once:
s.begin(9600);
Serial.begin(9600);
Serial.println("Hello World");
}

void loop(){
  /* put your main code here, to run repeatedly:
  if(s.available()>0)
  {
    Serial.println(s.readString());
    /*
    command =  s.readString();
    Serial.println(command);
    decode(command);
    Serial.print(NO2);
    Serial.print(',');
    Serial.print(NH3);
    Serial.print(',');
    Serial.print(CO);
    Serial.print(',');
    Serial.print(PPM);
    Serial.print(',');
    Serial.print(PM25);\
    */

   if(Serial.available() >0)
   {
    command =  Serial.readString();
    Serial.println(command);
    decode(command);
    Serial.print(NO2);
    Serial.print(',');
    Serial.print(NH3);
    Serial.print(',');
    Serial.print(CO);
    Serial.print(',');
    Serial.print(PPM);
    Serial.print(',');
    Serial.print(PM25);
   }
}


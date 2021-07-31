#include "Arduino.h"
#include "SoftwareSerial.h"
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "RzK6MeFktTZPaLTyN1xv-a2Iq6Hc0pFY";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WC_to_No_Internet";  //apna net ki id likhe yahan
char pass[] = "information0P"; //or yahan password  

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
String command, NO2, NH3, CO, PPM, PM25;
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, CO);
  Blynk.virtualWrite(V1, NO2);
  Blynk.virtualWrite(V2, NH3);
  Blynk.virtualWrite(V3, PPM);
  Blynk.virtualWrite(V4, PM25);
}
SoftwareSerial s(14, 12); //RX TX uses different type of pinout


//functions
void decode(String command)
{
  NO2 = command.substring(command.indexOf('@') + 1, command.indexOf(','));
  NH3 = command.substring(command.indexOf(',') + 1, command.indexOf('!'));
  CO = command.substring(command.indexOf("!") + 1, command.indexOf("#"));
  PPM = command.substring(command.indexOf('#') + 1, command.indexOf('&'));
  PM25 = command.substring(command.indexOf('&') + 1, command.indexOf('$'));
}

//---------

void setup()
{
  // put your setup code here, to run once:
  s.begin(9600);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000, myTimerEvent);
  Serial.println("Hello World");
}

void loop()
{
  if (s.available() > 0)
  {
    command = s.readString();
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

  Blynk.run();
  timer.run();

}
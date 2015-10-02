/*
==========================================================
 Sketch based on:

"How To Use the ESP8266 and Arduino as a Webserver":
 http://allaboutee.com/2014/12/30/esp8266-and-arduino-webserver/


Project : Send Photo resistor values to computer
Author: ScottC
Created: 25th June 2011
Description: This sketch will make the arduino read Photo resistor
             values on analog pin A0. The analog readings will
             be dependent on the amount of light reaching the
             sensor. The Analog readings will be sent to the
             computer via the USB cable using Serial communication.
==============================================================
*/

#include <SoftwareSerial.h>

#define DEBUG true

SoftwareSerial esp8266(2, 3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
// This means that you need to connect the TX line from the esp to the Arduino's pin 2
// and the RX line from the esp to the Arduino's pin 3
int testNumber = 200;


int photoRPin = 0;

int minLight;          //Used to calibrate the readings
int maxLight;          //Used to calibrate the readings
int lightLevel;
int adjustedLightLevel;

String claro = " - light";
String escuro = " - dark";

void setup()
{

  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different

  sendData("AT+RST\r\n", 2000, DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n", 500, DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n", 500, DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n", 500, DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", 500, DEBUG); // turn on server on port 80

  //Setup the starting light level limits
  lightLevel = analogRead(photoRPin);
  minLight = lightLevel - 20;
  maxLight = lightLevel;



}

void loop()
{

  if (esp8266.available()) // check if the esp is sending a message
  {


    if (esp8266.find("+IPD,"))
    {
      delay(1000);

      testNumber = photoCellRead();

      String lightisComing;

      if (testNumber > 50) {
        lightisComing = "Light is passing";
      } else {
        lightisComing = "You are blocking the photo cell";
      }


      int connectionId = esp8266.read() - 48; // subtract 48 because the read() function returns
      // the ASCII decimal value and 0 (the first decimal number) starts at 48
      // start
      String webpage = "<p>Is there light?</p>";
      webpage += testNumber;
      webpage += " - " + lightisComing;

      webpage += "<script>setTimeout(function(){window.location=window.location;},5000)</script>";
      webpage += "\r\n";
      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      cipSend += "\r\n";

      sendData(cipSend, 2000, DEBUG);
      sendData(webpage, 2000, DEBUG);




      // end

      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
      closeCommand += "\r\n";

      sendData(closeCommand, 3000, DEBUG);


    }
  }
}


String sendData(String command, const int timeout, boolean debug)
{
  String response = "";

  esp8266.print(command); // send the read character to the esp8266

  long int time = millis();

  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {

      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }

  if (debug)
  {
    Serial.print(response);
    Serial.flush();
  }

  return response;
}

int photoCellRead()
{
  //auto-adjust the minimum and maximum limits in real time
  lightLevel = analogRead(photoRPin);
  if (minLight > lightLevel) {
    minLight = lightLevel;
  }
  if (maxLight < lightLevel) {
    maxLight = lightLevel;
  }

  //Adjust the light level to produce a result between 0 and 100.
  adjustedLightLevel = map(lightLevel, minLight, maxLight, 0, 100);
  if (adjustedLightLevel > 50) {
    //Send the adjusted Light level result to Serial port (processing)
    Serial.println(adjustedLightLevel + claro);
    //digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    Serial.println(adjustedLightLevel + escuro);
    //digitalWrite(ledPin, LOW);   // turn the LED off (LOW is the voltage level)
  }
  //slow down the transmission for effective Serial communication.
  delay(100);

  return adjustedLightLevel;

}

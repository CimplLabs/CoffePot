/* ==========================================================
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

int photoRPin = 0;
int ledPin =  2;       // the number of the LED pin 
int minLight;          //Used to calibrate the readings
int maxLight;          //Used to calibrate the readings
int lightLevel;
int adjustedLightLevel;

String claro = " - light";
String escuro = " - dark";

void setup() {
 Serial.begin(9600);
 
 //Setup the starting light level limits
 lightLevel=analogRead(photoRPin);
 minLight=lightLevel-20;
 maxLight=lightLevel;

 pinMode(ledPin, OUTPUT);
}

void loop(){
 //auto-adjust the minimum and maximum limits in real time
 lightLevel=analogRead(photoRPin);
 if(minLight>lightLevel){
 minLight=lightLevel;
 }
 if(maxLight<lightLevel){
 maxLight=lightLevel;
 }
 
 //Adjust the light level to produce a result between 0 and 100.
 adjustedLightLevel = map(lightLevel, minLight, maxLight, 0, 100); 
 if (adjustedLightLevel>50) {
 //Send the adjusted Light level result to Serial port (processing)
 Serial.println(adjustedLightLevel+claro);
 //digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
 } else {
  Serial.println(adjustedLightLevel+escuro);
  //digitalWrite(ledPin, LOW);   // turn the LED off (LOW is the voltage level)
 }
 //slow down the transmission for effective Serial communication.
 delay(50);


}

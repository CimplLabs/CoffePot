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

int photoRPin1 = 0;
int photoRPin2 = 1;
int photoRPin3 = 2;
int photoRPin4 = 3;

int minLight1;          //Used to calibrate the readings
int maxLight1;          //Used to calibrate the readings
int minLight2;          //Used to calibrate the readings
int maxLight2;          //Used to calibrate the readings
int minLight3;          //Used to calibrate the readings
int maxLight3;          //Used to calibrate the readings
int minLight4;          //Used to calibrate the readings
int maxLight4;          //Used to calibrate the readings

int lightLevel1;
int lightLevel2;
int lightLevel3;
int lightLevel4;

int adjustedLightLevel1;
int adjustedLightLevel2;
int adjustedLightLevel3;
int adjustedLightLevel4;

String claro = " - light";
String escuro = " - dark";

void setup() {
    Serial.begin(9600);

    //Setup the starting light level limits
    lightLevel1 = analogRead(photoRPin1);
    minLight1 = lightLevel1 - 20;
    maxLight1 = lightLevel1;

    lightLevel2 = analogRead(photoRPin2);
    minLight2 = lightLevel2 - 20;
    maxLight2 = lightLevel2;

    lightLevel3 = analogRead(photoRPin3);
    minLight3 = lightLevel3 - 20;
    maxLight3 = lightLevel3;

    lightLevel4 = analogRead(photoRPin4);
    minLight4 = lightLevel4 - 20;
    maxLight4 = lightLevel4;
}

void loop() {
    //auto-adjust the minimum and maximum limits in real time
    lightLevel1 = analogRead(photoRPin1);
    Serial.println(lightLevel1);

    if (minLight1 > lightLevel1) {
        minLight1 = lightLevel1;
    }

    if (maxLight1 < lightLevel1) {
        maxLight1 = lightLevel1;
    }

    lightLevel2 = analogRead(photoRPin2);
    Serial.println(lightLevel2);

    if (minLight2 > lightLevel2) {
        minLight1 = lightLevel1;
    }

    if (maxLight2 < lightLevel2) {
        maxLight2 = lightLevel2;
    }

    lightLevel3 = analogRead(photoRPin3);
    Serial.println(lightLevel3);

    if (minLight3 > lightLevel3) {
        minLight3 = lightLevel3;
    }

    if (maxLight3 < lightLevel3) {
        maxLight3 = lightLevel3;
    }

    lightLevel4 = analogRead(photoRPin4);
    Serial.println(lightLevel4);

    if (minLight4 > lightLevel4) {
        minLight4 = lightLevel4;
    }

    if (maxLight4 < lightLevel4) {
        maxLight4 = lightLevel4;
    }

    //Adjust the light level to produce a result between 0 and 100.
    adjustedLightLevel1 = map(lightLevel1, minLight1, maxLight1, 0, 100);
    adjustedLightLevel2 = map(lightLevel2, minLight2, maxLight2, 0, 100);
    adjustedLightLevel3 = map(lightLevel3, minLight3, maxLight3, 0, 100);
    adjustedLightLevel4 = map(lightLevel4, minLight4, maxLight4, 0, 100);

    if (adjustedLightLevel1 > 50) {
        //Send the adjusted Light level result to Serial port (processing)
        Serial.println(adjustedLightLevel1 + claro);
        //digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    } else {
        Serial.println(adjustedLightLevel1 + escuro);
        //digitalWrite(ledPin, LOW);   // turn the LED off (LOW is the voltage level)
    }

    if (adjustedLightLevel2 > 50) {
        //Send the adjusted Light level result to Serial port (processing)
        Serial.println(adjustedLightLevel2 + claro);
        //digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    } else {
        Serial.println(adjustedLightLevel2 + escuro);
        //digitalWrite(ledPin, LOW);   // turn the LED off (LOW is the voltage level)
    }

    if (adjustedLightLevel3 > 50) {
        //Send the adjusted Light level result to Serial port (processing)
        Serial.println(adjustedLightLevel3 + claro);
        //digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    } else {
        Serial.println(adjustedLightLevel3 + escuro);
        //digitalWrite(ledPin, LOW);   // turn the LED off (LOW is the voltage level)
    }

    if (adjustedLightLevel4 > 50) {
        //Send the adjusted Light level result to Serial port (processing)
        Serial.println(adjustedLightLevel4 + claro);
        //digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    } else {
        Serial.println(adjustedLightLevel4 + escuro);
        //digitalWrite(ledPin, LOW);   // turn the LED off (LOW is the voltage level)
    }

    Serial.println("--------------------------------------");

    if (adjustedLightLevel1 > 50 && adjustedLightLevel2 > 50) {
        Serial.println("Coffee Pot 1 is empty!");
    } else if (adjustedLightLevel1 > 50 && adjustedLightLevel2 <= 50) {
        Serial.println("Coffee Pot 1 is half way done/empty!");
    } else if (adjustedLightLevel1 <= 50 && adjustedLightLevel2 <= 50) {
        Serial.println("Coffee Pot 1 has fresh coffee! Hurry up!");
    }

    if (adjustedLightLevel3 > 50 && adjustedLightLevel4 > 50) {
        Serial.println("Coffee Pot 2 is empty!");
    } else if (adjustedLightLevel3 > 50 && adjustedLightLevel4 <= 50) {
        Serial.println("Coffee Pot 2 is half way done/empty!");
    } else if (adjustedLightLevel3 <= 50 && adjustedLightLevel4 <= 50) {
        Serial.println("Coffee Pot 2 has fresh coffee! Hurry up!");
    }

    Serial.println("--------------------------------------");
    Serial.flush();

    //slow down the transmission for effective Serial communication.
    delay(2000);
}

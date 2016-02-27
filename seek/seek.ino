#include <SoftwareSerial.h>
#include <Servo.h>

#define USE_SOFT_SER 1

SoftwareSerial bluetooth(11,10); //RX TX (connect pin11(RX) to TX on the module.
//Servo MyServo;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  while (!bluetooth.available()) {
    Serial.print("bluetooth serial not available");
  }
  Serial.print("bluetooth serial available");
  //MyServo.attach(2); output to servo motor;
}

void loop() {
  if (bluetooth.available()) {
    int command = bluetooth.read();

    switch (command) {
      case 'a':
        Serial.print("a was sent");
        digitalWrite(13, HIGH);
        break;

      case 'b':
        Serial.print("b was sent");
        digitalWrite(13, LOW);
        break;
    }
  }
}

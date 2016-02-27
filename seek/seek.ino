#include <SoftwareSerial.h>;
#include <Servo.h>;

SoftwareSerial bluetooth(11,10); //RX TX (connect pin11(RX) to TX on the module.
//Servo MyServo;
#define USE_SOFT_SER 1

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

    if (command == 97) // 97 is the code for a {
     Serial.print(" a ");
     digitalWrite(13, HIGH);
    }

    if (command == 98) // 98 is the code for b {
      Serial.print(" b ");
      digitalWrite(13, LOW);
    }
  }
}

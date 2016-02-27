#include <SoftwareSerial.h>
#include <Servo.h>

#define USE_SOFT_SER 1

#if USE_SOFT_SER
  SoftwareSerial bluetooth(11,10); //RX TX (connect pin11(RX) to TX on the module.
#else
  #define bluetooth Serial
#endif

void setLeftMotorTo(int speed);
void setRightMotorTo(int speed);
//Servo MyServo;

void setup() {
#if USE_SOFT_SER
  Serial.begin(9600);
#endif
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
      case 'f': // move forward
        // set both motors to go forwards at the same speed
        setLeftMotorTo(0.5);
        setRightMotorTo(0.5);
        break;
      case 'b': // move backward
        // set both motors to go backwards at the same speed
        setLeftMotorTo(-0.5);
        setRightMotorTo(-0.5);
        break;
      case 'r': // turn right
        // set the right to go backwards at a speed x
        setRightMotorTo(-0.5);
        // set the left to go forwards at speed x
        setLeftMotorTo(0.5);
        break;
      case 'l': // turn left
        // set the right to go forwards at speed x
        setRightMotorTo(0.5);
        // set the left to go backwards at a speed x
        setLeftMotorTo(-0.5);
        break;
    }
    // sleep for n seconds
    delay(500);
    // set both motors to 0
    setLeftMotorTo(0);
    setRightMotorTo(0);
  }
}

void setLeftMotorTo(int speed) {

}

void setRightMotorTo(int speed) {

}

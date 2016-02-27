#include <SoftwareSerial.h>
#include <Servo.h>

#define USE_SOFT_SER 1

#if USE_SOFT_SER
  SoftwareSerial bluetooth(8, 7); //RX TX (connect pin11(RX) to TX on the module.
#else
  #define bluetooth Serial
#endif

int left_pin[] = {11, 10};
int right_pin[] = {6, 5};
int light_pin = 4;
boolean lights = false;

void setLeftMotorTo(int speed);
void setRightMotorTo(int speed);
//Servo MyServo;

void setup() {
#if USE_SOFT_SER
  Serial.begin(9600);
#endif
  bluetooth.begin(9600);
  
  pinMode(left_pin[0], OUTPUT);
  pinMode(left_pin[1], OUTPUT);
  pinMode(right_pin[0], OUTPUT);
  pinMode(right_pin[1], OUTPUT);
  pinMode(4, INPUT);
  
  digitalWrite(4, LOW);
}

void loop() {
  if (bluetooth.available()) {
    int command = bluetooth.read();

    switch (command) {
      case 'f': // move forward
        // set both motors to go forwards at the same speed
        setLeftMotorTo(126);
        setRightMotorTo(126);
        Serial.print("f\n");
        break;
      case 'b': // move backward
        // set both motors to go backwards at the same speed
        setLeftMotorTo(-126);
        setRightMotorTo(-126);
        Serial.print("b\n");
        break;
      case 'r': // turn right
        // set the right to go backwards at a speed x
        setRightMotorTo(-126);
        // set the left to go forwards at speed x
        setLeftMotorTo(126);
        Serial.print("r\n");
        break;
      case 'l': // turn left
        // set the right to go forwards at speed x
        setRightMotorTo(126);
        // set the left to go backwards at a speed x
        setLeftMotorTo(-126);
        Serial.print("l\n");
        break;
      case 'h':
        if(lights) {
          pinMode(light_pin, INPUT);
        }
        else {
          pinMode(light_pin, OUTPUT);
        }
        lights = !lights;
        break;
    }
    // sleep for n seconds
    delay(1000);
    // set both motors to 0
    setLeftMotorTo(0);
    setRightMotorTo(0);
  }
}

void setLeftMotorTo(int target_speed) {
  if (target_speed < 0) {
    digitalWrite(left_pin[0], LOW);
    digitalWrite(left_pin[1], HIGH);
  } else if (target_speed > 0) {
    digitalWrite(left_pin[0], HIGH);
    digitalWrite(left_pin[1], LOW);
  } else {
    digitalWrite(left_pin[0], LOW);
    digitalWrite(left_pin[1], LOW);
  }
}

void setRightMotorTo(int target_speed) {
  if (target_speed < 0) {
    digitalWrite(right_pin[0], LOW);
    digitalWrite(right_pin[1], HIGH);
  } else if (target_speed > 0) {
    digitalWrite(right_pin[0], HIGH);
    digitalWrite(right_pin[1], LOW);
  } else {
    digitalWrite(right_pin[0], LOW);
    digitalWrite(right_pin[1], LOW);
  }
}

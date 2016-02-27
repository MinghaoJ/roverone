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

int left_speed = 0;
int right_speed = 0;

void setLeftMotorTo(int speed);
void setRightMotorTo(int speed);
//Servo MyServo;

void setup() {
#if USE_SOFT_SER
  Serial.begin(9600);
#endif
  bluetooth.begin(9600);
  while (!bluetooth.available()) {
#if USE_SOFT_SER
    Serial.print("bluetooth serial not available");
#endif
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
        setLeftMotorTo(126);
        setRightMotorTo(126);
        break;
      case 'b': // move backward
        // set both motors to go backwards at the same speed
        setLeftMotorTo(-126);
        setRightMotorTo(-126);
        break;
      case 'r': // turn right
        // set the right to go backwards at a speed x
        setRightMotorTo(-126);
        // set the left to go forwards at speed x
        setLeftMotorTo(126);
        break;
      case 'l': // turn left
        // set the right to go forwards at speed x
        setRightMotorTo(126);
        // set the left to go backwards at a speed x
        setLeftMotorTo(-126);
        break;
    }
    // sleep for n seconds
    delay(500);
    // set both motors to 0
    setLeftMotorTo(0);
    setRightMotorTo(0);
  }
}

void setMotorTo(int pin, int current_speed, int target_speed) {
  if (target_speed > current_speed) {
    // loop up from the current speed
    for (int i = current_speed; i < target_speed; i += 10) {
      analogWrite(pin, i);
    }
  } else if (target_speed < current_speed) {
    // loop down from the current speed
    for (int i = current_speed; i > target_speed; i -= 10) {
      analogWrite(pin, i);
    }
  }
  analogWrite(pin, target_speed);

}

void setLeftMotorTo(int target_speed) {
  if (target_speed > 0) {
    analogWrite(left_pin[0], 0);
    setMotorTo(left_pin[1], left_speed, target_speed);
  } else {
    analogWrite(left_pin[1], 0);
    setMotorTo(left_pin[0], left_speed, -target_speed);
  }

  left_speed = target_speed;
}

void setRightMotorTo(int target_speed) {
  if (target_speed > 0) {
    analogWrite(right_pin[0], 0);
    setMotorTo(right_pin[1], right_speed, target_speed);
  } else {
    analogWrite(right_pin[1], 0);
    setMotorTo(right_pin[0], right_speed, -target_speed);
  }

  right_speed = target_speed;
}

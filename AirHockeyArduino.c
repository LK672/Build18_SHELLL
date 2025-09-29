/*
Arduino pins
Driver connections
D9 -> Driver PULL+
D8 -> Driver DIR+
GND -> Driver PULL-
GND -> Driver DIR-

Joystick
GND -> GND
5V -> 5V
VRX -> A1 (Defined below)
VRY -> A0 (Defined below)
SW connected to nothing (I think this is clicking of the joystick)
*/

#include <AccelStepper.h>

#define VRX_PIN  A1 // Arduino pin connected to VRX pin
#define VRY_PIN  A0 // Arduino pin connected to VRY pin

/**
On the DM542T stepper motor driver max amprage setting of peak 3.97A and 200 
pulses per revolution, this is the max speed we can set. Any higher speed will
show little to no differnece in motor speed. */ 
#define SPEED 3600

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  800

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

int xValue = 0 ; // To store value of the X axis
int yValue = 0 ; // To store value of the Y axis
int command = COMMAND_NO;

AccelStepper stepper1(AccelStepper::DRIVER, 9, 8);

void setup() {
  // this sets the 9600 standard baud rate for serial communication
  Serial.begin(9600);
  stepper1.setMaxSpeed(SPEED);
  stepper1.setSpeed(SPEED);
}

void loop() {
  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  // converts the analog value to commands
  // reset commands
  command = COMMAND_NO;

  // check left/right commands
  if (xValue < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  else if (xValue > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  // check up/down commands
  if (yValue < UP_THRESHOLD)
    command = command | COMMAND_UP;
  else if (yValue > DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;

  // Note: at a time, there may be no command, one command, or two commands

  // print command to serial and process command
  if (command & COMMAND_LEFT) {
    stepper1.setSpeed(-SPEED);
    stepper1.runSpeed();
  }

  if (command & COMMAND_RIGHT) {
    stepper1.setSpeed(SPEED);
    stepper1.runSpeed();
  }

  // if (command & COMMAND_UP) {
  // }

  // if (command & COMMAND_DOWN) {
  // }
}

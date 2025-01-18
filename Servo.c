#include <Servo.h>

Servo servo1;

#define SERVO_PIN 11
int pos = 0;

void setup() {
    servo1.attach(SERVO_PIN)
}

void loop() {
    for (actual_angle = 0; actual_angle <= 270; actual_angle += 100)
    {
        pos = map(actual_angle, 0, 270, 0, 180);
        servo1.write(pos);
        delay(30);
    }
    for (actual_angle = 270; actual_angle >= 0; actual_angle -= 100)
    {
        pos = map(actual_angle, 0, 270, 0, 180);
        servo1.write(pos);
        delay(30);
    }
    
    
}


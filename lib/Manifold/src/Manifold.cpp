#include "Manifold.h"
#include <Arduino.h>
#include <Servo.h>

int servo_fwd = 0;   // Positive speed value for the servo
int servo_stp = 90;  // Zero value for STOP
int servo_bwd = 180; // Negative speed value for the servo

// Initialize static member
int Manifold::instance_count = 0;

Manifold::Manifold(int num_outputs, int pin) : num_outputs(num_outputs), manifold_pin(pin) {
    current_position = -1;
}

void Manifold::initialize() {
    servo.attach(manifold_pin); // Attach the servo to the specified pin
    reset();           // Reset the manifold
}

void Manifold::openValve(int valve_number) {
}

void Manifold::reset() {
    servo.write(servo_bwd);
    delay(20000);
    servo.write(servo_stp);
    current_position = 0;
}

void Manifold::stop() {
    servo.write(servo_stp);
}

void Manifold::test() {
    servo.write(servo_fwd);
    delay(12500);
    servo.write(servo_stp);
    delay(5000);
    servo.write(servo_fwd);
    delay(21000);
    servo.write(servo_stp);
    delay(5000);
    servo.write(servo_bwd);
    delay(21000);
    servo.write(servo_stp);
    delay(5000);
}
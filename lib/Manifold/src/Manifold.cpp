#include "Manifold.h"
#include <Arduino.h>
#include <Servo.h>

int servo_fwd = 0;   // Positive speed value for the servo
int servo_stp = 90;  // Zero value for STOP
int servo_bwd = 180; // Negative speed value for the servo

int travel_btwn_valves = 21700; // Travel time between valves in ms
int travel_from_0_to_1 = 12500; // travel time between reset and valve 1 in ms

// Initialize static member
int Manifold::instance_count = 0;

Manifold::Manifold(int num_outputs, int pin, Screen* screen) 
    : num_outputs(num_outputs), manifold_pin(pin), screen(screen) {
    current_position = -1;
}

void Manifold::initialize() {
    log("Init manifold", nullptr);
    servo.attach(manifold_pin); // Attach the servo to the specified pin
    reset(); // Reset the manifold
    log("Init manifold", "Done.");
}

void Manifold::goToValve(int valve_number) {
    if (valve_number < 0 || valve_number > num_outputs) {
        log("Invalid valve", nullptr);
        return;
    }

    char buffer[16];
    sprintf(buffer, "Valve: %d", valve_number);
    log("Moving to valve", buffer);

    if (current_position == -1) {
        reset();
    }

    while (current_position < valve_number) {
        moveOnePosition(true); // Move forward
    }

    while (current_position > valve_number) {
        moveOnePosition(false); // Move backward
    }

    log("At valve", buffer);
}

void Manifold::moveOnePosition(bool forward) {
    if (forward) {
        servo.write(servo_fwd);
        delay(current_position == 0 ? travel_from_0_to_1 : travel_btwn_valves);
        current_position++;
    } else {
        servo.write(servo_bwd);
        delay(travel_btwn_valves);
        current_position--;
    }
    servo.write(servo_stp);
}

void Manifold::reset() {
    log("Resetting...", nullptr);
    servo.write(servo_bwd);
    delay(travel_btwn_valves);
    servo.write(servo_stp);
    current_position = 0;
    log("Reset done", nullptr);
}

void Manifold::stop() {
    servo.write(servo_stp);
}

void Manifold::log(const char* line1, const char* line2) {
    screen->clear();
    screen->print(0, 0, line1);
    if (line2) {
        screen->print(0, 1, line2);
    }
}

void Manifold::test() {
    goToValve(1);
    delay(5000);
    goToValve(2);
    delay(5000);
    goToValve(3);
    delay(5000);
    goToValve(4);
    delay(5000);
    goToValve(5);
    delay(5000);
}
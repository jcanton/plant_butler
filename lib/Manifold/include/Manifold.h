#ifndef MANIFOLD_H
#define MANIFOLD_H

#include <Servo.h>

class Manifold {
private:
    int num_outputs;
    int manifold_pin; // Digital pin to which the servo is attached
    int current_position;
    static int instance_count;
    Servo servo; // Servo object for controlling the manifold

public:
    Manifold(int num_outputs, int pin); // Constructor
    void initialize();                  // Initialize the manifold
    void reset();                       // Reset the servo to its initial position
    void stop();                        // Stop everything
    void test();
    void openValve(int valve_number);   // Open a specific valve
};

#endif // MANIFOLD_H

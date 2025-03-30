#ifndef MANIFOLD_H
#define MANIFOLD_H

#include <Servo.h>
#include <Screen.h> // Include Screen header

class Manifold {
private:
    int num_outputs;
    int manifold_pin; // Digital pin to which the servo is attached
    int current_position;
    static int instance_count;
    Servo servo; // Servo object for controlling the manifold
    Screen* screen; // Pointer to a Screen object for displaying messages
    void moveOnePosition(bool forward); // Move one position forward or backward
    void log(const char* line1, const char* line2 = nullptr); // Log messages to the screen

public:
    Manifold(int num_outputs, int pin, Screen* screen); // Constructor
    void initialize();                  // Initialize the manifold
    void reset();                       // Reset the servo to its initial position
    void stop();                        // Stop everything
    void test();
    void goToValve(int valve_number);   // Open a specific valve
};

#endif // MANIFOLD_H

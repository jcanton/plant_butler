#include "Manifold.h"

// Initialize static member
int Manifold::instance_count = 0;

Manifold::Manifold(int num_outputs) : num_outputs(num_outputs) {
    number = ++instance_count;
}

void Manifold::reset() {
    // Empty for now
}

void Manifold::openValve(int valve_number) {
    // Empty for now
}

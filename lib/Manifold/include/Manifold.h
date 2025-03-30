#ifndef MANIFOLD_H
#define MANIFOLD_H

class Manifold {
private:
    int num_outputs;
    int number;
    static int instance_count;

public:
    Manifold(int num_outputs);
    void reset();
    void openValve(int valve_number);
};

#endif // MANIFOLD_H

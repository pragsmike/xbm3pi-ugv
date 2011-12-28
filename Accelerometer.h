#ifndef Accelerometer_h
#define Accelerometer_h

#include "mbed.h"

class Accelerometer {

public:
    Accelerometer(void);
    void tick(void);
    
    int x, y, z;

private:
    AnalogIn    ax;
    AnalogIn    ay;
    AnalogIn    az;
};
#endif

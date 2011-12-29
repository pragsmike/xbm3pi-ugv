#ifndef Rover_h
#define Rover_h

#include "m3pi.h"

class Rover {

public:
	Rover(m3pi &_m3pi);
    void drive(float x, float y);
    void init();

private:
    m3pi *_m3pi;
};
#endif

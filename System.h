#ifndef System_h
#define System_h

#include "mbed.h"
#include "Log.h"
#include "TelemetryData.h"
#include "Gyro.h"
#include "Accelerometer.h"
#include "mavlink.h"

class System {

public:
	System(TelemetryData &td);

    void tick(void);
    void setMode(int target, int base_mode, int nav_mode);

    void takeoff();
    void land();

private:
    Ticker      	ticker;
    Timer			timeSinceStart;
    TelemetryData	*td;
};
#endif

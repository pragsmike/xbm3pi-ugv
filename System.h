#ifndef System_h
#define System_h

#include "Log.h"
#include "StatusDisplay.h"
#include "TelemetryData.h"
#include "mavlink.h"

class System {

public:
	System(TelemetryData &td, StatusDisplay &status);

    void tick(void);
    void setMode(int target, int base_mode, int nav_mode);

    void takeoff();
    void land();

private:
    Ticker      	ticker;
    Timer			timeSinceStart;
    TelemetryData	*td;
    StatusDisplay	*_status;
};
#endif

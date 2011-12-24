#ifndef TelemetryEncoder_h
#define TelemetryEncoder_h

#include "mbed.h"
#include "Gyro.h"
#include "Accelerometer.h"

class TelemetryEncoder {

public:
    TelemetryEncoder(void);
    int fillFrame(uint8_t *bp);

private:
    Gyro            gyro;
    Accelerometer   accelerometer;
};
#endif

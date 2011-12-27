#ifndef TelemetryEncoderMavLink_h
#define TelemetryEncoderMavLink_h

#include "mbed.h"
#include "mavlink.h"

#include "Gyro.h"
#include "Accelerometer.h"
#include "Timer.h"

class TelemetryEncoderMavLink {

public:
    TelemetryEncoderMavLink(void);
    int fillFrame(uint8_t *bp);

private:
    Gyro            gyro;
    Accelerometer   accelerometer;
    Timer			timeSinceStart;
};
#endif

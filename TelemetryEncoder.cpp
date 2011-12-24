#include "TelemetryEncoder.h"
#include "mbed.h"

TelemetryEncoder::TelemetryEncoder(void) {
}
int TelemetryEncoder::fillFrame( uint8_t *bp) {
        uint8_t *firstByte = bp;
        *bp++ = 0;

        *bp++ = (accelerometer.x>>8) & 0xff;
        *bp++ = accelerometer.x & 0xff;

        *bp++ = (accelerometer.y>>8) & 0xff;
        *bp++ = accelerometer.y & 0xff;

        *bp++ = (accelerometer.z>>8) & 0xff;
        *bp++ = accelerometer.z & 0xff;

        *bp++ = (gyro.x>>8) & 0xff;
        *bp++ = gyro.x & 0xff;

        *bp++ = (gyro.y>>8) & 0xff;
        *bp++ = gyro.y & 0xff;
        
        *bp++ = (gyro.z>>8) & 0xff;
        *bp++ = gyro.z & 0xff;

        int sum = 0;
        for (int i = 0; i < (bp-firstByte); i++) {
            sum += firstByte[i];
        }
        *bp++ = (sum&0xff);
        return (bp-firstByte);
}

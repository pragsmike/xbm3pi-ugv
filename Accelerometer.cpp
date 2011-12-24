#include "Accelerometer.h"

Accelerometer::Accelerometer(void) : ax(p15), ay(p16), az(p17) {
    ticker.attach(this, &Accelerometer::tick, 0.005);
}

void Accelerometer::tick(void) {
    x = ax.read_u16() - 0x8000;
    y = ay.read_u16() - 0x8000;
    z = az.read_u16() - 0x8000;
}

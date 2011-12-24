#include "CommandDispatcher.h"


CommandDispatcher::CommandDispatcher(m3pi &m3pi) {
    _m3pi = &m3pi;
}

void CommandDispatcher::init() {
    _m3pi->locate(0,1);
    _m3pi->printf("ready?");

    wait (1.0);
    _m3pi->stop();
    _m3pi->cls();
    _m3pi->printf("Receiving");
}

#define RAD2 .707

void CommandDispatcher::drive(float x, float y) {
    x = x * -0.15;
    float xt = RAD2*x + RAD2*y;
    float yt = - RAD2*x + RAD2*y;

    _m3pi->locate(0,0);
    _m3pi->printf("%f", xt);
    _m3pi->locate(0,1);
    _m3pi->printf("%f", yt);
    _m3pi->left_motor(xt);
    _m3pi->right_motor(yt);
}

#ifndef CommandDispatcher_h
#define CommandDispatcher_h

#include "m3pi.h"

class CommandDispatcher {

public:
    CommandDispatcher(m3pi &_m3pi);
    void drive(float x, float y);
    void init();

private:
    m3pi *_m3pi;
};
#endif

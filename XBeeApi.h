#ifndef XBeeApi_h
#define XBeeApi_h

#include "mbed.h"
#include "XBee.h"

class XBeeApi {

public:
    XBeeApi(PinName p_tx, PinName p_rx, PinName p_rst);

    int readable();
    int getc();
    void send(uint8_t *payload, int payloadLength);
private:
    XBee        _xbee;
    DigitalOut  _rst;
    
    int unread;
    Rx16Response response;
};
#endif

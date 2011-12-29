#ifndef USBSerial_h
#define USBSerial_h

#include "mbed.h"

class USBSerial {

public:
	USBSerial(Serial &pc);

    int readable();
    int getc();
    void send(uint8_t *payload, int payloadLength);
private:
    Serial *_pc;
};
#endif

#ifndef Gyro_h
#define Gyro_h

#include "mbed.h"

class Gyro {

public:
    Gyro(void);
    void tick(void);
    
    int x, y, z;

private:
    SPI         spi;
    DigitalOut  cs;
    int         readWord();
    int         readByte(uint8_t regaddr);
    void        writeByte(uint8_t regaddr, uint8_t data);
    Ticker      ticker;

};
#endif

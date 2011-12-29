#include "Gyro.h"

#define WHO_AM_I 0x0f

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define STATUS_REG 0x27

#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D
#define FIFO_CTRL_REG 0x2E


Gyro::Gyro(void) : spi(p5, p6, p7), cs(p14) {  // mosi, miso, sclk

    // Setup the spi for 8 bit data, high steady state clock,
    // second edge capture, with a 1MHz clock rate
    spi.format(8,3);
    spi.frequency(1000000);
//    cs = 1;
    
    writeByte(CTRL_REG2,0x00);      // hpf
    writeByte(CTRL_REG3,0x00);      // interrupts
    writeByte(CTRL_REG4,0x00);      // full-scale range
    writeByte(FIFO_CTRL_REG, 0x00);
    writeByte(CTRL_REG5,0x00);      // high-pass filtering of outputs
    writeByte(CTRL_REG1,0x0f);      // power up, enable axes
}

void Gyro::tick(void) {
    int status = readByte(STATUS_REG);
    if ((status & 0x08) == 0) {
        return;
    }        
    cs = 0;
    spi.write(0xC0 | OUT_X_L);
    x = readWord();
    y = readWord();
    z = readWord();
    cs = 1;
    
    // rotate coords, as accel. and gyro oriented differently
    int t = x;
    x = -y;
    y = -t;
    z = -z;
}
int Gyro::readWord() {
    int l = spi.write(0x00);
    int h = spi.write(0x00);
    return (h<<8)|l;
}
int Gyro::readByte(uint8_t regaddr) {
    cs = 0;
    spi.write(0x80 | regaddr);
    int d = spi.write(0x00);
    cs = 1;
    return d;
}
void Gyro::writeByte(uint8_t regaddr, uint8_t data) {
    cs = 0;
    spi.write(regaddr);
    spi.write(data);
    cs = 1;
}

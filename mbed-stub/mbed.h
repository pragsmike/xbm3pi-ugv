#ifndef MBED_H
#define MBED_H

#include "stdint.h"

#define p5 5
#define p6 6
#define p7 7
#define p14 14
#define p15 15
#define p16 16
#define p17 17

#define wait(t)

class AnalogIn {
public:
	AnalogIn(int i);
	uint16_t read_u16();
private:
};

class DigitalOut {
public:
	DigitalOut(int i);
private:
};

class SPI {
public:
	SPI(int i, int j, int k);
	void format(int i, int i);
	void frequency(int i);
	int write(int i);
private:
};


class Ticker {
public:
    template<typename T>
    void attach(T* tptr, void (T::*mptr)(void), float t) {
            }
private:
};

class Timer {
public:
    inline void start() {;};
    inline int read_us() { return 0;};
private:
};


class Serial {
public:
	inline int putc(int c) { return 0; };
	inline int printf(const char* format) { return 0; };
	inline int printf(const char* format, int a) { return 0; };
	inline int printf(const char* format, int a, int b) { return 0; };
	inline int printf(const char* format, int a, int b, int c) { return 0; };
	inline int printf(const char* format, char *a) { return 0; };
private:
};
#endif

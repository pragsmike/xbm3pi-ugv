
#ifndef Log_H
#define Log_H

#include "mbed.h"

class Log {

public:
	Log(Serial &pc);

	int putc(int c);
	int printf(const char* format);
	int printf(const char* format, int a);
	int printf(const char* format, int a, int b);
	int printf(const char* format, int a, int b, int c);
	int printf(const char* format, char *a);

private:
    Serial				*_pc;

};

#endif

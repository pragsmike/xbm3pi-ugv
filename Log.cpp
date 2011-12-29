#include "Log.h"

Log::Log(Serial &pc) {
	_pc = &pc;
}

// yuck.  http://c-faq.com/~scs/cclass/int/sx11c.html
int Log::printf(const char* format) {
	return _pc->printf(format);
}
int Log::printf(const char* format, int a) {
	return _pc->printf(format, a);
}
int Log::printf(const char* format, int a, int b) {
	return _pc->printf(format, a, b);
}
int Log::printf(const char* format, int a, int b, int c) {
	return _pc->printf(format, a, b, c);
}
int Log::printf(const char* format, char *a) {
	return _pc->printf(format, a);
}
int Log::putc(int c) {
	return _pc->putc(c);
}

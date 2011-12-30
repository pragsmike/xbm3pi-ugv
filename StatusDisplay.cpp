#include "StatusDisplay.h"
#include "mbed.h"

StatusDisplay::StatusDisplay() {
}

StatusDisplay::~StatusDisplay() {
}

void StatusDisplay::showMode(int mode) {
	DigitalOut led(LED1);
	led = (mode != 0);
}

void StatusDisplay::showActive(bool b) {
	DigitalOut led(LED2);
	led = b;
}

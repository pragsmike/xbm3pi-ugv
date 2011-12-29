#include "mbed.h"
#include "USBSerial.h"


USBSerial::USBSerial(Serial &pc) {
	_pc = &pc;
}

int USBSerial::readable() {
    return _pc->readable();
}

int USBSerial::getc() {
    return _pc->getc();
}

void USBSerial::send(uint8_t *payload, int payloadLength) {
	for (int i = 0; i < payloadLength; i++) {
		while (!_pc->writeable()) {
			wait_us(100);
		}
		_pc->putc(payload[i]);
	}
}

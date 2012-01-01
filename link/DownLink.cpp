/*
 * DownLink.cpp
 *
 *  Created on: Dec 31, 2011
 *      Author: mg
 */

#include "DownLink.h"

DownLink::DownLink() {
	sourceCount = 0;
}

DownLink::~DownLink() {}

int DownLink::available(void) {
	int a = 0;
	for (unsigned i = 0; i < sourceCount; i++ ) {
		a += sources[i]->available();
	}
	return a;
}
mavlink_message_t * DownLink::nextMessage(void) {
	for (unsigned i = 0; i < sourceCount; i++ ) {
		if (sources[i]->available()) {
			return sources[i]->nextMessage();
		}
	}
	return 0;
}

void DownLink::addSource(IMsgSource &src) {
	if (sourceCount < sizeof(sources)) {
		sources[sourceCount++] = &src;
	}
}
void DownLink::clearSources() {
	sourceCount = 0;
}

int DownLink::nextMessageBytes(uint8_t *bp) {
	if (!available())
		return 0;
	uint16_t len = mavlink_msg_to_send_buffer(bp, nextMessage());
	return len;
}

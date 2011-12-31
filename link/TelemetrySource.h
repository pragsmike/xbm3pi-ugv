/*
 * TelemetrySource.h
 *
 *  Created on: Dec 31, 2011
 *      Author: mg
 */

#ifndef TELEMETRYSOURCE_H_
#define TELEMETRYSOURCE_H_

#include "mavlink.h"
#include "../TelemetryEncoderMavLink.h"
#include "IMsgSource.h"

class TelemetrySource : public IMsgSource {
public:
	TelemetrySource(TelemetryEncoderMavLink &e);
	virtual ~TelemetrySource();

	int available(void);
	mavlink_message_t *nextMessage();
	int nextMessageBytes(uint8_t *bytes);

	void forceAvailable(uint8_t msgType);

	void setPeriod(uint8_t msgTypeId, int periodTicks);
	void setTick(int tick);
	bool isMsgTypeAvailAtTick(int tick, uint8_t msgType);
private:
	mavlink_message_t m;
	uint8_t msgTypePeriods[255];
	int _tick;
	TelemetryEncoderMavLink *encoder;
	int msgTypesAvailable[10];
	int msgTypesAvailableCount;
	int msgTypesKnown[10];
	int msgTypesKnownCount;
};

#endif /* TELEMETRYSOURCE_H_ */

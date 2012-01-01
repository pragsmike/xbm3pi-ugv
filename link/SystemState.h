/*
 * SystemState.h
 *
 *  Created on: Dec 31, 2011
 *      Author: mg
 */

#ifndef SYSTEMSTATE_H_
#define SYSTEMSTATE_H_

#include "mavlink.h"
#include "../TelemetryData.h"
#include "IMsgSource.h"

class SystemState : public IMsgSource {
public:
	SystemState(TelemetryData &data);
	virtual ~SystemState();

	int available(void);
	mavlink_message_t *nextMessage();

    void sendCommandAck(uint16_t command, uint8_t result);
private:
    int 					pending;

    TelemetryData 			*telemetryData;
	mavlink_command_ack_t	command_ack;
	mavlink_message_t 		msg;
};

#endif /* SYSTEMSTATE_H_ */

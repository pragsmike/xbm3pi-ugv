/*
 * SystemState.cpp
 *
 *  Created on: Dec 31, 2011
 *      Author: mg
 */

#include "SystemState.h"

SystemState::SystemState(TelemetryData &data) {
	telemetryData = &data;
	pending = 0;
}

SystemState::~SystemState() {}

int SystemState::available(void) {
	return pending;
}
mavlink_message_t * SystemState::nextMessage(void) {
	if (!pending)
		return 0;
	pending = 0;
	mavlink_msg_command_ack_encode(telemetryData->mavlink_system.sysid, telemetryData->mavlink_system.compid, &msg, &command_ack);
	return &msg;
}
void SystemState::sendCommandAck(uint16_t command, uint8_t result) {
	command_ack.command = command;
	command_ack.result = result;
	pending = 1;
}

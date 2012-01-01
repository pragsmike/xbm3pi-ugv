/*
 * MissionSyncer.cpp
 *
 *  Created on: Dec 31, 2011
 *      Author: mg
 */

#include "MissionSyncer.h"

MissionSyncer::MissionSyncer(TelemetryData &data) {
	telemetryData = &data;
	pending = 0;
}

MissionSyncer::~MissionSyncer() {}

int MissionSyncer::available(void) {
	return pending;
}
mavlink_message_t * MissionSyncer::nextMessage(void) {
	if (!pending)
		return 0;
	pending = 0;
	mavlink_msg_mission_count_encode(telemetryData->mavlink_system.sysid, telemetryData->mavlink_system.compid, &msg, &param);
	return &msg;
}
void MissionSyncer::sendMissionList() {
	pending = 1;
}
void MissionSyncer::sendMissionRequest(uint8_t system, uint8_t component, uint8_t index) {
	mission_request.target_system = system;
	mission_request.target_component = component;
	mission_request.seq = index;
}

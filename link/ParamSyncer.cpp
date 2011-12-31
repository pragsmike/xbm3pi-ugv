/*
 * ParamSyncer.cpp
 *
 *  Created on: Dec 31, 2011
 *      Author: mg
 */

#include "ParamSyncer.h"

ParamSyncer::ParamSyncer(TelemetryData &data) {
	telemetryData = &data;
	pending = 0;
}

ParamSyncer::~ParamSyncer() {}

int ParamSyncer::available(void) {
	return pending;
}
mavlink_message_t * ParamSyncer::nextMessage(void) {
	if (!pending)
		return 0;
	pending = 0;
	mavlink_msg_param_value_encode(telemetryData->mavlink_system.sysid, telemetryData->mavlink_system.compid, &msg, &param);
	return &msg;
}
void ParamSyncer::sendParamList() {
	pending = 1;
}

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

	param.param_count = 1;
	param.param_index = 0;
	param.param_id[0] = 'A';
	param.param_id[1] = 'Y';
	param.param_id[3] = 0;
	param.param_type = MAVLINK_TYPE_FLOAT;
	param.param_value = 12.;

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
void ParamSyncer::setParamValue(char *id, int idLength, float param_value) {
	param.param_value = param_value;
	pending = 1;
}

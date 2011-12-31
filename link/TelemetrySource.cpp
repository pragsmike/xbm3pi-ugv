#include "TelemetrySource.h"

TelemetrySource::TelemetrySource(TelemetryEncoderMavLink &e) {
	encoder = &e;
	msgTypesAvailableCount = 0;
	msgTypesKnown[msgTypesKnownCount++] = MAVLINK_MSG_ID_HEARTBEAT;
	msgTypesKnown[msgTypesKnownCount++] = MAVLINK_MSG_ID_RAW_IMU;
	msgTypesKnown[msgTypesKnownCount++] = MAVLINK_MSG_ID_SYS_STATUS;
	msgTypesKnown[msgTypesKnownCount++] = MAVLINK_MSG_ID_SCALED_IMU;
	msgTypesKnown[msgTypesKnownCount++] = MAVLINK_MSG_ID_ATTITUDE;
	msgTypesKnown[msgTypesKnownCount++] = MAVLINK_MSG_ID_LOCAL_POSITION_NED;
}

TelemetrySource::~TelemetrySource() {}

int TelemetrySource::available(void) {
	return msgTypesAvailableCount;
}

mavlink_message_t *TelemetrySource::nextMessage() {
	if (msgTypesAvailableCount > 0) {
		encoder->fillMsg(m, msgTypesAvailable[--msgTypesAvailableCount]);
		return &m;
	}
	return 0;
}

void TelemetrySource::forceAvailable(uint8_t c) {
	msgTypesAvailable[msgTypesAvailableCount++] = c;
}

int TelemetrySource::nextMessageBytes(uint8_t *bp) {
	if (!available())
		return 0;
	uint16_t len = mavlink_msg_to_send_buffer(bp, nextMessage());
	return len;
}

void TelemetrySource::setPeriod(uint8_t msgTypeId, int periodTicks) {
	msgTypePeriods[msgTypeId] = periodTicks;
}

bool TelemetrySource::isMsgTypeAvailAtTick(int tick, uint8_t msgType) {
	int period = msgTypePeriods[msgType];
	return ((period != 0) && (tick%period) == 0);
}

void TelemetrySource::setTick(int tick) {
	_tick = tick;
	msgTypesAvailableCount = 0;
	for (int i = 0; i < msgTypesKnownCount; i++) {
		if (isMsgTypeAvailAtTick(_tick, msgTypesKnown[i])) {
			msgTypesAvailable[msgTypesAvailableCount++] = msgTypesKnown[i];
		}
	}
}

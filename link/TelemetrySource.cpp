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

	setPeriod(MAVLINK_MSG_ID_HEARTBEAT, 			503);
	if (1) {
		setPeriod(MAVLINK_MSG_ID_RAW_IMU,   			0);
		setPeriod(MAVLINK_MSG_ID_SCALED_IMU,   			0);
		setPeriod(MAVLINK_MSG_ID_ATTITUDE,   			0);
		setPeriod(MAVLINK_MSG_ID_LOCAL_POSITION_NED, 	0);
		setPeriod(MAVLINK_MSG_ID_SYS_STATUS,   			509);
	} else {
		setPeriod(MAVLINK_MSG_ID_RAW_IMU,   			150);
		setPeriod(MAVLINK_MSG_ID_SCALED_IMU,   			152);
		setPeriod(MAVLINK_MSG_ID_ATTITUDE,   			460);
		setPeriod(MAVLINK_MSG_ID_LOCAL_POSITION_NED, 	544);
		setPeriod(MAVLINK_MSG_ID_SYS_STATUS,   			256);
	}
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

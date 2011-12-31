/**
 * Main class for unit tests
 */
#include <UnitTest++.h>
#include "../link/TelemetrySource.h"

using namespace UnitTest;

namespace {

uint8_t b[MAVLINK_MAX_PACKET_LEN];
TelemetryData			data;
TelemetryEncoderMavLink	encoder(data);
TelemetrySource 		source(encoder);

TEST(TelemetrySourceNoneAvailable)
{
	CHECK(source.available() == false);
	CHECK(source.nextMessage() == (mavlink_message_t *)0);
}


TEST(TelemetrySourceOneAvailable)
{
	source.forceAvailable(MAVLINK_MSG_ID_RAW_IMU);

	CHECK(source.available() == 1);
	mavlink_message_t *m = source.nextMessage();
	CHECK(m != (mavlink_message_t *)0);
	CHECK_EQUAL(MAVLINK_MSG_ID_RAW_IMU, m->msgid );
}
void checkMessageTypeAvailAtTick(int tick, int msgType) {
	source.setTick(tick);
	CHECK_EQUAL(true, source.isMsgTypeAvailAtTick(tick, msgType));
	int guard = 10;
	while (guard-- > 0 && source.available()) {
		if (msgType == source.nextMessage()->msgid)
			return;
	}
	CHECK_EQUAL(0, 1);
}
void checkMessageTypeNotAvailAtTick(int tick, int msgType) {
	source.setTick(tick);
	CHECK_EQUAL(false, source.isMsgTypeAvailAtTick(tick, msgType));
	int guard = 10;
	while (guard-- > 0 && source.available()) {
		if (msgType == source.nextMessage()->msgid) {
			CHECK_EQUAL(2,3);
		}
	}
}
void setAllPeriodsToZero() {
	source.setPeriod(MAVLINK_MSG_ID_HEARTBEAT, 			0);
	source.setPeriod(MAVLINK_MSG_ID_RAW_IMU,   			0);
	source.setPeriod(MAVLINK_MSG_ID_SCALED_IMU,   		0);
	source.setPeriod(MAVLINK_MSG_ID_ATTITUDE,   		0);
	source.setPeriod(MAVLINK_MSG_ID_LOCAL_POSITION_NED, 0);
	source.setPeriod(MAVLINK_MSG_ID_SYS_STATUS,   		0);
}
TEST(TelemetrySourceAllTypesDisabled)
{
	setAllPeriodsToZero();

	for (int tick = 0; tick < 10; tick++) {
		source.setTick(tick);
		CHECK_EQUAL(false, source.available());
	}
}
TEST(TelemetrySourceOneTypeEnabled)
{
	setAllPeriodsToZero();

	source.setPeriod(MAVLINK_MSG_ID_RAW_IMU, 			1);

	checkMessageTypeAvailAtTick(0, MAVLINK_MSG_ID_RAW_IMU);
	checkMessageTypeAvailAtTick(1, MAVLINK_MSG_ID_RAW_IMU);

	source.setPeriod(MAVLINK_MSG_ID_RAW_IMU, 			2);

	checkMessageTypeAvailAtTick(0, MAVLINK_MSG_ID_RAW_IMU);
	checkMessageTypeNotAvailAtTick(1, MAVLINK_MSG_ID_RAW_IMU);
	checkMessageTypeAvailAtTick(2, MAVLINK_MSG_ID_RAW_IMU);
	checkMessageTypeNotAvailAtTick(3, MAVLINK_MSG_ID_RAW_IMU);
}
TEST(TelemetrySourceAvailable)
{
	setAllPeriodsToZero();
	source.setPeriod(MAVLINK_MSG_ID_RAW_IMU, 			1);
	source.setTick(0);
	CHECK_EQUAL(1, source.available());

	source.setPeriod(MAVLINK_MSG_ID_SYS_STATUS, 		1);
	source.setTick(0);
	CHECK_EQUAL(2, source.available());

}
TEST(TelemetrySourceTwoTypesEnabled)
{
	setAllPeriodsToZero();

	source.setPeriod(MAVLINK_MSG_ID_RAW_IMU, 			1);
	source.setPeriod(MAVLINK_MSG_ID_SYS_STATUS, 		1);

	checkMessageTypeAvailAtTick(0, MAVLINK_MSG_ID_RAW_IMU);
	checkMessageTypeAvailAtTick(0, MAVLINK_MSG_ID_SYS_STATUS);
	checkMessageTypeAvailAtTick(1, MAVLINK_MSG_ID_RAW_IMU);
	checkMessageTypeAvailAtTick(1, MAVLINK_MSG_ID_SYS_STATUS);

	source.setPeriod(MAVLINK_MSG_ID_RAW_IMU, 			2);

	checkMessageTypeAvailAtTick(0, MAVLINK_MSG_ID_RAW_IMU);
	checkMessageTypeNotAvailAtTick(1, MAVLINK_MSG_ID_RAW_IMU);
	checkMessageTypeAvailAtTick(2, MAVLINK_MSG_ID_RAW_IMU);
	checkMessageTypeNotAvailAtTick(3, MAVLINK_MSG_ID_RAW_IMU);
}


}

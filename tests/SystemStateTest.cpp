#include <UnitTest++.h>
#include "../link/SystemState.h"

using namespace UnitTest;

namespace {

TelemetryData			data;
SystemState				systemState(data);

TEST(SystemStateInitialState)
{
	CHECK_EQUAL(0, systemState.available());
	CHECK_EQUAL((mavlink_message_t *)0, systemState.nextMessage());
}

TEST(SystemStateSendCommandAckList)
{
	systemState.sendCommandAck(MAV_CMD_NAV_TAKEOFF, MAV_RESULT_ACCEPTED);
	CHECK_EQUAL(1, systemState.available());
	mavlink_message_t *m = systemState.nextMessage();
	CHECK(m != 0);
	CHECK_EQUAL(MAVLINK_MSG_ID_COMMAND_ACK, m->msgid);
}

}

#include <UnitTest++.h>
#include "../link/MissionSyncer.h"
#include "../TelemetryData.h"

using namespace UnitTest;

namespace {

TelemetryData			data;
MissionSyncer				syncer(data);

TEST(MissionSyncerInitialState)
{
	CHECK_EQUAL(0, syncer.available());
	CHECK_EQUAL((mavlink_message_t *)0, syncer.nextMessage());
}

TEST(MissionSyncerSendParamList)
{
	syncer.sendMissionList();
	CHECK_EQUAL(1, syncer.available());
	mavlink_message_t *m = syncer.nextMessage();
	CHECK(m != 0);
	CHECK_EQUAL(MAVLINK_MSG_ID_MISSION_COUNT, m->msgid);
}

}

/**
 * Main class for unit tests
 */
#include <UnitTest++.h>
#include "../link/ParamSyncer.h"
#include "../TelemetryData.h"

using namespace UnitTest;

namespace {

TelemetryData			data;
ParamSyncer				syncer(data);

TEST(ParamSyncerInitialState)
{
	CHECK_EQUAL(0, syncer.available());
	CHECK_EQUAL((mavlink_message_t *)0, syncer.nextMessage());
}

TEST(ParamSyncerSendParamList)
{
	syncer.sendParamList();
	CHECK_EQUAL(1, syncer.available());
	mavlink_message_t *m = syncer.nextMessage();
	CHECK(m != 0);
	CHECK_EQUAL(MAVLINK_MSG_ID_PARAM_VALUE, m->msgid);
}

}

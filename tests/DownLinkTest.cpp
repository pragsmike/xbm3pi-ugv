/**
 * Main class for unit tests
 */
#include <UnitTest++.h>
#include "../link/ParamSyncer.h"
#include "../link/DownLink.h"


using namespace UnitTest;

namespace {

TelemetryData			data;
ParamSyncer				syncer(data);
DownLink				downLink;

class StubSource : public IMsgSource
{
public:
	int available() { return 0;}
	mavlink_message_t *nextMessage() {
		return (mavlink_message_t *) 0;
	};
};
class NonEmptyStubSource : public IMsgSource
{
public:
	NonEmptyStubSource(mavlink_message_t &m) {
		msg = &m;
		count = 1;
	}
	int available() { return count;}
	mavlink_message_t *nextMessage() {
		if (count == 0)
			return (mavlink_message_t *) 0;
		count--;
		return msg;
	};
private:
	mavlink_message_t *msg;
	int count;
};
TEST(DownLinkInitialState)
{
	CHECK_EQUAL(0, downLink.available());
	CHECK_EQUAL((mavlink_message_t *)0, downLink.nextMessage());
}
TEST(DownLinkEmptySource)
{
	StubSource stubSource;
	downLink.clearSources();
	downLink.addSource(stubSource);
	CHECK_EQUAL(0, downLink.available());
	CHECK_EQUAL((mavlink_message_t *)0, downLink.nextMessage());
}
TEST(DownLinkNonEmptySource)
{
	mavlink_message_t msg;

	NonEmptyStubSource stubSource(msg);
	downLink.clearSources();
	downLink.addSource(stubSource);
	CHECK_EQUAL(1, downLink.available());
	CHECK_EQUAL(&msg, downLink.nextMessage());
}

TEST(DownLinkTwoNonEmptySource)
{
	mavlink_message_t msg1;
	mavlink_message_t msg2;

	NonEmptyStubSource stubSource1(msg1);
	NonEmptyStubSource stubSource2(msg2);

	downLink.clearSources();
	downLink.addSource(stubSource1);
	downLink.addSource(stubSource2);


	CHECK_EQUAL(2, downLink.available());
	CHECK_EQUAL(&msg1, downLink.nextMessage());
	CHECK_EQUAL(&msg2, downLink.nextMessage());
}

}

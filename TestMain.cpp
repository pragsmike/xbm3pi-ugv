/**
 * Main class for unit tests
 */
#include <UnitTest++.h>

TEST(FailSpectacularly)
{
	CHECK(false);
}


int main(int, char const *[])
{
	return UnitTest::RunAllTests();
}

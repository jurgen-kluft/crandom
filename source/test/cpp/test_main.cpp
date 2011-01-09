#include "xbase\x_target.h"
#include "xbase\x_types.h"

#include "xunittest\xunittest.h"

using namespace xcore;

UNITTEST_SUITE_LIST(xRandomUnitTest);
UNITTEST_SUITE_DECLARE(xRandomUnitTest, xrandom);

s32 main(s32 argc, char** argv)
{
	UnitTest::TestReporterStdout reporter;
	s32 r = UNITTEST_SUITE_RUN(reporter, xRandomUnitTest);

	return r;
}
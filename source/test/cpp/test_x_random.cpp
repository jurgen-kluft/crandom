#include "xbase\x_types.h"
#include "xrandom\Random.h"

#include "xunittest\xunittest.h"

using namespace xcore;

UNITTEST_SUITE_BEGIN(xrandom)
{
    UNITTEST_FIXTURE(main)
    {
        UNITTEST_FIXTURE_SETUP() {}
        UNITTEST_FIXTURE_TEARDOWN() {}

        UNITTEST_TEST(randomness)
        {
			f32 rf = xqrnd::Float();
			for (s32 i=0; i<50; i++)
			{
				f32 rf2 = xqrnd::Float();
				CHECK_NOT_EQUAL(rf, rf2);
			}
        }
	}
}
UNITTEST_SUITE_END
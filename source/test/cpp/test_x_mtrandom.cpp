#include "xbase\x_types.h"
#include "xrandom\mtrandom.h"

#include "xunittest\xunittest.h"

using namespace xcore;

UNITTEST_SUITE_BEGIN(xmtrandom)
{
    UNITTEST_FIXTURE(main)
    {
		xmtrandom	sMtRnd;

        UNITTEST_FIXTURE_SETUP() 
		{
			sMtRnd.Seed();
		}
        UNITTEST_FIXTURE_TEARDOWN()
		{
			sMtRnd.Release();
		}

        UNITTEST_TEST(randomness)
        {
			f32 rf = sMtRnd.RandF();
			for (s32 i=0; i<50; i++)
			{
				f32 rf2 = sMtRnd.RandF();
				CHECK_NOT_EQUAL(rf, rf2);
			}
        }
	}
}
UNITTEST_SUITE_END
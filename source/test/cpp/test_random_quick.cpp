#include "crandom/c_random.h"
#include "crandom/c_random_quick.h"

#include "cunittest/cunittest.h"

using namespace ncore;

UNITTEST_SUITE_BEGIN(random_quick)
{
    UNITTEST_FIXTURE(main)
    {
        UNITTEST_FIXTURE_SETUP() {}
        UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(Init)
		{
			rndquick sRnd;
            sRnd.reset();

			u32 ru = g_random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,g_random_u32(&sRnd));
			sRnd.reset(132465);
			ru=g_random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,g_random_u32(&sRnd));
			sRnd.reset(-1325);
			ru=g_random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,g_random_u32(&sRnd));
			ru=g_random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,g_random_u32(&sRnd));
			sRnd.reset('a');
			ru=g_random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,g_random_u32(&sRnd));
		}

		UNITTEST_TEST(Rand)
		{
			rndquick sRnd;
            sRnd.reset();

			u32 ru;
			ru=g_random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,g_random_u32(&sRnd));
			ru=g_random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,g_random_u32(&sRnd));
			ru=g_random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,g_random_u32(&sRnd));

			for(s32 i=0;i<50;i++)
			{
				ru=g_random_u32(&sRnd);
				CHECK_EQUAL((ru>=0),true);
				if(ru%3!=0) CHECK_NOT_EQUAL(ru/3*3,ru);
			}
		}

		UNITTEST_TEST(RandBool)
		{
			rndquick sRnd;
            sRnd.reset();

			u32 rbool = 0;
			u32 trueCount = 0, falseCount = 0;
			for (s32 i = 0; i < 50; i++)
			{
				rbool = g_random_bool(&sRnd);
				CHECK_EQUAL(rbool != 1 && rbool != 0, false);
				trueCount += rbool ? 1 : 0;
				falseCount += rbool ? 0 : 1;
			}
			CHECK_TRUE(trueCount > 0 && falseCount > 0);
		}
	}
}
UNITTEST_SUITE_END

#include "crandom/c_random.h"
#include "crandom/c_random_quick.h"

#include "cunittest/cunittest.h"

using namespace ncore;

UNITTEST_SUITE_BEGIN(xrandom_quick)
{
    UNITTEST_FIXTURE(main)
    {
        UNITTEST_FIXTURE_SETUP() {}
        UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(xrnd_Init)
		{
			rndquick sRnd;

			u32 ru = sRnd.generate();
			CHECK_NOT_EQUAL(ru,sRnd.generate());
			sRnd.reset(132465);
			ru=sRnd.generate();
			CHECK_NOT_EQUAL(ru,sRnd.generate());
			sRnd.reset(-1325);
			ru=sRnd.generate();
			CHECK_NOT_EQUAL(ru,sRnd.generate());
			ru=sRnd.generate();
			CHECK_NOT_EQUAL(ru,sRnd.generate());
			sRnd.reset('a');
			ru=sRnd.generate();
			CHECK_NOT_EQUAL(ru,sRnd.generate());
		}

		UNITTEST_TEST(xrnd_Rand)
		{
			rndquick sRnd;

			u32 ru;
			ru=sRnd.generate();
			CHECK_NOT_EQUAL(ru,sRnd.generate());
			ru=sRnd.generate();
			CHECK_NOT_EQUAL(ru,sRnd.generate());
			ru=sRnd.generate();
			CHECK_NOT_EQUAL(ru,sRnd.generate());

			for(s32 i=0;i<50;i++)
			{
				ru=sRnd.generate();
				CHECK_EQUAL((ru>=0),true);
				if(ru%3!=0) CHECK_NOT_EQUAL(ru/3*3,ru);
			}
		}
	}
	
}
UNITTEST_SUITE_END
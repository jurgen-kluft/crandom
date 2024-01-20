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

			u32 ru = random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,random_u32(&sRnd));
			sRnd.reset(132465);
			ru=random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,random_u32(&sRnd));
			sRnd.reset(-1325);
			ru=random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,random_u32(&sRnd));
			ru=random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,random_u32(&sRnd));
			sRnd.reset('a');
			ru=random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,random_u32(&sRnd));
		}

		UNITTEST_TEST(Rand)
		{
			rndquick sRnd;

			u32 ru;
			ru=random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,random_u32(&sRnd));
			ru=random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,random_u32(&sRnd));
			ru=random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,random_u32(&sRnd));

			for(s32 i=0;i<50;i++)
			{
				ru=random_u32(&sRnd);
				CHECK_EQUAL((ru>=0),true);
				if(ru%3!=0) CHECK_NOT_EQUAL(ru/3*3,ru);
			}
		}
	}
	
}
UNITTEST_SUITE_END
#include "crandom/c_random.h"
#include "crandom/c_random_mersenne_twister.h"

#include "cunittest/xunittest.h"

using namespace ncore;

UNITTEST_SUITE_BEGIN(xrandom_mt)
{
	UNITTEST_FIXTURE(main)
	{
		UNITTEST_FIXTURE_SETUP() {}
		UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(seed1)
        {
			rndmersenne sMtRnd;
			sMtRnd.reset();
			CHECK_NOT_EQUAL(sMtRnd.generate(),sMtRnd.generate());
			sMtRnd.reset(12345679);
			CHECK_NOT_EQUAL(sMtRnd.generate(),sMtRnd.generate());
			sMtRnd.reset(-132);	
			CHECK_NOT_EQUAL(sMtRnd.generate(),sMtRnd.generate());
			//sMtRnd.reset(123.5f);//	warning
			CHECK_NOT_EQUAL(sMtRnd.generate(),sMtRnd.generate());
			sMtRnd.reset('x');	
			CHECK_NOT_EQUAL(sMtRnd.generate(),sMtRnd.generate());
		}
		
	}
}
UNITTEST_SUITE_END
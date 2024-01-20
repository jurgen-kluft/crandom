#include "crandom/c_random.h"
#include "crandom/c_random_mersenne_twister.h"

#include "cunittest/cunittest.h"

using namespace ncore;

UNITTEST_SUITE_BEGIN(random_mt)
{
    UNITTEST_FIXTURE(main)
    {
        UNITTEST_FIXTURE_SETUP() {}
        UNITTEST_FIXTURE_TEARDOWN() {}

        UNITTEST_TEST(generate_u32)
        {
            rndmersenne sMtRnd;
            sMtRnd.reset();
            CHECK_NOT_EQUAL(sMtRnd.generate_u32(), sMtRnd.generate_u32());
            sMtRnd.reset(12345679);
            CHECK_NOT_EQUAL(sMtRnd.generate_u32(), sMtRnd.generate_u32());
            sMtRnd.reset(-132);
            CHECK_NOT_EQUAL(sMtRnd.generate_u32(), sMtRnd.generate_u32());
            CHECK_NOT_EQUAL(sMtRnd.generate_u32(), sMtRnd.generate_u32());
            sMtRnd.reset('x');
            CHECK_NOT_EQUAL(sMtRnd.generate_u32(), sMtRnd.generate_u32());
        }


        UNITTEST_TEST(generate_u64)
        {
            rndmersenne sMtRnd;
            sMtRnd.reset();
            CHECK_NOT_EQUAL(sMtRnd.generate_u64(), sMtRnd.generate_u64());
            sMtRnd.reset(12345679);
            CHECK_NOT_EQUAL(sMtRnd.generate_u64(), sMtRnd.generate_u64());
            sMtRnd.reset(-132);
            CHECK_NOT_EQUAL(sMtRnd.generate_u64(), sMtRnd.generate_u64());
            CHECK_NOT_EQUAL(sMtRnd.generate_u64(), sMtRnd.generate_u64());
            sMtRnd.reset('x');
            CHECK_NOT_EQUAL(sMtRnd.generate_u64(), sMtRnd.generate_u64());
        }
    }
}
UNITTEST_SUITE_END
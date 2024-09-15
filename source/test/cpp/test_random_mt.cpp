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
            rndmersenne sRnd;
            sRnd.reset();

            CHECK_NOT_EQUAL(sRnd.generate_u32(), sRnd.generate_u32());
            sRnd.reset(12345679);
            CHECK_NOT_EQUAL(sRnd.generate_u32(), sRnd.generate_u32());
            sRnd.reset(-132);
            CHECK_NOT_EQUAL(sRnd.generate_u32(), sRnd.generate_u32());
            CHECK_NOT_EQUAL(sRnd.generate_u32(), sRnd.generate_u32());
            sRnd.reset('x');
            CHECK_NOT_EQUAL(sRnd.generate_u32(), sRnd.generate_u32());
        }

        UNITTEST_TEST(generate_u64)
        {
            rndmersenne sRnd;
            sRnd.reset();

            CHECK_NOT_EQUAL(sRnd.generate_u64(), sRnd.generate_u64());
            sRnd.reset(12345679);
            CHECK_NOT_EQUAL(sRnd.generate_u64(), sRnd.generate_u64());
            sRnd.reset(-132);
            CHECK_NOT_EQUAL(sRnd.generate_u64(), sRnd.generate_u64());
            CHECK_NOT_EQUAL(sRnd.generate_u64(), sRnd.generate_u64());
            sRnd.reset('x');
            CHECK_NOT_EQUAL(sRnd.generate_u64(), sRnd.generate_u64());
        }

        UNITTEST_TEST(RandBool)
        {
            rndmersenne sRnd;
            sRnd.reset();

            u32 rbool     = 0;
            u32 trueCount = 0, falseCount = 0;
            for (s32 i = 0; i < 50; i++)
            {
                rbool = random_bool(&sRnd);
                CHECK_EQUAL(rbool != 1 && rbool != 0, false);
                trueCount += rbool ? 1 : 0;
                falseCount += rbool ? 0 : 1;
            }
            CHECK_TRUE(trueCount > 0 && falseCount > 0);
        }
    }
}
UNITTEST_SUITE_END

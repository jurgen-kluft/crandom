#include "ccore/c_target.h"
#include "ccore/c_debug.h"
#include "cbase/c_random.h"

#include "crandom/c_random.h"
#include "crandom/c_random_good.h"

#include "cunittest/cunittest.h"

using namespace ncore;

UNITTEST_SUITE_BEGIN(random_good)
{
	UNITTEST_FIXTURE(main)
	{
		UNITTEST_FIXTURE_SETUP() {}
		UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(Init)
		{
			rndgood sRnd;
            sRnd.reset();

			u32 ru = g_random_u32(&sRnd);
            CHECK_NOT_EQUAL(ru, g_random_u32(&sRnd));
			sRnd.reset(132465);
            ru = g_random_u32(&sRnd);
            CHECK_NOT_EQUAL(ru, g_random_u32(&sRnd));
			sRnd.reset(-1325);
            ru = g_random_u32(&sRnd);
            CHECK_NOT_EQUAL(ru, g_random_u32(&sRnd));
            ru = g_random_u32(&sRnd);
            CHECK_NOT_EQUAL(ru, g_random_u32(&sRnd));
			sRnd.reset('a');
            ru = g_random_u32(&sRnd);
            CHECK_NOT_EQUAL(ru, g_random_u32(&sRnd));
		}

		UNITTEST_TEST(Rand)
		{
			rndgood sRnd;
            sRnd.reset();

			u32 ru = g_random_u32(&sRnd);
            CHECK_NOT_EQUAL(ru, g_random_u32(&sRnd));
            ru = g_random_u32(&sRnd, 10);
            CHECK_NOT_EQUAL(ru, g_random_u32(&sRnd, 10));
            ru = g_random_u32(&sRnd, 31);
            CHECK_NOT_EQUAL(ru, g_random_u32(&sRnd, 31));

			u32 history[50];
			for (s32 i = 0; i < 50; i++)
			{
                ru = g_random_u32(&sRnd);
				for (s32 j = 0; j < i; ++j)
				{
					CHECK_NOT_EQUAL(ru, history[j]);
				}
				history[i] = ru;

				if (ru % 3 != 0)
				{
					CHECK_NOT_EQUAL(ru / 3 * 3, ru);
				}
			}
		}

		UNITTEST_TEST(RandSign)
		{
			rndgood sRnd;
            sRnd.reset();

			s32 rs = g_random_s32(&sRnd);
			CHECK_NOT_EQUAL(rs, g_random_s32(&sRnd));
			rs = g_random_s32(&sRnd, 10);
			CHECK_NOT_EQUAL(rs, g_random_s32(&sRnd, 10));
			rs = g_random_u32(&sRnd, 31);
			CHECK_NOT_EQUAL(rs, g_random_s32(&sRnd, 31));

			u32 zzz = 0, zzz2 = 0;
			for (s32 i = 0; i < 50; i++)
			{
				rs = g_random_u32(&sRnd);

				if (rs > 0)
					zzz = 1;
				else
					zzz2 = 1;

				if (rs % 3 != 0)
					CHECK_NOT_EQUAL(rs / 3 * 3, rs);
			}
			CHECK_EQUAL(zzz == 1 && zzz2 == 1, true);
		}

		UNITTEST_TEST(RandF)
		{
			rndgood sRnd;
            sRnd.reset();

			f32 rfloat;
			rfloat = g_random_f32(&sRnd);
			CHECK_NOT_EQUAL(rfloat, g_random_f32(&sRnd));
			for (s32 i = 0; i < 50; i++)
			{
				rfloat = g_random_f32(&sRnd);
				CHECK_EQUAL(rfloat >= 0.0, true);
				CHECK_EQUAL(rfloat <= 1.0, true);
				if ((s32)rfloat % 3 != 0)
					CHECK_EQUAL(rfloat / 3 * 3, rfloat);
			}
		}
		UNITTEST_TEST(RandFSign)
		{
			rndgood sRnd;
            sRnd.reset();

			f32 rfloat;
			u32 zzz = 0, zzz2 = 0;
			rfloat = g_random_f32S(&sRnd);
			CHECK_NOT_EQUAL(rfloat, g_random_f32S(&sRnd));
			for (s32 i = 0; i < 50; i++)
			{
				rfloat = g_random_f32S(&sRnd);
				CHECK_EQUAL(rfloat >= -1.0, true);
				CHECK_EQUAL(rfloat <= 1.0, true);
				if (rfloat > 0.0)
					zzz = 1;
				else
					zzz2 = 1;
				if ((s32)rfloat % 3 != 0)
					CHECK_EQUAL(rfloat / 3 * 3, rfloat);
			}
			CHECK_EQUAL(zzz == 1 && zzz2 == 1, true);
		}

		UNITTEST_TEST(RandBool)
		{
			rndgood sRnd;
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

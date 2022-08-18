#include "cbase/c_target.h"
#include "cbase/c_debug.h"

#include "crandom/c_random.h"
#include "crandom/c_random_good.h"

#include "cunittest/cunittest.h"

using namespace ncore;

class xrand
{
	random_t *m_rnd;

public:
	xrand(random_t *rnd) : m_rnd(rnd) { reset(); }

	void reset(s32 inSeed = 0) { m_rnd->reset(inSeed); }
	u32 generate() { return m_rnd->generate(); }

	inline u32 randU32(u32 inBits = 32)
	{
		ASSERT(inBits <= 32);
		u32 r = generate();
		return (r >> (32 - inBits));
	}

	inline s32 randS32(u32 inBits = 31)
	{
		ASSERT(inBits <= 31);
		return (randU32(inBits + 1) - (1 << inBits));
	}

	inline f32 randF32()
	{
		u32 r = generate();
		u32 fake_float = (r >> (32 - 23)) | 0x3f800000;
		return ((*(f32 *)&fake_float) - 1.0f);
	}

	inline f32 randF32S() { return ((randF32() - 0.5f) * 2.0f); }
	inline bool randBool() { return (randU32(1) == 0); }
};

UNITTEST_SUITE_BEGIN(xrandom_good)
{
	UNITTEST_FIXTURE(main)
	{
		UNITTEST_FIXTURE_SETUP() {}
		UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(xrnd_Init)
		{
			rndgood sGoodRnd;
			xrand sRnd(&sGoodRnd);

			u32 ru = sRnd.randU32();
			CHECK_NOT_EQUAL(ru, sRnd.randU32());
			sRnd.reset(132465);
			ru = sRnd.randU32();
			CHECK_NOT_EQUAL(ru, sRnd.randU32());
			sRnd.reset(-1325);
			ru = sRnd.randU32();
			CHECK_NOT_EQUAL(ru, sRnd.randU32());
			//sRnd.Init(1.0f);//warning
			ru = sRnd.randU32();
			CHECK_NOT_EQUAL(ru, sRnd.randU32());
			sRnd.reset('a');
			ru = sRnd.randU32();
			CHECK_NOT_EQUAL(ru, sRnd.randU32());
		}
		UNITTEST_TEST(xrnd_Rand)
		{
			rndgood sGoodRnd;
			xrand sRnd(&sGoodRnd);

			u32 ru = sRnd.randU32();
			CHECK_NOT_EQUAL(ru, sRnd.randU32());
			ru = sRnd.randU32(10);
			CHECK_NOT_EQUAL(ru, sRnd.randU32(10));
			ru = sRnd.randU32(31);
			CHECK_NOT_EQUAL(ru, sRnd.randU32(31));

			u32 history[50];
			for (s32 i = 0; i < 50; i++)
			{
				ru = sRnd.randU32();
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

		UNITTEST_TEST(xrnd_RandSign)
		{
			rndgood sGoodRnd;
			xrand sRnd(&sGoodRnd);

			s32 rs = sRnd.randS32();
			CHECK_NOT_EQUAL(rs, sRnd.randS32());
			rs = sRnd.randS32(10);
			CHECK_NOT_EQUAL(rs, sRnd.randS32(10));
			rs = sRnd.randU32(31);
			CHECK_NOT_EQUAL(rs, sRnd.randS32(31));

			u32 zzz = 0, zzz2 = 0;
			for (s32 i = 0; i < 50; i++)
			{
				rs = sRnd.randU32();

				if (rs > 0)
					zzz = 1;
				else
					zzz2 = 1;

				if (rs % 3 != 0)
					CHECK_NOT_EQUAL(rs / 3 * 3, rs);
			}
			CHECK_EQUAL(zzz == 1 && zzz2 == 1, true);
		}

		UNITTEST_TEST(xrnd_RandF)
		{
			rndgood sGoodRnd;
			xrand sRnd(&sGoodRnd);

			f32 rfloat;
			rfloat = sRnd.randF32();
			CHECK_NOT_EQUAL(rfloat, sRnd.randF32());
			for (s32 i = 0; i < 50; i++)
			{
				rfloat = sRnd.randF32();
				CHECK_EQUAL(rfloat >= 0.0, true);
				CHECK_EQUAL(rfloat <= 1.0, true);
				if ((s32)rfloat % 3 != 0)
					CHECK_EQUAL(rfloat / 3 * 3, rfloat);
			}
		}
		UNITTEST_TEST(xrnd_RandFSign)
		{
			rndgood sGoodRnd;
			xrand sRnd(&sGoodRnd);

			f32 rfloat;
			u32 zzz = 0, zzz2 = 0;
			rfloat = sRnd.randF32S();
			CHECK_NOT_EQUAL(rfloat, sRnd.randF32S());
			for (s32 i = 0; i < 50; i++)
			{
				rfloat = sRnd.randF32S();
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
		UNITTEST_TEST(xrnd_randBool)
		{
			rndgood sGoodRnd;
			xrand sRnd(&sGoodRnd);

			u32 rbool = 0;
			u32 ru = 0, ru2 = 0;
			for (s32 i = 0; i < 50; i++)
			{
				rbool = sRnd.randBool();
				if (rbool == 1)
					ru = 1;
				else
					ru2 = 1;
				CHECK_EQUAL(rbool != 1 && rbool != 0, false);
			}
			CHECK_EQUAL(ru == 1 && ru2 == 1, true);
		}
	}
}
UNITTEST_SUITE_END
#include "xrandom/x_random.h"
#include "xrandom/x_random_quick.h"

#include "xunittest/xunittest.h"

using namespace xcore;

UNITTEST_SUITE_BEGIN(xrandom_quick)
{
    UNITTEST_FIXTURE(main)
    {
        UNITTEST_FIXTURE_SETUP() {}
        UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(xrnd_Init)
		{
			xrng_quick sQuickRnd;

			u32 ru;
			xrandom sRnd(&sQuickRnd);
			ru=sRnd.randU32();
			CHECK_NOT_EQUAL(ru,sRnd.randU32());
			sRnd.reset(132465);
			ru=sRnd.randU32();
			CHECK_NOT_EQUAL(ru,sRnd.randU32());
			sRnd.reset(-1325);
			ru=sRnd.randU32();
			CHECK_NOT_EQUAL(ru,sRnd.randU32());
			ru=sRnd.randU32();
			CHECK_NOT_EQUAL(ru,sRnd.randU32());
			sRnd.reset('a');
			ru=sRnd.randU32();
			CHECK_NOT_EQUAL(ru,sRnd.randU32());
		}
		UNITTEST_TEST(xrnd_Rand)
		{
			xrng_quick sQuickRnd;

			u32 ru;
			xrandom  sRnd(&sQuickRnd);
			ru=sRnd.randU32();
			CHECK_NOT_EQUAL(ru,sRnd.randU32());
			ru=sRnd.randU32(10);
			CHECK_NOT_EQUAL(ru,sRnd.randU32(10));
			ru=sRnd.randU32(31);
			CHECK_NOT_EQUAL(ru,sRnd.randU32(31));

			for(s32 i=0;i<50;i++)
			{
				ru=sRnd.randU32();
				CHECK_EQUAL((ru>=0),true);
				if(ru%3!=0) CHECK_NOT_EQUAL(ru/3*3,ru);
			}
		}
		UNITTEST_TEST(xrnd_RandSign)
		{
			xrng_quick sQuickRnd;

			s32 rs;
			xrandom  sRnd(&sQuickRnd);
			rs=sRnd.randS32();
			CHECK_NOT_EQUAL(rs,sRnd.randS32());
			rs=sRnd.randS32(10);
			CHECK_NOT_EQUAL(rs,sRnd.randS32(10));
			rs=sRnd.randU32(31);
			CHECK_NOT_EQUAL(rs,sRnd.randS32(31));
			u32 zzz=0,zzz2=0;
			for(s32 i=0;i<50;i++)
			{
				rs=sRnd.randU32();
				if(rs>0) zzz=1;
				else zzz2=1;
				if(rs%3!=0) CHECK_NOT_EQUAL(rs/3*3,rs);
			}
			CHECK_EQUAL(zzz==1&&zzz2==1,true);
		}
		UNITTEST_TEST(xrnd_RandF)
		{
			xrng_quick sQuickRnd;
			xrandom  sRnd(&sQuickRnd);

			f32 rfloat;
			rfloat=sRnd.randF32();
			CHECK_NOT_EQUAL(rfloat,sRnd.randF32());
			for(s32 i=0;i<50;i++)
			{
				rfloat=sRnd.randF32();
				CHECK_EQUAL(rfloat>=0.0,true);
				CHECK_EQUAL(rfloat<=1.0,true);
				if((s32)rfloat%3!=0) CHECK_EQUAL(rfloat/3*3,rfloat);
			}
		}
		UNITTEST_TEST(xrnd_RandFSign)
		{
			xrng_quick sQuickRnd;
			xrandom  sRnd(&sQuickRnd);

			f32 rfloat;
			u32 zzz=0,zzz2=0;
			rfloat=sRnd.randF32S();
			CHECK_NOT_EQUAL(rfloat,sRnd.randF32S());
			for(s32 i=0;i<50;i++)
			{
				rfloat=sRnd.randF32S();
				CHECK_EQUAL(rfloat>=-1.0,true);
				CHECK_EQUAL(rfloat<=1.0,true);
				if(rfloat>0.0) zzz=1;
				else zzz2=1;
				if((s32)rfloat%3!=0) CHECK_EQUAL(rfloat/3*3,rfloat);
			}
			CHECK_EQUAL(zzz==1&&zzz2==1,true);
		}
		UNITTEST_TEST(xrnd_randBool)
		{
			xrng_quick sQuickRnd;

			xrandom  sRnd(&sQuickRnd);

			u32 rbool=0;
			u32 ru=0,ru2=0;
			for(s32 i=0;i<50;i++)
			{
				rbool=sRnd.randBool();
				if(rbool==1) ru=1;
				else ru2=1;
				CHECK_EQUAL(rbool!=1&&rbool!=0,false);
			}
			CHECK_EQUAL(ru==1&&ru2==1,true);
		}
	}
	
}
UNITTEST_SUITE_END
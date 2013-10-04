#include "xrandom\x_random.h"
#include "xrandom\x_random_quick.h"

#include "xunittest\xunittest.h"

using namespace xcore;

UNITTEST_SUITE_BEGIN(xrandom_quick)
{
    UNITTEST_FIXTURE(main)
    {
        UNITTEST_FIXTURE_SETUP() {}
        UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(xrnd_Init)
		{
			xrnd_quick sQuickRnd;

			xrnd sRnd;
			u32 ru;
			sRnd.init(&sQuickRnd);
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
			sRnd.init(&sQuickRnd, 132465);
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
			sRnd.init(&sQuickRnd, -1325);
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
			//sRnd.Init(1.0f);//warning
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
			sRnd.init(&sQuickRnd, 'a');
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
		}
		UNITTEST_TEST(xrnd_Rand)
		{
			xrnd_quick sQuickRnd;

			xrnd  sRnd;
			u32 ru;
			sRnd.init(&sQuickRnd);
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
			ru=sRnd.rand(10);
			CHECK_NOT_EQUAL(ru,sRnd.rand(10));
			ru=sRnd.rand(31);
			CHECK_NOT_EQUAL(ru,sRnd.rand(31));

			for(s32 i=0;i<50;i++)
			{
				ru=sRnd.rand();
				CHECK_EQUAL((ru>=0),true);
				if(ru%3!=0) CHECK_NOT_EQUAL(ru/3*3,ru);
			}
		}
		UNITTEST_TEST(xrnd_RandSign)
		{
			xrnd_quick sQuickRnd;

			xrnd  sRnd;
			s32 rs;
			sRnd.init(&sQuickRnd);
			rs=sRnd.randSign();
			CHECK_NOT_EQUAL(rs,sRnd.randSign());
			rs=sRnd.randSign(10);
			CHECK_NOT_EQUAL(rs,sRnd.randSign(10));
			rs=sRnd.rand(31);
			CHECK_NOT_EQUAL(rs,sRnd.randSign(31));
			u32 zzz=0,zzz2=0;
			for(s32 i=0;i<50;i++)
			{
				rs=sRnd.rand();
				if(rs>0) zzz=1;
				else zzz2=1;
				if(rs%3!=0) CHECK_NOT_EQUAL(rs/3*3,rs);
			}
			CHECK_EQUAL(zzz==1&&zzz2==1,true);
		}
		UNITTEST_TEST(xrnd_RandF)
		{
			xrnd_quick sQuickRnd;
			xrnd  sRnd;
			sRnd.init(&sQuickRnd);

			f32 rfloat;
			rfloat=sRnd.randF();
			CHECK_NOT_EQUAL(rfloat,sRnd.randF());
			for(s32 i=0;i<50;i++)
			{
				rfloat=sRnd.randF();
				CHECK_EQUAL(rfloat>=0.0,true);
				CHECK_EQUAL(rfloat<=1.0,true);
				if((s32)rfloat%3!=0) CHECK_EQUAL(rfloat/3*3,rfloat);
			}
		}
		UNITTEST_TEST(xrnd_RandFSign)
		{
			xrnd_quick sQuickRnd;
			xrnd  sRnd;
			sRnd.init(&sQuickRnd);

			f32 rfloat;
			u32 zzz=0,zzz2=0;
			rfloat=sRnd.randFSign();
			CHECK_NOT_EQUAL(rfloat,sRnd.randFSign());
			for(s32 i=0;i<50;i++)
			{
				rfloat=sRnd.randFSign();
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
			xrnd_quick sQuickRnd;

			xrnd  sRnd;
			sRnd.init(&sQuickRnd);

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
#include "crandom/c_random.h"
#include "crandom/c_random_sitmo.h"

#include "cunittest/cunittest.h"

using namespace ncore;

UNITTEST_SUITE_BEGIN(random_sitmo)
{
    UNITTEST_FIXTURE(main)
    {
        UNITTEST_FIXTURE_SETUP() {}
        UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(Init)
		{
			rndsitmo sRnd;

			u32 ru;
			ru=random_u32(&sRnd);
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
			rndsitmo sRnd;

			u32 ru;
			ru=random_u32(&sRnd);
			CHECK_NOT_EQUAL(ru,random_u32(&sRnd));
			ru=random_u32(&sRnd, 10);
			CHECK_NOT_EQUAL(ru,random_u32(&sRnd, 10));
			ru=random_u32(&sRnd, 31);
			CHECK_NOT_EQUAL(ru,random_u32(&sRnd, 31));

			for(s32 i=0;i<50;i++)
			{
				ru=random_u32(&sRnd);
				CHECK_EQUAL((ru>=0),true);
				if(ru%3!=0) CHECK_NOT_EQUAL(ru/3*3,ru);
			}
		}
		UNITTEST_TEST(RandSign)
		{
			rndsitmo sRnd;

			s32 rs;
			rs=random_s32(&sRnd);
			CHECK_NOT_EQUAL(rs,random_s32(&sRnd));
			rs=random_s32(&sRnd, 10);
			CHECK_NOT_EQUAL(rs,random_s32(&sRnd, 10));
			rs=random_u32(&sRnd, 31);
			CHECK_NOT_EQUAL(rs,random_s32(&sRnd, 31));
			u32 zzz=0,zzz2=0;
			for(s32 i=0;i<50;i++)
			{
				rs=random_u32(&sRnd);
				if(rs>0) zzz=1;
				else zzz2=1;
				if(rs%3!=0) CHECK_NOT_EQUAL(rs/3*3,rs);
			}
			CHECK_EQUAL(zzz==1&&zzz2==1,true);
		}
		UNITTEST_TEST(RandF)
		{
			rndsitmo sRnd;

			f32 rfloat;
			rfloat=random_f32(&sRnd);
			CHECK_NOT_EQUAL(rfloat,random_f32(&sRnd));
			for(s32 i=0;i<50;i++)
			{
				rfloat=random_f32(&sRnd);
				CHECK_EQUAL(rfloat>=0.0,true);
				CHECK_EQUAL(rfloat<=1.0,true);
				if((s32)rfloat%3!=0) CHECK_EQUAL(rfloat/3*3,rfloat);
			}
		}
		UNITTEST_TEST(RandFSign)
		{
			rndsitmo sRnd;

			f32 rfloat;
			u32 zzz=0,zzz2=0;
			rfloat=random_f32S(&sRnd);
			CHECK_NOT_EQUAL(rfloat,random_f32S(&sRnd));
			for(s32 i=0;i<50;i++)
			{
				rfloat=random_f32S(&sRnd);
				CHECK_EQUAL(rfloat>=-1.0,true);
				CHECK_EQUAL(rfloat<=1.0,true);
				if(rfloat>0.0) zzz=1;
				else zzz2=1;
				if((s32)rfloat%3!=0) CHECK_EQUAL(rfloat/3*3,rfloat);
			}
			CHECK_EQUAL(zzz==1&&zzz2==1,true);
		}
		UNITTEST_TEST(randBool)
		{
			rndsitmo sRnd;

			u32 rbool=0;
			u32 ru=0,ru2=0;
			for(s32 i=0;i<50;i++)
			{
				rbool=random_bool(&sRnd);
				if(rbool==1) ru=1;
				else ru2=1;
				CHECK_EQUAL(rbool!=1&&rbool!=0,false);
			}
			CHECK_EQUAL(ru==1&&ru2==1,true);
		}
	}
	
}
UNITTEST_SUITE_END
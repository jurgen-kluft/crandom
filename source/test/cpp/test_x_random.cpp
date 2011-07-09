#include "xbase\x_types.h"
#include "xrandom\Random.h"

#include "xunittest\xunittest.h"

using namespace xcore;

UNITTEST_SUITE_BEGIN(xrandom)
{
    UNITTEST_FIXTURE(main)
    {
        UNITTEST_FIXTURE_SETUP() {}
        UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(xrnd_Init)
		{
			xrnd  sRnd;
			u32 ru;
			sRnd.init();
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
			sRnd.init(132465);
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
			sRnd.init(-1325);
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
			//sRnd.Init(1.0f);//warning
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
			sRnd.init('a');
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
		}
		UNITTEST_TEST(xrnd_Rand)
		{
			xrnd  sRnd;
			u32 ru;
			sRnd.init();
			ru=sRnd.rand();
			CHECK_NOT_EQUAL(ru,sRnd.rand());
			ru=sRnd.rand(10);
			CHECK_NOT_EQUAL(ru,sRnd.rand(10));
			ru=sRnd.rand(1112310);
			CHECK_NOT_EQUAL(ru,sRnd.rand(1112310));
			ru=sRnd.rand(-110);
			CHECK_NOT_EQUAL(ru,sRnd.rand(-110));
			for(s32 i=0;i<50;i++)
			{
				ru=sRnd.rand();
				CHECK_EQUAL((ru>=0),true);
				if(ru%3!=0) CHECK_NOT_EQUAL(ru/3*3,ru);
			}
		}
		UNITTEST_TEST(xrnd_RandSign)
		{
			xrnd  sRnd;
			s32 rs;
			sRnd.init();
			rs=sRnd.randSign();
			CHECK_NOT_EQUAL(rs,sRnd.randSign());
			rs=sRnd.randSign(10);
			CHECK_NOT_EQUAL(rs,sRnd.randSign(10));
			rs=sRnd.rand(1112310);
			CHECK_NOT_EQUAL(rs,sRnd.randSign(1112310));
			rs=sRnd.randSign(-110);
			CHECK_NOT_EQUAL(rs,sRnd.randSign(-110));
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
			xrnd  sRnd;
			f32 rfloat;
			sRnd.init();
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
			xrnd  sRnd;
			f32 rfloat;
			u32 zzz=0,zzz2=0;
			sRnd.init();
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
			xrnd  sRnd;
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
		UNITTEST_TEST(xrnd_operator_copy)
		{
			xrnd  sRnd;
			xrnd  sRndCopy;
			for(s32 i=0;i<50;i++)
			{
				sRnd.init(i);
				sRndCopy=sRnd;
				s32 rs=sRnd.rand();
				s32 rs2=sRndCopy.rand();
				CHECK_EQUAL(rs,rs2);
			}
		}
	}
	UNITTEST_FIXTURE(xqrnd)
	{
		UNITTEST_FIXTURE_SETUP() {}
		UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(xqrnd_Init)
		{
			xqrnd  sQRnd;
			u32 ru;
			sQRnd.init();
			ru=sQRnd.rand();
			CHECK_NOT_EQUAL(ru,sQRnd.rand());
			sQRnd.init(132465);
			ru=sQRnd.rand();
			CHECK_NOT_EQUAL(ru,sQRnd.rand());
			sQRnd.init(-1325);
			ru=sQRnd.rand();
			CHECK_NOT_EQUAL(ru,sQRnd.rand());
			//sQRnd.init(1.0f);//warning
			ru=sQRnd.rand();
			CHECK_NOT_EQUAL(ru,sQRnd.rand());
			sQRnd.init('a');
			ru=sQRnd.rand();
			CHECK_NOT_EQUAL(ru,sQRnd.rand());
		}
		UNITTEST_TEST(xqrnd_Rand)
		{
			xqrnd  sQRnd;
			u32 ru;
			sQRnd.init();
			ru=sQRnd.rand();
			CHECK_EQUAL(ru==0||ru==1,true);
			CHECK_NOT_EQUAL(sQRnd.rand(),sQRnd.rand());
			for(s32 i=0;i<50;i++)
			{
				sQRnd.init(1);
				ru=sQRnd.rand(1);
				CHECK_EQUAL(ru==0,true);
				sQRnd.init(-1);
				ru=sQRnd.rand(1);
				CHECK_EQUAL(ru==1,true);
			}//get the number of sign bit to be rand
			CHECK_NOT_EQUAL(sQRnd.rand(10),sQRnd.rand(10));
			ru=sQRnd.rand(1112310);
			CHECK_NOT_EQUAL(ru,sQRnd.rand(1112310));
			ru=sQRnd.rand(-110);
			CHECK_NOT_EQUAL(ru,sQRnd.rand(-110));
			for(s32 i=0;i<50;i++)
			{
				ru=sQRnd.rand();
				CHECK_EQUAL((ru>=0),true);
				if(ru%3!=0) CHECK_NOT_EQUAL(ru/3*3,ru);
			}
		}
		UNITTEST_TEST(xqrnd_RandSign)
		{
			xqrnd  sQRnd;
			s32 rs;
			sQRnd.init();
			rs=sQRnd.randSign();
			CHECK_NOT_EQUAL(rs,sQRnd.randSign());
			rs=sQRnd.randSign(10);
			CHECK_NOT_EQUAL(rs,sQRnd.randSign(10));
			rs=sQRnd.rand(1112310);
			CHECK_NOT_EQUAL(rs,sQRnd.randSign(1112310));
			rs=sQRnd.randSign(-110);
			CHECK_NOT_EQUAL(rs,sQRnd.randSign(-110));
			u32 zzz=0,zzz2=0;
			for(s32 i=0;i<50;i++)
			{
				rs=sQRnd.rand();
				if(rs>0) zzz=1;
				else zzz2=1;
				if(rs%3!=0) CHECK_NOT_EQUAL(rs/3*3,rs);
			}
			CHECK_EQUAL(zzz==1&&zzz2==1,true);
		}
		UNITTEST_TEST(xqrnd_RandF)
		{
			xqrnd  sQRnd;
			f32 rfloat;
			sQRnd.init();
			rfloat=sQRnd.randF();
			CHECK_NOT_EQUAL(rfloat,sQRnd.randF());
			for(s32 i=0;i<50;i++)
			{
				rfloat=sQRnd.randF();
				CHECK_EQUAL(rfloat>=0.0,true);
				CHECK_EQUAL(rfloat<=1.0,true);
				if((s32)rfloat%3!=0) CHECK_EQUAL(rfloat/3*3,rfloat);
			}
		}
		UNITTEST_TEST(xqrnd_RandFSign)
		{
			xqrnd  sQRnd;
			f32 rfloat;
			u32 zzz=0,zzz2=0;
			sQRnd.init();
			rfloat=sQRnd.randFSign();
			CHECK_NOT_EQUAL(rfloat,sQRnd.randFSign());
			for(s32 i=0;i<50;i++)
			{
				rfloat=sQRnd.randFSign();
				CHECK_EQUAL(rfloat>=-1.0,true);
				CHECK_EQUAL(rfloat<=1.0,true);
				if(rfloat>0.0) zzz=1;
				else zzz2=1;
				if((s32)rfloat%3!=0) CHECK_EQUAL(rfloat/3*3,rfloat);
			}
			CHECK_EQUAL(zzz==1&&zzz2==1,true);
		}
		UNITTEST_TEST(xqrnd_RandBool)
		{
			xqrnd  sQRnd;
			u32 rbool=0;
			u32 ru=0,ru2=0;
			for(s32 i=0;i<100;i++)
			{
				rbool=sQRnd.randBool();
				if (rbool==1) 
					ru=1;
				else
					ru2=1;

				CHECK_EQUAL(rbool!=1&&rbool!=0,false);
			}
			CHECK_EQUAL(ru==1&&ru2==1,true);
		}
		UNITTEST_TEST(xqrnd_operator_copy)
		{
			xqrnd  sQRnd;
			xqrnd  sQRndCopy;
			for(s32 i=0;i<50;i++)
			{
				sQRnd.init(i);
				sQRndCopy=sQRnd;
				s32 rs=sQRnd.rand();
				s32 rs2=sQRndCopy.rand();
				CHECK_EQUAL(rs,rs2);
			}
        }
	}
}
UNITTEST_SUITE_END
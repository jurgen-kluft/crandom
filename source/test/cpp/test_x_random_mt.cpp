#include "xbase\x_types.h"
#include "xrandom\x_random.h"
#include "xrandom\private\x_random_mersenne_twister.h"

#include "xunittest\xunittest.h"

using namespace xcore;

UNITTEST_SUITE_BEGIN(xrandom_mt)
{
	UNITTEST_FIXTURE(main)
	{
		UNITTEST_FIXTURE_SETUP() {}
		UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(seed1)
        {
			xrnd_mt sMtRnd;
			sMtRnd.seed();	
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			sMtRnd.seed(12345679);
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			sMtRnd.seed(-132);	
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			//sMtRnd.seed(123.5f);//	warning
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			sMtRnd.seed('x');	
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			sMtRnd.release();
		}
		UNITTEST_TEST(seed2)
        {
			xrnd_mt sMtRnd;
			u32 ru[3]={1,0, 999};
			sMtRnd.seed(ru,3);
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());

			ru[0] = 92394;
			sMtRnd.seed(ru,3);
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			

			ru[1] = 82348;
			sMtRnd.seed(ru,3);
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			
			ru[2] = 123775;
			sMtRnd.seed(ru,3);
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			sMtRnd.release();
		}
		UNITTEST_TEST(release)
        {

			// fix several buffer overflows here.. -- setting inLenght to random values far greater than the size of ru[]

			xrnd_mt sMtRnd;
			s32 rs,rs2,rs3=0;
			u32 ru[]={1,2,3};
			sMtRnd.release();
			sMtRnd.seed(123);
			rs=sMtRnd.rand();
			sMtRnd.release();
			sMtRnd.seed(123);
			rs2=sMtRnd.rand();
			CHECK_EQUAL(rs,rs2);
			sMtRnd.release();
			sMtRnd.seed(789);
			rs3=sMtRnd.rand();
			CHECK_NOT_EQUAL(rs,rs3);
			sMtRnd.release();
			sMtRnd.seed(ru,3);
			rs=sMtRnd.rand();
			sMtRnd.release();
			
			ru[0] = 55; // try actually changing the seed
			
			
			sMtRnd.seed(ru,3);
			rs2=sMtRnd.rand();
			CHECK_NOT_EQUAL(rs,rs2);
			sMtRnd.release();


			sMtRnd.seed(ru,3);
			//sMtRnd.seed(ru,132456);          //when inLength is too big ,there are debug wrong.
			rs=sMtRnd.rand();
			sMtRnd.release();
			
			ru[1] = 23489; // try again

			sMtRnd.seed(ru,3);
			rs2=sMtRnd.rand();
			CHECK_NOT_EQUAL(rs,rs2);          //when inLength big than 31,Realse() can't work right.			
			sMtRnd.release();
		}

		UNITTEST_TEST(randF)
        {
			xrnd_mt sMtRnd;
			u32 number[3]={1,2,3};
			f32 rf;
			sMtRnd.seed();
			rf=sMtRnd.randF();
			CHECK_NOT_EQUAL(rf,sMtRnd.randF());
			sMtRnd.seed(number,3);
			rf=sMtRnd.randF();
			CHECK_NOT_EQUAL(rf,sMtRnd.randF());			
			for(s32 i=0;i<50;i++)
			{
				rf=sMtRnd.randF();
				CHECK_EQUAL(rf>0.0,true);
				CHECK_EQUAL(rf<1.0,true);
				if((s32)rf%3!=0) CHECK_EQUAL(rf==((rf/3)*3),true);
			}
			sMtRnd.release();
		}
		UNITTEST_TEST(randFSign)
        {
			xrnd_mt sMtRnd;
			u32 number[3]={1,2,3};
			f32 rf;
			sMtRnd.seed();
			rf=sMtRnd.randFSign();
			CHECK_NOT_EQUAL(rf,sMtRnd.randFSign());
			sMtRnd.seed(number,3);
			rf=sMtRnd.randFSign();
			CHECK_NOT_EQUAL(rf,sMtRnd.randFSign());
			u32 zzz=0,zzz2=0;
			for(s32 i=0;i<50;i++)
			{
				rf=sMtRnd.randFSign();
				if(rf>0.0) zzz=1;
				else zzz2=1;
				CHECK_EQUAL(rf>-1.0,true);
				CHECK_EQUAL(rf<1.0,true);
				if((s32)rf%3!=0) CHECK_EQUAL(rf==((rf/3)*3),true);
			}
			CHECK_EQUAL(zzz==1&&zzz2==1,true);
			sMtRnd.release();
		}
		UNITTEST_TEST(randBool)
        {
			xrnd_mt sMtRnd;
			u32 number[3]={1,2,3};
			bool rbool;
			sMtRnd.seed();
			rbool=sMtRnd.randBool();
			CHECK_EQUAL(rbool==0||rbool==1,true);
			sMtRnd.seed(number,3);
			rbool=sMtRnd.randBool();
			CHECK_EQUAL(rbool==0||rbool==1,true);
			for(s32 i=0;i<50;i++)
			{
				rbool=sMtRnd.randBool();
				CHECK_EQUAL(rbool==0||rbool==1,true);
			}
			sMtRnd.release();
		}
	}
}
UNITTEST_SUITE_END
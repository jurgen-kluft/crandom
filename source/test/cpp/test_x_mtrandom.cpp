#include "xbase\x_types.h"
#include "xrandom\mtrandom.h"

#include "xunittest\xunittest.h"

using namespace xcore;

UNITTEST_SUITE_BEGIN(xmtrandom)
{
	UNITTEST_FIXTURE(xmtrandom)
	{
		UNITTEST_FIXTURE_SETUP() {}
		UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(xmtrandom_Seed1)
        {
			xmtrandom	sMtRnd;
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
		UNITTEST_TEST(xmtrandom_Seed2)
        {
			xmtrandom	sMtRnd;
			u32 ru[3]={1,0};
			sMtRnd.seed(ru,0);
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			//sMtRnd.seed(ru,123.0f);            //warning
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			sMtRnd.seed(ru,'a');
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			//sMtRnd.seed(ru,132465789);          //when inLength is too big,Seed() can not working.
			sMtRnd.seed(ru,-123456798);
			CHECK_NOT_EQUAL(sMtRnd.rand(),sMtRnd.rand());
			sMtRnd.release();
		}
		UNITTEST_TEST(xmtrandom_Release)
        {
			xmtrandom	sMtRnd;
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
			sMtRnd.seed(ru,31);
			rs=sMtRnd.rand();
			sMtRnd.release();
			sMtRnd.seed(ru,31);
			rs2=sMtRnd.rand();
			CHECK_NOT_EQUAL(rs,rs2);
			sMtRnd.release();
			sMtRnd.seed(ru,32);
			//sMtRnd.seed(ru,132456);          //when inLength is too big ,there are debug wrong.
			rs=sMtRnd.rand();
			sMtRnd.release();
			sMtRnd.seed(ru,32);
			rs2=sMtRnd.rand();
			CHECK_NOT_EQUAL(rs,rs2);          //when inLength big than 31,Realse() can't work right.			
			sMtRnd.release();
		}
		UNITTEST_TEST(xmtrandom_Rand)
		{
			xmtrandom	sMtRnd;
			u32 number[3]={1,2,3},ru;
			sMtRnd.seed();
			ru=sMtRnd.rand(33);
			CHECK_EQUAL(ru==1||ru==0,true);//when inBits is big than 33 ,Rand() can not work right.
			ru=sMtRnd.rand((s32)'x');
			CHECK_NOT_EQUAL(ru==1||ru==0,true);//when inBits is big than 32 ,Rand() can not work right.
			ru=sMtRnd.rand((s32)11.02f);
			CHECK_NOT_EQUAL(ru,sMtRnd.rand((s32)11.02f));
			ru=sMtRnd.rand(-123456);
			CHECK_NOT_EQUAL(ru,sMtRnd.rand(-123456));//when inBIt is small than 0,Rand() still working.
			sMtRnd.seed(number,10);
			ru=sMtRnd.rand(10);
			CHECK_NOT_EQUAL(ru,sMtRnd.rand(11));
			for(s32 i=0;i<50;i++)
			{
				CHECK_EQUAL((sMtRnd.rand(i)>=0),true);
			}
			sMtRnd.release();
		}
		UNITTEST_TEST(xmtrandom_RandSign)
		{
			xmtrandom	sMtRnd;
			u32 number[3]={1,2,3};
			s32 ru;
			sMtRnd.seed();
			ru=sMtRnd.randSign(50);
			CHECK_EQUAL(ru==1||ru==0,false);//when inBits is big than 31 ,RandSign() still working.
			ru=sMtRnd.randSign((s32)'x');
			CHECK_EQUAL(ru==1||ru==0,false);//when inBits is big than 31 ,RandSign() still working.
			ru=sMtRnd.randSign((s32)11.02f);
			CHECK_NOT_EQUAL(ru,sMtRnd.randSign((s32)11.02f));
			ru=sMtRnd.randSign(-123456);
			CHECK_NOT_EQUAL(ru,sMtRnd.randSign(-123456));//when inBIt is small than 0,RandSign() still working.
			sMtRnd.seed(number,10);
			ru=sMtRnd.randSign(10);			
			CHECK_NOT_EQUAL(ru,sMtRnd.randSign(10));
			u32 zzz=0,zzz2=0;
			for(s32 i=0;i<50;i++)
			{
				ru=sMtRnd.randSign(i);
				if(ru>0) zzz=1;
				else zzz2=1;
				if(ru%3!=0) CHECK_EQUAL(ru==(s32)((ru/3)*3),false);
			}
			CHECK_EQUAL(zzz==1&&zzz2==1,true);
			sMtRnd.release();
		}
		UNITTEST_TEST(xmtrandom_RandF)
        {
			xmtrandom	sMtRnd;
			u32 number[3]={1,2,3};
			f32 rf;
			sMtRnd.seed();
			rf=sMtRnd.randF();
			CHECK_NOT_EQUAL(rf,sMtRnd.randF());
			sMtRnd.seed(number,15);
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
		UNITTEST_TEST(xmtrandom_RandFSign)
        {
			xmtrandom	sMtRnd;
			u32 number[3]={1,2,3};
			f32 rf;
			sMtRnd.seed();
			rf=sMtRnd.randFSign();
			CHECK_NOT_EQUAL(rf,sMtRnd.randFSign());
			sMtRnd.seed(number,15);
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
		UNITTEST_TEST(xmtrandom_RandBool)
        {
			xmtrandom	sMtRnd;
			u32 number[3]={1,2,3};
			bool rbool;
			sMtRnd.seed();
			rbool=sMtRnd.randBool();
			CHECK_EQUAL(rbool==0||rbool==1,true);
			sMtRnd.seed(number,15);
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
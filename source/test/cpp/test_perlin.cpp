#include "crandom/c_perlin.h"

#include "cunittest/cunittest.h"

using namespace ncore;

UNITTEST_SUITE_BEGIN(perlin)
{
    UNITTEST_FIXTURE(noise)
    {
        UNITTEST_FIXTURE_SETUP() {}
        UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(noise1D)
		{
			noise snoise;
			f32 rfT=0.1f;
			f32 rf=snoise.noise1D(rfT);
			for(s32 i=1;i<50;i++)
			{
				f32 rf2=snoise.noise1D((f32)i+rfT);
				f32 rf3=snoise.noise1D((f32)i+rfT);
				CHECK_EQUAL(rf2,rf3);
				CHECK_NOT_EQUAL(rf2,0);
				CHECK_EQUAL((rf2>-1.0)&&(rf2<1.0),true);
				if((s32)rf2%2!=0)CHECK_EQUAL(rf2==((rf2/2)*2),true);
			}
		}
		UNITTEST_TEST(noise2D)
		{
			noise snoise;
			f32 rfX=0.7f,rfY=1.2f;
			f32 rf=snoise.noise2D(rfX,rfY);
			CHECK_EQUAL(rf,snoise.noise2D(rfX,rfY));
			CHECK_NOT_EQUAL(rf,snoise.noise2D(rfX,rfY+1.0f));
			CHECK_NOT_EQUAL(rf,snoise.noise2D(rfX+2.0f,rfY));
			CHECK_NOT_EQUAL(rf,snoise.noise2D(rfX+2.0f,rfY+1.0f));
			for(s32 i=1;i<50;i++)
			{
				f32 rf2=snoise.noise2D((f32)i+rfX,(f32)i+rfY);
				CHECK_EQUAL((rf2>-1.0)&&(rf2<1.0),true);
				if((s32)rf2%2!=0)CHECK_EQUAL(rf2==((rf2/2)*2),true);
			}
		}
		UNITTEST_TEST(noise3D)
		{
			noise snoise;
			f32 rfX=0.2f,rfY=0.4f,rfZ=0.8f;
			f32 rf=snoise.noise3D(rfX,rfY,rfZ);
			CHECK_EQUAL(rf,snoise.noise3D(rfX,rfY,rfZ));
			CHECK_NOT_EQUAL(rf,snoise.noise3D(rfX,rfY+1.0f,rfZ));
			CHECK_NOT_EQUAL(rf,snoise.noise3D(rfX+2.0f,rfY,rfZ));
			CHECK_NOT_EQUAL(rf,snoise.noise3D(rfX,rfY,rfZ+3.0f));
			CHECK_NOT_EQUAL(rf,snoise.noise3D(rfX+2.0f,rfY+1.0f,rfZ+3.0f));
			for(s32 i=1;i<50;i++)
			{
				f32 rf2=snoise.noise3D((f32)i+rfX,(f32)i+rfY,(f32)i+rfZ);
				CHECK_EQUAL((rf2>-1.0)&&(rf2<1.0),true);
				if((s32)rf2%2!=0)CHECK_EQUAL(rf2==((rf2/2)*2),true);
			}
		}
	}

	UNITTEST_FIXTURE(turbnoise)
	{
		UNITTEST_FIXTURE_SETUP() {}
		UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(evaluate)
		{
			tnoise sxTBn;
			f32 rf=0.3f,rf2=0.9f;
			CHECK_EQUAL(sxTBn.evaluate(132.0000f),sxTBn.evaluate(132));
			CHECK_EQUAL(sxTBn.evaluate(97),sxTBn.evaluate('a'));
			CHECK_EQUAL(sxTBn.evaluate(97),0);
			CHECK_EQUAL(sxTBn.evaluate(654131.0000f),0);
			CHECK_NOT_EQUAL(sxTBn.evaluate(2121.541f),0);
			CHECK_NOT_EQUAL(sxTBn.evaluate(1.1f),sxTBn.evaluate(-1.1f));
			for(s32 i=1;i<50;i++)
			{
				f32 rf3=sxTBn.evaluate((f32)i+rf);
				CHECK_NOT_EQUAL(rf3,sxTBn.evaluate((f32)i+rf2));
				if((s32)rf3%2!=2) CHECK_EQUAL(rf3==((rf3/2)*2),true);
				CHECK_NOT_EQUAL(rf3,0);
				CHECK_EQUAL((rf3<1)&&(rf3>-1),true);
			}
		}
		UNITTEST_TEST(getFrequency)
		{
			tnoise sxTBn;
			CHECK_EQUAL(sxTBn.getFrequency(),1.0f);
			sxTBn.evaluate(654131.0000f);
			CHECK_EQUAL(sxTBn.getFrequency(),1.0f);
		}
		UNITTEST_TEST(setFrequency)
		{
			tnoise sxTBn;
			sxTBn.setFrequency(1.2f);
			CHECK_EQUAL(sxTBn.getFrequency(),1.2f);
			//sxTBn.setFrequency(1.2);//warning
			sxTBn.setFrequency('a');
			CHECK_EQUAL(sxTBn.getFrequency(),'a');
			sxTBn.setFrequency(891219);
			CHECK_EQUAL(sxTBn.getFrequency(),891219);
			sxTBn.setFrequency(-132.0f);
			CHECK_EQUAL(sxTBn.getFrequency(),-132.0f);
		}
	}
	UNITTEST_FIXTURE(pnoise)
	{
		UNITTEST_FIXTURE_SETUP() {}
		UNITTEST_FIXTURE_TEARDOWN() {}

		UNITTEST_TEST(evaluate)
		{
			pnoise sxpn;
			f32 rf=0.3f,rf2=0.9f;
			CHECK_EQUAL(sxpn.evaluate(132.0000f),sxpn.evaluate(132));
			CHECK_EQUAL(sxpn.evaluate(97),sxpn.evaluate('a'));
			CHECK_EQUAL(sxpn.evaluate(97),0);
			CHECK_EQUAL(sxpn.evaluate(654131.0000f),0);
			CHECK_NOT_EQUAL(sxpn.evaluate(2121.541f),0);
			CHECK_NOT_EQUAL(sxpn.evaluate(1.1f),sxpn.evaluate(-1.1f));
			for(s32 i=1;i<50;i++)
			{
				f32 rf3=sxpn.evaluate((f32)i+rf);
				CHECK_NOT_EQUAL(rf3,sxpn.evaluate((f32)i+rf2));
				if((s32)rf3%2!=2) CHECK_EQUAL(rf3==((rf3/2)*2),true);
				CHECK_NOT_EQUAL(rf3,0);
				CHECK_EQUAL((rf3<1)&&(rf3>-1),true);
			}
		}
		UNITTEST_TEST(getPersistence)
		{
			pnoise sxpn;
			CHECK_EQUAL(sxpn.getPersistence(),1.0f);
			sxpn.evaluate(97);
			CHECK_EQUAL(sxpn.getPersistence(),1.0f);
		}
		UNITTEST_TEST(getOctaves)
		{
			pnoise sxpn;
			CHECK_EQUAL(sxpn.getOctaves(),1);
			sxpn.evaluate(97);
			CHECK_EQUAL(sxpn.getOctaves(),1);
		}
		UNITTEST_TEST(setPersistence)
		{
			pnoise sxpn;
			sxpn.setPersistence(1.2f);
			CHECK_EQUAL(sxpn.getPersistence(),1.2f);
			//sxpn.setPersistence(1.2);//warning
			sxpn.setPersistence('a');
			CHECK_EQUAL(sxpn.getPersistence(),'a');
			sxpn.setPersistence(891219);
			CHECK_EQUAL(sxpn.getPersistence(),891219);
			sxpn.setPersistence(-132.0f);
			CHECK_EQUAL(sxpn.getPersistence(),-132.0f);
		}
		UNITTEST_TEST(setOctaves)
		{
			pnoise sxpn;
			//sxpn.setOctaves(1.2f);//warning
			sxpn.setOctaves(12);
			CHECK_EQUAL(sxpn.getOctaves(),12);
			sxpn.setOctaves('a');
			CHECK_EQUAL(sxpn.getOctaves(),'a');
			sxpn.setOctaves(891219);
			CHECK_EQUAL(sxpn.getOctaves(),891219);
			sxpn.setOctaves(-132);
			CHECK_EQUAL(sxpn.getOctaves(),-132);
		}
	}
}
UNITTEST_SUITE_END

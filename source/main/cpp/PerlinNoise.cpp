// PerlinNoise.cpp - Core Perlin Noise implementation - 
#include "CSystem\CSystem.h"
#include "CRandom\Random.h"
#include "CRandom\PerlinNoise.h"
#include "CMath\Methods\Math.h"
BEGIN_CORE_NAMESPACE



//---------------------------------------------------------------------------------------------------------------------
//	Perlin noise
//---------------------------------------------------------------------------------------------------------------------


//
// Dimensions of Perlin noise
//
enum EPerlinDimensions
{
	B_BITS	= 8,
	B		= 0x100,
	BM		= 0xff,
	N		= 0x1000,
	NP		= 12,
	NM		= 0xfff
};



//
// Perlin noise lookup tables
//
DECLARE_STRUCT(PerlinNoiseTables)
struct PerlinNoiseTables
{
	///@name Construction/Destruction
						PerlinNoiseTables();

	int					mRefCount;												///< Reference count
	int					mP[B + B + 2];											///< Permutations
	float				mG1[B + B + 2];											///< Gradiants
	float				mG2[B + B + 2][2];
	float				mG3[B + B + 2][3];
};
pPerlinNoiseTables		sPT = NULL;



//
// Initialize perlin noise
//
PerlinNoiseTables::PerlinNoiseTables() :
	mRefCount(0)
{
	GoodRandom rnd;

	int i;
	for (i=0; i<B; i++) 
	{
		mP[i]		= i;
		mG1[i]		= rnd.RandFSign();
		mG2[i][0]	= rnd.RandF();
		mG2[i][1]	= rnd.RandF();
		mG3[i][0]	= rnd.RandF();
		mG3[i][1]	= rnd.RandF();
		mG3[i][2]	= rnd.RandF();
	}

	// Reorder permutations
	while (--i) 
		Basic::Swap(mP[i], mP[rnd.Rand(B_BITS)]);

	for (i=0; i<B+2; i++) 
	{
		mP[B + i]		= mP[i];
		mG1[B + i]		= mG1[i];
		mG2[B + i][0]	= mG2[i][0];
		mG2[B + i][1]	= mG2[i][1];
		mG3[B + i][0]	= mG3[i][0];
		mG3[B + i][1]	= mG3[i][1];
		mG3[B + i][2]	= mG3[i][2];
	}
}



/**
@brief	Construct perlin noise

		Construct the Perlin noise generator. If this is the first Perlin noise object
		coming into existence, the shared Perlin noise lookup tables are constructed.

**/
PerlinNoise::PerlinNoise()
{
	// Make sure we have perlin noise tables
	if (sPT == NULL)
		sPT = new PerlinNoiseTables;

	sPT->mRefCount++;
}



/**
@brief	Destruct perlin noise

		Destructs the Perlin noise generator. If this is the last Perlin noise object
		coming into existence, the shared Perlin noise lookup tables are destructed.
**/
PerlinNoise::~PerlinNoise()
{
	sPT->mRefCount--;
	if (sPT->mRefCount == 0)
	{
		delete sPT;
		sPT = NULL;
	}
}



// Helpers
#define SMOOTH_STEP(t) ( t * t * (3.0f - 2.0f * t) )
#define INLINE_LERP(t, a, b) ( a + t * (b - a) )
#define INLINE_SETUP(vec, b0, b1, r0, r1)\
	t = vec + (float)N;\
	b0 = ((int)t) & BM;\
	b1 = (b0+1) & BM;\
	r0 = t - (int)t;\
	r1 = r0 - 1.0f;



//
// Return noise on 1D line <inT>
//
float PerlinNoise::Noise1D(float inT)
{
	int bx0, bx1;
	float rx0, rx1, sx, t, u, v;

	INLINE_SETUP(inT, bx0,bx1, rx0,rx1);

	sx = SMOOTH_STEP(rx0);

	u = rx0 * sPT->mG1[ sPT->mP[ bx0 ] ];
	v = rx1 * sPT->mG1[ sPT->mP[ bx1 ] ];

	return INLINE_LERP(sx, u, v);
}	//Noise1D



//
// Return noise in 2-space at <inVector>
//
float PerlinNoise::Noise2D(float inX, float inY)
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, sx, sy, a, b, t, u, v;
	pcFloat q;
	int i, j;

	INLINE_SETUP(inX, bx0,bx1, rx0,rx1);
	INLINE_SETUP(inY, by0,by1, ry0,ry1);

	i = sPT->mP[ bx0 ];
	j = sPT->mP[ bx1 ];

	b00 = sPT->mP[ i + by0 ];
	b10 = sPT->mP[ j + by0 ];
	b01 = sPT->mP[ i + by1 ];
	b11 = sPT->mP[ j + by1 ];

	sx = SMOOTH_STEP(rx0);
	sy = SMOOTH_STEP(ry0);

	#define AT_2(rx,ry) ( rx * q[0] + ry * q[1] )

	q = &sPT->mG2[ b00 ][0]; u = AT_2(rx0,ry0);
	q = &sPT->mG2[ b10 ][0]; v = AT_2(rx1,ry0);
	a = INLINE_LERP(sx, u, v);

	q = &sPT->mG2[ b01 ][0]; u = AT_2(rx0,ry1);
	q = &sPT->mG2[ b11 ][0]; v = AT_2(rx1,ry1);
	b = INLINE_LERP(sx, u, v);

	#undef AT_2

	return INLINE_LERP(sy, a, b);
}



//
// Return noise in 3-space at <inVector>
//
float PerlinNoise::Noise3D(float inX, float inY, float inZ)
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, rz0, rz1, sy, sz, a, b, c, d, t, u, v;
	pcFloat q;
	int i, j;

	INLINE_SETUP(inX, bx0,bx1, rx0,rx1);
	INLINE_SETUP(inY, by0,by1, ry0,ry1);
	INLINE_SETUP(inZ, bz0,bz1, rz0,rz1);

	i = sPT->mP[ bx0 ];
	j = sPT->mP[ bx1 ];

	b00 = sPT->mP[ i + by0 ];
	b10 = sPT->mP[ j + by0 ];
	b01 = sPT->mP[ i + by1 ];
	b11 = sPT->mP[ j + by1 ];

	t  = SMOOTH_STEP(rx0);
	sy = SMOOTH_STEP(ry0);
	sz = SMOOTH_STEP(rz0);

	#define AT_3(rx, ry, rz) ( rx*q[0] + ry*q[1] + rz*q[3] )

	q = sPT->mG3[b00 + bz0]; u = AT_3(rx0, ry0, rz0);
	q = sPT->mG3[b10 + bz0]; v = AT_3(rx1, ry0, rz0);
	a = INLINE_LERP(t, u, v);

	q = sPT->mG3[b01 + bz0]; u = AT_3(rx0, ry1, rz0);
	q = sPT->mG3[b11 + bz0]; v = AT_3(rx1, ry1, rz0);
	b = INLINE_LERP(t, u, v);

	c = INLINE_LERP(sy, a, b);

	q = sPT->mG3[b00 + bz1]; u = AT_3(rx0, ry0, rz1);
	q = sPT->mG3[b10 + bz1]; v = AT_3(rx1, ry0, rz1);
	a = INLINE_LERP(t, u, v);

	q = sPT->mG3[b01 + bz1]; u = AT_3(rx0, ry1, rz1);
	q = sPT->mG3[b11 + bz1]; v = AT_3(rx1, ry1, rz1);
	b = INLINE_LERP(t, u, v);

	d = INLINE_LERP(sy, a, b);
	
	#undef AT_3

	return INLINE_LERP(sz, c, d);
}
#undef SMOOTH_STEP
#undef INLINE_LERP
#undef INLINE_SETUP


//---------------------------------------------------------------------------------------------------------------------
//	Turbulence
//---------------------------------------------------------------------------------------------------------------------



//
// Evaluate turbulence at <inPos>
//
float TurbulenceNoise::Evaluate(float inPos)
{
	float value;
	float freq=mFrequency;
	float totamp = 0.0f;
	
	for ( value=0.0f; freq>=1.0f; freq /= 2.0f) 
	{
		value+=Math<float>::FAbs(mNoise.Noise1D(freq*inPos)/freq);
		totamp+=1.0f/freq;
	}
	value*=1.0f/totamp;
	return value;
}



//---------------------------------------------------------------------------------------------------------------------
//	Fractional Brownian Motion Noise
//---------------------------------------------------------------------------------------------------------------------



//
// Evaluate Fractional Brownian Motion at <inPos>
//
float ProceduralFbmNoise::Evaluate(float inPos)
{
	float value		= 0.0f;
	float frequency = 1.0f;
	float totamp	= 0.0f;

	for ( int i=0; i<mOctaves; i++ )
	{
		float exponent = Math<float>::Pow(frequency, -mH);
		value += mNoise.Noise1D( inPos ) * exponent;
		totamp+=exponent;
		inPos *= mLacunarity;
		frequency *= mLacunarity;
	}
	value*=1.0f/totamp;
	return value;
}



//---------------------------------------------------------------------------------------------------------------------
//	PersistenceNoise
//---------------------------------------------------------------------------------------------------------------------



//
// Evaluate harmonic noise
//
float PersistenceNoise::Evaluate(float inPos)
{
	float value		= 0.0f;
	float amplitude = 1.0f;
	float totamp	= 0.0f;

	for (int i=0; i<mOctaves; i++)
	{
		float frequency = (float)(1<<i);
	    value += mNoise.Noise1D(inPos * frequency) * amplitude;
		totamp+=amplitude;
		amplitude*=mPersistence;
	}
	value*=1.0f/totamp;
	return value;
}




END_CORE_NAMESPACE

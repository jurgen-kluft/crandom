// PerlinNoise.h - Core Perlin noise - 
#ifndef __CORE_PERLIN_H__
#define __CORE_PERLIN_H__
#include "CCore\CCore.h"
#ifdef USE_PRAGMA_ONCE
	#pragma once
#endif

BEGIN_CORE_NAMESPACE


/**
@group		CRandom
@brief		Perlin noise
**/
class PerlinNoise
{
public:
	///@name Construction/Destruction
						PerlinNoise();
						~PerlinNoise();

	///@name Noise
	float				Noise1D(float inT);										///< Return noise on 1D line <inT>
	float				Noise2D(float inX, float inY);							///< Return noise in 2-space at <inVector>
	float				Noise3D(float inX, float inY, float inZ);				///< Return noise in 3-space at <inVector>
};



/**
@group		CRandom
@brief		Turbulence using Perlin noise
			Ken Perlin's turbulence function using Perlin noise
**/
class TurbulenceNoise
{
public:
	///@name Construction/Destruction
	inline				TurbulenceNoise()										: mFrequency(1.0f) { }

	///@name Turbulence
	float				Evaluate(float inPos);									///< Evaluate turbulence at <inPos>

	///@name Properties
	inline float		GetFrequency() const									{ return mFrequency; } ///< Get the frequency of the turbulence
	inline void			SetFrequency(float inFrequency)							{ mFrequency = inFrequency; } ///< Set the frequency of the turbulence

private:
	float				mFrequency;
	PerlinNoise			mNoise;
};



/**
@group		CRandom
@brief		Fractional Brownian Motion using Perlin Noise
			Fractional Brownian Motion (aka fBm by F. Kenton Musgrave) using Perlin Noise
**/
class ProceduralFbmNoise
{
public:
	///@name Construction/Destruction
						ProceduralFbmNoise()									: mH(1.0f), mLacunarity(2.0f), mOctaves(1) { }

	///@name Brownian motion	
	float				Evaluate(float inPos);									///< Evaluate Fractional Brownian Motion at <inPos>

	///@name Properties
	inline float		GetH() const											{ return mH; }
	inline float		GetLacunarity() const									{ return mLacunarity; }
	inline int			GetOctaves() const										{ return mOctaves; }
	inline void			SetH(float inH)											{ mH = inH; }
	inline void			SetLacunarity(float inLacunarity)						{ mLacunarity = inLacunarity; }
	inline void			SetOctaves(int inOctaves)								{ mOctaves = inOctaves; }

private:
	float				mH;														///< Fractal increment parameter
    float				mLacunarity;											///< Gap between successive frequencies
    int					mOctaves;												///< Number of frequencies in the fBm
	PerlinNoise			mNoise;
};



/**
@group		CRandom
@brief		Persistence Noise
			Harmonic noise as used by http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
			Looks a lot like the other two...
**/
class PersistenceNoise
{
public:
	///@name Construction/Destruction
						PersistenceNoise()										: mPersistence(1.0f), mOctaves(1) { }

	///@name Persistence noise
	float				Evaluate(float inPos);									///< Evaluate harmonic noise

	///@name Properties
	inline float		GetPersistence() const									{ return mPersistence; }
	inline int			GetOctaves() const										{ return mOctaves; }
	inline void			SetPersistence(float inPersistence)						{ mPersistence = inPersistence; }
	inline void			SetOctaves(int inOctaves)								{ mOctaves = inOctaves; }

private:
	float				mPersistence;
    int					mOctaves;						
	PerlinNoise			mNoise;
};


END_CORE_NAMESPACE
#endif	///< __CORE_PERLIN_H__
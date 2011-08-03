// xnoise.h - Core Perlin noise - 
#ifndef __XRANDOM_PERLIN_H__
#define __XRANDOM_PERLIN_H__
#include "xbase\x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase\x_types.h"

namespace xcore
{
	/**
	@group		xrandom
	@brief		Perlin noise
	**/
	class xnoise
	{
	public:
		///@name Construction/Destruction
							xnoise();
							~xnoise();

		///@name Noise
		f32					noise1D(f32 inT);										///< Return noise on 1D line <inT>
		f32					noise2D(f32 inX, f32 inY);								///< Return noise in 2-space at <inVector>
		f32					noise3D(f32 inX, f32 inY, f32 inZ);						///< Return noise in 3-space at <inVector>
	};



	/**
	@group		xrandom
	@brief		Turbulence using Perlin noise
				Ken Perlin's turbulence function using Perlin noise
	**/
	class xturbnoise
	{
	public:
		///@name Construction/Destruction
		inline				xturbnoise()											: mFrequency(1.0f) { }

		///@name Turbulence
		f32					evaluate(f32 inPos);									///< Evaluate turbulence at <inPos>

		///@name Properties
		inline f32			getFrequency() const									{ return mFrequency; } ///< Get the frequency of the turbulence
		inline void			setFrequency(f32 inFrequency)							{ mFrequency = inFrequency; } ///< Set the frequency of the turbulence

	private:
		f32					mFrequency;
		xnoise				mNoise;
	};

	/**
	@group		xrandom
	@brief		Persistence Noise
				Harmonic noise as used by http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
				Looks a lot like the other two...
	**/
	class xpnoise
	{
	public:
		///@name Construction/Destruction
							xpnoise()												: mPersistence(1.0f), mOctaves(1) { }

		///@name Persistence noise
		f32					evaluate(f32 inPos);									///< Evaluate harmonic noise

		///@name Properties
		inline f32			getPersistence() const									{ return mPersistence; }
		inline s32			getOctaves() const										{ return mOctaves; }
		inline void			setPersistence(f32 inPersistence)						{ mPersistence = inPersistence; }
		inline void			setOctaves(s32 inOctaves)								{ mOctaves = inOctaves; }

	private:
		f32					mPersistence;
		s32					mOctaves;						
		xnoise				mNoise;
	};


}
#endif	///< __XRANDOM_PERLIN_H__

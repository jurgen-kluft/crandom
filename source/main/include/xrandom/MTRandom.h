// MTRandom.h - Core Mersenne Twister random number generator - 
#ifndef __CORE_MT_RANDOM_H__
#define __CORE_MT_RANDOM_H__
#include "CCore\CCore.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

// Includes
#include "CSystem\Types.h"
#include "CSystem\Defines.h"
#include "CGenerics\vector.h"
BEGIN_CORE_NAMESPACE



/**
@group		CRandom
@desc		Mersenne Twister random number generator
@note		The period is 2^19937-1, and 623-dimensional equi-distribution property is assured.
			Note that this means, by default, that there is negligible serial correlation between 
			successive values in the output sequence. 
**/
class MTRandom
{
	enum EPeriodParameters
	{
		N			= 624,
		M			= 397,
		MATRIX_A	= 0x9908b0df,												// Constant vector a
		UMASK		= 0x80000000,												// Most significant w-r bits
		LMASK		= 0x7fffffff												// Least significant r bits
	};

	static inline uint32 MixBits(uint32 u, uint32 v)							{ return (u & UMASK) | (v & LMASK); }
	static inline uint32 Twist(uint32 u, uint32 v)								{ return (MixBits(u,v) >> 1) ^ ((v&1) ? MATRIX_A : 0); }

	static inline float	ToFloat(uint inUInt)									{ uint fakeFloat = (inUInt>>(32-23)) | 0x3f800000; return ((*(float *)&fakeFloat)-1.0f); }

public:
	static void			Seed(uint32 inSeed = 19650218);
	static void			Seed(pcUInt32 inSeed, int inLength);

	static void			Release();												///< Reset to initial state

	static uint			Rand(int inBits = 32);
	static int			RandSign(int inBits = 31);
	static float		RandF()													{ return (ToFloat(Rand())); }		///< Return float in range [0.0 ... 1.0]
	static float		RandFSign()												{ return ((RandF()-0.5f)*2.0f); }	///< Return float in range [-1.0 ... 1.0]
	static bool			RandBool()												{ return (Rand(1)==0); }			///< Return true or false

private:
	static uint32		Twiddle(uint32, uint32);
	static void			GenerateNewState();


	static uint32*		sState;
	static uint32*		sNextState;
	static int			sLeft;
	static bool			sInitialized;
};


END_CORE_NAMESPACE
#endif	///< __CORE_MT_RANDOM_H__
// Random.h - Core Random number generators - 
#ifndef __CORE_RANDOM_H__
#define __CORE_RANDOM_H__
#include "CCore\CCore.h"
#ifdef USE_PRAGMA_ONCE
	#pragma once
#endif

#include "CSystem\Types.h"
BEGIN_CORE_NAMESPACE


//---------------------------------------------------------------------------------------------------------------------
//	Random number generators (one very good, one very fast)
//---------------------------------------------------------------------------------------------------------------------

/**
@group		CRandom
@brief		Good random value generator
**/
class GoodRandom
{
private:
	///@name Implementation
	inline float		uint2float(uint inUInt)									{ uint fake_float = (inUInt>>(32-23)) | 0x3f800000; return ((*(float *)&fake_float)-1.0f); }
	uint8				mArray[256+sizeof(uint)];								///< Random generator data
	int					mIndex;													///< Random index

public:
	///@name Construction/Destruction
						GoodRandom(int inSeed = 0)								{ Init(inSeed); }
						GoodRandom(const GoodRandom& inOther)					{ *this = inOther; }

	///@name Random functions
	void				Init(int inSeed = 0);									///< Init with random seed
	inline uint			Rand(int inBits = 32)									{ uint r1 = (uint8)(mIndex+4*53); uint r2 = (uint8)(mIndex+4); uint r  = *((uint*)(mArray+r1)); *((uint*)(mArray+r2)) ^= r; mIndex = r2; return (r >> (32-inBits)); }
	inline int			RandSign(int inBits = 31)								{ return (Rand(inBits+1)-(1 << inBits)); }	
	inline float		RandF()													{ return (uint2float(Rand())); } ///< Return float in range [0.0 ... 1.0]
	inline float		RandFSign()												{ return ((RandF()-0.5f)*2.0f); } ///< Return float in range [-1.0 ... 1.0]
	inline bool			RandBool()												{ return (Rand(1)==0); } ///< Return true or false

	///@name Operators
	GoodRandom&			operator=(const GoodRandom& inRHS);						///< Copy from another random number generator
};



/**
@group		CRandom
@brief		Quick and dirty random generator
**/
class QuickRandom
{
private:
	///@name Implementation
	uint				mSeed;													///< Random seed
	inline float		uint2float(uint inUInt)									{ uint fake_float = (inUInt>>(32-23)) | 0x3f800000; return ((*(float *)&fake_float)-1.0f); }
	inline void			Gen32()													{ mSeed = mSeed*1664525 + 1013904223; }	///< Do quick update

public:
	///@name Construction/Destruction
						QuickRandom(int inSeed = 0)								: mSeed(inSeed) { }
						QuickRandom(const QuickRandom& inOther)					{ *this = inOther; }

	///@name Random functions
	inline void			Init(int inSeed = 0)									{ mSeed = inSeed; }
	inline uint			Rand(int inBits = 32)									{ uint rVal = mSeed>>(32-inBits); Gen32(); return rVal; }
	inline int			RandSign(int inBits = 31)								{ return (Rand(inBits+1) - (1 << inBits)); }
	inline float		RandF()													{ float r = uint2float(mSeed); Gen32(); return r; }	///< Return float in range [0.0 ... 1.0]
	inline float		RandFSign()												{ return ((RandF()-0.5f)*2.0f); } ///< Return float in range [-1.0 ... 1.0]
	inline bool			RandBool()												{ return (Rand(1)==0); } ///< Return true or false

	///@name Operators
	inline QuickRandom& operator=(const QuickRandom& inRHS)						{ mSeed = inRHS.mSeed; return *this; }
};



//
// Some global random functions using QuickRandom
//
class Random
{
public:
	static f_inline int		Integer()											{ return (int)sGenerator.Rand(16); }
	static f_inline int		Integer(int inBitSize)								{ return (int)sGenerator.Rand(inBitSize); }
	static f_inline float	Float()												{ return sGenerator.RandF(); }
	static f_inline void	SetSeed(uint inSeed)								{ sGenerator.Init(inSeed); }

protected:
	static QuickRandom		sGenerator;
};


END_CORE_NAMESPACE
#endif

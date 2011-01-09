// Random.h - Core Random number generators - 
#ifndef __XRANDOM_RANDOM_H__
#define __XRANDOM_RANDOM_H__
#include "xbase\x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase\x_types.h"

namespace xcore
{
	//---------------------------------------------------------------------------------------------------------------------
	//	Random number generators (one very good, one very fast)
	//---------------------------------------------------------------------------------------------------------------------

	/**
	@group		xrandom
	@brief		Good random value generator
	**/
	class xrnd
	{
	private:
		///@name Implementation
		inline f32			uint2float(u32 inUInt)									{ u32 fake_float = (inUInt>>(32-23)) | 0x3f800000; return ((*(f32 *)&fake_float)-1.0f); }
		u8					mArray[256+sizeof(u32)];								///< Random generator data
		s32					mIndex;													///< Random index

	public:
		///@name Construction/Destruction
							xrnd(s32 inSeed = 0)									{ Init(inSeed); }
							xrnd(const xrnd& inOther)								{ *this = inOther; }

		///@name Random functions
		void				Init(s32 inSeed = 0);									///< Init with random seed
		inline u32			Rand(s32 inBits = 32)									{ u32 r1 = (u8)(mIndex+4*53); u32 r2 = (u8)(mIndex+4); u32 r  = *((u32*)(mArray+r1)); *((u32*)(mArray+r2)) ^= r; mIndex = r2; return (r >> (32-inBits)); }
		inline s32			RandSign(s32 inBits = 31)								{ return (Rand(inBits+1)-(1 << inBits)); }	
		inline f32			RandF()													{ return (uint2float(Rand())); } ///< Return f32 in range [0.0 ... 1.0]
		inline f32			RandFSign()												{ return ((RandF()-0.5f)*2.0f); } ///< Return f32 in range [-1.0 ... 1.0]
		inline xbool		RandBool()												{ return (Rand(1)==0); } ///< Return true or false

		///@name Operators
		xrnd&				operator=(const xrnd& inRHS);							///< Copy from another random number generator
	};



	/**
	@group		xrandom
	@brief		Quick and dirty random generator
	**/
	class xqrnd
	{
	private:
		///@name Implementation
		u32					mSeed;													///< Random seed
		inline f32			uint2float(u32 inUInt)									{ u32 fake_float = (inUInt>>(32-23)) | 0x3f800000; return ((*(f32 *)&fake_float)-1.0f); }
		inline void			Gen32()													{ mSeed = mSeed*1664525 + 1013904223; }	///< Do quick update

	public:
		///@name Construction/Destruction
							xqrnd(s32 inSeed = 0)									: mSeed(inSeed) { }
							xqrnd(const xqrnd& inOther)								{ *this = inOther; }

		///@name Random functions
		inline void			Init(s32 inSeed = 0)									{ mSeed = inSeed; }
		inline u32			Rand(s32 inBits = 32)									{ u32 rVal = mSeed>>(32-inBits); Gen32(); return rVal; }
		inline s32			RandSign(s32 inBits = 31)								{ return (Rand(inBits+1) - (1 << inBits)); }
		inline f32			RandF()													{ f32 r = uint2float(mSeed); Gen32(); return r; }	///< Return f32 in range [0.0 ... 1.0]
		inline f32			RandFSign()												{ return ((RandF()-0.5f)*2.0f); } ///< Return f32 in range [-1.0 ... 1.0]
		inline xbool		RandBool()												{ return (Rand(1)==0); } ///< Return true or false

		///@name Operators
		inline xqrnd&		operator=(const xqrnd& inRHS)							{ mSeed = inRHS.mSeed; return *this; }

	public:
		static f_inline s32		Integer()											{ return (s32)sGenerator.Rand(16); }
		static f_inline s32		Integer(s32 inBitSize)								{ return (s32)sGenerator.Rand(inBitSize); }
		static f_inline f32		Float()												{ return sGenerator.RandF(); }
		static f_inline void	SetSeed(u32 inSeed)									{ sGenerator.Init(inSeed); }

	protected:
		static xqrnd		sGenerator;
	};

}
#endif

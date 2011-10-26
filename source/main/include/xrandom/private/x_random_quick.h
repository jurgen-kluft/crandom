// Random.h - Core Random number generators - 
#ifndef __XRANDOM_RANDOM_QUICK_H__
#define __XRANDOM_RANDOM_QUICK_H__
#include "xbase\x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase\x_types.h"
#include "xbase\x_allocator.h"

#include "xrandom\x_irandom.h"

namespace xcore
{
	// Forward declares
	class x_iallocator;

	/**
	@group		xrandom
	@brief		Quick and dirty random generator
	**/
	class xrnd_quick : public xirnd
	{
	private:
		///@name Implementation
		u32					mSeed;													///< Random seed
		x_iallocator*		mAllocator;

		inline f32			uint2float(u32 inUInt)									{ u32 fake_float = (inUInt>>(32-23)) | 0x3f800000; return ((*(f32 *)&fake_float)-1.0f); }
		inline void			gen32()													{ mSeed = mSeed*1664525 + 1013904223; }	///< Do quick update

	public:
		///@name Construction/Destruction
							xrnd_quick(x_iallocator* alloc=NULL);

		///@name Random functions
		virtual void		init(s32 inSeed = 0)									{ mSeed = inSeed; }
		virtual void		release();
		virtual u32			rand(u32 inBits = 32)									{ ASSERT(inBits <= 32); u32 rVal = mSeed>>(32-(inBits)); gen32(); return rVal; }
		virtual s32			randSign(u32 inBits = 31)								{ ASSERT(inBits <= 31); return (rand(inBits+1) - (1 << inBits)); }
		virtual f32			randF()													{ f32 r = uint2float(mSeed); gen32(); return r; }	///< Return f32 in range [0.0 ... 1.0]
		virtual f32			randFSign()												{ return ((randF()-0.5f)*2.0f); } ///< Return f32 in range [-1.0 ... 1.0]
		virtual xbool		randBool()												{ return (rand(1)==0); } ///< Return true or false

		XCORE_CLASS_PLACEMENT_NEW_DELETE
	};

}
#endif

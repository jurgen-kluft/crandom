/**
* @file x_random_good.h
*
* Core Random number generators
*/

#ifndef __XRANDOM_RANDOM_GOOD_H__
#define __XRANDOM_RANDOM_GOOD_H__
#include "xbase\x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase\x_types.h"
#include "xbase\x_allocator.h"

#include "xrandom\x_irandom.h"
#include "xbase\x_endian.h"

namespace xcore
{
	// Forward declares
	class x_iallocator;

	/**
	 *	Random number generators (one very good, one very fast)
	 */

	/**
	 * @group		xrandom
	 * @brief		Good random value generator
	 */
	class xrnd_good : public xirnd
	{
	private:
		///@name Implementation
		inline f32			uint2float(u32 inUInt)									{ u32 fake_float = (inUInt>>(32-23)) | 0x3f800000; return ((*(f32 *)&fake_float)-1.0f); }
		u8					mArray[256+sizeof(u32)];								///< Random generator data
		s32					mIndex;													///< Random index
		x_iallocator*		mAllocator;

	public:
		///@name Construction/Destruction
							xrnd_good(x_iallocator* alloc=NULL);

		///@name Random functions
		virtual void		init(s32 inSeed = 0);									///< Init with random seed
		virtual void		release();
		
		virtual u32			rand(u32 inBits = 32)									
		{ 
			ASSERT(inBits <= 32);

			u32 r1 = (u8)(mIndex+4*53); 
			u32 r2 = (u8)(mIndex+4); 
			u32 r  = *((u32*)(mArray+r1)); 
//#ifdef X_BIG_ENDIAN
//			r = xcore::x_endian_swap::swap(r);
//#endif

			*((u32*)(mArray+r2)) ^= r; 

//#ifdef X_BIG_ENDIAN
//			*((u32*)(mArray+r2)) = xcore::x_endian_swap::swap( *((u32*)(mArray+r2)) );
//#endif
			
			mIndex = r2; 
			return (r >> (32-inBits)); 
		}

		virtual s32			randSign(u32 inBits = 31)								{ ASSERT(inBits <= 31); return (rand(inBits+1)-(1 << inBits)); }	
		virtual f32			randF()													{ return (uint2float(rand())); } ///< Return f32 in range [0.0 ... 1.0]
		virtual f32			randFSign()												{ return ((randF()-0.5f)*2.0f); } ///< Return f32 in range [-1.0 ... 1.0]
		virtual xbool		randBool()												{ return (rand(1)==0); } ///< Return true or false

		XCORE_CLASS_PLACEMENT_NEW_DELETE
	};


}
#endif

/**
* @file x_random_quick.cpp
*
* Core Random number generators, quick
*/

#include "xbase\x_target.h"
#include "xbase\x_memory_std.h"
#include "xbase\x_allocator.h"

#include "xrandom\x_random_quick.h"

namespace xcore
{

	/**
	 *	Quick random
	 */
	static inline f32	uint2float(u32 inUInt)
	{
		u32 fake_float = (inUInt>>(32-23)) | 0x3f800000; 
		return ((*(f32 *)&fake_float)-1.0f); 
	}

	static inline void	gen32(u32& seed)
	{
		seed = seed*1664525 + 1013904223; 
	}


	xrnd_quick::xrnd_quick(x_iallocator* alloc) 
		: mSeed(0xdeadbeef)
		, mAllocator(alloc)
	{
	}

	void		xrnd_quick::init(s32 inSeed)
	{
		mSeed = inSeed; 
	}

	u32			xrnd_quick::rand(u32 inBits)
	{
		ASSERT(inBits <= 32);
		u32 rVal = mSeed>>(32-(inBits)); 
		gen32(mSeed); 
		return rVal; 
	}

	s32			xrnd_quick::randSign(u32 inBits)
	{ 
		ASSERT(inBits <= 31); 
		return (rand(inBits+1) - (1 << inBits)); 
	}

	f32			xrnd_quick::randF()
	{ 
		f32 r = uint2float(mSeed); 
		gen32(mSeed);
		return r; 
	}

	f32			xrnd_quick::randFSign()
	{
		return ((randF()-0.5f)*2.0f);
	}

	bool		xrnd_quick::randBool()
	{
		return (rand(1)==0);
	} 

	void		xrnd_quick::release()
	{
		if (mAllocator!=NULL) 
		{
			this->~xrnd_quick(); 
			mAllocator->deallocate(this); 
			mAllocator = NULL;
		}
	}

}

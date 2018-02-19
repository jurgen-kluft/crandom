/**
* @file x_random_quick.cpp
*
* Core Random number generators, quick
*/

#include "xbase/x_target.h"
#include "xbase/x_memory_std.h"
#include "xbase/x_allocator.h"

#include "xrandom/x_random_quick.h"

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


	xrng_quick::xrng_quick(x_iallocator* alloc) 
		: mSeed(0xdeadbeef)
		, mAllocator(alloc)
	{
	}

	void		xrng_quick::reset(s32 inSeed)
	{
		mSeed = inSeed; 
	}

	u32			xrng_quick::randU32(u32 inBits)
	{
		ASSERT(inBits <= 32);
		u32 rVal = mSeed>>(32-(inBits)); 
		gen32(mSeed); 
		return rVal; 
	}

	s32			xrng_quick::randS32(u32 inBits)
	{ 
		ASSERT(inBits <= 31); 
		return (randU32(inBits+1) - (1 << inBits)); 
	}

	f32			xrng_quick::randF32()
	{ 
		f32 r = uint2float(mSeed); 
		gen32(mSeed);
		return r; 
	}

	f32			xrng_quick::randF32S()
	{
		return ((randF32()-0.5f)*2.0f);
	}

	bool		xrng_quick::randBool()
	{
		return (randU32(1)==0);
	} 

	void		xrng_quick::randBuffer(xbuffer& buffer)
	{
		u32 rnd;
		for (u32 i=0; i<buffer.size(); ++i)
		{
			if ((i&3) == 0)
				rnd = randU32();

			buffer[i] = (rnd&0xff);
			rnd = rnd >> 8;
		}
	}

	void		xrng_quick::release()
	{
		if (mAllocator!=NULL) 
		{
			this->~xrng_quick(); 
			mAllocator->deallocate(this); 
			mAllocator = NULL;
		}
	}

}

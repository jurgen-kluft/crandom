#include "xbase/x_target.h"
#include "xbase/x_allocator.h"

#include "xrandom/x_random_quick.h"

namespace xcore
{
	static inline u32	gen32(u32& seed)
	{
		u32 current = seed;
		seed = seed*1664525 + 1013904223; 
		return current;
	}

	xrndquick::xrndquick(xalloc* alloc) 
		: mSeed(0xdeadbeef)
		, mAllocator(alloc)
	{
	}

	void		xrndquick::reset(s32 inSeed)
	{
		mSeed = inSeed; 
	}

	u32			xrndquick::generate()
	{
		return gen32(mSeed); 
	}

	void		xrndquick::release()
	{
		if (mAllocator!=NULL) 
		{
			this->~xrndquick(); 
			mAllocator->deallocate(this); 
			mAllocator = NULL;
		}
	}

}

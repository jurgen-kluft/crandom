// x_random_quick.cpp - Core Random number generators, quick
#include "xbase\x_target.h"
#include "xbase\x_memory_std.h"
#include "xbase\x_allocator.h"

#include "xrandom\private\x_random_quick.h"

namespace xcore
{

	//---------------------------------------------------------------------------------------------------------------------
	//	Quick random
	//---------------------------------------------------------------------------------------------------------------------
	xrnd_quick::xrnd_quick(x_iallocator* alloc) 
		: mSeed(0xdeadbeef)
		, mAllocator(alloc)
	{
	}

	void		xrnd_quick::release()
	{
		this->~xrnd_quick(); 
		if (mAllocator!=NULL) 
		{
			mAllocator->deallocate(this); 
			mAllocator = NULL;
		}
	}

}

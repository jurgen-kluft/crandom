/**
* @file x_random.cpp
*
* Core Random number generators implementation
*/

#include "xbase\x_target.h"
#include "xbase\x_memory_std.h"
#include "xbase\x_allocator.h"

#include "xrandom\x_random.h"
#include "xrandom\x_random_good.h"
#include "xrandom\x_random_quick.h"
#include "xrandom\x_random_mersenne_twister.h"
#include "xrandom\x_random_sitmo.h"

namespace xcore
{
	xrandom*			gCreate_RNG_Good(x_iallocator* allocator)
	{
		void* mem = allocator->allocate(sizeof(xrng_good), 4);
		xrng_good* rnd = new (mem) xrng_good(allocator);
		return rnd;
	}

	xrandom*			gCreate_RNG_Quick(x_iallocator* allocator)
	{
		void* mem = allocator->allocate(sizeof(xrng_quick), 4);
		xrng_quick* rnd = new (mem) xrng_quick(allocator);
		return rnd;
	}

	xrandom*			gCreate_RNG_MT(x_iallocator* allocator)
	{
		void* mem = allocator->allocate(sizeof(xrng_mt), 4);
		xrng_mt* rnd = new (mem) xrng_mt(allocator);
		return rnd;
	}

	xrandom*			gCreate_RNG_Sitmo(x_iallocator* allocator)
	{
		void* mem = allocator->allocate(sizeof(xrng_sitmo), 4);
		xrng_sitmo* rnd = new (mem) xrng_sitmo(allocator);
		return rnd;
	}
}

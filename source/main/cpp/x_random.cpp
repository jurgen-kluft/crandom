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
#include "xrandom\x_random_mersenne_twister.h"
#include "xrandom\x_random_quick.h"

namespace xcore
{
	xirnd*			gCreateRandomGeneratorGood(x_iallocator* allocator)
	{
		void* mem = allocator->allocate(sizeof(xrnd_good), 4);
		xrnd_good* rnd = new (mem) xrnd_good(allocator);
		return rnd;
	}

	xirnd*			gCreateRandomGeneratorQuick(x_iallocator* allocator)
	{
		void* mem = allocator->allocate(sizeof(xrnd_quick), 4);
		xrnd_quick* rnd = new (mem) xrnd_quick(allocator);
		return rnd;
	}

	xirnd*			gCreateRandomGeneratorMersenneTwister(x_iallocator* allocator)
	{
		void* mem = allocator->allocate(sizeof(xrnd_mt), 4);
		xrnd_mt* rnd = new (mem) xrnd_mt(allocator);
		return rnd;
	}

}

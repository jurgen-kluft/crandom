/**
* @file x_random.h
*
* Core Random number generators
*/

// Random.h - Core Random number generators - 
#ifndef __XRANDOM_RANDOM_H__
#define __XRANDOM_RANDOM_H__
#include "xbase\x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase\x_debug.h"
#include "xrandom\x_irandom.h"

namespace xcore
{
	// Forward declares
	class x_iallocator;

	/**
	 * @group		xrandom
	 * @brief		Random number generator
	 */
	class xrnd
	{
	public:
		///@name Construction/Destruction
							xrnd() : mGenerator(NULL)					{  }

		///@name Random functions
		void				init(xirnd* inGenerator, s32 inSeed = 0)	{ mGenerator=inGenerator; mGenerator->init(inSeed); }
		void				release()									{ mGenerator->release(); mGenerator=NULL; }

		inline u32			rand(u32 inBits = 32)						{ ASSERT (inBits <= 32); return mGenerator->rand(inBits); }
		inline s32			randSign(u32 inBits = 31)					{ ASSERT (inBits <= 31); return mGenerator->randSign(inBits); }
		inline f32			randF()										{ return mGenerator->randF(); }
		inline f32			randFSign()									{ return mGenerator->randFSign(); }
		inline xbool		randBool()									{ return mGenerator->randBool(); }

		inline void			randBuffer(xbyte* dst, u32 num_bytes)
		{
			u32 rnd;
			for (u32 i=0; i<num_bytes; ++i)
			{
				if ((i&3) == 0)
					 rnd = rand();

				*dst++ = (rnd&0xff);
				rnd = rnd >> 8;
			}
		}

	private:
							xrnd(const xrnd& inOther)					{ }
		xirnd*				mGenerator;
	};

	extern xirnd*			gCreateRandomGeneratorGood(x_iallocator* allocator);
	extern xirnd*			gCreateRandomGeneratorQuick(x_iallocator* allocator);
	extern xirnd*			gCreateRandomGeneratorMersenneTwister(x_iallocator* allocator);
}
#endif

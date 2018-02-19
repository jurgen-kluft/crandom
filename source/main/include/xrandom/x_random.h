/**
* @file x_random.h
*
* Core Random number generators
*/

// Random.h - Core Random number generators - 
#ifndef __XRANDOM_RANDOM_H__
#define __XRANDOM_RANDOM_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase/x_debug.h"
#include "xrandom/x_rndgen.h"

namespace xcore
{
	// Forward declares
	class x_iallocator;

	/**
	 * @group		xrandom
	 * @brief		Random number generator
	 */
	class xrandom
	{
	public:
		///@name Construction/Destruction
							xrandom(xrndgen* gen) : m_rndgen(gen)		{ reset(); }
							xrandom(const xrandom& o) : m_rndgen(o.m_rndgen)	{ }

		///@name Random functions
		void				reset(s32 inSeed = 0)						{ m_rndgen->reset(inSeed); }
		void				release()									{ m_rndgen->release(); m_rndgen=NULL; }

		inline u32			randU32(u32 inBits = 32)					{ ASSERT (inBits <= 32); return m_rndgen->randU32(inBits); }
		inline s32			randS32(u32 inBits = 31)					{ ASSERT (inBits <= 31); return m_rndgen->randS32(inBits); }
		inline f32			randF32()									{ return m_rndgen->randF32(); }
		inline f32			randF32S()									{ return m_rndgen->randF32S(); }
		inline xbool		randBool()									{ return m_rndgen->randBool(); }
		inline void			randBuffer(xbuffer& buffer)					{ return m_rndgen->randBuffer(buffer); }

	private:
		xrndgen*			m_rndgen;
	};

	extern xrandom			gCreate_RNG_Good(x_iallocator* allocator);
	extern xrandom			gCreate_RNG_Quick(x_iallocator* allocator);
	extern xrandom			gCreate_RNG_MT(x_iallocator* allocator);
	extern xrandom			gCreate_RNG_Sitmo(x_iallocator* allocator);
}
#endif

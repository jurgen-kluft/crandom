/**
* @file x_irandom.h
*
* Core Random number generator interface
*/

#ifndef __XRANDOM_IRANDOM_H__
#define __XRANDOM_IRANDOM_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase/x_buffer.h"

namespace xcore
{
	/**
	 * @group		xrandom
	 * @brief		Random number generator interface
	**/
	class xrndgen
	{
	public:
		virtual				~xrndgen() {}

		///@name Random functions
		virtual void		reset(s32 inSeed = 0) = 0;

		virtual u32			randU32(u32 inBits = 32) = 0;
		virtual s32			randS32(u32 inBits = 31) = 0;
		virtual f32			randF32() = 0;
		virtual f32			randF32S() = 0;
		virtual xbool		randBool() = 0;
		virtual void		randBuffer(xbuffer&) = 0;

		virtual void		release() = 0;
	};
}
#endif	///< __XRANDOM_IRANDOM_H__

/**
* @file x_irandom.h
*
* Core Random number generator interface
*/

#ifndef __XRANDOM_IRANDOM_H__
#define __XRANDOM_IRANDOM_H__
#include "xbase\x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

namespace xcore
{
	/**
	 * @group		xrandom
	 * @brief		Random number generator interface
	**/
	class xirnd
	{
	public:
		virtual				~xirnd() {}

		///@name Random functions
		virtual void		init(s32 inSeed = 0) = 0;
		virtual void		release() = 0;

		virtual u32			rand(u32 inBits = 32) = 0;
		virtual s32			randSign(u32 inBits = 31) = 0;
		virtual f32			randF() = 0;
		virtual f32			randFSign() = 0;
		virtual xbool		randBool() = 0;
	};

}
#endif	///< __XRANDOM_IRANDOM_H__

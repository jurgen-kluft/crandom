// xmtrandom.cpp - Mersenne Twister random number generator
#include "xbase\x_target.h"
#include "xbase\x_types.h"
#include "xbase\x_allocator.h"

#include "xrandom\xrandom.h"
#include "xrandom\mtrandom.h"

namespace xcore
{
	xmtrandom::xmtrandom()
		: mState(NULL)
		, mNextState(NULL)
		, mLeft(0)
		, mInitialized(false)
	{

	}

	void		xmtrandom::Seed(u32 inSeed)
	{
		if (mState==NULL)
			mState = (u32*)xrandom_get_heap_allocator()->allocate(xmtrandom::N * sizeof(u32), X_ALIGNMENT_DEFAULT);

		mState[0]= inSeed & (u32)0xffffffff;
		for (s32 j=1; j<N; j++)
		{
			mState[j] = ((u32)1812433253 * (mState[j-1] ^ (mState[j-1] >> 30)) + j); 
			mState[j] &= (u32)0xffffffff;
		}
		mLeft = 1;
		mInitialized = true;
	}



	void	xmtrandom::Seed(u32 const* inSeedArray, s32 inLength)
	{
		Seed();

		s32 i=1;
		s32 j=0;

		s32 k = (N>inLength) ? N : inLength;

		for (; k; k--)
		{
			mState[i] = (mState[i] ^ ((mState[i-1] ^ (mState[i-1] >> 30)) * (u32)1664525)) + inSeedArray[j] + j;
			mState[i] &= (u32)0xffffffff;

			i++;
			j++;
			if (i>=N)
			{
				mState[0] = mState[N-1];
				i=1;
			}
			if (j>=inLength)
				j=0;
		}
		for (k=N-1; k; k--)
		{
			mState[i] = (mState[i] ^ ((mState[i-1] ^ (mState[i-1] >> 30)) * (u32)1566083941)) - i;
			mState[i] &= (u32)0xffffffff;

			i++;
			if (i>=N)
			{
				mState[0] = mState[N-1];
				i = 1;
			}
		}

		mState[0] = 0x80000000;														// MSB is 1; assuring non-zero initial array
		mLeft = 1;
		mInitialized = true;
	}


	/**
	@brief	Resets the generator to it's initial state
	**/
	void	xmtrandom::Release()
	{
		if (mState != NULL)
		{
			xrandom_get_heap_allocator()->deallocate(mState);
			mState = NULL;
		}
		mNextState = NULL;
		mLeft = 0;
		mInitialized = false;
	}


	/**
	@brief	Generates a random number on [0,0x7fffffff]-interval
	**/
	u32	xmtrandom::Rand(s32 inBits)
	{
		if (--mLeft == 0)
			GenerateNewState();

		u32 x = *mNextState++;
		x ^= (x >> 11);
		x ^= (x << 7) & (u32)0x9d2c5680;
		x ^= (x << 15) & (u32)0xefc60000;
		x ^= (x >> 18);
		return (s32)(x>>(32-inBits));
	}


	/**
	@brief	Generates a random number on [0,0xffffffff]-interval
	**/
	s32		xmtrandom::RandSign(s32 inBits)
	{
		if (--mLeft == 0)
			GenerateNewState();

		u32 x = *mNextState++;
		x ^= (x >> 11);
		x ^= (x << 7) & (u32)0x9D2C5680;
		x ^= (x << 15) & (u32)0xEFC60000;
		x ^= (x >> 18);
		return (s32)(x>>(32-inBits));
	}


	void	xmtrandom::GenerateNewState()
	{
		// If Seed() has not been called, a default initial seed is used
		if (!mInitialized)
			Seed();

		mLeft = N;
		mNextState = mState;

		u32*	statePtr = mState;

		s32 j;
		for (j=N-M+1; --j; statePtr++) 
			*statePtr = statePtr[M] ^ Twist(statePtr[0], statePtr[1]);

		for (j=M; --j; statePtr++) 
			*statePtr = statePtr[M-N] ^ Twist(statePtr[0], statePtr[1]);

		*statePtr = statePtr[M-N] ^ Twist(statePtr[0], mState[0]);
	}

}

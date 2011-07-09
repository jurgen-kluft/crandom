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

	void		xmtrandom::seed(u32 inSeed)
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



	void	xmtrandom::seed(u32 const* inSeedArray, s32 inLength)
	{
		seed();

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
	@brief	Releases all memory and resets the generator to it's initial state
	**/
	void	xmtrandom::release()
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
	@brief	Generates a random number on [0,0xffffffff]-interval
	**/
	u32	xmtrandom::rand(s32 inBits)
	{
		if (--mLeft == 0)
			generateNewState();

		u32 x = *mNextState++;
		return (s32)(x>>(32-inBits));
	}


	/**
	@brief	Generates a random number on [0,0x7fffffff]-interval
	**/
	s32		xmtrandom::randSign(s32 inBits)
	{
		if (--mLeft == 0)
			generateNewState();

		u32 x = *mNextState++;
		return (s32)(x>>(32-inBits));
	}

	/**
	@brief	Generates a random number on [0,0xffffffff]-interval
	**/
	u32	xmtrandom::rand()
	{
		if (--mLeft == 0)
			generateNewState();
		return *mNextState++;
	}


	/**
	@brief	Generates a random number on [0,0x7fffffff]-interval
	**/
	s32		xmtrandom::randSign()
	{
		if (--mLeft == 0)
			generateNewState();
		return (s32)(*mNextState++ >> 1);
	}

	void	xmtrandom::generateNewState()
	{
		// If Seed() has not been called, a default initial seed is used
		if (!mInitialized)
			seed();

		mLeft = N;
		mNextState = mState;

		u32*	statePtr = mState;

		s32 j;
		for (j=N-M+1; --j; statePtr++) 
			*statePtr = statePtr[M] ^ twist(statePtr[0], statePtr[1]);

		for (j=M; --j; statePtr++) 
			*statePtr = statePtr[M-N] ^ twist(statePtr[0], statePtr[1]);

		*statePtr = statePtr[M-N] ^ twist(statePtr[0], mState[0]);
	}

}

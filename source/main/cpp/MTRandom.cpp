// xmtrandom.cpp - Mersenne Twister random number generator
#include "xbase\x_target.h"
#include "xrandom\xmtrandom.h"

namespace xcore
{
	u32*					xmtrandom::sState		= NULL;
	u32*					xmtrandom::sNextState	= NULL;
	s32						xmtrandom::sLeft			= 0;
	xbool					xmtrandom::sInitialized	= false;

	void		xmtrandom::Seed(u32 inSeed)
	{
		if (sState==NULL)
			sState = new u32[xmtrandom::N];

		sState[0]= inSeed & (u32)0xffffffff;
		for (s32 j=1; j<N; j++)
		{
			sState[j] = ((u32)1812433253 * (sState[j-1] ^ (sState[j-1] >> 30)) + j); 
			sState[j] &= (u32)0xffffffff;
		}
		sLeft = 1;
		sInitialized = true;
	}



	void	xmtrandom::Seed(u32 const* inSeedArray, s32 inLength)
	{
		Seed();

		s32 i=1;
		s32 j=0;

		s32 k = (N>inLength) ? N : inLength;

		for (; k; k--)
		{
			sState[i] = (sState[i] ^ ((sState[i-1] ^ (sState[i-1] >> 30)) * (u32)1664525)) + inSeedArray[j] + j;
			sState[i] &= (u32)0xffffffff;

			i++;
			j++;
			if (i>=N)
			{
				sState[0] = sState[N-1];
				i=1;
			}
			if (j>=inLength)
				j=0;
		}
		for (k=N-1; k; k--)
		{
			sState[i] = (sState[i] ^ ((sState[i-1] ^ (sState[i-1] >> 30)) * (u32)1566083941)) - i;
			sState[i] &= (u32)0xffffffff;

			i++;
			if (i>=N)
			{
				sState[0] = sState[N-1];
				i = 1;
			}
		}

		sState[0] = 0x80000000;														// MSB is 1; assuring non-zero initial array
		sLeft = 1;
		sInitialized = true;
	}


	/**
	@brief	Resets the generator to it's initial state
	**/
	void	xmtrandom::Release()
	{
		if (sState != NULL)
		{
			delete sState;
			sState = NULL;
		}
		sNextState = NULL;
		sLeft = 0;
		sInitialized = false;
	}


	/**
	@brief	Generates a random number on [0,0x7fffffff]-interval
	**/
	u32	xmtrandom::Rand(s32 inBits)
	{
		if (--sLeft == 0)
			GenerateNewState();

		u32 x = *sNextState++;
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
		if (--sLeft == 0)
			GenerateNewState();

		u32 x = *sNextState++;
		x ^= (x >> 11);
		x ^= (x << 7) & (u32)0x9D2C5680;
		x ^= (x << 15) & (u32)0xEFC60000;
		x ^= (x >> 18);
		return (s32)(x>>(32-inBits));
	}


	void	xmtrandom::GenerateNewState()
	{
		// If Seed() has not been called, a default initial seed is used
		if (!sInitialized)
			Seed();

		sLeft = N;
		sNextState = sState;

		u32*	statePtr = sState;

		s32 j;
		for (j=N-M+1; --j; statePtr++) 
			*statePtr = statePtr[M] ^ Twist(statePtr[0], statePtr[1]);

		for (j=M; --j; statePtr++) 
			*statePtr = statePtr[M-N] ^ Twist(statePtr[0], statePtr[1]);

		*statePtr = statePtr[M-N] ^ Twist(statePtr[0], sState[0]);
	}

}

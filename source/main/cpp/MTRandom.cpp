// MTRandom.cpp - Core Mersenne Twister random number generator - 
#include "CCore\CCore.h"
#include "CRandom\MTRandom.h"
BEGIN_CORE_NAMESPACE



uint32*					MTRandom::sState		= NULL;
uint32*					MTRandom::sNextState	= NULL;
int						MTRandom::sLeft			= 0;
bool					MTRandom::sInitialized	= false;



void		MTRandom::Seed(uint32 inSeed)
{
	if (sState==NULL)
		sState = new uint32[MTRandom::N];

    sState[0]= inSeed & (uint32)0xffffffff;
    for (int j=1; j<N; j++)
	{
        sState[j] = ((uint32)1812433253 * (sState[j-1] ^ (sState[j-1] >> 30)) + j); 
        sState[j] &= (uint32)0xffffffff;
    }
    sLeft = 1;
	sInitialized = true;
}



void	MTRandom::Seed(pcUInt32 inSeedArray, int inLength)
{
    Seed();

	int i=1;
	int j=0;

	int k = (N>inLength) ? N : inLength;

    for (; k; k--)
	{
        sState[i] = (sState[i] ^ ((sState[i-1] ^ (sState[i-1] >> 30)) * (uint32)1664525)) + inSeedArray[j] + j;
        sState[i] &= (uint32)0xffffffff;
        
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
        sState[i] = (sState[i] ^ ((sState[i-1] ^ (sState[i-1] >> 30)) * (uint32)1566083941)) - i;
        sState[i] &= (uint32)0xffffffff;
        
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
void	MTRandom::Release()
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
uint	MTRandom::Rand(int inBits)
{
	if (--sLeft == 0)
		GenerateNewState();

	uint32 x = *sNextState++;
    x ^= (x >> 11);
    x ^= (x << 7) & (uint32)0x9d2c5680;
    x ^= (x << 15) & (uint32)0xefc60000;
    x ^= (x >> 18);
    return (int32)(x>>(32-inBits));
}


/**
@brief	Generates a random number on [0,0xffffffff]-interval
**/
int		MTRandom::RandSign(int inBits)
{
	if (--sLeft == 0)
		GenerateNewState();

	uint32 x = *sNextState++;
	x ^= (x >> 11);
	x ^= (x << 7) & (uint32)0x9D2C5680;
	x ^= (x << 15) & (uint32)0xEFC60000;
	x ^= (x >> 18);
	return (int32)(x>>(32-inBits));
}


void	MTRandom::GenerateNewState()
{
	// If Seed() has not been called, a default initial seed is used
    if (!sInitialized)
		Seed();

    sLeft = N;
	sNextState = sState;
    
    uint32*	statePtr = sState;

    int j;
    for (j=N-M+1; --j; statePtr++) 
        *statePtr = statePtr[M] ^ Twist(statePtr[0], statePtr[1]);

    for (j=M; --j; statePtr++) 
        *statePtr = statePtr[M-N] ^ Twist(statePtr[0], statePtr[1]);

    *statePtr = statePtr[M-N] ^ Twist(statePtr[0], sState[0]);
}

END_CORE_NAMESPACE

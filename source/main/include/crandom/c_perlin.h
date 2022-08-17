#ifndef __CRANDOM_PERLIN_H__
#define __CRANDOM_PERLIN_H__
#include "cbase/c_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

namespace ncore
{
    /**
     * @group		random_t
     * @brief		Perlin noise
     */
    class noise
    {
    public:
        ///@name Construction/Destruction
        noise();
        ~noise();

        ///@name Noise
        f32 noise1D(f32 inT);                   ///< Return noise on 1D line <inT>
        f32 noise2D(f32 inX, f32 inY);          ///< Return noise in 2-space at <inVector>
        f32 noise3D(f32 inX, f32 inY, f32 inZ); ///< Return noise in 3-space at <inVector>
    };

    /**
     * @group		random_t
     * @brief		Turbulence using Perlin noise
     *			Ken Perlin's turbulence function using Perlin noise
     */
    class tnoise
    {
    public:
        ///@name Construction/Destruction
        inline tnoise()
            : mFrequency(1.0f)
        {
        }

        ///@name Turbulence
        f32 evaluate(f32 inPos); ///< Evaluate turbulence at <inPos>

        ///@name Properties
        inline f32  getFrequency() const { return mFrequency; }                 ///< Get the frequency of the turbulence
        inline void setFrequency(f32 inFrequency) { mFrequency = inFrequency; } ///< Set the frequency of the turbulence

    private:
        f32    mFrequency;
        noise mNoise;
    };

    /**
     * @group		random_t
     * @brief		Persistence Noise
     *			Harmonic noise as used by http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
     *			Looks a lot like the other two...
     */
    class pnoise
    {
    public:
        ///@name Construction/Destruction
        pnoise()
            : mPersistence(1.0f)
            , mOctaves(1)
        {
        }

        ///@name Persistence noise
        f32 evaluate(f32 inPos); ///< Evaluate harmonic noise

        ///@name Properties
        inline f32  getPersistence() const { return mPersistence; }
        inline s32  getOctaves() const { return mOctaves; }
        inline void setPersistence(f32 inPersistence) { mPersistence = inPersistence; }
        inline void setOctaves(s32 inOctaves) { mOctaves = inOctaves; }

    private:
        f32    mPersistence;
        s32    mOctaves;
        noise mNoise;
    };

} // namespace ncore
#endif ///< __CRANDOM_PERLIN_H__

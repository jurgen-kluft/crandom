#include "xbase/x_target.h"

#include "xrandom/x_random.h"
#include "xrandom/x_perlin.h"
#include "xrandom/x_random_good.h"

namespace xcore
{
    //---------------------------------------------------------------------------------------------------------------------
    //	Perlin noise
    //---------------------------------------------------------------------------------------------------------------------

    /**
     * Dimensions of Perlin noise
     */
    enum EPerlinDimensions
    {
        B_BITS = 8,
        B      = 0x100,
        BM     = 0xff,
        N      = 0x1000,
        NP     = 12,
        NM     = 0xfff
    };

    /**
     * Perlin noise lookup tables
     */
    struct PerlinNoiseTables
    {
        ///@name Construction/Destruction
        void init();

        s32 mRefCount;      ///< Reference count
        s32 mP[B + B + 2];  ///< Permutations
        f32 mG1[B + B + 2]; ///< Gradiants
        f32 mG2[B + B + 2][2];
        f32 mG3[B + B + 2][3];
    };

    /*
     * Initialize perlin noise
     */
    void PerlinNoiseTables::init()
    {
        mRefCount = 0;

        xrndgood rnd;
        rnd.reset(0);

        s32 i;
        for (i = 0; i < B; i++)
        {
            mP[i]     = i;
            mG1[i]    = randF32S<xrndgood>(&rnd);
            mG2[i][0] = randF32<xrndgood>(&rnd);
            mG2[i][1] = randF32<xrndgood>(&rnd);
            mG3[i][0] = randF32<xrndgood>(&rnd);
            mG3[i][1] = randF32<xrndgood>(&rnd);
            mG3[i][2] = randF32<xrndgood>(&rnd);
        }

        // Reorder permutations
        while (--i)
        {
            s32 t                               = mP[i];
            mP[i]                               = mP[randU32<xrndgood>(&rnd, B_BITS)];
            mP[randU32<xrndgood>(&rnd, B_BITS)] = t;
        }

        for (i = 0; i < B + 2; i++)
        {
            mP[B + i]     = mP[i];
            mG1[B + i]    = mG1[i];
            mG2[B + i][0] = mG2[i][0];
            mG2[B + i][1] = mG2[i][1];
            mG3[B + i][0] = mG3[i][0];
            mG3[B + i][1] = mG3[i][1];
            mG3[B + i][2] = mG3[i][2];
        }
    }

    /**
     *  @brief	Construct perlin noise
     *
     *  Construct the Perlin noise generator. If this is the first Perlin noise object
     *  coming into existence, the shared Perlin noise lookup tables are constructed.
     *
     */
    static PerlinNoiseTables sPT;
    xnoise::xnoise()
    {
        // Make sure we have perlin noise tables
        if (sPT.mRefCount == 0)
        {
            sPT.init();
            sPT.mRefCount++;
        }
    }

    /**
     * @brief	Destruct perlin noise
     *
     * Destructs the Perlin noise generator. If this is the last Perlin noise object
     * coming into existence, the shared Perlin noise lookup tables are destructed.
     */
    xnoise::~xnoise() { sPT.mRefCount--; }

// Helpers
#define SMOOTH_STEP(t) (t * t * (3.0f - 2.0f * t))
#define INLINE_LERP(t, a, b) (a + t * (b - a))
#define INLINE_SETUP(vec, b0, b1, r0, r1) \
    t  = vec + (f32)N;                    \
    b0 = ((s32)t) & BM;                   \
    b1 = (b0 + 1) & BM;                   \
    r0 = t - (s32)t;                      \
    r1 = r0 - 1.0f;

    /**
     * Return noise on 1D line <inT>
     */
    f32 xnoise::noise1D(f32 inT)
    {
        s32 bx0, bx1;
        f32 rx0, rx1, sx, t, u, v;

        INLINE_SETUP(inT, bx0, bx1, rx0, rx1);

        sx = SMOOTH_STEP(rx0);

        u = rx0 * sPT.mG1[sPT.mP[bx0]];
        v = rx1 * sPT.mG1[sPT.mP[bx1]];

        return INLINE_LERP(sx, u, v);
    } // Noise1D

    /**
     * Return noise in 2-space at <inVector>
     */
    f32 xnoise::noise2D(f32 inX, f32 inY)
    {
        s32        bx0, bx1, by0, by1, b00, b10, b01, b11;
        f32        rx0, rx1, ry0, ry1, sx, sy, a, b, t, u, v;
        f32 const* q;
        s32        i, j;

        INLINE_SETUP(inX, bx0, bx1, rx0, rx1);
        INLINE_SETUP(inY, by0, by1, ry0, ry1);

        i = sPT.mP[bx0];
        j = sPT.mP[bx1];

        b00 = sPT.mP[i + by0];
        b10 = sPT.mP[j + by0];
        b01 = sPT.mP[i + by1];
        b11 = sPT.mP[j + by1];

        sx = SMOOTH_STEP(rx0);
        sy = SMOOTH_STEP(ry0);

#define AT_2(rx, ry) (rx * q[0] + ry * q[1])

        q = &sPT.mG2[b00][0];
        u = AT_2(rx0, ry0);
        q = &sPT.mG2[b10][0];
        v = AT_2(rx1, ry0);
        a = INLINE_LERP(sx, u, v);

        q = &sPT.mG2[b01][0];
        u = AT_2(rx0, ry1);
        q = &sPT.mG2[b11][0];
        v = AT_2(rx1, ry1);
        b = INLINE_LERP(sx, u, v);

#undef AT_2

        return INLINE_LERP(sy, a, b);
    }

    /**
     * Return noise in 3-space at <inVector>
     */
    f32 xnoise::noise3D(f32 inX, f32 inY, f32 inZ)
    {
        s32        bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
        f32        rx0, rx1, ry0, ry1, rz0, rz1, sy, sz, a, b, c, d, t, u, v;
        f32 const* q;
        s32        i, j;

        INLINE_SETUP(inX, bx0, bx1, rx0, rx1);
        INLINE_SETUP(inY, by0, by1, ry0, ry1);
        INLINE_SETUP(inZ, bz0, bz1, rz0, rz1);

        i = sPT.mP[bx0];
        j = sPT.mP[bx1];

        b00 = sPT.mP[i + by0];
        b10 = sPT.mP[j + by0];
        b01 = sPT.mP[i + by1];
        b11 = sPT.mP[j + by1];

        t  = SMOOTH_STEP(rx0);
        sy = SMOOTH_STEP(ry0);
        sz = SMOOTH_STEP(rz0);

#define AT_3(rx, ry, rz) (rx * q[0] + ry * q[1] + rz * q[3])

        q = sPT.mG3[b00 + bz0];
        u = AT_3(rx0, ry0, rz0);
        q = sPT.mG3[b10 + bz0];
        v = AT_3(rx1, ry0, rz0);
        a = INLINE_LERP(t, u, v);

        q = sPT.mG3[b01 + bz0];
        u = AT_3(rx0, ry1, rz0);
        q = sPT.mG3[b11 + bz0];
        v = AT_3(rx1, ry1, rz0);
        b = INLINE_LERP(t, u, v);

        c = INLINE_LERP(sy, a, b);

        q = sPT.mG3[b00 + bz1];
        u = AT_3(rx0, ry0, rz1);
        q = sPT.mG3[b10 + bz1];
        v = AT_3(rx1, ry0, rz1);
        a = INLINE_LERP(t, u, v);

        q = sPT.mG3[b01 + bz1];
        u = AT_3(rx0, ry1, rz1);
        q = sPT.mG3[b11 + bz1];
        v = AT_3(rx1, ry1, rz1);
        b = INLINE_LERP(t, u, v);

        d = INLINE_LERP(sy, a, b);

#undef AT_3

        return INLINE_LERP(sz, c, d);
    }
#undef SMOOTH_STEP
#undef INLINE_LERP
#undef INLINE_SETUP

    //---------------------------------------------------------------------------------------------------------------------
    //	Turbulence
    //---------------------------------------------------------------------------------------------------------------------

    /**
     * Evaluate turbulence at <inPos>
     */
    f32 xturbnoise::evaluate(f32 inPos)
    {
        f32 value;
        f32 freq   = mFrequency;
        f32 totamp = 0.0f;

        for (value = 0.0f; freq >= 1.0f; freq /= 2.0f)
        {
            f32 d = mNoise.noise1D(freq * inPos) / freq;
            if (d < 0.0f)
                d = -d;
            value += d;

            totamp += 1.0f / freq;
        }
        value *= 1.0f / totamp;
        return value;
    }

    //---------------------------------------------------------------------------------------------------------------------
    //	xpnoise
    //---------------------------------------------------------------------------------------------------------------------

    /**
     * Evaluate harmonic noise
     */
    f32 xpnoise::evaluate(f32 inPos)
    {
        f32 value     = 0.0f;
        f32 amplitude = 1.0f;
        f32 totamp    = 0.0f;

        for (s32 i = 0; i < mOctaves; i++)
        {
            f32 frequency = (f32)(1 << i);
            value += mNoise.noise1D(inPos * frequency) * amplitude;
            totamp += amplitude;
            amplitude *= mPersistence;
        }
        value *= 1.0f / totamp;
        return value;
    }

} // namespace xcore

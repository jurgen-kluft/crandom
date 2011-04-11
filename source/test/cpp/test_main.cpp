#include "xbase\x_target.h"
#include "xbase\x_types.h"
#include "xbase\x_allocator.h"

#include "xrandom\xrandom.h"

#include "xunittest\xunittest.h"

using namespace xcore;

UNITTEST_SUITE_LIST(xRandomUnitTest);
UNITTEST_SUITE_DECLARE(xRandomUnitTest, xrandom);
UNITTEST_SUITE_DECLARE(xRandomUnitTest, xmtrandom);

namespace xcore
{
	class TestHeapAllocator : public x_iallocator
	{
	public:
		TestHeapAllocator(xcore::x_iallocator* allocator)
			: mAllocator(allocator)
			, mNumAllocations(0)
		{
		}

		xcore::x_iallocator*	mAllocator;
		s32						mNumAllocations;

		const char*	name() const
		{
			return "xrandom unittest test heap allocator";
		}

		void*		allocate(s32 size, s32 alignment)
		{
			++mNumAllocations;
			return mAllocator->allocate(size, alignment);
		}

		void*		callocate(s32 n_elems, s32 elem_size)
		{
			++mNumAllocations;
			return mAllocator->callocate(n_elems, elem_size);
		}

		void*		reallocate(void* mem, s32 size, s32 alignment)
		{
			return mAllocator->reallocate(mem, size, alignment);
		}

		void		deallocate(void* mem)
		{
			--mNumAllocations;
			mAllocator->deallocate(mem);
		}

		void		release()
		{
		}
	};
}

class UnitTestAllocator : public UnitTest::Allocator
{
public:
	xcore::x_iallocator*	mAllocator;
	int						mNumAllocations;

	UnitTestAllocator(xcore::x_iallocator* allocator)
		: mNumAllocations(0)
	{
		mAllocator = allocator;
	}

	void*	Allocate(int size)
	{
		++mNumAllocations;
		return mAllocator->allocate(size, 4);
	}
	void	Deallocate(void* ptr)
	{
		--mNumAllocations;
		mAllocator->deallocate(ptr);
	}
};

bool gRunUnitTest(UnitTest::TestReporter& reporter)
{
	xcore::x_iallocator* systemAllocator = xcore::gCreateSystemAllocator();

	UnitTestAllocator unittestAllocator( systemAllocator );
	UnitTest::SetAllocator(&unittestAllocator);

	TestHeapAllocator testHeapAllocator(systemAllocator);
	xcore::xrandom_set_heap_allocator(&testHeapAllocator);

	int r = UNITTEST_SUITE_RUN(reporter, xRandomUnitTest);
	if (unittestAllocator.mNumAllocations!=0)
	{
		reporter.reportFailure(__FILE__, __LINE__, "xunittest", "memory leaks detected!");
		r = -1;
	}
	if (testHeapAllocator.mNumAllocations!=0)
	{
		reporter.reportFailure(__FILE__, __LINE__, "xrandom", "memory leaks detected!");
		r = -1;
	}

	systemAllocator->release();
	return r==0;
}

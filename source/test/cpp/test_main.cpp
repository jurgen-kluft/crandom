#include "xbase\x_target.h"
#include "xbase\x_types.h"

#include "xunittest\xunittest.h"

using namespace xcore;

UNITTEST_SUITE_LIST(xRandomUnitTest);
UNITTEST_SUITE_DECLARE(xRandomUnitTest, xrandom);

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

	void	Release()
	{
		mAllocator->release();
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


class UnitTestObserver : public UnitTest::Observer
{
public:
	void	BeginFixture(const char* filename, const char* suite_name, const char* fixture_name)
	{
	}
	void	EndFixture()
	{
	}
};


int main(int argc, char** argv)
{
	UnitTestAllocator unittestAllocator( xcore::gCreateSystemAllocator() );
	UnitTestObserver unittestObserver;
	UnitTest::SetAllocator(&unittestAllocator);
	UnitTest::SetObserver(&unittestObserver);

	UnitTest::TestReporterStdout stdout_reporter;
	UnitTest::TestReporter& reporter = stdout_reporter;

	int r = UNITTEST_SUITE_RUN(reporter, xRandomUnitTest);

	if (unittestAllocator.mNumAllocations!=0)
	{
		reporter.reportFailure(__FILE__, __LINE__, __FUNCTION__, "memory leaks detected!");
		r = -1;
	}

	unittestAllocator.Release();
	return r;

}
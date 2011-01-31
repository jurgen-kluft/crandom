#ifndef __XRANDOM_XRANDOM_H__
#define	__XRANDOM_XRANDOM_H__

#include "xrandom\random.h"

namespace xcore
{
	class x_iallocator;
	extern void				xrandom_set_heap_allocator(x_iallocator* allocator);
	extern x_iallocator*	xrandom_get_heap_allocator();
}

#endif	///< __XRANDOM_XRANDOM_H__
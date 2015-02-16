#include "memory.h"

#include "../Tcdefs.h"
#include "../Dlgcode.h"
#include "process.h"
#include <stdlib.h>

#ifdef CS_UNITTESTING
#endif
 
#pragma warning(push)
#pragma warning(disable:4702)

void *err_malloc (size_t size)
{
	void *z = (void *) TCalloc (size);
	if (z)
		return z;
	AbortProcess ("OUTOFMEMORY");
	return 0;
}

#pragma warning(pop)

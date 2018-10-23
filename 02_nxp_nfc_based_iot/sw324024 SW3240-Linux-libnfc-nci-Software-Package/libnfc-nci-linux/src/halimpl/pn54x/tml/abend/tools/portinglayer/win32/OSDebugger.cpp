

#include "core/Types.h"

void callDebugger()
{
	*(int *)(uintptr_t)0xbbadbeef = 0;
}



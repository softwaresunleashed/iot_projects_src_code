

#include "AllocatorsPF.h"

#include "core/Locker.h"

#include <new>

// #include "MemoryProfiler.h"

#undef malloc
#undef free
#undef strdup

#define VERBOSE_TAG "AllocatorsPF"
#include "core/Verbose.h"

// #define USE_PROFILER

// MemoryProfiler memoryProfiler;
// 
// void dumpLeaks()
// {
// 	memoryProfiler.dumpLeaks();
// }
// void keepStacktrace(bool val)
// {
// 	memoryProfiler.keepStack(val);
// }
// 
// void recordLeaks(bool val)
// {
// 	memoryProfiler.recordLeak(val);
// }
// 
// uint32_t getMemoryUsage()
// {
// 	return memoryProfiler.getMemoryUsage();
// }




void* operator new(size_t size)
{
	void *p = tools_malloc(size);
	if (p == 0)
	{
		// abort();
	}
	return p;
}

void operator delete(void *p)
{
	tools_free(p);
}

void * tools_malloc(uint32_t size)
{
#ifdef USE_PROFILER
	void *result = memoryProfiler.allocBloc(size);
#else
	void *result = malloc(size);
#endif // def USE_PROFILER

	if (!result)
	{
		FATAL("Out of memory\n");
	}

	return result;
}

void * tools_realloc(void *ptr,uint32_t size)
{
	if (!ptr)
	{
		return tools_malloc(size);
	}
#ifdef USE_PROFILER
	void *newBloc    = memoryProfiler.allocBloc(size);
	uint32_t oldSize = memoryProfiler.getBlocSize(ptr);
	memcpy(newBloc,ptr,oldSize);
	memoryProfiler.freeBloc(ptr);
	return newBloc;
#else
	return realloc(ptr,size);
#endif // def USE_PROFILER

}

void tools_free(void *ptr)
{
#ifdef USE_PROFILER
	memoryProfiler.freeBloc(ptr);
#else
	free(ptr);
#endif // def USE_PROFILER
}

char * tools_strdup(const char * str)
{
	char* dup = (char*)tools_malloc(strlen(str) + 1);
	strcpy(dup, str);
	return dup;
}













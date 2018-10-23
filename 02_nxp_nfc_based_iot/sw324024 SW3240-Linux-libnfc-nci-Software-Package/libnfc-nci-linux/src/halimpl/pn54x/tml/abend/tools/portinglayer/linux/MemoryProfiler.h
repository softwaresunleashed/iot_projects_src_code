

#ifndef MemoryProfiler_H
#define MemoryProfiler_H

#include "core/Types.h"
#include <pthread.h>

struct sMemoryInfo;
/** **/
class MemoryProfiler
{
	public:
		MemoryProfiler()
		{
			if (!m_lock)
			{
				init();
			}
		}

		void* allocBloc(uint32_t size);
		void freeBloc(void *ptr);

		uint32_t getBlocSize(void * ptr);

		void dumpLeaks();

		void keepStack(bool val);
		void recordLeak(bool val);

		uint32_t getMemoryUsage();

	private:
// 		char **grabStack(uint32_t &outBtsize);
		void   init();

	private:
		sMemoryInfo            *m_lastAllocated;
		static uint32_t         m_overAllMemory;
		static pthread_mutex_t *m_lock;
		static bool             m_keepStack;
		static bool             m_recordLeak;
};


#endif // ndef MemoryProfiler_H



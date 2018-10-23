

#include "MemoryProfiler.h"


#include <Windows.h>
#undef ERROR

#define VERBOSE_TAG "MemoryProfiler"
#include "core/Verbose.h"


// **************** User params ************************
#define MEMORY_FILL_MOTIF               0xCC
#define STACK_SIZE                      10
#define STACK_FILTER_CMD                "c++filt"




#define STACK_IGNORE  2
#define REAL_STACK_SIZE (STACK_SIZE+STACK_IGNORE)

static uint32_t magicBegin = 0xDEAC0DE;
static uint32_t magicEnd   = 0xBAADBEEF;

struct sMemoryInfo
{
	uint32_t     sanityCheck1;
	uint32_t     size;
	uint32_t     recordLeak;
	sMemoryInfo *prev;
	sMemoryInfo *next;
	uint32_t     sanityCheck2;
};

void *MemoryProfiler::m_lock = NULL;
bool MemoryProfiler::m_keepStack = true;
bool MemoryProfiler::m_recordLeak = false;
uint32_t MemoryProfiler::m_overAllMemory = 0;

void MemoryProfiler::keepStack(bool val)
{
	m_keepStack = val;
}


void * MemoryProfiler::allocBloc(uint32_t size)
{
	if (size == 0)
	{
		WARN("Try to malloc 0 byte !!!\n");
	}
	if (!m_lock)
	{
		init();
	}
	WaitForSingleObject(m_lock,INFINITE);
	uint32_t     realSize    = size + sizeof(sMemoryInfo) + sizeof(uint32_t) * 2; // + 2 uint32_t for override check.
	void        *result      = malloc(realSize);

	if (!result)
	{
		FATAL("Out of memory\n");
	}

	sMemoryInfo *info        = reinterpret_cast<sMemoryInfo*>(result);
	uint8_t     *buffAsByte  = reinterpret_cast<uint8_t*>(result);
	void        *returnedBuf = reinterpret_cast<void*>(buffAsByte + sizeof(sMemoryInfo));

	m_overAllMemory += size;

	if (!m_lastAllocated)
	{
		info->prev = NULL;
	}
	else
	{
		m_lastAllocated->next = info;
		info->prev = m_lastAllocated;
	}

	m_lastAllocated = info;

	// Fill infos.
	info->sanityCheck1 = magicBegin;
	info->size         = size;
	info->recordLeak   = m_recordLeak;
	info->next         = NULL;
	info->sanityCheck2 = magicEnd;

	// *****************************
	// Add magic numbers for memory override check.
	{
		uint32_t *buffAsIntBegin = reinterpret_cast<uint32_t*>(returnedBuf);
		uint8_t  *buffAsByte     = reinterpret_cast<uint8_t*>(returnedBuf);
		uint32_t *buffAsIntEnd   = reinterpret_cast<uint32_t*>(buffAsByte + info->size + sizeof(uint32_t));
		buffAsIntBegin[0]        = magicBegin;
		buffAsIntEnd[0]          = magicEnd;
		buffAsIntBegin++;
		returnedBuf              = buffAsIntBegin;
	}
	// *****************************

	// Fill memory with a motif
	memset(returnedBuf, MEMORY_FILL_MOTIF, info->size);

	ReleaseMutex(m_lock);
	return returnedBuf;
}

void MemoryProfiler::freeBloc(void * ptr)
{
	if (!ptr)
	{
		WARN("delete of NULL object called\n");
		return;
	}

	WaitForSingleObject(m_lock,INFINITE);
	uint8_t     *buffAsByte = reinterpret_cast<uint8_t*>(ptr);
	sMemoryInfo *info       = reinterpret_cast<sMemoryInfo*>(buffAsByte - sizeof(sMemoryInfo) - sizeof(uint32_t)); // sMemoryInfo - 1 magic number

	if ((info->sanityCheck1 != magicBegin) || (info->sanityCheck2 != magicEnd))
	{
		FATAL("Memory Overwritten at the begining. Memory head infos corrupted !\n");
	}

	// *****************************
	// Check magic numbers for memory override check.
	{
		uint32_t *buffAsIntBegin = reinterpret_cast<uint32_t*>(ptr);
		uint8_t  *buffAsByte     = reinterpret_cast<uint8_t*>(ptr);
		uint32_t *buffAsIntEnd   = reinterpret_cast<uint32_t*>(buffAsByte + info->size);
		buffAsIntBegin--;

		if (buffAsIntBegin[0] != magicBegin)
		{
			FATAL("Memory Overwritten at the begining of block.!\n");
		}
		if (buffAsIntEnd[0] != magicEnd)
		{
			FATAL("Memory Overwritten at the end of block. !\n");
		}
	}
	// *****************************

	m_overAllMemory -= info->size;

	sMemoryInfo *prev       = info->prev;
	sMemoryInfo *next       = info->next;

	if (m_lastAllocated == info)
	{
		if (prev)
		{
			m_lastAllocated = prev;
		}
		else if (next)
		{
			WARN("Should not happened ?!\n");
			m_lastAllocated = next;
		}else
		{
			m_lastAllocated = NULL;
		}
	}

	// Unchain block.
	if (prev)
	{
		prev->next = next;
	}
	if (next)
	{
		next->prev = prev;
	}

	info->prev = NULL;
	info->next = NULL;

	uint32_t     realSize    = info->size + sizeof(sMemoryInfo) + sizeof(uint32_t) * 2;
	memset(info,0,realSize);
	
	free(info);
	ReleaseMutex(m_lock);
}

uint32_t MemoryProfiler::getBlocSize(void * ptr)
{
	WaitForSingleObject(m_lock,INFINITE);
	uint8_t      *buffAsByte = reinterpret_cast<uint8_t*>(ptr);
	sMemoryInfo  *info       = reinterpret_cast<sMemoryInfo*>(buffAsByte - sizeof(sMemoryInfo));
	uint32_t      size = info->size;
	ReleaseMutex(m_lock);
	return size;
}

void MemoryProfiler::recordLeak(bool val)
{
	m_recordLeak = val;
}

void MemoryProfiler::dumpLeaks()
{
	WARN("dumpLeaks() NOT IMPLEMENTED\n");
}


uint32_t MemoryProfiler::getMemoryUsage()
{
	return m_overAllMemory;
}

void MemoryProfiler::init()
{
	m_lock = CreateMutex(NULL,false,NULL);
	m_lastAllocated = NULL;
}





#undef VERBOSE_TAG

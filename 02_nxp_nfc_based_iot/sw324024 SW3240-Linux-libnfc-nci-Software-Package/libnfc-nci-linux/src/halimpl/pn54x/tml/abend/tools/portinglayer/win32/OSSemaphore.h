#ifndef OSSEMAPHORE_H
#define OSSEMAPHORE_H

/**
 @author Charles GORAND <charles.gorand@effinnov.com>
*/

#include "OSLocker.h"

// Simple Semaphore implementation.

class OSSemaphore
{
	public:
		OSSemaphore();

		~OSSemaphore();
		
		void wait();
		
		void post();
	private:
		OSLocker m_lock;
		int32_t  m_counter;
		
};

#endif

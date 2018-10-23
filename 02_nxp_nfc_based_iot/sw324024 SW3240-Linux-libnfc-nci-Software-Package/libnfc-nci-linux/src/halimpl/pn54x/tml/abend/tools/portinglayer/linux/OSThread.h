#ifndef OSTHREAD_H
#define OSTHREAD_H

#include "core/Types.h"

/**
 @author Charles GORAND <charles.gorand@effinnov.com>
*/
class ThreadedObject;
class OSThread
{
	public:
		OSThread();
		~OSThread();
		
		uint32_t getCurrentThreadId();
		uint32_t getThreadId();
		
		void release();
		
		void start(ThreadedObject *t);
		
	private:
		friend void* thread_object_func(void* ref);
		void internalRun();
		
	private:
		void           *m_threadHandle;
		ThreadedObject *m_thread;
};

#endif

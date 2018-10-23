#include "OSThread.h"

#include "core/ThreadedObject.h"

#define VERBOSE_TAG "OSThread"
#include "core/Verbose.h"

#include <unistd.h>
#include <pthread.h>
// #include <typeinfo>

struct tThreadInfo
{
	pthread_t thread;
};

void* thread_object_func(void* ref)
{
	OSThread *t = (OSThread*)ref;

	t->internalRun();

	return 0;
}


OSThread::OSThread()
{
	m_thread       = NULL;
	m_threadHandle = NULL;
	
}


OSThread::~OSThread()
{
	if (m_threadHandle)
	{
		release();
	}
}

void OSThread::release()
{
	tThreadInfo * linuxThread = (tThreadInfo*)m_threadHandle;

	if (!linuxThread)
	{
		return;
	}

	_free(m_threadHandle);
}

void OSThread::start(ThreadedObject * t)
{
	m_threadHandle = _malloc(sizeof(tThreadInfo));
	memset(m_threadHandle,0,sizeof(tThreadInfo));
	
	tThreadInfo * linuxThread = (tThreadInfo*)m_threadHandle;

	m_thread = t;
	
	if (pthread_create(&(linuxThread->thread), NULL, thread_object_func, this))
	{
		ERROR("Cannot create thread");
	}
	else
	{
		if(pthread_setname_np((linuxThread->thread),"OS_LAYER_TASK"))
		{
			ERROR("pthread_setname_np in %s failed", __FUNCTION__ );
		}
	}

	pthread_detach(linuxThread->thread);
	
}

void OSThread::internalRun()
{
	m_thread->internalRun();
}

uint32_t OSThread::getCurrentThreadId()
{
	return pthread_self();
}

uint32_t OSThread::getThreadId()
{
	tThreadInfo * linuxThread = (tThreadInfo*)m_threadHandle;
	return linuxThread->thread;
}




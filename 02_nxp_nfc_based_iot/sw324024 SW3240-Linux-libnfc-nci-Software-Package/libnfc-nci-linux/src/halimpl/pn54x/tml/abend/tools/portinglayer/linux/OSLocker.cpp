#include "OSLocker.h"

#define VERBOSE_TAG "OSLocker"
#include "core/Verbose.h"

#include <pthread.h>
#include <errno.h>

OSLocker::OSLocker(bool isRec)
{
	pthread_mutex_t* lock=(pthread_mutex_t*)_malloc(sizeof(pthread_mutex_t));
	if (isRec)
	{
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(lock,&attr);
	}else
	{
		pthread_mutex_init(lock,NULL);
	}
	m_handle   = lock;
	m_cond     = NULL;
}


OSLocker::~OSLocker()
{
	pthread_mutex_destroy((pthread_mutex_t *)m_handle);
	_free(m_handle);

	if (m_cond)
	{
		pthread_cond_destroy((pthread_cond_t *)m_cond);
		_free(m_cond);
	}
}

void logErrorCode(int res)
{
	switch (res)
	{
		case EINVAL:
		{
			FATAL("Retcode is EINVAL\n");
			break;
		}
		case EFAULT:
		{
			FATAL("Retcode is EFAULT\n");
			break;
		}
		case EPERM:
		{
			FATAL("Retcode is EPERM\n");
			break;
		}
		case EBUSY:
		{
			FATAL("Retcode is EBUSY\n");
			break;
		}
		case EAGAIN:
		{
			FATAL("Retcode is EAGAIN\n");
			break;
		}
		case EDEADLK:
		{
			FATAL("Retcode is EDEADLK\n");
			break;
		}
		default :
		{
			FATAL("Retcode is %i\n",res);
			break;
		}
	};
} 

void OSLocker::lock()
{
	int res = pthread_mutex_lock((pthread_mutex_t *)m_handle);
	if (res)
	{
		ERROR("lock() failed errno %i\n",strerror (errno));
		logErrorCode(res);
	}
}

void OSLocker::unlock()
{
	int res = pthread_mutex_unlock((pthread_mutex_t *)m_handle);
	if (res)
	{
		ERROR("unlock() failed %s\n",strerror (errno));
		logErrorCode(res);
	}
}

void OSLocker::wait(bool needLock)
{
	if (needLock)
	{
		lock();
	}
	if (!m_cond)
	{
		pthread_cond_t *cond = (pthread_cond_t*)_malloc(sizeof(pthread_cond_t));
		pthread_cond_init(cond,NULL);
		m_cond = cond;
	}
	
	pthread_cond_wait((pthread_cond_t*)m_cond,(pthread_mutex_t*)m_handle);
	
	if (needLock)
	{
		unlock();
	}
}

void OSLocker::wakeUp(bool needLock)
{
	if (needLock)
	{
		lock();
	}
	if (!m_cond)
	{
		// WARN("No Thread to wake up !\n");
		if (needLock)
		{
			unlock();
		}
		return;
	}

	pthread_cond_broadcast((pthread_cond_t*)m_cond);
	if (needLock)
	{
		unlock();
	}
}





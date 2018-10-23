#include "ThreadedObject.h"

#include "OSThread.h"
#include "MiscPort.h"

#define VERBOSE_TAG "ThreadedObject"
#include "Verbose.h"


#define DEBUG_ 0
#if DEBUG_
#define ENTER_FUNC 			LOG("--> %s\n",__FUNCTION__)
#define EXIT_FUNC  			LOG("<-- %s\n",__FUNCTION__)
#define WITHIN_FUNC(fmt,...)  	LOG("--- %s (%d): "fmt"\n",__FUNCTION__,__LINE__,##__VA_ARGS__)
#else
#define ENTER_FUNC
#define EXIT_FUNC
#define WITHIN_FUNC(...)
#endif

ThreadedObject::ThreadedObject()
{
	ENTER_FUNC;
	m_State = STOPPED;
	m_osThread = NEW(OSThread());

	m_microSleep = 0;
	m_prevCall   = 0;

	EXIT_FUNC;
}


ThreadedObject::~ThreadedObject()
{
	ENTER_FUNC;
	stop();

	DELETE(m_osThread);
	EXIT_FUNC;
}

void ThreadedObject::main()
{
	ENTER_FUNC;
	EXIT_FUNC;
}

uint32_t ThreadedObject::getSchedulerDelay()
{
	ENTER_FUNC;
	if (!m_prevCall)
	{
		m_prevCall = Tools_GETTICKS();
	}
	uint32_t currentTime = Tools_GETTICKS();
	uint32_t result = currentTime - m_prevCall;
	m_prevCall = currentTime;
	EXIT_FUNC;
	return result;
}

void ThreadedObject::resetSchedulerDelayCounter()
{
	ENTER_FUNC;
	m_prevCall = 0;
	EXIT_FUNC;
}

uint32_t ThreadedObject::getSchedulerDelay(uint32_t* context)
{
	ENTER_FUNC;
	if (!context)
	{
		ERROR("NULL context passed to getSchedulerDelay()\n");
		EXIT_FUNC;
		return 0;
	}
	if (!*context)
	{
		*context = Tools_GETTICKS();
	}
	uint32_t currentTime = Tools_GETTICKS();
	uint32_t result = currentTime - *context;
	*context = currentTime;
	EXIT_FUNC;
	return result;
}
void ThreadedObject::resetSchedulerDelayCounter(uint32_t* context)
{
	ENTER_FUNC;
	if (!context)
	{
		EXIT_FUNC;
		return;
	}
	*context = 0;
	EXIT_FUNC;
}

void ThreadedObject::setNextCallMicroSec(uint32_t next_call)
{
	ENTER_FUNC;
	m_microSleep = next_call;
	EXIT_FUNC;
}

void ThreadedObject::setNextCallMilliSec(uint32_t next_call)
{
	ENTER_FUNC;
	/** MilliSeconds **/
	m_microSleep = next_call * 1000;
	EXIT_FUNC;
}

void ThreadedObject::start()
{
	ENTER_FUNC;
	m_StateLock.lock();
	if(STOPPED == m_State)
	{
		m_State = STARTING;
		m_osThread->start(this);
	}
	m_StateLock.unlock();
	EXIT_FUNC;
}

void ThreadedObject::stop()
{
	ENTER_FUNC;
	m_StateLock.lock();

	if(STARTING == m_State)
	{
		m_StateLock.wait(false);
	}
	if(STARTED == m_State)
	{
		m_State = STOPPING;
		m_StateLock.unlock();
		m_CanDelete.lock();
		m_CanDelete.unlock();
		m_osThread->release();
	}
	else
	{
		// Stopping from another thread
		m_StateLock.unlock();
		m_CanDelete.lock();
		m_CanDelete.unlock();
	}
	EXIT_FUNC;
}

bool ThreadedObject::isRunning()
{
	ENTER_FUNC;
	bool lRunnning = false;
	m_StateLock.lock();
	lRunnning = ((STARTED == m_State )?true:false);
	m_StateLock.unlock();
	EXIT_FUNC;
	return lRunnning;
}

void ThreadedObject::cancel()
{
	ENTER_FUNC;
	stop();
	EXIT_FUNC;
}




void ThreadedObject::usleep(uint32_t delay)
{
	PortingLayer_usleep(delay);
}

void ThreadedObject::msleep(uint32_t delay)
{
	PortingLayer_usleep(delay*1000);
}

void ThreadedObject::onExit()
{
}



void ThreadedObject::internalRun()
{
	ENTER_FUNC;
	m_CanDelete.lock();
	m_StateLock.lock();
	m_State = STARTED;
	m_StateLock.wakeUp(false);
	m_StateLock.unlock();
	m_StateLock.lock();
	while (STARTED == m_State)
	{
		m_StateLock.unlock();
		main();
		
		if (m_microSleep)
		{
			PortingLayer_usleep(m_microSleep);
		}
		m_StateLock.lock();
	}
	m_StateLock.unlock();

	onExit();

	m_StateLock.lock();
	m_State = STOPPED;
	m_StateLock.unlock();
	m_CanDelete.unlock();
	EXIT_FUNC;
}





#include "RunnablePoster.h"

#include "core/Runnable.h"

#define VERBOSE_TAG "RunnablePoster"
#include "core/Verbose.h"

RunnablePoster::RunnablePoster()
{
	m_isDeleted = false;
	m_isBusy    = false;
	start();
}

RunnablePoster::~RunnablePoster()
{
	m_lock.lock();
	m_isDeleted = true;
	uint32_t size = m_runnableList.size();
	
	if (size == 0)
	{
		m_lock.wakeUp(false);
	}
	
	m_lock.unlock();
	while(size)
	{
		m_lock.lock();
		size = m_runnableList.size();
		m_lock.unlock();
		ThreadedObject::msleep(10);
	}
	stop();
}

void RunnablePoster::post(Runnable* ref)
{
	m_lock.lock();
	if (m_isDeleted)
	{
		m_lock.unlock();
		return;
	}
	m_lockBusy.lock();
	m_isBusy = true;
	m_lockBusy.unlock();
	m_runnableList.add(ref);
	m_lock.unlock();
	m_lock.wakeUp();

}

void RunnablePoster::main()
{
	
	// Lock
	m_lock.lock();
		
	if (m_runnableList.size() == 0)
	{
		m_lock.wait(false);
	}
	
	while(m_runnableList.size())
	{
		m_toRun.add(m_runnableList.remove(0));
	}
	m_lock.unlock();
	
	m_lockToRun.lock();
	while(m_toRun.size())
	{
		Runnable *r = (Runnable*)m_toRun.remove(0);
		m_lockToRun.unlock();
		m_lockBusy.lock();
		m_isBusy = true;
		m_lockBusy.unlock();
		r->run();
		delete r;
		m_lockToRun.lock();
	}
	m_lockToRun.unlock();
	m_lockBusy.lock();
	m_isBusy = false;
	
	if (m_isDeleted)
	{
		stop();
	}
	
	m_lockBusy.unlock();
}

bool RunnablePoster::isBusy()
{
	bool isBusy = true;
	
	m_lockBusy.lock();
	isBusy = m_isBusy;
	m_lockBusy.unlock();
	return isBusy;
}

void RunnablePoster::abort()
{
	m_lock.lock();
	m_runnableList.clear();
	m_lock.unlock();
	m_lockToRun.lock();
	while(m_toRun.size())
	{
		Runnable *r = (Runnable*)m_toRun.remove(0);
		delete r;
	}
	m_lockToRun.unlock();
}

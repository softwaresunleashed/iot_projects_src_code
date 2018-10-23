#include "OSSemaphore.h"

OSSemaphore::OSSemaphore()
{
	m_counter = 0;
}


OSSemaphore::~OSSemaphore()
{
}

void OSSemaphore::wait()
{
	m_lock.lock();
	m_counter++;
	if (m_counter>0)
	{
		m_lock.wait(false);
	}
	m_lock.unlock();
}

void OSSemaphore::post()
{
	m_lock.lock();
	bool needWakeUp = false;
	if (m_counter > 0)
	{
		needWakeUp = true;
	}
	m_counter--;
	
	if (needWakeUp)
	{
		m_lock.wakeUp(false);
	}
	m_lock.unlock();
}




#include "Locker.h"
#include "ThreadedObject.h"
#include "OSThread.h"

#include "OSLocker.h"

Locker::Locker()
{
	m_oslocker = NEW(OSLocker());
	m_isLocked = false;
	m_isAslept = false;
}


Locker::~Locker()
{
	DELETE(m_oslocker);
}

void Locker::lock()
{
	m_oslocker->lock();
	m_isLocked = true;
}

void Locker::unlock()
{
	m_isLocked = false;
	m_oslocker->unlock();
}


AutoLocker::AutoLocker(Locker & locker)
{
	m_locker = &locker;
	m_locker->lock();
}

AutoLocker::~ AutoLocker()
{
	if (m_locker)
	{
		m_locker->unlock();
	}
}

void AutoLocker::detach()
{
	if (m_locker)
	{
		m_locker->unlock();
	}
	m_locker = NULL;
}

void Locker::wait(bool needLock)
{
	if (needLock)
	{
		lock();
	}

	m_isAslept = true;
	m_oslocker->wait(false);
	m_isAslept = false;

	if (needLock)
	{
		unlock();
	}
}

void Locker::wakeUp(bool needLock)
{
	if (needLock)
	{
		lock();
	}

	m_oslocker->wakeUp(false);

	if (needLock)
	{
		unlock();
	}
}







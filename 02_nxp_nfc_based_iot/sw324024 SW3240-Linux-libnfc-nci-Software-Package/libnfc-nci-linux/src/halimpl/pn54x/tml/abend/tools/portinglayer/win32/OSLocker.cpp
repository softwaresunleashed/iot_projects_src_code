#include "OSLocker.h"

#include <windows.h>
#include <process.h>

OSLocker::OSLocker(bool isRec)
{
	m_handle = CreateMutex(NULL,false,NULL);
	m_cond   = CreateEvent(NULL,true,false,NULL); 
	ResetEvent(m_cond);
}


OSLocker::~OSLocker()
{
	CloseHandle(m_handle);
	CloseHandle(m_cond);
	m_handle = NULL;
	m_cond = NULL;
}

void OSLocker::lock()
{
	DWORD result = WaitForSingleObject(m_handle,INFINITE);
	if (result != 0)
	{
		DWORD i = GetLastError();
		i = 0;
	}
}

void OSLocker::unlock()
{
	bool result = ReleaseMutex(m_handle);
	if (!result)
	{
		DWORD i = GetLastError();
		i = 0;
	}
}

void OSLocker::wait(bool needLock)
{
	if (needLock)
	{
		lock();
	}
	DWORD result = SignalObjectAndWait(m_handle,m_cond,INFINITE,false);
	// FIXME : Need to relock again !
	// Relock !
	lock();
	
	if (result != 0)
	{
		DWORD i = GetLastError();
		i = 0;


	}
	ResetEvent(m_cond);
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
	SetEvent(m_cond);
	if (needLock)
	{
		unlock();
	}
}




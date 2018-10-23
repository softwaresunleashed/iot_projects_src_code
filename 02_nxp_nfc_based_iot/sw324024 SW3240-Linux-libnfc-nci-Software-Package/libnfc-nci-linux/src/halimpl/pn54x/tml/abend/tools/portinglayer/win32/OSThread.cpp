#include "OSThread.h"

/** Windows header **/
#include <windows.h>
#undef DELETE

#include "core/ThreadedObject.h"

/** Structure to handle thread informations **/
struct tWinThread
{
	DWORD dwThreadId;
	HANDLE hThread;
};

// DWORD WINAPI Thread_win32(LPVOID ref)
unsigned long __stdcall Thread_win32(void* ref)
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
	tWinThread * winThread = (tWinThread*)m_threadHandle;

	if (!winThread)
	{
		return;
	}

	if (winThread->hThread)
	{
		CloseHandle(winThread->hThread);
		winThread->hThread = NULL;
	}
	_free(m_threadHandle);
}

void OSThread::start(ThreadedObject * t)
{
	m_threadHandle = _malloc(sizeof(tWinThread));
	memset(m_threadHandle,0,sizeof(tWinThread));
	
	tWinThread * winThread = (tWinThread*)m_threadHandle;

	m_thread = t;
	
	winThread->hThread = CreateThread(
				     NULL,
				     0,
				     Thread_win32,
				     this,
				     0,
				     &(winThread->dwThreadId));
}

void OSThread::internalRun()
{
	m_thread->internalRun();
}

uint32_t OSThread::getCurrentThreadId()
{
	return GetCurrentThreadId();
}

uint32_t OSThread::getThreadId()
{
	tWinThread * winThread = (tWinThread*)m_threadHandle;
	// return GetThreadId(winThread->hThread);
	return winThread->dwThreadId;
}




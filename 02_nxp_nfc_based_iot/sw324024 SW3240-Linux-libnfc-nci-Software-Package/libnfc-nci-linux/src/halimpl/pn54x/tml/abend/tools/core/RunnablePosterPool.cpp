#include "RunnablePosterPool.h"

RunnablePosterPool::RunnablePosterPool()
{
	m_isAbort = false;
}


RunnablePosterPool::~RunnablePosterPool()
{
	AutoLocker      al(m_lock);
	m_isAbort = true;
	
	RunnablePoster *scan   = NULL;
	while(m_threadContainer.size()>0)
	{
		scan = (RunnablePoster*)m_threadContainer.remove(0);
		DELETE(scan);
	}
}

void RunnablePosterPool::postRunnable(Runnable* r)
{
	RunnablePoster *p = acquirePoster();
	if (p)
	{
		p->post(r);
		releasePoster(p);
	}
}


RunnablePoster* RunnablePosterPool::acquirePoster()
{
	AutoLocker      al(m_lock);
	RunnablePoster *result = NULL;
	RunnablePoster *scan   = NULL;
	
	if (m_isAbort)
	{
		return NULL;
	}
	
	// Scan if a Runnable is not busy ...
	for (uint32_t i = 0;i < m_threadContainer.size();i++)
	{
		scan = (RunnablePoster*)m_threadContainer.get(i);
		// Is it busy ?
		if (!scan->isBusy())
		{
			// Remove it from list ...
			m_threadContainer.remove(i);
			// ... and return it to caller.
			return scan;
		}
	}
	
	// None of Runnable Poster are available.
	// Create a new one !
	result = new RunnablePoster();
	
	return result;
	
}


void RunnablePosterPool::releasePoster(RunnablePoster* posterToRelease)
{
	AutoLocker al(m_lock);
	// put RunnablePoster into pool.
	m_threadContainer.add(posterToRelease);
}

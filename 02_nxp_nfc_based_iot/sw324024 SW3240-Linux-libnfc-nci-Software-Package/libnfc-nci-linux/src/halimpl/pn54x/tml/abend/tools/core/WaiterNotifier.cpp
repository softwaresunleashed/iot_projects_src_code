/*
 * WaiterNotifier.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: paul
 */

#include "WaiterNotifier.h"

WaiterNotifier::WaiterNotifier()
{
	m_state = NONE;
}

WaiterNotifier::~WaiterNotifier()
{
}

void WaiterNotifier::wait(bool needLock)
{
	if(needLock)
	{
		lock();
	}

	if(m_state == NONE)
	{
		m_state = WAITING;
		wait(false);
	}
	else if(m_state == NOTIFIED)
	{
		//already notified -> exit
	}
	else
	{
		//Waiting: Not expected state
	}

	m_state = NONE;

	if(needLock)
	{
		unlock();
	}
}

void WaiterNotifier::notify(bool needLock)
{
	if(needLock)
	{
		lock();
	}

	if(m_state == WAITING)
	{
		m_state = NOTIFIED;
		wakeUp(false);
	}
	else if(m_state == NONE)
	{
		//already notified -> exit
		m_state = NOTIFIED;
	}
	else
	{
		//notified: Not expected state
	}

	if(needLock)
	{
		unlock();
	}
}

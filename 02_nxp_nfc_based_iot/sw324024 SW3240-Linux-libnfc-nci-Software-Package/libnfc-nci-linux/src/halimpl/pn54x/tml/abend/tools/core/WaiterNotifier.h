/*
 * WaiterNotifier.h
 *
 *  Created on: Jun 16, 2014
 *      Author: paul
 */

#ifndef WAITERNOTIFIER_H
#define WAITERNOTIFIER_H

#include "Locker.h"

class WaiterNotifier : private Locker
{
public:
	WaiterNotifier();
	~WaiterNotifier();

	void notify(bool needLock);
	void wait(bool needLock);

private:
	enum eState
	{
		NONE,
		WAITING,
		NOTIFIED
	};

	eState m_state;
};



#endif /* WAITERNOTIFIER_H */

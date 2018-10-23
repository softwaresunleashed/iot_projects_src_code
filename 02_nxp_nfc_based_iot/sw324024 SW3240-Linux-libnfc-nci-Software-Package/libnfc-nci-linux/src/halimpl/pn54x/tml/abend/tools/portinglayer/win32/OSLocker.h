#ifndef OSLOCKER_H
#define OSLOCKER_H

#include <stdint.h>

/**
 @author Charles GORAND <charles.gorand@effinnov.com>
*/
class OSLocker
{
	public:
		OSLocker(bool isRec=false);
		~OSLocker();
		
		void lock();
		void unlock();
		
		void wait(bool needLock=true);
		void wakeUp(bool needLock=true);

	private:
		void *m_handle;
		void *m_cond;
};

#endif

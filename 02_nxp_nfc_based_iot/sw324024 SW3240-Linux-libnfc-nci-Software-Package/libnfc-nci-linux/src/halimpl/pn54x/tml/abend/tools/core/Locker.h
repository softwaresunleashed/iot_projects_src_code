
#ifndef LOCKER_H
#define LOCKER_H

/**
 * This class allows to use mutexes.
 * It also allows to lock a Thread, and wake up it later.
 */
class OSLocker;
class Locker
{
	public:
		/**
		 *               Ctrs
		 */
		Locker();
		virtual ~Locker();

		/**
		 *               Lock the mutex
		 */
		virtual void lock();
		/**
		 *               Unlock the mutex
		 */
		virtual void unlock();

		/**
		 *               Is the mutex is Locked ?
		 * @return true/false
		 */
		inline bool isLocked()
		{
			return m_isLocked;
		}

		virtual void wait(bool needLock=true);

		virtual void wakeUp(bool needLock=true);

		inline bool isAslept()
		{
			return m_isAslept;
		}


	private:
		OSLocker *m_oslocker;
		bool      m_isLocked;
		bool      m_isAslept;
};

/**
 * Helper class : Allows to lock/unlock a mutex
 * into an intruction bloc.
 * Ex :
 * void f()
 * {
 * 	AutoLocker al(m_myLocker);
 *	// After here m_myLocker is locked
 * 	if (cond)
 * 	{
 * 		// When f() will returned
 * 		// m_myLocker will be unlocked
 * 		return;
 * 	}
 * 	// When f() will returned
 * 	// m_myLocker will be unlocked
 * }
 */
class AutoLocker
{
	public:

		AutoLocker(Locker &locker);
		virtual ~AutoLocker();

		/**
		 *               Unlock the locker.
		 *               After this, the locker will never be modified
		 */
		void detach();

	private:
		Locker  *m_locker;
};

#endif

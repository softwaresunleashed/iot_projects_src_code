
#ifndef RunnablePoster_H
#define RunnablePoster_H

#include "core/Locker.h"
#include "core/ThreadedObject.h"
#include "core/Container.h"


class Runnable;
/** **/
class RunnablePoster: public ThreadedObject
{
	public:
		RunnablePoster();
		virtual ~RunnablePoster();
	
		/**
		 *              Post a Runnable to be excuted in background.
		 * @param ref Pointer on Runnable to run. Ownership is transfered to this object.
		 */
		void post(Runnable *ref);
		
		/**
		 *              Indicate if RunnablePoster has Runnables or if it is running somes.
		 * @return true if there is some runnables.
		 */
		bool isBusy();
		void abort();

	protected:
		virtual void main();
	
	private:
		Locker    m_lock;
		Container m_runnableList;
		Locker 	  m_lockToRun;
		Container m_toRun;
		
		Locker    m_lockBusy;
		bool      m_isBusy;
		bool      m_isDeleted;
};

#endif // ndef RunnablePoster_H



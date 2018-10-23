#ifndef RUNNABLEPOSTERPOOL_H
#define RUNNABLEPOSTERPOOL_H

#include "core/Locker.h"
#include "core/RunnablePoster.h"
#include "core/Runnable.h"
#include "core/Container.h"
/** This class allows to execute Runnables. Any of Runnables can be blocking,
 *  this class will automatically create new RunnablePoster if needed.
 *  NOTE : Posted Runnables may not be executed in the same order that they were posted.
**/
class RunnablePosterPool
{
	public:
		RunnablePosterPool();
		virtual ~RunnablePosterPool();
		
		/**
		 *                Post a Runnable into RunnablePosterPool. The Runnable will be
		 *                released automattically when job is completed. The Runnable
		 *                will be executed as soon as possible even if previous posted
		 *                Runnable are blocking their RunnablePoster, a new RunnablePoster
		 *                is spawn.
		 * @param r Runnable to run.
		 */
		void postRunnable(Runnable *r);
		
	private:
		RunnablePoster *acquirePoster();
		void releasePoster(RunnablePoster *posterToRelease);
	private:
		Container m_threadContainer;
		Locker    m_lock;
		bool      m_isAbort;
};

#endif // RUNNABLEPOSTERPOOL_H

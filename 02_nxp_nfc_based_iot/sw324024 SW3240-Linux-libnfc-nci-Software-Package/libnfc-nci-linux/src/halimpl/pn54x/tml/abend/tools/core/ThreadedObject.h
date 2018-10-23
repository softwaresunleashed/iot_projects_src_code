

#ifndef THREADEDOBJECT_H
#define THREADEDOBJECT_H

#include "core/Locker.h"
#include "core/Types.h"
#include "core/Defines.h"
#include "core/Allocators.h"

/**
 * This class allows to execute code in a separate Thread.
 * The only difference with classic Thread is that
 * the function main() is called like this :
 * while(Running)
 * {
 * 	main();
 * 	sleep();
 * }
 * This behavior allows to a real thread can process
 * severals ThreadedObject at a time :
 * while(Running)
 * {
 * 	thread1->main();
 * 	thread2->main();
 * 	[...]
 * 	sleep();
 * }
 */
class OSThread;
class ThreadedObject
{
	friend class OSThread;
	protected:

		/**
		 *               Start the Thread.
		 */
		void start();

		/**
		 *               Stop the Thread. This function can
		 *               be called inside or outside the Thread.
		 */
		void stop();

		/**
		 *               Thread Main function.
		 *               The implementation of this function
		 *               will be executed in a separate Thread.
		 *               This function should give back hand as
		 *               soon as possible. It will be called again
		 *               depending on setNextCallXXX() function.
		 */
		virtual void main();


		/**
		 *               Called before the Thread exit.
		 */
		virtual void onExit();

		/**
		 *               Set the delay between main() called function in Micro seconds.
		 *               This delay is an informative delay.(= not real time)
		 * @param next_call delay in µs.
		 */
		void setNextCallMicroSec(uint32_t next_call);
		/**
		 *               Set the delay between main() called function in Milli seconds.
		 *               This delay is an informative delay.(= not real time)
		 * @param next_call delay in ms.
		 */
		void setNextCallMilliSec(uint32_t next_call);

		// Helper function to mesure latency for main() calls.
		uint32_t getSchedulerDelay();
		void resetSchedulerDelayCounter();


		uint32_t getSchedulerDelay(uint32_t *context);
		void resetSchedulerDelayCounter(uint32_t *context);

	public:
		ThreadedObject();
		virtual ~ThreadedObject();

		/**
		 *               Is the Thread is running ?
		 * @return
		 */
		bool isRunning();

		/**
		 *               Abort a Thread. The thread will exit after main()
		 *               function returned.
		 */
		void cancel();

		/**
		 *               Sleep current Thread for delay µs.
		 * @param delay delay in µs
		 */
		static void usleep(uint32_t delay);

		/**
		 *               Sleep current Thread for delay ms.
		 * @param delay delay in ms
		 */
		static void msleep(uint32_t delay);

	private:
		void internalRun();
		
	private:
		enum eState
		{
			STOPPED,
			STOPPING,
			STARTING,
			STARTED
		};
		OSThread *m_osThread;
		uint32_t  m_microSleep;

		eState  m_State;
		Locker m_StateLock;
		Locker m_CanDelete;

		// **** Schedule delay
		uint32_t  m_prevCall;
};


#endif

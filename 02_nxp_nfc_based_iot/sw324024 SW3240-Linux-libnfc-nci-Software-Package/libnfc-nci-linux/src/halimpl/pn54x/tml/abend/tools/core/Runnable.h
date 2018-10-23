
#ifndef Runnable_H
#define Runnable_H

#include "core/Types.h"

/** **/
class Runnable
{
	public:
		Runnable();
		 virtual ~Runnable();
	
	protected:
		friend class RunnablePoster;
		virtual void run() = 0;

	private:
};
#endif // ndef Runnable_H



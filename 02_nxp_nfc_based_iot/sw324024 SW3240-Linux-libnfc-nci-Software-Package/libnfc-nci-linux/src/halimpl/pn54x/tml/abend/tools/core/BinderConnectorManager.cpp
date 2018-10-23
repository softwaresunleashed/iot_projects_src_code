#include "BinderConnectorManager.h"

#include "OSBinderConnector.h"

#define VERBOSE_TAG "BinderConnectorManager"
#include "core/Verbose.h"

BinderConnectorManager::BinderConnectorManager(const char* url)
{
	m_isDelete         = false;
	m_nbRunnablePosted = 0;
	m_listener         = NULL;
	m_binderConnector  = NEW(OSBinderConnector(url));
	m_tryConnect       = true;
	m_discNotified     = false;
	m_errorFlag        = false;
	m_isWaiting        = false;
	start();
}


BinderConnectorManager::~BinderConnectorManager()
{
	m_isDelete = true;
	m_binderConnector->disconnect();
	stop();
	
	// Wait that all Runnable are executed...
	// NOTE : Useless if using counter references ...
	m_lLock.lock();
	while(m_nbRunnablePosted>0)
	{
		m_lLock.wait(false);
	}
	m_lLock.unlock();
	
	DELETE(m_binderConnector);
}

void BinderConnectorManager::main()
{
	if (m_isDelete)
	{
		return;
	}
	
	if (!m_binderConnector->isConnectedToProvider())
	{
		bool res = m_binderConnector->connect();
		
		m_tryConnect = false;
		
		if (!res)
		{
			// Wait
			setNextCallMilliSec(100);
			// WARN("BinderConnectorManager :  can't connect\n");
			if (!m_discNotified)
			{
				m_discNotified = true;
				if (m_listener)
				{
					ConnectionRunnable *r = NEW(ConnectionRunnable(this,false));
					m_lLock.lock();
					m_nbRunnablePosted++;
					// Avoid deadlock
					m_poster.postRunnable(r);
					m_lLock.unlock();
				}
			}
		}else
		{
			// Connected !
			m_discNotified = false;
			setNextCallMilliSec(0);
			
			ConnectionRunnable *r = NEW(ConnectionRunnable(this,true));
			m_lLock.lock();
			m_nbRunnablePosted++;
			// Avoid deadlock
			m_poster.postRunnable(r);
			m_lLock.unlock();
		}
	}else
	{
		bool result = m_binderConnector->readData(m_readParcel);
		
		if (result)
		{
			uint8_t token = m_readParcel.readByte();
			
			if (token == REQUEST_TOKEN)
			{
				m_requestLock.lock();
				// Skip token
				m_writeParcel.deserialize(m_readParcel);
				m_requestLock.wakeUp(false);
				m_requestLock.unlock();
			}
			
			if (token == UNEXPECTED_MESSAGE_TOKEN)
			{
				if (m_listener != NULL)
				{
					Parcel *p = NEW(Parcel());
					// Skip token
					p->deserialize(m_readParcel);
					UnsolicitedRunnable *r = NEW(UnsolicitedRunnable(this,p));
					m_lLock.lock();
					m_nbRunnablePosted++;
					// Avoid deadlock
					m_poster.postRunnable(r);
					m_lLock.unlock();
				}
			}
		}else
		{
			// Error 
			m_requestLock.lock();
			m_errorFlag = true;
			if (m_isWaiting)
			{
				m_requestLock.wakeUp(false);
			}
			m_requestLock.unlock();
		}
	}
	
}

bool BinderConnectorManager::sendDataAndReadResult(Parcel & p)
{
	while (m_tryConnect)
	{
		ThreadedObject::msleep(10);
	}
	
	if (!m_binderConnector->isConnectedToProvider())
	{
		return false;
	}
	
	// Lock any concurent access !
	m_concurencyLock.lock();
	
	// Lock wait/answer access.
	m_requestLock.lock();
	
	m_writeParcel.clear();
	
	m_errorFlag = false;
	
	m_binderConnector->sendData(p);
	
	// Wait answer
	m_isWaiting = true;
	m_requestLock.wait(false);
	m_isWaiting = false;
	
	if(m_errorFlag == false)
	{
		p.setData(m_writeParcel.getData(),m_writeParcel.getSize());
		m_requestLock.unlock();
		m_concurencyLock.unlock();
		return true;
	}

	m_requestLock.unlock();
	m_concurencyLock.unlock();
	return false ;
}

void BinderConnectorManager::setUnsolicitedListener(BinderConnectorManagerListener * ptr)
{
	m_lLock.lock();
	m_listener = ptr;
	m_lLock.unlock();
}

BinderConnectorManager::UnsolicitedRunnable::UnsolicitedRunnable(BinderConnectorManager *b,Parcel *p)
{
	m_ptr = b;
	m_p   = p;
}

void BinderConnectorManager::UnsolicitedRunnable::run()
{
	if ((m_ptr)&&(m_p))
	{
		m_ptr->onMessage(*m_p);
		DELETE(m_p);
	}
}

void BinderConnectorManager::onMessage(const Parcel & p)
{
	if (m_listener)
	{
		m_listener->onMessage(p);
	}
	
	m_lLock.lock();
	// Called by Runnable.
	m_nbRunnablePosted--;
	if (m_nbRunnablePosted == 0)
	{
		m_lLock.wakeUp(false);
	}
	
	m_lLock.unlock();
}

BinderConnectorManager::ConnectionRunnable::ConnectionRunnable(BinderConnectorManager * b, bool onOff)
{
	m_ptr    = b;
	m_status = onOff;
}

void BinderConnectorManager::ConnectionRunnable::run()
{
	if ((m_ptr)&&(m_ptr->m_listener))
	{
		if (m_status)
		{
			m_ptr->m_listener->onConnect();
		}else
		{
			m_ptr->m_listener->onDisconnect();
		}
		m_ptr->m_lLock.lock();
		// Called by Runnable.
		m_ptr->m_nbRunnablePosted--;
		if (m_ptr->m_nbRunnablePosted == 0)
		{
			m_ptr->m_lLock.wakeUp(false);
		}
	
		m_ptr->m_lLock.unlock();
	}
}



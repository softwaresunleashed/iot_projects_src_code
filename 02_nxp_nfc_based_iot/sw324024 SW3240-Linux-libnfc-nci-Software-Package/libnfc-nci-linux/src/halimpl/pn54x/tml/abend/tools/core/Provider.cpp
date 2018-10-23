#include "Provider.h"

#include "core/ClientProviderManager.h"
#include "core/RunnablePoster.h"
#include "core/Runnable.h"

#define VERBOSE_TAG "Provider"
#include "core/Verbose.h"

class RunnableNotifyClient : public Runnable
{
	public :
		RunnableNotifyClient(void* handle,const Parcel &p,Provider *pr)
		{
			m_handle = handle;
			m_parcel.setData(p.getData(),p.getSize());
			m_provider = pr;
		}
		
	protected:
		virtual void run()
		{
			m_provider->notifyClientInternal(m_handle,m_parcel);
		}
	private:
		Parcel    m_parcel;
		void     *m_handle;
		Provider *m_provider;
};

class RunnableNotifyAllClient : public Runnable
{
	public :
		RunnableNotifyAllClient(const Parcel &p,Provider *pr)
		{
			m_parcel.setData(p.getData(),p.getSize());
			m_provider = pr;
		}
		
	protected:
		virtual void run()
		{
			m_provider->notifyClientAllInternal(m_parcel);
		}
	private:
		Parcel    m_parcel;
		Provider *m_provider;
};

Provider::Provider(const char* url)
{
	m_url = _strdup(url);
	
	m_runnablePoster = NEW(RunnablePoster());
	
	m_clientProviderManager = NEW(ClientProviderManager(this));
	
	m_listening = false;
}


Provider::~Provider()
{
	m_lock.lock();
	if (m_listening)
	{
		FATAL("Call disconnectClients() first !\n");
	}
	m_lock.unlock();
	
	DELETE(m_runnablePoster);
	
	DELETE(m_clientProviderManager);
	_free(m_url);
}

void Provider::acceptClients()
{
	m_lock.lock();
	if (!m_listening)
	{
		m_listening = true;
		m_clientProviderManager->startListening();
	}
	m_lock.unlock();
}

void Provider::disconnectClients()
{
	m_lock.lock();
	if (m_listening)
	{
		m_listening = false;
		m_clientProviderManager->stopListening();
	}
	m_lock.unlock();
}


void Provider::notifyAllClient(const Parcel &p)
{
	// m_clientProviderManager->notifyAllClient(p);
	Runnable *r = NEW(RunnableNotifyAllClient(p,this));
	m_runnablePoster->post(r);
}

void Provider::notifyClient(void * handle,const Parcel &p)
{
	// m_clientProviderManager->notifyClient(handle,p);
	Runnable *r = NEW(RunnableNotifyClient(handle,p,this));
	m_runnablePoster->post(r);
}

void Provider::notifyClientAllInternal(const Parcel & p)
{
	m_clientProviderManager->notifyAllClient(p);
}

void Provider::notifyClientInternal(void * handle, const Parcel & p)
{
	m_clientProviderManager->notifyClient(handle,p);
}



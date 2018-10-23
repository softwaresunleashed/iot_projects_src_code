#include "Binder.h"

class BinderUnsolListener : public BinderConnectorManager::BinderConnectorManagerListener
{
	public:
		BinderUnsolListener(Binder *b)
		{
			m_b = b;
		}
	protected:
		virtual void onMessage(const Parcel &p)
		{
			m_b->onMessage(p);
		}
		
		virtual void onConnect()
		{
			m_b->onConnect();
		}
		virtual void onDisconnect()
		{
			m_b->onDisconnect();
		}
		
	private:
		Binder *m_b;
};

Binder::Binder(const char* url):m_binderConnectorManager(url)
{
	m_listener = NEW(BinderUnsolListener(this));
	m_binderConnectorManager.setUnsolicitedListener(m_listener);
}


Binder::~Binder()
{
	m_binderConnectorManager.setUnsolicitedListener(NULL);
	DELETE(m_listener);
}

void Binder::onMessage(const Parcel & p)
{
	// Nothing to do by default !
}

bool Binder::sendDataAndReadResult(Parcel & p)
{
	return m_binderConnectorManager.sendDataAndReadResult(p);
}

void Binder::onConnect()
{
	// Nothing to do by default !
}

void Binder::onDisconnect()
{
	// Nothing to do by default !
}





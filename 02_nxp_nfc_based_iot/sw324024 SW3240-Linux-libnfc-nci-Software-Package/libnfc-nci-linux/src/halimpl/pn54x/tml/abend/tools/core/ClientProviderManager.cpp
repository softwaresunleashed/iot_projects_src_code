#include "ClientProviderManager.h"

#include "core/Provider.h"

#include "OSProviderConnector.h"

#define VERBOSE_TAG "ClientProviderManager"
#include "core/Verbose.h"

ClientProviderManager::ClientProviderManager(Provider *p)
{
	m_serverConnector = NULL;
	m_providerRef     = p;
	m_shouldStop      = false;
}


ClientProviderManager::~ClientProviderManager()
{
	stopListening();
}

void ClientProviderManager::startListening()
{
	if (!m_serverConnector)
	{
		m_serverConnector = NEW(OSProviderConnector(m_providerRef->m_url))
	}
	m_shouldStop = false;
	start();
}

void ClientProviderManager::stopListening()
{
	// Shutdown connection
	m_lock.lock();
	if (m_serverConnector)
	{
		LOG(">>>>>>>>>>>>>>> Disconnect\n");
		m_serverConnector->disconnect();
	}
	m_shouldStop = true;
	m_lock.unlock();
	
	stop();
	
	Client *scan = NULL;
	
	// Remove all clients.
	m_lock.lock();
	while(m_clientList.size())
	{
		scan = (Client*)m_clientList.remove(0);
		m_lock.unlock();
		DELETE(scan);
		m_lock.lock();
	}
	while(m_flushList.size())
	{
		scan = (Client*)m_flushList.remove(0);
		m_lock.unlock();
		m_lock.lock();
		DELETE(scan);
	}
	m_lock.unlock();
	DELETE(m_serverConnector);
}

void ClientProviderManager::main()
{
	m_lock.lock();
	if (m_shouldStop)
	{
		setNextCallMilliSec(10);
		m_lock.unlock();
		return;
	}
	m_lock.unlock();
	
	ProviderConnector *newConnector = NEW(OSProviderConnector(m_providerRef->m_url));
	LOG(">>>>>>>>>>>>>>> Accept\n");
	bool result = m_serverConnector->accept(*newConnector);
	LOG(">>>>>>>>>>>>>>> Accept result : %X\n",result);
	if (!result)
	{
		DELETE(newConnector);
	}else
	{
		// Client connection succeed
		// Spawning client handler.
		Client *c = NEW(Client(newConnector,this));
		m_lock.lock();
		m_clientList.add(c);
		m_providerRef->onClientConnect(c);
		m_lock.unlock();
	}
}

void ClientProviderManager::onClientRequest(void *handle,const Parcel & inParcel, Parcel & outParcel)
{
	m_lock.lock();
	m_providerRef->onClientRequest(handle,inParcel,outParcel);
	m_lock.unlock();
}

void ClientProviderManager::onClientDisconnect(void * ptr)
{
	m_lock.lock();
	Client *c = (Client*)m_clientList.removePtr(ptr);
	m_providerRef->onClientDisconnect(c);
	// Cannot delete client now as it may still running.
	m_flushList.add(c);
	m_lock.unlock();
}

void ClientProviderManager::notifyClient(void * handle, const Parcel & p)
{
	// NOTE: Even if handle == Client* we force rescan
	// in case client does not exists any more.
	Client *scan = NULL;
	m_lock.lock();
	for (uint32_t i = 0; i < m_clientList.size();i++)
	{
		scan = (Client*)m_clientList.get(i);
		if (scan == handle)
		{
			scan->notifyClient(p);
		}
	}
	m_lock.unlock();
}

void ClientProviderManager::notifyAllClient(const Parcel & p)
{
	Client *scan = NULL;
	m_lock.lock();
	for (uint32_t i = 0; i < m_clientList.size();i++)
	{
		scan = (Client*)m_clientList.get(i);
		scan->notifyClient(p);
	}
	m_lock.unlock();
}

ClientProviderManager::Client::Client(ProviderConnector * connector,ClientProviderManager *mgr)
{
	m_connector        = connector;
	m_clientManagerRef = mgr;
	start();
}

ClientProviderManager::Client::~ Client()
{
	m_connector->disconnect();
	stop();
	m_clientManagerRef = NULL;
	DELETE(m_connector);
}

void ClientProviderManager::Client::notifyClient(const Parcel & p)
{
	if (m_connector->isBinderConnected())
	{
		m_lock.lock();
		m_tempParcel.clear();
		m_tempParcel.writeByte(UNEXPECTED_MESSAGE_TOKEN);
		p.serialize(m_tempParcel);
		m_connector->sendData(m_tempParcel);
		m_lock.unlock();
	}
}

void ClientProviderManager::Client::main()
{
	bool result = m_connector->readData(m_inParcel);
	
	if (!result)
	{
		// Disconnected !
		m_clientManagerRef->onClientDisconnect(this);
		stop();
		return;
	}
	
	m_outParcel.clear();
	
	if (m_inParcel.getSize() > 0)
	{
		m_clientManagerRef->onClientRequest(this,m_inParcel,m_outParcel);
	}
	
	m_lock.lock();
	
	m_tempParcel.clear();
	m_tempParcel.writeByte(REQUEST_TOKEN);
	m_outParcel.serialize(m_tempParcel);
	m_connector->sendData(m_tempParcel);
	m_lock.unlock();
	
}











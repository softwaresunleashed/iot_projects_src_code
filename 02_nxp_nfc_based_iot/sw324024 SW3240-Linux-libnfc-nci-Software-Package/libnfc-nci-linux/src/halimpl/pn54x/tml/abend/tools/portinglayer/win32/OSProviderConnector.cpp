#include "OSProviderConnector.h"

#include "SocketConnection.h"

#define VERBOSE_TAG "OSProviderConnector"
#include "core/Verbose.h"


OSProviderConnector::OSProviderConnector(const char* url)
{
	m_sock = NEW(SocketConnection());
	m_isClient = false;
	m_isBound  = false;
	
}


OSProviderConnector::~OSProviderConnector()
{
	disconnect();
	DELETE(m_sock);
}

bool OSProviderConnector::accept(ProviderConnector & pc)
{
	if (!m_isBound)
	{
		SocketConnection::eRetCode result = m_sock->bind(14256);
		if (result == SocketConnection::SUCCESS)
		{
			result = m_sock->listen();
			if (result == SocketConnection::SUCCESS)
			{
				m_isBound = true;
			}else
			{
				ERROR("OSProviderConnector : Cannot listen  !\n");
			}
		}else
		{
			ERROR("OSProviderConnector : Cannot bind  !\n");
		}
	}
	
	OSProviderConnector *osPc = (OSProviderConnector*)&pc;
	SocketConnection::eRetCode ret = m_sock->accept(*(osPc->m_sock));
	
	if (ret != SocketConnection::SUCCESS)
	{
		return false;
	}
	
	osPc->m_isClient = true;
	return true;
}

void OSProviderConnector::disconnect()
{
	m_sock->close();
	m_isClient = false;
}

bool OSProviderConnector::sendData(const Parcel & p)
{
	uint32_t size = p.getSize();
	SocketConnection::eRetCode ret = m_sock->sendData((uint8_t*)&size,4);
	if (ret != SocketConnection::SUCCESS)
	{
		disconnect();
		return false;
	}
	
	ret = m_sock->sendData(p.getData(),p.getSize());
	if (ret != SocketConnection::SUCCESS)
	{
		disconnect();
		return false;
	}
	
	return true;
}

bool OSProviderConnector::readData(Parcel & p)
{
	uint32_t size = 0;
	uint32_t readBytes = 0;
	SocketConnection::eRetCode ret = m_sock->readData((uint8_t*)&size,4,readBytes);
	if (ret != SocketConnection::SUCCESS)
	{
		disconnect();
		return false;
	}
	
	uint8_t *data = (uint8_t*)_malloc(size);
	ret = m_sock->readData(data,size,readBytes);
	
	if (ret != SocketConnection::SUCCESS)
	{
		_free(data);
		disconnect();
		return false;
	}
	
	p.setData(data,size);
	_free(data);
	
	return true;
}

bool OSProviderConnector::isBinderConnected()
{
	return m_isClient;
}



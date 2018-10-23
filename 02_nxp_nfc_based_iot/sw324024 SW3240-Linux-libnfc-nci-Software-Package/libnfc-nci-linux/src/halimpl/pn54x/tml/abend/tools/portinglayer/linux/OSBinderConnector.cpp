#include "OSBinderConnector.h"
#include "SocketConnection.h"

OSBinderConnector::OSBinderConnector(const char* url):BinderConnector(url)
{
	m_sock        = NEW(SocketConnection());
	m_isConnected = false;
	m_url         = _strdup(url);
}


OSBinderConnector::~OSBinderConnector()
{
	disconnect();
	_free(m_url);
	DELETE(m_sock);
}

bool OSBinderConnector::connect()
{
	SocketConnection::eRetCode ret = m_sock->connect(m_url,14256);
	if (ret != SocketConnection::SUCCESS)
	{
		return false;
	}
	m_isConnected = true;
	return true;
}

void OSBinderConnector::disconnect()
{
	m_sock->close();
	m_isConnected = false;
}

bool OSBinderConnector::sendData(const Parcel & p)
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

bool OSBinderConnector::readData(Parcel & p)
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

bool OSBinderConnector::isConnectedToProvider()
{
	return m_isConnected;
}



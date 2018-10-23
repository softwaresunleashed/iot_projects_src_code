#include "OSBroadCastMessage.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "core/Allocators.h"

OSBroadCastMessage::OSBroadCastMessage()
{
	m_socket = -1;
	sockaddr_in *addr = (sockaddr_in*)_malloc(sizeof(sockaddr_in));
	m_addr = addr;

}

OSBroadCastMessage::~OSBroadCastMessage()
{
	close();
	_free(m_addr);
}

OSBroadCastMessage::eRetCode OSBroadCastMessage::connect(const char* host, uint16_t port)
{
	
	if ((m_socket=socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		return OSBroadCastMessage::CANNOT_CONNECT;
	}
	
	memset(m_addr,0,sizeof(sockaddr_in));
	((sockaddr_in*)m_addr)->sin_family=AF_INET;
	((sockaddr_in*)m_addr)->sin_addr.s_addr=inet_addr(host);
	((sockaddr_in*)m_addr)->sin_port=htons(port);
}


OSBroadCastMessage::eRetCode OSBroadCastMessage::close()
{
	if (m_socket == -1)
	{
		// Nothing opened
		return OSBroadCastMessage::SUCCESS;
	}
	
	::shutdown(PTR2UINT(m_socket),SHUT_RDWR);
	::close(m_socket);
	return OSBroadCastMessage::SUCCESS;
}

OSBroadCastMessage::eRetCode OSBroadCastMessage::bind(uint16_t port)
{
	sockaddr_in *addr = (sockaddr_in*)m_addr;
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(port);

	m_socket = ::socket(AF_INET, SOCK_DGRAM , 0);
	
	if (m_socket == -1)
	{
		return OSBroadCastMessage::CANNOT_BIND;
	}

	int on = 1;

	setsockopt(PTR2UINT(m_socket), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	int result = ::bind(PTR2UINT(m_socket),(struct sockaddr *)addr,sizeof(sockaddr_in));


	if ( result == -1 )
	{
		return OSBroadCastMessage::CANNOT_BIND;
	}


	return OSBroadCastMessage::SUCCESS;
}



OSBroadCastMessage::eRetCode OSBroadCastMessage::readData(uint8_t* outBuffer, uint32_t length, uint32_t& readByte)
{
	if (m_socket == -1)
	{
		return OSBroadCastMessage::NOT_CONNECTED;
	}
}


OSBroadCastMessage::eRetCode OSBroadCastMessage::sendData(const uint8_t* buffer, uint32_t length)
{
	if (m_socket == -1)
	{
		return OSBroadCastMessage::NOT_CONNECTED;
	}
	
	if (sendto(m_socket,buffer,length,0,(struct sockaddr *) m_addr,sizeof(sockaddr_in)) < 0) 
	{
	       return OSBroadCastMessage::CANNOT_SEND;
	}
}


#include "SocketConnection.h"



#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
       
#include "core/Allocators.h"

#define VERBOSE_TAG "SocketConnection"
#include "core/Verbose.h"

SocketConnection::SocketConnection(eMode mode)
{
	m_socket = -1;
	sockaddr_in *addr = (sockaddr_in*)_malloc(sizeof(sockaddr_in));
	m_addr = addr;
	m_mode = mode;
}

SocketConnection::~SocketConnection()
{
	close();
	_free(m_addr);
}

SocketConnection::eRetCode SocketConnection::connect(const char * host, unsigned short port)
{
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	struct hostent * hp=NULL;

	int type = SOCK_STREAM;
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(host) ;
	server.sin_port = htons(port);

	if (server.sin_addr.s_addr == INADDR_NONE)
	{
		hp = gethostbyname(host);
	}

	if (hp)
	{
		char* addr = inet_ntoa(*(struct in_addr*)hp->h_addr_list[0]);
		server.sin_addr.s_addr = inet_addr(addr) ;
	}

	if (m_mode == SocketConnection::UDP)
	{
		type = SOCK_DGRAM;
	}
	
	m_socket = socket(AF_INET, type , 0);
	if (m_socket == -1)
	{
		return SocketConnection::CANNOT_CONNECT;
	}
	
	int result = ::connect(m_socket, (struct sockaddr*) & server, sizeof(sockaddr_in));
	if (result == -1)
	{
		this->close();
		return SocketConnection::CANNOT_CONNECT;
	}
// 	fcntl(m_socket, F_SETFL, O_NONBLOCK);

// WIN32
	// Set socket to non blocking mode
/*	unsigned long ioctl_opt = 1;
	if (ioctlsocket(m_socket, FIONBIO, &ioctl_opt) == SOCKET_ERROR)
	{
		return SocketConnection::CANNOT_CONNECT;
	}*/
	return SocketConnection::SUCCESS;
}

SocketConnection::eRetCode SocketConnection::close()
{
	if (m_socket == -1)
	{
		// Nothing opened
		return SocketConnection::SUCCESS;
	}
	
	::shutdown(PTR2UINT(m_socket),SHUT_RDWR);
	::close(m_socket);
	return SocketConnection::SUCCESS;
}

SocketConnection::eRetCode SocketConnection::sendData(const uint8_t* buffer, uint32_t length)
{
	if (m_socket == -1)
	{
		return SocketConnection::NOT_CONNECTED;
	}

	if (!buffer)
	{
		return SocketConnection::INVALID_PARAM;
	}

	int result = -1;
	int tosend = length;
	int sent = 0 ;

	while (tosend)
	{
		if (m_mode == SocketConnection::TCP)
		{
			result = send(m_socket, buffer + sent, tosend, MSG_NOSIGNAL);
		}else
		{
			result = sendto(m_socket, buffer + sent, tosend, MSG_NOSIGNAL,NULL,0);
		}
//WIN32
// 		result = send(PTR2UINT(m_socket), (const char*)buffer + sent, tosend, 0);

		if (result == -1)
		{
			return CANNOT_SEND;
		}
		tosend -= result ;
		sent += result ;
	}
	return SocketConnection::SUCCESS;
}

SocketConnection::eRetCode SocketConnection::readData(uint8_t* outBuffer, uint32_t length, unsigned int & readByte)
{
	readByte = 0;

	if (m_socket == -1)
	{
		return SocketConnection::NOT_CONNECTED;
	}

	if (!outBuffer)
	{
		return SocketConnection::INVALID_PARAM;
	}

	int result;
	
	if (m_mode == SocketConnection::TCP)
	{
		result = recv(m_socket, outBuffer, length, MSG_NOSIGNAL|MSG_WAITALL);
	}else 
	{
		result = recvfrom(m_socket, outBuffer, length, MSG_NOSIGNAL,NULL,NULL);
	}

//WIN32
// 	result = recv(PTR2UINT(m_socket),(char*) outBuffer, length, 0);


	if (result == -1)
	{
		if (errno == EAGAIN)
		{
			return SocketConnection::NO_DATA_IN_STREAM;
		}
// 		int lastErr = WSAGetLastError();
//WIN32
// 		if (WSAGetLastError() == WSAEWOULDBLOCK)
// 		{
// 			return SocketConnection::NO_DATA_IN_STREAM;
// 		}
		return SocketConnection::UNKNOWN_ERROR;
	}

	if (result == 0)
	{
		return SocketConnection::NOT_CONNECTED;
	}

	readByte = result;

	return SocketConnection::SUCCESS;

}

SocketConnection::eRetCode SocketConnection::bind(uint16_t port,const char* multiAddr)
{
	sockaddr_in *addr = (sockaddr_in*)m_addr;
	int type = SOCK_STREAM;
	
	if (m_mode == SocketConnection::UDP)
	{
		type = SOCK_DGRAM;
	}
	
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(port);
	

	m_socket = ::socket(AF_INET, type , 0);
	
	if (m_socket == -1)
	{
		return SocketConnection::CANNOT_BIND;
	}

	int on = 1;

	setsockopt(PTR2UINT(m_socket), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	int result = ::bind(PTR2UINT(m_socket),(struct sockaddr *)addr,sizeof(sockaddr_in));


	if ( result == -1 )
	{
		return SocketConnection::CANNOT_BIND;
	}

	if ((m_mode == SocketConnection::UDP) && (multiAddr))
	{
		struct ip_mreq mreq;
		mreq.imr_multiaddr.s_addr=inet_addr(multiAddr);
		mreq.imr_interface.s_addr=htonl(INADDR_ANY);
		if (setsockopt(m_socket,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) 
		{
			perror(0);
			return SocketConnection::CANNOT_BIND;
		}
	}
	

	return SocketConnection::SUCCESS;
}

SocketConnection::eRetCode SocketConnection::listen()
{
	if (m_socket == -1)
	{
		return SocketConnection::CANNOT_LISTEN;
	}
	
	if (m_mode == SocketConnection::UDP)
	{
		return SocketConnection::INVALID_MODE;
	}
	
	int result = ::listen(m_socket, 64);

	if (result == -1)
	{
		return SocketConnection::CANNOT_LISTEN;
	}


	return SocketConnection::SUCCESS;
}

SocketConnection::eRetCode SocketConnection::accept(SocketConnection &socketInterface)
{
	if (m_socket == -1)
	{
		return SocketConnection::NOT_CONNECTED;
	}
	
	if (m_mode == UDP)
	{
		return SocketConnection::INVALID_MODE;
	}
	
	
	SocketConnection *socket = (SocketConnection*)&socketInterface;
	socklen_t length = sizeof(sockaddr);
	
	int newSocket = ::accept(m_socket,(sockaddr*)m_addr,&length);

	if (newSocket <= 0)
	{
		return SocketConnection::CANNOT_CONNECT;
	}

	socket->m_socket = newSocket;

	return SocketConnection::SUCCESS;
}

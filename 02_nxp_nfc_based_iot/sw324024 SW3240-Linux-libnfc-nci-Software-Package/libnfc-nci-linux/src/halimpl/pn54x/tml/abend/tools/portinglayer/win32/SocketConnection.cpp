
#include "SocketConnection.h"



#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

#include <winsock.h>

#undef DELETE
#undef ERROR
#include "core/Allocators.h"

#define VERBOSE_TAG "SocketConnection"
#include "core/Verbose.h"

class Initiator
{
	public :
		Initiator()
		{
			WORD wVersionRequested;
			WSADATA wsaData;
			int err;

			/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
			wVersionRequested = MAKEWORD(2, 2);

			err = WSAStartup(wVersionRequested, &wsaData);
			if (err != 0) 
			{
				/* Tell the user that we could not find a usable */
				/* Winsock DLL.                                  */
				ERROR("WSAStartup failed with error: %d\n", err);
				return ;
			}
		}
};

static Initiator init;

SocketConnection::SocketConnection()
{
	m_socket = (void*)-1;
	sockaddr_in *addr = (sockaddr_in*)_malloc(sizeof(sockaddr_in));
	m_addr = addr;
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

	m_socket = (void*)socket(AF_INET, SOCK_STREAM , 0);
	if (m_socket == (void*)-1)
	{
		return SocketConnection::CANNOT_CONNECT;
	}
	
	int result = ::connect((SOCKET)m_socket, (struct sockaddr*) & server, sizeof(sockaddr_in));
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
	if (m_socket == (void*)-1)
	{
		// Nothing opened
		return SocketConnection::SUCCESS;
	}
//WIN32
	::closesocket((SOCKET)m_socket);

// 	::close(m_socket);
	return SocketConnection::SUCCESS;
}

SocketConnection::eRetCode SocketConnection::sendData(const uint8_t* buffer, uint32_t length)
{
	if (m_socket == (void*)-1)
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
// 		result = send(m_socket, buffer + sent, tosend, MSG_NOSIGNAL);
//WIN32
		result = send((SOCKET)m_socket, (const char*)buffer + sent, tosend, 0);

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

	if (m_socket == (void*)-1)
	{
		return SocketConnection::NOT_CONNECTED;
	}

	if (!outBuffer)
	{
		return SocketConnection::INVALID_PARAM;
	}

	int result;
// 	result = recv(m_socket, outBuffer, length, MSG_NOSIGNAL);

//WIN32
	result = recv((SOCKET)m_socket,(char*) outBuffer, length, 0);


	if (result == -1)
	{
		if (errno == EAGAIN)
		{
			return SocketConnection::NO_DATA_IN_STREAM;
		}
		int lastErr = WSAGetLastError();
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

SocketConnection::eRetCode SocketConnection::bind(uint16_t port)
{
	sockaddr_in *addr = (sockaddr_in*)m_addr;
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(port);

	m_socket = (void*)::socket(AF_INET, SOCK_STREAM , 0);
	
	if (m_socket == (void*)-1)
	{
		return SocketConnection::CANNOT_BIND;
	}

	char on = 1;

	setsockopt((SOCKET)m_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	int result = ::bind((SOCKET)m_socket,(struct sockaddr *)addr,sizeof(sockaddr_in));


	if ( result == -1 )
	{
		return SocketConnection::CANNOT_BIND;
	}


	return SocketConnection::SUCCESS;
}

SocketConnection::eRetCode SocketConnection::listen()
{
	if (m_socket == (void*)-1)
	{
		return SocketConnection::CANNOT_LISTEN;
	}
	
	int result = ::listen((SOCKET)m_socket, 64);

	if (result == -1)
	{
		return SocketConnection::CANNOT_LISTEN;
	}


	return SocketConnection::SUCCESS;
}

SocketConnection::eRetCode SocketConnection::accept(SocketConnection &socketInterface)
{
	if (m_socket == (void*)-1)
	{
		return SocketConnection::NOT_CONNECTED;
	}
	
	
	SocketConnection *socket = (SocketConnection*)&socketInterface;
	int length = sizeof(sockaddr);
	void* newSocket = (void*)::accept((SOCKET)m_socket,(sockaddr*)&m_addr,&length);
	int err = WSAGetLastError();
    if (err > 0)
	{
		return SocketConnection::CANNOT_CONNECT;
	}

	socket->m_socket = newSocket;

	return SocketConnection::SUCCESS;
}


#ifndef SocketConnection_H
#define SocketConnection_H

#include "core/Types.h"



/** **/
class SocketConnection
{
	private:
		void      *m_socket;
		void      *m_addr;

	public:
		enum eRetCode
		{
			SUCCESS,
			CANNOT_CONNECT,
			CANNOT_SEND,
			NOT_CONNECTED,
			NO_DATA_IN_STREAM,
			INVALID_PARAM,
			CANNOT_BIND,
			CANNOT_LISTEN,
			UNKNOWN_ERROR
		};

		SocketConnection();
		virtual ~SocketConnection();

		virtual eRetCode connect(const char* host, unsigned short port);

		virtual eRetCode close();

		virtual eRetCode sendData(const uint8_t* buffer, uint32_t length);

		virtual eRetCode readData(uint8_t* outBuffer, uint32_t length, uint32_t &readByte);

		virtual eRetCode bind(uint16_t port);

		virtual eRetCode listen();

		virtual eRetCode accept(SocketConnection &socketInterface);

};

#endif // ndef SocketConnection_H



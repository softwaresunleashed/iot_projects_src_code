
#ifndef SocketConnection_H
#define SocketConnection_H

#include "core/Types.h"



/** **/
class SocketConnection
{
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
			INVALID_MODE,
			UNKNOWN_ERROR
		};
		
		enum eMode
		{
			TCP,
			UDP
		};
		

		SocketConnection(eMode mode=TCP);
		virtual ~SocketConnection();

		virtual eRetCode connect(const char* host, unsigned short port);

		virtual eRetCode close();

		virtual eRetCode sendData(const uint8_t* buffer, uint32_t length);

		virtual eRetCode readData(uint8_t* outBuffer, uint32_t length, uint32_t &readByte);

		virtual eRetCode bind(uint16_t port,const char* multiAddr=0);

		virtual eRetCode listen();

		virtual eRetCode accept(SocketConnection &socketInterface);
		
		
	private:
		int        m_socket;
		void      *m_addr;
		eMode      m_mode;

	

};

#endif // ndef SocketConnection_H



#ifndef OSBROADCASTMESSAGE_H
#define OSBROADCASTMESSAGE_H

#include "core/Types.h"

class OSBroadCastMessage
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
			UNKNOWN_ERROR
		};
		
		OSBroadCastMessage();
		virtual ~OSBroadCastMessage();
		
		eRetCode connect(const char* host, uint16_t port);
		
		eRetCode bind(uint16_t port);
		
		eRetCode sendData(const uint8_t* buffer, uint32_t length);

		eRetCode readData(uint8_t* outBuffer, uint32_t length, uint32_t &readByte);
		
		eRetCode close();
		
	private:
		int        m_socket;
		void      *m_addr;


		
};

#endif // OSBROADCASTMESSAGE_H

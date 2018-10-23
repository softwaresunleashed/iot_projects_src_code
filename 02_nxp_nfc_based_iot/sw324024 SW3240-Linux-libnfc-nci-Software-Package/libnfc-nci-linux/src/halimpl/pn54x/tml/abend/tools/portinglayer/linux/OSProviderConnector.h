#ifndef OSPROVIDERCONNECTOR_H
#define OSPROVIDERCONNECTOR_H

#include "core/ProviderConnector.h"

/**
 @author Charles GORAND <charles.gorand@effinnov.com>
*/
class SocketConnection;
class OSProviderConnector: public ProviderConnector
{
	public:
		OSProviderConnector(const char* url);

		~OSProviderConnector();

		bool accept(ProviderConnector &pc);
		void disconnect();
		bool sendData(const Parcel &p);
		bool readData(Parcel &p);
		bool isBinderConnected();
		
	private:
		SocketConnection *m_sock;
		bool              m_isClient;
		bool              m_isBound;
};

#endif

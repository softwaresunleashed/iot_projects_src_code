#ifndef OSBINDERCONNECTOR_H
#define OSBINDERCONNECTOR_H

#include "core/BinderConnector.h"

/**
 @author Charles GORAND <charles.gorand@effinnov.com>
*/
class SocketConnection;
class OSBinderConnector : public BinderConnector
{
	public:
		OSBinderConnector(const char* url);
		~OSBinderConnector();
		
		
		virtual bool connect();
		virtual void disconnect();
	
		virtual bool sendData(const Parcel &p);
		virtual bool readData(Parcel &p);
		virtual bool isConnectedToProvider();

	private:
		SocketConnection *m_sock;
		bool              m_isConnected;
		char*             m_url;
};

#endif

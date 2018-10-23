#ifndef BINDERCONNECTOR_H
#define BINDERCONNECTOR_H

#include "core/Parcel.h"

/**
 @author Charles GORAND <charles.gorand@effinnov.com>
*/
class BinderConnector
{
	public:
		BinderConnector(const char* url);
		virtual ~BinderConnector();
		
		virtual bool connect() = 0;
		virtual void disconnect() = 0;
	
		virtual bool sendData(const Parcel &p) = 0;
		virtual bool readData(Parcel &p) = 0;
		virtual bool isConnectedToProvider() = 0;

};

#endif

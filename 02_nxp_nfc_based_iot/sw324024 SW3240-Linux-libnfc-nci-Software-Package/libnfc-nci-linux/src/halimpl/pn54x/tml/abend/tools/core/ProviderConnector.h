#ifndef PROVIDERCONNECTOR_H
#define PROVIDERCONNECTOR_H

#include "core/Parcel.h"

/**
 @author Charles GORAND <charles.gorand@effinnov.com>
*/
class ProviderConnector
{
	public:
		ProviderConnector();

		~ProviderConnector();

		virtual bool accept(ProviderConnector &pc) = 0;
		virtual void disconnect() = 0;
		virtual bool sendData(const Parcel &p) = 0;
		virtual bool readData(Parcel &p) = 0;
		virtual bool isBinderConnected() = 0;
};

#endif

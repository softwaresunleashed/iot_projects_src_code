
#ifndef PROVIDER_H
#define PROVIDER_H

#include "core/Parcel.h"
#include "core/Locker.h"

/**
 @author Charles GORAND <charles.gorand@effinnov.com>
*/
class ClientProviderManager;
class RunnablePoster;
class Provider
{
	public:
		Provider(const char* url);
		~Provider();
	
	protected:
		friend class ClientProviderManager;
		friend class RunnableNotifyClient;
		friend class RunnableNotifyAllClient;
	
	protected:
		void acceptClients();
		void disconnectClients();
		
	protected:
		virtual void onClientRequest(void *handle,const Parcel & inParcel, Parcel & outParcel) = 0;
		virtual void onClientConnect(void *handle) = 0;
		virtual void onClientDisconnect(void *handle) = 0;
		
		void notifyAllClient(const Parcel &p);
		void notifyClient(void *handle,const Parcel &p);
		
	private:
		void notifyClientInternal(void *handle,const Parcel &p);
		void notifyClientAllInternal(const Parcel &p);
		
	private:
		ClientProviderManager *m_clientProviderManager;
		char*                  m_url;
		RunnablePoster        *m_runnablePoster;
		bool                   m_listening;
		
		Locker                 m_lock;

};

#endif

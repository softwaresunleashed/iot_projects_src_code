#ifndef CLIENTPROVIDERMANAGER_H
#define CLIENTPROVIDERMANAGER_H

#include "core/ThreadedObject.h"
#include "core/ProviderConnector.h"
#include "core/Locker.h"
#include "core/Container.h"

/**
 @author Charles GORAND <charles.gorand@effinnov.com>
 Internal Class.
*/
class Provider;
class ClientProviderManager : public ThreadedObject
{
	public:
		ClientProviderManager(Provider *p);
		virtual ~ClientProviderManager();

	protected:
		virtual void main();

	private:
		friend class Provider;

	private:
		void startListening();
		void stopListening();

		void onClientRequest(void* handle,const Parcel &inParcel, Parcel &outParcel);
		void onClientDisconnect(void *ptr);

		void notifyClient(void *handle, const Parcel &p);
		void notifyAllClient(const Parcel &p);

	private:
		ProviderConnector *m_serverConnector;
		Provider          *m_providerRef;
		Container          m_clientList;
		Container          m_flushList;
		Locker             m_lock;
		bool               m_shouldStop;

	private:
	class Client : public ThreadedObject
		{
			public:
				Client(ProviderConnector *connector, ClientProviderManager *mgr);
				virtual ~Client();

				void notifyClient(const Parcel &p);

				enum eToken
				{
					REQUEST_TOKEN = 0xCD,
					UNEXPECTED_MESSAGE_TOKEN = 0xFF
				};

			protected:
				virtual void main();

			private:
				ProviderConnector     *m_connector;
				ClientProviderManager *m_clientManagerRef;
				Parcel                 m_inParcel;
				Parcel                 m_outParcel;
				Parcel                 m_tempParcel;
				Locker                 m_lock;
		};


};

#endif

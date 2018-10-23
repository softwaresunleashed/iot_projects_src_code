#ifndef BINDERCONNECTORMANAGER_H
#define BINDERCONNECTORMANAGER_H

#include "core/ThreadedObject.h"
#include "core/BinderConnector.h"
#include "core/RunnablePoster.h"
#include "core/RunnablePosterPool.h"
#include "core/Runnable.h"

/**
 @author Charles GORAND <charles.gorand@effinnov.com>
*/
class BinderConnectorManager: public ThreadedObject
{
	public:
		BinderConnectorManager(const char* url);
		~BinderConnectorManager();
	
	protected:
		virtual void main();
	
	public:
		friend class BinderUnsolListener;
		class BinderConnectorManagerListener
		{
			protected:
				friend class BinderConnectorManager;
				virtual void onConnect() = 0;
				virtual void onDisconnect() = 0;
				virtual void onMessage(const Parcel &p) = 0;
		};
	private:
		class UnsolicitedRunnable : public Runnable
		{
			public:
				UnsolicitedRunnable(BinderConnectorManager *b,Parcel *p);
			protected:
				virtual void run();
			private:
				BinderConnectorManager *m_ptr;
				Parcel                 *m_p;
		};
		
		class ConnectionRunnable : public Runnable
		{
			public:
				ConnectionRunnable(BinderConnectorManager *b,bool onOff);
			protected:
				virtual void run();
			private:
				BinderConnectorManager *m_ptr;
				bool                    m_status;
		};
		
	private:
		friend class Binder;
		bool sendDataAndReadResult(Parcel &p);
		void setUnsolicitedListener(BinderConnectorManagerListener *ptr);
		void onMessage(const Parcel &p);
	private:
		enum eToken
		{
			REQUEST_TOKEN = 0xCD,
			UNEXPECTED_MESSAGE_TOKEN = 0xFF
		};
		
	private:
		BinderConnector     *m_binderConnector;
		Parcel               m_readParcel;
		Parcel               m_writeParcel;
		RunnablePosterPool   m_poster;
		
		Locker               m_requestLock;
		Locker               m_concurencyLock;
		Locker               m_lLock;
		
		bool                 m_isDelete;
		uint32_t             m_nbRunnablePosted;
		
		bool                 m_tryConnect;
		
		BinderConnectorManagerListener *m_listener;
		bool                 m_connectNotified;
		bool                 m_discNotified;
		bool                 m_errorFlag;
		bool                 m_isWaiting;

};

#endif

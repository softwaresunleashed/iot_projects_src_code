#ifndef BINDER_H
#define BINDER_H

#include "core/Parcel.h"
#include "core/BinderConnectorManager.h"
/**
 @author Charles GORAND <charles.gorand@effinnov.com>
 This class allows to implement Interprocess communication
*/
class Binder
{
	public:
		Binder(const char* url);
		~Binder();
	
	protected:
		bool sendDataAndReadResult(Parcel &p);
		
	protected:
		friend class BinderUnsolListener;
		
		/**
		 *               Called when a message is coming from Provider.
		 * @param p Parcel containing message.
		 */
		virtual void onMessage(const Parcel &p);
		/**
		 *               Called when connection is established with Provider.
		 */
		virtual void onConnect();
		/**
		 *               Called when connection is lost with Provider.
		 */
		virtual void onDisconnect();
	
	private:
		BinderConnectorManager                                          m_binderConnectorManager;
		BinderConnectorManager::BinderConnectorManagerListener *m_listener;
};

#endif

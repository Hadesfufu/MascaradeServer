#include "ConnectionManager.h"
#include "ConnectionTCP.h"
#include "ConnectionWebSocket.h"


ConnectionManager::ConnectionManager()
{

}


void ConnectionManager::init(){
	sf::Socket::Status status = m_TCPlistener.listen(m_TCPlisteningPort);
	if (status != sf::Socket::Status::Done)
		Log::error("ConnectionManager::ConnectionManager") << "Error while listening " << status;
	else
		Log::info("ConnectionManager::ConnectionManager") << "TCP listener live on :" << m_TCPlistener.getLocalPort();

	status = m_WebSocketlistener.listen(m_WebSocketlisteningPort);
	if (status != sf::Socket::Status::Done)
		Log::error("ConnectionManager::WebSocketlisteningThreadFunction") << "Error while listening " << status;
	else
		Log::info("ConnectionManager::ConnectionManager") << "WebSocket listener live on :" << m_WebSocketlistener.getLocalPort();
	
	m_SocketSelector.add(m_TCPlistener);
	m_SocketSelector.add(m_WebSocketlistener);
}

ConnectionManager::~ConnectionManager()
{
}

void ConnectionManager::addTCP()
{
	Log::info("ConnectionManager::addTCP") << "Adding TCP Connection";
	Connection* connection = new ConnectionTCP();
	sf::Socket::Status status = connection->acceptFrom(m_TCPlistener);
	if (status != sf::Socket::Done)
	{
		Log::error("ConnectionManager::TCPlisteningThreadFunction") << "Error while listening " << status;
		return;
	}
	connection->addToSelector(m_SocketSelector);
	m_connections.push_back(connection);
}

void ConnectionManager::addWebSocket()
{
	Log::info("ConnectionManager::addWebSocket") << "Adding WebSocket Connection";
	Connection* connection = new ConnectionWebSocket();
	sf::Socket::Status status = connection->acceptFrom(m_WebSocketlistener);
	if (status != sf::Socket::Done)
	{
		Log::error("ConnectionManager::WebSocketlisteningThreadFunction") << "Error while listening " << status;
		return;
	}
	connection->addToSelector(m_SocketSelector);
	m_connections.push_back(connection);
}

void ConnectionManager::update()
{
	Log::info("ConnectionManager::update") << "Waiting";
	if (m_SocketSelector.wait()) {
		if (m_SocketSelector.isReady(m_TCPlistener)) {
			addTCP();
		}
		else if (m_SocketSelector.isReady(m_WebSocketlistener)) {
			addWebSocket();
		}
		else {
			for (auto it = m_connections.begin(); it != m_connections.end();)
			{
				if ((*it)->isReady(m_SocketSelector)) {
					if ((*it)->receive().functionName == "disconnected")
					{
						m_messageHandler(*it);
						Log::debug() << "DELETING CONNECTION";
						(*it)->removeFromSelector(m_SocketSelector);
						it = m_connections.erase(it);
						continue;
					}
					else {
						m_messageHandler(*it);
					}
				}
				++it;
			}
		}
	}
}

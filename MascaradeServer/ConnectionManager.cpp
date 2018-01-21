#include "ConnectionManager.h"
#include "ConnectionTCP.h"
#include "ConnectionWebSocket.h"


ConnectionManager::ConnectionManager():
m_TCPlisteningThread(&ConnectionManager::TCPlisteningThreadFunction, this),
m_WebSocketlisteningThread(&ConnectionManager::WebSocketlisteningThreadFunction, this)
{
	m_TCPlistener.setBlocking(true);
	m_WebSocketlistener.setBlocking(true);
}

ConnectionManager::~ConnectionManager()
{
	m_TCPlisteningThread.terminate();
	m_WebSocketlisteningThread.terminate();
	Log::debug() << "Thread terminated";
}

void ConnectionManager::launchListeningThreads()
{
	m_TCPlisteningThread.launch();
	m_WebSocketlisteningThread.launch();
}

void ConnectionManager::TCPlisteningThreadFunction()
{
	Log::debug() << "TCP Thread listening";
	sf::Socket::Status status = m_TCPlistener.listen(m_TCPlisteningPort);
	if (status != sf::Socket::Status::Done)
		Log::error("ConnectionManager::TCPlisteningThreadFunction") << "Error while listening " << status;
	while (1)
	{
		Connection* connection = new ConnectionTCP();
		sf::Socket::Status status = connection->acceptFrom(m_TCPlistener);
		if (status != sf::Socket::Done)
		{
			Log::error("ConnectionManager::TCPlisteningThreadFunction") << "Error while listening " << status;
			return;
		}
		m_connectionsAccess.lock();
		m_connections.push_back(connection);
		m_connectionsAccess.unlock();
	}
}

void ConnectionManager::WebSocketlisteningThreadFunction()
{
	Log::debug() << "WebSocket Thread listening";
	sf::Socket::Status status = m_WebSocketlistener.listen(m_WebSocketlisteningPort);
	if (status != sf::Socket::Status::Done)
		Log::error("ConnectionManager::WebSocketlisteningThreadFunction") << "Error while listening " << status;

	while (1)
	{
		Connection* connection = new ConnectionWebSocket();
		sf::Socket::Status status = connection->acceptFrom(m_WebSocketlistener);
		if (status != sf::Socket::Done)
		{
			Log::error("ConnectionManager::WebSocketlisteningThreadFunction") << "Error while listening " << status;
			return;
		}
		m_connectionsAccess.lock();
		m_connections.push_back(connection);
		m_connectionsAccess.unlock();
	}
}

void ConnectionManager::checkReceive()
{
	//Log::debug() << m_connections.size();
	m_connectionsAccess.lock();
	for(auto it = m_connections.begin(); it != m_connections.end();)
	{
		if((*it)->receive().functionName == "disconnected")
		{
			m_messageHandler(*it);
			//Log::debug() << "DELETING CONNECTION";
			it = m_connections.erase(it);			
			continue;
		}
		else {
			m_messageHandler(*it);
		}
		++it;
	}
	m_connectionsAccess.unlock();
}

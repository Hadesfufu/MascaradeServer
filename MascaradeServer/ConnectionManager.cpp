#include "ConnectionManager.h"
#include "ConnectionTCP.h"


ConnectionManager::ConnectionManager():
m_listeningThread(&ConnectionManager::listeningThreadFunction, this)
{
	m_listener.setBlocking(true);
}

ConnectionManager::~ConnectionManager()
{
	m_listeningThread.terminate();
	Log::debug() << "Thread terminated";
}

void ConnectionManager::launchListeningThread()
{
	m_listeningThread.launch();
}

void ConnectionManager::listeningThreadFunction()
{
	Log::debug() << "Thread listening";
	sf::Socket::Status status = m_listener.listen(m_listeningPort);
	if(status != sf::Socket::Status::Done)
		Log::error("MascaradeServer") << "Error while listening " << status;
	while(1)
	{
		listen();
	}
}

void ConnectionManager::listen()
{
	Connection* connection = new ConnectionTCP();
	sf::Socket::Status status = connection->acceptFrom(m_listener);
	if (status != sf::Socket::Done)
	{
		Log::error("MascaradeServer") << "Error while listening " << status;
		return;
	}
	m_connectionsAccess.lock();
	m_connections.push_back(connection);
	m_connectionsAccess.unlock();
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

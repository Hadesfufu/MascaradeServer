#include "HTMLManager.h"



HTMLManager::HTMLManager()
:m_listeningThread(&HTMLManager::listeningThreadFunction, this)
{
}


HTMLManager::~HTMLManager()
{
}

void HTMLManager::listeningThreadFunction()
{
	Log::debug() << "Thread listening";
	sf::Socket::Status status = m_listener.listen(m_HTMLListeningPort);
	if (status != sf::Socket::Status::Done)
		Log::error("MascaradeServer") << "Error while listening " << status;
	while (1)
	{
		listen();
	}
}

void HTMLManager::listen()
{
	sf::TcpSocket* connection = new sf::TcpSocket();
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

#include "ConnectionManager.h"



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
	while(1)
	{
		listen();
	}
}

void ConnectionManager::listen()
{
	sf::Socket::Status status = m_listener.listen(m_listeningPort);
	if (status != sf::Socket::Done)
	{
		Log::error("MascaradeServer") << "Error while listening " << status;
		return;
	}

	m_connections.push_back(std::make_shared<Connection>());
	m_connections.back()->acceptFrom(m_listener);
}

void ConnectionManager::checkReceive()
{
	Log::debug() << m_connections.size();
	for(auto it = m_connections.begin(); it != m_connections.end(); ++it)
	{
		if (handleMessage((*it)->receive()) < 0)
			it = m_connections.erase(it);
	}
}

int ConnectionManager::handleMessage(std::string& s)
{
	if (s == "pass")
		return 0;
	else if (s == "disconnect")
		return -1;
	Log::debug("ConnectionManager-handleMessage") << s;
	return 0;
}

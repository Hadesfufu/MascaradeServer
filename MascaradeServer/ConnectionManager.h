////////////////////////////////////////////////////////////
// < Fichier : "ConnectionManager.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
#include "Singleton.h"
#include <vector>
#include "Connection.h"
#include <functional>

class ConnectionManager : public Singleton<ConnectionManager>
{
	friend class Singleton<ConnectionManager>;
public:

	void setListeningPort(int i) { m_listeningPort = i; }
	void launchListeningThread();

	void checkReceive();
	Connection* getConnection(int i) { if (m_connections.size() > i) return m_connections.at(i); else return nullptr; }

	void setMessageHandler(std::function<int(Connection*)> func) { m_messageHandler = func; }
private:
	ConnectionManager();
	~ConnectionManager();

	void listeningThreadFunction();
	void listen();

	std::vector<Connection*>					m_connections;
	std::function<int(Connection*)>				m_messageHandler;
	sf::TcpListener								m_listener;
	int											m_listeningPort;
	sf::Thread									m_listeningThread;
	sf::Mutex									m_connectionsAccess;
};

#endif
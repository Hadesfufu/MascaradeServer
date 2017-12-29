////////////////////////////////////////////////////////////
// < Fichier : "ConnectionManager.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H
#include "Singleton.h"
#include <vector>
#include "Connection.h"

class ConnectionManager : public Singleton<ConnectionManager>
{
	friend class Singleton<ConnectionManager>;
public:

	void setListeningPort(int i) { m_listeningPort = i; }
	void launchListeningThread();

	void checkReceive();
	Connection* getConnection(int i) { if (m_connections.size() > i) return m_connections.at(i).get(); else return nullptr; }
private:
	ConnectionManager();
	~ConnectionManager();

	int handleMessage(std::string& s);
	void listeningThreadFunction();
	void listen();

	std::vector<std::shared_ptr<Connection>>	m_connections;
	sf::TcpListener								m_listener;
	int											m_listeningPort;
	sf::Thread									m_listeningThread;
};

#endif
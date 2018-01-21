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

	void setTCPListeningPort(int i) { m_TCPlisteningPort = i; }
	void setWebSocketListeningPort(int i) { m_WebSocketlisteningPort = i; }

	void launchListeningThreads();

	void checkReceive();
	Connection* getConnection(int i) { if (m_connections.size() > i) return m_connections.at(i); else return nullptr; }

	void setMessageHandler(std::function<int(Connection*)> func) { m_messageHandler = func; }
private:
	ConnectionManager();
	~ConnectionManager();

	void TCPlisteningThreadFunction();

	void WebSocketlisteningThreadFunction();

	std::vector<Connection*>					m_connections;
	std::function<int(Connection*)>				m_messageHandler;

	sf::TcpListener								m_TCPlistener;
	int											m_TCPlisteningPort;
	sf::Thread									m_TCPlisteningThread;

	sf::TcpListener								m_WebSocketlistener;
	int											m_WebSocketlisteningPort;
	sf::Thread									m_WebSocketlisteningThread;

	sf::Mutex									m_connectionsAccess;
};

#endif
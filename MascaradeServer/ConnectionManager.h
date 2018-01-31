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

	void update();
	void init();
	Connection* getConnection(int i) { if (m_connections.size() > i) return m_connections.at(i); else return nullptr; }

	void setMessageHandler(std::function<int(Connection*)> func) { m_messageHandler = func; }
private:
	ConnectionManager();
	~ConnectionManager();

	void addTCP();
	void addWebSocket();

	std::vector<Connection*>					m_connections;
	std::function<int(Connection*)>				m_messageHandler;

	sf::TcpListener								m_TCPlistener;
	int											m_TCPlisteningPort;

	sf::TcpListener								m_WebSocketlistener;
	int											m_WebSocketlisteningPort;

	sf::SocketSelector							m_SocketSelector;
};

#endif
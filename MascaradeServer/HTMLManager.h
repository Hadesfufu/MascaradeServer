////////////////////////////////////////////////////////////
// < Fichier : "HTMLManager.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef HTMLMANAGER_H
#define HTMLMANAGER_H
#include "Singleton.h"
#include <SFML/Network/TcpListener.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>

class HTMLManager : public Singleton<HTMLManager>
{
	friend class Singleton<HTMLManager>;
public:
	HTMLManager();
	~HTMLManager();

	void launchListeningThread();

	void setListeningPort(int i) { m_HTMLListeningPort = i; }
private: 

	void listeningThreadFunction();
	void listen();

	sf::TcpListener				m_listener;
	int							m_HTMLListeningPort;
	std::vector<sf::TcpSocket>	m_sockets;

	sf::Thread					m_listeningThread;
	sf::Mutex					m_connectionsAccess;
};


#endif
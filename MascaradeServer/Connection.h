////////////////////////////////////////////////////////////
// < Fichier : "Connection.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef CONNECTION_H
#define CONNECTION_H
#include "Singleton.h"
#include <SFML/Network.hpp>

class Player;

class Connection 
{

public:


	struct Query
	{
		std::string functionName;
		std::map<std::string, std::string> parameters;
	};

	Connection();
	~Connection();

	void						connect(std::string address, int port);
	void						disconnect();
	virtual sf::Socket::Status	acceptFrom(sf::TcpListener& tl);
	
	virtual void		send(sf::Packet&) = 0;
	virtual Query&		receive() = 0;
	
	Query&				getQuery() { return m_query; }
	Player*				getPlayer() { return m_player; }

	int					getRemotePort() { return m_socket.getRemotePort(); }
	int					getRemoteAddress() { return m_socket.getRemoteAddress().getLocalAddress().toInteger(); }
	int					getLocalPort() { return m_socket.getLocalPort(); }

	void				addToSelector(sf::SocketSelector& selector) { selector.add(m_socket); }
	void				removeFromSelector(sf::SocketSelector& selector) { selector.remove(m_socket); }
	bool				isReady(sf::SocketSelector& selector) { return selector.isReady(m_socket); }

protected:

	void listening();
	
	Query						m_query;
	sf::TcpSocket				m_socket;
	Player*						m_player;
};

#endif
////////////////////////////////////////////////////////////
// < Fichier : "Connection.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef CONNECTION_H
#define CONNECTION_H
#include "Singleton.h"
#include <SFML/Network.hpp>

class Player;

struct Query
{
	std::string functionName;
	std::map<std::string,std::string> parameters;
};

class Connection 
{

public:
	Connection();
	~Connection();

	void				connect(std::string address, int port);
	void				disconnect();
	virtual sf::Socket::Status	acceptFrom(sf::TcpListener& tl);
	
	virtual void		send(sf::Packet&) = 0;
	virtual Query&		receive() = 0;
	
	Query&				getQuery() { return m_query; }
	Player*				getPlayer() { return m_player; }

protected:

	void listening();
	
	Query						m_query;
	sf::TcpSocket				m_socket;
	Player*						m_player;
};

#endif
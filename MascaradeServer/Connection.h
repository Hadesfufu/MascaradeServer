////////////////////////////////////////////////////////////
// < Fichier : "Connection.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef CONNECTION_H
#define CONNECTION_H
#include "Singleton.h"
#include <SFML/Network.hpp>

class Connection 
{

public:
	Connection();
	~Connection();

	void connect(std::string address, int port);
	void disconnect();
	void acceptFrom(sf::TcpListener& tl);

	void send(std::string string);

	void launchListening();
	std::string receive();
	
	int getRemotePort() { return m_socket.getRemotePort(); }
	int getLocalPort() { return m_socket.getLocalPort(); }
	std::string getAddress() { return m_socket.getRemoteAddress().toString(); }

private:

	void listening();
	void appendString(std::string& s, char* c, int nb);
	sf::TcpSocket				m_socket;

	static const std::string	eom;
};

#endif
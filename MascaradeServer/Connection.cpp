#include "Connection.h"
#include "Log.h"
#include "Player.h"

Connection::Connection()
{
	m_player = new Player(this);
}


Connection::~Connection()
{
	delete m_player;
}

void Connection::connect(std::string address, int port)
{
	if (m_socket.connect(address, port) != sf::Socket::Done)
	{
		Log::error("Connection") << "Error while listening";
	}
}

sf::Socket::Status Connection::acceptFrom(sf::TcpListener& tl)
{
	sf::Socket::Status status = tl.accept(m_socket);
	if (status != sf::Socket::Done)
		Log::error("Connection") << "Error while linking to client";
	return status;
}

void Connection::disconnect()
{
	m_socket.disconnect();
}

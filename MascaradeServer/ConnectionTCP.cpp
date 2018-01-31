#include "ConnectionTCP.h"



ConnectionTCP::ConnectionTCP()
{
}


ConnectionTCP::~ConnectionTCP()
{
}

Connection::Query& ConnectionTCP::receive()
{
	sf::Packet p;
	sf::Socket::Status status = m_socket.receive(p);
	if (status == sf::Socket::Disconnected)
	{
		Log::info("ConnectionTCP::receive") << "Disconnecting : ";
		m_query.functionName = "disconnected";
	}
	else if (status == sf::Socket::Error)
	{
		Log::error("ConnectionTCP::receive") << "Error" << status;
	}
	else if(status == sf::Socket::Done)
	{
		std::string s;
		if (p >> s)
			m_query.functionName = s;
		else
			Log::error("ConnectionTCP::receive") << "no function name";

		std::size_t delim;
		std::pair<std::string, std::string> input;
		while(p >> s)
		{
			delim = s.find(":");
			if(delim == std::string::npos)
			{
				Log::error("ConnectionTCP::receive") << "input is not complete : no \":\" found";
				break;
			}
			input.first = s.substr(0, delim);
			input.second = s.substr(delim + 1);
			m_query.parameters.insert(input);
		}
	}

	return m_query;
}

void ConnectionTCP::send(sf::Packet& packet)
{
	sf::Socket::Status status = m_socket.send(packet);
	if (status != sf::Socket::Done)
	{
		Log::error("Connection-send-string") << "Error while sending to client";
	}
}

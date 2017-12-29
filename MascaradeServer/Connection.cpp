#include "Connection.h"
#include "Log.h"

const std::string Connection::eom = "eom;";

Connection::Connection()
{
}


Connection::~Connection()
{
}

void Connection::connect(std::string address, int port)
{
	if (m_socket.connect(address, port) != sf::Socket::Done)
	{
		Log::error("Connection") << "Error while listening";
	}
}

void Connection::acceptFrom(sf::TcpListener& tl)
{

	if (tl.accept(m_socket) != sf::Socket::Done)
	{
		Log::error("Connection") << "Error while linking to client";
		return;
	}

}

void Connection::send(std::string send)
{
	send += eom;
	if (m_socket.send(send.c_str(), send.size()) != sf::Socket::Done)
	{
		Log::error("Connection") << "Error while sending to client";
	}
}

std::string Connection::receive()
{
	std::string returner="";
	const size_t size = 512;
	char data[size];
	std::size_t received;

	do{
		sf::Socket::Status status = m_socket.receive(data, size, received);
		if (status != sf::Socket::Done)
		{
			if (status == sf::Socket::Disconnected) {
				Log::error("MascaradeServer") << "Client Disconnected !";
				return "disconnect";
			}
			else
				Log::error("MascaradeServer") << "Error while receiving : " << status;
			return "pass";
		}
		appendString(returner, data, received);
	} while (returner.find(eom) == std::string::npos);
	returner.erase(returner.end() - 4,returner.end());
	return returner;
}

void Connection::disconnect()
{
	m_socket.disconnect();
}


void Connection::appendString(std::string& s, char* c, int nb)
{
	for (int i = 0; i < nb; i++)
	{
		s += c[i];
	}
}
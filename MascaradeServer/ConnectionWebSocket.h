////////////////////////////////////////////////////////////
// < Fichier : "ConnectionWebSocket.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef ConnectionWebSocket_H
#define ConnectionWebSocket_H
#include "Connection.h"

class HTTPSerialisation
{
	virtual std::string serialize() = 0;
};


class ConnectionWebSocket : public Connection
{
	enum State
	{
		HandShake,
		Reste
	};

public:
	ConnectionWebSocket();
	~ConnectionWebSocket();

	void				send(sf::Packet&);
	Query&				receive();
	sf::Socket::Status	acceptFrom(sf::TcpListener& tl);

private:
	void manageInit();
};

#endif

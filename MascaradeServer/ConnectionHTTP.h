////////////////////////////////////////////////////////////
// < Fichier : "ConnectionHTTP.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef CONNECTIONHTTP_H
#define CONNECTIONHTTP_H
#include "Connection.h"

class HTTPSerialisation
{
	virtual std::string serialize() = 0;
};

class ConnectionHTTP : public Connection
{
public:
	ConnectionHTTP();
	~ConnectionHTTP();

	void		send(sf::Packet&);
	Query&		receive();
};

#endif

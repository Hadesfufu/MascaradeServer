////////////////////////////////////////////////////////////
// < Fichier : "ConnectionTCP.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef CONNECTIONTCP_H
#define CONNECTIONTCP_H
#include "Connection.h"

class ConnectionTCP : public Connection
{
public:
	ConnectionTCP();
	~ConnectionTCP();

	void		send(sf::Packet&);
	Query&		receive();
private:

};
#endif


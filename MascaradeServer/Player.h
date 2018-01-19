////////////////////////////////////////////////////////////
// < Fichier : "Player.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Connection.h"

class Player
{
public:
	Player(Connection* c);
	~Player();

	std::string& getName() { return m_name; }

	void setName(std::string& s) { m_name = s; }

private:

	std::string m_name;
	int			m_currentVersion;
	Connection* m_connection;
	//user data

};


#endif
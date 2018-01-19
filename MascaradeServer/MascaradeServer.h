////////////////////////////////////////////////////////////
// < Fichier : "MascaradeServer.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef MASCARADESERVER_H
#define MASCARADESERVER_H


#include "Singleton.h"
#include <list>
#include "Game.h"
#include <SFML/Network.hpp>
#include "ConnectionManager.h"
#include "NotificationManager.h"


class MascaradeServer : public Singleton<MascaradeServer>
{
	friend class Singleton < MascaradeServer >;

public:

	void launchServer();
	void load();

	void updateClient(Connection* c);

	int	 handleMessage(Connection*);
	void login(NotificationManager::Dictionary dic);
private:

	MascaradeServer();
	~MascaradeServer();

	std::vector<Card>	m_cards;
	std::list<Game>		m_games;
	sf::Packet			m_sendPacket;
};

#endif

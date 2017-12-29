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

class MascaradeServer : public Singleton<MascaradeServer>
{
	friend class Singleton < MascaradeServer >;

public:

	void launchServer();

private:

	MascaradeServer();
	~MascaradeServer();

	std::list<Game> m_games;
};

#endif

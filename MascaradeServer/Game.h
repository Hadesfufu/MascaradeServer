////////////////////////////////////////////////////////////
// < Fichier : "Game.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Player.h"
#include "Card.h"
#include <list>

class Game
{
public:
	Game();
	~Game();

	void addPlayer(Player p) { m_players.push_back(p); }


	void addCard(Card c) { m_cards.push_back(c); }
	//void removeCard(Card c) { m_cards.erase(std::find(m_cards.begin(), m_cards.end(), c)); }


private:

	std::vector<Player> m_players;
	std::vector<Card>	m_cards;

};


#endif
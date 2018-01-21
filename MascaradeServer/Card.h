////////////////////////////////////////////////////////////
// < Fichier : "Card.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef CARD_H
#define CARD_H
#include <string>
#include "Parameters.h"

class Card
{
public:
	Card();
	Card(json&);
	~Card();

	void load(json& node);
private:

	std::string				m_name;
	//std::function<void>		m_effect;
	
};


#endif
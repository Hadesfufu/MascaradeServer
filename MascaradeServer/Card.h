////////////////////////////////////////////////////////////
// < Fichier : "Card.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef CARD_H
#define CARD_H
#include <string>

class Card
{
public:
	Card();
	~Card();


	void load(std::string name);
private:

	std::string				m_name;
	//std::function<void>		m_effect;
	
};


#endif
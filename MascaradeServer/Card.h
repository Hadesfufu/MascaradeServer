////////////////////////////////////////////////////////////
// < Fichier : "Card.h"> 
// < Author : Yohan "HadesFufu" Masson > 
//////////////////////////////////////////////////////////// 
#ifndef CARD_H
#define CARD_H
#include <string>
#include "external/pugixml/pugixml.hpp"

class Card
{
public:
	Card();
	Card(pugi::xml_node& node);
	~Card();

	void load(pugi::xml_node& node);
private:

	std::string				m_name;
	//std::function<void>		m_effect;
	
};


#endif
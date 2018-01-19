#include "Card.h"



Card::Card()
{
}


Card::~Card()
{
}


Card::Card(pugi::xml_node& node)
{
	load(node);
}

void Card::load(pugi::xml_node& node)
{
	
}

#include "MascaradeServer.h"
#include "ConnectionManager.h"


MascaradeServer::MascaradeServer()
{
}


MascaradeServer::~MascaradeServer()
{
}


void MascaradeServer::launchServer()
{
	ConnectionManager::getInstance()->setListeningPort(53000);
	ConnectionManager::getInstance()->launchListeningThread();
	while (1) {
		//ConnectionManager::getInstance()->getConnection(0)->send("hi!");
		ConnectionManager::getInstance()->checkReceive();
		sf::sleep(sf::seconds(2));
	}
}

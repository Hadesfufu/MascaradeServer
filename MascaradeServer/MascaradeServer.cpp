#include "MascaradeServer.h"
#include "ConnectionManager.h"
#include "Parameters.h"
#include "NotificationManager.h"


MascaradeServer::MascaradeServer()
{
	NotificationManager::getInstance()->AddObserver("login()", this, &MascaradeServer::login);
}


MascaradeServer::~MascaradeServer()
{
}


void MascaradeServer::launchServer()
{
	ConnectionManager::getInstance()->setMessageHandler(std::bind(&MascaradeServer::handleMessage, this, std::placeholders::_1));
	ConnectionManager::getInstance()->setListeningPort(*Parameters::getInstance()->get<int>("ftpListeningPort"));
	ConnectionManager::getInstance()->launchListeningThread();
	while (1) {
		ConnectionManager::getInstance()->checkReceive();
	}
}

void MascaradeServer::load()
{
	std::string filename = *Parameters::getInstance()->get<std::string>("cardFile");
	pugi::xml_document doc;
	if (!doc.load_file(filename.c_str())) {
		Log::error("Behavior_Walking") << "The file hasn't been found";
		return;
	}
	pugi::xml_node child = doc.first_child();
	while(child)
	{
		if (child.name() == "Card")
			m_cards.emplace_back(child);
		child = child.next_sibling();
	}
}

int MascaradeServer::handleMessage(Connection* connection)
{
	std::string s;
	Query& query = connection->getQuery();
	if (query.functionName=="disconnected") {
		//Log::error("MascaradeServer::handleMessage") << "Disconnecting : ";
		return 0;
	}
	else {
		NotificationManager::getInstance()->PostNotification(query.functionName, connection);
		//Log::debug() << s;
	}
	return 0;	
}

void MascaradeServer::updateClient(Connection* c)
{
	
}

void MascaradeServer::login(NotificationManager::Dictionary dic)
{
	sf::Packet p;
	Connection* connection = (Connection*)dic.m_object;
	std::string name;
	name=connection->getQuery().parameters.at("name");
	connection->getPlayer()->setName(name);
	Log::debug("MascaradeServer::login") << "client named" << name << "logged in";
	p << "Logged in !";
	connection->send(p);
}


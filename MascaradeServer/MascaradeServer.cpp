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
	ConnectionManager::getInstance()->setTCPListeningPort(Parameters::getInstance()->getJson().at("ftpListeningPort"));
	ConnectionManager::getInstance()->setWebSocketListeningPort(Parameters::getInstance()->getJson().at("webListeningPort"));
	ConnectionManager::getInstance()->launchListeningThreads();
	while (1) {
		ConnectionManager::getInstance()->checkReceive();
	}
}

void MascaradeServer::load()
{
	std::string filename = Parameters::getInstance()->getJson().at("cardFile");
	std::ifstream file_stream;
	file_stream.open(filename);
	json myJson; 
	file_stream >> myJson;
	json cardArray = myJson.at("cardArray");
	if (!cardArray.is_array())
		Log::error("MascaradeServer::load") << "There is no \"cardArray\"";

	for (auto& element : cardArray) {
		m_cards.emplace_back(element);
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


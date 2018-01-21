
#include "MascaradeServer.h"
#include <sstream>

int main()
{
	/*
	sf::TcpListener listener;
	listener.listen(53000);
	sf::TcpSocket sock;
	listener.accept(sock);
	Log::debug() << "coucou" << sock.getRemoteAddress().toString() << sock.getRemotePort();
	---------
	const size_t size = 16;
	size_t lastReceived;
	sf::Socket::Status status;
	std::vector<char*> datas;
	do
	{
		char* data = new char[size];
		status = sock.receive(data, size, lastReceived);
		datas.push_back(data);
		Log::debug() << status << size << lastReceived;
	} while (size == lastReceived);

	std::string s;
	auto lastItem = datas.size()-1;
	for(int i = 0; i < datas.size(); i++)
	{
		if (i == lastItem)
			s.append(datas[i], lastReceived);
		else
			s.append(datas[i], size);
		delete datas[i];
	}
	---------
	Log::debug() << s;

	size_t f = s.find("Sec-WebSocket-Key:");
	s = s.substr(f+19);
	f = s.find("\n");
	s = s.substr(0, f);
	Log::debug("cuted") << s;

	std::hash<std::string> hash_fn;
	size_t str_hash = hash_fn(s);

	std::stringstream ss;
	ss << str_hash;


	std::string r = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection : Upgrade\r\nSec - WebSocket - Accept : " +ss.str() + "\r\nSec - WebSocket - Protocol : chat";
	status = sock.send(r.c_str(), r.size());
	//sock.disconnect();
	Log::debug() << r << status;
	system("pause");
	*/
	
	MascaradeServer::getInstance()->launchServer();
	return 0;
}

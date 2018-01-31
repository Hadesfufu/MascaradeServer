#include "ConnectionWebSocket.h"
#include <sstream>
#include <openssl\sha.h>
#include "base64.h"
#include "crypto.hpp"

ConnectionWebSocket::ConnectionWebSocket()
{
}


ConnectionWebSocket::~ConnectionWebSocket()
{
}

Connection::Query& ConnectionWebSocket::receive()
{
	Log::info("ConnectionWebSocket::receive") << "receive";
	const size_t size = 1024;
	size_t lastReceived;
	sf::Socket::Status status;
	std::vector<char*> datas;
	do
	{
		char* data = new char[size];
		status = m_socket.receive(data, size, lastReceived);
		datas.push_back(data);
	} while (size == lastReceived);
	
	std::string message;
	auto lastItem = datas.size() - 1;
	for (int i = 0; i < datas.size(); i++)
	{
		if (i == lastItem)
			message.append(datas[i], lastReceived);
		else
			message.append(datas[i], size);
		delete datas[i];
	}
	
	//Log::debug("ConnectionWebSocket::receive") << message;

	if (status == sf::Socket::Disconnected)
	{
		Log::info("ConnectionTCP::receive") << "Disconnecting : ";
		m_query.functionName = "disconnected";
	}
	else if (status == sf::Socket::Error)
	{
		Log::error("ConnectionTCP::receive") << "Error" << status;
	}
	else if (status == sf::Socket::Done)
	{

		/*
		 *	functionname:{argumenta : mescouilles; argumentb : mesboules;}
		 *
		 */
		m_query.functionName = message;
		/*std::string s;
		if (p >> s)
			m_query.functionName = s;
		else
			Log::error("ConnectionTCP::receive") << "no function name";

		std::size_t delim;
		std::pair<std::string, std::string> input;
		while (p >> s)
		{
			delim = s.find(":");
			if (delim == std::string::npos)
			{
				Log::error("ConnectionTCP::receive") << "input is not complete : no \":\" found";
				break;
			}
			input.first = s.substr(0, delim);
			input.second = s.substr(delim + 1);
			m_query.parameters.insert(input);
		}*/
	}

	return m_query;
}

void ConnectionWebSocket::send(sf::Packet& p)
{
	sf::Socket::Status status;
	std::string r /*= "HTTP/1.1 200 OK \n\rServer : MascaradeHTML / 0.1 \n\rContent - Type : text / html\n\r\n\r"*/;
	std::string s;
	while(p >> s)
	{
		r += s;
	}
	status = m_socket.send(r.c_str(), r.size());
	Log::debug() << "sent data :" << r;
	if (status != sf::Socket::Done)
		Log::error("ConnectionWebSocket::send") << "Error while sending data";
}

sf::Socket::Status ConnectionWebSocket::acceptFrom(sf::TcpListener& tl)
{
	sf::Socket::Status status = tl.accept(m_socket);
	if (status != sf::Socket::Done)
		Log::error("Connection") << "Error while linking to client";
	manageInit();
	return status;
}

void ConnectionWebSocket::manageInit()
{
	Query q = receive();
	if (q.functionName.empty())
		return;
	/*sf::Packet p;
	std::string header = q.functionName;
	size_t keyBegin = header.find("Sec-WebSocket-Key:");
	size_t keyEnd = header.substr(keyBegin+19).find("\n");
	std::string key = header.substr(keyBegin+19, keyEnd);
	
	
	Log::debug("cuted") << key;

	std::string s = "dGhlIHNhbXBsZSBub25jZQ==";
	Log::debug() << s;
	s += "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
	Log::debug() << s;
	SHA1 checksum;
	checksum.update(s);

	std::string sha = checksum.final();
	Log::debug("CHECK SHA1") << sha;
	Log::debug("CHECK SHA1 in base64") << base64_encode(sha);
	
	/*std::hash<std::string> hash_fn;
	size_t str_hash = hash_fn(key);
	std::stringstream ss;
	ss << str_hash;*/
	//
	std::string stream = q.functionName;
	Log::debug() << stream;
	static const std::string kWebSocketKeyIdentifier("Sec-WebSocket-Key: ");
	static const int kWebSocketKeyLen = 24;
	static const std::string kWebSocketMagic("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");

	std::size_t pos = stream.find(kWebSocketKeyIdentifier);
	if (pos == std::string::npos) {
		Log::error("No websocket Key");
	}

	std::string key;
	try {
		key = stream.substr(pos + kWebSocketKeyIdentifier.length(), kWebSocketKeyLen);
	}
	catch (std::out_of_range &err) {
		Log::error("Out of range");
	}
	key.append(kWebSocketMagic);
	Log::debug() << "key: " << key;

	std::string output = SimpleWeb::Crypto::SHA1(key);
	std::string final = base64_encode(output);
	std::string r = "HTTP/1.1 101 Switching Protocols\nUpgrade: websocket\nConnection : Upgrade\nSec-WebSocket-Key: " + final + "\nSec-WebSocket-Version: 13\n\n";
	size_t to_send = r.length(), sent;
	m_socket.send(r.c_str(), r.length(), sent);
	Log::debug("sender") << r.length() << sent;
	//m_socket.disconnect();
}

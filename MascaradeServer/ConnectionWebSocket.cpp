#include "ConnectionWebSocket.h"
#include <sstream>
#include "base64.h"
#include "sha1/sha1.h"
//#include <openssl\sha.h>
//#include "base64.h"
//#include "crypto.hpp"

#include <stdint.h>
uint32_t htonl(uint32_t x)
{
#if BYTE_ORDER == LITTLE_ENDIAN
	unsigned char *s = (unsigned char *)&x;
	return (uint32_t)(s[0] << 24 | s[1] << 16 | s[2] << 8 | s[3]);
#else
	return x;
#endif
}

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
	
	Log::debug("ConnectionWebSocket::receive") << message;

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

	SHA1	sha;
	unsigned int    message_digest[5];

	sha.Reset();

	sha << key.c_str();

	sha.Result(message_digest);

	for (int i = 0; i < 5; i++) {
		message_digest[i] = htonl(message_digest[i]);
	}

	std::string final = base64_encode(
		reinterpret_cast<const unsigned char*>
		(message_digest), 20
	);

	Log::debug() << final;
	std::string r = "HTTP/1.1 101 Switching Protocols\nUpgrade: websocket\nConnection: Upgrade\nSec-WebSocket-Key: " + final + "\nSec-WebSocket-Version: 13\n\n";
	size_t sent;
	m_socket.send(r.c_str(), r.length(), sent);
	Log::debug("sender") << r.length() << sent;
	//m_socket.disconnect();
}

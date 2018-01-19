#include "ConnectionHTTP.h"



ConnectionHTTP::ConnectionHTTP()
{
}


ConnectionHTTP::~ConnectionHTTP()
{
}

Query& ConnectionHTTP::receive()
{
	const size_t size = 1024;
	size_t lastReceived;
	sf::Socket::Status status;
	std::vector<char*> datas;
	do
	{
		char* data = new char[size];
		status = m_socket.receive(data, size, lastReceived);
		datas.push_back(data);
		//Log::debug() << status << size << lastReceived;
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

void ConnectionHTTP::send(sf::Packet& p)
{

	sf::Socket::Status status;
	std::string r = "HTTP/1.1 200 OK \n\rServer : MascaradeHTML / 0.1 \n\rContent - Type : text / html\n\r\n\r";
	std::string s;
	while(p >> s)
	{
		r += s;
	}
	status = m_socket.send(r.c_str(), r.size());
	m_socket.disconnect();
}


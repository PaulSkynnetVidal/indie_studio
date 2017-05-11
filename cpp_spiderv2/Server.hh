#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/phoenix/bind/bind_member_function.hpp>
#include <map>
#include <iostream>
#include <fstream>
#include "IServer.hh"

#ifndef _SERVER_HH_
# define _SERVER_HH_

#define PING "101"
#define LEAVE "200"
#define QUIT "201"
#define SEQ "301"

#define GIME "401"*/

using boost::asio::ip::tcp;

typedef boost::shared_ptr<tcp::socket> sock_ptr;

class Server : public IServer
{
public:
	typedef std::string (Server::*serv_func)(std::string, sock_ptr);

private:
	const int _port;
	std::list<boost::thread*> _TList;
	std::map<std::string, serv_func> _mapProtocole;
	short _nameIt;

public:
	Server(const int port);
	~Server();

	virtual void 	Launch();
	virtual void 	Close(){};

private:
	void		initProtocole();
	void		ClientLoop(sock_ptr sock, short numb);
	void		sendData(sock_ptr sock, std::string message);

	std::string	quit(std::string str, sock_ptr sock);
	std::string	ping(std::string str, sock_ptr sock);
	std::string	leave(std::string str, sock_ptr sock);
	std::string	sequence(std::string str, sock_ptr sock);
};

#endif /* _SERVER_HH_ */

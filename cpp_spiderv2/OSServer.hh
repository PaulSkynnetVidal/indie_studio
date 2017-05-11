#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <list>
#include <map>
#include <fstream>
#include <functional>
#include <thread>
#include <algorithm>
#include "IServer.hh"

#ifndef _OPEN_SSL_SERVER_HH_
#define _OPEN_SSL_SERVER_HH_

#define PING "101"
#define LEAVE "200"
#define QUIT "201"
#define SEQ "301"
#define max_length 2048

class OSServer : public IServer
{
public:
	typedef std::string (OSServer::*serv_func)(const std::string, SSL*) const;

private:
	int		_port;
	int		_socket;
	short 	_nameIt;
	SSL_CTX	*ctx;

	std::list<int>	_cList;
	std::list<SSL *>	_sList;
	std::list<std::thread *>	_tList;
	std::map<std::string, serv_func> _mapProtocole;

public:
	OSServer(const int port);
	~OSServer();

	virtual void	Launch();
	virtual void	Close(){};

	void	initOpenSSL() const;
	void	createContext();
	void	cleanUpOpenSSL() const;
	void	configureContext();
	void	createSocket();

	void	loop();
	void	clientLoop(SSL *ssl, short numb);
	void	sendData(SSL *ssl, const std::string mess) const;

	std::string	quit(const std::string str, SSL *ssl) const;
	std::string	ping(const std::string str, SSL *ssl) const;
	std::string	leave(const std::string str, SSL *ssl) const;
	std::string	sequence(const std::string str, SSL *ssl) const;
};

#endif /* _OPEN_SSL_SERVER_HH_ */
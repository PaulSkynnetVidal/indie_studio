#pragma once
#include "stdafx.h"
#define WIN32_LEAN_AND_MEAN

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "4242"

class ISocket
{
public:
	virtual ~ISocket() {}

	virtual bool connectToServer(std::string const &host, short port) = 0;
	virtual int	Recv(std::string &buffer, int blocksize) = 0;
	virtual int Send(std::string const &data) = 0;
	virtual int waitRecv() = 0;
};
#pragma once

#include "stdafx.h"
#include "ISocket.hh"

class Socket : public ISocket
{
private:
	WSADATA wsaData;
	SOCKET ConnectSocket;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	char recvbuf[DEFAULT_BUFLEN];
	size_t iResult;
	int recvbuflen;

public:
	Socket()
	{
		ConnectSocket = INVALID_SOCKET;
		recvbuflen = DEFAULT_BUFLEN;
	}

	~Socket()
	{
		closesocket(ConnectSocket);
		WSACleanup();
	}

	bool init()
	{
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
			return 1;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		return 0;
	}

	bool connectToServer(std::string const &host, short port)
	{
		std::string port_string;
		std::stringstream ss;
		ss << port;
		port_string = ss.str();

		iResult = getaddrinfo(host.c_str(), port_string.c_str(), &hints, &result);
		if (iResult != 0) {
			std::cerr << "getaddrinfo failed with error: " << iResult << std::endl;
			WSACleanup();
			return 1;
		}

		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

			ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket == INVALID_SOCKET) {
				std::cerr << "socket failed with error: " << WSAGetLastError() << std::endl;
				WSACleanup();
				return 1;
			}

			iResult = connect(ConnectSocket, ptr->ai_addr, ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(ConnectSocket);
				ConnectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (ConnectSocket == INVALID_SOCKET) {
			std::cerr << "Unable to connect to server!" << std::endl;
			WSACleanup();
			return 1;
		}
		return 0;
	}

	int	Recv(std::string &buffer, int blocksize)
	{
		char *pute;
		if (!(pute = (char*)malloc(sizeof(char) * blocksize)))
		{
			std::cerr << "malloc failed" << std::endl;
			return SOCKET_ERROR;
		}
		int tamer = 0;
		tamer = recv(ConnectSocket, pute, blocksize, 0);
		buffer = pute;
		free(pute);
		return tamer;
	}

	int Send(std::string const &data)
	{
		int res;
		res = send(ConnectSocket, data.c_str(), (int)data.size(), 0);
		if (res == SOCKET_ERROR) {
			std::cerr << "send failed with error: " << WSAGetLastError() << std::endl;
			closesocket(ConnectSocket);
			WSACleanup();
			return SOCKET_ERROR;
		}
		return res;
	}

	int		waitRecv()
	{
		fd_set fds;
		int n;
		struct timeval tv;

		FD_ZERO(&fds);
		FD_SET(ConnectSocket, &fds);

		tv.tv_sec = 30;
		tv.tv_usec = 0;

		n = select(ConnectSocket, &fds, NULL, NULL, &tv);
		return n;
	}
};
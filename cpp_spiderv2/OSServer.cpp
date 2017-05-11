#include "OSServer.hh"

OSServer::OSServer(const int port)
{
	_port = port;
	_nameIt = 0;
  	_mapProtocole[PING] = &OSServer::ping;
  	_mapProtocole[LEAVE] = &OSServer::leave;
  	_mapProtocole[QUIT] = &OSServer::quit;
  	_mapProtocole[SEQ] = &OSServer::sequence;
}

OSServer::~OSServer()
{
	for_each(_sList.begin(), _sList.end(), SSL_free);
	for_each(_cList.begin(), _cList.end(), close);
	std::cout << "Shuting down server..." << std::endl;
}

void	OSServer::Launch()
{
	this->initOpenSSL();
	this->createContext();
	this->configureContext();
	createSocket();
	this->loop();
}

void	OSServer::initOpenSSL() const
{
	SSL_load_error_strings();
	OpenSSL_add_ssl_algorithms();
}

void	OSServer::createContext()
{
    const SSL_METHOD *method;
    method = SSLv23_server_method();
    ctx = SSL_CTX_new(method);
    if (!ctx)
	{
		perror("Unable to create SSL context");
		ERR_print_errors_fp(stderr);
		exit(EXIT_FAILURE);
    }
}

void	OSServer::cleanUpOpenSSL() const
{
    EVP_cleanup();
}

void	OSServer::configureContext()
{
    if (SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM) < 0)
	{
        ERR_print_errors_fp(stderr);
		exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM) < 0 )
	{
        ERR_print_errors_fp(stderr);
		exit(EXIT_FAILURE);
    }
}

void	OSServer::createSocket()
{
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0)
	{
		perror("Unable to create socket");
		exit(EXIT_FAILURE);
    }
    if (bind(_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		perror("Unable to bind");
		exit(EXIT_FAILURE);
    }
    if (listen(_socket, 1) < 0)
	{
		perror("Unable to listen");
		exit(EXIT_FAILURE);
    }
}

void	OSServer::loop()
{
	while (1)
	{
        struct sockaddr_in addr;
        uint len = sizeof(addr);
        SSL *ssl;

        int client = accept(_socket, (struct sockaddr*)&addr, &len);
        if (client < 0)
		{
            perror("Unable to accept");
            exit(EXIT_FAILURE);
        }
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client);
        if (SSL_accept(ssl) <= 0)
		{
            ERR_print_errors_fp(stderr);
        }
        else {
		_cList.push_back(client);
		_sList.push_back(ssl);
		_tList.push_back(new std::thread(std::bind(&OSServer::clientLoop, this, ssl, _nameIt)));
		++_nameIt;
        }
	}
}

void	OSServer::clientLoop(SSL *ssl, short numb)
{
	std::cout << "New client connected" << std::endl;
  	std::string file("client_");
  	file = file + std::to_string(numb);
  	file = file + ".log";
	std::cout << "created file : " << file << std::endl;

  	std::ofstream myfile;
	myfile.open(file);

	myfile << "*** I'm a header, please ignore ***\n";

  try
  {
    for (;;)
    {
      char data[max_length];
      int length = SSL_read(ssl, data, max_length);
	  if (length < 0)
	  {
		throw "SSL_read() returned negative value";
	  }
      std::string sdata(data);
      std::string res("");

      serv_func p = _mapProtocole[sdata.substr(0, 3)];
      if (p)
      {
        if ((res = (this->*p)(sdata, ssl)) != "" && res.size() > 2)
        {
          res = res.substr(2, res.size() - 2);
          myfile << res;
          std::string mess("300: ");
          mess += std::to_string(res.size());
          mess += "\r\n";
          sendData(ssl, mess);
        }
      }
      else
      {
        sendData(ssl, "Bad imput\r\n");
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
  myfile.close();
}

void		OSServer::sendData(SSL* ssl, const std::string mess) const
{
  std::cout << "Sending : " << mess << std::endl;
  SSL_write(ssl, mess.c_str(), mess.size());
}

std::string	OSServer::quit(const std::string str, SSL *ssl) const
{
	std::cout << "reçu QUIT" << std::endl;
	return "";
};

std::string	OSServer::ping(const std::string str, SSL *ssl) const
{
	std::cout << "reçu PING" << std::endl;
	sendData(ssl, "102: PONG\r\n");
	return "";
};

std::string	OSServer::leave(const std::string str, SSL *ssl) const
{
	std::cout << "reçu LEAVE" << std::endl;
	return "";
};

std::string OSServer::sequence(const std::string str, SSL *ssl) const
{
	std::cout << "reçu SEQ" << std::endl;
	return str.substr(3, str.size() - 3);
};
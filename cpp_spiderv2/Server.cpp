#include "Server.hh"

using boost::asio::ip::tcp;

const int max_length = 1024;

Server::Server(const int port) : _port(port)
{
  initProtocole();
  _nameIt = 0;
}

Server::~Server() {}

void  Server::initProtocole()
{
  std::cout << "initialisation du protocole" << std::endl;
  _mapProtocole[PING] = &Server::ping;
  _mapProtocole[LEAVE] = &Server::leave;
  _mapProtocole[QUIT] = &Server::quit;
  _mapProtocole[SEQ] = &Server::sequence;
}

void Server::Launch()
{
	boost::asio::io_service io_serv;
	tcp::acceptor a(io_serv, tcp::endpoint(tcp::v4(), _port));
	for (;;)
	{
		sock_ptr sock(new tcp::socket(io_serv));

		a.accept(*sock);
		_TList.push_back(new boost::thread(boost::bind(&Server::ClientLoop, this, sock, _nameIt)));
		++_nameIt;
	}
}

void Server::ClientLoop(sock_ptr sock, short numb)
{
	std::cout << "New client connected" << std::endl;
  std::string file("client_");
  file = file + std::to_string(numb);
  file = file + ".log";

  //DEBUG
  std::cout << "name of file : " << file << std::endl;
  //!DEBUG

  std::ofstream myfile;
  myfile.open(file);

  myfile << "*** I'm a header, please ignore ***\n";

  try
  {
    for (;;)
    {
      char data[max_length];

      boost::system::error_code error;
      size_t length = sock->read_some(boost::asio::buffer(data), error);

      if (error == boost::asio::error::eof)
        break;
      else if (error)
        throw boost::system::system_error(error);

      std::string sdata(data);
      std::string res("");

      serv_func p = _mapProtocole[sdata.substr(0, 3)];
      if (p)
      {
        if ((res = (this->*p)(sdata, sock)) != "" && res.size() > 2)
        {
          res = res.substr(2, res.size() - 3);
          myfile << res;
          std::string mess("300: ");
          mess += std::to_string(res.size());
          mess += "\r\n";
          sendData(sock, mess);
        }
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
  myfile.close();
}

void		Server::sendData(sock_ptr sock, std::string mess)
{
  std::cout << "Sending : " << mess << std::endl;
  boost::asio::write(*sock, boost::asio::buffer(mess, mess.size()));
}

std::string	Server::quit(std::string str, sock_ptr sock){
	std::cout << "reçu QUIT" << std::endl;
	return "";
};

std::string	Server::ping(std::string str, sock_ptr sock){
	std::cout << "reçu PING" << std::endl;
  sendData(sock, "102: PONG\r\n");
	return "";
};

std::string	Server::leave(std::string str, sock_ptr sock){
	std::cout << "reçu LEAVE" << std::endl;
	return "";
};

std::string Server::sequence(std::string str, sock_ptr sock){
	std::cout << "reçu SEQ" << std::endl;
	return str.substr(3, str.size() - 3);
};

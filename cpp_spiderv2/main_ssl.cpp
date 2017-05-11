#include "OSServer.hh"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "wrong argument number / type" << std::endl;
		return -1;
	}
	OSServer _server(atoi(av[1]));
	_server.Launch();
	return 0;
}
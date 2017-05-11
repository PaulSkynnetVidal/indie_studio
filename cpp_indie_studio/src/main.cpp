#include "Core.hh"
#include "MenuCore.hh"

#include <unistd.h>

int main(int ac, char const *av[])
{
  bomber::MenuCore	menu;
  std::string		map;
  bool			secondPlayer(false);

  while ((menu.run(map, secondPlayer)))
    {
      bomber::Core	core;
      if (!core.run(map, secondPlayer))
	break;
    }
  return 0;
}

/*
int	main(int ac, char const *av[])
{
  try
    {
      bomber::Core	game("map");

      while (game.getDevice()->run())
	{
	  game.update();
	  game.draw();
	}
    }
  catch (int e)
  {
      // NOTE: Temporary catch, waiting exceptions
      switch (e)
	{
	  case 1:
	  std::cout << "Can't init device" << std::endl;
	  case 2:
	  std::cout << "Can't init video driver" << std::endl;
	  case 3:
	  std::cout << "Can't init scene manager" << std::endl;
	  default:
	  std::cout << "Unknown error" << std::endl;
	}
  }
  return 0;
}
*/

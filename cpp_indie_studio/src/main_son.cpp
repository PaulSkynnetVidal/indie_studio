//
// main.cpp for main in /home/debrab_t/rendu/cpp_indie_studio/son
//
// Made by debrab_t
// Login   <debrab_t@epitech.net>
//
// Started on  Fri Jun 10 03:21:30 2016 debrab_t
// Last update Fri Jun 10 03:23:11 2016 debrab_t
//

#include "Son.hpp"
#include <unistd.h>

int	main()
{
  My_Sound 	son;

  son.Play_Sound("sono/fire.wav");
  sleep(10);
}

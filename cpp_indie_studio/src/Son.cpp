//
// son.cpp for test in /home/bouqui_c/rendu/TEK2/CPP/cpp_indie_studio/son
//
// Made by bouqui_c
// Login   <bouqui_c@epitech.net>
//
// Started on  Sat Jun  4 19:02:10 2016 bouqui_c
// Last update Fri Jun 10 14:49:22 2016 debrab_t
//

#include <unistd.h>
#include "Son.hpp"

My_Sound::My_Sound()
{}

void	My_Sound::Play_Sound(const std::string& filename)
{

    if (!buffer.loadFromFile(filename))
    {
      std::cerr << "This sound can't be loaded" << std::endl;
      return;
    }

  sound.setBuffer(buffer);
  sound.play();
}

void	My_Sound::Stop()
{
  sound.stop();
}

My_Sound::~My_Sound()
{}

My_Music::My_Music()
{}

void	My_Music::Play_Music(const std::string& filename)
{
  sf::Music	music;

  if (!music.openFromFile(filename))
    {
      std::cerr << "This music can't be loaded" << std::endl;
      return;
    }
  music.play();
}

My_Music::~My_Music()
{}

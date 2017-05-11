//
// Son.hpp for son in /home/bouqui_c/rendu/TEK2/CPP/cpp_indie_studio/son
//
// Made by bouqui_c
// Login   <bouqui_c@epitech.net>
//
// Started on  Sun Jun  5 01:37:58 2016 bouqui_c
// Last update Fri Jun 10 14:48:54 2016 debrab_t
//

#ifndef SON_HPP_
# define SON_HPP_

#include <iostream>
#include "SFML/Audio.hpp"

class	My_Sound
{
private:

  sf::SoundBuffer	buffer;
  sf::Sound		sound;

public:

  My_Sound();
  ~My_Sound();

  void	Play_Sound(const std::string& filename);
  void	Stop();
};

class	My_Music
{

private:
  sf::Music	music;

public:

  My_Music();
  ~My_Music();

  void	Play_Music(const std::string& filename);

};

#endif /* !SON_HPP_ */

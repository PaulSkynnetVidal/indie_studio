//
// Player.hh for player in /home/debrab_t/rendu/cpp_indie_studio/src
//
// Made by debrab_t
// Login   <debrab_t@epitech.net>
//
// Started on  Tue May 24 15:19:52 2016 debrab_t
// Last update Fri Jun 10 11:58:08 2016 David Calo
//

#ifndef PLAYER_HH_
# define PLAYER_HH_

# include "bomber.hh"
# include "map.hh"

namespace	bomber
{
  class		Player
    {
    public:
      Player(bomber::v2d const &, bomber::Map const * map, bool);
      ~Player();

      void	movePlayer(bool move, bomber::e_direction dir, bomber::v2d base, irr::u32 time);

      void	giveBonus(e_bonus);
      void	addSpeed();
      void	addRange();
      void	addBomb();

    protected:
      int	_bombs;
      int	_bombsUse;
      int	_lives;
      int	_range;
      irr::u32		_speed;
      irr::u32		_lastTime;
      bomber::v2d	_pos;

      irr::scene::IAnimatedMeshSceneNode*	_node;

    public:
      int	getBombs() const;
      int	getBombsUse() const;
      int	getRange() const;
      int	getX() const;
      int	getY() const;
      bomber::v2d const &	getPos() const;
      irr::scene::IAnimatedMeshSceneNode*      getNode() const;

      void	setBombsUse(int b);

  };
}

#endif /* PLAYER_HH_ */

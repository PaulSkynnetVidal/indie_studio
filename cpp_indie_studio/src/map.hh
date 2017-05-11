
#ifndef MAP_HH_
# define MAP_HH_

# include <iostream>
# include <irrlicht.h>
# include <vector>
# include <cstring>
# include <iostream>
# include <random>
# include <cstdlib>
# include <cstdio>
# include <ctime>

# include "bomber.hh"
# include "Bombe.hh"
# include "Son.hpp"

namespace	bomber
{
  class		Player;

  typedef struct	s_storNodes
    {
      irr::scene::IAnimatedMeshSceneNode*	node;
      int					y;
      int					x;
      int					var;
    }			t_storNodes;

    typedef struct	s_expNodes
    {
      irr::scene::IAnimatedMeshSceneNode*	node;
      irr::u32					time;
    }			t_expNodes;

  class	Map
    {
    public:
      Map();
      ~Map();

      int	buildMap();
      void	addPlayer(bool);

      void	choiceBonus(bomber::v2d const &);
      int	checkBombes();
      void	checkExplosion();
      void	checkBonus();

      int	putGround(const int, const int, const int, const std::string &);
      int	putBombe(Bombe *, int);
      int	putExplosion(bomber::v2d const &);
      int	putBonusSpeed(bomber::v2d const &);
      int	putBonusRange(bomber::v2d const &);
      int	putBonusBombe(bomber::v2d const &);

      void	movePlayer(int, e_direction);
      void	actionBomb(int);

      bomber::v2d	getPlayerPosition(bool second) const;
      char		getInfoPosition(bomber::v2d const &) const;
      void		setInfoPosition(bomber::v2d const &, char);

    protected:
      int	charToObj(bomber::v2d const &);
      int	initSize();

      void	removeFromNode(bomber::v2d const &, std::vector<t_storNodes> &);
      bool	removePosition(bomber::v2d const & pos);
      void	clearBlock(bomber::v2d const &, int);
      void	clearUp(bomber::v2d const &, int);
      void	clearDown(bomber::v2d const &, int);
      void	clearLeft(bomber::v2d const &, int);
      void	clearRight(bomber::v2d const &, int);

    protected:
      int	_end;
      irr::u32	_time;

      bomber::v2d	_size;
      bomber::v2d	_base;

      std::vector<std::string>	map;
      std::vector<t_storNodes>	_nGround;
      std::vector<t_storNodes>	_nBomb;
      std::vector<t_storNodes>	_nCrate;
      std::vector<t_storNodes>	_nBonus;
      std::vector<t_expNodes>	_nExplosion;
      std::vector<Bombe *>	_bombes;
      std::vector<Player>	_player;

      irr::video::IVideoDriver	*_driver;
      irr::scene::ISceneManager	*_smgr;

      My_Sound			son;

    public:
      int			getBaseX() const;
      int			getBaseY() const;
      int			getX() const;
      int			getY() const;
      bomber::v2d const &	getBase() const;
      bomber::v2d const &	getSize() const;
      std::vector<std::string>	getMap() const;
      irr::video::IVideoDriver	*getVideoDriver() const;
      irr::scene::ISceneManager	*getSceneManager() const;

      void	setTime(irr::u32);
      void	setMap(const std::vector<std::string> file);
      void	setVideoDriver(irr::video::IVideoDriver *driver);
      void	setSceneManager(irr::scene::ISceneManager *smgr);

    };
}

#endif /* MAP_HH_ */

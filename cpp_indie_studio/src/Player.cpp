//
// player.cpp for player in /home/debrab_t/rendu/cpp_indie_studio/src
//
// Made by debrab_t
// Login   <debrab_t@epitech.net>
//
// Started on  Tue May 24 15:19:43 2016 debrab_t
// Last update Fri Jun 10 12:03:17 2016 David Calo
//

# include "Player.hh"
# include "unistd.h"

bomber::Player::Player(bomber::v2d const & pos, bomber::Map const * map, bool second)
  : _bombs(1), _bombsUse(0), _lives(1), _range(1), _speed(1), _lastTime(0), _pos(pos), _node(0)
{
  irr::scene::IAnimatedMesh*		mesh;

  if (!(mesh = map->getSceneManager()->getMesh("obj/ninja.b3d")))
    exit (1);
  // TODO: use 'throw'
  else if ((_node = map->getSceneManager()->addAnimatedMeshSceneNode(mesh)))
    {
      this->_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      this->_node->setMD2Animation(irr::scene::EMAT_STAND);
      this->_node->setPosition(irr::core::vector3df((pos.X * 100) + map->getBaseX() - 40, 110,
						   (pos.Y * 100) + map->getBaseY() + 50));
      this->_node->setFrameLoop(0, 13);
      this->_node->setAnimationSpeed(10);
      this->_node->setScale(irr::core::vector3df(20));
      this->_node->setRotation(irr::core::vector3df(0, 0, 0));
      if (!second)
	this->_node->setMaterialTexture(0, map->getVideoDriver()->getTexture("obj/texture/bonus.png"));
      else
  	this->_node->setMaterialTexture(0, map->getVideoDriver()->getTexture("obj/texture/deadpool_player_two.png"));
    }
}

bomber::Player::~Player()
{
//  this->_node->remove();
}
void	bomber::Player::movePlayer(bool move, bomber::e_direction dir, bomber::v2d base, irr::u32 time)
{
  if (time > (_lastTime + (MOV_SPD / _speed)))
    {
      // TODO: create Map member function to replace the following call
      if (move)
	{
	  _pos += bomber::getMovVector(dir);
          this->_node->setPosition(irr::core::vector3df((_pos.X * 100)
						       + base.X - 40, 110,
						       (_pos.Y * 100)
						       + base.Y + 50));
	}
      this->_node->setRotation(irr::core::vector3df(0, bomber::getRotValue(dir), 0));
      _lastTime = time;
    }
}

void	bomber::Player::giveBonus(e_bonus bonus)
{
  switch (bonus)
    {
    case B_SPEED:
      addSpeed();
      break;
    case B_RANGE:
      addRange();
      break;
    case B_BOMB:
      addBomb();
      break;
    }
}

void	bomber::Player::addSpeed()
{
  if (_speed < MAX_SPEED)
    _speed++;
}
void	bomber::Player::addRange()
{
  if (_range < MAX_RANGE)
    _range++;
}
void	bomber::Player::addBomb()
{
  if (_bombs < MAX_BOMB)
    _bombs++;
}

int	bomber::Player::getX() const { return _pos.X; }
int	bomber::Player::getY() const { return _pos.Y; }
bomber::v2d const &	bomber::Player::getPos() const { return _pos; }
int	bomber::Player::getRange() const { return _range; }
int	bomber::Player::getBombs() const { return _bombs; }
int	bomber::Player::getBombsUse() const { return _bombsUse; }
void	bomber::Player::setBombsUse(int b) { _bombsUse += b; }

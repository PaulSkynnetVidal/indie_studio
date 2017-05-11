
#include "map.hh"
#include "Player.hh"

bomber::Map::Map() : _end(0), _time(0)
{
  son.Play_Sound("./src/sono/jeu.wav");
}

bomber::Map::~Map() {}

// TODO: use throw instead of return and make void methods

int	bomber::Map::buildMap()
{
  initSize();
  for (size_t x = 1; x < map.size() && x != _size.X; x++)
    {
      for (size_t y = 0; y < map[x].size() && y != _size.Y; y++)
	charToObj(bomber::v2d(x - 1, y));
    }
}


bomber::v2d	bomber::Map::getPlayerPosition(bool second) const
{
  // TODO: choose position in map (find char 'p')
  if (second)
    return bomber::v2d(15, 15);
  return bomber::v2d(3, 3);
}


void	bomber::Map::addPlayer(bool second)
{
  _player.push_back(Player(getPlayerPosition(false), this, false));
  if (second)
    _player.push_back(Player(getPlayerPosition(second), this, true));
}

void	bomber::Map::choiceBonus(bomber::v2d const & pos)
{
  switch (rand() % BONUS_LUCK)
    {
    case 3:
      putBonusSpeed(pos);
      break;
    case 4:
      putBonusRange(pos);
      break;
    case 5:
      putBonusBombe(pos);
      break;
    }
}

int    bomber::Map::checkBombes()
{
  for (int i = 0; i < _bombes.size(); i++)
    {
      if (_bombes[i]->getTime() + BOMB_TIME < _time)
        {
          setInfoPosition(_bombes[i]->getPos(), ' ');
          _nBomb[i].node->remove();
	  _player[_nBomb[i].var].setBombsUse(-1);
          _nBomb.erase(_nBomb.begin() + i);
          clearBlock(_bombes[i]->getPos(), _bombes[i]->getRange());
	  son.Play_Sound("./src/sono/fire.wav");
          _bombes.erase(_bombes.begin() + i);
          i--;
        }
    }
  return (_end);
}

void	bomber::Map::checkExplosion()
{
  for (int i = 0; i < _nExplosion.size(); i++)
    {
      if (_nExplosion[i].time + EXP_TIME < _time)
        {
          _nExplosion[i].node->remove();
          _nExplosion.erase(_nExplosion.begin() + i);
          i--;
        }
    }
}

void	bomber::Map::checkBonus()
{
  for (size_t i = 0; i < _nBonus.size(); i++)
    {
      bomber::v2d	bPos(_nBonus[i].x, _nBonus[i].y);
      if (_player[0].getPos() == bPos)
	{
	  son.Play_Sound("./src/sono/bonus.wav");
	  _nBonus[i].node->remove();
	  _player[0].giveBonus((e_bonus)_nBonus[i].var);
	  _nBonus.erase(_nBonus.begin() + i);
	  i--;
	}
      if (_player[1].getPos() == bPos)
	{
	  son.Play_Sound("./src/sono/bonus.wav");
	  _nBonus[i].node->remove();
	  _player[1].giveBonus((e_bonus)_nBonus[i].var);
	  _nBonus.erase(_nBonus.begin() + i);
	  i--;
	}
    }
}

int	bomber::Map::putGround(const int x, const int z, const int y,
		       const std::string &texture)
{
  irr::scene::IAnimatedMeshSceneNode*	node;
  irr::scene::IAnimatedMesh*		mesh;
  t_storNodes				mynode;

  if (!(mesh = _smgr->getMesh("obj/box.obj")))
    return 1;
  else if ((node = _smgr->addAnimatedMeshSceneNode(mesh)))
    {
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      node->setMD2Animation(irr::scene::EMAT_STAND);
      node->setPosition(irr::core::vector3df((x * 100) + _base.X, z * 50,
					     (y * 100) + _base.Y));
      node->setRotation(irr::core::vector3df(0,0,0));
      node->setMaterialTexture(0, _driver->getTexture(texture.c_str()));
      mynode.node = node;
      mynode.x = x;
      mynode.y = y;
      if (z == 2)
      	this->_nCrate.push_back(mynode);
      else
	this->_nGround.push_back(mynode);
      if (z > 0)
        putGround(x, 0, y, "obj/texture/ground.jpg");
    }
  return (0);
}

int	bomber::Map::putExplosion(bomber::v2d const & pos)
{
  irr::scene::IAnimatedMeshSceneNode*	node;
  irr::scene::IAnimatedMesh*		mesh;

  if (!(mesh = _smgr->getMesh("obj/box.obj")))
    return 1;
  else if ((node = _smgr->addAnimatedMeshSceneNode(mesh)))
    {
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      node->setPosition(irr::core::vector3df((pos.X * 100) + _base.X, 1,
					     (pos.Y * 100) + _base.Y));
      node->setRotation(irr::core::vector3df(0,0,0));
      node->setMaterialTexture(0, _driver->getTexture("obj/texture/lavaground.jpg"));
    }
  _nExplosion.push_back({node, _time});
  return (putGround(pos.X, 0, pos.Y, "obj/texture/ground.jpg"));
}

int	bomber::Map::putBombe(Bombe *b, int player)
{
  irr::scene::IAnimatedMeshSceneNode*	node;
  irr::scene::IAnimatedMesh*		mesh;

  bomber::v2d		pos = b->getPos();

  if (!(mesh = _smgr->getMesh("obj/dinamite.obj")))
    return 1;
  else if ((node = _smgr->addAnimatedMeshSceneNode(mesh)))
    {
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      node->setMD2Animation(irr::scene::EMAT_STAND);
      node->setPosition(irr::core::vector3df((pos.X * 100) + _base.X - 40, 175,
					     (pos.Y * 100) + _base.Y + 50));
      node->setScale(irr::core::vector3df(35));
      node->setRotation(irr::core::vector3df(0,(pos.X * _base.X) + (pos.Y * _base.Y),0));
      node->setMaterialTexture(0, _driver->getTexture("obj/texture/D.png"));
    }
  setInfoPosition(pos, 'b');
  b->setTime(_time);
  this->_bombes.push_back(b);
  this->_nBomb.push_back({node, pos.Y, pos.X, player});
  return (putGround(pos.X, 0, pos.Y, "obj/texture/ground.jpg"));
}

int	bomber::Map::putBonusSpeed(bomber::v2d const & pos)
{
  irr::scene::IAnimatedMeshSceneNode*	node;
  irr::scene::IAnimatedMesh*		mesh;

  if (!(mesh = _smgr->getMesh("obj/speed.obj")))
    return 1;
  else if ((node = _smgr->addAnimatedMeshSceneNode(mesh)))
    {
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      node->setMD2Animation(irr::scene::EMAT_STAND);
      node->setPosition(irr::core::vector3df((pos.X * 100) + _base.X - 40, 150,
					     (pos.Y * 100) + _base.Y + 50));
      node->setScale(irr::core::vector3df(6));
      node->setRotation(irr::core::vector3df(0,(pos.Y * _base.X) + (pos.X * _base.Y),0));
      node->setMaterialTexture(0, _driver->getTexture("obj/texture/bonus.png"));
      irr::scene::ISceneNodeAnimator* anim=_smgr->createRotationAnimator(irr::core::vector3df(0, 3, 0));
      node->addAnimator(anim);
    }
  setInfoPosition(pos, 'B');
  this->_nBonus.push_back({node, pos.Y, pos.X, B_SPEED});
  return (putGround(pos.X, 0, pos.Y, "obj/texture/ground.jpg"));
}

int	bomber::Map::putBonusRange(bomber::v2d const & pos)
{
  irr::scene::IAnimatedMeshSceneNode*	node;
  irr::scene::IAnimatedMesh*		mesh;

  if (!(mesh = _smgr->getMesh("obj/range.obj")))
    return 1;
  else if ((node = _smgr->addAnimatedMeshSceneNode(mesh)))
    {
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      node->setMD2Animation(irr::scene::EMAT_STAND);
      node->setPosition(irr::core::vector3df((pos.X * 100) + _base.X - 40, 150,
					     (pos.Y * 100) + _base.Y + 50));
      node->setScale(irr::core::vector3df(4));
      node->setRotation(irr::core::vector3df(0,(pos.Y * _base.X) + (pos.X * _base.Y),0));
      node->setMaterialTexture(0, _driver->getTexture("obj/texture/bonus.png"));
      irr::scene::ISceneNodeAnimator* anim=_smgr->createRotationAnimator(irr::core::vector3df(0, 3, 0));
      node->addAnimator(anim);
    }
  setInfoPosition(pos, 'B');
  this->_nBonus.push_back({node, pos.Y, pos.X, B_RANGE});
  return (putGround(pos.X, 0, pos.Y, "obj/texture/ground.jpg"));
}

int	bomber::Map::putBonusBombe(bomber::v2d const & pos)
{
  irr::scene::IAnimatedMeshSceneNode*	node;
  irr::scene::IAnimatedMesh*		mesh;

  if (!(mesh = _smgr->getMesh("obj/bombe.obj")))
    return 1;
  else if ((node = _smgr->addAnimatedMeshSceneNode(mesh)))
    {
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      node->setMD2Animation(irr::scene::EMAT_STAND);
      node->setPosition(irr::core::vector3df((pos.X * 100) + _base.X - 40, 150,
					     (pos.Y * 100) + _base.Y + 50));
      node->setScale(irr::core::vector3df(20));
      node->setRotation(irr::core::vector3df(0,(pos.Y * _base.X) + (pos.X * _base.Y),0));
      node->setMaterialTexture(0, _driver->getTexture("obj/texture/bonus.png"));
      irr::scene::ISceneNodeAnimator* anim=_smgr->createRotationAnimator(irr::core::vector3df(0, 3, 0));
      node->addAnimator(anim);
    }
  setInfoPosition(pos, 'B');
  this->_nBonus.push_back({node, pos.Y, pos.X, B_BOMB});
  return (putGround(pos.X, 0, pos.Y, "obj/texture/ground.jpg"));
}

int	bomber::Map::charToObj(bomber::v2d const & pos)
{
  switch(getInfoPosition(pos))
    {
    case ' ':
      return (putGround(pos.X, 0, pos.Y, "obj/texture/ground.jpg"));
      break;
    case '~':
      return (putGround(pos.X, 0, pos.Y, "obj/texture/water.jpg"));
      break;
    case 'i':
      return (putGround(pos.X, 1, pos.Y, "obj/texture/grayground.jpg"));
      break;
    case 'c':
      return (putGround(pos.X, 2, pos.Y, "obj/texture/woodbox.png"));
      break;
    case 'l':
      return (putGround(pos.X, 0, pos.Y, "obj/texture/lavaground.jpg"));
      break;
    }
  return (0);
}

int	bomber::Map::initSize()
{
  std::string	str = map[0];

  int	n = std::stoi(str.substr(0, str.find('-')));
  this->_base.X = (n * -100) / 2 + 100;
  _size.X = n + 1;

  n = std::stoi(str.substr(str.find('-') + 1));
  this->_base.Y = (n * -100) / 2 + 100;
  _size.Y = n;

  if (this->_base.X == 0 || this->_base.Y == 0)
    return (0);
  return (1);
  // NOTE: on error throw 'Size of map incorect'
}

void	bomber::Map::removeFromNode(bomber::v2d const & pos, std::vector<t_storNodes> & node)
{
  for (int i = 0; i < node.size(); i++)
    {
      bomber::v2d	cPos(node[i].x, node[i].y);
      if (pos == cPos)
	{
	  node[i].node->remove();
	  setInfoPosition(cPos, ' ');
	  node.erase(node.begin() + i);
	  i--;
	  return;
	}
    }
}

void    bomber::Map::clearBlock(bomber::v2d const & pos, int range)
{
  putExplosion(pos);
  removePosition(pos);
  range -= 1;
  clearUp(pos + bomber::v2d(1, 0), range);
  clearDown(pos + bomber::v2d(-1, 0), range);
  clearLeft(pos + bomber::v2d(0, 1), range);
  clearRight(pos + bomber::v2d(0, -1), range);
}

bool	bomber::Map::removePosition(bomber::v2d const & pos)
{
  switch (getInfoPosition(pos))
    {
    case 'c':
      removeFromNode(pos, _nCrate);
      choiceBonus(pos);
      putExplosion(pos);
      return false;
    case 'B':
      removeFromNode(pos, _nBonus);
      putExplosion(pos);
      return true;
    case 'i':
      return false;
    case 'b':
      for (int i = 0; i < _bombes.size(); i++)
	{
	  if (_bombes[i]->getPos() == pos)
	    _bombes[i]->setTime(0);
	}
    default:
      putExplosion(pos);
      if (_player[0].getPos() == pos)
	_end = 1;
      else if (_player[1].getPos() == pos)
	_end = 2;
      break;
    }
  return true;
}

void	bomber::Map::clearUp(bomber::v2d const & pos, int range)
{
  if (removePosition(pos) && range > 0)
    clearUp(pos + bomber::v2d(1, 0), range - 1);
}

void	bomber::Map::clearDown(bomber::v2d const & pos, int range)
{
  if (removePosition(pos) && range > 0)
    clearDown(pos + bomber::v2d(-1, 0), range - 1);
}

void	bomber::Map::clearLeft(bomber::v2d const & pos, int range)
{
  if (removePosition(pos) && range > 0)
    clearLeft(pos + bomber::v2d(0, 1), range - 1);
}

void	bomber::Map::clearRight(bomber::v2d const & pos, int range)
{
  if (removePosition(pos) && range > 0)
      clearRight(pos + bomber::v2d(0, -1), range - 1);
}

void	bomber::Map::movePlayer(int player, bomber::e_direction dir)
{
  bool		canMove = false;
  char		c = getInfoPosition(_player[player].getPos() + bomber::getMovVector(dir));
  if (c == ' ' || c == 'B')
    canMove = true;
  _player[player].movePlayer(canMove, dir, getBase(), _time);
}

void	bomber::Map::actionBomb(int player)
{
  if ((_player[player].getBombsUse() < _player[player].getBombs()) && getInfoPosition(_player[player].getPos()) != 'b')
    {
      putBombe(new Bombe(_player[player].getPos(), _player[player].getRange()), player);
      _player[player].setBombsUse(1);
    }
}

// TODO: Use an enum
char	bomber::Map::getInfoPosition(bomber::v2d const & pos) const { return map[pos.X + 1][pos.Y]; }
void	bomber::Map::setInfoPosition(bomber::v2d const & pos, char c) { map[pos.X + 1][pos.Y] = c; }

int				bomber::Map::getBaseX() const { return _base.X; }
int				bomber::Map::getBaseY() const { return _base.Y; }
int				bomber::Map::getX() const { return _size.X; }
int				bomber::Map::getY() const { return _size.Y; }
bomber::v2d const &		bomber::Map::getBase() const { return _base; }
bomber::v2d const &		bomber::Map::getSize() const { return _size; }
std::vector<std::string>	bomber::Map::getMap() const { return map; }
irr::video::IVideoDriver *	bomber::Map::getVideoDriver() const { return _driver; }
irr::scene::ISceneManager *	bomber::Map::getSceneManager() const { return _smgr; }

void	bomber::Map::setTime(irr::u32 time) { _time = time; }
void	bomber::Map::setMap(const std::vector<std::string> file) { map = file; }
void	bomber::Map::setVideoDriver(irr::video::IVideoDriver *driver) { _driver = driver; }
void	bomber::Map::setSceneManager(irr::scene::ISceneManager* smgr) { _smgr = smgr; }

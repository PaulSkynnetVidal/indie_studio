#include "Bombe.hh"

bomber::Bombe::Bombe(bomber::v2d const & pos, int range)
: _x(pos.X) , _y(pos.Y), _time(0), _range(range)
{}

bomber::Bombe::~Bombe() {}

int		bomber::Bombe::getX() const { return this->_x; }
int		bomber::Bombe::getY() const { return this->_y; }
int		bomber::Bombe::getRange() const { return this->_range; }
irr::u32	bomber::Bombe::getTime() const { return this->_time; }
bomber::v2d	bomber::Bombe::getPos() const { return bomber::v2d(_x, _y); }

void		bomber::Bombe::setTime(irr::u32 time) { this->_time = time; }

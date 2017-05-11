#ifndef BOMBE_HH_
# define BOMBE_HH_

# include <cstdint>
# include <iostream>
# include <irrlicht.h>

# include "bomber.hh"

namespace	bomber
{
  class	Bombe
    {
    public:
      Bombe(bomber::v2d const &, int);
      ~Bombe();

      // void		time_for_explosion();

    private:
      int		_x;
      int		_y;
      int		_range;
      irr::u32		_time;

    public:
      int		getX() const;
      int		getY() const;
      int		getRange() const;
      irr::u32		getTime() const;
      bomber::v2d	getPos() const;

      void		setTime(irr::u32 time);
    };
}

#endif // !BOMBE_HH_

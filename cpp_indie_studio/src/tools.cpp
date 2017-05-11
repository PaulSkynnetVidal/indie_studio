# include "bomber.hh"

namespace	bomber
{
  v2d	getMovVector(bomber::e_direction dir)
    {
      switch (dir)
	{
	case D_UP:
	  return (bomber::v2d(-1, 0));
	case D_DOWN:
	  return (bomber::v2d(1, 0));
	case D_LEFT:
	  return (bomber::v2d(0, -1));
	case D_RIGHT:
	  return (bomber::v2d(0, 1));
	}
    }

  irr::u32	getRotValue(bomber::e_direction dir)
    {
      switch (dir)
        {
        case D_UP:
          return ROT_FRONT;
        case D_DOWN:
          return ROT_BACK;
        case D_LEFT:
          return ROT_LEFT;
        case D_RIGHT:
          return ROT_RIGHT;
      }
    }

}

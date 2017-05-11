#ifndef BOMBER_HH_
# define BOMBER_HH_

# include <irrlicht.h>

# define DEFAULT_BPP 24

# define MENU_TITLE L"BomberTrash - Menu"
# define MENU_DIM(c) ((c) == 'x' ? 800 : ((c) == 'y' ? 600 : 0))

# define GAME_TITLE L"BomberTrash - Game"
# define GAME_DIM(c) ((c) == 'x' ? 1024 : ((c) == 'y' ? 768 : 0))

# define PRESS_DOWN true
# define PRESS_UP false

# define MOV_SPD 250
# define BOMB_TIME 3000
# define EXP_TIME 500
# define BONUS_LUCK 7 // NOTE: Has to be higher than number of bonuses

# define MAX_BOMB 4
# define MAX_RANGE 5
# define MAX_SPEED 5

namespace	bomber
{
    typedef irr::core::position2di	v2d;

    enum	e_rotation
      {
        ROT_FRONT = 270,
        ROT_RIGHT = 0,
        ROT_BACK = 90,
        ROT_LEFT = 180
      };

    enum	e_bonus
      {
        B_SPEED,
        B_RANGE,
        B_BOMB
      };

    enum	e_direction
      {
        D_UP,
        D_DOWN,
        D_RIGHT,
        D_LEFT
      };

    irr::u32	getRotValue(e_direction);
    v2d		getMovVector(e_direction);
}

#endif

#ifndef BOMBERBLOKE_HPP
#define BOMBERBLOKE_HPP

#include "engine.hpp"

#define DEFAULT_BLOKE_SIZE 0.9
#define ACCELERATION_RATIO 0.75
#define DECCELERATION_RATIO 0.5
#define DEFAULT_SPEED double(0.1 / TICK_RATE)
#define DEFAULT_MAX_SPEED double(0.5 / TICK_RATE)
#define DEFAULT_BOMB_TIMER 5*TICK_RATE
#define MAX_BOMBS 10
#define BOMB_SIZE 0.75

extern double _zoom;
extern double _bloke_size[2];

extern unsigned int  _default_bomb_timer;
class bomb;
class bloke;

enum powerups{
  SATELLITE,
  KICK,
  PENETRATION
};

 enum flags{
  FLAG_NONE = 0,
  FLAG_DEAD,
};

enum block_types{
  EMPTY,
  RESERVED,
  SPAWN_POINT,
  WOOD
};

#include "bomberbloke_actors.hpp"

/* Cereal magic: include all actor types here so cereal knows about them */
#include "bomb.hpp"
#include "bloke.hpp"
#include "woodenCrate.hpp"
#include "BomberBlokeScene.hpp"

#endif

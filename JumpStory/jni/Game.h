#ifndef GAME_H_
#define GAME_H_

#include "Global.h"
#include "World.h"

class Game{
  World world;
public:
  Game();
  void draw();
  void update(float dt);
  void save();
  void resume();
};

#endif // GAME_H_

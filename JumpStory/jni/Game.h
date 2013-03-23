#ifndef GAME_H_
#define GAME_H_

#include "Global.h"
#include "World.h"
#include "Menu.h"
#include "GameState.h"

class Game{
  World world;
  Menu menu;
  FPS fps;
  void drawFps();
public:
  Game();
  void draw();
  void update(float dt);
  void save();
  void resume();

  void touch(int x, int y);
  void keyDown(uint keyCode);
};

#endif // GAME_H_

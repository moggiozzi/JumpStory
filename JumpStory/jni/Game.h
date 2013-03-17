#ifndef GAME_H_
#define GAME_H_

#include "Global.h"
#include "World.h"
enum GameState{
  S_MENU, S_INGAME, S_GAMEOVER, S_PAUSE,
};

class Game{
  World world;
  FPS fps;
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

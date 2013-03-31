#ifndef GAME_H_
#define GAME_H_

#ifndef GLOBAL_H_
#include "Global.h"
#endif
#ifndef WORLD_H_
#include "World.h"
#endif
#ifndef MENU_H_
#include "Menu.h"
#endif
#ifndef GAMESTATE_H_
#include "GameState.h"
#endif
#ifndef FPS_H_
#include "Fps.h"
#endif
class Game{
  World world;
  Menu menu;
  Fps fps;
  void drawFps();
public:
  Game();
  bool init();
  void draw();
  void update(float dt);
  void save();
  void resume();

  void touch(int x, int y);
  bool keyDown(uint keyCode);
};

#endif // GAME_H_

#ifndef MENU_H_
#define MENU_H_

#include "Global.h"

class Menu{
public:
  bool init();
  void update(float dt){}
  void draw();
  void touch(int x, int y);
  void keyDown(uint keyCode);
};

#endif

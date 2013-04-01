#ifndef WORLD_H_
#define WORLD_H_

#ifndef GLHELPER_H_
#include "GLHelper.h"
#endif
#ifndef COLLISION_LAYER_H_
#include "CollisionLayer.h"
#endif
#ifndef CHARACTER_H_
#include "Character.h"
#endif

class World{
  Vector2<int> bottomLeft; // координаты нижней левой точки с которой надо рисовать "мир"
  CollisionLayer collisionLayer;
  Character *character;
public:
  World() : character(0) {}
  ~World(){}
  //Vector2f getSize(){return size;}
  bool init();
  void initLevel();
  void draw();
  void update(float dt);
  bool keyDown(uint keyCode);
  void touch(int x, int y);
};

#endif // WORLD_H_

#ifndef WORLD_H_
#define WORLD_H_

#include "GLHelper.h"
#include "CollisionLayer.h"
#include "Character.h"

class World{
  float g;
  Vector2 bottomLeft; // координаты нижней левой точки с которой надо рисовать "мир"
  CollisionLayer collisionLayer;
  Character *character;

  Vector2f charPos, charSpeed, charMaxSpeed, worldSpeed;
public:
  World(){}
  //Vector2f getSize(){return size;}
  void init();
  void draw();
  void update(float dt);
  void keyDown(uint keyCode);
  void touch(int x, int y);
};

#endif // WORLD_H_

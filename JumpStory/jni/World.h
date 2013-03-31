#ifndef WORLD_H_
#define WORLD_H_

#include "GLHelper.h"
#include "CollisionLayer.h"
#include "Character.h"

class World{
  float g;
  Vector2<int> bottomLeft; // ���������� ������ ����� ����� � ������� ���� �������� "���"
  CollisionLayer collisionLayer;
  Character *character;

  Vector2<float> charPos, charSpeed, charMaxSpeed, worldSpeed;
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

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

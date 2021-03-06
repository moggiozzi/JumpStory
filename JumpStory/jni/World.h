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

#include "Mummy.h"

class World{
  Vector2<int> bottomLeft; // ���������� ������ ����� ����� � ������� ���� �������� "���"
  CollisionLayer collisionLayer;
  Character *character;
  Mummy *mummy;
  uint score;
public:
  World() : character(0) {}
  ~World(){}
  //Vector2f getSize(){return size;}
  bool init();
  void initLevel();
  void draw(bool isActive=true);
  void update(float dt);

  bool keyDown(uint keyCode);
  void touch(int x, int y);
  void accel(float x, float y, float z);
  
  uint getSaveDataSize();
  void saveTo(char *data);
  void loadFrom(const char *data, const char * const dataEnd);
};

#endif // WORLD_H_

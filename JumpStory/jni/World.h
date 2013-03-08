#ifndef WORLD_H_
#define WORLD_H_

#include "GLHelper.h"
#include "CollisionLayer.h"

class World{
  double g;
  //Vector2<> size;
  //Rect<int> viewPort;
  CollisionLayer collisionLayer;
public:
  World():g(9.81){}
  //Vector2f getSize(){return size;}
  void init();
  void draw();
  void update(double dt);
};

#endif // WORLD_H_

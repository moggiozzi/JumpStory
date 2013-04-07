#ifndef MUMMY_H_
#define MUMMY_H_

#include "Primitives.h"
#include "Sprite.h"
#include "CollisionLayer.h"

class Mummy{
  Vector2<float> pos;
  Vector2<float> speed;
  float angle;
  bool isLeft;
  Sprite sprite;
public:
  Mummy(Texture *tex);
  ~Mummy();
  void draw();
  void update(float dt, CollisionLayer& collisionLayer);

  void setPos(float x, float y){ pos.set(x,y); }
  int getWidth(){return sprite.getWidth();}
  int getHeight(){return sprite.getHeight();}
  float getX(){return pos.x();}
  float getY(){return pos.y();}

};

#endif
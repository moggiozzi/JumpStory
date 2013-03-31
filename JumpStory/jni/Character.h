#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Helper.h"
#include "Sprite.h"

class Character{
  Vector2<float> pos;
  Vector2<float> speed;
  Sprite *sprite;
public:
  Character(Texture *charTex);
  ~Character();
  void draw();
  void update(float dt);

  void setPos(float x, float y){ pos.set(x,y); }
  int getWidth(){return sprite->getWidth();}
  int getHeight(){return sprite->getHeight();}
  float getX(){return pos.x();}
  float getY(){return pos.y();}
};

#endif // CHARACTER_H_
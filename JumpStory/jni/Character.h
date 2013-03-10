#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Helper.h"
#include "Sprite.h"

class Character{
  Vector2f pos;
  Vector2f speed;
  Sprite *sprite;
public:
  Character(Texture *charTex);
  void draw();
  void update(float dt);

  void setPos(float x, float y){pos.x=x;pos.y=y;}
  int getWidth(){return sprite->texture->width;}
  int getHeight(){return sprite->texture->height;}
  float getX(){return pos.x;}
  float getY(){return pos.y;}
};

#endif // CHARACTER_H_
#ifndef CHARACTER_H_
#define CHARACTER_H_

#ifndef PRIMITIVES_H_
#include "Primitives.h"
#endif
#ifndef SPRITE_H_
#include "Sprite.h"
#endif
#ifndef WORLD_INFO_H_
#include "WorldInfo.h"
#endif
#ifndef COLLISION_LAYER_H_
#include "CollisionLayer.h"
#endif

class Character{
  Vector2<float> pos;
  Vector2<float> speed, maxSpeed;
  Sprite *sprite;
  float maxJumpHeight;
public:
  Character(Texture *charTex);
  ~Character();
  void draw();
  void update(float dt, CollisionLayer& collisionLayer);

  void setPos(const Vector2<float>& p){pos.set(p.x(),p.y());}
  void setPos(float x, float y){ pos.set(x,y); }
  void setPosX(float x){ pos.setX(x); }
  void setPosY(float y){ pos.setY(y); }
  int getWidth(){return sprite->getWidth();}
  int getHeight(){return sprite->getHeight();}
  Vector2<float> getPos(){return pos;}
  float getPosX(){return pos.x();}
  float getPosY(){return pos.y();}
  Vector2<float> getSpeed(){return speed;}
  void setSpeed(float x, float y){speed.set(x,y);}
  void setSpeedX(float x);
  void setSpeedY(float y);
  Vector2<float> getMaxSpeed(){return maxSpeed;}
  void setMaxSpeed(float x, float y){
    maxSpeed.set(x,y);
  }

};

#endif // CHARACTER_H_

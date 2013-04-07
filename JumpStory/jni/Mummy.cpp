#include "Mummy.h"
#include "GLHelper.h"
#include "WorldInfo.h"

Mummy::Mummy(Texture *tex):
  sprite(tex), angle(0), speed(100,0) {}

void Mummy::draw(){
  Vector2<int> p(worldToDeviceX(pos.x()), worldToDeviceY(pos.y()));
  sprite.draw(p,angle);
}

void Mummy::update(float dt, CollisionLayer& collisionLayer){
  Segment<int> s = collisionLayer.getSegments()[1];
  float nx = pos.x(), ny = s.y1() + (float)getHeight();
  if ( nx < s.x1()-(float)getWidth()/2.0f ){
    nx = s.x1()-(float)getWidth()/2.0f;
    isLeft = false;
  }
  if ( nx > s.x2()-(float)getWidth()/2.0f ) {
    nx = s.x2()-(float)getWidth()/2.0f;
    isLeft = true;
  }
  if (isLeft){
    angle += dt*speed.x()*2;
    nx -= dt*speed.x();
  } else {
    angle -= dt*speed.x()*2;
    nx += dt*speed.x();
  }
  pos.set(nx,ny);
}

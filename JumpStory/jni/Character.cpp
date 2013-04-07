#include "Character.h"
#include "WorldInfo.h"

#include "GameState.h"
#include "AudioHelper.h"
#include "CollisionLayer.h"

int jumpSoundId;

void Character::setSpeedX(float x){
  if ( fabs(x)>fabs(maxSpeed.x()) )
    speed.setX( maxSpeed.x()*sign(x) );
  else
    speed.setX( x );
}
void Character::setSpeedY(float y){
  if ( fabs(y)>fabs(maxSpeed.y()) )
    speed.setY( maxSpeed.y()*sign(y) );
  else
    speed.setY( y );
}

Character::Character(Texture *charTex){
  sprite = new Sprite(charTex);
  AudioHelper::open("res/jump.ogg", jumpSoundId, false);
}

Character::~Character(){
  delete sprite;
}

void Character::draw(){
  sprite->draw( worldToDeviceX(pos.x()), worldToDeviceY(pos.y()));//.x - worldX), (int) (GLHelper::getHeight() - (pos.y - worldY)));
}

void Character::update(float dt, CollisionLayer& collisionLayer){
  // обновить чара
  float nx = pos.x()+speed.x()*dt;
  float ny = pos.y()+speed.y()*dt;
  if(speed.y()<0 && 
     collisionLayer.isIntersect(
       pos.x()+getWidth()/4.0f,
       pos.y()-getHeight(),
       nx+getWidth()/4.0f,
       ny-getHeight(), getWidth()/2.0f)
    ){ // Столкнулись. Надо поменять направление.
    speed.setY( maxSpeed.y());
    pos.set(pos.x()+speed.x()*dt, pos.y()+speed.y()*dt);
    AudioHelper::play(jumpSoundId);
  }else{
    setPos(nx, ny);
  }
  if(-speed.y()<maxSpeed.y())
    speed.setY( speed.y() - g*dt );
  if(abs(speed.x())>g/10.0f)
    if(speed.x()>0)
      speed.setX(speed.x() - g*dt/2.0f);
    else
      speed.setX(speed.x() + g*dt/2.0f);
  else
    speed.setX(0.0f);
  if((int)pos.x() < -(int)getWidth())
    pos.setX((float)GLHelper::getWidth());
  if(pos.x() > GLHelper::getWidth())
    pos.setX((float)-getWidth());
  if( pos.y() < worldMaxY-GLHelper::getWidth()/2 )
    setGameState( GS_GAMEOVER );
}

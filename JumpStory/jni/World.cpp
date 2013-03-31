#include "World.h"
#include "ResourceManager.h"
#include "AudioHelper.h"
#include "GameState.h"
#include "WorldInfo.h"

namespace{
  Texture charTex,platTex,bgTex,ghostTex;
  Vector2<float> ghostPos;
}

int jumpSoundId;

bool World::init(){
  ResourceManager::loadImage("res/character.png",&charTex);
  ResourceManager::loadImage("res/bg.png",&bgTex);
  ResourceManager::loadImage("res/ghost.png",&ghostTex);
  AudioHelper::open("res/jump.ogg", jumpSoundId, false);
  if (character)
    delete character;
  character = new Character(&charTex);
  collisionLayer.init();
  initLevel();
  return true;
}

void World::initLevel(){
  character->setPos(50.0f,50.0f+character->getHeight());
  charPos.set(50.0f, 50.0f+character->getHeight());
  charSpeed.set(0.0f, 0.0f);
  charMaxSpeed.set(200.0f, 400.0f);
  g = 400.0f;
  //double t = charMaxSpeed.y/g;
  //maxJumpHeight = g*t*t/2;
  maxJumpHeight = charMaxSpeed.y()*charMaxSpeed.y()/(2.0f*g)-character->getHeight();
  worldPos.set(0.0f, charPos.y() - character->getHeight()/2.0f - GLHelper::getHeight()/2.0f);
  worldMaxY = worldPos.y();
  worldSpeed.set(0.0f, GLHelper::getHeight()/2 - GLHelper::getHeight() - (charPos.y() - worldPos.y()));
  ghostPos.set(0.0f, 0.0f);
  collisionLayer.initLevel();
}

void World::draw(){
  GLHelper::setColor(0.6f,0.6f,1.0f);
  uint x = (GLHelper::getWidth() - bgTex.getWidth())/2;
  uint y = (GLHelper::getHeight() - bgTex.getHeight())/2;
  GLHelper::drawTexture(&bgTex, x, y);

  collisionLayer.draw();

  GLHelper::setColor(1.f,1.f,1.f);
  //character->draw();
  GLHelper::drawTexture(&charTex, (int)charPos.x(), (int)(GLHelper::getHeight() - (charPos.y() - worldPos.y())));

  GLHelper::setColor(1.f,1.f,1.f,0.5f);
  GLHelper::drawTexture(&ghostTex, (int)ghostPos.x(),(int)(GLHelper::getHeight() -(ghostPos.y()-worldPos.y())));
}

void World::update(float dt){
  // обновить чара
  float nx = charPos.x()+charSpeed.x()*dt;
  float ny = charPos.y()+charSpeed.y()*dt;
  if(charSpeed.y()<0 && 
     collisionLayer.isIntersect(
       charPos.x()+character->getWidth()/4.0f,
       charPos.y()-character->getHeight(),
       nx+character->getWidth()/4.0f,
       ny-character->getHeight(), character->getWidth()/2.0f)
    ){ // —толкнулись. Ќадо помен€ть направление.
    charSpeed.setY(charMaxSpeed.y());
    charPos.set(charPos.x()+charSpeed.x()*dt, charPos.y()+charSpeed.y()*dt);
    AudioHelper::play(jumpSoundId);
  }else{
    charPos.set(nx, ny);
  }
  if(-charSpeed.y()<charMaxSpeed.y())
    charSpeed.setY( charSpeed.y() - g*dt );
  if(abs(charSpeed.x())>g/10.0f)
    if(charSpeed.x()>0)
      charSpeed.setX(charSpeed.x() - g*dt/2.0f);
    else
      charSpeed.setX(charSpeed.x() + g*dt/2.0f);
  else
    charSpeed.setX(0);
  if((int)charPos.x() < -(int)character->getWidth())
    charPos.setX((float)GLHelper::getWidth());
  if(charPos.x() > GLHelper::getWidth())
    charPos.setX((float)-character->getWidth());
  if( charPos.y() < worldMaxY-GLHelper::getWidth()/2 )
    setGameState( GS_GAMEOVER );

  // обновить мир
  float nWorldY = charPos.y() - character->getHeight()/2 - GLHelper::getHeight()/2;
  float d = nWorldY-worldPos.y();
  worldSpeed.setY(d*4.0f*charMaxSpeed.y()/GLHelper::getHeight());
  //if ( worldY + worldSpeed.y*dt > worldMaxY-64 )
  worldPos.setY(worldPos.y() + worldSpeed.y()*dt);
  if ( worldPos.y() > worldMaxY )
    worldMaxY = worldPos.y();

  collisionLayer.update();

  // враги
  ghostPos.setX( ghostPos.x() + g/4*dt );
  if( ghostPos.x() > GLHelper::getWidth())
    ghostPos.setX( -(float)ghostTex.getWidth() );
  ghostPos.setY( ghostPos.y() + g/4*dt );
  if(ghostPos.y()-worldPos.y()-ghostTex.getHeight()>GLHelper::getHeight())
    ghostPos.setY( worldPos.y() );
}

bool World::keyDown(uint keyCode){
  if (keyCode == KEY_ESC){
    setGameState(GS_PAUSE);
    return true;
  }
  switch(keyCode){
  case KEY_LEFT:
    charSpeed.setX( -charMaxSpeed.x() );
    return true;
    break;
  case KEY_RIGHT:
    charSpeed.setX( charMaxSpeed.x() );
    return true;
    break;
  }
  return false;
}

void World::touch(int x, int y){
  if(x<GLHelper::getWidth()/2)
    keyDown(KEY_LEFT);
  else
    keyDown(KEY_RIGHT);
}
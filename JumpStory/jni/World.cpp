#include "World.h"
#include "ResourceManager.h"
#include "AudioHelper.h"
#include "GameState.h"
#include "WorldInfo.h"

namespace{
  Texture charTex,platTex,bgTex,ghostTex;
  Vector2<float> ghostPos;
}

bool World::init(){
  ResourceManager::loadImage("res/character.png",&charTex);
  ResourceManager::loadImage("res/bg.png",&bgTex);
  ResourceManager::loadImage("res/ghost.png",&ghostTex);
  if (character)
    delete character;
  character = new Character(&charTex);
  collisionLayer.init();
  initLevel();
  return true;
}

void World::initLevel(){
  character->setPos(50.0f,50.0f+character->getHeight());
  character->setSpeed(0.0f, 0.0f);
  character->setMaxSpeed(200.0f, 400.0f);

  worldPos.set(0.0f, character->getPosY() - character->getHeight()/2.0f - GLHelper::getHeight()/2.0f);
  worldMaxY = worldPos.y();
  worldSpeed.set(0.0f, GLHelper::getHeight()/2 - GLHelper::getHeight() - (character->getPosY() - worldPos.y()));

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
  character->draw();

  GLHelper::setColor(1.f,1.f,1.f,0.5f);
  GLHelper::drawTexture(&ghostTex, (int)ghostPos.x(),(int)(GLHelper::getHeight() -(ghostPos.y()-worldPos.y())));
}

void World::update(float dt){
  // обновить чара
  character->update(dt, collisionLayer);

  // обновить мир
  float nWorldY = character->getPosY() - character->getHeight()/2 - GLHelper::getHeight()/2;
  float d = nWorldY-worldPos.y();
  worldSpeed.setY(d*4.0f*character->getMaxSpeed().y()/GLHelper::getHeight());
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
    character->setSpeedX( -character->getMaxSpeed().x() );
    return true;
    break;
  case KEY_RIGHT:
    character->setSpeedX( character->getMaxSpeed().x() );
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
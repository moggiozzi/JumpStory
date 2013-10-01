#include "World.h"
#include "ResourceManager.h"
#include "AudioHelper.h"
#include "GameState.h"
#include "WorldInfo.h"

namespace{
  Texture charTex,platTex,bgTex,ghostTex,mummyTex;
  Vector2<float> ghostPos;
}

#define charMaxSpeedX 200.0f
#define charMaxSpeedY 400.0f

bool World::init(){
  ResourceManager::loadImage("res/character.png",&charTex);
  //ResourceManager::loadImage("res/bg.png",&bgTex);
  ResourceManager::loadImage("res/ghost.png",&ghostTex);
  ResourceManager::loadImage("res/mummy.png",&mummyTex);
  if (character)
    delete character;
  character = new Character(&charTex);
  mummy = new Mummy(&mummyTex);

  maxJumpDist.setY( charMaxSpeedY*charMaxSpeedY/(2.0f*g) - character->getHeight() );
  maxJumpDist.setX( maxJumpDist.y() );

  collisionLayer.init();
  initLevel();
  return true;
}

void World::initLevel(){
  score = 0;
  character->setPos(50.0f,50.0f+character->getHeight());
  character->setSpeed(0.0f, 0.0f);
  character->setMaxSpeed(charMaxSpeedX, charMaxSpeedY);

  worldPos.set(0.0f, character->getPosY() - character->getHeight()/2.0f - GLHelper::getHeight()/2.0f);
  worldPos.setY(-64);
  worldMaxY = worldPos.y();
  worldSpeed.set(0.0f, GLHelper::getHeight()/2 - GLHelper::getHeight() - (character->getPosY() - worldPos.y()));

  ghostPos.set(0.0f, 0.0f);

  collisionLayer.initLevel();
}

void World::draw(bool isActive){
  GLHelper::setColor(0.6f,0.6f,1.0f);
  uint x = (GLHelper::getWidth() - bgTex.getWidth())/2;
  uint y = (GLHelper::getHeight() - bgTex.getHeight())/2;
  GLHelper::drawTexture(&bgTex, x, y);

  collisionLayer.draw();

  GLHelper::setColor(1.f,1.f,1.f);

  if(!isActive)
    return;
  character->draw();
  
  mummy->draw();

  GLHelper::setColor(1.f,1.f,1.f,0.5f);
  GLHelper::drawTexture(&ghostTex, (int)ghostPos.x(),(int)(GLHelper::getHeight() -(ghostPos.y()-worldPos.y())));

  static char scoreText[16];
  GLHelper::setColor(0.f,1.f,0.f);
  sprintf(scoreText,"Score: %d", score);
  GLHelper::drawText(0,16,scoreText);
}

void World::update(float dt){
  // обновить чара
  character->update(dt, collisionLayer);

  if ( score < character->getPosY() )
    score = (uint)character->getPosY();

  mummy->update(dt, collisionLayer);

  // обновить мир
  float nWorldY = character->getPosY() - character->getHeight()/2 - GLHelper::getHeight()/2;
  float d = nWorldY-worldPos.y();
  worldSpeed.setY(d*3.0f*character->getMaxSpeed().y()/GLHelper::getHeight());
  worldPos.setY(worldPos.y() + worldSpeed.y()*dt);
  if ( worldPos.y() > worldMaxY )
    worldMaxY = worldPos.y();

  collisionLayer.update();

  // враги
  static float ga = 0.0f;
  float dx = g/4.0*dt;
  ga+=dx;
  ghostPos.setX( ghostPos.x() + dx );
  if( ghostPos.x() > GLHelper::getWidth())
    ghostPos.setX( -(float)ghostTex.getWidth() );
  float s = sin(ga/15.0);
  ghostPos.setY( ghostPos.y() + g/4.0f*dt + s );
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

void World::accel(float x, float y, float z){
  character->setSpeedX( -x/2.0f * character->getMaxSpeed().x() );
}

uint World::getSaveDataSize(){
  uint dataSize =
		  collisionLayer.getSaveDataSize() +
		  3*sizeof(Vector2<float>);
  return dataSize;
}
void World::saveTo(char *data){
  *((Vector2<float>*)data) = character->getPos();
  data += sizeof(Vector2<float>);
  *((Vector2<float>*)data) = ghostPos;
  data += sizeof(Vector2<float>);
  *((Vector2<float>*)data) = worldPos;
  data += sizeof(Vector2<float>);
  collisionLayer.saveTo(data);
}
void World::loadFrom(const char *data, const char * const dataEnd){
  int s = 3*sizeof(Vector2<float>);
  if (dataEnd < data+s) {
    LOGI("Error: World::loadFrom() not valid data");
    return;
  }
  character->setPos( *((Vector2<float>*)data) );
  data += sizeof(Vector2<float>);
  ghostPos.set( *((Vector2<float>*)data) );
  data += sizeof(Vector2<float>);
  worldPos.set( *((Vector2<float>*)data) );
  data += sizeof(Vector2<float>);
  collisionLayer.loadFrom(data, dataEnd);
}

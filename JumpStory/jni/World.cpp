#include "World.h"
#include "ResourceManager.h"
#include "AudioHelper.h"

namespace{
  Texture charTex,platTex,bgTex,ghostTex;
  Vector2f ghostPos;
}

int jumpSoundId;

void World::init(){
  ResourceManager::loadImage("res/character.png",&charTex);
  ResourceManager::loadImage("res/bg.png",&bgTex);
  ResourceManager::loadImage("res/ghost.png",&ghostTex);
  AudioHelper::open("res/jump.ogg", jumpSoundId, false);
  character = new Character(&charTex);
  character->setPos(50.0f,50.0f+character->getHeight());
  charPos.x = 50.0f;
  charPos.y = 50.0f+character->getHeight();
  charSpeed.x=0.0f;
  charSpeed.y=0.0f;
  charMaxSpeed.y=400.0f;
  charMaxSpeed.x=200.0f;
  g = 400.0f;
  //double t = charMaxSpeed.y/g;
  //maxJumpHeight = g*t*t/2;
  maxJumpHeight = charMaxSpeed.y*charMaxSpeed.y/(2*g)-character->getHeight();
  worldX = 0; //character->getX()+character->getWidth+GLHelper::getWidth;
  worldY = charPos.y - character->getHeight()/2 - GLHelper::getHeight()/2;
  worldSpeed.x = 0;
  worldSpeed.y = (GLHelper::getHeight()/2 - GLHelper::getHeight() - (charPos.y - worldY));
  ghostPos.x=0;
  ghostPos.y=0;

  collisionLayer.init();
}

void World::draw(){
  GLHelper::setColor(0.6f,0.6f,1.0f);
  uint x = (GLHelper::getWidth() - bgTex.width)/2;
  uint y = (GLHelper::getHeight() - bgTex.height)/2;
  GLHelper::drawTexture(&bgTex, x, y);

  collisionLayer.draw();

  GLHelper::setColor(1.f,1.f,1.f);
  //character->draw();
  GLHelper::drawTexture(&charTex, (int)charPos.x, (int)(GLHelper::getHeight() - (charPos.y - worldY)));

  GLHelper::setColor(1.f,1.f,1.f,0.5f);
  GLHelper::drawTexture(&ghostTex, (int)ghostPos.x,(int)(GLHelper::getHeight() -(ghostPos.y-worldY)));
}

void World::update(float dt){
  // �������� ����
  float nx = charPos.x+charSpeed.x*dt;
  float ny = charPos.y+charSpeed.y*dt;
  if(charSpeed.y<0 && 
     collisionLayer.isIntersect(
       charPos.x+character->getWidth()/4,
       charPos.y-character->getHeight(),
       nx+character->getWidth()/4,
       ny-character->getHeight(), character->getWidth()/2.0f)
    ){ // �����������. ���� �������� �����������.
    charSpeed.y = charMaxSpeed.y;
    charPos.x = charPos.x+charSpeed.x*dt;
    charPos.y = charPos.y+charSpeed.y*dt;
    AudioHelper::play(jumpSoundId);
  }else{
    charPos.x = nx;
    charPos.y = ny;
  }
  if(-charSpeed.y<charMaxSpeed.y)
    charSpeed.y -= g*dt;
  if(abs(charSpeed.x)>g/10)
    if(charSpeed.x>0)
      charSpeed.x -= g*dt/2;
    else
      charSpeed.x += g*dt/2;
  else
    charSpeed.x = 0;
  if((int)charPos.x < -(int)character->getWidth())
    charPos.x = (float)GLHelper::getWidth();
  if(charPos.x > GLHelper::getWidth())
    charPos.x = (float)-character->getWidth();
  
  // �������� ���
  float nWorldY = charPos.y - character->getHeight()/2 - GLHelper::getHeight()/2;
  float d = nWorldY-worldY;
  worldSpeed.y = d*4.0f*charMaxSpeed.y/GLHelper::getHeight();
  worldY += worldSpeed.y*dt;
  collisionLayer.update();

  // �����
  ghostPos.x += g/4*dt;
  if( ghostPos.x > GLHelper::getWidth())
    ghostPos.x = -(float)ghostTex.width;
  ghostPos.y += g/4*dt;
  if(ghostPos.y-worldY-ghostTex.height>GLHelper::getHeight())
    ghostPos.y=worldY;
}

void World::keyDown(uint keyCode){
  switch(keyCode){
  case KEY_LEFT:
    charSpeed.x = -charMaxSpeed.x;
    break;
  case KEY_RIGHT:
    charSpeed.x = charMaxSpeed.x;
    break;

  }
}

void World::touch(int x, int y){
  if(x<GLHelper::getWidth()/2)
    keyDown(KEY_LEFT);
  else
    keyDown(KEY_RIGHT);
}
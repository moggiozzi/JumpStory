#include "World.h"
#include "ResourceManager.h"

namespace{
  Texture charTex,platTex,bgTex,ghostTex;
  Vector2f ghostPos;
}

void World::init(){
  collisionLayer.generate();
  ResourceManager::loadImage("character.png",&charTex);
  ResourceManager::loadImage("bg.png",&bgTex);
  ResourceManager::loadImage("ghost.png",&ghostTex);
  character = new Character(&charTex);
  character->setPos(50.0f,50.0f+character->getHeight());
  charPos.x = 50.0f;
  charPos.y = 50.0f+character->getHeight();
  charSpeed.x=0.0f;
  charSpeed.y=0.0f;
  charMaxSpeed.y=400.0f;
  charMaxSpeed.x=200.0f;
  g = 400.0f;
  worldX = 0; //character->getX()+character->getWidth+GLHelper::getWidth;
  worldY = charPos.y - character->getHeight()/2 - GLHelper::getHeight()/2;
  worldSpeed.x = 0;
  worldSpeed.y = (GLHelper::getHeight()/2 - GLHelper::getHeight() - (charPos.y - worldY));
  ghostPos.x=0; 
  ghostPos.y=0;
}

void World::draw(){
  GLHelper::setColor(0.5f,0.5f,0.9f);
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
  // обновить чара
  float nx = charPos.x+charSpeed.x*dt;
  float ny = charPos.y+charSpeed.y*dt;
  if(charSpeed.y<0 && 
     collisionLayer.isIntersect(
       charPos.x+character->getWidth()/4,
       charPos.y-character->getHeight(),
       nx+character->getWidth()/4,
       ny-character->getHeight(), character->getWidth()/2.0f)
    ){ // —толкнулись. Ќадо помен€ть направление.
    charSpeed.y = charMaxSpeed.y;
    charPos.x = charPos.x+charSpeed.x*dt;
    charPos.y = charPos.y+charSpeed.y*dt;
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
  
  // обновить мир
  float nWorldY = charPos.y - character->getHeight()/2 - GLHelper::getHeight()/2;
  float d = nWorldY-worldY;
  worldSpeed.y = d*4.0f*charMaxSpeed.y/GLHelper::getHeight();
  worldY += worldSpeed.y*dt;

  // враги
  ghostPos.x += g/4*dt;
  if( ghostPos.x > GLHelper::getWidth())
    ghostPos.x = -(float)ghostTex.width;
  ghostPos.y += g/4*dt;
  if(ghostPos.y-worldY-ghostTex.height>GLHelper::getHeight())
    ghostPos.y=worldY;
}

void World::keyDown(uint keyCode){
  switch(keyCode){
  case VK_LEFT:
    charSpeed.x = -charMaxSpeed.x;
    break;
  case VK_RIGHT:
    charSpeed.x = charMaxSpeed.x;
    break;

  }
}

void World::touch(int x, int y){
  if(x<GLHelper::getWidth()/2)
    keyDown(VK_LEFT);
  else
    keyDown(VK_RIGHT);
}
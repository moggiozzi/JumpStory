#include "CollisionLayer.h"
#include "GLHelper.h"
#include "ResourceManager.h"
#include <algorithm>

#define platformTypeCnt 4
int widthTypes[platformTypeCnt]={ 64, 128, 192, 64 };
Texture textures[4];

CollisionLayer::CollisionLayer(){
}

void CollisionLayer::init(){
  ResourceManager::loadImage("res/pl64.png",&textures[0]);
  ResourceManager::loadImage("res/pl128.png",&textures[1]);
  ResourceManager::loadImage("res/pl192.png",&textures[2]);
  ResourceManager::loadImage("res/pl.png",&textures[3]);
  generate();
}

bool CollisionLayer::isIntersect(float x1, float y1, float x2, float y2, float w){
  // todo оптимизировать
  for(uint i=0;i<segments.size();i++){

    if((x1>segments[i].x1 && x1<segments[i].x2) || 
       (x1+w>segments[i].x1 && x1+w<segments[i].x2) )
      if((y1>=segments[i].y1 && y2<=segments[i].y1)||
         (y1<=segments[i].y1 && y2>=segments[i].y1))
         return true;
  }
  return false;
}

void CollisionLayer::draw(){
  uint w = GLHelper::getWidth(),
       h = GLHelper::getHeight();
  uint n = segments.size();
  for(uint i=0;i<n;i++) {
    int w = segments[i].getWidth();
    uint j=0;
    for(;j<platformTypeCnt-1;j++){
      if(w==widthTypes[j]) {
        GLHelper::drawTexture(&textures[j], worldToDeviceX(segments[i].x1), worldToDeviceY(segments[i].y1)-16);
        break;
      }
    }
    if(j==platformTypeCnt-1){
      int x = segments[i].x1;
      while(x<segments[i].x2){
        GLHelper::drawTexture(&textures[j], worldToDeviceX(x), worldToDeviceY(segments[i].y1)-16);
        x+=widthTypes[j];
      }
    }
    GLHelper::drawLine2d( worldToDeviceX(segments[i].x1), worldToDeviceY(segments[i].y1),
      worldToDeviceX(segments[i].x2), worldToDeviceY(segments[i].y2) );
  }
}

void CollisionLayer::generate(){
  segments.clear();

  Segment s(-100,0,GLHelper::getWidth()+100,0);
  segments.push_back(s);

  int platformHeight = 64;
  uint w = GLHelper::getWidth();
  int x = 0;
  while(x<GLHelper::getHeight()*2)
  {
    int k = rand()%3;
    s.x1 = rand()%(w - widthTypes[k]);
    s.x2 = s.x1 + widthTypes[k];
    x = s.y1 = s.y2 = x + rand() % (maxJumpHeight-64)+64;
    segments.push_back(s);
  }
}
void CollisionLayer::update(){
  for(uint i=0;i<segments.size();i++){
    if(worldY - segments[i].y1 > 64){
      int k = rand()%3;
      segments[i].x1 = rand()%(GLHelper::getWidth() - widthTypes[k]);
      segments[i].x2 = segments[i].x1 + widthTypes[k];
      segments[i].y1 = segments[i].y2 = segments[i].y1 + GLHelper::getHeight()*2+64;
    }
  }
}
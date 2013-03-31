#include "CollisionLayer.h"
#include "GLHelper.h"
#include "ResourceManager.h"
#include "WorldInfo.h"
#include "Primitives.h"
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
  initLevel();
}

bool CollisionLayer::isIntersect(float x1, float y1, float x2, float y2, float w){
  // todo оптимизировать
  Rect<float> r(x1,y1,w,y2-y1);
  for(uint i=0;i<segments.size();i++){
    if ( IsIntersect<float>(r,(Segment<float>)segments[i]) )
      return true;
    if((x1>segments[i].x1() && x1<segments[i].x2()) || 
       (x1+w>segments[i].x1() && x1+w<segments[i].x2()) )
      if((y1>=segments[i].y1() && y2<=segments[i].y1())||
         (y1<=segments[i].y1() && y2>=segments[i].y1()))
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
      if(w==widthTypes[j]){
        GLHelper::drawTexture(&textures[j], worldToDeviceX((float)segments[i].x1()), worldToDeviceY((float)segments[i].y1())-16);
        break;
      }
    }
    if(j==platformTypeCnt-1){ // длинная платформа
      int x = segments[i].x1();
      while(x<segments[i].x2()){
        GLHelper::drawTexture(&textures[j], worldToDeviceX((float)x), worldToDeviceY((float)segments[i].y1())-16);
        x+=widthTypes[j];
      }
    }
    GLHelper::drawLine2d( worldToDeviceX((float)segments[i].x1()), worldToDeviceY((float)segments[i].y1()),
      worldToDeviceX((float)segments[i].x2()), worldToDeviceY((float)segments[i].y2()) );
  }
}

void CollisionLayer::initLevel(){
  segments.clear();

  Segment<int> s(-100,0,GLHelper::getWidth()+100,0);
  segments.push_back(s);

  int platformHeight = 64;
  uint w = GLHelper::getWidth();
  int y = 0, x1, x2;
  while(y<GLHelper::getHeight()*2)
  {
    int k = rand()%3;
    x1 = rand()%(w - widthTypes[k]);
    x2 = x1 + widthTypes[k];
    y = y + rand() % ((int)maxJumpHeight-64)+64;
    segments.push_back(Segment<int>(x1,y,x2,y));
  }
}

void CollisionLayer::update(){
  for(uint i=0;i<segments.size();i++){
    if(worldPos.y() - segments[i].y1() > 64){
      int k = rand()%3;
      int x1 = rand()%(GLHelper::getWidth() - widthTypes[k]);
      int x2 = x1 + widthTypes[k];
      int y = segments[i].y1() + GLHelper::getHeight()*2+64;
      segments[i].set(x1, y, x2, y);
    }
  }
}
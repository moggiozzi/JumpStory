#include "CollisionLayer.h"
#include "GLHelper.h"
#include "ResourceManager.h"
#include "WorldInfo.h"
#include "Primitives.h"
#include <algorithm>

#define platformTypeCnt 4
int widthTypes[platformTypeCnt]={ 64, 128, 192, 64 };
Texture textures[4];
const int platformHeight = 64;
uint highestSegmentIdx = 0;

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
    //GLHelper::drawLine2d( worldToDeviceX((float)segments[i].x1()), worldToDeviceY((float)segments[i].y1()),
    //  worldToDeviceX((float)segments[i].x2()), worldToDeviceY((float)segments[i].y2()) );
  }
}
void CollisionLayer::check(int curr, int prev){
  float d = getDist(segments[curr],segments[prev]);
  int w = GLHelper::getWidth();
  int y = segments[curr].y1();
  if ( d > maxJumpDist.x() ){
    int sw = segments[curr].getWidth();
    int rx1 = segments[prev].x1()-maxJumpDist.x()-sw;
    rx1 = rx1<0 ? 0 : rx1;
    int rx2 = segments[prev].x2()+maxJumpDist.x();
    rx2 = rx2 > w-sw ? w-sw : rx2;
    int x = rx1 + rand()%(rx2-rx1);
    segments[curr].set(x,y,x+sw,y);
    d = getDist(segments[curr],segments[prev]);
      //Segment<int> s(x,y,x+widthTypes[k],y);
    //float d2 = getDist(s,segments[n-2]);
    //if (d2>maxJumpDist.x())
    //  int ddd=1;
  }
  if ( d < platformHeight ) {
    y += platformHeight;
    segments[curr].setY(y);
  }
}
void CollisionLayer::initLevel(){
  segments.clear();

  Segment<int> s(-100,0,GLHelper::getWidth()+100,0);
  segments.push_back(s);

  uint w = GLHelper::getWidth();
  int y = 0, x1, x2;
  while(y<GLHelper::getHeight()*2)
  {
    int k = rand()%3;
    x1 = rand()%(w - widthTypes[k]);
    x2 = x1 + widthTypes[k];
    y = y + rand() % ((int)maxJumpDist.y()-platformHeight)+platformHeight;
    segments.push_back(Segment<int>(x1,y,x2,y));
    uint n = segments.size();
    if ( n>1 ) {
      check(n-1,n-2);
    }
  }
  highestSegmentIdx = segments.size()-1;
}

void CollisionLayer::update(){
  for(uint i=0;i<segments.size();i++){
    if(worldPos.y() - segments[i].y1() > 2*platformHeight ) {
      int k = rand()%3;
      int x1 = rand()%(GLHelper::getWidth() - widthTypes[k]);
      int x2 = x1 + widthTypes[k];
      int y = segments[highestSegmentIdx].y1() + rand() % ((int)maxJumpDist.y()-platformHeight)+platformHeight;
      segments[i].set(x1, y, x2, y);
      highestSegmentIdx = i;
      check( i, (i>0 ? i-1: segments.size()-1) );
    }
  }
}

uint CollisionLayer::getSaveDataSize(){
  //n; (pos,length),(pos,length),...
  return sizeof(uint)+segments.size()*(sizeof(Vector2<int>)+sizeof(uint));
}
void CollisionLayer::saveTo(char *data){
  *((uint*)data) = segments.size();
  data += sizeof(uint);
  for(uint i=0;i<segments.size();i++){
    *((Vector2<int>*)data) = segments[i].p1();
    data += sizeof(Vector2<int>);
    *((int*)data) = segments[i].getWidth();
    data += sizeof(int);
  }
}
void CollisionLayer::loadFrom(const char *data, const char * const dataEnd){
  if (dataEnd < data+sizeof(uint)) {
    LOGI("Error: CollisionLayer::loadFrom() not valid data");
    return;
  }
  uint n = *((uint*)data);
  data += sizeof(uint);
  int dl = n*(sizeof(Vector2<int>)+sizeof(int));
  if (dataEnd < data+dl) {
    LOGI("Error: CollisionLayer::loadFrom() not valid data");
    return;
  }
  segments.clear();
  Vector2<int> pos;
  int width;
  for(uint i=0;i<n;i++){
    pos = *((Vector2<int>*)data);
    data += sizeof(Vector2<int>);
    width = *((int*)data);
    data += sizeof(int);
    segments.push_back(Segment<int>(pos.x(),pos.y(),pos.x()+width,pos.y()));
  }
}

#include "CollisionLayer.h"
#include "GLHelper.h"

#define segCnt 100
CollisionLayer::CollisionLayer(){
}

bool CollisionLayer::isIntersect(float x1, float y1, float x2, float y2, float w){
  // todo оптимизировать
  for(int i=0;i<segments.size();i++){

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
  for(uint i=0;i<n;i++)
    GLHelper::drawLine2d(segments[i].x1-worldX,h-(segments[i].y1-worldY),
    segments[i].x2-worldX,h-(segments[i].y2-worldY));
}

void CollisionLayer::generate(){
  // todo генерация уровня
  segments.clear();

  Segment s(-100,5,GLHelper::getWidth()+100,5);
  segments.push_back(s);

  uint w = GLHelper::getWidth()/3;
  for(int i=0;i<segCnt;i++){
    s.x1 = i%3*w;
    s.x2=i%3*w+w;
    s.y1=i*w;
    s.y2=i*w;
    segments.push_back(s);
  }

}
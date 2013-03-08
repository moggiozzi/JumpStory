#include "CollisionLayer.h"
#include "GLHelper.h"

CollisionLayer::CollisionLayer(){
}

bool CollisionLayer::isIntersect(const Point& p1, const Point& p2){
  return false;
}

void CollisionLayer::draw(){
  for(int i=0;i<100;i++)
    GLHelper::drawLine2d(segments[i].x1,segments[i].y1,segments[i].x2,segments[i].y2);
}

void CollisionLayer::generate(){
  // todo генерация уровня
  segments.clear();
  uint w = GLHelper::getWidth()/3;
  Segment s(0,GLHelper::getWidth(),0,0); //
  for(int i=0;i<100;i++){
    s.x1 = i%3*w;
    s.x2=i%3*w+w;
    s.y1=i*w;
    s.y2=i*w;
    segments.push_back(s);
  }

}
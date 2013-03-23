#include "Helper.h"

int Rect::getTop(){ return y; }
int Rect::getBottom(){ return y+height; }
int Rect::getLeft(){ return x; }
int Rect::getRight(){ return x+width; }

bool Rect::isContain( int x, int y ){
  return getLeft() <= x && getRight()  >= x && 
         getTop()  <= y && getBottom() >= y;
}

bool Rect::isContain( Vector2 &point ){
  return isContain( point.y, point.y );
}

bool cmpY(Segment& s1, Segment& s2){ return s1.y1<s2.y2; }

double getDistSqr(Vector2 p1, Vector2 p2){
  return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

double getDist(Vector2 p1, Vector2 p2){
  return sqrt(getDistSqr(p1,p2));
}

double getDist(Vector2 p1, Segment s1){
  double a = getDistSqr(p1, s1.p1);
  double b = getDistSqr(p1, s1.p2);
  double c = s1.getWidth()*s1.getWidth();
  if(a>=b+c) return sqrt(b);
  if(b>=a+c) return sqrt(a);
  a=sqrt(a); b=sqrt(b); c=sqrt(c);
  double p = (a+b+c)/2.0;
  double s = sqrt(p*(p-a)*(p-b)*(p-c));
  double h = s*2.0/c;
  return h;
}

double getDist(Segment& s1, Segment& s2){
  double d1 = getDist(s1.p1,s2);
  double d2 = getDist(s1.p2,s2);
  double d3 = getDist(s2.p1,s1);
  double d4 = getDist(s2.p2,s1);
  return std::min( std::min(d1,d2), std::min(d3,d4) );
}
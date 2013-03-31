#include "Helper.h"

int Vector2::x() const{ return x_; }
int Vector2::y() const{ return y_; }
Vector2::Vector2(int x, int y) : x_(x), y_(y){}
Vector2 operator - (const Vector2& l, const Vector2& r){
  return Vector2(l.x()-r.x(),l.y()-r.y());
}
void Vector2::set(int x, int y){ x_ = x; y_ = y; }
void Vector2::setX(int x){ x_ = x; }
void Vector2::setY(int y){ y_ = y; }

Vector2f::Vector2f(float x, float y) : x_(x), y_(y){}
Vector2f::operator Vector2(){
  return Vector2(static_cast<int>(x_), static_cast<int>(y_));
}
float Vector2f::x() const{ return x_; }
float Vector2f::y() const{ return y_; }
void Vector2f::set(float x, float y){ x_ = x; y_ = y; }
void Vector2f::setX(float x){ x_ = x; }
void Vector2f::setY(float y){ y_ = y; }

Segment::Segment(int x1, int y1, int x2, int y2):
  p1_(x1,y1),p2_(x2,y2){}
Segment::Segment(Vector2 p1, Vector2 p2):p1_(p1),p2_(p2){}
int Segment::getWidth()const{return static_cast<int>(getDist(p1_,p2_));}
const Vector2& Segment::p1(){return p1_;}
const Vector2& Segment::p2(){return p2_;}

Rect::Rect( int x, int y, int w, int h) :
  pos_(x, y), size_(w, h) { }
const Vector2& Rect::getPos()const { return pos_; }
const Vector2& Rect::getSize()const { return size_; }
void Rect::setPos(Vector2 &pos){ pos_ = pos; }
void Rect::setSize(Vector2 &size){ size_ = size; }
void Rect::setX(int x){pos_.setX(x);}
void Rect::setY(int y){pos_.setY(y);}
void Rect::setWidth(int w){size_.setX(w);}
void Rect::setHeight(int h){size_.setY(h);}
int Rect::x()const{return pos_.x();}
int Rect::y()const{return pos_.y();}
int Rect::getWidth()const{return size_.x();}
int Rect::getHeight()const{return size_.y();}
int Rect::getTop()const{ return pos_.y(); }
int Rect::getBottom()const{ return pos_.y()+size_.y(); }
int Rect::getLeft()const{ return pos_.x(); }
int Rect::getRight()const{ return pos_.x()+size_.x(); }

bool Rect::isContain(const Vector2 &p )const{
  return getLeft() <= p.x() && getRight()  >= p.x() && 
         getTop()  <= p.y() && getBottom() >= p.y();
}

bool cmpY(Segment& s1, Segment& s2){ return s1.p1().y()<s2.p1().y(); }

float getDistSqr(Vector2 p1, Vector2 p2){
  return static_cast<float>( (p1.x()-p2.x())*(p1.x()-p2.x())+(p1.y()-p2.y())*(p1.y()-p2.y()) );
}

float getDist(Vector2 p1, Vector2 p2){
  return sqrt(getDistSqr(p1,p2));
}

float getDist(Vector2 p1, Segment s1){
  float a = getDistSqr(p1, s1.p1());
  float b = getDistSqr(p1, s1.p2());
  float c = static_cast<float>( s1.getWidth()*s1.getWidth() );
  if(a>=b+c) return sqrt(b);
  if(b>=a+c) return sqrt(a);
  a=sqrt(a); b=sqrt(b); c=sqrt(c);
  float p = (a+b+c)/2.0f;
  float s = sqrt(p*(p-a)*(p-b)*(p-c));
  float h = s*2.0f/c;
  return h;
}

float getDist(Segment& s1, Segment& s2){
  float d1 = getDist(s1.p1(),s2);
  float d2 = getDist(s1.p2(),s2);
  float d3 = getDist(s2.p1(),s1);
  float d4 = getDist(s2.p2(),s1);
  return std::min( std::min(d1,d2), std::min(d3,d4) );
}

bool isIntersect(Segment& s1, Segment& s2){
  return getDist(s1, s2) > 0.0f;
}
bool isIntersect(Segment& s, Rect& r){
  return r.isContain(s.p1()) || r.isContain(s.p2());
}
bool isIntersect(Rect& r, Segment s){
  return isIntersect(s,r);
}
bool isIntersect(Rect& r1, Rect& r2){
  return true;//r.isContain(r1.p1) || r.isContain(s.p2);
}

int Texture::getWidth(){ return size.x(); }
int Texture::getHeight(){ return size.y(); }
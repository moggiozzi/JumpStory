#ifndef HELPER_H_
#define HELPER_H_

#include "Global.h"
#include <algorithm>

#ifdef __ANDROID__
#define KEY_ESC   AKEYCODE_BACK
#define KEY_LEFT  AKEYCODE_DPAD_LEFT
#define KEY_RIGHT AKEYCODE_DPAD_RIGHT
#else
#include <GL/freeglut.h>
#define KEY_ESC   27
#define KEY_LEFT  GLUT_KEY_LEFT
#define KEY_RIGHT GLUT_KEY_RIGHT
#endif

class Vector2;
class Segment;
class Rect;
//float getDistSqr(Vector2 p1, Vector2 p2);
float getDist(Vector2 p1, Vector2 p2);
float getDist(Vector2 p1, Segment s1);
float getDist(Segment& s1, Segment& s2);
bool isIntersect(Segment& s1, Segment& s2);
bool isIntersect(Segment& s, Rect& r);
bool isIntersect(Rect& r, Segment s);
bool isIntersect(Rect& r1, Rect& r2);

class Vector2{
  int x_,y_;
public:
  int x() const;
  int y() const;
  void set(int x, int y);
  void setX(int x);
  void setY(int y);
  Vector2(int x = 0, int y = 0);
};
Vector2 operator - (const Vector2& l, const Vector2& r);

// todo  через шаблон
class Vector2f{
  float x_,y_;
public:
  float x() const;
  float y() const;
  Vector2f(float x = 0, float y = 0);
  void set(float x, float y);
  void setX(float x);
  void setY(float y);
  operator Vector2();
};

class Segment{
  Vector2 p1_, p2_;
public:
  const Vector2& p1();
  const Vector2& p2();
  Segment(int x1=0, int y1=0, int x2=0, int y2=0);
  Segment::Segment(Vector2 p1, Vector2 p2);
  int getWidth()const;
};
bool cmpY(Segment& s1, Segment& s2);


class Rect{
  Vector2 pos_;
  Vector2 size_;
public:
  Rect( int x=0, int y=0, int w=0, int h=0 );
  const Vector2& getPos()const;
  const Vector2& getSize()const;
  int x()const;
  int y()const;
  int getWidth()const;
  int getHeight()const;
  void setPos(Vector2 &pos);
  void setSize(Vector2 &size);
  void setX(int x);
  void setY(int y);
  void setWidth(int w);
  void setHeight(int h);
  int getTop()const;
  int getBottom()const;
  int getLeft()const;
  int getRight()const;
  bool isContain(const Vector2 &point )const;
};


class Texture {
public:
#if !defined(__ANDROID__)
  int id; // id for DevIL data
#endif
  Vector2 size;
  int getWidth();
  int getHeight();
  uint format;
  /// флаг генерации GL текстуры
  bool isGenTexNameGl;
  /// "имя" текстуры GL
  uint texNameGl;
  char *pixels;
  Texture(): isGenTexNameGl(false), pixels(0) {}
};

class FPS{
#define maxSpansCnt 100
  float spans[maxSpansCnt];
  uint currentSpanIdx;
  uint currentSpanCnt;
public:
  FPS():currentSpanIdx(0),currentSpanCnt(0){
    for(uint i=0;i<maxSpansCnt;i++){
      spans[i]=0;
    }
  }
  void add(float span){
    spans[currentSpanIdx]=span;
    currentSpanIdx=(currentSpanIdx+1)%maxSpansCnt;
    if(currentSpanCnt<maxSpansCnt)
      currentSpanCnt++;
  }
  uint getFps(){
    float sum = 0;
    for(uint i=0;i<currentSpanCnt;i++)
      sum+=spans[i];
    if(sum>0)
      return static_cast<uint>(currentSpanCnt/sum);
    else
      return 0;
  }
};

#endif

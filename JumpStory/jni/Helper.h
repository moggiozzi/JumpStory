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

// todo  через шаблон
struct Vector2f{
  float x,y;
};
struct Vector2{
  int x,y;
};
#define Point Vector2
struct Segment{
  union{
    Vector2 p1;
    struct{
      int x1,y1;
    };
  };
  union{
    Vector2 p2;
    struct{
      int x2,y2;
    };
  };
  Segment(){}
  Segment(int _x1, int _y1, int _x2, int _y2):
    x1(_x1),y1(_y1),x2(_x2),y2(_y2){}
  Segment(const Vector2 &_p1, const Vector2 &_p2):
    x1(_p1.x),y1(_p1.y),x2(_p2.x),y2(_p2.y){}
  int getWidth(){return abs(x2-x1);}
};
bool cmpY(Segment& s1, Segment& s2);

double getDistSqr(Vector2 p1, Vector2 p2);
double getDist(Vector2 p1, Vector2 p2);
double getDist(Vector2 p1, Segment s1);
double getDist(Segment& s1, Segment& s2);

struct Rect{
  //	T x, y, w, h;
  //	Rect ( T _x, T _y, T _w, T _h ) :
  //		x(_x), y(_y), w(_w), h(_h) { }
  union {
    Vector2 pos;
    struct {
      int x,y;
    };
  };
  union {
    Vector2 size;
    struct {
      int width, height;
    };
  };
  Rect( int _x=0, int _y=0, int _w=0, int _h=0 ) :
    x(_x), y(_y), width(_w), height(_h) { }
  int getTop();
  int getBottom();
  int getLeft();
  int getRight();
  bool isContain( int x, int y );
  bool isContain( Vector2 &point );
};


struct Texture {
#if !defined(__ANDROID__)
  int id; // id for DevIL data
#endif
  union 
  {
    Vector2 size;
    struct{
      int width;
      int height;
    };
  };
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

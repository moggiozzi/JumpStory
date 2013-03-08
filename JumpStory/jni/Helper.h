#ifndef HELPER_H_
#define HELPER_H_

#include "Global.h"

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
};

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
    int size;
    struct {
      int w, h;
    };
  };
  Rect( int _x=0, int _y=0, int _w=0, int _h=0 ) :
    x(_x), y(_y), w(_w), h(_h) { }
};

struct Texture {
#if !defined(__ANDROID__)
  int id; // id for DevIL data
#endif
  uint width;
  uint height;
  uint format;
  /// флаг генерации GL текстуры
  bool isGenTexNameGl;
  /// "имя" текстуры GL
  uint texNameGl;
  char *pixels;
  Texture(): isGenTexNameGl(false), pixels(0) {}
};

#endif

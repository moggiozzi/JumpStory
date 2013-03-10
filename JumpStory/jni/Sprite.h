#ifndef SPRITE_H_
#define SPRITE_H_

#include "GLHelper.h"

class Sprite{

  /// прямоугольник текстуры для отрисовки
  //Rect rect;
public:
  Texture *texture;
  Sprite( Texture *tex ):texture(tex){}
  //Sprite( Texture *tex, int x, int y, int w, int h ) :
  //  rect( x, y, w, h ), texture( tex ) { }
  void draw(int x, int y);
  void draw(int x, int y, int w, int h);
};

#endif

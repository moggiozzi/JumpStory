#ifndef SPRITE_H_
#define SPRITE_H_

#include "GLHelper.h"

class Sprite{

  /// прямоугольник текстуры для отрисовки
  //Rect rect;
  Texture *texture_;
public:
  Sprite( Texture *tex ):texture_(tex){}
  int getWidth(){ return texture_->getWidth(); }
  int getHeight(){return texture_->getHeight();}
  void draw(int x, int y);
  void draw(Vector2<int>& pos);
  //void draw(int x, int y, int w, int h);
};

#endif

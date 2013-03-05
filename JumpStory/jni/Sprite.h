#ifndef SPRITE_H_
#define SPRITE_H_

#include "GLHelper.h"

class Sprite{
	mTexture *texture;
	/// прямоугольник текстуры для отрисовки
	Rect<uint> rect;
public:
	Sprite( mTexture *tex, int x, int y, int w, int h ) :
		rect( x, y, w, h ), texture( tex ) { }
	void draw(int x, int y);
	void draw(int x, int y, int w, int h);
};

#endif

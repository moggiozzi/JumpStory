#ifndef HELPER_H_
#define HELPER_H_

template <typename T>
struct Vector2{
	T x,y;
};

template <typename T>
struct Rect{
//	T x, y, w, h;
//	Rect ( T _x, T _y, T _w, T _h ) :
//		x(_x), y(_y), w(_w), h(_h) { }
  union {
	Vector2<T> pos;
	struct {
	  T x,y;
	};
  };
  union {
    Vector2<T> size;
	struct {
      T w, h;
    };
  };
  Rect<T>( T _x, T _y, T _w, T _h ) :
		x(_x), y(_y), w(_w), h(_h) { }
};

struct mTexture{
	uint width;
	uint height;
	uint format;
	/// флаг генерации GL текстуры
	bool isGenTexNameGl;
	/// "имя" текстуры GL
	uint texNameGl;
	char *pixels;
	mTexture(): isGenTexNameGl(false), pixels(0) {}

};

#endif

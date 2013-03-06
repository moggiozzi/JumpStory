#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Helper.h"
#include "Sprite.h"

class Character{
	Point pos;
	Sprite sprite;
public:
	void draw();

};

#endif // CHARACTER_H_
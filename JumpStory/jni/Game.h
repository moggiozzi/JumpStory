#ifndef GAME_H_
#define GMAE_H_

#include "Global.h"

class Game{
public:
	void init(android_app* app);
	void draw();
	void doStep(float dt);
};

#endif

#ifndef GAME_H_
#define GAME_H_

#include "Global.h"
#include "World.h"

class Game{
	World world;
public:
	void init(android_app* app);
	void draw();
	void doStep(float dt);
};

#endif // GAME_H_

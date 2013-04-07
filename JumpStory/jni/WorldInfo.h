#ifndef WORLD_INFO_H_
#define WORLD_INFO_H_

#ifndef PRIMITIVES_H_
#include "Primitives.h"
#endif

extern Vector2<float> maxJumpDist;
extern Vector2<float> worldPos;
extern float worldMaxY;
extern Vector2<float> worldSpeed;
extern float g;
int worldToDeviceX(float x);
int worldToDeviceY(float y);
Vector2<int> worldToDevice(Vector2<float> pos);
float deviceToWorldX(int x);
float deviceToWorldY(int y);
Vector2<float> deviceToWorld(Vector2<int> pos);

#endif
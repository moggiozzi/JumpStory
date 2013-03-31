#ifndef WORLD_INFO_H_
#define WORLD_INFO_H_

#include "Helper.h"

extern float maxJumpHeight;
extern Vector2<float> worldPos;
extern float worldMaxY;
int worldToDeviceX(float x);
int worldToDeviceY(float y);
Vector2<int> worldToDevice(Vector2<float> pos);
float deviceToWorldX(int x);
float deviceToWorldY(int y);
Vector2<float> deviceToWorld(Vector2<int> pos);

#endif
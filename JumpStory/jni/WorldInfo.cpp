#include "WorldInfo.h"
#include "GLHelper.h"

Vector2<float> worldPos;
Vector2<float> worldSpeed;
float worldMaxY;
float maxJumpHeight;
float g=400.0f;
int worldToDeviceX(float x){
  return (int)(x-worldPos.x());
}
int worldToDeviceY(float y){
  return (int)(GLHelper::getHeight()-(y-worldPos.y()));
}
Vector2<int> worldToDevice(Vector2<float> pos){
  Vector2<int> dpos(worldToDeviceX(pos.x()), worldToDeviceY(pos.y()));
  return dpos;
}
float deviceToWorldX(int x){
  return 0;
}
float deviceToWorldY(int y){
  return 0;
}
Vector2<float> deviceToWorld(Vector2<int> pos){
  return Vector2<float>();
}
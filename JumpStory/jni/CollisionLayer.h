#ifndef COLLISION_LAYER_H_
#define COLLISION_LAYER_H_

#include <vector>
#include "Helper.h"

class CollisionLayer{
  std::vector<Segment> segments;
  void generate();
public:
  CollisionLayer();
  bool isIntersect(float x1, float y1, float x2, float y2, float w=0);
  void init();
  void initLevel();
  void draw();
  void update();
};

#endif
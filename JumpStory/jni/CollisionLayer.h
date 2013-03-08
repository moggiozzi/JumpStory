#ifndef COLLISION_LAYER_H_
#define COLLISION_LAYER_H_

#include <vector>
#include "Helper.h"

class CollisionLayer{
  std::vector<Segment> segments;
public:
  CollisionLayer();
  bool isIntersect(const Point& p1, const Point& p2);
  void draw();
  void generate();
};

#endif
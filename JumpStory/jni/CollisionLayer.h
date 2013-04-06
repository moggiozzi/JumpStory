#ifndef COLLISION_LAYER_H_
#define COLLISION_LAYER_H_

#ifndef PRIMITIVES_H_
#include "Primitives.h"
#endif
#include <vector>

typedef std::vector< Segment<int> > Segments;
class CollisionLayer{
  Segments segments;
  void generate();
public:
  CollisionLayer();
  bool isIntersect(float x1, float y1, float x2, float y2, float w=0);
  void init();
  void initLevel();
  void draw();
  void update();
  const Segments getSegments(){ return segments; }
};

#endif
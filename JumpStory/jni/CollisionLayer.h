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
  void check(int curr, int prev);
public:
  CollisionLayer();
  bool isIntersect(float x1, float y1, float x2, float y2, float w=0);
  void init();
  void initLevel();
  void draw();
  void update();
  const Segments getSegments(){ return segments; }

  uint getSaveDataSize();
  void saveTo(char *data);
  void loadFrom(const char *data, const char * const dataEnd);
};

#endif
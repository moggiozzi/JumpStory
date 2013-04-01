#include "Tests.h"
#include "Primitives.h"

bool testGetDist(){
  Segment<int> s1(0,0,192,0);
  Segment<int> s2(96,5,288,5);
  float d1 = getDist(s1,s2);
  Segment<int> s3(43,1047,235,1047);
  Segment<int> s4(137,1088,201,1088);
  float d2 = getDist(s3,s4);
  return true;
}

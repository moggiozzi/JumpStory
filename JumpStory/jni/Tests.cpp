#include "Tests.h"
#include "Primitives.h"

bool testGetDist(){
  Segment<int> s1(0,0,192,0);
  Segment<int> s2(96,5,288,5);
  float d1 = getDist(s1,s2);
  Segment<int> s3(43,1047,235,1047);
  Segment<int> s4(137,1088,201,1088);
  float d2 = getDist(s3,s4);
  Segment<int> s5(251,401,315,401);
  Segment<int> s6(719,294,911,294);
  float d3 = getDist(s5,s6);
  Segment<int> s7(1010,2060,1074,2060);
  Segment<int> s8(575,427,639,427);
  float d4 = getDist(s7,s8);
  return true;
}

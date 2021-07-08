#include "AMvector.h"
#include "primitives.h"
#include "random.h"


// generates view vectors
class camera{
  vec sample(); // get a view vector

  // DoF params
  float focal_plane_distance;
  float position_jitter_amnt;
  // maybe some sort of autofocus? like some kind of idea
  // for setting DoF parameters via a scene depth check


  // lookat - create x+y offset vectors (basisx, basisy) +
  // the vector looking forwards (basisz)

  // position
  // direction

};


// holds scene geometry
class scene{

  // nearest intersection query

};

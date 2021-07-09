#include "AMvector.h"
#include "primitives.h"
#include "random.h"

#define MAX_BOUNCES 15

class camera{ // generates view vectors
public:
  camera() { }

  // get a view vector, generated from basis vectors
  vec3 sample(int x, int y) const; // x and y are pixel indices

  // lookat function sets basis vectors
  // position
  // direction - basis vectors

  // DoF autofocus? auto generate params from scene?
  base_type focal_plane_distance;
  base_type position_jitter_amnt;
  base_type FoV; // field of view
};


class scene{ // holds scene geometry
public:
  scene() { }

  // manipulation of the scene
  // nearest intersection query
};


class renderer{ // wrapper class, used in the render loop
public:
  renderer() { }

  camera c; // representing viewer
  scene s; // representing objects under view

  // get a colored sample from a set of pixel coords
  vec3 get_sample(int x, int y) const;
};

#include "AMvector.h"
#include "primitives.h"
#include "random.h"

#define MAX_BOUNCES 15

class camera{ // generates view vectors from a set of basis vectors
public:
  camera() { }

  void lookat(); // sets basis vectors
  vec3 sample(const int x, const int y) const; // x and y are pixel indices

  vec3 position; // location of viewer
  vec3 bx,by,bz; // basis vectors for camera calcs

  // DoF autofocus - autogen DoF params from scene? Maybe a project for later
  base_type focal_plane_distance;
  base_type position_jitter_amnt;
  base_type FoV; // field of view
};


class scene{ // holds scene geometry
public:
  scene() { }
  // random generation of scene geometry
  // manipulation of the scene geometry
  // nearest intersection query
};


class renderer{ // wrapper class, used in the render loop
public:
  renderer() { }

  camera c; // representing viewer
  scene s; // representing objects under view

  // get a pathtracing sample from a set of pixel coords
  vec3 get_color_sample(const int x, const int y) const;
};

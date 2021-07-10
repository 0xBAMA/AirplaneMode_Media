#include "AMvector.h"
#include "primitives.h"
#include "random.h"

#define MAX_BOUNCES 15

struct ray{
  vec3 origin;
  vec3 direction;
};

class camera{ // generates view vectors from a set of basis vectors
public:
  camera() { }

  // sets basis vectors for sample calcs
  void lookat(const vec3 from, const vec3 at, const vec3 up);

  // sets xdim and ydim
  void resolution(const int x, const int y) { xdim = x, ydim = y; }

  // x and y are pixel indices
  ray sample(const int x, const int y) const;

  vec3 position;  // location of viewer
  vec3 bx,by,bz;  // basis vectors for camera calcs
  int xdim, ydim; // overal dimensions of the screen

  // DoF autofocus - autogen DoF params from scene? Maybe a project for later
  base_type focal_plane_distance;
  base_type position_jitter_amnt;
  base_type FoV; // field of view
};


class scene{ // holds scene geometry
public:
  scene() { }

  // random generation of scene geometry
  void populate();

  // manipulation of the scene geometry
  void clear();

  // nearest intersection query
  bool intersection_query();

  // eventually bvh stuff
    // ...
};


class renderer{ // wrapper class, used in the render loop
public:
  renderer() { }
  camera c; // representing viewer
  scene s; // representing objects under view

  base_type gamma = 2.2; // gamma correction factor

  // get a pathtracing sample from a set of pixel coords
  vec3 get_color_sample(const int x, const int y) const;
};

vec3 tonemap(vec3 in); // applies tonemapping to a vec3 color

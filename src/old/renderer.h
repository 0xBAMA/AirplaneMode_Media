#include "AMvector.h"
#include "primitives.h"

#include <memory>

#define X_IMAGE_DIM 1920/4
#define Y_IMAGE_DIM 1080/4
#define MAX_BOUNCES 1
#define NUM_SAMPLES 1
#define NUM_THREADS 8

class camera{ // generates view vectors from a set of basis vectors
public:
  camera() { }

  void lookat(const vec3 from, const vec3 at, const vec3 up); // sets basis vectors for sample calcs
  void resolution(const int x, const int y) { xdim = x, ydim = y; } // sets xdim and ydim
  ray sample(const int x, const int y) const; // x and y are pixel indices

  vec3 position;  // location of viewer
  vec3 bx,by,bz;  // basis vectors for camera calcs
  int xdim, ydim; // overal dimensions of the screen

  // DoF autofocus - autogen DoF params from scene? Maybe a project for later
  base_type focal_plane_distance;
  base_type position_jitter_amnt;
  base_type FoV = 1.; // field of view
};


class scene{ // holds scene geometry
public:
  scene() { }

  hitrecord ray_query(ray r) const; // nearest intersection query

  void populate(); // random generation of scene geometry
  void clear(); // manipulation of the scene geometry

  std::vector<std::shared_ptr<primitive>> contents; // list of primitives making up the scene
  // std::vector<material> materials; // list of materials present in the scene

  // eventually bvh stuff
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

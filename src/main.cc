#include <chrono> // timing utilities
#include <iostream>
using std::cerr, std::cin, std::cout, std::endl, std::flush;
#include <stdio.h> // printf if needed
#include <vector> // std::vector
#include <string> // std::string
#include <thread> // threads
#include <memory> // shared_ptr

// my vector library
#include "AMvector.h"

// image input
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// image output
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// render parameters
#define X_IMAGE_DIM 1920/4
#define Y_IMAGE_DIM 1080/4
#define MAX_BOUNCES 1
#define NUM_SAMPLES 4
#define NUM_THREADS 8
#define IMAGE_GAMMA 2.2
#define FIELD_OF_VU 1.0 
#define HIT_EPSILON base_type(std::numeric_limits<base_type>::epsilon())
#define DMAX_TRAVEL base_type(std::numeric_limits<base_type>::max())


// todo : prng utilities


// base class for primitives
class primitive {
public:
  virtual hitrecord intersect(ray r) const = 0; // pure virtual, base definition dne
  int material_index; // indexes into scene material list
};

// sphere
class sphere : public primitive {
public:
  sphere(vec3 c, base_type r, int m) : center(c), radius(r) {material_index = m;}
  hitrecord intersect(ray r) const override {
    hitrecord h;   h.material_index = material_index;   h.dtransit = DMAX;
    vec3 disp = r.origin - center;
    base_type b = dot(r.direction, disp);
    base_type c = dot(disp, disp) - radius*radius;
    base_type des = b * b - c; // b squared minus c - discriminant of the quadratic
    if(des >= 0){ // hit at either one or two poitns
      h.dtransit = std::min( -b + sqrt(des), -b - sqrt(des) );
      h.position = r.origin + h.dtransit * r.direction;
      h.normal = normalize(h.position - center);
      h.front = true;
    }
    return h;
  }
private:  // geometry parameters
  vec3 center;
  base_type radius;
};

// triangle
class triangle : public primitive {
public:
  triangle(vec3 p0, vec3 p1, vec3 p2, int m) : points{p0, p1, p2} {material_index = m;}
  hitrecord intersect(ray r) const override { // Möller–Trumbore intersection algorithm
    hitrecord hit;  hit.material_index = material_index;  hit.dtransit = DMAX;
    const vec3 edge1 = points[1] - points[0];
    const vec3 edge2 = points[2] - points[0];
    const vec3 pvec = cross(r.direction, edge2);
    const base_type det = dot(edge1, pvec);
    static const base_type eps = std::numeric_limits<base_type>::epsilon();
    if (det > -eps && det < eps)
      return hit; // no hit, return

    const base_type invDet = 1.0f / det;
    const vec3 tvec = r.origin - points[0];
    hit.uv.values[0] = dot(tvec, pvec) * invDet; // u value
    if (hit.uv.values[0] < 0.0f || hit.uv.values[0] > 1.0f)
      return hit; // no hit, return

    const vec3 qvec = cross(tvec, edge1);
    hit.uv.values[1] = dot(r.direction, qvec) * invDet; // v value
    if (hit.uv.values[1] < 0.0f || hit.uv.values[0] + hit.uv.values[1] > 1.0f)
      return hit; // no hit, return

    hit.dtransit = dot(edge2, qvec) * invDet; // distance term to hit
    hit.position = points[0] + hit.uv.values[0] * edge2 + hit.uv.values[1] * edge1;
    hit.normal = cross(edge1, edge2);
    hit.front = dot(hit.normal, r.direction) > 0 ? true : false; // determine front or back

    return hit; // return true result with all relevant info
  }
private:  // geometry parameters
  vec3 points[3];
};


//   todo : material handling


// camera
class camera{ // generates view vectors from a set of basis vectors
public:
  camera(){}
  void lookat(const vec3 from, const vec3 at, const vec3 up){position = from; bz = normalize(at-from); bx = normalize(cross(up, bz)); by = normalize(cross(bx, bz));}
  ray sample(const vec2 p) const { // argument is pixel location
    ray r;
    r.origin = position;
    // remap [0, dimension] indexing to [-dimension/2., dimension/2.]
    base_type lx = p.values[0] - base_type(x/2.) / base_type(x/2.);
    base_type ly = p.values[1] - base_type(y/2.) / base_type(y/2.);
    base_type aspect_ratio = base_type(x) / base_type(y); // calculate pixel offset
    r.direction = normalize(aspect_ratio*lx*bx + ly*by + (1./FoV)*bz); // construct from basis
    return r;
  }
private:
  vec3 position;  // location of viewer
  vec3 bx,by,bz;  // basis vectors for sample calcs
  int x = X_IMAGE_DIM, y = Y_IMAGE_DIM; // overal dimensions of the screen
  base_type FoV = 1.; // field of view
};


//   scene as primitive list + material list + camera container


//   renderer class
//     note: with camera::sample, jitter p at calling location


int main(int argc, char const *argv[]){
  std::string filename = std::string(argv[1]); // first command line argument is filename
  auto tstart = std::chrono::high_resolution_clock::now();

  // declare renderer object
  // render and save image to 'filename'

  cout << "Total Render Time: " <<
    std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now()-tstart).count()/1000.
        << " seconds" << endl;

  return 0;
}

#include <chrono>          // timing utilities
#include <iostream>       // text i/o
using std::cerr, std::cin, std::cout, std::endl, std::flush;
#include <stdio.h>      // printf if needed
#include <vector>      // std::vector
#include <random>     // prng
#include <string>    // std::string
#include <algorithm>// clamp
#include <thread>  // threads
#include <memory> // shared_ptr

// my vector library
#include "AMvector.h"

// image input
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// image output
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// default types
#define base_type double
using vec2 = vector2<base_type>;
using vec3 = vector3<base_type>;

// render parameters
constexpr int       X_IMAGE_DIM = 1920/4;
constexpr int       Y_IMAGE_DIM = 1080/4;
constexpr int       MAX_BOUNCES = 6;
constexpr int       NUM_SAMPLES = 16;
constexpr int       NUM_THREADS = 8;
constexpr base_type IMAGE_GAMMA = 2.2;
constexpr base_type FIELD_OF_VIEW = 1.0;
constexpr base_type HIT_EPSILON = base_type(std::numeric_limits<base_type>::epsilon());
constexpr base_type DMAX_TRAVEL = base_type(std::numeric_limits<base_type>::max())/10.;

// ray representation (origin+direction)
struct ray{
  vec3 origin;
  vec3 direction;
};

// represents a ray hit and the associated information
struct hitrecord {                // hit record
    vec3 position;               // position
    vec3 normal;                // normal
    base_type dtransit = DMAX_TRAVEL; // how far the ray traveled, initially very large
    int material_index = 0;          // material (indexed into scene list)
    vec2 uv;                        // used for triangles, barycentric coords
    bool front;                    // hit on frontfacing side
};

inline uint32_t wang_hash(uint32_t x){
    x = (x ^ 12345391) * 2654435769;
    x ^= (x << 6) ^ (x >> 26); x *= 2654435769;
    x += (x << 5) ^ (x >> 12);
    return x;
}

// Random Utilities
base_type rng(std::shared_ptr<std::mt19937_64> gen){ // gives a value in the range 0.-1.
  std::uniform_real_distribution<base_type> distribution(0., 1.);
  return distribution(*gen);
}
vec3 random_unit_vector(std::shared_ptr<std::mt19937_64> gen){ // random direction vector (unit length)
  base_type z = rng(gen) * 2.0f - 1.0f;
  base_type a = rng(gen) * 2. * pi;
  base_type r = sqrt(1.0f - z * z);
  base_type x = r * cos(a);
  base_type y = r * sin(a);
  return vec3(x, y, z);
}
vec3 random_in_unit_disk(std::shared_ptr<std::mt19937_64> gen){ // random in unit disk (xy plane)
  vec3 val = random_unit_vector(gen);
  return vec3(val.values[0], val.values[1], 0.);
}

class primitive { // base class for primitives
public:
  virtual hitrecord intersect(ray r) const = 0; // pure virtual, base definition dne
  int material_index; // indexes into scene material list
};

// sphere
class sphere : public primitive {
public:
  sphere(vec3 c, base_type r, int m) : center(c), radius(r) {material_index = m;}
  hitrecord intersect(ray r) const override {
    hitrecord h; h.dtransit = DMAX_TRAVEL;
    vec3 disp = r.origin - center;
    base_type b = dot(r.direction, disp);
    base_type c = dot(disp, disp) - radius*radius;
    base_type des = b * b - c; // b squared minus c - discriminant of the quadratic
    if(des >= 0){ // hit at either one or two points
      h.dtransit = std::min( -b + std::sqrt(des), -b - std::sqrt(des) );
      h.material_index = material_index;
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
    hitrecord hit;  hit.dtransit = DMAX_TRAVEL;
    const vec3 edge1 = points[1] - points[0];
    const vec3 edge2 = points[2] - points[0];
    const vec3 pvec = cross(r.direction, edge2);
    const base_type det = dot(edge1, pvec);
    if (det > -HIT_EPSILON && det < HIT_EPSILON)
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
    hit.material_index = material_index;
    hit.front = dot(hit.normal, r.direction) > 0 ? true : false; // determine front or back

    return hit; // return true result with all relevant info
  }
private:  // geometry parameters
  vec3 points[3];
};

//   todo : material handling

class camera{ // camera class generates view vectors from a set of basis vectors
public:
  camera(){}
  void lookat(const vec3 from, const vec3 at, const vec3 up){
    position = from;
    bz = normalize(at-from);
    bx = normalize(cross(up, bz));
    by = normalize(cross(bx, bz));
  }
  ray sample(const vec2 p) const { // argument is pixel location - assumes any desired jitter is applied at call site
    ray r;
    r.origin = position;
    // remap [0, dimension] indexing to [-dimension/2., dimension/2.]
    base_type lx = (p.values[0] - base_type(x/2.)) / base_type(x/2.);
    base_type ly = (p.values[1] - base_type(y/2.)) / base_type(y/2.);
    base_type aspect_ratio = base_type(x) / base_type(y);            // calculate pixel offset
    r.direction = normalize(aspect_ratio*lx*bx + ly*by + (1./FoV)*bz); // construct from basis
    return r;
  }
private:
  vec3 position;  // location of viewer
  vec3 bx,by,bz;  // basis vectors for sample calcs
  int x = X_IMAGE_DIM, y = Y_IMAGE_DIM; // overal dimensions of the screen
  base_type FoV = FIELD_OF_VIEW; // field of view
};

class scene{ // scene as primitive list + material list container
public:
  scene() { }
  void clear() { contents.clear(); }
  void populate(){
    std::random_device r;
    std::seed_seq s{r(), r(), r(), r(), r(), r(), r(), r(), r()};
    auto gen = std::make_shared<std::mt19937_64>(s);
    for (int i = 0; i < 60; i++){
      contents.push_back(std::make_shared<sphere>(2.*vec3(rng(gen)-0.5, rng(gen)-0.5, rng(gen)-0.5), 0.1*rng(gen), 0));
      contents.push_back(std::make_shared<triangle>(2.*vec3(rng(gen)-0.5,rng(gen)-0.5,rng(gen)-0.5), 2.*vec3(rng(gen)-0.5,rng(gen)-0.5,rng(gen)-0.5), 2.*vec3(rng(gen)-0.5,rng(gen)-0.5,rng(gen)-0.5), 1));
    }
  }
  hitrecord ray_query(ray r) const {
    hitrecord h; // iterate through primitives and check for nearest intersection
    base_type current_min = DMAX_TRAVEL; // initially 'a big number'
    for(int i = 0; i < contents.size(); i++) {
      hitrecord temp = contents[i]->intersect(r);
      if(temp.dtransit < DMAX_TRAVEL && temp.dtransit > 0. && temp.dtransit < current_min) {
        current_min = temp.dtransit;
        h = temp;
      }
    }
    return h;
  }
  std::vector<std::shared_ptr<primitive>> contents; // list of primitives making up the scene
  // std::vector<std::shared_ptr<material>> materials; // list of materials present in the scene
};

class renderer{
public:
  renderer() { bytes.resize(xdim*ydim*4, 0); s.populate(); rng_seed();}
  void render_and_save_to(std::string filename){
    c.lookat(vec3(0., 0., 2.), vec3(0.), vec3(0.,1.,0.));
    std::thread threads[NUM_THREADS];                 // create thread pool
    for (int id = 0; id < NUM_THREADS; id++){        // do work
      threads[id] = std::thread(
        [this, id]() {
          for (int y = id; y < this->ydim; y+=NUM_THREADS)
          for (int x =  0; x < this->xdim; x++) {
            vec3 running_color = vec3(0.);      // initially zero, averages sample data
            for (int s = 0; s < nsamples; s++) // get sample data (n samples)
              running_color += get_pathtrace_color_sample(x,y,id);
            running_color /= base_type(nsamples);  // sample averaging
            tonemap_and_gamma(running_color);     // tonemapping + gamma
            write(running_color, vec2(x,y));     // write final output values
          }
        }
      );
    }
    for (int id = 0; id < NUM_THREADS; id++)
      threads[id].join();
    cout << "Writing with filename " << filename << endl;
    stbi_write_png(filename.c_str(), xdim, ydim, 4, &bytes[0], xdim * 4);
  }
private:
  camera c; // generates view rays
  scene s; // holds all scene geometry + their associated materials
  int xdim=X_IMAGE_DIM, ydim=Y_IMAGE_DIM, nsamples=NUM_SAMPLES, bmax=MAX_BOUNCES;
  std::vector<unsigned char> bytes;        // image buffer for stb_image_write
  std::vector<std::shared_ptr<std::mt19937_64>> gen; // PRNG states per thread
  void rng_seed(){
    std::random_device r;
    for(int i = 0; i < NUM_THREADS; i++){
      std::seed_seq s{r(), r(), r(), r(), r(), r(), r(), r(), r()};
      gen.push_back(std::make_shared<std::mt19937_64>(s));
    }
  }
  void tonemap_and_gamma(vec3& in){
    in *= 0.6f; // function to tonemap color value in place
    base_type a = 2.51f;
    base_type b = 0.03f;
    base_type c = 2.43f;
    base_type d = 0.59f;
    base_type e = 0.14f;
    in = (in*(a*in+vec3(b)))/(in*(c*in+vec3(d))+e);
    in.values[0] = std::pow(std::clamp(in.values[0], 0., 1.), 1./IMAGE_GAMMA);
    in.values[1] = std::pow(std::clamp(in.values[1], 0., 1.), 1./IMAGE_GAMMA);
    in.values[2] = std::pow(std::clamp(in.values[2], 0., 1.), 1./IMAGE_GAMMA);
  }
  vec3 get_pathtrace_color_sample(const int x, const int y, const int id){
    // throughput's initial value of 1. in each channel indicates that it is initially
    // capable of carrying all of the light intensity possible (100%), and it is reduced
    vec3 throughput = vec3(1.); // by the albedo of the material on each bounce
    vec3 current    = vec3(0.); // init to zero - initially no light present
    vec3 old_ro, ro, rd; // old_ro holds previous hit location, unitialized

    // get initial ray origin + ray direction from camera
    ray r = c.sample(vec2(x+rng(gen[id]),y+rng(gen[id])));  ro = r.origin;  rd = r.direction;

    for (int bounce = 0; bounce < MAX_BOUNCES; bounce++){
      old_ro = ro; // cache old hit locaDMAXtion
      hitrecord h = s.ray_query(ray{ro, rd}); // get a new hit location (scene query)
      // 0 material is emissive
      // 1 material is diffuse
      if(h.dtransit < DMAX_TRAVEL && h.material_index == 0)
        current = vec3(h.normal*0.5 + vec3(0.5)) * (2./h.dtransit);
      if(h.dtransit < DMAX_TRAVEL && h.material_index == 1)
        current = (h.front ? vec3(0.618) : vec3(0.1618))*(2./h.dtransit);

    }
    return current;
    // return vec3(x/base_type(X_IMAGE_DIM), y/base_type(Y_IMAGE_DIM), rng(gen[id]));
    // return vec3(rng(gen[id]));
  }
  void write(vec3 col, vec2 loc){ // writes to image buffer
    const int index = 4.*(loc.values[1]*xdim+loc.values[0]);
    for(int c = 0; c < 4; c++)
      bytes[index+c] = (c == 3) ? 255 : col.values[c] * 255.;
  }
};

int main(int argc, char const *argv[]){
  std::string filename = std::string(argv[1]); // from CLI
  auto tstart = std::chrono::high_resolution_clock::now();

  renderer r; r.render_and_save_to(filename);

  cout << "Total Render Time: " <<
    std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now()-tstart).count()/1000.
        << " seconds" << endl; return 0;
}

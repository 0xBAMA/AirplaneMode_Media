#include "renderer.h"
#include <algorithm>
#include <cmath>

void camera::lookat( const vec3 from, const vec3 at, const vec3 up ){
  // camera is located at 'from'
  position = from;

  // camera's forward vector (basis z) is simply at minus from
  bz = normalize(from-at);

  // now the other basis vectors (x and y) created with cross products - order matters
  bx = cross(up, bz); // 'right' perpendicular to both 'up' and 'forward'
  by = cross(bz, bx); // stored 'up' vector is perpendicular to 'forward' and 'right'
}

ray camera::sample( const int x, const int y ) const{
  ray r; // result from the camera

  // need to calculate pixel offset
  r.origin = vec3(0.);
  r.direction = vec3(0.);

  return r;
}


void scene::populate(){
  // randomly generate some primitives to test against
}

bool scene::intersection_query(){
  // check for nearest intersection
  return false;
}


vec3 renderer::get_color_sample( const int x, const int y ) const{
    vec3 sample_value = vec3(0.);

    // throughput's initial value of 1. in each channel indicates that it is initially
    // capable of carrying all of the light intensity possible (100%), and it is reduced
    vec3 throughput = vec3(1.); // by the albedo of the material on each bounce

    vec3 old_ro, ro, rd; // old_ro holds previous hit location, unitialized

    // get initial ray origin + ray direction from camera
    ray r = c.sample(x,y);  ro = r.origin;  rd = r.direction;

    for (int bounce = 0; bounce < MAX_BOUNCES; bounce++){
        old_ro = ro; // cache old hit location

        // get a new hit location (scene query)

        // ray origin becomes new hit location

        // consider the new hit normal and r_in

              // new ray direction decided for next loop iteration

        // sample color += throughput * current_emission (light emission)

        // throughput *= albedo (representing signal attenuation)

        // russian roulette termination was here in my old implementation

    } // end loop over bounces


    // return sample_value;
    return vec3(sin(base_type(0.01*x*y))); // something to give some output
  }


vec3 tonemap(vec3 v){
  v *= 0.6f;
  base_type a = 2.51f;
  base_type b = 0.03f;
  base_type c = 2.43f;
  base_type d = 0.59f;
  base_type e = 0.14f;

  vec3 result = (v*(a*v+vec3(b)))/(v*(c*v+vec3(d))+e);
  result.values[0] = std::clamp(result.values[0], 0., 1.);
  result.values[1] = std::clamp(result.values[1], 0., 1.);
  result.values[2] = std::clamp(result.values[2], 0., 1.);
  return result;
}

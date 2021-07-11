#include "renderer.h"
#include "primitives.h"

#include <iostream>
#include <algorithm>
#include <cmath>

void camera::lookat( const vec3 from, const vec3 at, const vec3 up ){
  // camera is located at 'from'
  position = from;

  // camera's forward vector (basis z) is simply at minus from
  bz = normalize(at-from);

  // now the other basis vectors (x and y) created with cross products - order matters
  bx = normalize(cross(up, bz)); // 'right' perpendicular to both 'up' and 'forward'
  by = normalize(cross(bx, bz)); // stored 'up' vector is perpendicular to 'right' and 'forward'
}

ray camera::sample( const int x, const int y ) const{
  ray r; // result from the camera
  r.origin = position;

  // remap [0, dimension] indexing to [-dimension/2., dimension/2.]
  base_type lx = (base_type(x + rbt()) - base_type(xdim/2.)) / base_type(xdim/2.);
  base_type ly = (base_type(y + rbt()) - base_type(ydim/2.)) / base_type(ydim/2.);

  base_type aspect_ratio = float(xdim) / float(ydim); // need to calculate pixel offset
  r.direction = normalize(aspect_ratio*lx*bx + ly*by + (1./FoV)*bz); // construct from basis

  return r;
}


void scene::populate(){
  // randomly generate some primitives to test against
  for (int i = 0; i < 1500; i++){
    contents.push_back(std::make_shared<sphere>(2.*vec3(rbt()-0.5, rbt()-0.5, rbt()-0.5), 0.2*rbt(), 0));
    contents.push_back(std::make_shared<triangle>(2.*vec3(rbt()-0.5,rbt()-0.5,rbt()-0.5), 2.*vec3(rbt()-0.5,rbt()-0.5,rbt()-0.5), 2.*vec3(rbt()-0.5,rbt()-0.5,rbt()-0.5), 1));
  }
}

hitrecord scene::ray_query(ray r) const{
  hitrecord h; // iterate through primitives and check for nearest intersection
  base_type current_min = DMAX; // initially 'a big number'

  for(int i = 0; i < contents.size(); i++) {
    hitrecord temp = contents[i]->intersect(r);
    if(temp.dtransit < DMAX && temp.dtransit > 0. && temp.dtransit < current_min) {
      current_min = temp.dtransit;
      h = temp;
    }
  }

  return h;
}

vec3 renderer::get_color_sample( const int x, const int y ) const{
  // throughput's initial value of 1. in each channel indicates that it is initially
  // capable of carrying all of the light intensity possible (100%), and it is reduced
  vec3 throughput   = vec3(1.); // by the albedo of the material on each bounce
  vec3 sample_value = vec3(0.); // init to zero - initially no light present

  vec3 old_ro, ro, rd; // old_ro holds previous hit location, unitialized

  // get initial ray origin + ray direction from camera
  ray r = c.sample(x,y);  ro = r.origin;  rd = r.direction;

  for (int bounce = 0; bounce < MAX_BOUNCES; bounce++){
    old_ro = ro; // cache old hit location

    // get a new hit location (scene query)
    hitrecord h = s.ray_query(ray{ro, rd});

    if(h.dtransit < DMAX)
      sample_value = vec3(h.normal*0.5 + vec3(0.5)) * (2./h.dtransit);

    // if(h.dtransit < DMAX && h.material == 1)
      // sample_value = vec3(h.uv.values[0],h.uv.values[1],1-(h.uv.values[0]+h.uv.values[1]));

    // ray origin becomes new hit location

    // consider the new hit normal and r_in

        // new ray direction decided for next loop iteration

    // sample color += throughput * current_emission (light emission)

    // throughput *= albedo (representing signal attenuation)

    // russian roulette termination was here in my old implementation

  } // end loop over bounces
  return sample_value; // return placeholder
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

#include "renderer.h"

void camera::lookat(){

}

vec3 camera::sample(const int x, const int y) const{
  // currently placeholder
  // this will probably look a lot like the camera code in SDF_Path
  return vec3(0.,0.,0.);
}

vec3 renderer::get_color_sample(const int x, const int y) const{
    vec3 sample_value = vec3(0.,0.,0.);

    // throughput's initial value of 1. in each channel indicates that it is initially
    // capable of carrying all of the light intensity possible (100%), and it is reduced
    vec3 throughput = vec3(1.,1.,1.); // by the albedo of the materials on bounce

    // get initial ray origin + direction from camera
    // for bounce < max_bounces
        // cache old hit location
        // get a new hit location
        // ray origin becomes new hit location
        // consider the new hit normal and r_in
            // new ray direction decided for next loop iteration
        // sample color += throughput * current_emission (light emission)
        // throughput *= albedo (representing signal attenuation)
        // russian roulette termination was here in my old implementation
    // end loop over bounces

    return sample_value;
}

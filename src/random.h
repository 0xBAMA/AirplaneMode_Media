#ifndef IO_H
#define IO_H

#include <random>
#include "AMvector.h"

#define RAND_METHOD 0 // std::random or wang hash here?
#if RAND_METHOD == 0

  // from demofox
  // https://blog.demofox.org/2020/05/25/casual-shadertoy-path-tracing-1-basic-camera-diffuse-emissive/
  uint wang_hash(){
    static uint seed = 0;
    seed = uint(seed ^ uint(61)) ^ uint(seed >> uint(16));
    seed *= uint(9);
    seed = seed ^ (seed >> 4);
    seed *= uint(0x27d4eb2d);
    seed = seed ^ (seed >> 15);
    return seed;
  }
  base_type random_float01(){ // random value 0-1
    return float(wang_hash()) / 4294967296.0;
  }

#elif RAND_METHOD == 1

  base_type random_float01(){ // random value 0-1
    std::default_random_engine generator; // another generation method
    std::uniform_real_distribution<base_type> distribution(0., 1.);
    return distribution(generator);
  }

#endif

vec3 random_unit_vector(){ // random unit vector (unit length)
  base_type z = random_float01() * 2.0f - 1.0f;
  base_type a = random_float01() * 2. * PI;
  base_type r = sqrt(1.0f - z * z);
  base_type x = r * cos(a);
  base_type y = r * sin(a);
  return vec3(x, y, z);
}

vec3 random_in_unit_disk(){ // random in unit disk (xy plane)
  vec3 val = random_unit_vector();
  return vec3(val.values[0], val.values[1], 0.);
}

#endif

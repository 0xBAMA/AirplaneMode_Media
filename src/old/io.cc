#include "io.h"
#include "renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// stb_image - https://github.com/nothings/stb/blob/master/stb_image.h
#include "stb_image.h"
#include "stb_image_write.h"

vec3 gamma(vec3 color, base_type gamma){
  for (int channel = 0; channel < 3; channel++) // gamma correction comes last
    color.values[channel] = pow(color.values[channel], 1./gamma);

  return color;
}

void image::write(const vec3 v, const int x, const int y){
  for (int channel = 0; channel < 4; channel++){ // quantize 8 bit values and write
    this->bytes[4*(y*this->xdim+x)+channel] = static_cast<unsigned char>((channel < 3) ? (255.*v.values[channel]) : 255);
  }
}

void image::output_image(const std::string filename) const{
  cout << "Writing with filename " << filename << endl;
  stbi_write_png(filename.c_str(), xdim, ydim, 4, &bytes[0], xdim * 4);
}

void image::render_scene(int samplecount){
  renderer r;  // configure render params (DoF, view)

  r.c.lookat(/*from*/ vec3(0., 0., 2.), /*at*/ vec3(0.), /*up*/ vec3(0.,1.,0.));
  r.c.resolution(xdim, ydim);

  r.s.populate(); // populate scene geometry

  bytes.clear(); bytes.resize(xdim*ydim*4);  // clear image
  std::thread threads[NUM_THREADS];  // create thread pool
  for (int id = 0; id < NUM_THREADS; id++){ // do work
    threads[id] = std::thread(
      [this, id, r, samplecount]() { // lambda for one thread's work
        for (int y = id; y < this->ydim; y+=NUM_THREADS)
        for (int x =  0; x < this->xdim; x++) {
          vec3 running_color = vec3(0.);  // initially zero, averages sample data

          for (int s = 0; s < samplecount; s++)         // get sample data
            running_color += r.get_color_sample(x,y);

          running_color /= base_type(samplecount);         // sample averaging
          running_color = tonemap(running_color);         // tonemapping
          running_color = gamma(running_color, r.gamma); // gamma correction comes last

          write(running_color, x, y); // write final output values
        }
      }
    );
  }
  for (int id = 0; id < NUM_THREADS; id++)
    threads[id].join();  // destroy threads and return
}

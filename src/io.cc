#include "io.h"
#include "renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// stb_image - https://github.com/nothings/stb/blob/master/stb_image.h
#include "stb_image.h"
#include "stb_image_write.h"

void image::output_image(const std::string filename) const{
  cout << "writing with filename " << filename << endl;
  stbi_write_png(filename.c_str(), xdim, ydim, 4, &bytes[0], xdim * 4);
}

void image::black_image() {
  bytes.clear(); bytes.resize(xdim*ydim*4);
  for(int y = 0; y < ydim; y++)
  for(int x = 0; x < xdim; x++)
  for(int n = 0; n < 4; n++)
    bytes[4*(y*xdim+x)+n] = (n == 3) ? 255 : 0;
}

void image::xor_pattern() {
  bytes.clear(); bytes.resize(xdim*ydim*4);
  for(int y = 0; y < ydim; y++)
  for(int x = 0; x < xdim; x++)
  for(int n = 0; n < 4; n++)
    bytes[4*(y*xdim+x)+n] = x^y;
}

void image::xor_pattern_threaded() {
  bytes.clear(); bytes.resize(xdim*ydim*4);
  std::thread threads[NUM_THREADS];  // create threads
  for (int id = 0; id < NUM_THREADS; id++){ // do work
    threads[id] = std::thread(
      [this, id]() {
        for (int y = id; y < this->ydim; y+=NUM_THREADS)
        for (int x =  0; x < this->xdim; x++)
        for (int channel = 0; channel < 4; channel++)
          this->bytes[4*(y*this->xdim+x)+channel] = x^y;
      }
    );
  }
  for (int id = 0; id < NUM_THREADS; id++)
    threads[id].join();  // destroy threads and return
}

void image::render_scene(int samplecount){
  renderer r;  // configure render params (DoF, view)

  bytes.clear(); bytes.resize(xdim*ydim*4);  // clear image
  std::thread threads[NUM_THREADS];  // create thread pool
  for (int id = 0; id < NUM_THREADS; id++){ // do work
    threads[id] = std::thread(
      [this, id, r, samplecount]() { // lambda for one thread's work
        for (int y = id; y < this->ydim; y+=NUM_THREADS)
        for (int x =  0; x < this->xdim; x++) {
          vec3 running_color; // initially zero, averages sample data

          // accumulate sample results
          for (int s = 0; s < samplecount; s++)
            running_color += r.get_color_sample(x,y);

          // compute the average
          running_color /= base_type(samplecount);

          running_color.values[0] = sin(0.2*float(x));
          running_color.values[1] = sin(0.1*float(y));
          running_color.values[2] = sin(0.5*float(x*y));

          // sRGB (gamma)
          for (int channel; channel < 3; channel++)
            running_color.values[channel] = pow(running_color.values[channel], 1./r.gamma);

          // tonemapping
          running_color = tonemap(running_color);

          // map to the desired range (0-255)
          running_color *= 255.; // 0-1 mapped to 0-255

          // store quantized 8 bit values
          for (int channel = 0; channel < 4; channel++)
             this->bytes[4*(y*this->xdim+x)+channel] = static_cast<unsigned char>((channel < 3) ? running_color.values[channel] : 255);
        }
      }
    );
  }
  for (int id = 0; id < NUM_THREADS; id++)
    threads[id].join();  // destroy threads and return
}

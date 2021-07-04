#ifndef IO_H
#define IO_H

// STL includes
#include <iostream>
#include <stdio.h>
// iostream aliases
using std::cerr, std::cin, std::cout, std::endl, std::flush;

// stb_image - https://github.com/nothings/stb/blob/master/stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#include <vector>
#include <string>
#include <thread>

#define NUM_THREADS 4

class image{
public:
  int xdim = 0; int ydim = 0;
  std::vector<unsigned char> bytes;
};

void output_image(std::string filename, image in){
  cout << "writing with filename " << filename << endl;
  stbi_write_png(filename.c_str(), in.xdim, in.ydim, 4, &in.bytes[0], in.xdim * 4);
}

void black_image(int xin, int yin, image in) {
  in.bytes.clear(); in.bytes.resize(xin*yin*4);
  in.xdim = xin; in.ydim = yin;
  for(int y = 0; y < yin; y++)
  for(int x = 0; x < xin; x++)
  for(int n = 0; n < 4; n++)
    in.bytes[4*(y*xin+x)+n] = (n == 3) ? 255 : 0;
}

void xor_pattern(int xin, int yin, image in) {
  in.bytes.clear(); in.bytes.resize(xin*yin*4);
  in.xdim = xin; in.ydim = yin;
  for(int y = 0; y < yin; y++)
  for(int x = 0; x < xin; x++)
  for(int n = 0; n < 4; n++)
    in.bytes[4*(y*xin+x)+n] = x^y;
}

void xor_pattern_threaded(int xin, int yin, image in) {
  in.bytes.clear(); in.bytes.resize(xin*yin*4);
  in.xdim = xin; in.ydim = yin;
  std::thread threads[NUM_THREADS];  // create threads
  for (int id = 0; id < NUM_THREADS; id++){ // do work
    threads[id] = std::thread(
      [&in, xin, yin, id]() {
        for (int y = id; y < yin; y+=NUM_THREADS)
        for (int x = 0; x < xin; x++)
        for (int channel = 0; channel < 4; channel++)
          in.bytes[4*(y*xin+x)+channel] = x^y;
      }
    );
  }
  for (int id = 0; id < NUM_THREADS; id++)
    threads[id].join();  // destroy threads and return
}
#endif

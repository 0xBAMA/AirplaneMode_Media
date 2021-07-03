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

class image{
public:
  int xdim, ydim;
  std::vector<unsigned char> bytes;

  image(int xdim_in, int ydim_in) : xdim(xdim_in), ydim(ydim_in) { bytes.resize(xdim*ydim*4); }
  void output(std::string filename) { stbi_write_png(filename.c_str(), xdim, ydim, 4, &bytes[0], xdim * 4); }

  void xor_pattern() {
    for(int y = 0; y < ydim; y++)
    for(int x = 0; x < xdim; x++)
    for(int n = 0; n < 4; n++)
      bytes[4*(y*xdim+x)+n] = x ^ y;
  }

  void xor_threaded() {

    // create threads

    // do work

    // destroy threads and return 

  }
};
#endif

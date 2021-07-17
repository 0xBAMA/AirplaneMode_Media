#ifndef IO_H
#define IO_H

#include <iostream>
using std::cerr, std::cin, std::cout, std::endl, std::flush;
#include <stdio.h>
#include <vector>
#include <string>
#include <thread>
#include "AMvector.h"


class image{
public:
  image(int x, int y) : xdim(x), ydim(y) { }

  void render_scene(int nsamples);

  void write(const vec3 v, const int x, const int y);
  void output_image(const std::string filename) const;

  const int xdim, ydim;
  std::vector<unsigned char> bytes;
};

#endif

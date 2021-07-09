#ifndef IO_H
#define IO_H

#include <iostream>
// iostream aliases
using std::cerr, std::cin, std::cout, std::endl, std::flush;
#include <stdio.h>
#include <vector>
#include <string>
#include <thread>

#define NUM_THREADS 8

class image{
public:
  image(int x, int y) : xdim(x), ydim(y) { }
  void output_image(const std::string filename) const;

  const int xdim, ydim;
  std::vector<unsigned char> bytes;

  void black_image();
  void xor_pattern();
  void xor_pattern_threaded();
  void render_scene(int nsamples);
};

#endif

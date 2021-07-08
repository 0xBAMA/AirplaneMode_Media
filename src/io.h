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
#define NUM_SAMPLES 100

class image{
public:
  image(int x, int y, int s=NUM_THREADS) : xdim(x), ydim(y), samplecount(s) { }

  const int xdim, ydim;
  int samplecount;
  std::vector<unsigned char> bytes;

  void black_image();
  void xor_pattern();
  void xor_pattern_threaded();

  void render_scene();

  void output_image(const std::string filename) const;
};

#endif

#ifndef IO_H
#define IO_H

#include <iostream>
// iostream aliases
using std::cerr, std::cin, std::cout, std::endl, std::flush;
#include <stdio.h>
#include <vector>
#include <string>
#include <thread>

#define NUM_THREADS 4

class image{
public:
  const int xdim, ydim;
  std::vector<unsigned char> bytes;

  image(int x, int y) : xdim(x), ydim(y) { }

  void black_image();
  void xor_pattern();
  void xor_pattern_threaded();

  void output_image(const std::string filename) const;
};



#endif

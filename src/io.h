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
  int xdim = 0; int ydim = 0;
  std::vector<unsigned char> bytes;

  void black_image(int xin, int yin);
  void xor_pattern(int xin, int yin);
  void xor_pattern_threaded(int xin, int yin);

  void output_image(std::string filename);
};



#endif

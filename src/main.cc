// AirplaneMode - a minimal dependency pathtracer

#include "io.h"
#include "AMvector.h"

// Renderer settings
const int xdim = 1920;
const int ydim = 1080;

int main(int argc, char const *argv[])
{
  cout << endl;
  cout << " ╦ ╦┌─┐┬  ┬  ┌─┐  ╦ ╦┌─┐┬─┐┬  ┌┬┐ " << endl;
  cout << " ╠═╣├┤ │  │  │ │  ║║║│ │├┬┘│   ││ " << endl;
  cout << " ╩ ╩└─┘┴─┘┴─┘└─┘  ╚╩╝└─┘┴└─┴─┘─┴┘ " << endl;
  cout << endl;

  vec2f testvec2_1;  vec2f testvec2_2(0.f, 0.f);
  vec3f testvec3_1;  vec3f testvec3_2(0.f, 0.f, 0.f);

  image test1(xdim, ydim);
  test1.black_image();
  test1.output_image("black.png");

  image test2(xdim, ydim);
  test2.xor_pattern();
  test2.output_image("xor.png");

  image test3(xdim, ydim);
  test3.xor_pattern_threaded();
  test3.output_image("xor_threaded.png");

  return 0;
}

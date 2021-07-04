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

  image test1, test2, test3;

  black_image(xdim, ydim, test1);
  xor_pattern(xdim, ydim, test2);
  xor_pattern_threaded(xdim, ydim, test3);

  output_image("black.png", test1);
  output_image("xor.png", test2);
  output_image("xor_threaded.png", test3);

  return 0;
}

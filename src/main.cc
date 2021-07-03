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

  image test(xdim, ydim);
  test.xor_pattern();
  test.output("xor.png");

  return 0;
}

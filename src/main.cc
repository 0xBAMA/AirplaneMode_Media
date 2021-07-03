#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "includes.h"
#include "AMvector.h"

// AirportMode - a minimal dependency pathtracer

int main(int argc, char const *argv[])
{
  cout << endl;
  cout << " ╦ ╦┌─┐┬  ┬  ┌─┐  ╦ ╦┌─┐┬─┐┬  ┌┬┐ " << endl;
  cout << " ╠═╣├┤ │  │  │ │  ║║║│ │├┬┘│   ││ " << endl;
  cout << " ╩ ╩└─┘┴─┘┴─┘└─┘  ╚╩╝└─┘┴└─┴─┘─┴┘ " << endl;
  cout << endl;

  vec2<float> testvec2_1;
  vec2<float> testvec2_2(0., 0.);

  vec3<float> testvec3_1;
  vec3<float> testvec3_2(0., 0., 0.);


  /* std::vector<unsigned char> bytes;
  for(int y = 0; y < ydim; y++)
  for(int x = 0; x < xdim; x++){
    bytes.push_back(x ^ y);
    bytes.push_back(x ^ y);
    bytes.push_back(x ^ y);
    bytes.push_back(x ^ y);
  }
  stbi_write_png("../xor.png", xdim, ydim, 4, &bytes[0], xdim * 4); */

  return 0;
}

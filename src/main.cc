// AirplaneMode - a minimal dependency pathtracer

#include "io.h"
#include "AMvector.h"

// Renderer settings
const int xdim = 1920;
const int ydim = 1080;
const int nsamples = 64;

int main(int argc, char const *argv[])
{
  cout << endl;
  cout << " ╦ ╦┌─┐┬  ┬  ┌─┐  ╦ ╦┌─┐┬─┐┬  ┌┬┐ " << endl;
  cout << " ╠═╣├┤ │  │  │ │  ║║║│ │├┬┘│   ││ " << endl;
  cout << " ╩ ╩└─┘┴─┘┴─┘└─┘  ╚╩╝└─┘┴└─┴─┘─┴┘ " << endl;
  cout << endl << flush;

  image test_render(xdim, ydim);
  test_render.render_scene(nsamples);
  test_render.output_image("render_output.png");

  return 0;
}

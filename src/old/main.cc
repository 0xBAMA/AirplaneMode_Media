// AirplaneMode - a minimal dependency pathtracer
#include "io.h"
#include <chrono>

// Renderer settings
const int xdim = 1920/4;
const int ydim = 1080/4;
const int nsamples = 3;

int main(int argc, char const *argv[]){
  // start timer
  auto tstart = std::chrono::high_resolution_clock::now();

  // render the test image + write png
  image test_render(xdim, ydim);
  test_render.render_scene(nsamples);
  test_render.output_image("render_output.png");

  // report total time
  cout << "Total Render Time: " <<
    std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now()-tstart).count()/1000.
        << " seconds" << endl;

  return 0;
}

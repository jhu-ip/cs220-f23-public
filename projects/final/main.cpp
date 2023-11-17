#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "exception.h"
#include "plot.h"
#include "reader.h"
#include "renderer.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Usage: plot <input file> <output file>\n";
    return 1;
  }

  std::ifstream in(argv[1]);
  if (!in.is_open()) {
    std::cerr << "Error: couldn't open input file " << argv[1] << "\n";
    return 1;
  }

  std::ofstream out(argv[2]);
  if (!out.is_open()) {
    std::cerr << "Error: couldn't open output file " << argv[2] << "\n";
    return 1;
  }

  // TODO: make sure exceptions are handled properly

  Plot plot;

  // read the plot description
  Reader reader;
  reader.read_input(in, plot);

  // render the plot to an Image
  Renderer renderer(plot);
  std::unique_ptr<Image> img(renderer.render());

  // write the Image as a PNG file
  img->write_png(out);
  std::cout << "Wrote plot image successfully!\n";

  return 0;
}

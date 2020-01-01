#include <iostream>              // for cerr, cout
#include "dfiler/cli/options.h"  // for Options

int main(int argc, char** argv) {
  auto options = dfiler::cli::Options(argv[0], "A tool for managing dotfiles and such");
  options.Parse(argc, argv);

  std::cout << "Done" << std::endl;
}

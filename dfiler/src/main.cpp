#include <iostream>              // for cerr, cout
#include <memory>                // for unique_ptr
#include "dfiler/cli/command.h"  // for Command
#include "dfiler/cli/options.h"  // for Options

int main(int argc, char** argv) {
  auto options = dfiler::cli::Options(argv[0], "A tool for managing dotfiles and such");
  auto cmd = options.Parse(argc, argv);

  return cmd->Execute(std::cout, std::cerr);
}

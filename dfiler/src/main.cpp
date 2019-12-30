#include <iostream>

#include <dfiler/dfiler.h>

int main(int argc, char** argv) {
  auto options = dfiler::cli::Options(argv[0], "A tool for managing dotfiles and such");
  auto cmd = options.Parse(argc, argv);

  return cmd->Execute(std::cout, std::cerr);
}

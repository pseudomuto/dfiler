#include "dfiler/cli/options.h"
#include <cxxopts.hpp>  // for value, Options, OptionAdder
#include <memory>       // for shared_ptr

namespace dfiler::cli {
void Options::Parse(int argc, char** argv) {
  auto options = cxxopts::Options(name_, description_);

  options.positional_help("COMMAND");
  options.add_options()
      ("cmd", "the command to run", cxxopts::value(command_))
      ("h,help", "show this help message", cxxopts::value(help_));

  options.add_options("symlink")
      ("s,source", "the image directory", cxxopts::value(source_))
      ("t,target", "the target directory", cxxopts::value(target_))
      ("dryrun", "don't actually perform any symlinking", cxxopts::value(dryRun_));

  options.parse_positional("cmd");
  options.parse(argc, argv);

  helpText_ = options.help();
}
}  // namespace dfiler::cli

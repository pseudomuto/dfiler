#include <dfiler/dfiler.h>
#include <cxxopts.hpp>

#include "help_command.h"

namespace {
struct Flags {
  std::string command;
  bool help;
};

auto MakeOptions(const std::string& name, const std::string& description, Flags& flags) {
  auto options = cxxopts::Options(name, description);

  options.positional_help("COMMAND");
  options.add_options()("cmd", "the command to run", cxxopts::value(flags.command))("h, help", "show this help message",
                                                                                    cxxopts::value(flags.help));
  options.parse_positional("cmd");
  return options;
}
}  // namespace

namespace dfiler::cli {
std::unique_ptr<Command> Options::Parse(int argc, char**& argv) {
  auto flags = Flags();
  auto options = MakeOptions(name_, description_, flags);
  auto args = options.parse(argc, argv);

  if (flags.help || flags.command == "help") {
    return std::make_unique<HelpCommand>(options.help());
  }

  return std::make_unique<HelpCommand>(options.help(), true);
}
}  // namespace dfiler::cli

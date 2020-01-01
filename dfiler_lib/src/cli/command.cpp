#include "dfiler/cli/command.h"
#include <map>                   // for map
#include <string>                // for operator<, operator==, basic_string
#include "dfiler/cli/options.h"  // for Options
#include "help_command.h"        // for HelpCommand
#include "symlink_command.h"     // for SymlinkCommand

namespace {
enum class Cmd { Help, Symlink };

std::map<std::string, Cmd> availableCommands = {{"help", Cmd::Help}, {"symlink", Cmd::Symlink}};
}  // namespace

namespace dfiler::cli {
std::unique_ptr<Command> Command::FromOptions(Options& options) {
  if (options.Help() || options.Command() == "help") {
    return std::make_unique<HelpCommand>(options.HelpText());
  }

  switch (availableCommands[options.Command()]) {
    case Cmd::Symlink:
      return std::make_unique<SymlinkCommand>(options.Source(), options.Target(), options.DryRun());
    default:
      return std::make_unique<HelpCommand>(options.HelpText(), true);
  }
}
}  // namespace dfiler::cli

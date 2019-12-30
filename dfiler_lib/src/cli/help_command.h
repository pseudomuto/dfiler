#pragma once

#include <iosfwd>                // for ostream, string
#include <type_traits>           // for move
#include "dfiler/cli/command.h"  // for Command

namespace dfiler::cli {
class HelpCommand : public Command {
 public:
  explicit HelpCommand(std::string helpText, bool isErr = false) : helpText_(std::move(helpText)), isErr_(isErr){};

  int Execute(std::ostream& out, std::ostream& err) const override;

 private:
  const std::string helpText_;
  const bool isErr_;
};
}  // namespace dfiler::cli

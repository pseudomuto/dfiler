#pragma once

#include <iosfwd>                // for ostream
#include <string>                // for string
#include <type_traits>           // for move
#include "dfiler/cli/command.h"  // for Command

namespace dfiler::cli {
class HelpCommand : public Command {
 public:
  explicit HelpCommand(std::string helpText, bool isErr = false) : helpText_(std::move(helpText)), isErr_(isErr){};

  int Execute(std::ostream& out, std::ostream& err) const override;

  auto HelpText() const noexcept { return helpText_; }
  auto IsError() const noexcept { return isErr_; }

 private:
  const std::string helpText_;
  const bool isErr_;
};
}  // namespace dfiler::cli

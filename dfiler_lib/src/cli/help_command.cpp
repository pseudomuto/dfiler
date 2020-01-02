#include "help_command.h"
#include <ostream>  // for operator<<, endl, ostream, basic_ostream

namespace dfiler::cli {
int HelpCommand::Execute(std::ostream& out, std::ostream& err) const {
  if (isErr_) {
    err << helpText_ << std::endl;
  } else {
    out << helpText_ << std::endl;
  }

  return isErr_ ? 1 : 0;
}
}  // namespace dfiler::cli
